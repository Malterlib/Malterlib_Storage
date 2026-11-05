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

		// Declared before the public section, which uses it.
		using CParsedOptions = NPrivate::TCParseUniquePointerOptions<void, tp_COptions...>;

	public: // NOLINT(malterlib-member-order): The public declarations use CParsedOptions.
		using CAllocator = typename CParsedOptions::CAllocator;
		using CTag = typename CParsedOptions::CTag;

		TCUniquePointer();
		~TCUniquePointer();

		TCUniquePointer(TCCopy<TCUniquePointer> const &_Other);
		template <typename tf_CType>
		TCUniquePointer(TCExplicit<tf_CType> &&_Other);
		template <typename tf_CType, typename tf_CAllocator>
		TCUniquePointer(TCExplicit<tf_CType> &&_Other, tf_CAllocator &&_Allocator);

		template <typename tf_CType, typename ...tfp_CParams>
		TCUniquePointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams);
		template <typename tf_CType, typename ...tfp_CParams, typename tf_CAllocator>
		TCUniquePointer(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams, tf_CAllocator &&_Allocator);

		template <typename tf_CType, typename ...tfp_COptions>
		TCUniquePointer(TCUniquePointer<tf_CType, tfp_COptions...> &&_pOther)
			requires (NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCUniquePointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value)
		;

		TCUniquePointer(TCUniquePointer &&_pOther);
		explicit TCUniquePointer(t_CType *_pPtr);
		template <typename tf_CParam0>
		explicit TCUniquePointer(t_CType *_pPtr, tf_CParam0 &&_Param0);
		TCUniquePointer(CNullPtr _pNull);

		t_CType *f_Detach();

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

		mark_nodebug NTraits::TCAddLValueReference<t_CType> operator * () const
			requires (!NTraits::cIsVoid<t_CType>)
		;

		template <typename tf_CType>
		TCUniquePointer &operator = (TCExplicit<tf_CType> &&_Other);
		TCUniquePointer &operator = (TCCopy<TCUniquePointer> const &_Other);
		TCUniquePointer &operator = (TCUniquePointer &&_pOther);
		TCUniquePointer &operator = (CNullPtr _pNull);

		template <typename tf_CType, typename ...tfp_COptions>
		TCUniquePointer &operator = (TCUniquePointer<tf_CType, tfp_COptions...> &&_pOther)
			requires (NPrivate::TCIsValidConversion<t_CType, tf_CType, CAllocator, typename TCUniquePointer<tf_CType, tfp_COptions...>::CAllocator>::mc_Value)
		;

		template <typename tf_CType, typename ...tfp_CParams>
		TCUniquePointer &operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams);

		void f_Clear();

		template <typename tf_CType>
		bool operator == (tf_CType *_pOther) const noexcept;
		bool operator == (CNullPtr _pOther) const noexcept;
		template <typename tf_CType, typename ...tfp_COptions>
		bool operator == (TCUniquePointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept;

		template <typename tf_CType>
		auto operator <=> (tf_CType *_pOther) const noexcept;
		auto operator <=> (CNullPtr _pOther) const noexcept;
		template <typename tf_CType, typename ...tfp_COptions>
		auto operator <=> (TCUniquePointer<tf_CType, tfp_COptions...> const &_pOther) const noexcept;

		bool f_IsEmpty() const;
		inline_small explicit operator bool () const;

	private:
		struct CData : public CAllocator
		{
			CData();
			CData(CAllocator const &_Other);
			CData(CAllocator &&_Other);
			template <typename tf_CParam0>
			CData(tf_CParam0 &&_Other);

			t_CType *m_pPointTo;

		private:
			CData(CData const &_Other);
			CData(CData &&_Other);
		};

		// Disable copy construction

		TCUniquePointer(TCUniquePointer const &_pOther) = delete;

		CAllocator &fp_GetAllocator();
		CAllocator const &fp_GetAllocator() const;

		template <typename tf_CDummy>
		void fp_Delete();
		void fp_Delete();

		TCUniquePointer &operator = (TCUniquePointer const &_pOther) = delete;

		CData mp_Data;
	};
}

#include "Malterlib_Storage_UniquePointer.hpp"

#ifndef DMibPNoShortCuts
using namespace NMib::NStorage;
#endif
