// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStorage::NIndirection
{
	template <typename t_CType, typename t_CAllocator>
	struct TCIndirection;
}

#include "Private/Malterlib_Storage_Indirection_Traits.h"

namespace NMib::NStorage
{
	template <typename t_CType>
	concept cIsIndirection = NPrivate::TCIsIndirectionHelper<t_CType>::mc_Value;
}

#include "Private/Malterlib_Storage_Indirection_Helpers.h"

namespace NMib::NStorage::NIndirection
{
	template <typename t_CType, typename t_CAllocator = NMib::NMemory::CDefaultAllocator>
	struct TCIndirection final
	{
	protected:
		struct CData : public t_CAllocator
		{
			t_CType *m_pPointTo;
		};

		CData m_Data;

		t_CAllocator &fp_GetAllocator();

		template <typename tf_CDummy>
		void fp_Delete();
		void fp_Delete();

		template <typename tf_CDummy>
		void fp_Create();
		void fp_Create();

	public:
		mark_artificial mark_nodebug inline_always t_CType const &f_Get() const &;
		mark_artificial mark_nodebug inline_always t_CType &f_Get() &;
		mark_artificial mark_nodebug inline_always t_CType &&f_Get() &&;

	public:
		template <typename ...tfp_CParams>
		mark_artificial inline_always auto operator () (tfp_CParams && ...p_Params);

		template <typename ...tfp_CParams>
		mark_artificial inline_always auto operator () (tfp_CParams && ...p_Params) const;

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Member access																						|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename tf_CMemberPtr>
		NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *> operator ->* (tf_CMemberPtr const &_MemberPtr)
			requires (NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>)
		;

		template <typename tf_CMemberPtr>
		NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>> operator ->* (tf_CMemberPtr const &_MemberPtr)
			requires (NTraits::cIsMemberObjectPointer<tf_CMemberPtr>)
		;

		template <typename tf_CMemberPtr>
		NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, NTraits::TCAddConst<t_CType> *> operator ->* (tf_CMemberPtr const &_MemberPtr) const
			requires (NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>)
		;

		template <typename tf_CMemberPtr>
		auto operator ->* (tf_CMemberPtr const &_MemberPtr) const -> NTraits::TCAddLValueReference<NTraits::TCAddConst<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
			requires (NTraits::cIsMemberObjectPointer<tf_CMemberPtr>)
		;

	public:
		using CType = t_CType;

		TCIndirection();
		~TCIndirection();

		template <typename ...tfp_CParams>
		TCIndirection(tfp_CParams && ...p_Params)
			requires NTraits::cIsPlacementNewConstructibleWith<t_CType, tfp_CParams && ...>
		;

		TCIndirection(TCIndirection const &_Other);
		TCIndirection(TCIndirection &_Other);
		TCIndirection(TCIndirection &&_Other);
		template <typename tf_CParam0>
		TCIndirection &operator = (tf_CParam0 &&_Param0);
		TCIndirection &operator = (TCIndirection const &_Other);
		TCIndirection &operator = (TCIndirection &_Other);
		TCIndirection &operator = (TCIndirection &&_Other);
		mark_artificial mark_nodebug inline_always operator t_CType const & () const;
		mark_artificial mark_nodebug inline_always operator t_CType & ();

		template <typename tf_CStream>
		void f_Stream(tf_CStream &_Stream)
		{
			_Stream % this->f_Get();
		}

		template <typename tf_CStr>
		void f_Format(tf_CStr &o_String) const;

		template <typename tf_CRight>
		auto operator <=> (tf_CRight const &_Right) const noexcept(noexcept(this->f_Get() <=> _Right))
		{
			return this->f_Get() <=> _Right;
		}

		template <typename tf_CType, typename tf_CAllocator>
		auto operator <=> (TCIndirection<tf_CType, tf_CAllocator> const &_Right) const noexcept(noexcept(this->f_Get() <=> _Right.f_Get()))
		{
			return this->f_Get() <=> _Right.f_Get();
		}

		template <typename tf_CRight>
		auto operator == (tf_CRight const &_Right) const noexcept(noexcept(this->f_Get() == _Right))
		{
			return this->f_Get() == _Right;
		}

		template <typename tf_CType, typename tf_CAllocator>
		auto operator == (TCIndirection<tf_CType, tf_CAllocator> const &_Right) const noexcept(noexcept(this->f_Get() == _Right.f_Get()))
		{
			return this->f_Get() == _Right.f_Get();
		}
	};
}

namespace NMib::NStorage
{
	template <typename t_CType, typename t_CAllocator = NMib::NMemory::CDefaultAllocator>
	using TCIndirection = NIndirection::TCIndirection<t_CType, t_CAllocator>;
}

namespace NMib
{
	template <typename tf_CType>
	NStorage::TCIndirection<NTraits::TCDecay<tf_CType>> fg_Indirect(tf_CType &&_Type)
	{
		return NStorage::TCIndirection<NTraits::TCDecay<tf_CType>>(fg_Forward<tf_CType>(_Type));
	}
}

#include "Malterlib_Storage_Indirection.hpp"

#ifndef DMibPNoShortCuts
using namespace NMib::NStorage;
#endif
