// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStorage::NReference
{
	template <typename t_CType>
	mark_artificial mark_nodebug inline_always t_CType &TCReference<t_CType>::f_Get() const volatile
	{
		return *m_Data.m_pPointTo;
	}

	template <typename t_CType>
	template <typename... tfp_CParams>
	mark_artificial inline_always auto TCReference<t_CType>::operator () (tfp_CParams &&...p_Params) const volatile
		-> NTraits::TCCallableReturnTypeFor<t_CType, void (tfp_CParams &&...)>
		requires (NTraits::TCIsCallableWith<t_CType, void (tfp_CParams &&...)>::mc_Value)
	{
		return f_Get()(fg_Forward<tfp_CParams>(p_Params)...);
	}

	template <typename t_CType>
	template <typename t_CMemberPtr>
	mark_artificial mark_nodebug inline_always NFunction::TCMemberFunctionBoundFunctor<t_CMemberPtr, t_CType *> TCReference<t_CType>::operator ->* (t_CMemberPtr const &_MemberPtr) const volatile
		requires (NTraits::TCIsMemberFunctionPointer<t_CMemberPtr>::mc_Value)
	{
		return NFunction::fg_MemberFunctionFunctor(_MemberPtr, &f_Get());
	}

	template <typename t_CType>
	template <typename t_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCReference<t_CType>::operator ->* (t_CMemberPtr const &_MemberPtr) const volatile
		 -> typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
		requires (NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value)
	{
		return f_Get().*_MemberPtr;
	}

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
	mark_artificial mark_nodebug inline_always TCReference<t_CType>::operator t_CType & () const volatile
	{
		return this->f_Get();
	}
}
