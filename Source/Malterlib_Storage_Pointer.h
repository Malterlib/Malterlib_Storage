// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
#include <Mib/Function/BindMemberFunction>
namespace NMib
{
	namespace NPtr
	{
		/////////////////////////////////////////////////////////////////////////
		// Auto clear ptr
		class CAutoClearPtr
		{
		public:
			CAutoClearPtr()
			{
			}
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
			CAutoClearPtrMember()
			{
			}
			DMibListLinkDS_List(CAutoClearPtr, m_Link) m_Linked;
			~CAutoClearPtrMember()
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
			typename TCEnableIf
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
			typename TCEnableIf
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
			typename TCEnableIf
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
			typename TCEnableIf
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

#define DMibAutoClearPtrDeclare mutable NMib::NPtr::CAutoClearPtrMember m_AutoClearPtrMember
#define DMibAutoClearPtrDeclareDebug(_Type) mutable NMib::NPtr::TCAutoClearPtrMemberDebug<_Type> m_AutoClearPtrMemberDebug
#ifndef DMibPNoShortCuts
#define DAutoClearPtrDeclare DMibAutoClearPtrDeclare
#endif


#if defined DMibContractsConfigure_CheckEnabled
		#define DMibDebugPointerDeclare mutable NMib::NPtr::CAutoClearPtrMemberDebug m_DebugPointerMember
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
			typename TCEnableIf
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
			typename TCEnableIf
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
			typename TCEnableIf
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
			typename TCEnableIf
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
			typename TCEnableIf
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
			typename TCEnableIf
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
		// Scoped pointer




		/////////////////////////////////////////////////////////////////////////
		// Refcount pointer

		/* TODO

			* Copy ctor och assignement bör ta sin parameter by const&. Reference count är inte en del av objectets state och bör kunna modifieras ven på ett const object
			* m_pPointTo bör initieras I constructors init lista eftersom den troligen inte är en native typ, så du får en dubbelinitiering.
			* Exception safety needs a look over
			* Automatically wrap an object with internal state if needed and rename to TCSharedPtr (automatically use intrusive functions if available in type)
			* Use a free function instead of f_RefCountIncrease. This wiill enable adaption of non modifiable third party refcounted objects

		*/
		namespace NPrivate
		{
			DMibTypeTraitsImplement_MemberTraits(f_RefCountIncrease);
		}

		template <typename t_CType>
		struct TCHasIntrusiveRefcount : public NTraits::TCCompileTimeConstant<bool, NPrivate::TCIsMemberCallableWith_f_RefCountIncrease<t_CType, void ()>::mc_Value>
		{
		};

#define DMibDefineSharedPointerType(d_Type, d_HasRefCount, d_VirtualDestructor) \
		template <>\
		struct NMib::NPtr::TCHasIntrusiveRefcount<d_Type> : public NMib::NTraits::TCCompileTimeConstant<bool, d_HasRefCount>\
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

			template <typename t_CType, CSharedPointerOptionUnderlaying t_Options, bint t_bHasRefCount = TCHasIntrusiveRefcount<typename NTraits::TCRemoveQualifiers<t_CType>::CType>::mc_Value>
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
			
			template <CSharedPointerOptionUnderlaying t_Options, bint t_bHasRefCount>
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
				typedef NMem::CDefaultAllocator CAllocator;
				enum
				{
					mc_bSupportWeak = false
				};
			};
			
			template <typename t_CFirst, typename... tp_CParams>
			struct TCParseSharedPointerOptions<t_CFirst, tp_CParams...>
			{
				typedef TCParseSharedPointerOptions<tp_CParams...> CParent;
				typedef t_CFirst CAllocator;
				enum
				{
					mc_bSupportWeak = CParent::mc_bSupportWeak
				};
			};

			template <typename... tp_CParams>
			struct TCParseSharedPointerOptions<CSupportWeakTag, tp_CParams...>
			{
				typedef TCParseSharedPointerOptions<tp_CParams...> CParent;
				typedef typename CParent::CAllocator CAllocator;
				enum
				{
					mc_bSupportWeak = true
				};
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

		template <typename tf_CObjectType, typename tf_CAllocator>
		void fg_DeleteWeakObject(tf_CAllocator &&_Allocator, tf_CObjectType *_pObject)
		{
			static_assert(sizeof(tf_CObjectType) > 0, "");
			static_assert(!NTraits::TCIsAbstract<tf_CObjectType>::mc_Value || NTraits::TCHasVirtualDestructor<tf_CObjectType>::mc_Value, "");
			_pObject->~tf_CObjectType();
			if (_pObject->f_WeakRefCountDecrease() == 0)
				fg_Forward<tf_CAllocator>(_Allocator).f_Free(_pObject);
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

			enum
			{
				mc_bSupportWeak = COptions::mc_bSupportWeak
			};

			
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
					_pPtr->f_RefCountIncrease();
				m_Data.m_pPointTo = _pPtr;
			}
			void fp_SetInit(CInternalData *_pPtr)
			{
				if (_pPtr)
					_pPtr->f_RefCountIncrease();
				m_Data.m_pPointTo = _pPtr;
			}
			
			void fp_SetConstruct(CInternalData *_pPtr)
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
					if (m_Data.m_pPointTo->f_RefCountDecrease() == 0)
					{
						auto Cleanup
							= g_OnScopeExit > [&]()
							{
								// Protect against exception in destructor
								m_Data.m_pPointTo->f_RefCountIncrease();
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
					if (m_Data.m_pPointTo->f_RefCountDecrease() == 0)
					{
						auto Cleanup
							= g_OnScopeExit > [&]()
							{
								// Protect against exception in destructor
								m_Data.m_pPointTo->f_RefCountIncrease();
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
				static_assert((NTraits::TCIsSame<typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator, CAllocator>::mc_Value), "");
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
				m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
				_Other.m_Data.m_pPointTo = nullptr;
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
			typename TCEnableIf
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
			typename TCEnableIf
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
				m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
				_Other.m_Data.m_pPointTo = nullptr;
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
				static_assert((NTraits::TCIsSame<typename TCSharedPointer<tf_CType, tfp_COptions...>::CAllocator, CAllocator>::mc_Value), "");
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

			bint f_IsEmpty() const
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
					_pPtr->f_WeakRefCountIncrease();
				m_Data.m_pPointTo = _pPtr;
			}

			void fp_SetInit(CInternalData *_pPtr)
			{
				if (_pPtr)
					_pPtr->f_WeakRefCountIncrease();
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
				if (m_Data.m_pPointTo)
				{
					if (m_Data.m_pPointTo->f_WeakRefCountDecrease() == 0)
					{
						fp_GetAllocator().f_Free(m_Data.m_pPointTo);
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
				
				if (!pData->f_RefCountIncreaseWhileNot(-1))
					return pReturn;
				
				pReturn.fp_SetConstruct(pData);
				
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

			bint f_IsEmpty() const
			{
				return m_Data.m_pPointTo == nullptr;
			}

			inline_small explicit operator bool() const
			{
				return !f_IsEmpty();
			}
		};

		template <typename tf_CLeft, typename tf_CType, typename... tfp_COptions>
		bool operator == (tf_CLeft *_pLeft, const TCSharedPointer<tf_CType, tfp_COptions...> &_pRight)
		{
			return _pLeft == _pRight.f_Get();
		}

		template <typename tf_CType, typename... tfp_COptions>
		bool operator == (CNullPtr _pLeft, const TCSharedPointer<tf_CType, tfp_COptions...> &_pRight)
		{
			return _pLeft == _pRight.f_Get();
		}

		template <typename tf_CLeft, typename tf_CType, typename... tfp_COptions>
		bool operator < (tf_CLeft _pLeft, const TCSharedPointer<tf_CType, tfp_COptions...> &_pRight)
		{
			return _pLeft < _pRight.f_Get();
		}

		template <typename tf_CType, typename... tfp_COptions>
		bool operator < (CNullPtr _pLeft, const TCSharedPointer<tf_CType, tfp_COptions...> &_pRight)
		{
			return _pLeft < _pRight.f_Get();
		}
	}
}

#ifndef DMibPNoShortCuts
using namespace NMib::NPtr;
#endif

