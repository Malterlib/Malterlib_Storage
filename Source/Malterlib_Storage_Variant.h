// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>
#include <Mib/Contract/Contract>

namespace NMib
{
	template <typename tf_CVisitor, typename tf_CToVisit0>
	void fg_Visit(tf_CVisitor &&_Visitor, tf_CToVisit0 &&_ToVisit0) noexcept(noexcept(fg_Forward<tf_CToVisit0>(_ToVisit0).f_Visit(fg_Forward<tf_CVisitor>(_Visitor))));

	template <typename tf_CReturn, typename tf_CVisitor, typename tf_CToVisit0>
	auto fg_VisitRet(tf_CVisitor &&_Visitor, tf_CToVisit0 &&_ToVisit0)
		noexcept(noexcept(fg_Forward<tf_CToVisit0>(_ToVisit0).template f_VisitRet<tf_CReturn>(fg_Forward<tf_CVisitor>(_Visitor))))
		-> tf_CReturn
	;

	template <typename t_CRet, typename t_CVisitor, typename t_CToVisit>
	struct TCInnerVisitor
	{
		TCInnerVisitor(t_CVisitor _Visitor, t_CToVisit _ToVisit);

		template <typename t_CInnerVisitor, typename t_CValue>
		struct TCValueVisitor
		{
			TCValueVisitor(t_CInnerVisitor _Visitor, t_CValue _Value);

			template <typename tf_CType>
			t_CRet operator () (tf_CType &&_Type) noexcept(noexcept(m_Visitor(fg_Forward<t_CValue>(m_Value), fg_Forward<tf_CType>(_Type))));

			t_CInnerVisitor m_Visitor;
			t_CValue m_Value;
		};

		template <typename tf_CType>
		t_CRet operator () (tf_CType &&_Value) noexcept(noexcept(fg_VisitRet<t_CRet>(TCValueVisitor<t_CVisitor, tf_CType>(m_Visitor, _Value), fg_Forward<t_CToVisit>(m_ToVisit))));

		t_CVisitor m_Visitor;
		t_CToVisit m_ToVisit;
	};

	template <typename t_CVisitor, typename t_CToVisit>
	struct TCInnerVisitor<void, t_CVisitor, t_CToVisit>
	{
		TCInnerVisitor(t_CVisitor _Visitor, t_CToVisit _ToVisit);

		template <typename t_CInnerVisitor, typename t_CValue>
		struct TCValueVisitor
		{
			TCValueVisitor(t_CInnerVisitor _Visitor, t_CValue _Value);

			template <typename tf_CType>
			void operator () (tf_CType &&_Type) noexcept(noexcept(m_Visitor(fg_Forward<t_CValue>(m_Value), fg_Forward<tf_CType>(_Type))));

			t_CInnerVisitor m_Visitor;
			t_CValue m_Value;
		};

		template <typename tf_CType>
		void operator () (tf_CType &&_Value) noexcept(noexcept(fg_Visit(TCValueVisitor<t_CVisitor, tf_CType>(m_Visitor, _Value), fg_Forward<t_CToVisit>(m_ToVisit))));

		t_CVisitor m_Visitor;
		t_CToVisit m_ToVisit;
	};

	template <typename tf_CVisitor, typename tf_CToVisit0, typename tf_CToVisit1>
	void fg_Visit(tf_CVisitor &&_Visitor, tf_CToVisit0 &&_ToVisit0, tf_CToVisit1 &&_ToVisit1)
		noexcept(noexcept(fg_Visit(TCInnerVisitor<void, tf_CVisitor, tf_CToVisit1>(_Visitor, _ToVisit1), _ToVisit0)))
	;

	template <typename tf_CRet, typename tf_CVisitor, typename tf_CToVisit0, typename tf_CToVisit1>
	auto fg_VisitRet(tf_CVisitor &&_Visitor, tf_CToVisit0 &&_ToVisit0, tf_CToVisit1 &&_ToVisit1)
		noexcept(noexcept(fg_VisitRet<tf_CRet>(TCInnerVisitor<tf_CRet, tf_CVisitor, tf_CToVisit1>(_Visitor, _ToVisit1), _ToVisit0)))
		-> tf_CRet
	;
}

namespace NMib::NStorage
{
	template <typename t_CIndex, typename ...tp_CMembers>
	struct TCVariantCommon;

	template <typename ...tp_CTypes>
	struct TCVariant;

#ifdef DCompiler_MSVC_Workaround
#	define DMibStorageVariantTypeInMember(...) __VA_ARGS__
#else
#	define DMibStorageVariantTypeInMember(...)
#endif

	namespace NPrivate
	{
		template <typename t_CType>
		struct TCGetRefType
		{
			using CType = t_CType const &;
		};

		template <>
		struct TCGetRefType<void>
		{
			using CType = CVoidTag const &;
		};

		template <typename tf_CType>
		constexpr typename TCGetRefType<tf_CType>::CType fg_GetTypeRefOrVoidTag() noexcept;

		struct CCompareVariant_Spaceship
		{
			template <typename tf_CLeft, typename tf_CRight>
			COrdering_Strong operator () (tf_CLeft const &_Left, tf_CRight const &_Right) const noexcept;

			template <typename tf_CSame>
			auto operator () (tf_CSame const &_Left, tf_CSame const &_Right) const noexcept(noexcept(_Left <=> _Right));
		};

		struct CCompareVariant_Equal
		{
			template <typename tf_CLeft, typename tf_CRight>
			bool operator () (tf_CLeft const &_Left, tf_CRight const &_Right) const noexcept;

			template <typename tf_CSame>
			bool operator () (tf_CSame const &_Left, tf_CSame const &_Right) const noexcept(noexcept(_Left <=> _Right));
		};

		struct CVariantVisitor_Destruct
		{
			void operator () (CVoidTag _Tag);

			template <typename tf_CType>
			void operator () (tf_CType &_Type);
		};

		struct CDummy
		{
			CDummy() = delete;
			~CDummy() = delete;
		};

		template <typename tf_CReturn>
		function_does_not_return inline_never TCEnableIf<!NTraits::cIsVoid<tf_CReturn>, tf_CReturn &> fg_InvalidVariant();

		template <typename tf_CReturn>
		function_does_not_return inline_never TCEnableIf<NTraits::cIsVoid<tf_CReturn>, void> fg_InvalidVariant();

		template <typename t_CType>
		struct TCIsVariant
		{
			static constexpr bool mc_Value = false;
		};

		template <typename t_CIndex, typename ...tp_CMembers>
		struct TCIsVariant<TCVariantCommon<t_CIndex, tp_CMembers...>>
		{
			static constexpr bool mc_Value = true;
		};

		template <typename ...tp_CTypes>
		struct TCIsVariant<TCVariant<tp_CTypes...>>
		{
			static constexpr bool mc_Value = true;
		};
	}

	template <typename t_CIndex, typename ...tp_CMembers>
	struct TCVariantCommon
	{
		static_assert(NTraits::cIsSame<t_CIndex, NPrivate::CDummy>, "Mismatched index type and member index types");
	};

	template <typename t_CIndex, typename t_CType, t_CIndex t_Member>
	struct TCVariantMember
	{
		using CType = t_CType;
		static constexpr t_CIndex mc_Member = t_Member;

#ifdef DDebugger_VisualStudio
		static constexpr bool mc_bDebugIsVoid = NTraits::cIsVoid<CType>;
		using CDebugType = TCConditional<mc_bDebugIsVoid, uint8, t_CType>;
#endif
	};

	template <typename t_CType, auto t_Member DMibStorageVariantTypeInMember(, typename t_CIndex = decltype(t_Member))>
	using TCMember = TCVariantMember<decltype(t_Member), t_CType, t_Member>;

	namespace NPrivate
	{
		template <typename t_CIndex, t_CIndex t_IndexToGet, typename ...tp_CMembers>
		struct TCGetMemberByIndex
		{
			using CType = NPrivate::CDummy;
		};

		template <typename t_CIndex, t_CIndex t_IndexToGet, typename t_CType0, t_CIndex t_Member0, typename ...tp_CMembers>
		struct TCGetMemberByIndex<t_CIndex, t_IndexToGet, TCVariantMember<t_CIndex, t_CType0, t_Member0>, tp_CMembers...>
			: public TCGetMemberByIndex<t_CIndex, t_IndexToGet, tp_CMembers...>
		{
		};

		template <typename t_CIndex, t_CIndex t_IndexToGet, typename t_CType0, typename ...tp_CMembers>
		struct TCGetMemberByIndex<t_CIndex, t_IndexToGet, TCVariantMember<t_CIndex, t_CType0, t_IndexToGet>, tp_CMembers...>
		{
			using CType = t_CType0;
		};

		template <typename t_CIndex, t_CIndex t_IndexToGet, typename t_CType0>
		struct TCGetMemberByIndex<t_CIndex, t_IndexToGet, TCVariantMember<t_CIndex, t_CType0, t_IndexToGet>>
		{
			using CType = t_CType0;
		};

		template <typename t_CIndex, typename t_CTypeToGet, typename ...tp_CMembers>
		struct TCGetMemberByType;

		template <typename t_CIndex, typename t_CTypeToGet, typename t_CType0, t_CIndex t_Member0, typename ...tp_CMembers>
		struct TCGetMemberByType<t_CIndex, t_CTypeToGet, TCVariantMember<t_CIndex, t_CType0, t_Member0>, tp_CMembers...>
			: public TCGetMemberByType<t_CIndex, t_CTypeToGet, tp_CMembers...>
		{
		};

		template <typename t_CIndex, typename t_CTypeToGet, t_CIndex t_Member0, typename ...tp_CMembers>
		struct TCGetMemberByType<t_CIndex, t_CTypeToGet, TCVariantMember<t_CIndex, t_CTypeToGet, t_Member0>, tp_CMembers...>
		{
			static constexpr t_CIndex mc_Value = t_Member0;
		};

		template <typename t_CIndex, typename t_CTypeToGet, t_CIndex t_Member0>
		struct TCGetMemberByType<t_CIndex, t_CTypeToGet, TCVariantMember<t_CIndex, t_CTypeToGet, t_Member0>>
		{
			static constexpr t_CIndex mc_Value = t_Member0;
		};

		template <typename t_CIndex, typename t_CTypeToGet, typename t_CType0, t_CIndex t_Member0>
		struct TCGetMemberByType<t_CIndex, t_CTypeToGet, TCVariantMember<t_CIndex, t_CType0, t_Member0>>
		{
			static constexpr t_CIndex mc_Value = t_CIndex(-1);
		};

		template <typename t_CIndex, typename t_CTypeToGet>
		struct TCGetMemberByType<t_CIndex, t_CTypeToGet>
		{
			static constexpr t_CIndex mc_Value = t_CIndex(-1);
		};

		template <typename t_CIndex, t_CIndex ...tp_Indices>
		struct TCAllAreUniqueIndex
		{
			static constexpr bool mc_Value = true;
		};

		template <typename t_CIndex, t_CIndex t_Member0, t_CIndex t_Member1, t_CIndex ...tp_Indices>
		struct TCAllAreUniqueIndex<t_CIndex, t_Member0, t_Member1, tp_Indices...>
		{
			static constexpr bool mc_Value = t_Member0 != t_Member1 && ((t_Member0 != tp_Indices) && ...) && TCAllAreUniqueIndex<t_CIndex, t_Member1, tp_Indices...>::mc_Value;
		};

		template <typename t_CIndex, typename t_CEnable, typename ...tp_CMembers>
		struct TCFirstDefaultConstructible
		{
			static constexpr t_CIndex mc_Value = t_CIndex(-1);
		};

		template <typename t_CIndex, typename t_CType0, t_CIndex t_Member0, typename ...tp_CMembers>
		struct TCFirstDefaultConstructible
			<
				t_CIndex
				, NTraits::TCCompileTimeTrue<NTraits::cIsReference<t_CType0> || !NTraits::cIsConstructibleWith<t_CType0>>
				, TCVariantMember<t_CIndex, t_CType0, t_Member0>
				, tp_CMembers...
			>
			: public TCFirstDefaultConstructible<t_CIndex, NTraits::CCompileTimeTrue, tp_CMembers...>
		{
		};

		template <typename t_CIndex, typename t_CType0, t_CIndex t_Member0>
		struct TCFirstDefaultConstructible
			<
				t_CIndex
				, NTraits::TCCompileTimeTrue<NTraits::cIsReference<t_CType0> || !NTraits::cIsConstructibleWith<t_CType0>>
				, TCVariantMember<t_CIndex, t_CType0, t_Member0>
			>
			: public TCFirstDefaultConstructible<t_CIndex, NTraits::CCompileTimeTrue>
		{
		};

		template <typename t_CIndex, typename t_CType0, t_CIndex t_Member0, typename ...tp_CMembers>
		struct TCFirstDefaultConstructible
		<
			t_CIndex
			, NTraits::TCCompileTimeTrue<!NTraits::cIsReference<t_CType0> && NTraits::cIsConstructibleWith<t_CType0>>
			, TCVariantMember<t_CIndex, t_CType0, t_Member0>
			, tp_CMembers...
		>
		{
			static constexpr t_CIndex mc_Value = t_Member0;
		};

		template <typename t_CIndex, typename t_CType0, t_CIndex t_Member0>
		struct TCFirstDefaultConstructible
		<
			t_CIndex
			, NTraits::TCCompileTimeTrue<!NTraits::cIsReference<t_CType0> && NTraits::cIsConstructibleWith<t_CType0>>
			, TCVariantMember<t_CIndex, t_CType0, t_Member0>
		>
		{
			static constexpr t_CIndex mc_Value = t_Member0;
		};

		template <typename t_CIndex, typename t_CEnable, typename ...tp_CMembers>
		struct TCFirstNothrowDefaultConstructible
		{
			static constexpr t_CIndex mc_Value = t_CIndex(-1);
		};

		template <typename t_CIndex, typename t_CType0, t_CIndex t_Member0, typename ...tp_CMembers>
		struct TCFirstNothrowDefaultConstructible
			<
				t_CIndex
				, NTraits::TCCompileTimeTrue
				<
					NTraits::cIsReference<t_CType0>
					|| !NTraits::cIsConstructibleWith<t_CType0>
					|| !NTraits::cIsNothrowDefaultConstructible<t_CType0>
				>
				, TCVariantMember<t_CIndex, t_CType0, t_Member0>
				, tp_CMembers...
			>
			: public TCFirstNothrowDefaultConstructible<t_CIndex, NTraits::CCompileTimeTrue, tp_CMembers...>
		{
		};

		template <typename t_CIndex, typename t_CType0, t_CIndex t_Member0>
		struct TCFirstNothrowDefaultConstructible
			<
				t_CIndex
				, NTraits::TCCompileTimeTrue
				<
					NTraits::cIsReference<t_CType0>
					|| !NTraits::cIsConstructibleWith<t_CType0>
					|| !NTraits::cIsNothrowDefaultConstructible<t_CType0>
				>
				, TCVariantMember<t_CIndex, t_CType0, t_Member0>
			>
			: public TCFirstNothrowDefaultConstructible<t_CIndex, NTraits::CCompileTimeTrue>
		{
		};

		template <typename t_CIndex, typename t_CType0, t_CIndex t_Member0, typename ...tp_CMembers>
		struct TCFirstNothrowDefaultConstructible
		<
			t_CIndex
			, NTraits::TCCompileTimeTrue<!NTraits::cIsReference<t_CType0> && NTraits::cIsConstructibleWith<t_CType0> && NTraits::cIsNothrowDefaultConstructible<t_CType0>>
			, TCVariantMember<t_CIndex, t_CType0, t_Member0>
			, tp_CMembers...
		>
		{
			static constexpr t_CIndex mc_Value = t_Member0;
		};

		template <typename t_CIndex, typename t_CType0, t_CIndex t_Member0>
		struct TCFirstNothrowDefaultConstructible
		<
			t_CIndex
			, NTraits::TCCompileTimeTrue<!NTraits::cIsReference<t_CType0> && NTraits::cIsConstructibleWith<t_CType0> && NTraits::cIsNothrowDefaultConstructible<t_CType0>>
			, TCVariantMember<t_CIndex, t_CType0, t_Member0>
		>
		{
			static constexpr t_CIndex mc_Value = t_Member0;
		};

		template <typename t_CIndex, typename t_FConstructorParams, typename t_CEnable, typename ...tp_CMembers>
		struct TCFirstConstructibleWith
		{
			static constexpr t_CIndex mc_Value = t_CIndex(-1);
		};

		template <typename t_CIndex, typename t_CReturn, typename ...tp_CConstructorParams, typename t_CType0, t_CIndex t_Member0, typename ...tp_CMembers>
		struct TCFirstConstructibleWith
			<
				t_CIndex
				, t_CReturn (tp_CConstructorParams ...p_ConstructorParams)
				, NTraits::TCCompileTimeTrue<!NTraits::cIsConstructibleWith<t_CType0, tp_CConstructorParams...>>
				, TCVariantMember<t_CIndex, t_CType0, t_Member0>
				, tp_CMembers...
			>
			: public TCFirstConstructibleWith<t_CIndex, t_CReturn (tp_CConstructorParams ...p_ConstructorParams), NTraits::CCompileTimeTrue, tp_CMembers...>
		{
		};

		template <typename t_CIndex, typename t_CReturn, typename ...tp_CConstructorParams, typename t_CType0, t_CIndex t_Member0, typename ...tp_CMembers>
		struct TCFirstConstructibleWith
		<
			t_CIndex
			, t_CReturn (tp_CConstructorParams ...p_ConstructorParams)
			, NTraits::TCCompileTimeTrue<NTraits::cIsConstructibleWith<t_CType0, tp_CConstructorParams...>>
			, TCVariantMember<t_CIndex, t_CType0, t_Member0>
			, tp_CMembers...
		>
		{
			static constexpr t_CIndex mc_Value = t_Member0;
		};

		template <typename t_CIndex, typename t_CReturn, typename ...tp_CConstructorParams, typename t_CType0, t_CIndex t_Member0>
		struct TCFirstConstructibleWith
		<
			t_CIndex
			, t_CReturn (tp_CConstructorParams ...p_ConstructorParams)
			, NTraits::TCCompileTimeTrue<NTraits::cIsConstructibleWith<t_CType0, tp_CConstructorParams...>>
			, TCVariantMember<t_CIndex, t_CType0, t_Member0>
		>
		{
			static constexpr t_CIndex mc_Value = t_Member0;
		};

		template <typename t_CType>
		struct TCCheckVariantContracts
		{
			static_assert(!NTraits::cIsUnboundedArray<t_CType>, "You cannot store an unbounded array in a variant");
			static_assert(!NTraits::cIsFunction<t_CType>, "You cannot store function types in a variant");
			static constexpr bool mc_Value = true;
		};

		template <typename t_CType>
		struct TCSizeOf
		{
			static constexpr umint mc_Value = sizeof(t_CType);
		};

		template <>
		struct TCSizeOf<void>
		{
			static constexpr umint mc_Value = 0;
		};

		template <typename t_CType>
		struct TCAlignOf
		{
			static constexpr umint mc_Value = alignof(t_CType);
		};

		template <>
		struct TCAlignOf<void>
		{
			static constexpr umint mc_Value = 0;
		};
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	struct TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>
	{
		using CIndexType = t_CIndex;
		using CIndexInteger = NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)>;
		using CIndexUnsignedInteger = NTraits::TCUnsigned<CIndexInteger>;
		static constexpr umint mc_Length = sizeof...(tp_CTypes);

	private:
		template <typename ...tp_CTypes2>
		friend struct TCVariant;

		static_assert(((CIndexInteger(tp_Member) >= CIndexInteger(0)) && ...), "Member index value needs to be positive");
		static constexpr CIndexInteger mcp_MinIndex = fg_MinConstexpr(CIndexInteger(tp_Member)...);
		static constexpr CIndexInteger mcp_MaxIndex = fg_MaxConstexpr(CIndexInteger(tp_Member)...);

		static constexpr CIndexInteger mcp_Member0 = NMeta::gc_IntegerSequence_Get<0, NMeta::TCIntegerSequence<CIndexInteger, CIndexInteger(tp_Member)...>>;
		static constexpr t_CIndex mcp_Member0Typed = t_CIndex(mcp_Member0);

		using CType0 = NMeta::TCTypeList_Get<0, NMeta::TCTypeList<tp_CTypes...>>;

		static constexpr umint mcp_NeededBits = gc_ConstantMax<smint, gc_HighestBitSet<mcp_MaxIndex>, gc_HighestBitSet<mcp_MinIndex>> + 2;

		using CTypeIDStorageType = NTraits::TCIntFromSizeLarger<(mcp_NeededBits + 7) / 8>;

		static_assert((NPrivate::TCCheckVariantContracts<tp_CTypes>::mc_Value && ...));

		static_assert(NPrivate::TCAllAreUniqueIndex<t_CIndex, tp_Member...>::mc_Value);

		template <CIndexInteger t_iMember>
		// NOLINTNEXTLINE(malterlib-type-naming): the type of a member, which can be an enum
		using TCTypeFromMemberInt = typename NPrivate::TCGetMemberByIndex<CIndexInteger, t_iMember, TCVariantMember<CIndexInteger, tp_CTypes, CIndexInteger(tp_Member)>...>::CType;

		template <typename t_CType>
		using TCMemberFromTypeInt = NPrivate::TCGetMemberByType<CIndexInteger, t_CType, TCVariantMember<CIndexInteger, tp_CTypes, CIndexInteger(tp_Member)>...>;

	public:
		template <t_CIndex t_iMember>
		using TCTypeFromMember = TCTypeFromMemberInt<CIndexInteger(t_iMember)>;

		template <typename t_CType>
		struct TCMemberFromType
		{
			static constexpr t_CIndex mc_Value = t_CIndex(TCMemberFromTypeInt<t_CType>::mc_Value);
		};

	private:
		template <CIndexInteger t_iMember>
		struct TCEvalConstructType
		{
			using CMemberType = TCTypeFromMemberInt<t_iMember>; // NOLINT(malterlib-type-naming): the type of a member, which can be an enum
			// NOLINTNEXTLINE(malterlib-type-naming): the type of a member, which can be an enum
			using CType = TCConditional<NTraits::cIsReference<CMemberType>, NTraits::TCAddPointer<NTraits::TCRemoveReference<CMemberType>>, NTraits::TCRemoveQualifiers<CMemberType>>;
		};

		static constexpr umint mcp_MaxSize = fg_MaxConstexpr
			(
				NPrivate::TCSizeOf
				<
					TCConditional<NTraits::cIsReference<tp_CTypes>, NTraits::TCAddPointer<NTraits::TCRemoveReference<tp_CTypes>>, NTraits::TCRemoveQualifiers<tp_CTypes>>
				>
				::mc_Value...
			)
		;

		static constexpr umint mcp_MaxAlignment = fg_MaxConstexpr
			(
				NPrivate::TCAlignOf
				<
					TCConditional<NTraits::cIsReference<tp_CTypes>, NTraits::TCAddPointer<NTraits::TCRemoveReference<tp_CTypes>>, NTraits::TCRemoveQualifiers<tp_CTypes>>
				>
				::mc_Value...
			)
		;

		static constexpr CIndexInteger mcp_FirstDefaultConstructible
			= NTraits::cIsVoid<CType0>
			? mcp_Member0
			: NPrivate::TCFirstDefaultConstructible<CIndexInteger, NTraits::CCompileTimeTrue, TCVariantMember<CIndexInteger, tp_CTypes, CIndexInteger(tp_Member)>...>::mc_Value
		;

		static constexpr CIndexInteger mcp_FirstNothrowDefaultConstructible
			= NTraits::cIsVoid<CType0>
			? mcp_Member0
			: NPrivate::TCFirstNothrowDefaultConstructible<CIndexInteger, NTraits::CCompileTimeTrue, TCVariantMember<CIndexInteger, tp_CTypes, CIndexInteger(tp_Member)>...>::mc_Value
		;

		static constexpr bool mcp_bAllHasNothrowCopyConstructor = ((NTraits::cIsNothrowCopyConstructible<tp_CTypes> || NTraits::cIsVoid<tp_CTypes>) && ...);
		static constexpr bool mcp_bAllHasNothrowMoveConstructor = ((NTraits::cIsNothrowMoveConstructible<tp_CTypes> || NTraits::cIsVoid<tp_CTypes>) && ...);

		template <umint t_MaxSize, typename t_CDummy = void>
		struct TCDetermineStorageType
		{
			using CType = uint8[mcp_MaxSize];
		};

		template <typename t_CDummy>
		struct TCDetermineStorageType<0, t_CDummy>
		{
			struct CType
			{
			};
		};

		struct CStorageType
		{
			DMibNoUniqueAddress alignas(mcp_MaxAlignment) TCDetermineStorageType<mcp_MaxSize>::CType m_Storage = {};
			CTypeIDStorageType m_CurrentType;
		};

		inline_small void fp_SetTypeID(CIndexInteger const &_TypeID);

		template <CIndexInteger t_iMember>
		struct TCEvalReturnType
		{
			using CMemberType = TCTypeFromMemberInt<t_iMember>; // NOLINT(malterlib-type-naming): the type of a member, which can be an enum
			using CType = TCConditional<NTraits::cIsRValueReference<CMemberType>, NTraits::TCAddRValueReference<CMemberType>, NTraits::TCAddLValueReference<CMemberType>>;
		};

		template <CIndexInteger t_iMember>
		struct TCEvalReturnTypeConst
		{
			using CMemberType = TCTypeFromMemberInt<t_iMember>; // NOLINT(malterlib-type-naming): the type of a member, which can be an enum
			using CType = TCConditional
				<
					NTraits::cIsRValueReference<CMemberType>
					, NTraits::TCAddRValueReference<NTraits::TCAddConst<NTraits::TCRemoveRValueReference<CMemberType>>>
					, NTraits::TCAddLValueReference<NTraits::TCAddConst<NTraits::TCRemoveLValueReference<CMemberType>>>
				>
			;
		};

		template <CIndexInteger t_iMember>
		struct TCEvalTryGetReturnType
		{
			using CMemberType = TCTypeFromMemberInt<t_iMember>;
			using CType = NTraits::TCDecay<CMemberType> *;
		};

		template <CIndexInteger t_iMember>
		struct TCEvalTryGetReturnTypeConst
		{
			using CMemberType = TCTypeFromMemberInt<t_iMember>;
			using CType = NTraits::TCAddConst<NTraits::TCDecay<CMemberType>> *;
		};

		template <CIndexInteger t_iMember, typename t_CReturnType = typename TCEvalReturnType<t_iMember>::CType>
		struct TCCallVisitor
		{
			template <typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static void fs_Call(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAs<t_iMember>())))
			;

			template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static auto fs_CallRet(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAs<t_iMember>())))
				-> tf_CRet
			;

			template <typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static void fs_CallFirst(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAs<t_iMember>())))
			;

			template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static auto fs_CallFirstRet(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAs<t_iMember>())))
				-> tf_CRet
			;
		};

		template <CIndexInteger t_iMember>
		struct TCCallVisitor<t_iMember, void>
		{
			template <typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static void fs_Call(tf_CThis &&_pThis, tf_CVisitor &&_Visitor) noexcept;

			template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static tf_CRet fs_CallRet(tf_CThis &&_pThis, tf_CVisitor &&_Visitor);

			template <typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static void fs_CallFirst(tf_CThis &&_pThis, tf_CVisitor &&_Visitor) noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag())));

			template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static tf_CRet fs_CallFirstRet(tf_CThis &&_pThis, tf_CVisitor &&_Visitor) noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag())));
		};

		template <CIndexInteger t_iMember, typename t_CReturnType = typename TCEvalReturnType<t_iMember>::CType>
		struct TCCallVisitorStorage
		{
			template <typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static void fs_Call(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>())))
			;

			template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static auto fs_CallRet(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>())))
				-> tf_CRet
			;

			template <typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static void fs_CallFirst(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>())))
			;

			template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static auto fs_CallFirstRet(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>())))
				-> tf_CRet
			;
		};

		template <CIndexInteger t_iMember>
		struct TCCallVisitorStorage<t_iMember, void>
		{
			template <typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static void fs_Call(tf_CThis &&_pThis, tf_CVisitor &&_Visitor) noexcept;

			template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static tf_CRet fs_CallRet(tf_CThis &&_pThis, tf_CVisitor &&_Visitor);

			template <typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static void fs_CallFirst(tf_CThis &&_pThis, tf_CVisitor &&_Visitor) noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag())));

			template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static tf_CRet fs_CallFirstRet(tf_CThis &&_pThis, tf_CVisitor &&_Visitor) noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag())));
		};

		template <CIndexInteger t_iMember, typename t_CReturnType = typename TCEvalReturnType<t_iMember>::CType>
		struct TCCallVisitorSet
		{
			template <typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static void fs_Call(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>())))
			;

			template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static auto fs_CallRet(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>())))
				-> tf_CRet
			;

			template <typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static void fs_CallFirst(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>())))
			;

			template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static auto fs_CallFirstRet(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept((fg_Forward<tf_CVisitor>(_Visitor))((fg_Forward<tf_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>())))
				-> tf_CRet
			;
		};

		template <CIndexInteger t_iMember>
		struct TCCallVisitorSet<t_iMember, void>
		{
			template <typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static void fs_Call(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept(fg_Forward<tf_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>()))
			;

			template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static tf_CRet fs_CallRet(tf_CThis &&_pThis, tf_CVisitor &&_Visitor);

			template <typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static void fs_CallFirst(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept(fg_Forward<tf_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>()) && noexcept((fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag())))
			;

			template <typename tf_CRet, typename tf_CThis, typename tf_CVisitor>
			mark_artificial inline_small static auto fs_CallFirstRet(tf_CThis &&_pThis, tf_CVisitor &&_Visitor)
				noexcept(noexcept(fg_Forward<tf_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>()) && noexcept((fg_Forward<tf_CVisitor>(_Visitor))(CVoidTag())))
				-> tf_CRet
			;
		};

		template <typename t_CType, bool t_bIsReference = NTraits::cIsReference<t_CType>, bool t_bIsArray = NTraits::cIsArray<t_CType>>
		struct TCEvalReturn
		{
			template <typename tf_CType0, typename tf_CType1>
			mark_nodebug inline_small static auto fs_Value(tf_CType1 &&_pToRet) -> decltype(*_pToRet);
		};

		template <typename t_CType>
		struct TCEvalReturn<t_CType, false, true>
		{
			template <typename tf_CType0, typename tf_CType1>
			mark_nodebug inline_small static t_CType &fs_Value(tf_CType1 &&_pToRet);
		};

		template <typename t_CType>
		struct TCEvalReturn<t_CType, true, false>
		{
			template <typename tf_CType0, typename tf_CType1>
			mark_nodebug inline_small static TCEnableIf<NTraits::cIsLValueReference<tf_CType0>, tf_CType0> fs_Value(tf_CType1 &&_pToRet);

			template <typename tf_CType0, typename tf_CType1>
			mark_nodebug inline_small static TCEnableIf<!NTraits::cIsLValueReference<tf_CType0>, tf_CType0> fs_Value(tf_CType1 &&_pToRet);
		};

		template <CIndexInteger tf_iMember>
		mark_nodebug inline_small auto fp_GetAs() -> TCEnableIf<!NTraits::cIsVoid<typename TCEvalReturnType<tf_iMember>::CType>, typename TCEvalReturnType<tf_iMember>::CType>;

		template <CIndexInteger tf_iMember>
		mark_nodebug inline_small auto fp_GetAs() const -> TCEnableIf<NTraits::cIsVoid<typename TCEvalReturnType<tf_iMember>::CType>, typename TCEvalReturnType<tf_iMember>::CType>;

		template <CIndexInteger tf_iMember>
		mark_nodebug inline_small auto fp_GetAs() const
			-> TCEnableIf<!NTraits::cIsVoid<typename TCEvalReturnTypeConst<tf_iMember>::CType>, typename TCEvalReturnTypeConst<tf_iMember>::CType>
		;

		template <CIndexInteger tf_iMember>
		mark_nodebug inline_small auto fp_GetAsStorage()
			-> TCEnableIf<!NTraits::cIsVoid<typename TCEvalReturnType<tf_iMember>::CType>, NTraits::TCAddLValueReference<typename TCEvalConstructType<tf_iMember>::CType>>
		;

		template <CIndexInteger tf_iMember>
		mark_nodebug inline_small auto fp_GetAsStorage() const -> TCEnableIf<NTraits::cIsVoid<typename TCEvalReturnType<tf_iMember>::CType>, typename TCEvalReturnType<tf_iMember>::CType>;

		template <CIndexInteger tf_iMember>
		mark_nodebug inline_small auto fp_GetAsStorage() const
			-> TCEnableIf
			<
				!NTraits::cIsVoid<typename TCEvalReturnTypeConst<tf_iMember>::CType>
				, NTraits::TCAddLValueReference<NTraits::TCAddConst<typename TCEvalConstructType<tf_iMember>::CType>>
			>
		;

		template <typename tf_CVisitor>
		inline_always void fp_VisitStorage(tf_CVisitor &&_Visitor)
			noexcept
			(
				noexcept(TCCallVisitorStorage<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor)))
				&& (true && ... && noexcept(TCCallVisitorStorage<CIndexInteger(tp_Member)>::fs_Call(this, fg_Forward<tf_CVisitor>(_Visitor))))
			)
		;

	public:
		template <typename tf_CVisitor>
		inline_always void f_Visit(tf_CVisitor &&_Visitor)
			noexcept
			(
				noexcept(TCCallVisitor<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor)))
				&& (true && ... && noexcept(TCCallVisitor<CIndexInteger(tp_Member)>::fs_Call(this, fg_Forward<tf_CVisitor>(_Visitor))))
			)
		;

		template <typename tf_CVisitor>
		inline_always void f_Visit(tf_CVisitor &&_Visitor) const
			noexcept
			(
				noexcept(TCCallVisitor<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor)))
				&& (true && ... && noexcept(TCCallVisitor<CIndexInteger(tp_Member)>::fs_Call(this, fg_Forward<tf_CVisitor>(_Visitor))))
			)
		;

		template <typename tf_CReturn, typename tf_CVisitor>
		inline_always auto f_VisitRet(tf_CVisitor &&_Visitor)
			noexcept
			(
				noexcept(TCCallVisitor<mcp_Member0>::template fs_CallFirstRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor)))
				&& (true && ... && noexcept(TCCallVisitor<CIndexInteger(tp_Member)>::template fs_CallRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor))))
			)
			-> tf_CReturn
		;

		template <typename tf_CReturn, typename tf_CVisitor>
		inline_always auto f_VisitRet(tf_CVisitor &&_Visitor) const
			noexcept
			(
				noexcept(TCCallVisitor<mcp_Member0>::template fs_CallFirstRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor)))
				&& (true && ... && noexcept(TCCallVisitor<CIndexInteger(tp_Member)>::template fs_CallRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor))))
			)
			-> tf_CReturn
		;

		template <typename tf_CVisitor>
		inline_always void f_VisitCreate(t_CIndex const &_Index, tf_CVisitor &&_Visitor)
			noexcept
			(
				noexcept(TCCallVisitorSet<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor)))
				&& (true && ... && noexcept(TCCallVisitorSet<CIndexInteger(tp_Member)>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor))))
			)
		;

		template <typename tf_CVisitor>
		inline_always auto f_TryVisitCreate(t_CIndex const &_Index, tf_CVisitor &&_Visitor)
			noexcept
			(
				noexcept(TCCallVisitorSet<mcp_Member0>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor)))
				&& (true && ... && noexcept(TCCallVisitorSet<CIndexInteger(tp_Member)>::fs_CallFirst(this, fg_Forward<tf_CVisitor>(_Visitor))))
			)
			-> bool
		;

		template <typename tf_CReturn, typename tf_CVisitor>
		inline_always auto f_VisitCreateReturn(t_CIndex const &_Index, tf_CVisitor &&_Visitor)
			noexcept
			(
				noexcept(TCCallVisitorSet<mcp_Member0>::template fs_CallFirstRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor)))
				&& (true && ... && noexcept(TCCallVisitorSet<CIndexInteger(tp_Member)>::template fs_CallRet<tf_CReturn>(this, fg_Forward<tf_CVisitor>(_Visitor))))
			)
			-> tf_CReturn
		;

		bool operator == (TCVariantCommon const &_Right) const noexcept(noexcept(fg_VisitRet<bool>(NPrivate::CCompareVariant_Equal(), *this, _Right)));

		auto operator <=> (TCVariantCommon const &_Right) const noexcept
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
		;

	private:
		void fp_DestroyCurrent();

#ifdef DDebugger_VisualStudio
		void fp_ReferenceDebugInfo();
#endif
	protected:
		template <typename t_CInType>
		struct TCEvalOneParamConstruction
		{
			using CInTypeNoRef = NTraits::TCRemoveReferenceStorable<t_CInType>;
			using CInTypeNoRefNoQualifier = NTraits::TCRemoveQualifiers<CInTypeNoRef>;

			static constexpr CIndexInteger mc_Value = TCChooseInt
				<
					CIndexInteger
					, (TCMemberFromTypeInt<CInTypeNoRef>::mc_Value >= 0)
					, TCMemberFromTypeInt<CInTypeNoRef>::mc_Value
					, TCChooseInt
					<
						CIndexInteger
						, (TCMemberFromTypeInt<CInTypeNoRefNoQualifier>::mc_Value >= 0)
						, TCMemberFromTypeInt<CInTypeNoRefNoQualifier>::mc_Value
						, CIndexInteger
						(
							NPrivate::TCFirstConstructibleWith
							<
								CIndexInteger
								, void (t_CInType _Param)
								, NTraits::CCompileTimeTrue
								, TCVariantMember<CIndexInteger, tp_CTypes, CIndexInteger(tp_Member)>...
							>::mc_Value
						)
					>
					::mc_Value
				>
				::mc_Value
			;
		};

	private:
		template <typename t_CParam>
		struct TCIsNothrowConstructibleWith
		{
			static constexpr CIndexInteger mc_ToConstruct = TCEvalOneParamConstruction<t_CParam>::mc_Value;

			using CTypeToConstruct = TCTypeFromMemberInt<mc_ToConstruct>;
			static constexpr bool mc_Value
				= mc_ToConstruct >= 0
				&& NTraits::cIsNothrowCopyConstructible<CTypeToConstruct>
				&&
				(
					NTraits::cIsSame<NTraits::TCRemoveQualifiers<CTypeToConstruct>, NTraits::TCRemoveQualifiers<t_CParam>>
					||
					(
						!NTraits::cIsReference<CTypeToConstruct>
						&& NTraits::cIsReference<t_CParam>
						&& NTraits::cIsSame<NTraits::TCRemoveQualifiers<CTypeToConstruct>, NTraits::TCRemoveReferenceAndQualifiers<t_CParam>>
					)
				)
			;
		};

		template <typename t_FConstructorParams>
		struct TCEvalManyParamConstruction
		{
			static constexpr CIndexInteger mc_Value = NPrivate::TCFirstConstructibleWith
				<
					CIndexInteger
					, t_FConstructorParams
					, NTraits::CCompileTimeTrue
					, TCVariantMember<CIndexInteger, tp_CTypes, CIndexInteger(tp_Member)>...
				>
				::mc_Value
			;
		};

		////////////////////////////////////////
		//
		template <CIndexInteger tf_iMember>
		typename TCEvalReturnType<tf_iMember>::CType fp_Set();

		template <CIndexInteger tf_iMember, typename tf_CParam0>
		typename TCEvalReturnType<tf_iMember>::CType fp_Set(tf_CParam0 &&_Param0)
			requires (NTraits::cIsConstructibleWith<TCTypeFromMemberInt<tf_iMember>, tf_CParam0 &&>)
		;

		template <CIndexInteger tf_iMember, typename tf_CParam0, typename ...tfp_CParams>
		typename TCEvalReturnType<tf_iMember>::CType fp_Set(tf_CParam0 &&_Param0, tfp_CParams && ...p_Params)
			requires (NTraits::cIsConstructibleWith<TCTypeFromMemberInt<tf_iMember>, tf_CParam0 &&, tfp_CParams && ...>)
		;

		template <CIndexInteger tf_iMember>
		void fp_SetNoRet();

		template <CIndexInteger tf_iMember, typename tf_CParam0>
		void fp_SetNoRet(tf_CParam0 &&_Param0)
			requires (NTraits::cIsConstructibleWith<TCTypeFromMemberInt<tf_iMember>, tf_CParam0 &&>)
		;

		template <CIndexInteger tf_iMember, typename tf_CParam0, typename ...tfp_CParams>
		void fp_SetNoRet(tf_CParam0 &&_Param0, tfp_CParams && ...p_Params)
			requires (NTraits::cIsConstructibleWith<TCTypeFromMemberInt<tf_iMember>, tf_CParam0 &&, tfp_CParams && ...>)
		;

		template <typename tf_CType, typename ...tfp_CParams, umint ...tfp_Indidies>
		void fp_AssignConstruct(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams, NMeta::TCIndices<tfp_Indidies...> const &_Indices)
			requires
			(
				TCEvalManyParamConstruction<void (tfp_CParams ...p_Params)>::mc_Value >= 0
				&& mcp_FirstNothrowDefaultConstructible != -1
				&& requires ()
				{
					this->fp_SetNoRet<TCEvalManyParamConstruction<void (tfp_CParams ...p_Params)>::mc_Value>(fg_Forward<tfp_CParams>(fg_Get<tfp_Indidies>(_CreateParams.m_Params))...);
				}
			)
		;

		inline_small CIndexInteger fp_GetTypeID() const;

	private:
		TCVariantCommon &fp_GetStreamable();

		TCVariantCommon const &fp_GetStreamable() const;

		struct CVariantVisitor_Move
		{
			TCVariantCommon &m_This;
			CVariantVisitor_Move(TCVariantCommon &_This);

			void operator () (CVoidTag _Tag);

			template <typename tf_CParam0>
			void operator () (tf_CParam0 &&_Param0);
		};

		struct CVariantVisitor_Copy
		{
			TCVariantCommon &m_This;
			CVariantVisitor_Copy(TCVariantCommon &_This);

			void operator () (CVoidTag _Tag);

			template <typename tf_CParam0>
			void operator () (tf_CParam0 &&_Param0);
		};

	public:
		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Default construction / destruction																|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		TCVariantCommon() noexcept
			requires
			(
				mcp_FirstNothrowDefaultConstructible != -1 && requires ()
				{
					this->fp_SetNoRet<mcp_FirstDefaultConstructible>();
				}
			)
		;

		~TCVariantCommon();

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Copy/Move variant construction																	|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename tf_CIndex, typename ...tfp_CMembers>
		TCVariantCommon(TCVariantCommon<tf_CIndex, tfp_CMembers...> &&_Other);

		TCVariantCommon(TCVariantCommon &&_Other);

		template <typename tf_CIndex, typename ...tfp_CMembers>
		TCVariantCommon(TCVariantCommon<tf_CIndex, tfp_CMembers...> const &_Other);

		TCVariantCommon(TCVariantCommon const &_Other);

		TCVariantCommon(TCVariantCommon &_Other);

		template <typename tf_CIndex, typename ...tfp_CMembers>
		TCVariantCommon(TCVariantCommon<tf_CIndex, tfp_CMembers...> &_Other);

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Any other construction																			|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename tf_CParam0, TCEnableIf<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value >= 0> * = nullptr>
		TCVariantCommon(tf_CParam0 &&_Param0)
			requires requires ()
			{
				this->fp_SetNoRet<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value>(fg_Forward<tf_CParam0>(_Param0));
			}
		;

		template
		<
			typename tf_CParam0
			, typename ...tfp_CParams
			, TCEnableIf<TCEvalManyParamConstruction<void (tf_CParam0 &&_Param0, tfp_CParams ...p_RestOfParams)>::mc_Value >= 0> * = nullptr
		>
		TCVariantCommon(tf_CParam0 &&_Param0, tfp_CParams && ...p_RestOfParams)
			requires requires ()
			{
				this->fp_SetNoRet<TCEvalManyParamConstruction<void (tf_CParam0 &&_Param0, tfp_CParams ...p_RestOfParams)>::mc_Value>
					(
						fg_Forward<tf_CParam0>(_Param0)
						, fg_Forward<tfp_CParams>(p_RestOfParams)...
					)
				;
			}
		;

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Copy/Move variant assignment																		|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename tf_CIndex, typename ...tfp_CMembers>
		TCVariantCommon &operator = (TCVariantCommon<tf_CIndex, tfp_CMembers...> &&_Other)
			requires (mcp_FirstNothrowDefaultConstructible != -1)
		;

		TCVariantCommon &operator = (TCVariantCommon &&_Other)
			requires (mcp_FirstNothrowDefaultConstructible != -1 || mcp_bAllHasNothrowMoveConstructor)
		;

		template <typename tf_CIndex, typename ...tfp_CMembers>
		TCVariantCommon &operator = (TCVariantCommon<tf_CIndex, tfp_CMembers...> const &_Other)
			requires (mcp_FirstNothrowDefaultConstructible != -1)
		;

		TCVariantCommon &operator = (TCVariantCommon const &_Other)
			requires (mcp_FirstNothrowDefaultConstructible != -1 || mcp_bAllHasNothrowCopyConstructor)
		;

		TCVariantCommon &operator = (TCVariantCommon &_Other)
			requires (mcp_FirstNothrowDefaultConstructible != -1 || mcp_bAllHasNothrowCopyConstructor)
		;

		template <typename tf_CIndex, typename ...tfp_CMembers>
		TCVariantCommon &operator = (TCVariantCommon<tf_CIndex, tfp_CMembers...> &_Other)
			requires (mcp_FirstNothrowDefaultConstructible != -1)
		;

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Any other assignment																				|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename tf_CParam0, TCEnableIf<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value >= 0> * = nullptr>
		TCVariantCommon &operator = (tf_CParam0 &&_Param)
			requires
			(
				(TCIsNothrowConstructibleWith<tf_CParam0 &&>::mc_Value || (mcp_FirstNothrowDefaultConstructible != -1)) && requires ()
				{
					this->fp_SetNoRet<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value>(fg_Forward<tf_CParam0>(_Param)); // Cannot throw
				}
			)
		;

		template <typename tf_CType, typename ...tfp_CParams>
		TCVariantCommon &operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
			requires requires ()
			{
				this->fp_AssignConstruct(fg_Move(_CreateParams), NMeta::TCConsecutiveIndices<TCConstruct<tf_CType, tfp_CParams...>::mc_nParams>());
			}
		;

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Misc functions																					|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		inline_small t_CIndex f_GetTypeID() const;

		template <typename tf_CType>
		inline_small bool f_IsOfType() const;

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Get already known type																			|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <t_CIndex tf_iMember>
		typename TCEvalReturnType<CIndexInteger(tf_iMember)>::CType f_Get();

		template <t_CIndex tf_iMember>
		typename TCEvalReturnTypeConst<CIndexInteger(tf_iMember)>::CType f_Get() const;

		template <typename tf_CType>
		typename TCEvalReturnType<TCMemberFromTypeInt<tf_CType>::mc_Value>::CType f_GetAsType()
			requires (TCMemberFromTypeInt<tf_CType>::mc_Value >= 0)
		;

		template <typename tf_CType>
		typename TCEvalReturnTypeConst<TCMemberFromTypeInt<tf_CType>::mc_Value>::CType f_GetAsType() const
			requires (TCMemberFromTypeInt<tf_CType>::mc_Value >= 0)
		;

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Try get already known type																		|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <t_CIndex tf_iMember>
		typename TCEvalTryGetReturnType<CIndexInteger(tf_iMember)>::CType f_TryGet();

		template <t_CIndex tf_iMember>
		typename TCEvalTryGetReturnTypeConst<CIndexInteger(tf_iMember)>::CType f_TryGet() const;

		template <typename tf_CType>
		typename TCEvalTryGetReturnType<TCMemberFromTypeInt<tf_CType>::mc_Value>::CType f_TryGetAsType()
			requires (TCMemberFromTypeInt<tf_CType>::mc_Value >= 0)
		;

		template <typename tf_CType>
		typename TCEvalTryGetReturnTypeConst<TCMemberFromTypeInt<tf_CType>::mc_Value>::CType f_TryGetAsType() const
			requires (TCMemberFromTypeInt<tf_CType>::mc_Value >= 0)
		;

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Initialize specific member with value																|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <t_CIndex tf_iMember>
		typename TCEvalReturnType<CIndexInteger(tf_iMember)>::CType f_Set()
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
		;

		template <t_CIndex tf_iMember, typename ...tfp_CParams>
		typename TCEvalReturnType<CIndexInteger(tf_iMember)>::CType f_Set(tfp_CParams && ...p_Params)
			requires
			(
				mcp_FirstNothrowDefaultConstructible != -1 && requires ()
				{
					this->fp_Set<CIndexInteger(tf_iMember)>(fg_Forward<tfp_CParams>(p_Params)...);
				}
			)
		;

		template <typename tf_CType, typename ...tfp_CParams>
		auto f_SetAsType(tfp_CParams && ...p_Params) -> decltype(f_Set<t_CIndex(TCMemberFromTypeInt<tf_CType>::mc_Value)>(fg_Forward<tfp_CParams>(p_Params)...))
			requires (TCMemberFromTypeInt<tf_CType>::mc_Value >= 0)
		;

		// Formatting

		template <typename tf_CStr>
		void f_Format(tf_CStr &o_Str) const;

	private:
		CStorageType mp_Storage;
	};

	template <typename t_CIndex, typename ...tp_CMembers>
	using TCStreamableVariant = TCVariantCommon<t_CIndex, tp_CMembers...>;

	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| Variant																							|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	namespace NPrivate
	{
		template <typename t_CTypes, typename t_CIndices = NMeta::TCConsecutiveIndices<NMeta::gc_TypeList_Len<t_CTypes>>>
		struct TCGetNonStreamableVariant
		{
		};

		template <typename ...tp_CTypes, umint ...tp_Indices>
		struct TCGetNonStreamableVariant<NMeta::TCTypeList<tp_CTypes...>, NMeta::TCIndices<tp_Indices...>>
		{
			using CType = TCVariantCommon<int32, TCVariantMember<int32, tp_CTypes, int32(tp_Indices)>...>;
		};
	}

	namespace NPrivate
	{
		template <typename t_CIndex, typename t_CTypes, typename t_CIndices = NMeta::TCConsecutiveIndices<NMeta::gc_TypeList_Len<t_CTypes>>>
		struct TCGetStreamableVariant
		{
		};

		template <typename t_CIndex, typename ...tp_CTypes, umint ...tp_Indices>
		struct TCGetStreamableVariant<t_CIndex, NMeta::TCTypeList<tp_CTypes...>, NMeta::TCIndices<tp_Indices...>>
		{
			using CType = TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, t_CIndex(tp_Indices)>...>;
		};
	}

	template <typename t_CIndex, typename ...tp_CTypes>
	using TCStreamableFixedVariant = typename NPrivate::TCGetStreamableVariant<t_CIndex, NMeta::TCTypeList<tp_CTypes...>>::CType;

	template <typename ...tp_CTypes>
	struct TCVariant : public NPrivate::TCGetNonStreamableVariant<NMeta::TCTypeList<tp_CTypes...>>::CType
	{
		using CParent = typename NPrivate::TCGetNonStreamableVariant<NMeta::TCTypeList<tp_CTypes...>>::CType;

		TCVariant() = default;
		~TCVariant() = default;

		TCVariant(TCVariant &&_Other);

		TCVariant(TCVariant &_Other);

		TCVariant(TCVariant const &_Other);

		TCVariant &operator = (TCVariant &&_Other)
			requires requires ()
			{
				this->fp_GetStreamable() = fg_Move(_Other.fp_GetStreamable());
			}
		;

		TCVariant &operator = (TCVariant const &_Other)
			requires requires ()
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
			}
		;

		TCVariant &operator = (TCVariant &_Other)
			requires requires ()
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
			}
		;

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Any Construct																						|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename ...tfp_CParams>
		TCVariant(tfp_CParams && ...p_Param);

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Copy Construct																					|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename ...tfp_CParams>
		TCVariant(TCVariant<tfp_CParams...> const &_Other);

		template <typename ...tfp_CParams>
		TCVariant(TCVariant<tfp_CParams...> &_Other);

		template <typename ...tfp_CParams>
		TCVariant(TCVariant<tfp_CParams...> &&_Other);

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Assignment																						|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename ...tfp_CParams>
		TCVariant &operator = (TCVariant<tfp_CParams...> const &_Other)
			requires requires ()
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
			}
		;

		template <typename ...tfp_CParams>
		TCVariant &operator = (TCVariant<tfp_CParams...> &_Other)
			requires requires ()
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
			}
		;

		template <typename ...tfp_CParams>
		TCVariant &operator = (TCVariant<tfp_CParams...> &&_Other)
			requires requires ()
			{
				this->fp_GetStreamable() = fg_Move(_Other.fp_GetStreamable());
			}
		;

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Any assignment																					|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename tf_CParam>
		inline_small TCVariant &operator = (tf_CParam &&_Param)
			requires requires ()
			{
				this->CParent::operator = (fg_Forward<tf_CParam>(_Param));
			}
		;
	};
}

/***************************************************************************************************\
|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
| Streaming																							|
|___________________________________________________________________________________________________|
\***************************************************************************************************/

namespace NMib::NStream
{
	namespace NPrivate
	{
		template <typename t_CStream>
		struct TCVariantVisitor_Feed
		{
			TCVariantVisitor_Feed(t_CStream &_Stream);

			void operator () (CVoidTag _Tag);

			template <typename tf_CType>
			void operator () (tf_CType &&_Data);

			t_CStream &m_Stream;
		};

		template <typename t_CStream>
		struct TCVariantVisitor_FeedMove
		{
			TCVariantVisitor_FeedMove(t_CStream &_Stream);

			void operator () (CVoidTag _Tag);

			template <typename tf_CType>
			void operator () (tf_CType &&_Data);

			t_CStream &m_Stream;
		};

		template <typename t_CStream>
		struct TCVariantVisitor_Consume
		{
			TCVariantVisitor_Consume(t_CStream &_Stream);

			void operator () (CVoidTag _Tag);

			template <typename tf_CType>
			void operator () (tf_CType &&_Data);

			t_CStream &m_Stream;
		};
	}

	template <typename t_CStream, typename t_CIndex, typename ...tp_CMembers>
	struct TCBinaryStreamTypeReference<t_CStream, NStorage::TCVariantCommon<t_CIndex, tp_CMembers...>>
	{
	private:
		// Declared before the public section, which uses it.
		using CStreamableVariant = NStorage::TCVariantCommon<t_CIndex, tp_CMembers...>;

	public:
		static constexpr void fs_Feed(t_CStream &_Stream, CStreamableVariant const &_Data);

		static constexpr void fs_Feed(t_CStream &_Stream, CStreamableVariant &&_Data);

		static constexpr void fs_Consume(t_CStream &_Stream, CStreamableVariant &_Data);
	};
}

#ifndef DMibPNoShortCuts
using namespace NMib::NStorage;
#endif

#include "Malterlib_Storage_Variant.hpp"
