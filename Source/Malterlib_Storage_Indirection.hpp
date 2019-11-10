// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStorage::NIndirection
{
	template <typename t_CType, typename t_CAllocator>
	t_CAllocator &TCIndirection<t_CType, t_CAllocator>::fp_GetAllocator()
	{
		return m_Data;
	}

	template <typename t_CType, typename t_CAllocator>
	template <typename t_CDummy>
	void TCIndirection<t_CType, t_CAllocator>::fp_Delete()
	{
		if (m_Data.m_pPointTo)
		{
			fg_DeleteObject(fp_GetAllocator(), (t_CType *)m_Data.m_pPointTo);
			m_Data.m_pPointTo = nullptr;
		}
	}

	template <typename t_CType, typename t_CAllocator>
	void TCIndirection<t_CType, t_CAllocator>::fp_Delete()
	{
		fp_Delete<t_CType>();
	}

	template <typename t_CType, typename t_CAllocator>
	template <typename t_CDummy>
	void TCIndirection<t_CType, t_CAllocator>::fp_Create()
	{
		m_Data.m_pPointTo = fg_ConstructObject<t_CType>(fp_GetAllocator());
	}

	template <typename t_CType, typename t_CAllocator>
	void TCIndirection<t_CType, t_CAllocator>::fp_Create()
	{
		fp_Create<t_CType>();
	}

	template <typename t_CType, typename t_CAllocator>
	mark_artificial inline_always t_CType const &TCIndirection<t_CType, t_CAllocator>::f_Get() const
	{
		return *m_Data.m_pPointTo;
	}

	template <typename t_CType, typename t_CAllocator>
	mark_artificial inline_always t_CType &TCIndirection<t_CType, t_CAllocator>::f_Get()
	{
		return *m_Data.m_pPointTo;
	}

	template <typename t_CType, typename t_CAllocator>
	template <typename... tfp_CParams>
	mark_artificial inline_always auto TCIndirection<t_CType, t_CAllocator>::operator () (tfp_CParams &&... p_Params)
	{
		return this->f_Get()(fg_Forward<tfp_CParams>(p_Params)...);
	}

	template <typename t_CType, typename t_CAllocator>
	template <typename... tfp_CParams>
	mark_artificial inline_always auto TCIndirection<t_CType, t_CAllocator>::operator () (tfp_CParams &&...p_Params) const
	{
		return this->f_Get()(fg_Forward<tfp_CParams>(p_Params)...);
	}

#ifndef DDocumentation_Doxygen

	template <typename t_CType, typename t_CAllocator>
	template <typename t_CMemberPtr>
	mark_artificial inline_always typename TCEnableIf
		<
			NTraits::TCIsMemberFunctionPointer<t_CMemberPtr>::mc_Value
			, NFunction::TCMemberFunctionBoundFunctor
			<
				t_CMemberPtr
				, t_CType *
			>
		>::CType
	TCIndirection<t_CType, t_CAllocator>::operator ->* (t_CMemberPtr const &_MemberPtr)
	{
		return NFunction::fg_MemberFunctionFunctor(_MemberPtr, &(this->f_Get()));
	}

	template <typename t_CType, typename t_CAllocator>
	template <typename t_CMemberPtr>
	mark_artificial inline_always typename TCEnableIf
	<
		NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
		, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
	>::CType
	TCIndirection<t_CType, t_CAllocator>::operator ->* (t_CMemberPtr const &_MemberPtr)
	{
		return (this->f_Get()).*_MemberPtr;
	}

	template <typename t_CType, typename t_CAllocator>
	template <typename t_CMemberPtr>
	mark_artificial inline_always typename TCEnableIf
		<
			NTraits::TCIsMemberFunctionPointer<t_CMemberPtr>::mc_Value
			, NFunction::TCMemberFunctionBoundFunctor
			<
				t_CMemberPtr
				, typename NTraits::TCAddConst<t_CType>::CType *
			>
		>::CType
	TCIndirection<t_CType, t_CAllocator>::operator ->* (t_CMemberPtr const &_MemberPtr) const
	{
		return NFunction::fg_MemberFunctionFunctor(_MemberPtr, &(this->f_Get()));
	}

	template <typename t_CType, typename t_CAllocator>
	template <typename t_CMemberPtr>
	mark_artificial inline_always typename TCEnableIf
	<
		NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
		, typename NTraits::TCAddLValueReference<typename NTraits::TCAddConst<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType>::CType
	>::CType
	TCIndirection<t_CType, t_CAllocator>::operator ->* (t_CMemberPtr const &_MemberPtr) const
	{
		return (this->f_Get()).*_MemberPtr;
	}

#endif

	template <typename t_CType, typename t_CAllocator>
	TCIndirection<t_CType, t_CAllocator>::TCIndirection()
	{
		this->fp_Create();
	}

	template <typename t_CType, typename t_CAllocator>
	TCIndirection<t_CType, t_CAllocator>::~TCIndirection()
	{
		this->fp_Delete();
	}

	template <typename t_CType, typename t_CAllocator>
	template <typename tf_CParam0, typename... tfp_CParams>
	TCIndirection<t_CType, t_CAllocator>::TCIndirection(tf_CParam0 &&_Param0, tfp_CParams && ... p_Params)
	{
		this->m_Data.m_pPointTo = fg_ConstructObject<t_CType>(this->fp_GetAllocator(), fg_Forward<tf_CParam0>(_Param0), fg_Forward<tfp_CParams>(p_Params)...);
	}

	template <typename t_CType, typename t_CAllocator>
	TCIndirection<t_CType, t_CAllocator>::TCIndirection(TCIndirection const &_Other)
	{
		this->m_Data.m_pPointTo = fg_ConstructObject<t_CType>(this->fp_GetAllocator(), _Other.f_Get());
	}

	template <typename t_CType, typename t_CAllocator>
	TCIndirection<t_CType, t_CAllocator>::TCIndirection(TCIndirection &_Other)
	{
		this->m_Data.m_pPointTo = fg_ConstructObject<t_CType>(this->fp_GetAllocator(), _Other.f_Get());
	}

	template <typename t_CType, typename t_CAllocator>
	TCIndirection<t_CType, t_CAllocator>::TCIndirection(TCIndirection &&_Other)
	{
		this->m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
		_Other.m_Data.m_pPointTo = nullptr;
	}

	template <typename t_CType, typename t_CAllocator>
	template <typename t_CParam0>
	TCIndirection<t_CType, t_CAllocator> &TCIndirection<t_CType, t_CAllocator>::operator =(t_CParam0 &&_Param0)
	{
		this->f_Get() = fg_Forward<t_CParam0>(_Param0);
		return *this;
	}

	template <typename t_CType, typename t_CAllocator>
	TCIndirection<t_CType, t_CAllocator> &TCIndirection<t_CType, t_CAllocator>::operator =(TCIndirection const &_Other)
	{
		this->f_Get() = _Other.f_Get();
		return *this;
	}

	template <typename t_CType, typename t_CAllocator>
	TCIndirection<t_CType, t_CAllocator> &TCIndirection<t_CType, t_CAllocator>::operator =(TCIndirection &_Other)
	{
		this->f_Get() = _Other.f_Get();
		return *this;
	}

	template <typename t_CType, typename t_CAllocator>
	TCIndirection<t_CType, t_CAllocator> &TCIndirection<t_CType, t_CAllocator>::operator =(TCIndirection &&_Other)
	{
		this->fp_Delete();
		this->m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
		_Other.m_Data.m_pPointTo = nullptr;
		return *this;
	}

	template <typename t_CType, typename t_CAllocator>
	mark_artificial inline_always TCIndirection<t_CType, t_CAllocator>::operator t_CType const & () const
	{
		return this->f_Get();
	}

	template <typename t_CType, typename t_CAllocator>
	mark_artificial inline_always TCIndirection<t_CType, t_CAllocator>::operator t_CType & ()
	{
		return this->f_Get();
	}

	template <typename t_CType, typename t_CAllocator>
	template <typename tf_CStr>
	void TCIndirection<t_CType, t_CAllocator>::f_Format(tf_CStr &o_String) const
	{
		o_String += typename tf_CStr::CFormat("{}") << f_Get();
	}
}
