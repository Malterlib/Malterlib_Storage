// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStorage
{
	template <typename t_CType, typename ...tp_COptions>
	TCUniquePointer<t_CType, tp_COptions...>::CData::CData()
	{
	}

	template <typename t_CType, typename ...tp_COptions>
	TCUniquePointer<t_CType, tp_COptions...>::CData::CData(CAllocator const &_Other)
		: CAllocator(_Other)
	{
	}

	template <typename t_CType, typename ...tp_COptions>
	TCUniquePointer<t_CType, tp_COptions...>::CData::CData(CAllocator &&_Other)
		: CAllocator(fg_Move(_Other))
	{
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CParam0>
	TCUniquePointer<t_CType, tp_COptions...>::CData::CData(tf_CParam0 &&_Other)
		: CAllocator(fg_Forward<tf_CParam0>(_Other))
	{
	}

	template <typename t_CType, typename ...tp_COptions>
	TCUniquePointer<t_CType, tp_COptions...>::CData::CData(CData const &_Other)
	{
	}

	template <typename t_CType, typename ...tp_COptions>
	TCUniquePointer<t_CType, tp_COptions...>::CData::CData(CData &&_Other)
	{
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCUniquePointer<t_CType, tp_COptions...>::fp_GetAllocator() -> CAllocator &
	{
		return mp_Data;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCUniquePointer<t_CType, tp_COptions...>::fp_GetAllocator() const -> CAllocator const &
	{
		return mp_Data;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CDummy>
	void TCUniquePointer<t_CType, tp_COptions...>::fp_Delete()
	{
		if (mp_Data.m_pPointTo)
		{
			fg_DeleteObject(fp_GetAllocator(), mp_Data.m_pPointTo);
			mp_Data.m_pPointTo = nullptr;
		}
	}

	template <typename t_CType, typename ...tp_COptions>
	void TCUniquePointer<t_CType, tp_COptions...>::fp_Delete()
	{
		fp_Delete<t_CType>();
	}

	template <typename t_CType, typename ...tp_COptions>
	TCUniquePointer<t_CType, tp_COptions...>::TCUniquePointer()
	{
		mp_Data.m_pPointTo = nullptr;
	}

	template <typename t_CType, typename ...tp_COptions>
	TCUniquePointer<t_CType, tp_COptions...>::~TCUniquePointer()
	{
		fp_Delete();
	}

	template <typename t_CType, typename ...tp_COptions>
	TCUniquePointer<t_CType, tp_COptions...>::TCUniquePointer(TCCopy<TCUniquePointer> const &_Other)
		: mp_Data((*_Other).fp_GetAllocator())
	{
		mp_Data.m_pPointTo = fg_ConstructObject<t_CType>(fp_GetAllocator(), *((*_Other).mp_Data.m_pPointTo));
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	TCUniquePointer<t_CType, tp_COptions...>::TCUniquePointer(TCExplicit<tf_CType> &&_Other)
	{
		mp_Data.m_pPointTo = *_Other;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename tf_CAllocator>
	TCUniquePointer<t_CType, tp_COptions...>::TCUniquePointer(TCExplicit<tf_CType> &&_Other, tf_CAllocator &&_Allocator)
		: mp_Data(fg_Forward<tf_CAllocator>(_Allocator))
	{
		mp_Data.m_pPointTo = *_Other;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_CParams>
	TCUniquePointer<t_CType, tp_COptions...>::TCUniquePointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
	{
		static_assert(NTraits::cIsVoid<tf_CType> || NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, CAllocator>::mc_Value, "Not a valid conversion");
		mp_Data.m_pPointTo = _CreateParams.template f_Create<t_CType>(fp_GetAllocator());
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_CParams, typename tf_CAllocator>
	TCUniquePointer<t_CType, tp_COptions...>::TCUniquePointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams, tf_CAllocator &&_Allocator)
		: mp_Data(fg_Forward<tf_CAllocator>(_Allocator))
	{
		static_assert
			(
				NTraits::cIsVoid<tf_CType> || NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, NTraits::TCRemoveReference<tf_CAllocator>>::mc_Value
				, "Not a valid conversion"
			)
		;
		mp_Data.m_pPointTo = _CreateParams.template f_Create<t_CType>(fp_GetAllocator());
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	TCUniquePointer<t_CType, tp_COptions...>::TCUniquePointer(TCUniquePointer<tf_CType, tfp_COptions...> &&_pOther)
		requires (NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCUniquePointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value)
		: mp_Data(fg_Move(_pOther.fp_GetAllocator()))
	{
		mp_Data.m_pPointTo = _pOther.f_Detach();
	}

	template <typename t_CType, typename ...tp_COptions>
	TCUniquePointer<t_CType, tp_COptions...>::TCUniquePointer(TCUniquePointer &&_pOther)
		: mp_Data(fg_Move(_pOther.fp_GetAllocator()))
	{
		mp_Data.m_pPointTo = _pOther.mp_Data.m_pPointTo;
		_pOther.mp_Data.m_pPointTo = nullptr;
	}

	template <typename t_CType, typename ...tp_COptions>
	TCUniquePointer<t_CType, tp_COptions...>::TCUniquePointer(t_CType *_pPtr)
	{
		mp_Data.m_pPointTo = _pPtr;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CParam0>
	TCUniquePointer<t_CType, tp_COptions...>::TCUniquePointer(t_CType *_pPtr, tf_CParam0 &&_Param0)
		: mp_Data(fg_Forward<tf_CParam0>(_Param0))
	{
		mp_Data.m_pPointTo = _pPtr;
	}

	template <typename t_CType, typename ...tp_COptions>
	TCUniquePointer<t_CType, tp_COptions...>::TCUniquePointer(CNullPtr _pNull)
	{
		mp_Data.m_pPointTo = nullptr;
	}

	template <typename t_CType, typename ...tp_COptions>
	t_CType *TCUniquePointer<t_CType, tp_COptions...>::f_Detach()
	{
		t_CType *pRet = mp_Data.m_pPointTo;
		mp_Data.m_pPointTo = nullptr;
		return pRet;
	}

	template <typename t_CType, typename ...tp_COptions>
	t_CType *TCUniquePointer<t_CType, tp_COptions...>::f_Get() const
	{
		return mp_Data.m_pPointTo;
	}

	template <typename t_CType, typename ...tp_COptions>
	t_CType *TCUniquePointer<t_CType, tp_COptions...>::operator -> () const
	{
		return mp_Data.m_pPointTo;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCUniquePointer<t_CType, tp_COptions...>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
	{
		return NFunction::fg_MemberFunctionFunctor(_MemberPtr, (t_CType *)mp_Data.m_pPointTo);
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCUniquePointer<t_CType, tp_COptions...>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
	{
		return ((t_CType *)mp_Data.m_pPointTo)->*_MemberPtr;
	}

	template <typename t_CType, typename ...tp_COptions>
	mark_nodebug NTraits::TCAddLValueReference<t_CType> TCUniquePointer<t_CType, tp_COptions...>::operator * () const
		requires (!NTraits::cIsVoid<t_CType>)
	{
		return *mp_Data.m_pPointTo;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	auto TCUniquePointer<t_CType, tp_COptions...>::operator = (TCExplicit<tf_CType> &&_Other) -> TCUniquePointer &
	{
		fp_Delete();
		mp_Data.m_pPointTo = *_Other;
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCUniquePointer<t_CType, tp_COptions...>::operator = (TCCopy<TCUniquePointer> const &_Other) -> TCUniquePointer &
	{
		fp_Delete();
		fp_GetAllocator() = (*_Other).fp_GetAllocator();
		mp_Data.m_pPointTo = fg_ConstructObject<t_CType>(fp_GetAllocator(), *(*_Other).mp_Data.m_pPointTo);
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCUniquePointer<t_CType, tp_COptions...>::operator = (TCUniquePointer &&_pOther) -> TCUniquePointer &
	{
		fp_Delete();
		fp_GetAllocator() = fg_Move(_pOther.fp_GetAllocator());
		mp_Data.m_pPointTo = _pOther.mp_Data.m_pPointTo;
		_pOther.mp_Data.m_pPointTo = nullptr;
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCUniquePointer<t_CType, tp_COptions...>::operator = (CNullPtr _pNull) -> TCUniquePointer &
	{
		fp_Delete();
		mp_Data.m_pPointTo = nullptr;
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	auto TCUniquePointer<t_CType, tp_COptions...>::operator = (TCUniquePointer<tf_CType, tfp_COptions...> &&_pOther) -> TCUniquePointer &
		requires (NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCUniquePointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value)
	{
		fp_Delete();
		fp_GetAllocator() = fg_Move(_pOther.fp_GetAllocator());
		mp_Data.m_pPointTo = _pOther.f_Detach();
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_CParams>
	auto TCUniquePointer<t_CType, tp_COptions...>::operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams) -> TCUniquePointer &
	{
		static_assert(NTraits::cIsVoid<tf_CType> || NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, CAllocator>::mc_Value, "Not a valid conversion");
		fp_Delete();
		mp_Data.m_pPointTo = _CreateParams.template f_Create<t_CType>(fp_GetAllocator());
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	void TCUniquePointer<t_CType, tp_COptions...>::f_Clear()
	{
		fp_Delete();
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	bool TCUniquePointer<t_CType, tp_COptions...>::operator == (tf_CType *_pOther) const noexcept
	{
		return f_Get() == _pOther;
	}

	template <typename t_CType, typename ...tp_COptions>
	bool TCUniquePointer<t_CType, tp_COptions...>::operator == (CNullPtr _pOther) const noexcept
	{
		return f_Get() == _pOther;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	bool TCUniquePointer<t_CType, tp_COptions...>::operator == (TCUniquePointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept
	{
		return f_Get() == _pOther.f_Get();
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	auto TCUniquePointer<t_CType, tp_COptions...>::operator <=> (tf_CType *_pOther) const noexcept
	{
		return f_Get() <=> _pOther;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCUniquePointer<t_CType, tp_COptions...>::operator <=> (CNullPtr _pOther) const noexcept
	{
		return f_Get() <=> _pOther;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	auto TCUniquePointer<t_CType, tp_COptions...>::operator <=> (TCUniquePointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept
	{
		return f_Get() <=> _pOther.f_Get();
	}

	template <typename t_CType, typename ...tp_COptions>
	bool TCUniquePointer<t_CType, tp_COptions...>::f_IsEmpty() const
	{
		return mp_Data.m_pPointTo == nullptr;
	}

	template <typename t_CType, typename ...tp_COptions>
	inline_small TCUniquePointer<t_CType, tp_COptions...>::operator bool () const
	{
		return !f_IsEmpty();
	}
}
