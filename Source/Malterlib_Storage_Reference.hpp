// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStorage::NReference
{
	template <typename t_CType>
	mark_artificial mark_nodebug inline_always t_CType &TCReference<t_CType>::f_Get() const volatile
	{
		return *mp_Data.m_pPointTo;
	}

	template <typename t_CType>
	template <typename ...tfp_CParams>
	mark_artificial inline_always auto TCReference<t_CType>::operator () (tfp_CParams && ...p_Params) const volatile
		-> NTraits::TCCallableReturnTypeFor<t_CType, void (tfp_CParams && ...p_Params)>
		requires (NTraits::cIsCallableWith<t_CType, void (tfp_CParams && ...p_Params)>)
	{
		return f_Get()(fg_Forward<tfp_CParams>(p_Params)...);
	}

	template <typename t_CType>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCReference<t_CType>::operator ->* (tf_CMemberPtr const &_MemberPtr) const volatile
		-> NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>
		requires (NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>)
	{
		return NFunction::fg_MemberFunctionFunctor(_MemberPtr, &f_Get());
	}

	template <typename t_CType>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCReference<t_CType>::operator ->* (tf_CMemberPtr const &_MemberPtr) const volatile
		-> NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>
		requires (NTraits::cIsMemberObjectPointer<tf_CMemberPtr>)
	{
		return f_Get().*_MemberPtr;
	}

	template <typename t_CType>
	TCReference<t_CType>::TCReference(t_CType &_Param0)
	{
		this->mp_Data.m_pPointTo = &_Param0;
	}

	template <typename t_CType>
	TCReference<t_CType>::TCReference(TCReference const &_Other)
	{
		this->mp_Data.m_pPointTo = _Other.mp_Data.m_pPointTo;
	}

	template <typename t_CType>
	TCReference<t_CType>::TCReference(TCReference volatile &_Other)
	{
		this->mp_Data.m_pPointTo = _Other.mp_Data.m_pPointTo;
	}

	template <typename t_CType>
	TCReference<t_CType>::TCReference(TCReference const volatile &_Other)
	{
		this->mp_Data.m_pPointTo = _Other.mp_Data.m_pPointTo;
	}

	template <typename t_CType>
	TCReference<t_CType>::TCReference(TCReference &_Other)
	{
		this->mp_Data.m_pPointTo = _Other.mp_Data.m_pPointTo;
	}

	template <typename t_CType>
	TCReference<t_CType>::TCReference(TCReference &&_Other)
	{
		this->mp_Data.m_pPointTo = _Other.mp_Data.m_pPointTo;
	}

	template <typename t_CType>
	mark_artificial mark_nodebug inline_always TCReference<t_CType>::operator t_CType & () const volatile
	{
		return this->f_Get();
	}
}

namespace NMib
{
	template <typename tf_CType>
	NStorage::TCReference<tf_CType> fg_Reference(tf_CType &_Type)
	{
		return NStorage::TCReference<tf_CType>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConst<tf_CType>> fg_ConstReference(tf_CType const &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConst<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>> fg_VolatileReference(tf_CType volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>> fg_ConstVolatileReference(tf_CType const volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<tf_CType> fg_Reference(NStorage::TCReference<tf_CType> &&_Type)
	{
		return NStorage::TCReference<tf_CType>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<tf_CType> fg_Reference(NStorage::TCReference<tf_CType> &_Type)
	{
		return NStorage::TCReference<tf_CType>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<tf_CType> fg_Reference(NStorage::TCReference<tf_CType> const &_Type)
	{
		return NStorage::TCReference<tf_CType>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<tf_CType> fg_Reference(NStorage::TCReference<tf_CType> volatile &_Type)
	{
		return NStorage::TCReference<tf_CType>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<tf_CType> fg_Reference(NStorage::TCReference<tf_CType> const volatile &_Type)
	{
		return NStorage::TCReference<tf_CType>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConst<tf_CType>> fg_ConstReference(NStorage::TCReference<tf_CType> &&_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConst<tf_CType>>(fg_Move(_Type));
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConst<tf_CType>> fg_ConstReference(NStorage::TCReference<tf_CType> &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConst<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConst<tf_CType>> fg_ConstReference(NStorage::TCReference<tf_CType> const &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConst<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConst<tf_CType>> fg_ConstReference(NStorage::TCReference<tf_CType> volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConst<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConst<tf_CType>> fg_ConstReference(NStorage::TCReference<tf_CType> const volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConst<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>> fg_VolatileReference(NStorage::TCReference<tf_CType> &&_Type)
	{
		return NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>>(fg_Move(_Type));
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>> fg_VolatileReference(NStorage::TCReference<tf_CType> &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>> fg_VolatileReference(NStorage::TCReference<tf_CType> const &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>> fg_VolatileReference(NStorage::TCReference<tf_CType> volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>> fg_VolatileReference(NStorage::TCReference<tf_CType> const volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>> fg_ConstVolatileReference(NStorage::TCReference<tf_CType> &&_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>>(fg_Move(_Type));
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>> fg_ConstVolatileReference(NStorage::TCReference<tf_CType> &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>> fg_ConstVolatileReference(NStorage::TCReference<tf_CType> const &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>> fg_ConstVolatileReference(NStorage::TCReference<tf_CType> volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>> fg_ConstVolatileReference(NStorage::TCReference<tf_CType> const volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>>(_Type);
	}
}
