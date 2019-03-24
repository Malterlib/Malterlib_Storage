// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStorage::NReference
{
	template <typename t_CType>
	mark_artificial inline_always t_CType &TCReference<t_CType>::f_Get() const volatile
	{
		return *m_Data.m_pPointTo;
	}

	template <typename t_CType>
	template <typename... tfp_CParams>
	mark_artificial inline_always typename TCEnableIf
	<
		NTraits::TCIsCallableWith<t_CType, void (tfp_CParams &&...)>::mc_Value
		, typename NTraits::TCIsCallableWith<t_CType, void (tfp_CParams &&...)>::CReturnType
	>::CType
	TCReference<t_CType>::operator () (tfp_CParams &&...p_Params) const volatile
	{
		return f_Get()(fg_Forward<tfp_CParams>(p_Params)...);
	}

#ifndef DDocumentation_Doxygen

	template <typename t_CType>
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
	TCReference<t_CType>::operator ->* (t_CMemberPtr const &_MemberPtr) const volatile
	{
		return NFunction::fg_MemberFunctionFunctor(_MemberPtr, &f_Get());
	}

	template <typename t_CType>
	template <typename t_CMemberPtr>
	mark_artificial inline_always typename TCEnableIf
	<
		NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
		, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
	>::CType
	TCReference<t_CType>::operator ->* (t_CMemberPtr const &_MemberPtr) const volatile
	{
		return f_Get().*_MemberPtr;
	}

#endif

	template <typename t_CType>
	TCReference<t_CType>::TCReference(t_CType &_Param0)
	{
		this->m_Data.m_pPointTo = &_Param0;
	}

	template <typename t_CType>
	TCReference<t_CType>::TCReference(TCReference const &_Other)
	{
		this->m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
	}

	template <typename t_CType>
	TCReference<t_CType>::TCReference(TCReference volatile &_Other)
	{
		this->m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
	}

	template <typename t_CType>
	TCReference<t_CType>::TCReference(TCReference const volatile &_Other)
	{
		this->m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
	}

	template <typename t_CType>
	TCReference<t_CType>::TCReference(TCReference &_Other)
	{
		this->m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
	}

	template <typename t_CType>
	TCReference<t_CType>::TCReference(TCReference &&_Other)
	{
		this->m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
	}

	template <typename t_CType>
	mark_artificial inline_always TCReference<t_CType>::operator t_CType & () const volatile
	{
		return this->f_Get();
	}
}
