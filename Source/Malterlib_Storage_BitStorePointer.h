// Copyright © 2022 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once
namespace NMib::NStorage
{
	template <typename t_CType, mint t_nBits = 2> // Safe for 32 bit systems
	struct TCBitStorePointer
	{
		TCBitStorePointer()
		{
		}

		// Assign
		TCBitStorePointer(t_CType *_pPtr, mint _Bits = 0)
			: mp_PointTo(fsp_ToInt(_pPtr))
			, mp_Bits(_Bits)
		{
		}

		template <typename tf_CType>
		TCBitStorePointer(TCExplicit<tf_CType> &&_Other, mint _Bits = 0)
			: mp_PointTo(fsp_ToInt(static_cast<t_CType *>(*_Other)))
			, mp_Bits(_Bits)
		{
		}

		TCBitStorePointer(TCBitStorePointer const &_Other, mint _Bits = 0)
			: mp_PointTo(_Other.mp_PointTo)
			, mp_Bits(_Bits)
		{
			// Let bits be the same
		}

		TCBitStorePointer &operator = (t_CType *_pPtr)
		{
			mp_PointTo = fsp_ToInt(_pPtr);
			return *this;
		}

		void f_SetBoth(t_CType *_pPtr, mint _Bits)
		{
			mp_PointTo = fsp_ToInt(_pPtr);
			mp_Bits = _Bits;
		}

		void f_SetBoth(TCBitStorePointer const &_Other)
		{
			mp_PointTo = _Other.mp_PointTo;
			mp_Bits = _Other.mp_Bits;
		}

		TCBitStorePointer &operator = (TCBitStorePointer const &_Other)
		{
			mp_PointTo = _Other.mp_PointTo;
			return *this;
		}

		template <typename tf_CType>
		TCBitStorePointer &operator =(TCExplicit<tf_CType> &&_Other)
		{
			mp_PointTo = fsp_ToInt(static_cast<t_CType *>(*_Other));
			return *this;
		}

		TCBitStorePointer &f_SetBits(mint _Bits)
		{
			DMibFastCheck((_Bits & ((mint(1u) << t_nBits) - 1)) == _Bits); // More bits that fits
			mp_Bits = _Bits;
			return *this;
		}

		TCBitStorePointer &f_ChangeBits(mint _Remove, mint _Add)
		{
			DMibFastCheck((_Remove & ((mint(1u) << t_nBits) - 1)) == _Remove); // More bits that fits
			DMibFastCheck((_Add & ((mint(1u) << t_nBits) - 1)) == _Add); // More bits that fits
			mp_Bits = (mp_Bits & ~_Remove) | _Add;
			return *this;
		}

		mint f_GetBits() const
		{
			return mp_Bits;
		}

		// Access
		mark_nodebug t_CType *f_Get() const
		{
			return fsp_FromInt(mp_PointTo);
		}

		mark_nodebug operator t_CType *() const
		{
			return fsp_FromInt(mp_PointTo);
		}

		mark_nodebug t_CType *operator ->() const
		{
			return fsp_FromInt(mp_PointTo);
		}

		template <typename t_CMemberPtr>
		mark_artificial mark_nodebug inline_always typename TCEnableIf
			<
				NTraits::TCIsMemberFunctionPointer<t_CMemberPtr>::mc_Value
				, NFunction::TCMemberFunctionBoundFunctor
				<
					t_CMemberPtr
					, t_CType *
				>
			>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, fsp_FromInt(mp_PointTo));
		}

		template <typename t_CMemberPtr>
		mark_artificial mark_nodebug inline_always typename TCEnableIf
			<
				NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
				, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
			>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return fsp_FromInt(mp_PointTo)->*_MemberPtr;
		}

		mark_nodebug t_CType &operator *() const
		{
			return *fsp_FromInt(mp_PointTo);
		}

		template <typename tf_CType>
		bool operator == (tf_CType const &_Other) const
		{
			return operator t_CType *() == static_cast<t_CType *>(_Other);
		}

		template <typename tf_CType>
		bool operator == (TCBitStorePointer<tf_CType> const &_Other) const
		{
			return operator t_CType *() == _Other.operator tf_CType *();
		}

	private:
		static inline_always mint fsp_ToInt(t_CType *_pPtr)
		{
			DMibFastCheck(!(reinterpret_cast<mint>(_pPtr) & ((mint(1u) << t_nBits) - 1))); // Unaligned pointer not supported
			return reinterpret_cast<mint>(_pPtr) >> t_nBits;
		}

		static inline_always constexpr t_CType *fsp_FromInt(mint _Pointer)
		{
			return reinterpret_cast<t_CType *>(_Pointer << t_nBits);
		}

		mint mp_PointTo:sizeof(mint)*8 - t_nBits;
		mint mp_Bits:t_nBits;
	};
}

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif
