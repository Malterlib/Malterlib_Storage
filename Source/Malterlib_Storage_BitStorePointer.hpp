// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStorage
{
	template <typename t_CType, umint t_nBits>
	TCBitStorePointer<t_CType, t_nBits>::TCBitStorePointer()
	{
	}

	template <typename t_CType, umint t_nBits>
	TCBitStorePointer<t_CType, t_nBits>::TCBitStorePointer(t_CType *_pPtr, umint _Bits)
		: mp_PointTo(fsp_ToInt(_pPtr))
		, mp_Bits(_Bits)
	{
	}

	template <typename t_CType, umint t_nBits>
	template <typename tf_CType>
	TCBitStorePointer<t_CType, t_nBits>::TCBitStorePointer(TCExplicit<tf_CType> &&_Other, umint _Bits)
		: mp_PointTo(fsp_ToInt(static_cast<t_CType *>(*_Other)))
		, mp_Bits(_Bits)
	{
	}

	template <typename t_CType, umint t_nBits>
	TCBitStorePointer<t_CType, t_nBits>::TCBitStorePointer(TCBitStorePointer const &_pOther, umint _Bits)
		: mp_PointTo(_pOther.mp_PointTo)
		, mp_Bits(_Bits)
	{
		// Let bits be the same
	}

	template <typename t_CType, umint t_nBits>
	auto TCBitStorePointer<t_CType, t_nBits>::operator = (t_CType *_pPtr) -> TCBitStorePointer &
	{
		mp_PointTo = fsp_ToInt(_pPtr);
		return *this;
	}

	template <typename t_CType, umint t_nBits>
	void TCBitStorePointer<t_CType, t_nBits>::f_SetBoth(t_CType *_pPtr, umint _Bits)
	{
		mp_PointTo = fsp_ToInt(_pPtr);
		mp_Bits = _Bits;
	}

	template <typename t_CType, umint t_nBits>
	void TCBitStorePointer<t_CType, t_nBits>::f_SetBoth(TCBitStorePointer const &_pOther)
	{
		mp_PointTo = _pOther.mp_PointTo;
		mp_Bits = _pOther.mp_Bits;
	}

	template <typename t_CType, umint t_nBits>
	auto TCBitStorePointer<t_CType, t_nBits>::operator = (TCBitStorePointer const &_pOther) -> TCBitStorePointer &
	{
		mp_PointTo = _pOther.mp_PointTo;
		return *this;
	}

	template <typename t_CType, umint t_nBits>
	template <typename tf_CType>
	auto TCBitStorePointer<t_CType, t_nBits>::operator = (TCExplicit<tf_CType> &&_Other) -> TCBitStorePointer &
	{
		mp_PointTo = fsp_ToInt(static_cast<t_CType *>(*_Other));
		return *this;
	}

	template <typename t_CType, umint t_nBits>
	auto TCBitStorePointer<t_CType, t_nBits>::f_SetBits(umint _Bits) -> TCBitStorePointer &
	{
		DMibFastCheck((_Bits & ((umint(1u) << t_nBits) - 1)) == _Bits); // More bits that fits
		mp_Bits = _Bits;
		return *this;
	}

	template <typename t_CType, umint t_nBits>
	auto TCBitStorePointer<t_CType, t_nBits>::f_ChangeBits(umint _Remove, umint _Add) -> TCBitStorePointer &
	{
		DMibFastCheck((_Remove & ((umint(1u) << t_nBits) - 1)) == _Remove); // More bits that fits
		DMibFastCheck((_Add & ((umint(1u) << t_nBits) - 1)) == _Add); // More bits that fits
		mp_Bits = (mp_Bits & ~_Remove) | _Add;
		return *this;
	}

	template <typename t_CType, umint t_nBits>
	umint TCBitStorePointer<t_CType, t_nBits>::f_GetBits() const
	{
		return mp_Bits;
	}

	template <typename t_CType, umint t_nBits>
	mark_nodebug t_CType *TCBitStorePointer<t_CType, t_nBits>::f_Get() const
	{
		return fsp_FromInt(mp_PointTo);
	}

	template <typename t_CType, umint t_nBits>
	mark_nodebug TCBitStorePointer<t_CType, t_nBits>::operator t_CType * () const
	{
		return fsp_FromInt(mp_PointTo);
	}

	template <typename t_CType, umint t_nBits>
	mark_nodebug t_CType *TCBitStorePointer<t_CType, t_nBits>::operator -> () const
	{
		return fsp_FromInt(mp_PointTo);
	}

	template <typename t_CType, umint t_nBits>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCBitStorePointer<t_CType, t_nBits>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
	{
		return NFunction::fg_MemberFunctionFunctor(_MemberPtr, fsp_FromInt(mp_PointTo));
	}

	template <typename t_CType, umint t_nBits>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCBitStorePointer<t_CType, t_nBits>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
	{
		return fsp_FromInt(mp_PointTo)->*_MemberPtr;
	}

	template <typename t_CType, umint t_nBits>
	mark_nodebug t_CType &TCBitStorePointer<t_CType, t_nBits>::operator * () const
	{
		return *fsp_FromInt(mp_PointTo);
	}

	template <typename t_CType, umint t_nBits>
	template <typename tf_CType>
	bool TCBitStorePointer<t_CType, t_nBits>::operator == (tf_CType const &_Other) const noexcept
	{
		return operator t_CType * () == static_cast<t_CType *>(_Other);
	}

	template <typename t_CType, umint t_nBits>
	template <typename tf_CType>
	bool TCBitStorePointer<t_CType, t_nBits>::operator == (TCBitStorePointer<tf_CType> const &_pOther) const noexcept
	{
		return operator t_CType * () == _pOther.operator tf_CType * ();
	}

	template <typename t_CType, umint t_nBits>
	inline_always umint TCBitStorePointer<t_CType, t_nBits>::fsp_ToInt(t_CType *_pPtr)
	{
		DMibFastCheck(!(reinterpret_cast<umint>(_pPtr) & ((umint(1u) << t_nBits) - 1))); // Unaligned pointer not supported
		return reinterpret_cast<umint>(_pPtr) >> t_nBits;
	}

	template <typename t_CType, umint t_nBits>
	inline_always constexpr t_CType *TCBitStorePointer<t_CType, t_nBits>::fsp_FromInt(umint _Pointer)
	{
		return reinterpret_cast<t_CType *>(_Pointer << t_nBits);
	}
}
