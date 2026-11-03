// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once
namespace NMib::NStorage
{
	template <typename t_CType, umint t_nBits = 2> // Safe for 32 bit systems
	struct TCBitStorePointer
	{
		TCBitStorePointer();

		// Assign
		TCBitStorePointer(t_CType *_pPtr, umint _Bits = 0);
		template <typename tf_CType>
		TCBitStorePointer(TCExplicit<tf_CType> &&_Other, umint _Bits = 0);
		TCBitStorePointer(TCBitStorePointer const &_pOther, umint _Bits = 0);

		TCBitStorePointer &operator = (t_CType *_pPtr);
		void f_SetBoth(t_CType *_pPtr, umint _Bits);
		void f_SetBoth(TCBitStorePointer const &_pOther);
		TCBitStorePointer &operator = (TCBitStorePointer const &_pOther);
		template <typename tf_CType>
		TCBitStorePointer &operator = (TCExplicit<tf_CType> &&_Other);

		TCBitStorePointer &f_SetBits(umint _Bits);
		TCBitStorePointer &f_ChangeBits(umint _Remove, umint _Add);
		umint f_GetBits() const;

		// Access
		mark_nodebug t_CType *f_Get() const;
		mark_nodebug operator t_CType * () const;
		mark_nodebug t_CType *operator -> () const;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
		;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
		;

		mark_nodebug t_CType &operator * () const;

		template <typename tf_CType>
		bool operator == (tf_CType const &_Other) const noexcept;
		template <typename tf_CType>
		bool operator == (TCBitStorePointer<tf_CType> const &_pOther) const noexcept;

	private:
		static inline_always umint fsp_ToInt(t_CType *_pPtr);
		static inline_always constexpr t_CType *fsp_FromInt(umint _Pointer);

		umint mp_PointTo:sizeof(umint) * 8 - t_nBits;
		umint mp_Bits:t_nBits;
	};
}

#include "Malterlib_Storage_BitStorePointer.hpp"

#ifndef DMibPNoShortCuts
using namespace NMib::NStorage;
#endif
