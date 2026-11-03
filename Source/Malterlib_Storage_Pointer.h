// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#ifndef DMibConfig_RefCountDebugging
#	define DMibConfig_RefCountDebugging 0
#endif

#ifndef DMibConfig_RefCountLeakDebugging
#	define DMibConfig_RefCountLeakDebugging 0
#endif

#if DMibConfig_RefCountDebugging
#	define DIfRefCountDebugging(...) __VA_ARGS__
#	define DIfNotRefCountDebugging(...)
#else
#	define DIfRefCountDebugging(...)
#	define DIfNotRefCountDebugging(...) __VA_ARGS__
#endif

#include <Mib/Core/Core>
#include <Mib/Function/BindMemberFunction>
namespace NMib::NStorage
{
	/////////////////////////////////////////////////////////////////////////
	// Auto clear ptr
	struct CAutoClearPtr
	{
		CAutoClearPtr();
		~CAutoClearPtr();

		DMibListLinkDS_Link(CAutoClearPtr, m_Link);
	};

	struct CAutoClearPtrDefaultDummy : public CAutoClearPtr
	{
		void *m_pPointTo;
	};

	struct CAutoClearPtrMember
	{
		CAutoClearPtrMember();
		~CAutoClearPtrMember();

		void f_Clear();

		DMibListLinkDS_List(CAutoClearPtr, m_Link) m_Linked;

	private:
		CAutoClearPtrMember(CAutoClearPtrMember const &_Other);
		CAutoClearPtrMember &operator = (CAutoClearPtrMember const &_Other);
	};

	struct CAutoClearPtrMemberDebug : public CAutoClearPtrMember
	{
		CAutoClearPtrMemberDebug();
		~CAutoClearPtrMemberDebug();

		void f_Clear();

	private:
		CAutoClearPtrMemberDebug(CAutoClearPtrMemberDebug const &_Other);
		CAutoClearPtrMemberDebug &operator = (CAutoClearPtrMemberDebug const &_Other);
	};

	template <typename t_CType>
	struct TCAutoClearPtrMemberDebug
	{
		DMibListLinkDS_List(CAutoClearPtr, m_Link) m_Linked;
		~TCAutoClearPtrMemberDebug();

		void f_Clear();
	};

	template <typename t_CType>
	struct TCAutoClearPtr : public CAutoClearPtr
	{
		TCAutoClearPtr();

		// Assign
		TCAutoClearPtr(t_CType *_pPtr);
		TCAutoClearPtr(TCAutoClearPtr const &_pOther);
		TCAutoClearPtr &operator = (t_CType *_pPtr);
		TCAutoClearPtr &operator = (TCAutoClearPtr const &_pOther);

		// Access
		operator t_CType * () const;
		t_CType *operator -> () const;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
		;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
		;

		mark_nodebug t_CType &operator * () const;

		template <typename tf_CType2>
		bool operator == (tf_CType2 const &_Other) const noexcept;
		template <typename tf_CType2>
		bool operator == (TCAutoClearPtr<tf_CType2> const &_pOther) const noexcept;

	private:
		t_CType *mp_pPointTo;
		void fp_RemoveOld();
	};

	template <typename t_CType>
	struct TCAutoClearPtrDebug : public CAutoClearPtr
	{
		TCAutoClearPtrDebug();

		// Assign
		TCAutoClearPtrDebug(t_CType *_pPtr);
		TCAutoClearPtrDebug(TCAutoClearPtrDebug const &_pOther);
		TCAutoClearPtrDebug &operator = (t_CType *_pPtr);
		TCAutoClearPtrDebug &operator = (TCAutoClearPtrDebug const &_pOther);

		// Access
		operator t_CType * () const;
		t_CType *operator -> () const;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
		;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
		;

		mark_nodebug t_CType &operator * () const;

		template <typename tf_CType2>
		bool operator == (tf_CType2 const &_Other) const noexcept;
		template <typename tf_CType2>
		bool operator == (TCAutoClearPtrDebug<tf_CType2> const &_pOther) const noexcept;

	private:
		t_CType *mp_pPointTo;
		void fp_RemoveOld();
	};

#define DMibAutoClearPtrDeclare mutable NMib::NStorage::CAutoClearPtrMember m_AutoClearPtrMember
#define DMibAutoClearPtrDeclareDebug(d_Type) mutable NMib::NStorage::TCAutoClearPtrMemberDebug<d_Type> m_AutoClearPtrMemberDebug
#ifndef DMibPNoShortCuts
#	define DAutoClearPtrDeclare DMibAutoClearPtrDeclare
#endif

#if defined DMibContractsConfigure_CheckEnabled
#	define DMibDebugPointerDeclare mutable NMib::NStorage::CAutoClearPtrMemberDebug m_DebugPointerMember
	template <typename t_CType>
	struct TCDebugPointer : public CAutoClearPtr
	{
		TCDebugPointer();

		// Assign
		TCDebugPointer(t_CType *_pPtr);
		TCDebugPointer(TCDebugPointer const &_Other);
		TCDebugPointer &operator = (t_CType *_pPtr);
		TCDebugPointer &operator = (TCDebugPointer const &_Other);

		// Access
		operator t_CType * () const;
		t_CType *operator -> () const;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
		;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
		;

		mark_nodebug t_CType &operator * () const;

		template <typename tf_CType2>
		bool operator == (tf_CType2 const &_Other) const noexcept;
		template <typename tf_CType2>
		bool operator == (TCDebugPointer<tf_CType2> const &_Other) const noexcept;

	private:
		t_CType *mp_pPointTo;

		void fp_RemoveOld();
	};

#else
#	define DMibDebugPointerDeclare
	template <typename t_CType>
	struct TCDebugPointer
	{
		TCDebugPointer();

		// Assign
		TCDebugPointer(t_CType *_pPtr);
		TCDebugPointer(TCDebugPointer const &_pOther);
		TCDebugPointer &operator = (t_CType *_pPtr);
		TCDebugPointer &operator = (TCDebugPointer const &_pOther);

		// Access
		operator t_CType * () const;
		t_CType *operator -> () const;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
		;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
		;

		mark_nodebug t_CType &operator * () const;

		template <typename tf_CType2>
		bool operator == (tf_CType2 const &_Other) const noexcept;
		template <typename tf_CType2>
		bool operator == (TCDebugPointer<tf_CType2> const &_pOther) const noexcept;

	private:
		t_CType *mp_pPointTo;
	};
#endif

#ifndef DMibPNoShortCuts
#	define DDebugPointerDeclare DMibDebugPointerDeclare
#endif

	template <typename t_CType>
	struct TCPointer
	{
		TCPointer();

		// Assign
		TCPointer(t_CType *_pPtr);
		template <typename tf_CType>
		TCPointer(TCExplicit<tf_CType> &&_Other);
		TCPointer(TCPointer const &_pOther);
		TCPointer &operator = (t_CType *_pPtr);
		TCPointer &operator = (TCPointer const &_pOther);
		template <typename tf_CType>
		TCPointer &operator = (TCExplicit<tf_CType> &&_Other);

		void f_Clear();

		// Access
		t_CType *f_Get() const;
		operator t_CType * () const;
		t_CType *operator -> () const;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
		;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
		;

		mark_nodebug t_CType &operator * () const;

		template <typename tf_CType2>
		bool operator == (tf_CType2 const &_Other) const noexcept;
		template <typename tf_CType2>
		bool operator == (TCPointer<tf_CType2> const &_pOther) const noexcept;

	private:
		t_CType *mp_pPointTo;
	};

	/////////////////////////////////////////////////////////////////////////
	// RefCount pointer

#if DMibConfig_RefCountDebugging
	struct CRefCountDebugReference
	{
		CRefCountDebugReference();
		~CRefCountDebugReference();

		CRefCountDebugReference(CRefCountDebugReference const &_Other) = delete;
		CRefCountDebugReference &operator = (CRefCountDebugReference const &_Other) = delete;

		CRefCountDebugReference(CRefCountDebugReference &&_Other);
		CRefCountDebugReference &operator = (CRefCountDebugReference &&_Other);

		NException::CCallstack *m_pCallstack = nullptr;
	};
#endif

	namespace NPrivate
	{
		template <typename t_CType>
		concept cHasIntrusiveRefCountHelper = requires (t_CType const *_pValue)
			{
				_pValue->m_RefCount.f_Get();
			}
		;
	}

	template <typename t_CType>
	struct TCHasIntrusiveRefCountOverride
	{
		static constexpr bool mc_bValue = NPrivate::cHasIntrusiveRefCountHelper<t_CType>;
	};

	template <typename t_CType>
	concept cHasIntrusiveRefCount = TCHasIntrusiveRefCountOverride<t_CType>::mc_bValue;

#define DMibDefineSharedPointerType(d_Type, d_HasRefCount, d_VirtualDestructor) \
	template <> \
	struct NMib::NStorage::TCHasIntrusiveRefCountOverride<d_Type> \
	{ \
		constexpr static bool mc_bValue = d_HasRefCount; \
	}; \
	template <> \
	struct NMib::NTraits::TCHasVirtualDestructorOverride<d_Type> \
	{ \
		constexpr static bool mc_Value = d_VirtualDestructor; \
	};

	struct CSupportWeakTag
	{
	};

	namespace NPrivate
	{
		template <typename t_CType, CSharedPointerOptionUnderlying t_Options, bool t_bHasRefCount = cHasIntrusiveRefCount<NTraits::TCRemoveQualifiers<t_CType>>>
		struct TCChooseSharedPointerTypeImp
		{
		};

		template <typename t_CType, CSharedPointerOptionUnderlying t_Options>
		struct TCChooseSharedPointerTypeImp<t_CType, t_Options, true>
		{
			using CType = t_CType;
		};

		template <CSharedPointerOptionUnderlying t_Options, bool t_bHasRefCount>
		struct TCChooseSharedPointerTypeImp<void, t_Options, t_bHasRefCount>
		{
			using CType = void;
		};

		template <CSharedPointerOptionUnderlying t_Options>
		struct TCChooseSharedPointerTypeImp<void, t_Options, false>
		{
			using CType = void;
		};

		template <typename tf_CType>
		tf_CType *fg_GetSharedPointerPointer(tf_CType *_pIn);

		template <typename tf_CToType, typename tf_CType>
		tf_CType *fg_ConvertSharedPointer(tf_CType *_pIn, tf_CToType *_pDummy);

		template <typename t_CType, bool t_bVirtualDestructor, CSharedPointerOptionUnderlying t_Options>
		struct TCSharedPointerCounter;

		template <typename t_CType, CSharedPointerOptionUnderlying t_Options>
		struct TCSharedPointerCounter<t_CType, true, t_Options>;

		template <typename tf_CType, bool tf_bVirtualDestructor, CSharedPointerOptionUnderlying tf_Options>
		tf_CType *fg_GetSharedPointerPointer(TCSharedPointerCounter<tf_CType, tf_bVirtualDestructor, tf_Options> *_pIn);

		template
		<
			typename tf_CToType
			, typename tf_CType
			, bool tf_bToVirtualDestructor
			, bool tf_bVirtualDestructor
			, CSharedPointerOptionUnderlying tf_ToOptions
			, CSharedPointerOptionUnderlying tf_Options
		>
		auto fg_ConvertSharedPointer
			(
				TCSharedPointerCounter<tf_CType, tf_bVirtualDestructor, tf_Options> *_pIn
				, TCSharedPointerCounter<tf_CToType, tf_bToVirtualDestructor, tf_ToOptions> *_pDummy
			)
			-> TCSharedPointerCounter<tf_CToType, tf_bToVirtualDestructor, tf_ToOptions> *
		;

		template <typename ...tp_CParams>
		struct TCParseSharedPointerOptions;

		template <>
		struct TCParseSharedPointerOptions<>
		{
			using CFunctions = NMeta::TCTypeList<>;
			using CAllocator = NMemory::CDefaultAllocator;

			static constexpr bool mc_bSupportWeak = false;
		};

		template <typename t_CFirst, typename ...tp_CParams>
		struct TCParseSharedPointerOptions<t_CFirst, tp_CParams...>
		{
			using CParent = TCParseSharedPointerOptions<tp_CParams...>;
			using CAllocator = t_CFirst;

			static constexpr bool mc_bSupportWeak = CParent::mc_bSupportWeak;
		};

		template <typename ...tp_CParams>
		struct TCParseSharedPointerOptions<CSupportWeakTag, tp_CParams...>
		{
			using CParent = TCParseSharedPointerOptions<tp_CParams...>;
			using CAllocator = typename CParent::CAllocator;

			static constexpr bool mc_bSupportWeak = true;
		};

		template <typename t_CType, typename t_CAllocator, CSharedPointerOptionUnderlying t_Options>
		struct TCSharedPointerData : public t_CAllocator
		{
			template <typename t_CType2>
			struct TCChooseSharedPointerType : public TCChooseSharedPointerTypeImp<t_CType2, t_Options>
			{
			};

			using CInternalData = typename TCChooseSharedPointerTypeImp<t_CType, t_Options>::CType;

			CInternalData *m_pPointTo;
			DIfRefCountDebugging(mutable NStorage::CRefCountDebugReference m_DebugRef);

			TCSharedPointerData();
			TCSharedPointerData(t_CAllocator const &_Other);
			TCSharedPointerData(t_CAllocator &&_Other);
			template <typename tf_CParam0>
			TCSharedPointerData(tf_CParam0 &&_Other);

		private:
			TCSharedPointerData(TCSharedPointerData const &_Other);
			TCSharedPointerData(TCSharedPointerData &&_Other);
		};
	}

	template <typename tf_CObjectType>
	NMemory::CCapturedDelete fg_DeleteWeakObjectGetCapturedDelete(tf_CObjectType *_pObject);

	template <typename tf_CObjectType, typename tf_CAllocator>
	void fg_DeleteWeakObject(tf_CAllocator &&_Allocator, tf_CObjectType *_pObject);

	namespace NPrivate
	{
		struct CShareAsConstTag
		{
		};

		// Adding const requires explicit sharing because the source retains a mutable handle.
		template <typename t_CTo, typename t_CFrom>
		struct TCIsConstAddingConversion
		{
			static constexpr bool mc_Value = NTraits::cIsConst<t_CTo> && !NTraits::cIsConst<t_CFrom>;
		};
	}

	template <typename t_CType, typename ...tp_COptions>
	struct TCSharedPointer
	{
	private:
		// Declared before the public section, which uses them.
		using COptions = NPrivate::TCParseSharedPointerOptions<tp_COptions...>;
		using CAllocator = typename COptions::CAllocator;

	public:
		TCSharedPointer<t_CType const, tp_COptions...> f_ShareAsConst() const;

		using CWeakPointer = TCWeakPointer<t_CType, CAllocator>;

		TCSharedPointer();
		~TCSharedPointer();

		void f_ForceDelete();

		TCSharedPointer(TCCopy<TCSharedPointer> const &_Other);
		TCSharedPointer(TCSharedPointer const &_pOther);
		TCSharedPointer(TCSharedPointer &&_pOther);

		template <typename tf_CType, typename ...tfp_COptions>
		TCSharedPointer(TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther)
			requires
			(
				NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
				&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
			)
		;

		template <typename tf_CType, typename ...tfp_COptions>
		TCSharedPointer(TCSharedPointer<tf_CType, tfp_COptions...> &&_pOther)
			requires
			(
				NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
				&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
			)
		;

		template <typename tf_CType, typename ...tfp_CParams>
		TCSharedPointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams);
		template <typename tf_CType, typename ...tfp_CParams, typename tf_CAllocator>
		TCSharedPointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams, tf_CAllocator &&_Allocator);

		explicit TCSharedPointer(t_CType *_pPtr);
		template <typename tf_CParam0>
		explicit TCSharedPointer(t_CType *_pPtr, tf_CParam0 &&_Param0);

		template <typename tf_CType>
		TCSharedPointer(TCExplicit<tf_CType> &&_Other);
		template <typename tf_CType, typename tf_CAllocator>
		TCSharedPointer(TCExplicit<tf_CType> &&_Other, tf_CAllocator &&_Allocator);

		template <typename tf_CType>
		TCSharedPointer(TCAttach<tf_CType> &&_Other);
		template <typename tf_CType, typename tf_CAllocator>
		TCSharedPointer(TCAttach<tf_CType> &&_Other, tf_CAllocator &&_Allocator);

		TCSharedPointer(CNullPtr _pNull);

		t_CType *f_Detach();
		bool f_Clear();

		CWeakPointer f_Weak() const;

		t_CType *f_Get() const;
		t_CType *operator -> () const;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
		;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
		;

		mark_nodebug t_CType &operator * () const;

		TCSharedPointer &operator = (CNullPtr _pNull);
		template <typename tf_CType>
		TCSharedPointer &operator = (TCExplicit<tf_CType> &&_Other);
		template <typename tf_CType>
		TCSharedPointer &operator = (TCAttach<tf_CType> &&_Other);
		TCSharedPointer &operator = (TCSharedPointer &&_pOther);
		TCSharedPointer &operator = (TCSharedPointer const &_pOther);

		template <typename tf_CType, typename ...tfp_COptions>
		TCSharedPointer &operator = (TCSharedPointer<tf_CType, tfp_COptions...> &&_pOther)
			requires
			(
				NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
				&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
			)
		;

		template <typename tf_CType, typename ...tfp_COptions>
		TCSharedPointer &operator = (TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther)
			requires
			(
				NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
				&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
			)
		;

		TCSharedPointer &operator = (TCCopy<TCSharedPointer> const &_Other);
		template <typename tf_CType, typename ...tfp_CParams>
		TCSharedPointer &operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams);

		template <typename tf_CStr>
		void f_Format(tf_CStr &o_Str) const;

		template <typename ...tfp_CParams>
		mark_artificial constexpr inline_always_debug auto operator () (tfp_CParams && ...p_Params) const
			requires requires
			{
				(*(this->f_Get()))(fg_Forward<tfp_CParams>(p_Params)...);
			}
		;

		template <typename tf_CType>
		bool operator == (tf_CType *_pOther) const noexcept;
		bool operator == (CNullPtr _pOther) const noexcept;
		template <typename tf_CType, typename ...tfp_COptions>
		bool operator == (TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept;
		template <typename tf_CType, typename ...tfp_COptions>
		bool operator == (TCWeakPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept;

		template <typename tf_CType>
		auto operator <=> (tf_CType *_pOther) const noexcept;
		auto operator <=> (CNullPtr _pOther) const noexcept;
		template <typename tf_CType, typename ...tfp_COptions>
		auto operator <=> (TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept;
		template <typename tf_CType, typename ...tfp_COptions>
		auto operator <=> (TCWeakPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept;

		bool f_IsEmpty() const;
		inline_small explicit operator bool () const;
		umint f_GetRefCount() const;

	private:
		template <typename t_CType2, typename ...tp_COptions2>
		friend struct TCSharedPointer;
		template <typename t_CType2, typename ...tp_COptions2>
		friend struct TCWeakPointer;

		static constexpr bool mcp_bSupportWeak = COptions::mc_bSupportWeak;

		using CData = NPrivate::TCSharedPointerData<t_CType, CAllocator, mcp_bSupportWeak ? ESharedPointerOption_SupportWeakPointer : ESharedPointerOption_None>;
		using CInternalData = typename CData::CInternalData;

		CData mp_Data;

		CAllocator &fp_GetAllocator();
		CAllocator const &fp_GetAllocator() const;

		void fp_Set(CInternalData *_pPtr);

		TCSharedPointer(NPrivate::CShareAsConstTag _Tag, CAllocator const &_Allocator, CInternalData *_pPointTo);

		void fp_SetAttach(CInternalData *_pPtr);
		void fp_SetInit(CInternalData *_pPtr);
		void fp_SetConstruct(CInternalData *_pPtr);
		void fp_SetCounted(CInternalData *_pPtr);

		CInternalData *fp_Get() const;

		bool fp_Delete();

		TCSharedPointer(CAllocator const &_Allocator);
	};

	template <typename tf_CType>
	auto fg_ToSharedPointer(tf_CType &&_Value)
		requires requires ()
		{
			NTraits::TCDecay<tf_CType>(fg_Forward<tf_CType>(_Value));
		}
	;

	template <typename t_CType, typename ...tp_COptions>
	using TCSharedPointerSupportWeak = TCSharedPointer<t_CType, CSupportWeakTag, tp_COptions...>;

	template <typename t_CType, typename ...tp_COptions>
	struct TCWeakPointer
	{
	private:
		// Declared before the public section, which uses them.
		using CAllocator = typename NPrivate::TCParseSharedPointerOptions<tp_COptions...>::CAllocator;
		using CData = NPrivate::TCSharedPointerData<t_CType, CAllocator, ESharedPointerOption_SupportWeakPointer>;
		using CInternalData = typename CData::CInternalData;

	public:
		TCWeakPointer();
		~TCWeakPointer();

		TCWeakPointer<t_CType const, tp_COptions...> f_ShareAsConst() const;

		TCWeakPointer(TCWeakPointer const &_pOther);
		TCWeakPointer(TCWeakPointer &&_pOther);

		template <typename tf_CType, typename ...tfp_COptions>
		TCWeakPointer(TCWeakPointer<tf_CType, tfp_COptions...> const &_pOther)
			requires
			(
				NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCWeakPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
				&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
			)
		;

		template <typename tf_CType, typename ...tfp_COptions>
		TCWeakPointer(TCWeakPointer<tf_CType, tfp_COptions...> &&_pOther)
			requires
			(
				NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCWeakPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
				&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
			)
		;

		explicit TCWeakPointer(t_CType *_pPtr);
		template <typename tf_CType>
		explicit TCWeakPointer(TCAttach<tf_CType> &&_Other);
		template <typename tf_CParam0>
		explicit TCWeakPointer(t_CType *_pPtr, tf_CParam0 &&_Param0);

		CInternalData *f_UnsafeGetPointerValue() const;
		t_CType *f_Unsafe_Detach();

		template <typename tf_CStr>
		void f_Format(tf_CStr &o_Str) const;

		template <typename tf_CType>
		TCWeakPointer(TCExplicit<tf_CType> &&_Other);
		template <typename tf_CType, typename tf_CAllocator>
		TCWeakPointer(TCExplicit<tf_CType> &&_Other, tf_CAllocator &&_Allocator);

		template <typename tf_CType, typename ...tfp_COptions>
		TCWeakPointer(TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther)
			requires
			(
				NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
				&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
			)
		;

		template <typename tf_CType, typename ...tfp_COptions>
		TCWeakPointer(TCSharedPointer<tf_CType, tfp_COptions...> &&_pOther)
			requires
			(
				NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
				&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
			)
		;

		TCWeakPointer(CNullPtr _pNull);

		bool f_Clear();

		TCWeakPointer &operator = (CNullPtr _pNull);
		template <typename tf_CType>
		TCWeakPointer &operator = (TCExplicit<tf_CType> &&_Other);
		TCWeakPointer &operator = (TCWeakPointer &&_pOther);
		TCWeakPointer &operator = (TCWeakPointer const &_pOther);

		template <typename tf_CType, typename ...tfp_COptions>
		TCWeakPointer &operator = (TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther)
			requires
			(
				NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
				&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
			)
		;

		template <typename tf_CType, typename ...tfp_COptions>
		TCWeakPointer &operator = (TCSharedPointer<tf_CType, tfp_COptions...> &&_pOther)
			requires
			(
				NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
				&& !NPrivate::TCIsConstAddingConversion<t_CType, tf_CType>::mc_Value
			)
		;

		TCSharedPointer<t_CType, CSupportWeakTag, tp_COptions...> f_Lock() const;

		template <typename tf_CType>
		bool operator == (tf_CType *_pOther) const noexcept;
		bool operator == (CNullPtr _pOther) const noexcept;
		template <typename tf_CType, typename ...tfp_COptions>
		bool operator == (TCWeakPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept;
		template <typename tf_CType, typename ...tfp_COptions>
		bool operator == (TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept;

		template <typename tf_CType>
		auto operator <=> (tf_CType *_pOther) const noexcept;
		auto operator <=> (CNullPtr _pOther) const noexcept;
		template <typename tf_CType, typename ...tfp_COptions>
		auto operator <=> (TCWeakPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept;
		template <typename tf_CType, typename ...tfp_COptions>
		auto operator <=> (TCSharedPointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept;

		bool f_IsEmpty() const;
		inline_small explicit operator bool () const;

	private:
		template <typename t_CType2, typename ...tp_COptions2>
		friend struct TCSharedPointer;
		template <typename t_CType2, typename ...tp_COptions2>
		friend struct TCWeakPointer;

		CData mp_Data;

		CAllocator &fp_GetAllocator();
		CAllocator const &fp_GetAllocator() const;

		void fp_Set(CInternalData *_pPtr);

		TCWeakPointer(NPrivate::CShareAsConstTag _Tag, CAllocator const &_Allocator, CInternalData *_pPointTo);

		void fp_SetInit(CInternalData *_pPtr);

		CInternalData *fp_Get() const;

		template <typename tf_CDummy>
		bool fp_Delete();
		bool fp_Delete();

		t_CType *fp_GetContained() const;
	};
}

#include "Malterlib_Storage_Pointer.hpp"

#ifndef DMibPNoShortCuts
using namespace NMib::NStorage;
#endif
