// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib
{
	template <typename tf_CVisitor, typename tf_CToVisit0>
	void fg_Visit(tf_CVisitor &&_Visitor, tf_CToVisit0 &&_ToVisit0) noexcept(noexcept(fg_Forward<tf_CToVisit0>(_ToVisit0).f_Visit(fg_Forward<tf_CVisitor>(_Visitor))))
	{
		fg_Forward<tf_CToVisit0>(_ToVisit0).f_Visit(fg_Forward<tf_CVisitor>(_Visitor));
	}

	template <typename tf_CReturn, typename tf_CVisitor, typename tf_CToVisit0>
	auto fg_VisitRet(tf_CVisitor &&_Visitor, tf_CToVisit0 &&_ToVisit0)
		noexcept(noexcept(fg_Forward<tf_CToVisit0>(_ToVisit0).template f_VisitRet<tf_CReturn>(fg_Forward<tf_CVisitor>(_Visitor))))
		-> tf_CReturn
	{
		return fg_Forward<tf_CToVisit0>(_ToVisit0).template f_VisitRet<tf_CReturn>(fg_Forward<tf_CVisitor>(_Visitor));
	}

	template <typename t_CRet, typename t_CVisitor, typename t_CToVisit>
	TCInnerVisitor<t_CRet, t_CVisitor, t_CToVisit>::TCInnerVisitor(t_CVisitor _Visitor, t_CToVisit _ToVisit)
		: m_Visitor(_Visitor)
		, m_ToVisit(_ToVisit)
	{
	}

	template <typename t_CRet, typename t_CVisitor, typename t_CToVisit>
	template <typename t_CInnerVisitor, typename t_CValue>
	TCInnerVisitor<t_CRet, t_CVisitor, t_CToVisit>::TCValueVisitor<t_CInnerVisitor, t_CValue>::TCValueVisitor(t_CInnerVisitor _Visitor, t_CValue _Value)
		: m_Visitor(_Visitor)
		, m_Value(_Value)
	{
	}

	template <typename t_CRet, typename t_CVisitor, typename t_CToVisit>
	template <typename t_CInnerVisitor, typename t_CValue>
	template <typename tf_CType>
	auto TCInnerVisitor<t_CRet, t_CVisitor, t_CToVisit>
		::TCValueVisitor<t_CInnerVisitor, t_CValue>::operator () (tf_CType &&_Type) noexcept(noexcept(m_Visitor(fg_Forward<t_CValue>(m_Value), fg_Forward<tf_CType>(_Type))))
		-> t_CRet
	{
		return m_Visitor(fg_Forward<t_CValue>(m_Value), fg_Forward<tf_CType>(_Type));
	}

	template <typename t_CRet, typename t_CVisitor, typename t_CToVisit>
	template <typename tf_CType>
	auto TCInnerVisitor<t_CRet, t_CVisitor, t_CToVisit>::operator () (tf_CType &&_Value)
		noexcept(noexcept(fg_VisitRet<t_CRet>(TCValueVisitor<t_CVisitor, tf_CType>(m_Visitor, _Value), fg_Forward<t_CToVisit>(m_ToVisit))))
		-> t_CRet
	{
		TCValueVisitor<t_CVisitor, tf_CType> Visitor(m_Visitor, _Value);

		return fg_VisitRet<t_CRet>(Visitor, fg_Forward<t_CToVisit>(m_ToVisit));
	}

	template <typename t_CVisitor, typename t_CToVisit>
	TCInnerVisitor<void, t_CVisitor, t_CToVisit>::TCInnerVisitor(t_CVisitor _Visitor, t_CToVisit _ToVisit)
		: m_Visitor(_Visitor)
		, m_ToVisit(_ToVisit)
	{
	}

	template <typename t_CVisitor, typename t_CToVisit>
	template <typename t_CInnerVisitor, typename t_CValue>
	TCInnerVisitor<void, t_CVisitor, t_CToVisit>::TCValueVisitor<t_CInnerVisitor, t_CValue>::TCValueVisitor(t_CInnerVisitor _Visitor, t_CValue _Value)
		: m_Visitor(_Visitor)
		, m_Value(_Value)
	{
	}

	template <typename t_CVisitor, typename t_CToVisit>
	template <typename t_CInnerVisitor, typename t_CValue>
	template <typename tf_CType>
	void TCInnerVisitor<void, t_CVisitor, t_CToVisit>
		::TCValueVisitor<t_CInnerVisitor, t_CValue>::operator () (tf_CType &&_Type) noexcept(noexcept(m_Visitor(fg_Forward<t_CValue>(m_Value), fg_Forward<tf_CType>(_Type))))
	{
		m_Visitor(fg_Forward<t_CValue>(m_Value), fg_Forward<tf_CType>(_Type));
	}

	template <typename t_CVisitor, typename t_CToVisit>
	template <typename tf_CType>
	void TCInnerVisitor<void, t_CVisitor, t_CToVisit>::operator () (tf_CType &&_Value)
		noexcept(noexcept(fg_Visit(TCValueVisitor<t_CVisitor, tf_CType>(m_Visitor, _Value), fg_Forward<t_CToVisit>(m_ToVisit))))
	{
		TCValueVisitor<t_CVisitor, tf_CType> Visitor(m_Visitor, _Value);

		fg_Visit(Visitor, fg_Forward<t_CToVisit>(m_ToVisit));
	}

	template <typename tf_CVisitor, typename tf_CToVisit0, typename tf_CToVisit1>
	void fg_Visit(tf_CVisitor &&_Visitor, tf_CToVisit0 &&_ToVisit0, tf_CToVisit1 &&_ToVisit1)
		noexcept(noexcept(fg_Visit(TCInnerVisitor<void, tf_CVisitor, tf_CToVisit1>(_Visitor, _ToVisit1), _ToVisit0)))
	{
		TCInnerVisitor<void, tf_CVisitor, tf_CToVisit1> Visitor(_Visitor, _ToVisit1);
		fg_Visit(Visitor, _ToVisit0);
	}

	template <typename tf_CRet, typename tf_CVisitor, typename tf_CToVisit0, typename tf_CToVisit1>
	auto fg_VisitRet(tf_CVisitor &&_Visitor, tf_CToVisit0 &&_ToVisit0, tf_CToVisit1 &&_ToVisit1)
		noexcept(noexcept(fg_VisitRet<tf_CRet>(TCInnerVisitor<tf_CRet, tf_CVisitor, tf_CToVisit1>(_Visitor, _ToVisit1), _ToVisit0)))
		-> tf_CRet
	{
		TCInnerVisitor<tf_CRet, tf_CVisitor, tf_CToVisit1> Visitor(_Visitor, _ToVisit1);
		return fg_VisitRet<tf_CRet>(Visitor, _ToVisit0);
	}
}

namespace NMib::NStorage::NPrivate
{
	template <typename tf_CLeft, typename tf_CRight>
	inline COrdering_Strong CCompareVariant_Spaceship::operator () (tf_CLeft const &_Left, tf_CRight const &_Right) const noexcept
	{
		return COrdering_Strong::equivalent;
	}

	template <typename tf_CSame>
	inline auto CCompareVariant_Spaceship::operator () (tf_CSame const &_Left, tf_CSame const &_Right) const noexcept(noexcept(_Left <=> _Right))
	{
		return _Left <=> _Right;
	}

	template <typename tf_CLeft, typename tf_CRight>
	inline bool CCompareVariant_Equal::operator () (tf_CLeft const &_Left, tf_CRight const &_Right) const noexcept
	{
		return false;
	}

	template <typename tf_CSame>
	inline bool CCompareVariant_Equal::operator () (tf_CSame const &_Left, tf_CSame const &_Right) const noexcept(noexcept(_Left <=> _Right))
	{
		return _Left == _Right;
	}

	template <typename tf_CType>
	inline void CVariantVisitor_Destruct::operator () (tf_CType &_Type)
	{
		fg_CallDestructor(_Type);
	}

	template <typename tf_CReturn>
	function_does_not_return inline_never TCEnableIf<!NTraits::cIsVoid<tf_CReturn>, tf_CReturn &> fg_InvalidVariant()
	{
		DMibError("Corrupt variant");
	}

	template <typename tf_CReturn>
	function_does_not_return inline_never TCEnableIf<NTraits::cIsVoid<tf_CReturn>, void> fg_InvalidVariant()
	{
		DMibError("Corrupt variant");
	}
}

namespace NMib::NStorage
{
	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	inline_small void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_SetTypeID(CIndexInteger const &_TypeID)
	{
		mp_Storage.m_CurrentType = _TypeID;
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember, typename t_CReturnType>
	template <typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitor<t_iMember, t_CReturnType>::fs_Call
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAs<t_iMember>())))
	{
		(fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAs<t_iMember>());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember, typename t_CReturnType>
	template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitor<t_iMember, t_CReturnType>::fs_CallRet
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAs<t_iMember>())))
		-> tf_CRet
	{
		return (fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAs<t_iMember>());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember, typename t_CReturnType>
	template <typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitor<t_iMember, t_CReturnType>::fs_CallFirst
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAs<t_iMember>())))
	{
		(fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAs<t_iMember>());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember, typename t_CReturnType>
	template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitor<t_iMember, t_CReturnType>::fs_CallFirstRet
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAs<t_iMember>())))
		-> tf_CRet
	{
		return (fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAs<t_iMember>());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember>
	template <typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitor<t_iMember, void>::fs_Call
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept
	{
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember>
	template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitor<t_iMember, void>::fs_CallRet
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		-> tf_CRet
	{
		return NPrivate::fg_InvalidVariant<tf_CRet>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember>
	template <typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitor<t_iMember, void>::fs_CallFirst
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag())))
	{
		(fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember>
	template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitor<t_iMember, void>::fs_CallFirstRet
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag())))
		-> tf_CRet
	{
		return (fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember, typename t_CReturnType>
	template <typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorStorage<t_iMember, t_CReturnType>::fs_Call
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>())))
	{
		(fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember, typename t_CReturnType>
	template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorStorage<t_iMember, t_CReturnType>::fs_CallRet
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>())))
		-> tf_CRet
	{
		return (fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember, typename t_CReturnType>
	template <typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorStorage<t_iMember, t_CReturnType>::fs_CallFirst
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>())))
	{
		(fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember, typename t_CReturnType>
	template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorStorage<t_iMember, t_CReturnType>::fs_CallFirstRet
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>())))
		-> tf_CRet
	{
		return (fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember>
	template <typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorStorage<t_iMember, void>::fs_Call
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept
	{
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember>
	template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorStorage<t_iMember, void>::fs_CallRet
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		-> tf_CRet
	{
		return NPrivate::fg_InvalidVariant<tf_CRet>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember>
	template <typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorStorage<t_iMember, void>::fs_CallFirst
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag())))
	{
		(fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember>
	template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorStorage<t_iMember, void>::fs_CallFirstRet
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag())))
		-> tf_CRet
	{
		return (fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember, typename t_CReturnType>
	template <typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorSet<t_iMember, t_CReturnType>::fs_Call
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>())))
	{
		(fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember, typename t_CReturnType>
	template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorSet<t_iMember, t_CReturnType>::fs_CallRet
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>())))
		-> tf_CRet
	{
		return (fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember, typename t_CReturnType>
	template <typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorSet<t_iMember, t_CReturnType>::fs_CallFirst
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>())))
	{
		(fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember, typename t_CReturnType>
	template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorSet<t_iMember, t_CReturnType>::fs_CallFirstRet
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>())))
		-> tf_CRet
	{
		return (fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember>
	template <typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorSet<t_iMember, void>::fs_Call
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept(fg_Forward<tf_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>()))
	{
		fg_Forward<tf_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember>
	template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorSet<t_iMember, void>::fs_CallRet
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		-> tf_CRet
	{
		fg_Forward<tf_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>();
		return NPrivate::fg_InvalidVariant<tf_CRet>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember>
	template <typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorSet<t_iMember, void>::fs_CallFirst
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept(fg_Forward<tf_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>()) && noexcept((fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag())))
	{
		fg_Forward<tf_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>();
		(fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> t_iMember>
	template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
	mark_artificial inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCCallVisitorSet<t_iMember, void>::fs_CallFirstRet
		(
			tf_CThis &&_pThis
			, tf_CVisitor &&_Visitor
		)
		noexcept(noexcept(fg_Forward<tf_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>()) && noexcept((fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag())))
		-> tf_CRet
	{
		fg_Forward<tf_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>();
		return (fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag());
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename t_CType, bool t_bIsReference, bool t_bIsArray>
	template <typename tf_CType0, typename tf_CType1>
	mark_nodebug inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCEvalReturn<t_CType, t_bIsReference, t_bIsArray>::fs_Value
		(
			tf_CType1 &&_pToRet
		)
		-> decltype(*_pToRet)
	{
		return *_pToRet;
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename t_CType>
	template <typename tf_CType0, typename tf_CType1>
	mark_nodebug inline_small t_CType &TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCEvalReturn<t_CType, false, true>::fs_Value(tf_CType1 &&_pToRet)
	{
		return (t_CType &)*_pToRet;
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename t_CType>
	template <typename tf_CType0, typename tf_CType1>
	mark_nodebug inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCEvalReturn<t_CType, true, false>::fs_Value(tf_CType1 &&_pToRet)
		-> TCEnableIf<NTraits::cIsLValueReference<tf_CType0>, tf_CType0>
	{
		return *(*_pToRet);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename t_CType>
	template <typename tf_CType0, typename tf_CType1>
	mark_nodebug inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCEvalReturn<t_CType, true, false>::fs_Value(tf_CType1 &&_pToRet)
		-> TCEnableIf<!NTraits::cIsLValueReference<tf_CType0>, tf_CType0>
	{
		return NMib::fg_Move(*(*_pToRet));
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> tf_iMember>
	mark_nodebug inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_GetAs()
		-> TCEnableIf<!NTraits::cIsVoid<typename TCEvalReturnType<tf_iMember>::CType>, typename TCEvalReturnType<tf_iMember>::CType>
	{
		using CType = TCTypeFromMemberInt<tf_iMember>; // NOLINT(malterlib-type-naming): the type of a member, which can be an enum
		using CConstructType = typename TCEvalConstructType<tf_iMember>::CType; // NOLINT(malterlib-type-naming): the type of a member, which can be an enum
		CConstructType *pRet = (CConstructType *)mp_Storage.m_Storage;
		using CReturnType = typename TCEvalReturnType<tf_iMember>::CType;
		return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> tf_iMember>
	mark_nodebug inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_GetAs() const
		-> TCEnableIf<NTraits::cIsVoid<typename TCEvalReturnType<tf_iMember>::CType>, typename TCEvalReturnType<tf_iMember>::CType>
	{
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> tf_iMember>
	mark_nodebug inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_GetAs() const
		-> TCEnableIf<!NTraits::cIsVoid<typename TCEvalReturnTypeConst<tf_iMember>::CType>, typename TCEvalReturnTypeConst<tf_iMember>::CType>
	{
		using CType = TCTypeFromMemberInt<tf_iMember>; // NOLINT(malterlib-type-naming): the type of a member, which can be an enum
		using CConstructType = typename TCEvalConstructType<tf_iMember>::CType; // NOLINT(malterlib-type-naming): the type of a member, which can be an enum

		CConstructType const *pRet = (CConstructType const *)mp_Storage.m_Storage;

		using CReturnType = typename TCEvalReturnTypeConst<tf_iMember>::CType;
		return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> tf_iMember>
	mark_nodebug inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_GetAsStorage()
		-> TCEnableIf<!NTraits::cIsVoid<typename TCEvalReturnType<tf_iMember>::CType>, NTraits::TCAddLValueReference<typename TCEvalConstructType<tf_iMember>::CType>>
	{
		using CConstructType = typename TCEvalConstructType<tf_iMember>::CType; // NOLINT(malterlib-type-naming): the type of a member, which can be an enum

		CConstructType *pRet = (CConstructType *)mp_Storage.m_Storage;
		return *pRet;
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> tf_iMember>
	mark_nodebug inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_GetAsStorage() const
		-> TCEnableIf<NTraits::cIsVoid<typename TCEvalReturnType<tf_iMember>::CType>, typename TCEvalReturnType<tf_iMember>::CType>
	{
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> tf_iMember>
	mark_nodebug inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_GetAsStorage() const
		-> TCEnableIf
		<
			!NTraits::cIsVoid<typename TCEvalReturnTypeConst<tf_iMember>::CType>
			, NTraits::TCAddLValueReference<NTraits::TCAddConst<typename TCEvalConstructType<tf_iMember>::CType>>
		>
	{
		using CConstructType = typename TCEvalConstructType<tf_iMember>::CType;

		CConstructType const *pRet = (CConstructType const *)mp_Storage.m_Storage;
		return *pRet;
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CVisitor>
	inline_always void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_VisitStorage(tf_CVisitor &&_Visitor)
		noexcept
		(
			noexcept(TCCallVisitorStorage<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor)))
			&& (true && ... && noexcept(TCCallVisitorStorage<CIndexInteger(tp_Member)>::fs_Call(this, fg_Forward<tf_CVisitor>(_Visitor))))
		)
	{
		auto TypeID = f_GetTypeID();

		if (TypeID == mcp_Member0Typed)
		{
			TCCallVisitorStorage<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor));
			return;
		}

#if defined DMibContractConfigure_CheckEnabled
		bool bFound =
#endif
			(
				...
				||
				[&]() inline_always_lambda
				{
					if constexpr (tp_Member == mcp_Member0Typed)
						return false;
					else
					{
						if (tp_Member == TypeID)
						{
							TCCallVisitorStorage<CIndexInteger(tp_Member)>::fs_Call(this, fg_Forward<tf_CVisitor>(_Visitor));
							return true;
						}
						return false;
					}
				}()
			)
		;

		DMibFastCheck(bFound);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CVisitor>
	inline_always void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_Visit(tf_CVisitor &&_Visitor)
		noexcept
		(
			noexcept(TCCallVisitor<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor)))
			&& (true && ... && noexcept(TCCallVisitor<CIndexInteger(tp_Member)>::fs_Call(this, fg_Forward<tf_CVisitor>(_Visitor))))
		)
	{
		auto TypeID = f_GetTypeID();

		if (TypeID == mcp_Member0Typed)
		{
			TCCallVisitor<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor));
			return;
		}

#if defined DMibContractConfigure_CheckEnabled
		bool bFound =
#endif
			(
				...
				||
				[&]() inline_always_lambda
				{
					if constexpr (tp_Member == mcp_Member0Typed)
						return false;
					else
					{
						if (tp_Member == TypeID)
						{
							TCCallVisitor<CIndexInteger(tp_Member)>::fs_Call(this, fg_Forward<tf_CVisitor>(_Visitor));
							return true;
						}
						return false;
					}
				}()
			)
		;

		DMibFastCheck(bFound);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CVisitor>
	inline_always void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_Visit(tf_CVisitor &&_Visitor) const
		noexcept
		(
			noexcept(TCCallVisitor<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor)))
			&& (true && ... && noexcept(TCCallVisitor<CIndexInteger(tp_Member)>::fs_Call(this, fg_Forward<tf_CVisitor>(_Visitor))))
		)
	{
		auto TypeID = f_GetTypeID();

		if (TypeID == mcp_Member0Typed)
		{
			TCCallVisitor<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor));
			return;
		}

#if defined DMibContractConfigure_CheckEnabled
		bool bFound =
#endif
			(
				...
				||
				[&]() inline_always_lambda
				{
					if constexpr (tp_Member == mcp_Member0Typed)
						return false;
					else
					{
						if (tp_Member == TypeID)
						{
							TCCallVisitor<CIndexInteger(tp_Member)>::fs_Call(this, fg_Forward<tf_CVisitor>(_Visitor));
							return true;
						}
						return false;
					}
				}()
			)
		;

		DMibFastCheck(bFound);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CReturn, typename tf_CVisitor>
	inline_always auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_VisitRet(tf_CVisitor &&_Visitor)
		noexcept
		(
			noexcept(TCCallVisitor<mcp_Member0>::template fs_CallFirstRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor)))
			&& (true && ... && noexcept(TCCallVisitor<CIndexInteger(tp_Member)>::template fs_CallRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor))))
		)
		-> tf_CReturn
	{
		auto TypeID = f_GetTypeID();

		if (TypeID == mcp_Member0Typed)
			return TCCallVisitor<mcp_Member0>::template fs_CallFirstRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor));

		TCAggregateSimple<tf_CReturn> Ret;

#if defined DMibContractConfigure_CheckEnabled
		bool bFound = false;
#endif
		auto Cleanup = g_OnScopeExit / [&]() inline_always_lambda
			{
#if defined DMibContractConfigure_CheckEnabled
				if (!bFound)
					return;
#endif
				Ret.f_Destruct();
			}
		;
#if defined DMibContractConfigure_CheckEnabled
		bFound =
#endif
			(
				...
				||
				[&]() inline_always_lambda
				{
					if constexpr (tp_Member == mcp_Member0Typed)
						return false;
					else
					{
						if (tp_Member == TypeID)
						{
							Ret.f_Construct(TCCallVisitor<CIndexInteger(tp_Member)>::template fs_CallRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor)));
							return true;
						}
						return false;
					}
				}()
			)
		;

		DMibFastCheck(bFound);

		return fg_Move(*Ret);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CReturn, typename tf_CVisitor>
	inline_always auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_VisitRet(tf_CVisitor &&_Visitor) const
		noexcept
		(
			noexcept(TCCallVisitor<mcp_Member0>::template fs_CallFirstRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor)))
			&& (true && ... && noexcept(TCCallVisitor<CIndexInteger(tp_Member)>::template fs_CallRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor))))
		)
		-> tf_CReturn
	{
		auto TypeID = f_GetTypeID();

		if (TypeID == mcp_Member0Typed)
			return TCCallVisitor<mcp_Member0>::template fs_CallFirstRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor));

		TCAggregateSimple<tf_CReturn> Ret;

#if defined DMibContractConfigure_CheckEnabled
		bool bFound = false;
#endif
		auto Cleanup = g_OnScopeExit / [&]() inline_always_lambda
			{
#if defined DMibContractConfigure_CheckEnabled
				if (!bFound)
					return;
#endif
				Ret.f_Destruct();
			}
		;
#if defined DMibContractConfigure_CheckEnabled
		bFound =
#endif
			(
				...
				||
				[&]() inline_always_lambda
				{
					if constexpr (tp_Member == mcp_Member0Typed)
						return false;
					else
					{
						if (tp_Member == TypeID)
						{
							Ret.f_Construct(TCCallVisitor<CIndexInteger(tp_Member)>::template fs_CallRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor)));
							return true;
						}
						return false;
					}
				}()
			)
		;

		DMibFastCheck(bFound);

		return fg_Move(*Ret);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CVisitor>
	inline_always void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_VisitCreate(t_CIndex const &_Index, tf_CVisitor &&_Visitor)
		noexcept
		(
			noexcept(TCCallVisitorSet<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor)))
			&& (true && ... && noexcept(TCCallVisitorSet<CIndexInteger(tp_Member)>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor))))
		)
	{
		if (_Index == mcp_Member0Typed)
			return TCCallVisitorSet<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor));

		auto TypeID = _Index;

#if defined DMibContractConfigure_CheckEnabled
		bool bFound =
#endif
			(
				...
				||
				[&]() inline_always_lambda
				{
					if constexpr (tp_Member == mcp_Member0Typed)
						return false;
					else
					{
						if (tp_Member == TypeID)
						{
							TCCallVisitorSet<CIndexInteger(tp_Member)>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor));
							return true;
						}
						return false;
					}
				}()
			)
		;

		DMibFastCheck(bFound);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CVisitor>
	inline_always auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_TryVisitCreate(t_CIndex const &_Index, tf_CVisitor &&_Visitor)
		noexcept
		(
			noexcept(TCCallVisitorSet<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor)))
			&& (true && ... && noexcept(TCCallVisitorSet<CIndexInteger(tp_Member)>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor))))
		)
		-> bool
	{
		if (_Index == mcp_Member0Typed)
		{
			TCCallVisitorSet<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor));
			return true;
		}

		auto TypeID = _Index;

		bool bFound =
			(
				... || [&]() inline_always_lambda
				{
					if constexpr (tp_Member == mcp_Member0Typed)
						return false;
					else
					{
						if (tp_Member == TypeID)
						{
							TCCallVisitorSet<CIndexInteger(tp_Member)>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor));
							return true;
						}
						return false;
					}
				}()
			)
		;

		return bFound;
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CReturn, typename tf_CVisitor>
	inline_always auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_VisitCreateReturn(t_CIndex const &_Index, tf_CVisitor &&_Visitor)
		noexcept
		(
			noexcept(TCCallVisitorSet<mcp_Member0>::template fs_CallFirstRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor)))
			&& (true && ... && noexcept(TCCallVisitorSet<CIndexInteger(tp_Member)>::template fs_CallRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor))))
		)
		-> tf_CReturn
	{
		if (_Index == mcp_Member0Typed)
			return TCCallVisitorSet<mcp_Member0>::template fs_CallFirstRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor));

		auto TypeID = _Index;
		TCAggregateSimple<tf_CReturn> Ret;

#if defined DMibContractConfigure_CheckEnabled
		bool bFound = false;
#endif
		auto Cleanup = g_OnScopeExit / [&]() inline_always_lambda
			{
#if defined DMibContractConfigure_CheckEnabled
				if (!bFound)
					return;
#endif
				Ret.f_Destruct();
			}
		;
#if defined DMibContractConfigure_CheckEnabled
		bFound =
#endif
			(
				...
				||
				[&]() inline_always_lambda
				{
					if constexpr (tp_Member == mcp_Member0Typed)
						return false;
					else
					{
						if (tp_Member == TypeID)
						{
							Ret.f_Construct(TCCallVisitorSet<CIndexInteger(tp_Member)>::template fs_CallRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor)));
							return true;
						}
						return false;
					}
				}()
			)
		;

		DMibFastCheck(bFound);

		return fg_Move(*Ret);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::operator == (TCVariantCommon const &_Right) const
		noexcept(noexcept(fg_VisitRet<bool>(NPrivate::CCompareVariant_Equal(), *this, _Right)))
		-> bool
	{
		if (f_GetTypeID() != _Right.f_GetTypeID())
			return false;

		return fg_VisitRet<bool>(NPrivate::CCompareVariant_Equal(), *this, _Right);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::operator <=> (TCVariantCommon const &_Right) const noexcept
		(
			noexcept
			(
				fg_VisitRet
				<
					TCCommonOrderingType
					<
						decltype
						(
							NPrivate::fg_GetTypeRefOrVoidTag<tp_CTypes>() <=> NPrivate::fg_GetTypeRefOrVoidTag<tp_CTypes>()
						)...
					>
				>
				(NPrivate::CCompareVariant_Spaceship(), *this, _Right)
			)
		)
	{
		using COrdering = TCCommonOrderingType
			<
				decltype
				(
					NPrivate::fg_GetTypeRefOrVoidTag<tp_CTypes>() <=> NPrivate::fg_GetTypeRefOrVoidTag<tp_CTypes>()
				)...
			>
		;

		if (auto Result = f_GetTypeID() <=> _Right.f_GetTypeID(); Result != 0)
			return COrdering(Result);

		return fg_VisitRet<COrdering>(NPrivate::CCompareVariant_Spaceship(), *this, _Right);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_DestroyCurrent()
	{
		fp_VisitStorage(NPrivate::CVariantVisitor_Destruct());
	}

#ifdef DDebugger_VisualStudio
	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_ReferenceDebugInfo()
	{
		(
			[&]
			{
				[[maybe_unused]] TCVariantMember<t_CIndex, tp_CTypes, tp_Member> Member;
			}
			()
			, ...
		);
	}
#endif

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> tf_iMember>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_Set() -> typename TCEvalReturnType<tf_iMember>::CType
	{
		if constexpr (NTraits::cIsVoid<typename TCEvalReturnType<tf_iMember>::CType>)
			fp_SetTypeID(tf_iMember);
		else
		{
			using CConstructType = typename TCEvalConstructType<tf_iMember>::CType;

			auto pRet = new(mp_Storage.m_Storage) CConstructType();

			fp_SetTypeID(tf_iMember);
			using CReturnType = typename TCEvalReturnType<tf_iMember>::CType;
			return TCEvalReturn<TCTypeFromMemberInt<tf_iMember>>::template fs_Value<CReturnType>(pRet);
		}
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> tf_iMember, typename tf_CParam0>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_Set(tf_CParam0 &&_Param0) -> typename TCEvalReturnType<tf_iMember>::CType
		requires (NTraits::cIsConstructibleWith<TCTypeFromMemberInt<tf_iMember>, tf_CParam0 &&>)
	{
		using CType = TCTypeFromMemberInt<tf_iMember>;
		using CConstructType = typename TCEvalConstructType<tf_iMember>::CType;

		CConstructType *pRet;
		if constexpr (NTraits::cIsReference<TCTypeFromMemberInt<tf_iMember>>)
			pRet = new(mp_Storage.m_Storage) CConstructType(&_Param0);
		else
			pRet = new(mp_Storage.m_Storage) CConstructType(fg_Forward<tf_CParam0>(_Param0));

		fp_SetTypeID(tf_iMember);
		using CReturnType = typename TCEvalReturnType<tf_iMember>::CType;
		return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> tf_iMember, typename tf_CParam0, typename ...tfp_CParams>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_Set(tf_CParam0 &&_Param0, tfp_CParams && ...p_Params)
		-> typename TCEvalReturnType<tf_iMember>::CType
		requires (NTraits::cIsConstructibleWith<TCTypeFromMemberInt<tf_iMember>, tf_CParam0 &&, tfp_CParams && ...>)
	{
		using CType = TCTypeFromMemberInt<tf_iMember>;
		using CConstructType = typename TCEvalConstructType<tf_iMember>::CType;

		auto pRet = new(mp_Storage.m_Storage) CConstructType(fg_Forward<tf_CParam0>(_Param0), fg_Forward<tfp_CParams>(p_Params)...);
		fp_SetTypeID(tf_iMember);
		using CReturnType = typename TCEvalReturnType<tf_iMember>::CType;
		return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> tf_iMember>
	void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_SetNoRet()
	{
		if constexpr (NTraits::cIsVoid<typename TCEvalReturnType<tf_iMember>::CType>)
			fp_SetTypeID(tf_iMember);
		else
		{
			using CConstructType = typename TCEvalConstructType<tf_iMember>::CType;
			new((void *)mp_Storage.m_Storage) CConstructType();
			fp_SetTypeID(tf_iMember);
		}
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> tf_iMember, typename tf_CParam0>
	void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_SetNoRet(tf_CParam0 &&_Param0)
		requires (NTraits::cIsConstructibleWith<TCTypeFromMemberInt<tf_iMember>, tf_CParam0 &&>)
	{
		using CConstructType = typename TCEvalConstructType<tf_iMember>::CType; // NOLINT(malterlib-type-naming): the type of a member, which can be an enum

		if constexpr (NTraits::cIsReference<TCTypeFromMemberInt<tf_iMember>>)
			new(mp_Storage.m_Storage) CConstructType(&_Param0);
		else
			new(mp_Storage.m_Storage) CConstructType(fg_Forward<tf_CParam0>(_Param0));

		fp_SetTypeID(tf_iMember);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)> tf_iMember, typename tf_CParam0, typename ...tfp_CParams>
	void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_SetNoRet(tf_CParam0 &&_Param0, tfp_CParams && ...p_Params)
		requires (NTraits::cIsConstructibleWith<TCTypeFromMemberInt<tf_iMember>, tf_CParam0 &&, tfp_CParams && ...>)
	{
		using CConstructType = typename TCEvalConstructType<tf_iMember>::CType;

		new(mp_Storage.m_Storage) CConstructType(fg_Forward<tf_CParam0>(_Param0), fg_Forward<tfp_CParams>(p_Params)...);
		fp_SetTypeID(tf_iMember);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CType, typename ...tfp_CParams, umint ...tfp_Indidies>
	void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_AssignConstruct
		(
			TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams
			, NMeta::TCIndices<tfp_Indidies...> const &_Indices
		)
		requires
		(
			TCEvalManyParamConstruction<void (tfp_CParams ...p_Params)>::mc_Value >= 0
			&& mcp_FirstNothrowDefaultConstructible != -1
			&& requires ()
			{
				this->fp_SetNoRet<TCEvalManyParamConstruction<void (tfp_CParams ...p_Params)>::mc_Value>(fg_Forward<tfp_CParams>(fg_Get<tfp_Indidies>(_CreateParams.m_Params))...);
			}
		)
	{
		fp_DestroyCurrent(); // Cannot throw

		try
		{
			fp_SetNoRet<TCEvalManyParamConstruction<void (tfp_CParams ...p_Params)>::mc_Value>(fg_Forward<tfp_CParams>(fg_Get<tfp_Indidies>(_CreateParams.m_Params))...);
		}
		catch (...)
		{
			fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
			throw;
		}
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	inline_small auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_GetTypeID() const -> CIndexInteger
	{
		return CIndexInteger(mp_Storage.m_CurrentType);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_GetStreamable() -> TCVariantCommon &
	{
		return *this;
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::fp_GetStreamable() const -> TCVariantCommon const &
	{
		return *this;
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::CVariantVisitor_Move::CVariantVisitor_Move(TCVariantCommon &_This)
		: m_This(_This)
	{
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::CVariantVisitor_Move::operator () (CVoidTag _Tag)
	{
		static constexpr CIndexInteger c_ToConstruct = TCMemberFromTypeInt<void>::mc_Value;

		static_assert(c_ToConstruct >= 0, "No type in the variant can be constructed with void argument type");
		m_This.fp_SetNoRet<c_ToConstruct>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CParam0>
	void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::CVariantVisitor_Move::operator () (tf_CParam0 &&_Param0)
	{
		static constexpr CIndexInteger c_ToConstruct = TCEvalOneParamConstruction<NTraits::TCAddRValueReference<tf_CParam0>>::mc_Value;

		static_assert(c_ToConstruct >= 0, "No type in the variant can be constructed with this argument type (move constructor)");
		m_This.fp_SetNoRet<c_ToConstruct>(fg_Move(_Param0));
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::CVariantVisitor_Copy::CVariantVisitor_Copy(TCVariantCommon &_This)
		: m_This(_This)
	{
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::CVariantVisitor_Copy::operator () (CVoidTag _Tag)
	{
		static constexpr CIndexInteger c_ToConstruct = TCMemberFromTypeInt<void>::mc_Value;

		static_assert(c_ToConstruct >= 0, "No type in the variant can be constructed with void argument type");
		m_This.fp_SetNoRet<c_ToConstruct>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CParam0>
	void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::CVariantVisitor_Copy::operator () (tf_CParam0 &&_Param0)
	{
		static constexpr CIndexInteger c_ToConstruct = TCEvalOneParamConstruction<tf_CParam0>::mc_Value;

		static_assert(c_ToConstruct >= 0, "No type in the variant can be constructed with this argument type (copy constructor)");

		m_This.fp_SetNoRet<c_ToConstruct>(fg_Forward<tf_CParam0>(_Param0));
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCVariantCommon() noexcept
		requires
		(
			mcp_FirstNothrowDefaultConstructible != -1 && requires ()
			{
				this->fp_SetNoRet<mcp_FirstDefaultConstructible>();
			}
		)
	{
		fp_SetNoRet<mcp_FirstDefaultConstructible>();
#ifdef DDebugger_VisualStudio
		TCVariantCommon::fp_ReferenceDebugInfo();
#endif
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::~TCVariantCommon()
	{
		fp_DestroyCurrent();
#ifdef DDebugger_VisualStudio
		TCVariantCommon::fp_ReferenceDebugInfo();
#endif
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CIndex, typename ...tfp_CMembers>
	TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCVariantCommon(TCVariantCommon<tf_CIndex, tfp_CMembers...> &&_Other)
	{
		_Other.f_Visit(CVariantVisitor_Move(*this));
#ifdef DDebugger_VisualStudio
		TCVariantCommon::fp_ReferenceDebugInfo();
#endif
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCVariantCommon(TCVariantCommon &&_Other)
	{
		_Other.f_Visit(CVariantVisitor_Move(*this));
#ifdef DDebugger_VisualStudio
		TCVariantCommon::fp_ReferenceDebugInfo();
#endif
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CIndex, typename ...tfp_CMembers>
	TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCVariantCommon(TCVariantCommon<tf_CIndex, tfp_CMembers...> const &_Other)
	{
		_Other.f_Visit(CVariantVisitor_Copy(*this));
#ifdef DDebugger_VisualStudio
		TCVariantCommon::fp_ReferenceDebugInfo();
#endif
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCVariantCommon(TCVariantCommon const &_Other)
	{
		_Other.f_Visit(CVariantVisitor_Copy(*this));
#ifdef DDebugger_VisualStudio
		TCVariantCommon::fp_ReferenceDebugInfo();
#endif
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCVariantCommon(TCVariantCommon &_Other)
	{
		_Other.f_Visit(CVariantVisitor_Copy(*this));
#ifdef DDebugger_VisualStudio
		TCVariantCommon::fp_ReferenceDebugInfo();
#endif
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CIndex, typename ...tfp_CMembers>
	TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCVariantCommon(TCVariantCommon<tf_CIndex, tfp_CMembers...> &_Other)
	{
		_Other.f_Visit(CVariantVisitor_Copy(*this));
#ifdef DDebugger_VisualStudio
		TCVariantCommon::fp_ReferenceDebugInfo();
#endif
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template
	<
		typename tf_CParam0
		, TCEnableIf<TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::template TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value >= 0> *
	>
	TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCVariantCommon(tf_CParam0 &&_Param0)
		requires requires ()
		{
			this->fp_SetNoRet<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value>(fg_Forward<tf_CParam0>(_Param0));
		}
	{
		this->fp_SetNoRet<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value>(fg_Forward<tf_CParam0>(_Param0));
#ifdef DDebugger_VisualStudio
		TCVariantCommon::fp_ReferenceDebugInfo();
#endif
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template
	<
		typename tf_CParam0
		, typename ...tfp_CParams
		, TCEnableIf
		<
			TCVariantCommon
			<
				t_CIndex
				, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...
			>
			::template TCEvalManyParamConstruction<void (tf_CParam0 &&_Param0, tfp_CParams ...p_RestOfParams)>::mc_Value
			>= 0
		>
		*
	>
	TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::TCVariantCommon(tf_CParam0 &&_Param0, tfp_CParams && ...p_RestOfParams)
		requires requires ()
		{
			this->fp_SetNoRet<TCEvalManyParamConstruction<void (tf_CParam0 &&_Param0, tfp_CParams ...p_RestOfParams)>::mc_Value>
				(
					fg_Forward<tf_CParam0>(_Param0)
					, fg_Forward<tfp_CParams>(p_RestOfParams)...
				)
			;
		}
	{
		this->fp_SetNoRet<TCEvalManyParamConstruction<void (tf_CParam0 &&_Param0, tfp_CParams ...p_RestOfParams)>::mc_Value>
			(
				fg_Forward<tf_CParam0>(_Param0)
				, fg_Forward<tfp_CParams>(p_RestOfParams)...
			)
		;
#ifdef DDebugger_VisualStudio
		TCVariantCommon::fp_ReferenceDebugInfo();
#endif
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CIndex, typename ...tfp_CMembers>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::operator = (TCVariantCommon<tf_CIndex, tfp_CMembers...> &&_Other) -> TCVariantCommon &
		requires (mcp_FirstNothrowDefaultConstructible != -1)
	{
		fp_DestroyCurrent(); // Cannot throw

		try
		{
			_Other.f_Visit(CVariantVisitor_Move(*this));
			return *this;
		}
		catch (...)
		{
			fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
			throw;
		}
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::operator = (TCVariantCommon &&_Other) -> TCVariantCommon &
		requires (mcp_FirstNothrowDefaultConstructible != -1 || mcp_bAllHasNothrowMoveConstructor)
	{
		fp_DestroyCurrent(); // Cannot throw

		if constexpr (mcp_bAllHasNothrowMoveConstructor)
		{
			_Other.f_Visit(CVariantVisitor_Move(*this));
			return *this;
		}
		else
		{
			try
			{
				_Other.f_Visit(CVariantVisitor_Move(*this));
				return *this;
			}
			catch (...)
			{
				fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
				throw;
			}
		}
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CIndex, typename ...tfp_CMembers>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::operator = (TCVariantCommon<tf_CIndex, tfp_CMembers...> const &_Other) -> TCVariantCommon &
		requires (mcp_FirstNothrowDefaultConstructible != -1)
	{
		fp_DestroyCurrent(); // Cannot throw
		try
		{
			_Other.f_Visit(CVariantVisitor_Copy(*this));
			return *this;
		}
		catch (...)
		{
			fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
			throw;
		}
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::operator = (TCVariantCommon const &_Other) -> TCVariantCommon &
		requires (mcp_FirstNothrowDefaultConstructible != -1 || mcp_bAllHasNothrowCopyConstructor)
	{
		fp_DestroyCurrent(); // Cannot throw

		if constexpr (mcp_bAllHasNothrowCopyConstructor)
		{
			_Other.f_Visit(CVariantVisitor_Copy(*this));
			return *this;
		}
		else
		{
			try
			{
				_Other.f_Visit(CVariantVisitor_Copy(*this));
				return *this;
			}
			catch (...)
			{
				fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
				throw;
			}
		}
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::operator = (TCVariantCommon &_Other) -> TCVariantCommon &
		requires (mcp_FirstNothrowDefaultConstructible != -1 || mcp_bAllHasNothrowCopyConstructor)
	{
		fp_DestroyCurrent(); // Cannot throw

		if constexpr (mcp_bAllHasNothrowCopyConstructor)
		{
			_Other.f_Visit(CVariantVisitor_Copy(*this));
			return *this;
		}
		else
		{
			try
			{
				_Other.f_Visit(CVariantVisitor_Copy(*this));
				return *this;
			}
			catch (...)
			{
				fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
				throw;
			}
		}
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CIndex, typename ...tfp_CMembers>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::operator = (TCVariantCommon<tf_CIndex, tfp_CMembers...> &_Other) -> TCVariantCommon &
		requires (mcp_FirstNothrowDefaultConstructible != -1)
	{
		fp_DestroyCurrent(); // Cannot throw
		try
		{
			_Other.f_Visit(CVariantVisitor_Copy(*this));
			return *this;
		}
		catch (...)
		{
			fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
			throw;
		}
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template
	<
		typename tf_CParam0
		, TCEnableIf<TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::template TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value >= 0> *
	>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::operator = (tf_CParam0 &&_Param) -> TCVariantCommon &
		requires
		(
			(TCIsNothrowConstructibleWith<tf_CParam0 &&>::mc_Value || (mcp_FirstNothrowDefaultConstructible != -1)) && requires ()
			{
				this->fp_SetNoRet<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value>(fg_Forward<tf_CParam0>(_Param)); // Cannot throw
			}
		)
	{
		if constexpr (TCIsNothrowConstructibleWith<tf_CParam0 &&>::mc_Value)
		{
			fp_DestroyCurrent(); // Cannot throw
			fp_SetNoRet<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value>(fg_Forward<tf_CParam0>(_Param)); // Cannot throw
		}
		else
		{
			fp_DestroyCurrent(); // Cannot throw

			try
			{
				fp_SetNoRet<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value>(fg_Forward<tf_CParam0>(_Param));
			}
			catch (...)
			{
				fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
				throw;
			}
		}

		return *this;
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CType, typename ...tfp_CParams>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams) -> TCVariantCommon &
		requires requires ()
		{
			this->fp_AssignConstruct(fg_Move(_CreateParams), NMeta::TCConsecutiveIndices<TCConstruct<tf_CType, tfp_CParams...>::mc_nParams>());
		}
	{
		fp_AssignConstruct(fg_Move(_CreateParams), NMeta::TCConsecutiveIndices<TCConstruct<tf_CType, tfp_CParams...>::mc_nParams>());
		return *this;
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	inline_small t_CIndex TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_GetTypeID() const
	{
		return (t_CIndex)mp_Storage.m_CurrentType;
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CType>
	inline_small bool TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_IsOfType() const
	{
		return fp_GetTypeID() == TCMemberFromTypeInt<tf_CType>::mc_Value;
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <t_CIndex tf_iMember>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_Get() -> typename TCEvalReturnType<CIndexInteger(tf_iMember)>::CType
	{
		DMibFastCheck(f_GetTypeID() == tf_iMember);

		return fp_GetAs<CIndexInteger(tf_iMember)>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <t_CIndex tf_iMember>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_Get() const -> typename TCEvalReturnTypeConst<CIndexInteger(tf_iMember)>::CType
	{
		DMibFastCheck(f_GetTypeID() == tf_iMember);

		return fp_GetAs<CIndexInteger(tf_iMember)>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CType>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_GetAsType() -> typename TCEvalReturnType<TCMemberFromTypeInt<tf_CType>::mc_Value>::CType
		requires (TCMemberFromTypeInt<tf_CType>::mc_Value >= 0)
	{
		static constexpr CIndexInteger c_ToGet = TCMemberFromTypeInt<tf_CType>::mc_Value;

		DMibFastCheck(fp_GetTypeID() == c_ToGet);

		return fp_GetAs<c_ToGet>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CType>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_GetAsType() const -> typename TCEvalReturnTypeConst<TCMemberFromTypeInt<tf_CType>::mc_Value>::CType
		requires (TCMemberFromTypeInt<tf_CType>::mc_Value >= 0)
	{
		static constexpr CIndexInteger c_ToGet = TCMemberFromTypeInt<tf_CType>::mc_Value;

		DMibFastCheck(fp_GetTypeID() == c_ToGet);

		return fp_GetAs<c_ToGet>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <t_CIndex tf_iMember>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_TryGet() -> typename TCEvalTryGetReturnType<CIndexInteger(tf_iMember)>::CType
	{
		if (f_GetTypeID() != tf_iMember)
			return nullptr;

		return &fp_GetAs<CIndexInteger(tf_iMember)>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <t_CIndex tf_iMember>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_TryGet() const -> typename TCEvalTryGetReturnTypeConst<CIndexInteger(tf_iMember)>::CType
	{
		if (f_GetTypeID() != tf_iMember)
			return nullptr;

		return &fp_GetAs<CIndexInteger(tf_iMember)>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CType>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_TryGetAsType() -> typename TCEvalTryGetReturnType<TCMemberFromTypeInt<tf_CType>::mc_Value>::CType
		requires (TCMemberFromTypeInt<tf_CType>::mc_Value >= 0)
	{
		static constexpr CIndexInteger c_ToGet = TCMemberFromTypeInt<tf_CType>::mc_Value;

		if (fp_GetTypeID() != c_ToGet)
			return nullptr;

		return &fp_GetAs<c_ToGet>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CType>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_TryGetAsType() const
		-> typename TCEvalTryGetReturnTypeConst<TCMemberFromTypeInt<tf_CType>::mc_Value>::CType
		requires (TCMemberFromTypeInt<tf_CType>::mc_Value >= 0)
	{
		static constexpr CIndexInteger c_ToGet = TCMemberFromTypeInt<tf_CType>::mc_Value;

		if (fp_GetTypeID() != c_ToGet)
			return nullptr;

		return &fp_GetAs<c_ToGet>();
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <t_CIndex tf_iMember>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_Set() -> typename TCEvalReturnType<CIndexInteger(tf_iMember)>::CType
		requires
		(
			(
				NTraits::cIsVoid<typename TCEvalReturnType<CIndexInteger(tf_iMember)>::CType>
				|| NTraits::cIsNothrowDefaultConstructible<TCTypeFromMemberInt<tf_iMember>>
				|| mcp_FirstNothrowDefaultConstructible != -1
			)
			&& requires ()
			{
				this->fp_Set<CIndexInteger(tf_iMember)>();
			}
		)
	{
		fp_DestroyCurrent();

		if constexpr (NTraits::cIsVoid<typename TCEvalReturnType<CIndexInteger(tf_iMember)>::CType>)
			return fp_Set<CIndexInteger(tf_iMember)>();
		else
		{
			try
			{
				return fp_Set<CIndexInteger(tf_iMember)>();
			}
			catch (...)
			{
				fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
				throw;
			}
		}
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <t_CIndex tf_iMember, typename ...tfp_CParams>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_Set(tfp_CParams && ...p_Params) -> typename TCEvalReturnType<CIndexInteger(tf_iMember)>::CType
		requires
		(
			mcp_FirstNothrowDefaultConstructible != -1 && requires ()
			{
				this->fp_Set<CIndexInteger(tf_iMember)>(fg_Forward<tfp_CParams>(p_Params)...);
			}
		)
	{
		fp_DestroyCurrent();

		try
		{
			return fp_Set<CIndexInteger(tf_iMember)>(fg_Forward<tfp_CParams>(p_Params)...);
		}
		catch (...)
		{
			fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
			throw;
		}
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CType, typename ...tfp_CParams>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_SetAsType(tfp_CParams && ...p_Params)
		-> decltype(f_Set<t_CIndex(TCMemberFromTypeInt<tf_CType>::mc_Value)>(fg_Forward<tfp_CParams>(p_Params)...))
		requires (TCMemberFromTypeInt<tf_CType>::mc_Value >= 0)
	{
		return f_Set<t_CIndex(TCMemberFromTypeInt<tf_CType>::mc_Value)>(fg_Forward<tfp_CParams>(p_Params)...);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	template <typename tf_CStr>
	void TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::f_Format(tf_CStr &o_Str) const
	{
		f_Visit
			(
				[&](auto const &_Value)
				{
					o_Str += typename tf_CStr::CFormat("{}") << _Value;
				}
			)
		;
	}

	template <typename ...tp_CTypes>
	TCVariant<tp_CTypes...>::TCVariant(TCVariant &&_Other)
		: CParent(fg_Move(_Other.fp_GetStreamable()))
	{
	}

	template <typename ...tp_CTypes>
	TCVariant<tp_CTypes...>::TCVariant(TCVariant &_Other)
		: CParent(_Other.fp_GetStreamable())
	{
	}

	template <typename ...tp_CTypes>
	TCVariant<tp_CTypes...>::TCVariant(TCVariant const &_Other)
		: CParent(_Other.fp_GetStreamable())
	{
	}

	template <typename ...tp_CTypes>
	auto TCVariant<tp_CTypes...>::operator = (TCVariant &&_Other) -> TCVariant &
		requires requires ()
		{
			this->fp_GetStreamable() = fg_Move(_Other.fp_GetStreamable());
		}
	{
		this->fp_GetStreamable() = fg_Move(_Other.fp_GetStreamable());
		return *this;
	}

	template <typename ...tp_CTypes>
	auto TCVariant<tp_CTypes...>::operator = (TCVariant const &_Other) -> TCVariant &
		requires requires ()
		{
			this->fp_GetStreamable() = _Other.fp_GetStreamable();
		}
	{
		this->fp_GetStreamable() = _Other.fp_GetStreamable();
		return *this;
	}

	template <typename ...tp_CTypes>
	auto TCVariant<tp_CTypes...>::operator = (TCVariant &_Other) -> TCVariant &
		requires requires ()
		{
			this->fp_GetStreamable() = _Other.fp_GetStreamable();
		}
	{
		this->fp_GetStreamable() = _Other.fp_GetStreamable();
		return *this;
	}

	template <typename ...tp_CTypes>
	template <typename ...tfp_CParams>
	TCVariant<tp_CTypes...>::TCVariant(tfp_CParams && ...p_Param)
		: CParent(fg_Forward<tfp_CParams>(p_Param)...)
	{
	}

	template <typename ...tp_CTypes>
	template <typename ...tfp_CParams>
	TCVariant<tp_CTypes...>::TCVariant(TCVariant<tfp_CParams...> const &_Other)
		: CParent(_Other.fp_GetStreamable())
	{
	}

	template <typename ...tp_CTypes>
	template <typename ...tfp_CParams>
	TCVariant<tp_CTypes...>::TCVariant(TCVariant<tfp_CParams...> &_Other)
		: CParent(_Other.fp_GetStreamable())
	{
	}

	template <typename ...tp_CTypes>
	template <typename ...tfp_CParams>
	TCVariant<tp_CTypes...>::TCVariant(TCVariant<tfp_CParams...> &&_Other)
		: CParent(fg_Move(_Other.fp_GetStreamable()))
	{
	}

	template <typename ...tp_CTypes>
	template <typename ...tfp_CParams>
	auto TCVariant<tp_CTypes...>::operator = (TCVariant<tfp_CParams...> const &_Other) -> TCVariant &
		requires requires ()
		{
			this->fp_GetStreamable() = _Other.fp_GetStreamable();
		}
	{
		this->fp_GetStreamable() = _Other.fp_GetStreamable();
		return *this;
	}

	template <typename ...tp_CTypes>
	template <typename ...tfp_CParams>
	auto TCVariant<tp_CTypes...>::operator = (TCVariant<tfp_CParams...> &_Other) -> TCVariant &
		requires requires ()
		{
			this->fp_GetStreamable() = _Other.fp_GetStreamable();
		}
	{
		this->fp_GetStreamable() = _Other.fp_GetStreamable();
		return *this;
	}

	template <typename ...tp_CTypes>
	template <typename ...tfp_CParams>
	auto TCVariant<tp_CTypes...>::operator = (TCVariant<tfp_CParams...> &&_Other) -> TCVariant &
		requires requires ()
		{
			this->fp_GetStreamable() = fg_Move(_Other.fp_GetStreamable());
		}
	{
		this->fp_GetStreamable() = fg_Move(_Other.fp_GetStreamable());
		return *this;
	}

	template <typename ...tp_CTypes>
	template <typename tf_CParam>
	inline_small auto TCVariant<tp_CTypes...>::operator = (tf_CParam &&_Param) -> TCVariant &
		requires requires ()
		{
			this->CParent::operator = (fg_Forward<tf_CParam>(_Param));
		}
	{
		this->CParent::operator = (fg_Forward<tf_CParam>(_Param));
		return *this;
	}
}

namespace NMib::NStream::NPrivate
{
	template <typename t_CStream>
	TCVariantVisitor_Feed<t_CStream>::TCVariantVisitor_Feed(t_CStream &_Stream)
		: m_Stream(_Stream)
	{
	}

	template <typename t_CStream>
	void TCVariantVisitor_Feed<t_CStream>::operator () (CVoidTag _Tag)
	{
	}

	template <typename t_CStream>
	template <typename tf_CType>
	void TCVariantVisitor_Feed<t_CStream>::operator () (tf_CType &&_Data)
	{
		m_Stream << fg_Forward<tf_CType>(_Data);
	}

	template <typename t_CStream>
	TCVariantVisitor_FeedMove<t_CStream>::TCVariantVisitor_FeedMove(t_CStream &_Stream)
		: m_Stream(_Stream)
	{
	}

	template <typename t_CStream>
	void TCVariantVisitor_FeedMove<t_CStream>::operator () (CVoidTag _Tag)
	{
	}

	template <typename t_CStream>
	template <typename tf_CType>
	void TCVariantVisitor_FeedMove<t_CStream>::operator () (tf_CType &&_Data)
	{
		m_Stream << fg_Move(_Data);
	}

	template <typename t_CStream>
	TCVariantVisitor_Consume<t_CStream>::TCVariantVisitor_Consume(t_CStream &_Stream)
		: m_Stream(_Stream)
	{
	}

	template <typename t_CStream>
	void TCVariantVisitor_Consume<t_CStream>::operator () (CVoidTag _Tag)
	{
	}

	template <typename t_CStream>
	template <typename tf_CType>
	void TCVariantVisitor_Consume<t_CStream>::operator () (tf_CType &&_Data)
	{
		m_Stream >> fg_Forward<tf_CType>(_Data);
	}
}

namespace NMib::NStream
{
	template <typename t_CStream, typename t_CIndex, typename ...tp_CMembers>
	constexpr void TCBinaryStreamTypeReference<t_CStream, NStorage::TCVariantCommon<t_CIndex, tp_CMembers...>>::fs_Feed(t_CStream &_Stream, CStreamableVariant const &_Data)
	{
		_Stream << _Data.f_GetTypeID();
		_Data.f_Visit(NPrivate::TCVariantVisitor_Feed<t_CStream>(_Stream));
	}

	template <typename t_CStream, typename t_CIndex, typename ...tp_CMembers>
	constexpr void TCBinaryStreamTypeReference<t_CStream, NStorage::TCVariantCommon<t_CIndex, tp_CMembers...>>::fs_Feed(t_CStream &_Stream, CStreamableVariant &&_Data)
	{
		_Stream << _Data.f_GetTypeID();
		_Data.f_Visit(NPrivate::TCVariantVisitor_FeedMove<t_CStream>(_Stream));
	}

	template <typename t_CStream, typename t_CIndex, typename ...tp_CMembers>
	constexpr void TCBinaryStreamTypeReference<t_CStream, NStorage::TCVariantCommon<t_CIndex, tp_CMembers...>>::fs_Consume(t_CStream &_Stream, CStreamableVariant &_Data)
	{
		typename CStreamableVariant::CIndexType TypeID;
		_Stream >> TypeID;
		bool bSuccess = _Data.f_TryVisitCreate(TypeID, NPrivate::TCVariantVisitor_Consume<t_CStream>(_Stream));
		if (!bSuccess)
			DMibErrorStream(NStr::CStr::CFormat("Unsupported type '{}' in variant") << TypeID);
	}
}
