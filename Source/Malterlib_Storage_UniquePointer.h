// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Function/BindMemberFunction>

namespace NMib::NStorage
{
	namespace NPrivate
	{
		template <typename t_CType0, typename t_CType1, typename t_CAllocator0, typename t_CAllocator1>
		struct TCIsValidConversion
		{
			enum
			{
				mc_Value
				=
				(
					(
						NTraits::TCHasVirtualDestructor<t_CType0>::mc_Value
						&& NTraits::TCIsBaseOf<t_CType1, t_CType0>::mc_Value
					)
					|| NTraits::TCIsSame<t_CType1, t_CType0>::mc_Value
					|| NTraits::TCIsSame<t_CType1, typename NTraits::TCRemoveQualifiers<t_CType0>::CType>::mc_Value
				)
				&& NTraits::TCIsSame<t_CAllocator0, t_CAllocator1>::mc_Value
			};
		};
	}


	template <typename t_CType, typename t_CAllocator, typename t_CPtr>
	void fg_Tag_UniquePointer(t_CType const volatile &_Type, t_CAllocator const volatile &_Allocator, t_CPtr const volatile &_Ptr);

	namespace NPrivate
	{
		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		struct TCUniquePointerTag
		{
			typedef decltype(fg_Tag_UniquePointer(fg_GetReference<t_CType>(), fg_GetReference<t_CAllocator>(), fg_GetReference<t_CPtr>())) CType;
		};

	}

	template
	<
		typename t_CType
		, typename t_CAllocator = NMib::NMemory::CDefaultAllocator
		, typename t_CPtr = TCDynamicPtr<typename t_CAllocator::CPtrHolder, t_CType>
		, typename t_CTag = typename NPrivate::TCUniquePointerTag<t_CType, t_CAllocator, t_CPtr>::CType
	>
	class TCUniquePointer
	{
		template <typename t_CType2, typename t_CAllocator2, typename t_CPtr2, typename t_CTag2> friend class TCUniquePointer;


		struct CData : public t_CAllocator
		{
		private:
			CData(CData const &_Other)
			{
			}
			CData(CData &&_Other)
			{
			}
		public:
			t_CPtr m_pPointTo;

			CData()
			{
			}

			CData(t_CAllocator const &_Other)
				: t_CAllocator(_Other)
			{
			}
			CData(t_CAllocator &&_Other)
				: t_CAllocator(fg_Move(_Other))
			{
			}

			template <typename t_CParam0>
			CData(t_CParam0 &&_Other)
				: t_CAllocator(fg_Forward<t_CParam0>(_Other))
			{
			}
		};

		CData m_Data;

		t_CAllocator &fp_GetAllocator()
		{
			return m_Data;
		}

		t_CAllocator const &fp_GetAllocator() const
		{
			return m_Data;
		}

		template <typename t_CDummy>
		void fp_Delete()
		{
			if (m_Data.m_pPointTo)
			{
				fg_DeleteObject(fp_GetAllocator(), (t_CType *)m_Data.m_pPointTo);
				m_Data.m_pPointTo = nullptr;
			}
		}

		void fp_Delete()
		{
			fp_Delete<t_CType>();
		}

	private:
		// Disable copy construction

		TCUniquePointer(TCUniquePointer const &_Other) = delete;
		TCUniquePointer &operator = (TCUniquePointer const &_Other) = delete;

	public:
		TCUniquePointer()
		{
			m_Data.m_pPointTo = nullptr;
		}
		~TCUniquePointer()
		{
			fp_Delete();
		}

		TCUniquePointer(TCCopy<TCUniquePointer> const &_Other)
			: m_Data((*_Other).fp_GetAllocator())
		{
			m_Data.m_pPointTo = fg_ConstructObject<t_CType>(fp_GetAllocator(), *((*_Other).m_Data.m_pPointTo));
		}

		template <typename tf_CType>
		TCUniquePointer(TCExplicit<tf_CType> &&_Other)
		{
			m_Data.m_pPointTo = *_Other;
		}

		template <typename tf_CType, typename tf_CAllocator>
		TCUniquePointer(TCExplicit<tf_CType> &&_Other, tf_CAllocator &&_Allocator)
			: m_Data(fg_Forward<tf_CAllocator>(_Allocator))
		{
			m_Data.m_pPointTo = *_Other;
		}

		template <typename tf_CType, typename... tfp_CParams>
		TCUniquePointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
		{
			static_assert(NTraits::TCIsVoid<tf_CType>::mc_Value || NPrivate::TCIsValidConversion<t_CType, tf_CType, t_CAllocator, t_CAllocator>::mc_Value, "Not a valid conversion");
			m_Data.m_pPointTo = _CreateParams.template f_Create<t_CType>(fp_GetAllocator());
		}

		template
		<
			typename tf_CType
			, typename... tfp_CParams
			, typename tf_CAllocator
		>
		TCUniquePointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams, tf_CAllocator &&_Allocator)
			: m_Data(fg_Forward<tf_CAllocator>(_Allocator))
		{
			static_assert(NTraits::TCIsVoid<tf_CType>::mc_Value || NPrivate::TCIsValidConversion<t_CType, tf_CType, t_CAllocator, typename NTraits::TCRemoveReference<tf_CAllocator>::CType>::mc_Value, "Not a valid conversion");
			m_Data.m_pPointTo = _CreateParams.template f_Create<t_CType>(fp_GetAllocator());
		}

		template <typename t_CType2, typename t_CAllocator2, typename t_CPtr2, typename t_CTag2>
		TCUniquePointer
		(
			TCUniquePointer<t_CType2, t_CAllocator2, t_CPtr2, t_CTag2> &&_Other
		)
			: m_Data(fg_Move(_Other.fp_GetAllocator()))
		{
			static_assert(NPrivate::TCIsValidConversion<t_CType, t_CType2, t_CAllocator, t_CAllocator2>::mc_Value, "Not a valid conversion");
			m_Data.m_pPointTo = _Other.f_Detach();
		}

		TCUniquePointer(TCUniquePointer &&_Other)
			: m_Data(fg_Move(_Other.fp_GetAllocator()))
		{
			m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
			_Other.m_Data.m_pPointTo = nullptr;
		}

		explicit TCUniquePointer(t_CType *_pPtr)
		{
			m_Data.m_pPointTo = _pPtr;
		}

		template <typename t_CParam0>
		explicit TCUniquePointer(t_CType *_pPtr, t_CParam0 &&_Param0)
			: m_Data(fg_Forward<t_CParam0>(_Param0))
		{
			m_Data.m_pPointTo = _pPtr;
		}

		TCUniquePointer(CNullPtr)
		{
			m_Data.m_pPointTo = nullptr;
		}

		t_CType *f_Detach()
		{
			t_CType *pRet = m_Data.m_pPointTo;
			m_Data.m_pPointTo = nullptr;
			return pRet;
		}

		t_CType *f_Get() const
		{
			return m_Data.m_pPointTo;
		}

		t_CType *operator ->() const
		{
			return m_Data.m_pPointTo;
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
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, (t_CType *)m_Data.m_pPointTo);
		}

		template <typename t_CMemberPtr>
		typename TCEnableIf
			<
				NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
				, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
			>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return ((t_CType *)m_Data.m_pPointTo)->*_MemberPtr;
		}

		t_CType &operator *() const
		{
			return *m_Data.m_pPointTo;
		}


		template <typename tf_CType>
		TCUniquePointer &operator = (TCExplicit<tf_CType> &&_Other)
		{
			fp_Delete();
			m_Data.m_pPointTo = *_Other;
			return *this;
		}

		TCUniquePointer & operator = (TCCopy<TCUniquePointer> const &_Other)
		{
			fp_Delete();
			fp_GetAllocator() = (*_Other).fp_GetAllocator();
			m_Data.m_pPointTo = fg_ConstructObject<t_CType>(fp_GetAllocator(), *(*_Other).m_Data.m_pPointTo);
			return *this;
		}

		TCUniquePointer & operator = (TCUniquePointer &&_Other)
		{
			fp_Delete();
			fp_GetAllocator() = fg_Move(_Other.fp_GetAllocator());
			m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
			_Other.m_Data.m_pPointTo = nullptr;
			return *this;
		}
		TCUniquePointer & operator = (CNullPtr)
		{
			fp_Delete();
			m_Data.m_pPointTo = nullptr;
			return *this;
		}

		template <typename t_CType2, typename t_CAllocator2, typename t_CPtr2, typename t_CTag2>
		TCUniquePointer & operator = (TCUniquePointer<t_CType2, t_CAllocator2, t_CPtr2, t_CTag2> &&_Other)
		{
			static_assert(NPrivate::TCIsValidConversion<t_CType, t_CType2, t_CAllocator, t_CAllocator2>::mc_Value, "Not a valid conversion");
			fp_Delete();
			fp_GetAllocator() = fg_Move(_Other.fp_GetAllocator());
			m_Data.m_pPointTo = _Other.f_Detach();
			return *this;
		}

		template <typename tf_CType, typename... tfp_CParams>
		TCUniquePointer &operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
		{
			static_assert(NTraits::TCIsVoid<tf_CType>::mc_Value || NPrivate::TCIsValidConversion<t_CType, tf_CType, t_CAllocator, t_CAllocator>::mc_Value, "Not a valid conversion");
			fp_Delete();
			m_Data.m_pPointTo = _CreateParams.template f_Create<t_CType>(fp_GetAllocator());
			return *this;
		}

		void f_Clear()
		{
			fp_Delete();
		}

		template <typename tf_CType>
		bint operator == (tf_CType *_Other) const
		{
			return f_Get() == _Other;
		}

		bint operator == (CNullPtr _Other) const
		{
			return f_Get() == _Other;
		}

		template <typename tf_CType1, typename tf_CAllocator1, typename tf_CPtr1, typename tf_CTag1>
		bint operator == (const TCUniquePointer<tf_CType1, tf_CAllocator1, tf_CPtr1, tf_CTag1> &_Other) const
		{
			return f_Get() == _Other.f_Get();
		}

		template <typename tf_CType>
		bint operator < (tf_CType *_Other) const
		{
			return f_Get() < _Other;
		}

		bint operator < (CNullPtr _Other) const
		{
			return f_Get() < _Other;
		}

		template <typename tf_CType1, typename tf_CAllocator1, typename tf_CPtr1, typename tf_CTag1>
		bint operator < (const TCUniquePointer<tf_CType1, tf_CAllocator1, tf_CPtr1, tf_CTag1> &_Other) const
		{
			return f_Get() < _Other.f_Get();
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


	template <typename tf_CLeft, typename tf_CType, typename tf_CAllocator, typename tf_CPtr, typename tf_CTag>
	bool operator == (tf_CLeft *_pLeft, const TCUniquePointer<tf_CType, tf_CAllocator, tf_CPtr, tf_CTag> &_pRight)
	{
		return _pLeft == _pRight.f_Get();
	}

	template <typename tf_CType, typename tf_CAllocator, typename tf_CPtr, typename tf_CTag>
	bool operator == (CNullPtr _pLeft, const TCUniquePointer<tf_CType, tf_CAllocator, tf_CPtr, tf_CTag> &_pRight)
	{
		return _pLeft == _pRight.f_Get();
	}

	template <typename tf_CLeft, typename tf_CType, typename tf_CAllocator, typename tf_CPtr, typename tf_CTag>
	bool operator < (tf_CLeft *_pLeft, const TCUniquePointer<tf_CType, tf_CAllocator, tf_CPtr, tf_CTag> &_pRight)
	{
		return _pLeft < _pRight.f_Get();
	}

	template <typename tf_CType, typename tf_CAllocator, typename tf_CPtr, typename tf_CTag>
	bool operator < (CNullPtr _pLeft, const TCUniquePointer<tf_CType, tf_CAllocator, tf_CPtr, tf_CTag> &_pRight)
	{
		return _pLeft < _pRight.f_Get();
	}
}

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif
