// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStorage::NIndirection
{
	template <typename t_CType, typename t_CAllocator>
	class TCIndirection;
}

#include "Private/Malterlib_Storage_Indirection_Traits.h"

namespace NMib::NStorage
{
	template <typename t_CType>
	struct TCIsIndirection : public NTraits::TCCompileTimeConstant<bool, NPrivate::TCIsIndirectionHelper<t_CType>::mc_Value>
	{
	};
}

#include "Private/Malterlib_Storage_Indirection_Helpers.h"

namespace NMib::NStorage::NIndirection
{
	template <typename t_CType, typename t_CAllocator = NMib::NMemory::CDefaultAllocator>
	class TCIndirection final
	{
	protected:
		struct CData : public t_CAllocator
		{
			t_CType *m_pPointTo;
		};

		CData m_Data;

		t_CAllocator &fp_GetAllocator();

		template <typename t_CDummy>
		void fp_Delete();
		void fp_Delete();

		template <typename t_CDummy>
		void fp_Create();
		void fp_Create();

	public:

		mark_artificial mark_nodebug inline_always t_CType const &f_Get() const &;
		mark_artificial mark_nodebug inline_always t_CType &f_Get() &;
		mark_artificial mark_nodebug inline_always t_CType &&f_Get() &&;

	public:

		template <typename... tfp_CParams>
		mark_artificial inline_always auto operator () (tfp_CParams &&... p_Params);

		template <typename... tfp_CParams>
		mark_artificial inline_always auto operator () (tfp_CParams &&...p_Params) const;

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Member access																						|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename t_CMemberPtr>
		NFunction::TCMemberFunctionBoundFunctor<t_CMemberPtr, t_CType *> operator ->* (t_CMemberPtr const &_MemberPtr)
			requires (NTraits::TCIsMemberFunctionPointer<t_CMemberPtr>::mc_Value)
		;

		template <typename t_CMemberPtr>
		typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType operator ->* (t_CMemberPtr const &_MemberPtr)
			requires (NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value)
		;

		template <typename t_CMemberPtr>
		NFunction::TCMemberFunctionBoundFunctor<t_CMemberPtr, typename NTraits::TCAddConst<t_CType>::CType *> operator ->* (t_CMemberPtr const &_MemberPtr) const
			requires (NTraits::TCIsMemberFunctionPointer<t_CMemberPtr>::mc_Value)
		;

		template <typename t_CMemberPtr>
		auto operator ->* (t_CMemberPtr const &_MemberPtr) const
			-> typename NTraits::TCAddLValueReference<typename NTraits::TCAddConst<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType>::CType
			requires (NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value)
		;

	public:
		typedef t_CType CType;

		TCIndirection();
		~TCIndirection();

		template <typename... tfp_CParams>
		TCIndirection(tfp_CParams && ... p_Params)
			requires NTraits::cConstructibleWith<t_CType, tfp_CParams &&...>
		;

		TCIndirection(TCIndirection const &_Other);
		TCIndirection(TCIndirection &_Other);
		TCIndirection(TCIndirection &&_Other);
		template <typename t_CParam0>
		TCIndirection &operator =(t_CParam0 &&_Param0);
		TCIndirection &operator =(TCIndirection const &_Other);
		TCIndirection &operator =(TCIndirection &_Other);
		TCIndirection &operator =(TCIndirection &&_Other);
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
		auto operator <=> (tf_CRight const &_Right) const
		{
			return this->f_Get() <=> _Right;
		}

		template <typename tf_CType, typename tf_CAllocator>
		auto operator <=> (TCIndirection<tf_CType, tf_CAllocator> const &_Right) const
		{
			return this->f_Get() <=> _Right.f_Get();
		}

		template <typename tf_CRight>
		auto operator == (tf_CRight const &_Right) const
		{
			return this->f_Get() == _Right;
		}

		template <typename tf_CType, typename tf_CAllocator>
		auto operator == (TCIndirection<tf_CType, tf_CAllocator> const &_Right) const
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
	template <typename t_CType>
	NStorage::TCIndirection<typename NTraits::TCDecay<t_CType>::CType> fg_Indirect(t_CType &&_Type)
	{
		return NStorage::TCIndirection<typename NTraits::TCDecay<t_CType>::CType>(fg_Forward<t_CType>(_Type));
	}
}

#include "Malterlib_Storage_Indirection.hpp"

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif
