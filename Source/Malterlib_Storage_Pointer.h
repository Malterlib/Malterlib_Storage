// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#ifndef DMibConfig_RefcountDebugging
#define DMibConfig_RefcountDebugging 0
#endif

#include <Mib/Core/Core>
#include <Mib/Function/BindMemberFunction>
namespace NMib::NStorage
{
	/////////////////////////////////////////////////////////////////////////
	// Auto clear ptr
	class CAutoClearPtr
	{
	public:
		CAutoClearPtr();
		~CAutoClearPtr();

		DMibListLinkDS_Link(CAutoClearPtr, m_Link);
	};

	class CAutoClearPtrDefaultDummy : public CAutoClearPtr
	{
	public:
		void *m_pPointTo;
	};


	class CAutoClearPtrMember
	{
	private:
		CAutoClearPtrMember(const CAutoClearPtrMember&_Other)
		{
		}
		CAutoClearPtrMember &operator = (const CAutoClearPtrMember&_Other)
		{
			return *this;
		}
	public:
		CAutoClearPtrMember();
		~CAutoClearPtrMember();

		void f_Clear();

		DMibListLinkDS_List(CAutoClearPtr, m_Link) m_Linked;
	};

	class CAutoClearPtrMemberDebug : public CAutoClearPtrMember
	{
	private:
		CAutoClearPtrMemberDebug(const CAutoClearPtrMemberDebug&_Other)
		{
		}
		CAutoClearPtrMemberDebug &operator = (const CAutoClearPtrMemberDebug&_Other)
		{
			return *this;
		}
	public:
		CAutoClearPtrMemberDebug();
		~CAutoClearPtrMemberDebug();

		void f_Clear();
	};


	template <typename t_CType>
	class TCAutoClearPtrMemberDebug
	{
	public:
		DMibListLinkDS_List(CAutoClearPtr, m_Link) m_Linked;
		~TCAutoClearPtrMemberDebug()
		{
			f_Clear();
		}
		void f_Clear()
		{
			CAutoClearPtr *pPtr = m_Linked.f_Pop();
			while (pPtr)
			{
				((CAutoClearPtrDefaultDummy *)pPtr)->m_pPointTo = nullptr;
				pPtr = m_Linked.f_Pop();
			}
		}
	};

	template <typename t_CType>
	class TCAutoClearPtr : public CAutoClearPtr
	{
		t_CType *m_pPointTo;
		void fp_RemoveOld()
		{
			if (m_pPointTo)
				m_pPointTo->m_AutoClearPtrMember.m_Linked.f_Remove(this);
		}
	public:
		TCAutoClearPtr()
			: m_pPointTo(nullptr)
		{
		}

		// Assign
		TCAutoClearPtr(t_CType *_pPtr)
		{

			if (_pPtr)
				_pPtr->m_AutoClearPtrMember.m_Linked.f_Insert(this);
			m_pPointTo = _pPtr;
		}
		TCAutoClearPtr(const TCAutoClearPtr &_Other)
		{

			if (_Other)
				_Other->m_AutoClearPtrMember.m_Linked.f_Insert(this);
			m_pPointTo = _Other.m_pPointTo;
		}

		TCAutoClearPtr & operator = (t_CType *_pPtr)
		{
			fp_RemoveOld();
			if (_pPtr)
				_pPtr->m_AutoClearPtrMember.m_Linked.f_Insert(this);

			m_pPointTo = _pPtr;
			return *this;
		}

		TCAutoClearPtr & operator = (const TCAutoClearPtr &_Other)
		{
			fp_RemoveOld();
			if (_Other)
				_Other->m_AutoClearPtrMember.m_Linked.f_Insert(this);

			m_pPointTo = _Other.m_pPointTo;
			return *this;
		}

		// Access
		operator t_CType *() const
		{
			return m_pPointTo;
		}

		t_CType *operator ->() const
		{
			return m_pPointTo;
		}

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
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, m_pPointTo);
		}

		template <typename t_CMemberPtr>
		mark_artificial inline_always typename TCEnableIf
			<
				NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
				, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
			>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return m_pPointTo->*_MemberPtr;
		}

		t_CType &operator *() const
		{
			return *m_pPointTo;
		}

		template <typename t_CType2>
		bool operator == (const t_CType2 &_Other) const
		{
			return operator t_CType *() == (t_CType *)_Other;
		}

		template <typename t_CType2>
		bool operator == (const TCAutoClearPtr<t_CType2> &_Other) const
		{
			return operator t_CType *() == _Other.operator t_CType2 *();
		}
	};

	template <typename t_CType>
	class TCAutoClearPtrDebug : public CAutoClearPtr
	{
		t_CType *m_pPointTo;
		void fp_RemoveOld()
		{
			if (m_pPointTo)
				m_pPointTo->m_AutoClearPtrMemberDebug.m_Linked.f_Remove(this);
		}
	public:
		TCAutoClearPtrDebug()
			: m_pPointTo(nullptr)
		{
		}

		// Assign
		TCAutoClearPtrDebug(t_CType *_pPtr)
		{
			if (_pPtr)
				_pPtr->m_AutoClearPtrMemberDebug.m_Linked.f_Insert(this);
			m_pPointTo = _pPtr;
		}
		TCAutoClearPtrDebug(const TCAutoClearPtrDebug &_Other)
		{

			if (_Other)
				_Other->m_AutoClearPtrMemberDebug.m_Linked.f_Insert(this);
			m_pPointTo = _Other.m_pPointTo;
		}

		TCAutoClearPtrDebug & operator = (t_CType *_pPtr)
		{
			fp_RemoveOld();

			if (_pPtr)
				_pPtr->m_AutoClearPtrMemberDebug.m_Linked.f_Insert(this);

			m_pPointTo = _pPtr;
			return *this;
		}
		TCAutoClearPtrDebug & operator = (const TCAutoClearPtrDebug &_Other)
		{
			fp_RemoveOld();

			if (_Other)
				_Other->m_AutoClearPtrMemberDebug.m_Linked.f_Insert(this);

			m_pPointTo = _Other.m_pPointTo;
			return *this;
		}

		// Access
		operator t_CType *() const
		{
			return m_pPointTo;
		}

		t_CType *operator ->() const
		{
			return m_pPointTo;
		}

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
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, m_pPointTo);
		}

		template <typename t_CMemberPtr>
		mark_artificial inline_always typename TCEnableIf
			<
				NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
				, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
			>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return m_pPointTo->*_MemberPtr;
		}

		t_CType &operator *() const
		{
			return *m_pPointTo;
		}

		template <typename t_CType2>
		bool operator == (const t_CType2 &_Other) const
		{
			return operator t_CType *() == (t_CType *)_Other;
		}

		template <typename t_CType2>
		bool operator == (const TCAutoClearPtrDebug<t_CType2> &_Other) const
		{
			return operator t_CType *() == _Other.operator t_CType2 *();
		}
	};

#define DMibAutoClearPtrDeclare mutable NMib::NStorage::CAutoClearPtrMember m_AutoClearPtrMember
#define DMibAutoClearPtrDeclareDebug(_Type) mutable NMib::NStorage::TCAutoClearPtrMemberDebug<_Type> m_AutoClearPtrMemberDebug
#ifndef DMibPNoShortCuts
#define DAutoClearPtrDeclare DMibAutoClearPtrDeclare
#endif


#if defined DMibContractsConfigure_CheckEnabled
	#define DMibDebugPointerDeclare mutable NMib::NStorage::CAutoClearPtrMemberDebug m_DebugPointerMember
	template <typename t_CType>
	class TCDebugPointer : public CAutoClearPtr
	{
		t_CType *m_pPointTo;

		void fp_RemoveOld()
		{
			if (m_pPointTo)
				m_pPointTo->m_DebugPointerMember.m_Linked.f_Remove(this);
		}
	public:
		TCDebugPointer()
			: m_pPointTo(nullptr)
		{
		}

		// Assign
		TCDebugPointer(t_CType *_pPtr)
		{
			if (_pPtr)
				_pPtr->m_DebugPointerMember.m_Linked.f_Insert(this);
			m_pPointTo = _pPtr;
		}
		TCDebugPointer(const TCDebugPointer &_Other)
		{

			if (_Other)
				_Other->m_DebugPointerMember.m_Linked.f_Insert(this);
			m_pPointTo = _Other.m_pPointTo;
		}

		TCDebugPointer & operator = (t_CType *_pPtr)
		{
			fp_RemoveOld();
			if (_pPtr)
				_pPtr->m_DebugPointerMember.m_Linked.f_Insert(this);

			m_pPointTo = _pPtr;
			return *this;
		}

		TCDebugPointer & operator = (const TCDebugPointer &_Other)
		{
			fp_RemoveOld();
			if (_Other)
				_Other->m_DebugPointerMember.m_Linked.f_Insert(this);

			m_pPointTo = _Other.m_pPointTo;
			return *this;
		}

		// Access
		operator t_CType *() const
		{
			return m_pPointTo;
		}

		t_CType *operator ->() const
		{
			return m_pPointTo;
		}

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
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, m_pPointTo);
		}

		template <typename t_CMemberPtr>
		mark_artificial inline_always typename TCEnableIf
			<
				NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
				, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
			>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return m_pPointTo->*_MemberPtr;
		}

		t_CType &operator *() const
		{
			return *m_pPointTo;
		}

		template <typename t_CType2>
		bool operator == (const t_CType2 &_Other) const
		{
			return operator t_CType *() == (t_CType *)_Other;
		}

		template <typename t_CType2>
		bool operator == (const TCDebugPointer<t_CType2> &_Other) const
		{
			return operator t_CType *() == _Other.operator t_CType2 *();
		}
	};

#else
#define DMibDebugPointerDeclare 
	template <typename t_CType>
	class TCDebugPointer
	{
		t_CType *m_pPointTo;
	public:
		TCDebugPointer()
			: m_pPointTo(nullptr)
		{
		}

		// Assign
		TCDebugPointer(t_CType *_pPtr)
		{
			m_pPointTo = _pPtr;
		}
		TCDebugPointer(const TCDebugPointer &_Other)
		{
			m_pPointTo = _Other.m_pPointTo;
		}

		TCDebugPointer & operator = (t_CType *_pPtr)
		{
			m_pPointTo = _pPtr;
			return *this;
		}

		TCDebugPointer & operator = (const TCDebugPointer &_Other)
		{
			m_pPointTo = _Other.m_pPointTo;
			return *this;
		}

		// Access
		operator t_CType *() const
		{
			return m_pPointTo;
		}

		t_CType *operator ->() const
		{
			return m_pPointTo;
		}

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
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, m_pPointTo);
		}

		template <typename t_CMemberPtr>
		mark_artificial inline_always typename TCEnableIf
			<
				NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
				, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
			>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return m_pPointTo->*_MemberPtr;
		}

		t_CType &operator *() const
		{
			return *m_pPointTo;
		}

		template <typename t_CType2>
		bool operator == (const t_CType2 &_Other) const
		{
			return operator t_CType *() == (t_CType *)_Other;
		}

		template <typename t_CType2>
		bool operator == (const TCDebugPointer<t_CType2> &_Other) const
		{
			return operator t_CType *() == _Other.operator t_CType2 *();
		}
	};
#endif

#ifndef DMibPNoShortCuts
#define DDebugPointerDeclare DMibDebugPointerDeclare
#endif

	template <typename t_CType>
	class TCPointer
	{
		t_CType *m_pPointTo;
	public:
		TCPointer()
			: m_pPointTo(nullptr)
		{
		}

		// Assign
		TCPointer(t_CType *_pPtr)
		{
			m_pPointTo = _pPtr;
		}

		template <typename tf_CType>
		TCPointer(TCExplicit<tf_CType> &&_Other)
		{
			m_pPointTo = *_Other;
		}

		TCPointer(const TCPointer &_Other)
		{
			m_pPointTo = _Other.m_pPointTo;
		}

		TCPointer & operator = (t_CType *_pPtr)
		{
			m_pPointTo = _pPtr;
			return *this;
		}

		TCPointer & operator = (const TCPointer &_Other)
		{
			m_pPointTo = _Other.m_pPointTo;
			return *this;
		}

		template <typename tf_CType>
		TCPointer &operator =(TCExplicit<tf_CType> &&_Other)
		{
			m_pPointTo = *_Other;
			return *this;
		}


		// Access
		t_CType *f_Get() const
		{
			return m_pPointTo;
		}

		operator t_CType *() const
		{
			return m_pPointTo;
		}

		t_CType *operator ->() const
		{
			return m_pPointTo;
		}

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
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, m_pPointTo);
		}

		template <typename t_CMemberPtr>
		mark_artificial inline_always typename TCEnableIf
			<
				NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
				, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
			>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return m_pPointTo->*_MemberPtr;
		}

		t_CType &operator *() const
		{
			return *m_pPointTo;
		}

		template <typename t_CType2>
		bool operator == (const t_CType2 &_Other) const
		{
			return operator t_CType *() == (t_CType *)_Other;
		}

		template <typename t_CType2>
		bool operator == (const TCPointer<t_CType2> &_Other) const
		{
			return operator t_CType *() == _Other.operator t_CType2 *();
		}
	};

	/////////////////////////////////////////////////////////////////////////
	// Bitstore pointer

	template <typename t_CType, mint t_nBits = 2> // Safe for 32 bit systems
	struct TCBitStorePointer
	{
		TCBitStorePointer()
			: mp_PointTo(0)
			, mp_Bits(0)
		{
		}

		// Assign
		TCBitStorePointer(t_CType *_pPtr, mint _Bits = 0)
			: mp_PointTo(fsp_ToInt(_pPtr))
			, mp_Bits(_Bits)
		{
		}

		template <typename tf_CType>
		TCBitStorePointer(TCExplicit<tf_CType> &&_Other, mint _Bits = 0)
			: mp_PointTo(fsp_ToInt(static_cast<t_CType *>(*_Other)))
			, mp_Bits(_Bits)
		{
		}

		TCBitStorePointer(TCBitStorePointer const &_Other, mint _Bits = 0)
			: mp_PointTo(_Other.mp_PointTo)
			, mp_Bits(_Bits)
		{
			// Let bits be the same
		}

		TCBitStorePointer &operator = (t_CType *_pPtr)
		{
			mp_PointTo = fsp_ToInt(_pPtr);
			return *this;
		}

		TCBitStorePointer &operator = (TCBitStorePointer const &_Other)
		{
			mp_PointTo = _Other.mp_PointTo;
			return *this;
		}

		template <typename tf_CType>
		TCBitStorePointer &operator =(TCExplicit<tf_CType> &&_Other)
		{
			mp_PointTo = fsp_ToInt(static_cast<t_CType *>(*_Other));
			return *this;
		}

		TCBitStorePointer &f_SetBits(mint _Bits)
		{
			DMibFastCheck((_Bits & ((mint(1u) << t_nBits) - 1)) == _Bits); // More bits that fits
			mp_Bits = _Bits;
			return *this;
		}

		TCBitStorePointer &f_ChangeBits(mint _Remove, mint _Add)
		{
			DMibFastCheck((_Remove & ((mint(1u) << t_nBits) - 1)) == _Remove); // More bits that fits
			DMibFastCheck((_Add & ((mint(1u) << t_nBits) - 1)) == _Add); // More bits that fits
			mp_Bits = (mp_Bits & ~_Remove) | _Add;
			return *this;
		}

		mint f_GetBits() const
		{
			return mp_Bits;
		}

		// Access
		t_CType *f_Get() const
		{
			return fsp_FromInt(mp_PointTo);
		}

		operator t_CType *() const
		{
			return fsp_FromInt(mp_PointTo);
		}

		t_CType *operator ->() const
		{
			return fsp_FromInt(mp_PointTo);
		}

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
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, fsp_FromInt(mp_PointTo));
		}

		template <typename t_CMemberPtr>
		mark_artificial inline_always typename TCEnableIf
			<
				NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
				, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
			>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return fsp_FromInt(mp_PointTo)->*_MemberPtr;
		}

		t_CType &operator *() const
		{
			return *fsp_FromInt(mp_PointTo);
		}

		template <typename tf_CType>
		bool operator == (tf_CType const &_Other) const
		{
			return operator t_CType *() == static_cast<t_CType *>(_Other);
		}

		template <typename tf_CType>
		bool operator == (TCBitStorePointer<tf_CType> const &_Other) const
		{
			return operator t_CType *() == _Other.operator tf_CType *();
		}

	private:
		static inline_always mint fsp_ToInt(t_CType *_pPtr)
		{
			DMibFastCheck(!(reinterpret_cast<mint>(_pPtr) & ((mint(1u) << t_nBits) - 1))); // Unaligned pointer not supported
			return reinterpret_cast<mint>(_pPtr) >> t_nBits;
		}

		static inline_always constexpr t_CType *fsp_FromInt(mint _Pointer)
		{
			return reinterpret_cast<t_CType *>(_Pointer << t_nBits);
		}

		mint mp_PointTo:sizeof(mint)*8 - t_nBits;
		mint mp_Bits:t_nBits;
	};

	/////////////////////////////////////////////////////////////////////////
	// Refcount pointer

#if DMibConfig_RefcountDebugging
	struct CRefCountDebugReference
	{
		CRefCountDebugReference();
		~CRefCountDebugReference();

		CRefCountDebugReference(CRefCountDebugReference const &_Other) = delete;
		CRefCountDebugReference &operator =(CRefCountDebugReference const &_Other) = delete;

		CRefCountDebugReference(CRefCountDebugReference &&_Other);
		CRefCountDebugReference &operator =(CRefCountDebugReference &&_Other);

		NException::CCallstack *m_pCallstack = nullptr;
	};
#define DMibRefcountDebuggingOnly(...) __VA_ARGS__
#else
#define DMibRefcountDebuggingOnly(...)
#endif

	namespace NPrivate
	{
		DMibTypeTraitsImplement_MemberTraits(f_RefCountIncrease);
	}

	template <typename t_CType>
	struct TCHasIntrusiveRefcount : public NTraits::TCCompileTimeConstant
		<
			bool
			, NPrivate::TCIsMemberCallableWith_f_RefCountIncrease
			<
				t_CType
				, void (DMibRefcountDebuggingOnly(NStorage::CRefCountDebugReference &o_DebugRef))
			>::mc_Value
		>
	{
	};

#define DMibDefineSharedPointerType(d_Type, d_HasRefCount, d_VirtualDestructor) \
	template <>\
	struct NMib::NStorage::TCHasIntrusiveRefcount<d_Type> : public NMib::NTraits::TCCompileTimeConstant<bool, d_HasRefCount>\
	{\
	};\
	template <>\
	struct NMib::NTraits::TCHasVirtualDestructor<d_Type> : public NMib::NTraits::TCCompileTimeConstant<bool, d_VirtualDestructor>\
	{ \
	};

	struct CSupportWeakTag
	{
	};

	namespace NPrivate
	{

		template <typename t_CType, CSharedPointerOptionUnderlaying t_Options, bool t_bHasRefCount = TCHasIntrusiveRefcount<typename NTraits::TCRemoveQualifiers<t_CType>::CType>::mc_Value>
		class TCChooseSharedPointerTypeImp
		{
		public:

		};

		template <typename t_CType, CSharedPointerOptionUnderlaying t_Options>
		class TCChooseSharedPointerTypeImp<t_CType, t_Options, true>
		{
		public:

			typedef t_CType CType;
		};

		template <CSharedPointerOptionUnderlaying t_Options, bool t_bHasRefCount>
		class TCChooseSharedPointerTypeImp<void, t_Options, t_bHasRefCount>
		{
		public:
			typedef void CType;
		};

		template <CSharedPointerOptionUnderlaying t_Options>
		class TCChooseSharedPointerTypeImp<void, t_Options, false>
		{
		public:
			typedef void CType;
		};

		template <typename tf_CType>
		tf_CType *fg_GetSharedPointerPointer(tf_CType *_In)
		{
			return _In;
		}

		template <typename tf_CToType, typename tf_CType>
		tf_CType *fg_ConvertSharedPointer(tf_CType *_pIn, tf_CToType *_pDummy)
		{
			return _pIn;
		}

		template <typename t_CType, bool t_bVirtualDestructor, CSharedPointerOptionUnderlaying t_Options>
		class TCSharedPointerCounter;

		template <typename t_CType, CSharedPointerOptionUnderlaying t_Options>
		class TCSharedPointerCounter<t_CType, true, t_Options>;


		template <typename tf_CType, bool tf_bVirtualDestructor, CSharedPointerOptionUnderlaying tf_Options>
		tf_CType *fg_GetSharedPointerPointer(TCSharedPointerCounter<tf_CType, tf_bVirtualDestructor, tf_Options> *_pIn);

		template <typename tf_CToType, typename tf_CType, bool tf_bToVirtualDestructor, bool tf_bVirtualDestructor, CSharedPointerOptionUnderlaying tf_ToOptions, CSharedPointerOptionUnderlaying tf_Options>
		TCSharedPointerCounter<tf_CToType, tf_bToVirtualDestructor, tf_ToOptions> *fg_ConvertSharedPointer(TCSharedPointerCounter<tf_CType, tf_bVirtualDestructor, tf_Options> *_pIn, TCSharedPointerCounter<tf_CToType, tf_bToVirtualDestructor, tf_ToOptions> *_pDummy);

		template <typename... tp_CParams>
		struct TCParseSharedPointerOptions;

		template <>
		struct TCParseSharedPointerOptions<>
		{
			typedef NMeta::TCTypeList<> CFunctions;
			typedef NMemory::CDefaultAllocator CAllocator;
			static constexpr bool mc_bSupportWeak = false;
		};

		template <typename t_CFirst, typename... tp_CParams>
		struct TCParseSharedPointerOptions<t_CFirst, tp_CParams...>
		{
			typedef TCParseSharedPointerOptions<tp_CParams...> CParent;
			typedef t_CFirst CAllocator;
			static constexpr bool mc_bSupportWeak = CParent::mc_bSupportWeak;
		};

		template <typename... tp_CParams>
		struct TCParseSharedPointerOptions<CSupportWeakTag, tp_CParams...>
		{
			typedef TCParseSharedPointerOptions<tp_CParams...> CParent;
			typedef typename CParent::CAllocator CAllocator;
			static constexpr bool mc_bSupportWeak = true;
		};

		template <typename t_CType, typename t_CAllocator, CSharedPointerOptionUnderlaying t_Options>
		struct TCSharedPointerData : public t_CAllocator
		{
		private:
			TCSharedPointerData(TCSharedPointerData const &_Other)
			{
			}
			TCSharedPointerData(TCSharedPointerData &&_Other)
			{
			}
		public:
			template <typename t_CType2>
			class TCChooseSharedPointerType : public TCChooseSharedPointerTypeImp<t_CType2, t_Options>
			{
			public:

			};

			typedef typename TCChooseSharedPointerTypeImp<t_CType, t_Options>::CType CInternalData;
			CInternalData *m_pPointTo;
			DMibRefcountDebuggingOnly(mutable NStorage::CRefCountDebugReference m_DebugRef);

			TCSharedPointerData()
			{
			}

			TCSharedPointerData(t_CAllocator const &_Other)
				: t_CAllocator(_Other)
			{
			}
			TCSharedPointerData(t_CAllocator &&_Other)
				: t_CAllocator(fg_Move(_Other))
			{
			}

			template <typename t_CParam0>
			TCSharedPointerData(t_CParam0 &&_Other)
				: t_CAllocator(fg_Forward<t_CParam0>(_Other))
			{
			}
		};
	}

	template <typename tf_CObjectType>
	NMemory::CCapturedDelete fg_DeleteWeakObjectGetCapturedDelete(tf_CObjectType *_pObject)
	{
		static_assert(sizeof(tf_CObjectType) > 0);
		static_assert(!NTraits::TCIsAbstract<tf_CObjectType>::mc_Value || NTraits::TCHasVirtualDestructor<tf_CObjectType>::mc_Value);
		if constexpr (NTraits::TCHasVirtualDestructor<tf_CObjectType>::mc_Value)
		{
			static_assert(!NTraits::TCHasOperatorDelete<tf_CObjectType>::mc_Value);
#if defined(DMibPOverrideOperatorNew)

			NMemory::CCaptureDefaultDelete Captured;
			delete _pObject;

			DMibFastCheck(Captured.m_Captured.m_pMemory);

			return Captured.m_Captured;
#else
			static_assert(!NTraits::TCHasVirtualDestructor<tf_CObjectType>::mc_Value); // Operator new has to be overridden for this to work
			return {_pObject, 0};
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
		_pObject->f_WeakRefCountSetCapturedDelete(CapturedDelete);
		if (_pObject->f_WeakRefCountDecrease(DMibRefcountDebuggingOnly(nullptr)) == 0)
		{
			if (CapturedDelete.m_Size)
				fg_Forward<tf_CAllocator>(_Allocator).f_Free(CapturedDelete.m_pMemory, CapturedDelete.m_Size);
			else
				fg_Forward<tf_CAllocator>(_Allocator).f_FreeNoSize(CapturedDelete.m_pMemory);
		}
	}

	template <typename t_CType, typename... tp_COptions>
	class TCSharedPointer
	{
		template <typename t_CType2, typename... tp_COptions2>
		friend class TCSharedPointer;
		template <typename t_CType2, typename... tp_COptions2>
		friend class TCWeakPointer;

		typedef NPrivate::TCParseSharedPointerOptions<tp_COptions...> COptions;
		typedef typename COptions::CAllocator CAllocator;

		static constexpr bool mc_bSupportWeak = COptions::mc_bSupportWeak;

		typedef NPrivate::TCSharedPointerData<t_CType, CAllocator, mc_bSupportWeak ? ESharedPointerOption_SupportWeakPointer : ESharedPointerOption_None > CData;

		typedef typename CData::CInternalData CInternalData;

		CData m_Data;

		CAllocator &fp_GetAllocator()
		{
			return m_Data;
		}

		CAllocator const &fp_GetAllocator() const
		{
			return m_Data;
		}


		void fp_Set(CInternalData *_pPtr)
		{
			fp_Delete();
			if (_pPtr)
				_pPtr->f_RefCountIncrease(DMibRefcountDebuggingOnly(m_Data.m_DebugRef));
			m_Data.m_pPointTo = _pPtr;
		}
		void fp_SetInit(CInternalData *_pPtr)
		{
			if (_pPtr)
				_pPtr->f_RefCountIncrease(DMibRefcountDebuggingOnly(m_Data.m_DebugRef));
			m_Data.m_pPointTo = _pPtr;
		}

		void fp_SetConstruct(CInternalData *_pPtr)
		{
			m_Data.m_pPointTo = _pPtr;
			DMibRefcountDebuggingOnly(m_Data.m_pPointTo->f_InitialRef(m_Data.m_DebugRef));
		}

		void fp_SetCounted(CInternalData *_pPtr)
		{
			m_Data.m_pPointTo = _pPtr;
		}

		CInternalData *fp_Get() const
		{
			return m_Data.m_pPointTo;
		}


		template <bool tf_bSupportWeak, typename TCEnableIf<tf_bSupportWeak>::CType * = nullptr>
		bool fp_Delete()
		{
			bool bRet = false;
			if (m_Data.m_pPointTo)
			{
				if (m_Data.m_pPointTo->f_RefCountDecrease(DMibRefcountDebuggingOnly(m_Data.m_DebugRef)) == 0)
				{
					auto Cleanup
						= g_OnScopeExit > [&]()
						{
							// Protect against exception in destructor
							m_Data.m_pPointTo->f_RefCountIncrease(DMibRefcountDebuggingOnly(m_Data.m_DebugRef));
						}
					;

					fg_DeleteWeakObject(fp_GetAllocator(), (CInternalData *)m_Data.m_pPointTo);
					Cleanup.f_Clear();
					bRet = true;
				}
				m_Data.m_pPointTo = nullptr;
			}
			return bRet;
		}

		template <bool tf_bSupportWeak, typename TCEnableIf<!tf_bSupportWeak>::CType * = nullptr>
		bool fp_Delete()
		{
			bool bRet = false;
			if (m_Data.m_pPointTo)
			{
				if (m_Data.m_pPointTo->f_RefCountDecrease(DMibRefcountDebuggingOnly(m_Data.m_DebugRef)) == 0)
				{
					auto Cleanup
						= g_OnScopeExit > [&]()
						{
							// Protect against exception in destructor
							m_Data.m_pPointTo->f_RefCountIncrease(DMibRefcountDebuggingOnly(m_Data.m_DebugRef));
						}
					;

					fg_DeleteObject(fp_GetAllocator(), &fg_RemoveQualifiers(*((CInternalData *)m_Data.m_pPointTo)));
					Cleanup.f_Clear();
					bRet = true;
				}

				m_Data.m_pPointTo = nullptr;
			}
			return bRet;
		}

		bool fp_Delete()
		{
			return fp_Delete<mc_bSupportWeak>();
		}

		// Used by weak pointer
		TCSharedPointer(CAllocator const &_Allocator)
			: m_Data(_Allocator)
		{
			m_Data.m_pPointTo = nullptr;
		}

	public:
		using CWeakPointer = TCWeakPointer<t_CType, CAllocator>;

		TCSharedPointer()
		{
			m_Data.m_pPointTo = nullptr;
		}
		~TCSharedPointer()
		{
			fp_Delete();
		}

		TCSharedPointer(TCCopy<TCSharedPointer> const &_Other)
			: m_Data((*_Other).fp_GetAllocator())
		{
			m_Data.m_pPointTo = nullptr; // Protect against exception in constructor
			if (*_Other)
				fp_SetConstruct(fg_ConstructObject<CInternalData>(fp_GetAllocator(), *((*_Other).m_Data.m_pPointTo)));
		}


		TCSharedPointer(TCSharedPointer const &_Other)
			: m_Data(_Other.fp_GetAllocator())
		{
			fp_SetInit(_Other.m_Data.m_pPointTo);
		}

		TCSharedPointer(TCSharedPointer &&_Other)
			: m_Data(fg_Move(_Other.fp_GetAllocator()))
		{
			m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
			_Other.m_Data.m_pPointTo = nullptr;
			DMibRefcountDebuggingOnly
				(
					if (m_Data.m_pPointTo)
				 		m_Data.m_pPointTo->f_RefCountMove(_Other.m_Data.m_DebugRef, m_Data.m_DebugRef);
				)
			;
		}

		template <typename tf_CType, typename... tfp_COptions>
		TCSharedPointer(TCSharedPointer<tf_CType, tfp_COptions...> const &_Other)
			: m_Data(_Other.fp_GetAllocator())
		{
			static_assert
				(
					NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
					, "Not a valid conversion"
				)
			;
			static_assert((NTraits::TCIsSame<typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator, CAllocator>::mc_Value));
			static_assert(mc_bSupportWeak == TCSharedPointer<tf_CType, tfp_COptions...>::mc_bSupportWeak);
			fp_SetInit(NPrivate::fg_ConvertSharedPointer(_Other.fp_Get(), (CInternalData *)nullptr));
		}

		template <typename tf_CType, typename... tfp_COptions>
		TCSharedPointer(TCSharedPointer<tf_CType, tfp_COptions...> &&_Other)
			: m_Data(fg_Move(_Other.fp_GetAllocator()))
		{
			static_assert
				(
					NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
					, "Not a valid conversion"
				)
			;
			static_assert(mc_bSupportWeak == TCSharedPointer<tf_CType, tfp_COptions...>::mc_bSupportWeak);
			m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
			_Other.m_Data.m_pPointTo = nullptr;
			DMibRefcountDebuggingOnly
				(
					if (m_Data.m_pPointTo)
				 		m_Data.m_pPointTo->f_RefCountMove(_Other.m_Data.m_DebugRef, m_Data.m_DebugRef);
				)
			;
		}

		template <typename tf_CType, typename... tfp_CParams>
		TCSharedPointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
		{
			static_assert(NTraits::TCIsVoid<tf_CType>::mc_Value || NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, CAllocator>::mc_Value, "Not a valid conversion");
			m_Data.m_pPointTo = nullptr; // Protect against exception in constructor
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

		template <typename tf_CType, typename... tfp_CParams, typename tf_CAllocator>
		TCSharedPointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams, tf_CAllocator &&_Allocator)
			: m_Data(fg_Forward<tf_CAllocator>(_Allocator))
		{
			static_assert
				(
					NTraits::TCIsVoid<tf_CType>::mc_Value
					|| NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename NTraits::TCRemoveReference<tf_CAllocator>::CType>::mc_Value
					, "Not a valid conversion"
				)
			;
			m_Data.m_pPointTo = nullptr; // Protect against exception in constructor
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

		explicit TCSharedPointer(t_CType *_pPtr)
		{
			fp_SetInit(_pPtr);
		}

		template <typename t_CParam0>
		explicit TCSharedPointer(t_CType *_pPtr, t_CParam0 &&_Param0)
			: m_Data(fg_Forward<t_CParam0>(_Param0))
		{
			fp_SetInit(_pPtr);
		}


		template <typename tf_CType>
		TCSharedPointer(TCExplicit<tf_CType> &&_Other)
		{
			fp_SetInit(*_Other);
		}

		template <typename tf_CType, typename tf_CAllocator>
		TCSharedPointer(TCExplicit<tf_CType> &&_Other, tf_CAllocator &&_Allocator)
			: m_Data(fg_Forward<tf_CAllocator>(_Allocator))
		{
			fp_SetInit(*_Other);
		}


		TCSharedPointer(CNullPtr)
		{
			m_Data.m_pPointTo = nullptr;
		}


		bool f_Clear()
		{
			return fp_Delete();
		}

		CWeakPointer f_Weak() const
		{
			return *this;
		}

		t_CType *f_Get() const
		{
			return NPrivate::fg_GetSharedPointerPointer((CInternalData *)m_Data.m_pPointTo);
		}
		t_CType *operator ->() const
		{
			return NPrivate::fg_GetSharedPointerPointer((CInternalData *)m_Data.m_pPointTo);
		}

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
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, NPrivate::fg_GetSharedPointerPointer((CInternalData *)m_Data.m_pPointTo));
		}

		template <typename t_CMemberPtr>
		mark_artificial inline_always typename TCEnableIf
			<
				NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
				, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
			>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return (NPrivate::fg_GetSharedPointerPointer((CInternalData *)m_Data.m_pPointTo))->*_MemberPtr;
		}


		t_CType &operator *() const
		{
			return *NPrivate::fg_GetSharedPointerPointer((CInternalData *)m_Data.m_pPointTo);
		}

		TCSharedPointer & operator = (CNullPtr)
		{
			fp_Delete();
			return *this;
		}

		template <typename tf_CType>
		TCSharedPointer &operator = (TCExplicit<tf_CType> &&_Other)
		{
			fp_Set(*_Other);
			return *this;
		}

		TCSharedPointer &operator = (TCSharedPointer &&_Other)
		{
			fp_Delete();
			fp_GetAllocator() = fg_Move(_Other.fp_GetAllocator());
			m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
			_Other.m_Data.m_pPointTo = nullptr;
			DMibRefcountDebuggingOnly
				(
					if (m_Data.m_pPointTo)
				 		m_Data.m_pPointTo->f_RefCountMove(_Other.m_Data.m_DebugRef, m_Data.m_DebugRef);
				)
			;
			return *this;
		}

		TCSharedPointer &operator = (const TCSharedPointer &_Other)
		{
			fp_Delete();
			fp_GetAllocator() = _Other.fp_GetAllocator();
			fp_SetInit(_Other.m_Data.m_pPointTo);
			return *this;
		}

		template <typename tf_CType, typename... tfp_COptions>
		TCSharedPointer &operator = (TCSharedPointer<tf_CType, tfp_COptions...> &&_Other)
		{
			fp_Delete();
			fp_GetAllocator() = fg_Move(_Other.fp_GetAllocator());
			static_assert
				(
					NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
					, "Not a valid conversion"
				)
			;
			static_assert((NTraits::TCIsSame<typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator, CAllocator>::mc_Value));
			static_assert(mc_bSupportWeak == TCSharedPointer<tf_CType, tfp_COptions...>::mc_bSupportWeak);
			m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
			_Other.m_Data.m_pPointTo = nullptr;
			DMibRefcountDebuggingOnly
				(
					if (m_Data.m_pPointTo)
				 		m_Data.m_pPointTo->f_RefCountMove(_Other.m_Data.m_DebugRef, m_Data.m_DebugRef);
				)
			;
			return *this;
		}

		template <typename tf_CType, typename... tfp_COptions>
		TCSharedPointer &operator = (TCSharedPointer<tf_CType, tfp_COptions...> const &_Other)
		{
			fp_Delete();
			fp_GetAllocator() = _Other.fp_GetAllocator();
			static_assert
				(
					NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
					, "Not a valid conversion"
				)
			;
			static_assert((NTraits::TCIsSame<typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator, CAllocator>::mc_Value));
			static_assert(mc_bSupportWeak == TCSharedPointer<tf_CType, tfp_COptions...>::mc_bSupportWeak);
			fp_SetInit(NPrivate::fg_ConvertSharedPointer(_Other.fp_Get(), (CInternalData *)nullptr));
			return *this;
		}

		TCSharedPointer &operator = (TCCopy<TCSharedPointer> const &_Other)
		{
			CInternalData *pNewObject = nullptr;
			if (*_Other)
			{
				pNewObject = fg_ConstructObject<CInternalData>((*_Other).fp_GetAllocator(), *((*_Other).m_Data.m_pPointTo));
			}
			auto Cleanup
				= g_OnScopeExit > [&]
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

		template <typename tf_CType, typename... tfp_CParams>
		TCSharedPointer &operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
		{
			static_assert(NTraits::TCIsVoid<tf_CType>::mc_Value || NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, CAllocator>::mc_Value, "Not a valid conversion");

			auto *pNewObject = NPrivate::fg_ConvertSharedPointer
				(
					fg_TransformConstruct<CData::template TCChooseSharedPointerType>(fg_Move(_CreateParams)).template f_Create<CInternalData>(fp_GetAllocator())
					, (CInternalData *)nullptr
				)
			;
			auto Cleanup
				= g_OnScopeExit > [&]
				{
					fg_DeleteObject(fp_GetAllocator(), pNewObject);
				}
			;

			fp_Delete();
			Cleanup.f_Clear();
			fp_SetConstruct(pNewObject);
			return *this;
		}

		template <typename tf_CType>
		bool operator == (tf_CType *_pOther) const
		{
			return f_Get() == _pOther;
		}

		bool operator == (CNullPtr _pOther) const
		{
			return f_Get() == _pOther;
		}

		template <typename tf_CType, typename... tfp_COptions>
		bool operator == (const TCSharedPointer<tf_CType, tfp_COptions...> &_Other) const
		{
			return f_Get() == static_cast<t_CType *>(_Other.f_Get());
		}

		template <typename tf_CType, typename... tfp_COptions>
		bool operator == (const TCWeakPointer<tf_CType, tfp_COptions...> &_Other) const
		{
			return f_Get() == static_cast<t_CType *>(_Other.fp_GetContained());
		}

		template <typename tf_CType>
		bool operator < (tf_CType *_pOther) const
		{
			return f_Get() < _pOther;
		}

		bool operator < (CNullPtr _pOther) const
		{
			return f_Get() < _pOther;
		}

		template <typename tf_CType, typename... tfp_COptions>
		bool operator < (const TCSharedPointer<tf_CType, tfp_COptions...> &_Other) const
		{
			return f_Get() < static_cast<t_CType *>(_Other.f_Get());
		}

		template <typename tf_CType, typename... tfp_COptions>
		bool operator < (const TCWeakPointer<tf_CType, tfp_COptions...> &_Other) const
		{
			return f_Get() < static_cast<t_CType *>(_Other.fp_GetContained());
		}

		template <typename tf_CLeft>
		friend bool operator == (tf_CLeft *_pLeft, const TCSharedPointer &_pRight)
		{
			return _pLeft == _pRight.f_Get();
		}

		friend bool operator == (CNullPtr _pLeft, const TCSharedPointer &_pRight)
		{
			return _pLeft == _pRight.f_Get();
		}

		template <typename tf_CLeft>
		friend bool operator < (tf_CLeft *_pLeft, const TCSharedPointer &_pRight)
		{
			return _pLeft < _pRight.f_Get();
		}

		friend bool operator < (CNullPtr _pLeft, const TCSharedPointer &_pRight)
		{
			return _pLeft < _pRight.f_Get();
		}

		bool f_IsEmpty() const
		{
			return m_Data.m_pPointTo == nullptr;
		}

		inline_small explicit operator bool() const
		{
			return !f_IsEmpty();
		}
	};

	template <typename t_CType, typename... tp_COptions>
	using TCSharedPointerSupportWeak = TCSharedPointer<t_CType, CSupportWeakTag, tp_COptions...>;

	template <typename t_CType, typename... tp_COptions>
	class TCWeakPointer
	{
		template <typename t_CType2, typename... tp_COptions2>
		friend class TCSharedPointer;
		template <typename t_CType2, typename... tp_COptions2>
		friend class TCWeakPointer;

		typedef typename NPrivate::TCParseSharedPointerOptions<tp_COptions...>::CAllocator CAllocator;

		typedef NPrivate::TCSharedPointerData<t_CType, CAllocator, ESharedPointerOption_SupportWeakPointer> CData;
		typedef typename CData::CInternalData CInternalData;

		CData m_Data;

		CAllocator &fp_GetAllocator()
		{
			return m_Data;
		}

		CAllocator const &fp_GetAllocator() const
		{
			return m_Data;
		}


		void fp_Set(CInternalData *_pPtr)
		{
			fp_Delete();
			if (_pPtr)
				_pPtr->f_WeakRefCountIncrease(DMibRefcountDebuggingOnly(m_Data.m_DebugRef));
			m_Data.m_pPointTo = _pPtr;
		}

		void fp_SetInit(CInternalData *_pPtr)
		{
			if (_pPtr)
				_pPtr->f_WeakRefCountIncrease(DMibRefcountDebuggingOnly(m_Data.m_DebugRef));
			m_Data.m_pPointTo = _pPtr;
		}

		CInternalData *fp_Get() const
		{
			return m_Data.m_pPointTo;
		}

		template <typename t_CDummy>
		bool fp_Delete()
		{
			bool bRet = false;
			auto pPointTo = m_Data.m_pPointTo;
			if (pPointTo)
			{
				if (pPointTo->f_WeakRefCountDecrease(DMibRefcountDebuggingOnly(&m_Data.m_DebugRef)) == 0)
				{
					NMemory::CCapturedDelete CapturedDelete = pPointTo->f_WeakRefCountGetCapturedDelete();
					if (CapturedDelete.m_Size)
						fp_GetAllocator().f_Free(CapturedDelete.m_pMemory, CapturedDelete.m_Size);
					else
						fp_GetAllocator().f_FreeNoSize(CapturedDelete.m_pMemory);
					bRet = true;
				}
				m_Data.m_pPointTo = nullptr;
			}
			return bRet;
		}

		bool fp_Delete()
		{
			return fp_Delete<CInternalData>();
		}

		t_CType *fp_GetContained() const
		{
			return NPrivate::fg_GetSharedPointerPointer((CInternalData *)m_Data.m_pPointTo);
		}

	public:
		TCWeakPointer()
		{
			m_Data.m_pPointTo = nullptr;
		}
		~TCWeakPointer()
		{
			fp_Delete();
		}

		TCWeakPointer(TCWeakPointer const &_Other)
			: m_Data(_Other.fp_GetAllocator())
		{
			fp_SetInit(_Other.m_Data.m_pPointTo);
		}

		TCWeakPointer(TCWeakPointer &&_Other)
			: m_Data(fg_Move(_Other.fp_GetAllocator()))
		{
			m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
			_Other.m_Data.m_pPointTo = nullptr;
			DMibRefcountDebuggingOnly
				(
					if (m_Data.m_pPointTo)
				 		m_Data.m_pPointTo->f_WeakRefCountMove(_Other.m_Data.m_DebugRef, m_Data.m_DebugRef);
				)
			;
		}

		template <typename tf_CType, typename... tfp_COptions>
		TCWeakPointer(TCWeakPointer<tf_CType, tfp_COptions...> const &_Other)
			: m_Data(_Other.fp_GetAllocator())
		{
			static_assert
				(
					NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCWeakPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
					, "Not a valid conversion"
				)
			;
			fp_SetInit(NPrivate::fg_ConvertSharedPointer(_Other.fp_Get(), (CInternalData *)nullptr));
		}

		template <typename tf_CType, typename... tfp_COptions>
		TCWeakPointer(TCWeakPointer<tf_CType, tfp_COptions...> &&_Other)
			: m_Data(fg_Move(_Other.fp_GetAllocator()))
		{
			static_assert
				(
					NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCWeakPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
					, "Not a valid conversion"
				)
			;
			m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
			_Other.m_Data.m_pPointTo = nullptr;
			DMibRefcountDebuggingOnly
				(
					if (m_Data.m_pPointTo)
				 		m_Data.m_pPointTo->f_WeakRefCountMove(_Other.m_Data.m_DebugRef, m_Data.m_DebugRef);
				)
			;
		}

		explicit TCWeakPointer(t_CType *_pPtr)
		{
			fp_SetInit(_pPtr);
		}

		template <typename t_CParam0>
		explicit TCWeakPointer(t_CType *_pPtr, t_CParam0 &&_Param0)
			: m_Data(fg_Forward<t_CParam0>(_Param0))
		{
			fp_SetInit(_pPtr);
		}

		CInternalData *f_UnsafeGetPointerValue() const
		{
			return m_Data.m_pPointTo;
		}

		template <typename tf_CType>
		TCWeakPointer(TCExplicit<tf_CType> &&_Other)
		{
			fp_SetInit(*_Other);
		}

		template <typename tf_CType, typename tf_CAllocator>
		TCWeakPointer(TCExplicit<tf_CType> &&_Other, tf_CAllocator &&_Allocator)
			: m_Data(fg_Forward<tf_CAllocator>(_Allocator))
		{
			fp_SetInit(*_Other);
		}


		template <typename tf_CType, typename... tfp_COptions>
		TCWeakPointer(TCSharedPointer<tf_CType, tfp_COptions...> const &_Other)
			: m_Data(_Other.fp_GetAllocator())
		{
			static_assert
				(
					TCSharedPointer<tf_CType, tfp_COptions...>::mc_bSupportWeak
					, "The source TCSharedPointer does not support TCWeakPointer, please add CSupportWeakTag"
				)
			;
			static_assert
				(
					NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
					, "Not a valid conversion"
				)
			;
			fp_SetInit(NPrivate::fg_ConvertSharedPointer(_Other.fp_Get(), (CInternalData *)nullptr));
		}

		template <typename tf_CType, typename... tfp_COptions>
		TCWeakPointer(TCSharedPointer<tf_CType, tfp_COptions...> &&_Other)
			: m_Data(fg_Move(_Other.fp_GetAllocator()))
		{
			static_assert
				(
					TCSharedPointer<tf_CType, tfp_COptions...>::mc_bSupportWeak
					, "The source TCSharedPointer does not support TCWeakPointer, please add CSupportWeakTag"
				)
			;
			static_assert
				(
					NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
					, "Not a valid conversion"
				)
			;
			fp_SetInit(NPrivate::fg_ConvertSharedPointer(_Other.fp_Get(), (CInternalData *)nullptr));
			_Other.f_Clear();
		}


		TCWeakPointer(CNullPtr)
		{
			m_Data.m_pPointTo = nullptr;
		}



		bool f_Clear()
		{
			return fp_Delete();
		}

		TCWeakPointer & operator = (CNullPtr)
		{
			fp_Delete();
			return *this;
		}

		template <typename tf_CType>
		TCWeakPointer &operator = (TCExplicit<tf_CType> &&_Other)
		{
			fp_Set(*_Other);
			return *this;
		}

		TCWeakPointer &operator = (TCWeakPointer &&_Other)
		{
			fp_Delete();
			fp_GetAllocator() = fg_Move(_Other.fp_GetAllocator());
			m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
			_Other.m_Data.m_pPointTo = nullptr;
			DMibRefcountDebuggingOnly
				(
					if (m_Data.m_pPointTo)
				 		m_Data.m_pPointTo->f_WeakRefCountMove(_Other.m_Data.m_DebugRef, m_Data.m_DebugRef);
				)
			;
			return *this;
		}

		TCWeakPointer &operator = (const TCWeakPointer &_Other)
		{
			fp_Delete();
			fp_GetAllocator() = _Other.fp_GetAllocator();
			fp_SetInit(_Other.m_Data.m_pPointTo);
			return *this;
		}

		template <typename tf_CType, typename... tfp_COptions>
		TCWeakPointer &operator = (TCSharedPointer<tf_CType, tfp_COptions...> const &_Other)
		{
			static_assert
				(
					TCSharedPointer<tf_CType, tfp_COptions...>::mc_bSupportWeak
					, "The source TCSharedPointer does not support TCWeakPointer, please add CSupportWeakTag"
				)
			;
			static_assert
				(
					NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
					, "Not a valid conversion"
				)
			;
			fp_Delete();
			fp_GetAllocator() = _Other.fp_GetAllocator();
			fp_SetInit(NPrivate::fg_ConvertSharedPointer(_Other.fp_Get(), (CInternalData *)nullptr));
			return *this;
		}

		template <typename tf_CType, typename... tfp_COptions>
		TCWeakPointer &operator = (TCSharedPointer<tf_CType, tfp_COptions...> &&_Other)
		{
			static_assert
				(
					TCSharedPointer<tf_CType, tfp_COptions...>::mc_bSupportWeak
					, "The source TCSharedPointer does not support TCWeakPointer, please add CSupportWeakTag"
				)
			;
			static_assert
				(
					NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value
					, "Not a valid conversion"
				)
			;
			fp_Delete();
			fp_GetAllocator() = fg_Move(_Other.fp_GetAllocator());
			fp_SetInit(NPrivate::fg_ConvertSharedPointer(_Other.fp_Get(), (CInternalData *)nullptr));
			_Other.f_Clear();
			return *this;
		}

		TCSharedPointer<t_CType, CSupportWeakTag, tp_COptions...> f_Lock() const
		{
			TCSharedPointer<t_CType, CSupportWeakTag, tp_COptions...> pReturn(fp_GetAllocator());

			auto pData = m_Data.m_pPointTo;
			if (!pData)
				return pReturn;

			if (!pData->f_RefCountIncreaseWhileValid(DMibRefcountDebuggingOnly(pReturn.m_Data.m_DebugRef)))
				return pReturn;

			pReturn.fp_SetCounted(pData);

			return pReturn;
		}

		template <typename tf_CType>
		bool operator == (tf_CType *_pOther) const
		{
			return fp_GetContained() == _pOther;
		}

		bool operator == (CNullPtr _pOther) const
		{
			return fp_GetContained() == _pOther;
		}

		template <typename tf_CType, typename... tfp_COptions>
		bool operator == (const TCWeakPointer<tf_CType, tfp_COptions...> &_Other) const
		{
			return fp_GetContained() == _Other.fp_GetContained();
		}

		template <typename tf_CType, typename... tfp_COptions>
		bool operator == (const TCSharedPointer<tf_CType, tfp_COptions...> &_Other) const
		{
			return fp_GetContained() == _Other.f_Get();
		}

		template <typename tf_CType>
		bool operator < (tf_CType *_pOther) const
		{
			return fp_GetContained() < _pOther;
		}

		bool operator < (CNullPtr _pOther) const
		{
			return fp_GetContained() < _pOther;
		}

		template <typename tf_CType, typename... tfp_COptions>
		bool operator < (const TCWeakPointer<tf_CType, tfp_COptions...> &_Other) const
		{
			return fp_GetContained() < _Other.fp_GetContained();
		}

		template <typename tf_CType, typename... tfp_COptions>
		bool operator < (const TCSharedPointer<tf_CType, tfp_COptions...> &_Other) const
		{
			return fp_GetContained() < _Other.f_Get();
		}

		bool f_IsEmpty() const
		{
			return m_Data.m_pPointTo == nullptr;
		}

		inline_small explicit operator bool() const
		{
			return !f_IsEmpty();
		}

		template <typename tf_CLeft>
		friend bool operator == (tf_CLeft *_pLeft, const TCWeakPointer &_pRight)
		{
			return _pLeft == _pRight.f_Get();
		}

		friend bool operator == (CNullPtr _pLeft, const TCWeakPointer &_pRight)
		{
			return _pLeft == _pRight.f_Get();
		}

		template <typename tf_CLeft>
		friend bool operator < (tf_CLeft *_pLeft, const TCWeakPointer &_pRight)
		{
			return _pLeft < _pRight.f_Get();
		}

		friend bool operator < (CNullPtr _pLeft, const TCWeakPointer &_pRight)
		{
			return _pLeft < _pRight.f_Get();
		}
	};
}

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif
