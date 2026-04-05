// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

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
						NTraits::cHasVirtualDestructor<t_CType0>
						&& NTraits::cIsBaseOf<t_CType1, t_CType0>
						&& NTraits::cIsConvertible<t_CType1 *, t_CType0 *>
					)
					|| NTraits::cIsSame<t_CType1, t_CType0>
					|| NTraits::cIsSame<t_CType1, NTraits::TCRemoveQualifiers<t_CType0>>
				)
				&& NTraits::cIsSame<t_CAllocator0, t_CAllocator1>
			};
		};
	}


	template <typename t_CType, typename t_CAllocator>
	void fg_Tag_UniquePointer(t_CType const volatile &_Type, t_CAllocator const volatile &_Allocator);

	namespace NPrivate
	{
		template <typename t_CType, typename t_CAllocator>
		struct TCUniquePointerTag
		{
			using CType = decltype(fg_Tag_UniquePointer(fg_GetReference<t_CType>(), fg_GetReference<t_CAllocator>()));
		};

		template <typename t_CEnableIf, typename... tp_CParams>
		struct TCParseUniquePointerOptions;

		template <>
		struct TCParseUniquePointerOptions<void>
		{
			using CAllocator = NMemory::CDefaultAllocator;
			using CTag = void;
		};


		template <typename t_CFirst, typename... tp_CParams>
		struct TCParseUniquePointerOptions<TCEnableIf<NTraits::cIsBaseOf<t_CFirst, NMemory::CAllocator_Base>>, t_CFirst, tp_CParams...>
		{
			using CParent = TCParseUniquePointerOptions<void, tp_CParams...>;
			using CAllocator = t_CFirst;
			using CTag = typename CParent::CTag;
		};

		template <typename t_CFirst, typename... tp_CParams>
		struct TCParseUniquePointerOptions<TCEnableIf<!NTraits::cIsBaseOf<t_CFirst, NMemory::CAllocator_Base>>, t_CFirst, tp_CParams...>
		{
			using CParent = TCParseUniquePointerOptions<void, tp_CParams...>;
			using CAllocator = typename CParent::CAllocator;
			using CTag = t_CFirst;
		};
	}

	template
	<
		typename t_CType
		, typename ...tp_COptions
	>
	class TCUniquePointer
	{
		template <typename t_CType2, typename ...tp_COptions2> friend class TCUniquePointer;

		using CParsedOptions = NPrivate::TCParseUniquePointerOptions<void, tp_COptions...>;
	public:
		using CAllocator = typename CParsedOptions::CAllocator;
		using CTag = typename CParsedOptions::CTag;

	private:

		struct CData : public CAllocator
		{
		private:
			CData(CData const &_Other)
			{
			}
			CData(CData &&_Other)
			{
			}
		public:
			t_CType *m_pPointTo;

			CData()
			{
			}

			CData(CAllocator const &_Other)
				: CAllocator(_Other)
			{
			}
			CData(CAllocator &&_Other)
				: CAllocator(fg_Move(_Other))
			{
			}

			template <typename t_CParam0>
			CData(t_CParam0 &&_Other)
				: CAllocator(fg_Forward<t_CParam0>(_Other))
			{
			}
		};

		CData m_Data;

		CAllocator &fp_GetAllocator()
		{
			return m_Data;
		}

		CAllocator const &fp_GetAllocator() const
		{
			return m_Data;
		}

		template <typename t_CDummy>
		void fp_Delete()
		{
			if (m_Data.m_pPointTo)
			{
				fg_DeleteObject(fp_GetAllocator(), m_Data.m_pPointTo);
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
			static_assert(NTraits::cIsVoid<tf_CType> || NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, CAllocator>::mc_Value, "Not a valid conversion");
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
			static_assert(NTraits::cIsVoid<tf_CType> || NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, NTraits::TCRemoveReference<tf_CAllocator>>::mc_Value, "Not a valid conversion");
			m_Data.m_pPointTo = _CreateParams.template f_Create<t_CType>(fp_GetAllocator());
		}

		template <typename tf_CType, typename ...tfp_COptions>
		TCUniquePointer
		(
			TCUniquePointer<tf_CType, tfp_COptions...> &&_Other
		)
			: m_Data(fg_Move(_Other.fp_GetAllocator()))
		{
			static_assert(NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCUniquePointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value, "Not a valid conversion");
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
		mark_artificial mark_nodebug inline_always auto operator ->* (t_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf
			<
				NTraits::cIsMemberFunctionPointer<t_CMemberPtr>
				, NFunction::TCMemberFunctionBoundFunctor
				<
					t_CMemberPtr
					, t_CType *
				>
			>
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, (t_CType *)m_Data.m_pPointTo);
		}

		template <typename t_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (t_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf
			<
				NTraits::cIsMemberObjectPointer<t_CMemberPtr>
				, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>>
			>
		{
			return ((t_CType *)m_Data.m_pPointTo)->*_MemberPtr;
		}

		mark_nodebug NTraits::TCAddLValueReference<t_CType> operator *() const
			requires(!NTraits::cIsVoid<t_CType>)
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

		template <typename tf_CType, typename ...tfp_COptions>
		TCUniquePointer & operator = (TCUniquePointer<tf_CType, tfp_COptions...> &&_Other)
		{
			static_assert(NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCUniquePointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value, "Not a valid conversion");
			fp_Delete();
			fp_GetAllocator() = fg_Move(_Other.fp_GetAllocator());
			m_Data.m_pPointTo = _Other.f_Detach();
			return *this;
		}

		template <typename tf_CType, typename... tfp_CParams>
		TCUniquePointer &operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
		{
			static_assert(NTraits::cIsVoid<tf_CType> || NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, CAllocator>::mc_Value, "Not a valid conversion");
			fp_Delete();
			m_Data.m_pPointTo = _CreateParams.template f_Create<t_CType>(fp_GetAllocator());
			return *this;
		}

		void f_Clear()
		{
			fp_Delete();
		}

		template <typename tf_CType>
		bool operator == (tf_CType *_Other) const noexcept
		{
			return f_Get() == _Other;
		}

		bool operator == (CNullPtr _Other) const noexcept
		{
			return f_Get() == _Other;
		}

		template <typename tf_CType, typename ...tfp_COptions>
		bool operator == (const TCUniquePointer<tf_CType, tfp_COptions...> &_Other) const noexcept
		{
			return f_Get() == _Other.f_Get();
		}

		template <typename tf_CType>
		auto operator <=> (tf_CType *_Other) const noexcept
		{
			return f_Get() <=> _Other;
		}

		auto operator <=> (CNullPtr _Other) const noexcept
		{
			return f_Get() <=> _Other;
		}

		template <typename tf_CType, typename ...tfp_COptions>
		auto operator <=> (const TCUniquePointer<tf_CType, tfp_COptions...> &_Other) const noexcept
		{
			return f_Get() <=> _Other.f_Get();
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
}

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif
