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
			static constexpr bool mc_Value =
				(
					(NTraits::cHasVirtualDestructor<t_CType0> && NTraits::cIsBaseOf<t_CType1, t_CType0> && NTraits::cIsConvertible<t_CType1 *, t_CType0 *>)
					|| NTraits::cIsSame<t_CType1, t_CType0>
					|| NTraits::cIsSame<t_CType1, NTraits::TCRemoveQualifiers<t_CType0>>
				)
				&& NTraits::cIsSame<t_CAllocator0, t_CAllocator1>
			;
		};
	}

	template <typename tf_CType, typename tf_CAllocator>
	void fg_Tag_UniquePointer(tf_CType const volatile &_Type, tf_CAllocator const volatile &_Allocator);

	namespace NPrivate
	{
		template <typename t_CType, typename t_CAllocator>
		struct TCUniquePointerTag
		{
			using CType = decltype(fg_Tag_UniquePointer(fg_GetReference<t_CType>(), fg_GetReference<t_CAllocator>()));
		};

		template <typename t_CEnableIf, typename ...tp_CParams>
		struct TCParseUniquePointerOptions;

		template <>
		struct TCParseUniquePointerOptions<void>
		{
			using CAllocator = NMemory::CDefaultAllocator;
			using CTag = void;
		};

		template <typename t_CFirst, typename ...tp_CParams>
		struct TCParseUniquePointerOptions<TCEnableIf<NTraits::cIsBaseOf<t_CFirst, NMemory::CAllocator_Base>>, t_CFirst, tp_CParams...>
		{
			using CParent = TCParseUniquePointerOptions<void, tp_CParams...>;
			using CAllocator = t_CFirst;
			using CTag = typename CParent::CTag;
		};

		template <typename t_CFirst, typename ...tp_CParams>
		struct TCParseUniquePointerOptions<TCEnableIf<!NTraits::cIsBaseOf<t_CFirst, NMemory::CAllocator_Base>>, t_CFirst, tp_CParams...>
		{
			using CParent = TCParseUniquePointerOptions<void, tp_CParams...>;
			using CAllocator = typename CParent::CAllocator;
			using CTag = t_CFirst;
		};
	}

	template <typename t_CType, typename ...tp_COptions>
	struct TCUniquePointer
	{
	private:
		template <typename t_CType2, typename ...tp_COptions2> friend struct TCUniquePointer;

		using CParsedOptions = NPrivate::TCParseUniquePointerOptions<void, tp_COptions...>;

	public:
		using CAllocator = typename CParsedOptions::CAllocator;
		using CTag = typename CParsedOptions::CTag;

	private:
		struct CData : public CAllocator
		{
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

			template <typename tf_CParam0>
			CData(tf_CParam0 &&_Other)
				: CAllocator(fg_Forward<tf_CParam0>(_Other))
			{
			}

		private:
			CData(CData const &_Other)
			{
			}

			CData(CData &&_Other)
			{
			}
		};

		CData mp_Data;

		CAllocator &fp_GetAllocator()
		{
			return mp_Data;
		}

		CAllocator const &fp_GetAllocator() const
		{
			return mp_Data;
		}

		template <typename tf_CDummy>
		void fp_Delete()
		{
			if (mp_Data.m_pPointTo)
			{
				fg_DeleteObject(fp_GetAllocator(), mp_Data.m_pPointTo);
				mp_Data.m_pPointTo = nullptr;
			}
		}

		void fp_Delete()
		{
			fp_Delete<t_CType>();
		}

	private:
		// Disable copy construction

		TCUniquePointer(TCUniquePointer const &_pOther) = delete;
		TCUniquePointer &operator = (TCUniquePointer const &_pOther) = delete;

	public:
		TCUniquePointer()
		{
			mp_Data.m_pPointTo = nullptr;
		}

		~TCUniquePointer()
		{
			fp_Delete();
		}

		TCUniquePointer(TCCopy<TCUniquePointer> const &_Other)
			: mp_Data((*_Other).fp_GetAllocator())
		{
			mp_Data.m_pPointTo = fg_ConstructObject<t_CType>(fp_GetAllocator(), *((*_Other).mp_Data.m_pPointTo));
		}

		template <typename tf_CType>
		TCUniquePointer(TCExplicit<tf_CType> &&_Other)
		{
			mp_Data.m_pPointTo = *_Other;
		}

		template <typename tf_CType, typename tf_CAllocator>
		TCUniquePointer(TCExplicit<tf_CType> &&_Other, tf_CAllocator &&_Allocator)
			: mp_Data(fg_Forward<tf_CAllocator>(_Allocator))
		{
			mp_Data.m_pPointTo = *_Other;
		}

		template <typename tf_CType, typename ...tfp_CParams>
		TCUniquePointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
		{
			static_assert(NTraits::cIsVoid<tf_CType> || NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, CAllocator>::mc_Value, "Not a valid conversion");
			mp_Data.m_pPointTo = _CreateParams.template f_Create<t_CType>(fp_GetAllocator());
		}

		template <typename tf_CType, typename ...tfp_CParams, typename tf_CAllocator>
		TCUniquePointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams, tf_CAllocator &&_Allocator)
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

		template <typename tf_CType, typename ...tfp_COptions>
		TCUniquePointer(TCUniquePointer<tf_CType, tfp_COptions...> &&_pOther)
			requires (NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCUniquePointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value)
			: mp_Data(fg_Move(_pOther.fp_GetAllocator()))
		{
			mp_Data.m_pPointTo = _pOther.f_Detach();
		}

		TCUniquePointer(TCUniquePointer &&_pOther)
			: mp_Data(fg_Move(_pOther.fp_GetAllocator()))
		{
			mp_Data.m_pPointTo = _pOther.mp_Data.m_pPointTo;
			_pOther.mp_Data.m_pPointTo = nullptr;
		}

		explicit TCUniquePointer(t_CType *_pPtr)
		{
			mp_Data.m_pPointTo = _pPtr;
		}

		template <typename tf_CParam0>
		explicit TCUniquePointer(t_CType *_pPtr, tf_CParam0 &&_Param0)
			: mp_Data(fg_Forward<tf_CParam0>(_Param0))
		{
			mp_Data.m_pPointTo = _pPtr;
		}

		TCUniquePointer(CNullPtr _pNull)
		{
			mp_Data.m_pPointTo = nullptr;
		}

		t_CType *f_Detach()
		{
			t_CType *pRet = mp_Data.m_pPointTo;
			mp_Data.m_pPointTo = nullptr;
			return pRet;
		}

		t_CType *f_Get() const
		{
			return mp_Data.m_pPointTo;
		}

		t_CType *operator -> () const
		{
			return mp_Data.m_pPointTo;
		}

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>, NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *>>
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, (t_CType *)mp_Data.m_pPointTo);
		}

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const
			-> TCEnableIf<NTraits::cIsMemberObjectPointer<tf_CMemberPtr>, NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>>
		{
			return ((t_CType *)mp_Data.m_pPointTo)->*_MemberPtr;
		}

		mark_nodebug NTraits::TCAddLValueReference<t_CType> operator * () const
			requires (!NTraits::cIsVoid<t_CType>)
		{
			return *mp_Data.m_pPointTo;
		}

		template <typename tf_CType>
		TCUniquePointer &operator = (TCExplicit<tf_CType> &&_Other)
		{
			fp_Delete();
			mp_Data.m_pPointTo = *_Other;
			return *this;
		}

		TCUniquePointer &operator = (TCCopy<TCUniquePointer> const &_Other)
		{
			fp_Delete();
			fp_GetAllocator() = (*_Other).fp_GetAllocator();
			mp_Data.m_pPointTo = fg_ConstructObject<t_CType>(fp_GetAllocator(), *(*_Other).mp_Data.m_pPointTo);
			return *this;
		}

		TCUniquePointer &operator = (TCUniquePointer &&_pOther)
		{
			fp_Delete();
			fp_GetAllocator() = fg_Move(_pOther.fp_GetAllocator());
			mp_Data.m_pPointTo = _pOther.mp_Data.m_pPointTo;
			_pOther.mp_Data.m_pPointTo = nullptr;
			return *this;
		}

		TCUniquePointer &operator = (CNullPtr _pNull)
		{
			fp_Delete();
			mp_Data.m_pPointTo = nullptr;
			return *this;
		}

		template <typename tf_CType, typename ...tfp_COptions>
		TCUniquePointer &operator = (TCUniquePointer<tf_CType, tfp_COptions...> &&_pOther)
			requires (NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCUniquePointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value)
		{
			fp_Delete();
			fp_GetAllocator() = fg_Move(_pOther.fp_GetAllocator());
			mp_Data.m_pPointTo = _pOther.f_Detach();
			return *this;
		}

		template <typename tf_CType, typename ...tfp_CParams>
		TCUniquePointer &operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
		{
			static_assert(NTraits::cIsVoid<tf_CType> || NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, CAllocator>::mc_Value, "Not a valid conversion");
			fp_Delete();
			mp_Data.m_pPointTo = _CreateParams.template f_Create<t_CType>(fp_GetAllocator());
			return *this;
		}

		void f_Clear()
		{
			fp_Delete();
		}

		template <typename tf_CType>
		bool operator == (tf_CType *_pOther) const noexcept
		{
			return f_Get() == _pOther;
		}

		bool operator == (CNullPtr _pOther) const noexcept
		{
			return f_Get() == _pOther;
		}

		template <typename tf_CType, typename ...tfp_COptions>
		bool operator == (TCUniquePointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept
		{
			return f_Get() == _pOther.f_Get();
		}

		template <typename tf_CType>
		auto operator <=> (tf_CType *_pOther) const noexcept
		{
			return f_Get() <=> _pOther;
		}

		auto operator <=> (CNullPtr _pOther) const noexcept
		{
			return f_Get() <=> _pOther;
		}

		template <typename tf_CType, typename ...tfp_COptions>
		auto operator <=> (TCUniquePointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept
		{
			return f_Get() <=> _pOther.f_Get();
		}

		bool f_IsEmpty() const
		{
			return mp_Data.m_pPointTo == nullptr;
		}

		inline_small explicit operator bool () const
		{
			return !f_IsEmpty();
		}
	};
}

#ifndef DMibPNoShortCuts
using namespace NMib::NStorage;
#endif
