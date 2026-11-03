// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStorage
{
	template <typename t_CType>
	TCAutoClearPtrMemberDebug<t_CType>::~TCAutoClearPtrMemberDebug()
	{
		f_Clear();
	}

	template <typename t_CType>
	void TCAutoClearPtrMemberDebug<t_CType>::f_Clear()
	{
		CAutoClearPtr *pPtr = m_Linked.f_Pop();
		while (pPtr)
		{
			((CAutoClearPtrDefaultDummy *)pPtr)->m_pPointTo = nullptr;
			pPtr = m_Linked.f_Pop();
		}
	}

	template <typename t_CType>
	TCAutoClearPtr<t_CType>::TCAutoClearPtr()
		: mp_pPointTo(nullptr)
	{
	}

	template <typename t_CType>
	TCAutoClearPtr<t_CType>::TCAutoClearPtr(t_CType *_pPtr)
	{
		if (_pPtr)
			_pPtr->m_AutoClearPtrMember.m_Linked.f_Insert(this);
		mp_pPointTo = _pPtr;
	}

	template <typename t_CType>
	TCAutoClearPtr<t_CType>::TCAutoClearPtr(TCAutoClearPtr const &_pOther)
	{
		if (_pOther)
			_pOther->m_AutoClearPtrMember.m_Linked.f_Insert(this);
		mp_pPointTo = _pOther.mp_pPointTo;
	}

	template <typename t_CType>
	auto TCAutoClearPtr<t_CType>::operator = (t_CType *_pPtr) -> TCAutoClearPtr &
	{
		fp_RemoveOld();
		if (_pPtr)
			_pPtr->m_AutoClearPtrMember.m_Linked.f_Insert(this);

		mp_pPointTo = _pPtr;
		return *this;
	}

	template <typename t_CType>
	auto TCAutoClearPtr<t_CType>::operator = (TCAutoClearPtr const &_pOther) -> TCAutoClearPtr &
	{
		fp_RemoveOld();
		if (_pOther)
			_pOther->m_AutoClearPtrMember.m_Linked.f_Insert(this);

		mp_pPointTo = _pOther.mp_pPointTo;
		return *this;
	}

	template <typename t_CType>
	TCAutoClearPtr<t_CType>::operator t_CType * () const
	{
		return mp_pPointTo;
	}

	template <typename t_CType>
	t_CType *TCAutoClearPtr<t_CType>::operator -> () const
	{
		return mp_pPointTo;
	}

	template <typename t_CType>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCAutoClearPtr<t_CType>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
	{
		return NFunction::fg_MemberFunctionFunctor(_MemberPtr, mp_pPointTo);
	}

	template <typename t_CType>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCAutoClearPtr<t_CType>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
	{
		return mp_pPointTo->*_MemberPtr;
	}

	template <typename t_CType>
	mark_nodebug t_CType &TCAutoClearPtr<t_CType>::operator * () const
	{
		return *mp_pPointTo;
	}

	template <typename t_CType>
	template <typename tf_CType2>
	bool TCAutoClearPtr<t_CType>::operator == (tf_CType2 const &_Other) const noexcept
	{
		return operator t_CType * () == (t_CType *)_Other;
	}

	template <typename t_CType>
	template <typename tf_CType2>
	bool TCAutoClearPtr<t_CType>::operator == (TCAutoClearPtr<tf_CType2> const &_pOther) const noexcept
	{
		return operator t_CType * () == _pOther.operator tf_CType2 * ();
	}

	template <typename t_CType>
	void TCAutoClearPtr<t_CType>::fp_RemoveOld()
	{
		if (mp_pPointTo)
			mp_pPointTo->m_AutoClearPtrMember.m_Linked.f_Remove(this);
	}

	template <typename t_CType>
	TCAutoClearPtrDebug<t_CType>::TCAutoClearPtrDebug()
		: mp_pPointTo(nullptr)
	{
	}

	template <typename t_CType>
	TCAutoClearPtrDebug<t_CType>::TCAutoClearPtrDebug(t_CType *_pPtr)
	{
		if (_pPtr)
			_pPtr->m_AutoClearPtrMemberDebug.m_Linked.f_Insert(this);
		mp_pPointTo = _pPtr;
	}

	template <typename t_CType>
	TCAutoClearPtrDebug<t_CType>::TCAutoClearPtrDebug(TCAutoClearPtrDebug const &_pOther)
	{
		if (_pOther)
			_pOther->m_AutoClearPtrMemberDebug.m_Linked.f_Insert(this);
		mp_pPointTo = _pOther.mp_pPointTo;
	}

	template <typename t_CType>
	auto TCAutoClearPtrDebug<t_CType>::operator = (t_CType *_pPtr) -> TCAutoClearPtrDebug &
	{
		fp_RemoveOld();

		if (_pPtr)
			_pPtr->m_AutoClearPtrMemberDebug.m_Linked.f_Insert(this);

		mp_pPointTo = _pPtr;
		return *this;
	}

	template <typename t_CType>
	auto TCAutoClearPtrDebug<t_CType>::operator = (TCAutoClearPtrDebug const &_pOther) -> TCAutoClearPtrDebug &
	{
		fp_RemoveOld();

		if (_pOther)
			_pOther->m_AutoClearPtrMemberDebug.m_Linked.f_Insert(this);

		mp_pPointTo = _pOther.mp_pPointTo;
		return *this;
	}

	template <typename t_CType>
	TCAutoClearPtrDebug<t_CType>::operator t_CType * () const
	{
		return mp_pPointTo;
	}

	template <typename t_CType>
	t_CType *TCAutoClearPtrDebug<t_CType>::operator -> () const
	{
		return mp_pPointTo;
	}

	template <typename t_CType>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCAutoClearPtrDebug<t_CType>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
	{
		return NFunction::fg_MemberFunctionFunctor(_MemberPtr, mp_pPointTo);
	}

	template <typename t_CType>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCAutoClearPtrDebug<t_CType>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
	{
		return mp_pPointTo->*_MemberPtr;
	}

	template <typename t_CType>
	mark_nodebug t_CType &TCAutoClearPtrDebug<t_CType>::operator * () const
	{
		return *mp_pPointTo;
	}

	template <typename t_CType>
	template <typename tf_CType2>
	bool TCAutoClearPtrDebug<t_CType>::operator == (tf_CType2 const &_Other) const noexcept
	{
		return operator t_CType * () == (t_CType *)_Other;
	}

	template <typename t_CType>
	template <typename tf_CType2>
	bool TCAutoClearPtrDebug<t_CType>::operator == (TCAutoClearPtrDebug<tf_CType2> const &_pOther) const noexcept
	{
		return operator t_CType * () == _pOther.operator tf_CType2 * ();
	}

	template <typename t_CType>
	void TCAutoClearPtrDebug<t_CType>::fp_RemoveOld()
	{
		if (mp_pPointTo)
			mp_pPointTo->m_AutoClearPtrMemberDebug.m_Linked.f_Remove(this);
	}

#if defined DMibContractsConfigure_CheckEnabled
	template <typename t_CType>
	TCDebugPointer<t_CType>::TCDebugPointer()
		: mp_pPointTo(nullptr)
	{
	}

	template <typename t_CType>
	TCDebugPointer<t_CType>::TCDebugPointer(t_CType *_pPtr)
	{
		if (_pPtr)
			_pPtr->m_DebugPointerMember.m_Linked.f_Insert(this);
		mp_pPointTo = _pPtr;
	}

	template <typename t_CType>
	TCDebugPointer<t_CType>::TCDebugPointer(TCDebugPointer const &_Other)
	{
		if (_Other)
			_Other->m_DebugPointerMember.m_Linked.f_Insert(this);
		mp_pPointTo = _Other.mp_pPointTo;
	}

	template <typename t_CType>
	auto TCDebugPointer<t_CType>::operator = (t_CType *_pPtr) -> TCDebugPointer &
	{
		fp_RemoveOld();
		if (_pPtr)
			_pPtr->m_DebugPointerMember.m_Linked.f_Insert(this);

		mp_pPointTo = _pPtr;
		return *this;
	}

	template <typename t_CType>
	auto TCDebugPointer<t_CType>::operator = (TCDebugPointer const &_Other) -> TCDebugPointer &
	{
		fp_RemoveOld();
		if (_Other)
			_Other->m_DebugPointerMember.m_Linked.f_Insert(this);

		mp_pPointTo = _Other.mp_pPointTo;
		return *this;
	}

	template <typename t_CType>
	TCDebugPointer<t_CType>::operator t_CType * () const
	{
		return mp_pPointTo;
	}

	template <typename t_CType>
	t_CType *TCDebugPointer<t_CType>::operator -> () const
	{
		return mp_pPointTo;
	}

	template <typename t_CType>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCDebugPointer<t_CType>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
	{
		return NFunction::fg_MemberFunctionFunctor(_MemberPtr, mp_pPointTo);
	}

	template <typename t_CType>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCDebugPointer<t_CType>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
	{
		return mp_pPointTo->*_MemberPtr;
	}

	template <typename t_CType>
	mark_nodebug t_CType &TCDebugPointer<t_CType>::operator * () const
	{
		return *mp_pPointTo;
	}

	template <typename t_CType>
	template <typename tf_CType2>
	bool TCDebugPointer<t_CType>::operator == (tf_CType2 const &_Other) const noexcept
	{
		return operator t_CType * () == (t_CType *)_Other;
	}

	template <typename t_CType>
	template <typename tf_CType2>
	bool TCDebugPointer<t_CType>::operator == (TCDebugPointer<tf_CType2> const &_Other) const noexcept
	{
		return operator t_CType * () == _Other.operator tf_CType2 * ();
	}

	template <typename t_CType>
	void TCDebugPointer<t_CType>::fp_RemoveOld()
	{
		if (mp_pPointTo)
			mp_pPointTo->m_DebugPointerMember.m_Linked.f_Remove(this);
	}
#else
	template <typename t_CType>
	TCDebugPointer<t_CType>::TCDebugPointer()
		: mp_pPointTo(nullptr)
	{
	}

	template <typename t_CType>
	TCDebugPointer<t_CType>::TCDebugPointer(t_CType *_pPtr)
	{
		mp_pPointTo = _pPtr;
	}

	template <typename t_CType>
	TCDebugPointer<t_CType>::TCDebugPointer(TCDebugPointer const &_pOther)
	{
		mp_pPointTo = _pOther.mp_pPointTo;
	}

	template <typename t_CType>
	auto TCDebugPointer<t_CType>::operator = (t_CType *_pPtr) -> TCDebugPointer &
	{
		mp_pPointTo = _pPtr;
		return *this;
	}

	template <typename t_CType>
	auto TCDebugPointer<t_CType>::operator = (TCDebugPointer const &_pOther) -> TCDebugPointer &
	{
		mp_pPointTo = _pOther.mp_pPointTo;
		return *this;
	}

	template <typename t_CType>
	TCDebugPointer<t_CType>::operator t_CType * () const
	{
		return mp_pPointTo;
	}

	template <typename t_CType>
	t_CType *TCDebugPointer<t_CType>::operator -> () const
	{
		return mp_pPointTo;
	}

	template <typename t_CType>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCDebugPointer<t_CType>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
	{
		return NFunction::fg_MemberFunctionFunctor(_MemberPtr, mp_pPointTo);
	}

	template <typename t_CType>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCDebugPointer<t_CType>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
	{
		return mp_pPointTo->*_MemberPtr;
	}

	template <typename t_CType>
	mark_nodebug t_CType &TCDebugPointer<t_CType>::operator * () const
	{
		return *mp_pPointTo;
	}

	template <typename t_CType>
	template <typename tf_CType2>
	bool TCDebugPointer<t_CType>::operator == (tf_CType2 const &_Other) const noexcept
	{
		return operator t_CType * () == (t_CType *)_Other;
	}

	template <typename t_CType>
	template <typename tf_CType2>
	bool TCDebugPointer<t_CType>::operator == (TCDebugPointer<tf_CType2> const &_pOther) const noexcept
	{
		return operator t_CType * () == _pOther.operator tf_CType2 * ();
	}
#endif

	template <typename t_CType>
	TCPointer<t_CType>::TCPointer()
		: mp_pPointTo(nullptr)
	{
	}

	template <typename t_CType>
	TCPointer<t_CType>::TCPointer(t_CType *_pPtr)
	{
		mp_pPointTo = _pPtr;
	}

	template <typename t_CType>
	template <typename tf_CType>
	TCPointer<t_CType>::TCPointer(TCExplicit<tf_CType> &&_Other)
	{
		mp_pPointTo = *_Other;
	}

	template <typename t_CType>
	TCPointer<t_CType>::TCPointer(TCPointer const &_pOther)
	{
		mp_pPointTo = _pOther.mp_pPointTo;
	}

	template <typename t_CType>
	auto TCPointer<t_CType>::operator = (t_CType *_pPtr) -> TCPointer &
	{
		mp_pPointTo = _pPtr;
		return *this;
	}

	template <typename t_CType>
	auto TCPointer<t_CType>::operator = (TCPointer const &_pOther) -> TCPointer &
	{
		mp_pPointTo = _pOther.mp_pPointTo;
		return *this;
	}

	template <typename t_CType>
	template <typename tf_CType>
	auto TCPointer<t_CType>::operator = (TCExplicit<tf_CType> &&_Other) -> TCPointer &
	{
		mp_pPointTo = *_Other;
		return *this;
	}

	template <typename t_CType>
	void TCPointer<t_CType>::f_Clear()
	{
		mp_pPointTo = nullptr;
	}

	template <typename t_CType>
	t_CType *TCPointer<t_CType>::f_Get() const
	{
		return mp_pPointTo;
	}

	template <typename t_CType>
	TCPointer<t_CType>::operator t_CType * () const
	{
		return mp_pPointTo;
	}

	template <typename t_CType>
	t_CType *TCPointer<t_CType>::operator -> () const
	{
		return mp_pPointTo;
	}

	template <typename t_CType>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCPointer<t_CType>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
	{
		return NFunction::fg_MemberFunctionFunctor(_MemberPtr, mp_pPointTo);
	}

	template <typename t_CType>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCPointer<t_CType>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
	{
		return mp_pPointTo->*_MemberPtr;
	}

	template <typename t_CType>
	mark_nodebug t_CType &TCPointer<t_CType>::operator * () const
	{
		return *mp_pPointTo;
	}

	template <typename t_CType>
	template <typename tf_CType2>
	bool TCPointer<t_CType>::operator == (tf_CType2 const &_Other) const noexcept
	{
		return operator t_CType * () == (t_CType *)_Other;
	}

	template <typename t_CType>
	template <typename tf_CType2>
	bool TCPointer<t_CType>::operator == (TCPointer<tf_CType2> const &_pOther) const noexcept
	{
		return operator t_CType * () == _pOther.operator tf_CType2 * ();
	}

	namespace NPrivate
	{
		template <typename tf_CType>
		tf_CType *fg_GetSharedPointerPointer(tf_CType *_pIn)
		{
			return _pIn;
		}

		template <typename tf_CToType, typename tf_CType>
		tf_CType *fg_ConvertSharedPointer(tf_CType *_pIn, tf_CToType *_pDummy)
		{
			return _pIn;
		}

		template <typename t_CType, typename t_CAllocator, CSharedPointerOptionUnderlying t_Options>
		TCSharedPointerData<t_CType, t_CAllocator, t_Options>::TCSharedPointerData()
		{
		}

		template <typename t_CType, typename t_CAllocator, CSharedPointerOptionUnderlying t_Options>
		TCSharedPointerData<t_CType, t_CAllocator, t_Options>::TCSharedPointerData(t_CAllocator const &_Other)
			: t_CAllocator(_Other)
		{
		}

		template <typename t_CType, typename t_CAllocator, CSharedPointerOptionUnderlying t_Options>
		TCSharedPointerData<t_CType, t_CAllocator, t_Options>::TCSharedPointerData(t_CAllocator &&_Other)
			: t_CAllocator(fg_Move(_Other))
		{
		}

		template <typename t_CType, typename t_CAllocator, CSharedPointerOptionUnderlying t_Options>
		template <typename tf_CParam0>
		TCSharedPointerData<t_CType, t_CAllocator, t_Options>::TCSharedPointerData(tf_CParam0 &&_Other)
			: t_CAllocator(fg_Forward<tf_CParam0>(_Other))
		{
		}

		template <typename t_CType, typename t_CAllocator, CSharedPointerOptionUnderlying t_Options>
		TCSharedPointerData<t_CType, t_CAllocator, t_Options>::TCSharedPointerData(TCSharedPointerData const &_Other)
		{
		}

		template <typename t_CType, typename t_CAllocator, CSharedPointerOptionUnderlying t_Options>
		TCSharedPointerData<t_CType, t_CAllocator, t_Options>::TCSharedPointerData(TCSharedPointerData &&_Other)
		{
		}
	}

	template <typename tf_CObjectType>
	NMemory::CCapturedDelete fg_DeleteWeakObjectGetCapturedDelete(tf_CObjectType *_pObject)
	{
		DMibFastCheck(_pObject->m_RefCount.f_Get() == -1);

		static_assert(sizeof(tf_CObjectType) > 0);
		static_assert(!NTraits::cIsAbstract<tf_CObjectType> || NTraits::cHasVirtualDestructor<tf_CObjectType> || NTraits::cIsFinal<tf_CObjectType>);

		if constexpr (NTraits::cHasVirtualDestructor<tf_CObjectType> && !NTraits::cIsFinal<tf_CObjectType>)
		{
			static_assert(!NTraits::cHasOperatorDelete<tf_CObjectType>);
#ifdef DMibPSizedDestructors
			// TCHasVirtualDestructorOverride speaks for a type that is incomplete where it is used; here the type is complete
			static_assert(NTraits::cHasSizedDestructor<tf_CObjectType>, "TCHasVirtualDestructorOverride claims a virtual destructor the type does not have");

			// The deleting destructor of the dynamic type destroys the object and
			// returns the memory it occupies, which the last weak reference frees.
			void *pMemory;
			umint Size = __builtin_malterlib_destroy(_pObject, &pMemory);

			return {pMemory, Size};
#else
			if constexpr (NMib::NPrivate::cHas_m_VirtualAllocSize<tf_CObjectType>)
			{
				umint DeleteSize = _pObject->m_VirtualAllocSize;
				_pObject->~tf_CObjectType();

				return {_pObject, DeleteSize};
			}
			else
			{
#	if defined(DMibPOverrideOperatorNew)
				NMemory::CCaptureDefaultDelete Captured;
				delete _pObject;

				DMibFastCheck(Captured.m_Captured.m_pMemory);

				return Captured.m_Captured;
#	else
				static_assert(!NTraits::cHasVirtualDestructor<tf_CObjectType>); // Operator new has to be overridden for this to work
				return {_pObject, 0};
#	endif
			}
#endif
		}
		else
		{
			_pObject->~tf_CObjectType();
			return {_pObject, sizeof(tf_CObjectType)};
		}
	}

	template <typename tf_CObjectType, typename tf_CAllocator>
	void fg_DeleteWeakObject(tf_CAllocator &&_Allocator, tf_CObjectType *_pObject)
	{
		NMemory::CCapturedDelete CapturedDelete = fg_DeleteWeakObjectGetCapturedDelete(_pObject);

		_pObject->m_RefCount.f_WeakSetCapturedDelete(CapturedDelete);
		if (_pObject->m_RefCount.f_WeakDecrease(DIfRefCountDebugging(nullptr)) == 0)
		{
#if DMibConfig_RefCountDebugging && DMibConfig_RefCountLeakDebugging
			_pObject->m_RefCount.m_Debug->m_DestroyLocation.f_FetchOr(0b00000000001);
#endif
			if (CapturedDelete.m_Size)
				fg_Forward<tf_CAllocator>(_Allocator).f_Free(CapturedDelete.m_pMemory, CapturedDelete.m_Size);
			else
				fg_Forward<tf_CAllocator>(_Allocator).f_FreeNoSize(CapturedDelete.m_pMemory);
		}
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::fp_GetAllocator() -> CAllocator &
	{
		return mp_Data;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::fp_GetAllocator() const -> CAllocator const &
	{
		return mp_Data;
	}

	template <typename t_CType, typename ...tp_COptions>
	void TCSharedPointer<t_CType, tp_COptions...>::fp_Set(CInternalData *_pPtr)
	{
		fp_Delete();
		if (_pPtr)
			_pPtr->m_RefCount.f_Increase(DIfRefCountDebugging(mp_Data.m_DebugRef));
		mp_Data.m_pPointTo = _pPtr;
	}

	template <typename t_CType, typename ...tp_COptions>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(NPrivate::CShareAsConstTag _Tag, CAllocator const &_Allocator, CInternalData *_pPointTo)
		: mp_Data(_Allocator)
	{
		fp_SetInit(_pPointTo);
	}

	template <typename t_CType, typename ...tp_COptions>
	void TCSharedPointer<t_CType, tp_COptions...>::fp_SetAttach(CInternalData *_pPtr)
	{
		fp_Delete();
		mp_Data.m_pPointTo = _pPtr;
		DIfRefCountDebugging(mp_Data.m_pPointTo->m_RefCount.f_Initial(mp_Data.m_DebugRef));
	}

	template <typename t_CType, typename ...tp_COptions>
	void TCSharedPointer<t_CType, tp_COptions...>::fp_SetInit(CInternalData *_pPtr)
	{
		if (_pPtr)
			_pPtr->m_RefCount.f_Increase(DIfRefCountDebugging(mp_Data.m_DebugRef));
		mp_Data.m_pPointTo = _pPtr;
	}

	template <typename t_CType, typename ...tp_COptions>
	void TCSharedPointer<t_CType, tp_COptions...>::fp_SetConstruct(CInternalData *_pPtr)
	{
		mp_Data.m_pPointTo = _pPtr;
		DIfRefCountDebugging(mp_Data.m_pPointTo->m_RefCount.f_Initial(mp_Data.m_DebugRef));
	}

	template <typename t_CType, typename ...tp_COptions>
	void TCSharedPointer<t_CType, tp_COptions...>::fp_SetCounted(CInternalData *_pPtr)
	{
		mp_Data.m_pPointTo = _pPtr;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::fp_Get() const -> CInternalData *
	{
		return mp_Data.m_pPointTo;
	}

	template <typename t_CType, typename ...tp_COptions>
	bool TCSharedPointer<t_CType, tp_COptions...>::fp_Delete()
	{
		if (!mp_Data.m_pPointTo) [[unlikely]]
			return false;

		bool bRet = false;
		if (mp_Data.m_pPointTo->m_RefCount.f_Decrease(DIfRefCountDebugging(mp_Data.m_DebugRef)) == 0)
		{
			if constexpr (mcp_bSupportWeak)
			{
#if DMibConfig_RefCountDebugging && DMibConfig_RefCountLeakDebugging
				mp_Data.m_pPointTo->m_RefCount.m_Debug->m_DestroyLocation.f_FetchOr(0b00000000010);
#endif
				auto Cleanup = g_OnScopeExit / [&]()
					{
#if DMibConfig_RefCountDebugging && DMibConfig_RefCountLeakDebugging
						mp_Data.m_pPointTo->m_RefCount.m_Debug->m_DestroyLocation.f_FetchOr(0b10000000000);
#endif
						// Protect against exception in destructor
						mp_Data.m_pPointTo->m_RefCount.f_Increase
							(
#if DMibConfig_RefCountDebugging
#	if DMibEnableSafeCheck > 0
								mp_Data.m_DebugRef
								, true
#	else
								mp_Data.m_DebugRef
#	endif
#else
#	if DMibEnableSafeCheck > 0
								true
#	endif
#endif
							)
						;
					}
				;

				fg_DeleteWeakObject(fp_GetAllocator(), (CInternalData *)mp_Data.m_pPointTo);
				Cleanup.f_Clear();
				bRet = true;
			}
			else
			{
#if DMibConfig_RefCountDebugging && DMibConfig_RefCountLeakDebugging
				mp_Data.m_pPointTo->m_RefCount.m_Debug->m_DestroyLocation.f_FetchOr(0b00000000100);
#endif
				auto Cleanup = g_OnScopeExit / [&]()
					{
#if DMibConfig_RefCountDebugging && DMibConfig_RefCountLeakDebugging
						mp_Data.m_pPointTo->m_RefCount.m_Debug->m_DestroyLocation.f_FetchOr(0b00000001000);
#endif
						// Protect against exception in destructor
						mp_Data.m_pPointTo->m_RefCount.f_Increase(DIfRefCountDebugging(mp_Data.m_DebugRef));
					}
				;

				fg_DeleteObject(fp_GetAllocator(), mp_Data.m_pPointTo);
				Cleanup.f_Clear();
				bRet = true;
			}
		}
		mp_Data.m_pPointTo = nullptr;

		return bRet;
	}

	// Used by weak pointer
	template <typename t_CType, typename ...tp_COptions>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(CAllocator const &_Allocator)
		: mp_Data(_Allocator)
	{
		mp_Data.m_pPointTo = nullptr;
	}

	// The mutable handle survives; callers must stop modifying the object before concurrent const readers use it.
	template <typename t_CType, typename ...tp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::f_ShareAsConst() const -> TCSharedPointer<t_CType const, tp_COptions...>
	{
		using CConst = TCSharedPointer<t_CType const, tp_COptions...>;

		return CConst(NPrivate::CShareAsConstTag(), fp_GetAllocator(), NPrivate::fg_ConvertSharedPointer(fp_Get(), (typename CConst::CInternalData *)nullptr));
	}

	template <typename t_CType, typename ...tp_COptions>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer()
	{
		mp_Data.m_pPointTo = nullptr;
	}

	template <typename t_CType, typename ...tp_COptions>
	TCSharedPointer<t_CType, tp_COptions...>::~TCSharedPointer()
	{
		fp_Delete();
	}

	template <typename t_CType, typename ...tp_COptions>
	void TCSharedPointer<t_CType, tp_COptions...>::f_ForceDelete()
	{
		DMibFastCheck(mp_Data.m_pPointTo && mp_Data.m_pPointTo->m_RefCount.f_Get() == 0);

		DIfRefCountDebugging(mp_Data.m_pPointTo->m_RefCount.f_Remove(mp_Data.m_DebugRef));

		if constexpr (mcp_bSupportWeak)
		{
#if DMibConfig_RefCountDebugging && DMibConfig_RefCountLeakDebugging
			mp_Data.m_pPointTo->m_RefCount.m_Debug->m_DestroyLocation.f_FetchOr(0b0000'0010'0000'0000);
#endif
			fg_DeleteWeakObject(fp_GetAllocator(), (CInternalData *)mp_Data.m_pPointTo);
		}
		else
		{
#if DMibConfig_RefCountDebugging && DMibConfig_RefCountLeakDebugging
			mp_Data.m_pPointTo->m_RefCount.m_Debug->m_DestroyLocation.f_FetchOr(0b0000'1000'0000'0000);
#endif
			fg_DeleteObject(fp_GetAllocator(), mp_Data.m_pPointTo);
		}
		mp_Data.m_pPointTo = nullptr;
	}

	template <typename t_CType, typename ...tp_COptions>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(TCCopy<TCSharedPointer> const &_Other)
		: mp_Data((*_Other).fp_GetAllocator())
	{
		mp_Data.m_pPointTo = nullptr; // Protect against exception in constructor
		if (*_Other)
			fp_SetConstruct(fg_ConstructObject<CInternalData>(fp_GetAllocator(), *((*_Other).mp_Data.m_pPointTo)));
	}

	template <typename t_CType, typename ...tp_COptions>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(TCSharedPointer const &_pOther)
		: mp_Data(_pOther.fp_GetAllocator())
	{
		fp_SetInit(_pOther.mp_Data.m_pPointTo);
	}

	template <typename t_CType, typename ...tp_COptions>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(TCSharedPointer &&_pOther)
		: mp_Data(fg_Move(_pOther.fp_GetAllocator()))
	{
		mp_Data.m_pPointTo = _pOther.mp_Data.m_pPointTo;
		_pOther.mp_Data.m_pPointTo = nullptr;
		DIfRefCountDebugging
			(
				if (mp_Data.m_pPointTo)
					mp_Data.m_pPointTo->m_RefCount.f_Move(_pOther.mp_Data.m_DebugRef, mp_Data.m_DebugRef);
			)
		;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther)
		requires
		(
			NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
			&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
		)
		: mp_Data(_pOther.fp_GetAllocator())
	{
		static_assert(mcp_bSupportWeak == TCSharedPointer<tf_CType, tfp_COptions...>::mcp_bSupportWeak);
		fp_SetInit(NPrivate::fg_ConvertSharedPointer(_pOther.fp_Get(), (CInternalData *)nullptr));
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(TCSharedPointer<tf_CType, tfp_COptions...> &&_pOther)
		requires
		(
			NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
			&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
		)
		: mp_Data(fg_Move(_pOther.fp_GetAllocator()))
	{
		static_assert(mcp_bSupportWeak == TCSharedPointer<tf_CType, tfp_COptions...>::mcp_bSupportWeak);
		mp_Data.m_pPointTo = NPrivate::fg_ConvertSharedPointer(_pOther.mp_Data.m_pPointTo, (CInternalData *)nullptr);
		_pOther.mp_Data.m_pPointTo = nullptr;
		DIfRefCountDebugging
			(
				if (mp_Data.m_pPointTo)
					mp_Data.m_pPointTo->m_RefCount.f_Move(_pOther.mp_Data.m_DebugRef, mp_Data.m_DebugRef);
			)
		;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_CParams>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
	{
		static_assert(NTraits::cIsVoid<tf_CType> || NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, CAllocator>::mc_Value, "Not a valid conversion");
		mp_Data.m_pPointTo = nullptr; // Protect against exception in constructor
		fp_SetConstruct
			(
				NPrivate::fg_ConvertSharedPointer
				(
					fg_TransformConstruct<CData::template TCChooseSharedPointerType>(fg_Move(_CreateParams)).template f_Create<CInternalData>(fp_GetAllocator())
					, (CInternalData *)nullptr
				)
			)
		;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_CParams, typename tf_CAllocator>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams, tf_CAllocator &&_Allocator)
		: mp_Data(fg_Forward<tf_CAllocator>(_Allocator))
	{
		static_assert
			(
				NTraits::cIsVoid<tf_CType> || NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, NTraits::TCRemoveReference<tf_CAllocator>>::mc_Value
				, "Not a valid conversion"
			)
		;
		mp_Data.m_pPointTo = nullptr; // Protect against exception in constructor
		fp_SetConstruct
			(
				NPrivate::fg_ConvertSharedPointer
				(
					fg_TransformConstruct<CData::template TCChooseSharedPointerType>(fg_Move(_CreateParams)).template f_Create<CInternalData>(fg_Forward<tf_CAllocator>(_Allocator))
					, (CInternalData *)nullptr
				)
			)
		;
	}

	template <typename t_CType, typename ...tp_COptions>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(t_CType *_pPtr)
	{
		fp_SetInit(_pPtr);
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CParam0>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(t_CType *_pPtr, tf_CParam0 &&_Param0)
		: mp_Data(fg_Forward<tf_CParam0>(_Param0))
	{
		fp_SetInit(_pPtr);
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(TCExplicit<tf_CType> &&_Other)
	{
		fp_SetInit(*_Other);
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename tf_CAllocator>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(TCExplicit<tf_CType> &&_Other, tf_CAllocator &&_Allocator)
		: mp_Data(fg_Forward<tf_CAllocator>(_Allocator))
	{
		fp_SetInit(*_Other);
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(TCAttach<tf_CType> &&_Other)
	{
		fp_SetConstruct(*_Other);
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename tf_CAllocator>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(TCAttach<tf_CType> &&_Other, tf_CAllocator &&_Allocator)
		: mp_Data(fg_Forward<tf_CAllocator>(_Allocator))
	{
		fp_SetConstruct(*_Other);
	}

	template <typename t_CType, typename ...tp_COptions>
	TCSharedPointer<t_CType, tp_COptions...>::TCSharedPointer(CNullPtr _pNull)
	{
		mp_Data.m_pPointTo = nullptr;
	}

	template <typename t_CType, typename ...tp_COptions>
	t_CType *TCSharedPointer<t_CType, tp_COptions...>::f_Detach()
	{
		auto pReturn = fg_Exchange(mp_Data.m_pPointTo, nullptr);
		DIfRefCountDebugging
			(
				if (pReturn)
					pReturn->m_RefCount.f_Remove(mp_Data.m_DebugRef)
			)
		;
		return pReturn;
	}

	template <typename t_CType, typename ...tp_COptions>
	bool TCSharedPointer<t_CType, tp_COptions...>::f_Clear()
	{
		return fp_Delete();
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::f_Weak() const -> CWeakPointer
	{
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	t_CType *TCSharedPointer<t_CType, tp_COptions...>::f_Get() const
	{
		return NPrivate::fg_GetSharedPointerPointer((CInternalData *)mp_Data.m_pPointTo);
	}

	template <typename t_CType, typename ...tp_COptions>
	t_CType *TCSharedPointer<t_CType, tp_COptions...>::operator -> () const
	{
		return NPrivate::fg_GetSharedPointerPointer((CInternalData *)mp_Data.m_pPointTo);
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCSharedPointer<t_CType, tp_COptions...>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
	{
		return NFunction::fg_MemberFunctionFunctor(_MemberPtr, NPrivate::fg_GetSharedPointerPointer((CInternalData *)mp_Data.m_pPointTo));
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CMemberPtr>
	mark_artificial mark_nodebug inline_always auto TCSharedPointer<t_CType, tp_COptions...>::operator ->* (tf_CMemberPtr const &_MemberPtr) const
		-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
	{
		return (NPrivate::fg_GetSharedPointerPointer((CInternalData *)mp_Data.m_pPointTo))->*_MemberPtr;
	}

	template <typename t_CType, typename ...tp_COptions>
	mark_nodebug t_CType &TCSharedPointer<t_CType, tp_COptions...>::operator * () const
	{
		return *NPrivate::fg_GetSharedPointerPointer((CInternalData *)mp_Data.m_pPointTo);
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::operator = (CNullPtr _pNull) -> TCSharedPointer &
	{
		fp_Delete();
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	auto TCSharedPointer<t_CType, tp_COptions...>::operator = (TCExplicit<tf_CType> &&_Other) -> TCSharedPointer &
	{
		fp_Set(*_Other);
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	auto TCSharedPointer<t_CType, tp_COptions...>::operator = (TCAttach<tf_CType> &&_Other) -> TCSharedPointer &
	{
		fp_SetAttach(*_Other);
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::operator = (TCSharedPointer &&_pOther) -> TCSharedPointer &
	{
		fp_Delete();
		fp_GetAllocator() = fg_Move(_pOther.fp_GetAllocator());
		mp_Data.m_pPointTo = _pOther.mp_Data.m_pPointTo;
		_pOther.mp_Data.m_pPointTo = nullptr;
		DIfRefCountDebugging
			(
				if (mp_Data.m_pPointTo)
					mp_Data.m_pPointTo->m_RefCount.f_Move(_pOther.mp_Data.m_DebugRef, mp_Data.m_DebugRef);
			)
		;
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::operator = (TCSharedPointer const &_pOther) -> TCSharedPointer &
	{
		fp_Delete();
		fp_GetAllocator() = _pOther.fp_GetAllocator();
		fp_SetInit(_pOther.mp_Data.m_pPointTo);
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::operator = (TCSharedPointer<tf_CType, tfp_COptions...> &&_pOther) -> TCSharedPointer &
		requires
		(
			NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
			&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
		)
	{
		fp_Delete();
		fp_GetAllocator() = fg_Move(_pOther.fp_GetAllocator());
		static_assert(mcp_bSupportWeak == TCSharedPointer<tf_CType, tfp_COptions...>::mcp_bSupportWeak);
		mp_Data.m_pPointTo = NPrivate::fg_ConvertSharedPointer(_pOther.mp_Data.m_pPointTo, (CInternalData *)nullptr);
		_pOther.mp_Data.m_pPointTo = nullptr;
		DIfRefCountDebugging
			(
				if (mp_Data.m_pPointTo)
					mp_Data.m_pPointTo->m_RefCount.f_Move(_pOther.mp_Data.m_DebugRef, mp_Data.m_DebugRef);
			)
		;
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::operator = (TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther) -> TCSharedPointer &
		requires
		(
			NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
			&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
		)
	{
		fp_Delete();
		fp_GetAllocator() = _pOther.fp_GetAllocator();
		static_assert(mcp_bSupportWeak == TCSharedPointer<tf_CType, tfp_COptions...>::mcp_bSupportWeak);
		fp_SetInit(NPrivate::fg_ConvertSharedPointer(_pOther.fp_Get(), (CInternalData *)nullptr));
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::operator = (TCCopy<TCSharedPointer> const &_Other) -> TCSharedPointer &
	{
		CInternalData *pNewObject = nullptr;
		if (*_Other)
			pNewObject = fg_ConstructObject<CInternalData>((*_Other).fp_GetAllocator(), *((*_Other).mp_Data.m_pPointTo));
		auto Cleanup = g_OnScopeExit / [&]
			{
				fg_DeleteObject((*_Other).fp_GetAllocator(), pNewObject);
			}
		;

		fp_Delete();
		Cleanup.f_Clear();
		fp_GetAllocator() = (*_Other).fp_GetAllocator();
		fp_SetConstruct(pNewObject);

		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_CParams>
	auto TCSharedPointer<t_CType, tp_COptions...>::operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams) -> TCSharedPointer &
	{
		static_assert(NTraits::cIsVoid<tf_CType> || NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, CAllocator>::mc_Value, "Not a valid conversion");

		auto *pNewObject = NPrivate::fg_ConvertSharedPointer
			(
				fg_TransformConstruct<CData::template TCChooseSharedPointerType>(fg_Move(_CreateParams)).template f_Create<CInternalData>(fp_GetAllocator())
				, (CInternalData *)nullptr
			)
		;
		auto Cleanup = g_OnScopeExit / [&]
			{
				fg_DeleteObject(fp_GetAllocator(), pNewObject);
			}
		;

		fp_Delete();
		Cleanup.f_Clear();
		fp_SetConstruct(pNewObject);
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CStr>
	void TCSharedPointer<t_CType, tp_COptions...>::f_Format(tf_CStr &o_Str) const
	{
		o_Str += typename tf_CStr::CFormat("0x{}") << f_Get();
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename ...tfp_CParams>
	mark_artificial constexpr inline_always_debug auto TCSharedPointer<t_CType, tp_COptions...>::operator () (tfp_CParams && ...p_Params) const
		requires requires
		{
			(*(this->f_Get()))(fg_Forward<tfp_CParams>(p_Params)...);
		}
	{
		DMibFastCheck(!f_IsEmpty());
		return (*f_Get())(fg_Forward<tfp_CParams>(p_Params)...);
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	bool TCSharedPointer<t_CType, tp_COptions...>::operator == (tf_CType *_pOther) const noexcept
	{
		return f_Get() == _pOther;
	}

	template <typename t_CType, typename ...tp_COptions>
	bool TCSharedPointer<t_CType, tp_COptions...>::operator == (CNullPtr _pOther) const noexcept
	{
		return f_Get() == _pOther;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	bool TCSharedPointer<t_CType, tp_COptions...>::operator == (TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept
	{
		return f_Get() == static_cast<t_CType *>(_pOther.f_Get());
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	bool TCSharedPointer<t_CType, tp_COptions...>::operator == (TCWeakPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept
	{
		return f_Get() == static_cast<t_CType *>(_pOther.fp_GetContained());
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	auto TCSharedPointer<t_CType, tp_COptions...>::operator <=> (tf_CType *_pOther) const noexcept
	{
		return f_Get() <=> _pOther;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::operator <=> (CNullPtr _pOther) const noexcept
	{
		return f_Get() <=> _pOther;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::operator <=> (TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept
	{
		return f_Get() <=> static_cast<t_CType *>(_pOther.f_Get());
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	auto TCSharedPointer<t_CType, tp_COptions...>::operator <=> (TCWeakPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept
	{
		return f_Get() <=> static_cast<t_CType *>(_pOther.fp_GetContained());
	}

	template <typename t_CType, typename ...tp_COptions>
	bool TCSharedPointer<t_CType, tp_COptions...>::f_IsEmpty() const
	{
		return mp_Data.m_pPointTo == nullptr;
	}

	template <typename t_CType, typename ...tp_COptions>
	inline_small TCSharedPointer<t_CType, tp_COptions...>::operator bool () const
	{
		return !f_IsEmpty();
	}

	template <typename t_CType, typename ...tp_COptions>
	umint TCSharedPointer<t_CType, tp_COptions...>::f_GetRefCount() const
	{
		return mp_Data.m_pPointTo->m_RefCount.f_Get();
	}

	template <typename tf_CType>
	auto fg_ToSharedPointer(tf_CType &&_Value)
		requires requires ()
		{
			NTraits::TCDecay<tf_CType>(fg_Forward<tf_CType>(_Value));
		}
	{
		return TCSharedPointer<NTraits::TCDecay<tf_CType>>{fg_Construct(fg_Forward<tf_CType>(_Value))};
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCWeakPointer<t_CType, tp_COptions...>::fp_GetAllocator() -> CAllocator &
	{
		return mp_Data;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCWeakPointer<t_CType, tp_COptions...>::fp_GetAllocator() const -> CAllocator const &
	{
		return mp_Data;
	}

	template <typename t_CType, typename ...tp_COptions>
	void TCWeakPointer<t_CType, tp_COptions...>::fp_Set(CInternalData *_pPtr)
	{
		fp_Delete();
		if (_pPtr)
			_pPtr->m_RefCount.f_WeakIncrease(DIfRefCountDebugging(mp_Data.m_DebugRef));
		mp_Data.m_pPointTo = _pPtr;
	}

	template <typename t_CType, typename ...tp_COptions>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer(NPrivate::CShareAsConstTag _Tag, CAllocator const &_Allocator, CInternalData *_pPointTo)
		: mp_Data(_Allocator)
	{
		fp_SetInit(_pPointTo);
	}

	template <typename t_CType, typename ...tp_COptions>
	void TCWeakPointer<t_CType, tp_COptions...>::fp_SetInit(CInternalData *_pPtr)
	{
		if (_pPtr)
			_pPtr->m_RefCount.f_WeakIncrease(DIfRefCountDebugging(mp_Data.m_DebugRef));
		mp_Data.m_pPointTo = _pPtr;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCWeakPointer<t_CType, tp_COptions...>::fp_Get() const -> CInternalData *
	{
		return mp_Data.m_pPointTo;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CDummy>
	bool TCWeakPointer<t_CType, tp_COptions...>::fp_Delete()
	{
		bool bRet = false;
		auto pPointTo = mp_Data.m_pPointTo;
		if (pPointTo)
		{
			if (pPointTo->m_RefCount.f_WeakDecrease(DIfRefCountDebugging(&mp_Data.m_DebugRef)) == 0)
			{
				NMemory::CCapturedDelete CapturedDelete = pPointTo->m_RefCount.f_WeakGetCapturedDelete();
				if (CapturedDelete.m_Size)
					fp_GetAllocator().f_Free(CapturedDelete.m_pMemory, CapturedDelete.m_Size);
				else
					fp_GetAllocator().f_FreeNoSize(CapturedDelete.m_pMemory);
				bRet = true;
			}
			mp_Data.m_pPointTo = nullptr;
		}
		return bRet;
	}

	template <typename t_CType, typename ...tp_COptions>
	bool TCWeakPointer<t_CType, tp_COptions...>::fp_Delete()
	{
		return fp_Delete<CInternalData>();
	}

	template <typename t_CType, typename ...tp_COptions>
	t_CType *TCWeakPointer<t_CType, tp_COptions...>::fp_GetContained() const
	{
		return NPrivate::fg_GetSharedPointerPointer((CInternalData *)mp_Data.m_pPointTo);
	}

	template <typename t_CType, typename ...tp_COptions>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer()
	{
		mp_Data.m_pPointTo = nullptr;
	}

	template <typename t_CType, typename ...tp_COptions>
	TCWeakPointer<t_CType, tp_COptions...>::~TCWeakPointer()
	{
		fp_Delete();
	}

	// The mutable handle survives; callers must stop modifying the object before concurrent const readers use it.
	template <typename t_CType, typename ...tp_COptions>
	auto TCWeakPointer<t_CType, tp_COptions...>::f_ShareAsConst() const -> TCWeakPointer<t_CType const, tp_COptions...>
	{
		using CConst = TCWeakPointer<t_CType const, tp_COptions...>;

		return CConst(NPrivate::CShareAsConstTag(), fp_GetAllocator(), NPrivate::fg_ConvertSharedPointer(fp_Get(), (typename CConst::CInternalData *)nullptr));
	}

	template <typename t_CType, typename ...tp_COptions>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer(TCWeakPointer const &_pOther)
		: mp_Data(_pOther.fp_GetAllocator())
	{
		fp_SetInit(_pOther.mp_Data.m_pPointTo);
	}

	template <typename t_CType, typename ...tp_COptions>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer(TCWeakPointer &&_pOther)
		: mp_Data(fg_Move(_pOther.fp_GetAllocator()))
	{
		mp_Data.m_pPointTo = _pOther.mp_Data.m_pPointTo;
		_pOther.mp_Data.m_pPointTo = nullptr;
		DIfRefCountDebugging
			(
				if (mp_Data.m_pPointTo)
					mp_Data.m_pPointTo->m_RefCount.f_WeakMove(_pOther.mp_Data.m_DebugRef, mp_Data.m_DebugRef);
			)
		;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer(TCWeakPointer<tf_CType, tfp_COptions...> const &_pOther)
		requires
		(
			NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCWeakPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
			&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
		)
		: mp_Data(_pOther.fp_GetAllocator())
	{
		fp_SetInit(NPrivate::fg_ConvertSharedPointer(_pOther.fp_Get(), (CInternalData *)nullptr));
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer(TCWeakPointer<tf_CType, tfp_COptions...> &&_pOther)
		requires
		(
			NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCWeakPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
			&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
		)
		: mp_Data(fg_Move(_pOther.fp_GetAllocator()))
	{
		mp_Data.m_pPointTo = _pOther.mp_Data.m_pPointTo;
		_pOther.mp_Data.m_pPointTo = nullptr;
		DIfRefCountDebugging
			(
				if (mp_Data.m_pPointTo)
					mp_Data.m_pPointTo->m_RefCount.f_WeakMove(_pOther.mp_Data.m_DebugRef, mp_Data.m_DebugRef);
			)
		;
	}

	template <typename t_CType, typename ...tp_COptions>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer(t_CType *_pPtr)
	{
		fp_SetInit(_pPtr);
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer(TCAttach<tf_CType> &&_Other)
	{
		mp_Data.m_pPointTo = *_Other;
		DIfRefCountDebugging(mp_Data.m_pPointTo->m_RefCount.f_WeakInitial(mp_Data.m_DebugRef););
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CParam0>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer(t_CType *_pPtr, tf_CParam0 &&_Param0)
		: mp_Data(fg_Forward<tf_CParam0>(_Param0))
	{
		fp_SetInit(_pPtr);
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCWeakPointer<t_CType, tp_COptions...>::f_UnsafeGetPointerValue() const -> CInternalData *
	{
		return mp_Data.m_pPointTo;
	}

	template <typename t_CType, typename ...tp_COptions>
	t_CType *TCWeakPointer<t_CType, tp_COptions...>::f_Unsafe_Detach()
	{
		auto *pReturn = fg_Exchange(mp_Data.m_pPointTo, nullptr);
		DIfRefCountDebugging
			(
				if (pReturn)
					pReturn->m_RefCount.f_WeakRemove(mp_Data.m_DebugRef)
			)
		;
		return pReturn;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CStr>
	void TCWeakPointer<t_CType, tp_COptions...>::f_Format(tf_CStr &o_Str) const
	{
		o_Str += typename tf_CStr::CFormat("0x{}") << fp_GetContained();
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer(TCExplicit<tf_CType> &&_Other)
	{
		fp_SetInit(*_Other);
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename tf_CAllocator>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer(TCExplicit<tf_CType> &&_Other, tf_CAllocator &&_Allocator)
		: mp_Data(fg_Forward<tf_CAllocator>(_Allocator))
	{
		fp_SetInit(*_Other);
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer(TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther)
		requires
		(
			NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
			&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
		)
		: mp_Data(_pOther.fp_GetAllocator())
	{
		static_assert(TCSharedPointer<tf_CType, tfp_COptions...>::mcp_bSupportWeak, "The source TCSharedPointer does not support TCWeakPointer, please add CSupportWeakTag");
		fp_SetInit(NPrivate::fg_ConvertSharedPointer(_pOther.fp_Get(), (CInternalData *)nullptr));
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer(TCSharedPointer<tf_CType, tfp_COptions...> &&_pOther)
		requires
		(
			NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
			&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
		)
		: mp_Data(fg_Move(_pOther.fp_GetAllocator()))
	{
		static_assert(TCSharedPointer<tf_CType, tfp_COptions...>::mcp_bSupportWeak, "The source TCSharedPointer does not support TCWeakPointer, please add CSupportWeakTag");
		fp_SetInit(NPrivate::fg_ConvertSharedPointer(_pOther.fp_Get(), (CInternalData *)nullptr));
		_pOther.f_Clear();
	}

	template <typename t_CType, typename ...tp_COptions>
	TCWeakPointer<t_CType, tp_COptions...>::TCWeakPointer(CNullPtr _pNull)
	{
		mp_Data.m_pPointTo = nullptr;
	}

	template <typename t_CType, typename ...tp_COptions>
	bool TCWeakPointer<t_CType, tp_COptions...>::f_Clear()
	{
		return fp_Delete();
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCWeakPointer<t_CType, tp_COptions...>::operator = (CNullPtr _pNull) -> TCWeakPointer &
	{
		fp_Delete();
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	auto TCWeakPointer<t_CType, tp_COptions...>::operator = (TCExplicit<tf_CType> &&_Other) -> TCWeakPointer &
	{
		fp_Set(*_Other);
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCWeakPointer<t_CType, tp_COptions...>::operator = (TCWeakPointer &&_pOther) -> TCWeakPointer &
	{
		fp_Delete();
		fp_GetAllocator() = fg_Move(_pOther.fp_GetAllocator());
		mp_Data.m_pPointTo = _pOther.mp_Data.m_pPointTo;
		_pOther.mp_Data.m_pPointTo = nullptr;
		DIfRefCountDebugging
			(
				if (mp_Data.m_pPointTo)
					mp_Data.m_pPointTo->m_RefCount.f_WeakMove(_pOther.mp_Data.m_DebugRef, mp_Data.m_DebugRef);
			)
		;
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCWeakPointer<t_CType, tp_COptions...>::operator = (TCWeakPointer const &_pOther) -> TCWeakPointer &
	{
		fp_Delete();
		fp_GetAllocator() = _pOther.fp_GetAllocator();
		fp_SetInit(_pOther.mp_Data.m_pPointTo);
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	auto TCWeakPointer<t_CType, tp_COptions...>::operator = (TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther) -> TCWeakPointer &
		requires
		(
			NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
			&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
		)
	{
		static_assert(TCSharedPointer<tf_CType, tfp_COptions...>::mcp_bSupportWeak, "The source TCSharedPointer does not support TCWeakPointer, please add CSupportWeakTag");
		fp_Delete();
		fp_GetAllocator() = _pOther.fp_GetAllocator();
		fp_SetInit(NPrivate::fg_ConvertSharedPointer(_pOther.fp_Get(), (CInternalData *)nullptr));
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	auto TCWeakPointer<t_CType, tp_COptions...>::operator = (TCSharedPointer<tf_CType, tfp_COptions...> &&_pOther) -> TCWeakPointer &
		requires
		(
			NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
			&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
		)
	{
		static_assert(TCSharedPointer<tf_CType, tfp_COptions...>::mcp_bSupportWeak, "The source TCSharedPointer does not support TCWeakPointer, please add CSupportWeakTag");
		fp_Delete();
		fp_GetAllocator() = fg_Move(_pOther.fp_GetAllocator());
		fp_SetInit(NPrivate::fg_ConvertSharedPointer(_pOther.fp_Get(), (CInternalData *)nullptr));
		_pOther.f_Clear();
		return *this;
	}

	template <typename t_CType, typename ...tp_COptions>
	TCSharedPointer<t_CType, CSupportWeakTag, tp_COptions...> TCWeakPointer<t_CType, tp_COptions...>::f_Lock() const
	{
		TCSharedPointer<t_CType, CSupportWeakTag, tp_COptions...> pReturn(fp_GetAllocator());

		auto pData = mp_Data.m_pPointTo;
		if (!pData)
			return pReturn;

		if (!pData->m_RefCount.f_IncreaseWhileValid(DIfRefCountDebugging(pReturn.mp_Data.m_DebugRef)))
			return pReturn;

		pReturn.fp_SetCounted(pData);

		return pReturn;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	bool TCWeakPointer<t_CType, tp_COptions...>::operator == (tf_CType *_pOther) const noexcept
	{
		return fp_GetContained() == _pOther;
	}

	template <typename t_CType, typename ...tp_COptions>
	bool TCWeakPointer<t_CType, tp_COptions...>::operator == (CNullPtr _pOther) const noexcept
	{
		return fp_GetContained() == _pOther;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	bool TCWeakPointer<t_CType, tp_COptions...>::operator == (TCWeakPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept
	{
		return fp_GetContained() == _pOther.fp_GetContained();
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	bool TCWeakPointer<t_CType, tp_COptions...>::operator == (TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept
	{
		return fp_GetContained() == _pOther.f_Get();
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType>
	auto TCWeakPointer<t_CType, tp_COptions...>::operator <=> (tf_CType *_pOther) const noexcept
	{
		return fp_GetContained() <=> _pOther;
	}

	template <typename t_CType, typename ...tp_COptions>
	auto TCWeakPointer<t_CType, tp_COptions...>::operator <=> (CNullPtr _pOther) const noexcept
	{
		return fp_GetContained() <=> _pOther;
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	auto TCWeakPointer<t_CType, tp_COptions...>::operator <=> (TCWeakPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept
	{
		return fp_GetContained() <=> _pOther.fp_GetContained();
	}

	template <typename t_CType, typename ...tp_COptions>
	template <typename tf_CType, typename ...tfp_COptions>
	auto TCWeakPointer<t_CType, tp_COptions...>::operator <=> (TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept
	{
		return fp_GetContained() <=> _pOther.f_Get();
	}

	template <typename t_CType, typename ...tp_COptions>
	bool TCWeakPointer<t_CType, tp_COptions...>::f_IsEmpty() const
	{
		return mp_Data.m_pPointTo == nullptr;
	}

	template <typename t_CType, typename ...tp_COptions>
	inline_small TCWeakPointer<t_CType, tp_COptions...>::operator bool () const
	{
		return !f_IsEmpty();
	}
}
