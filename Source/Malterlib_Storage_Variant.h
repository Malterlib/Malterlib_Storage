// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
#include <Mib/Contract/Contract>

namespace NMib::NStorage
{
	template <typename t_CIndex, typename ...tp_CMembers>
	struct TCVariantCommon;

	template <typename ...tp_CTypes>
	struct TCVariant;

#ifdef DCompiler_MSVC_Workaround
#define DMibStorageVariantTypeInMember(...) __VA_ARGS__
#else
#define DMibStorageVariantTypeInMember(...)
#endif

	namespace NPrivate
	{
		struct CVariantVisitor_Destruct
		{
			void operator () (CVoidTag)
			{
			}

			template <typename tf_CType>
			void operator () (tf_CType &_Type)
			{
				fg_CallDestructor(_Type);
			}
		};

		struct CDummy
		{
			CDummy() = delete;
			~CDummy() = delete;
		};

		template <typename t_CReturn>
		function_does_not_return inline_never typename TCEnableIf<!NTraits::TCIsVoid<t_CReturn>::mc_Value, t_CReturn &>::CType fg_InvalidVariant()
		{
			DMibError("Corrupt variant");
		}

		template <typename t_CReturn>
		function_does_not_return inline_never typename TCEnableIf<NTraits::TCIsVoid<t_CReturn>::mc_Value, void>::CType fg_InvalidVariant()
		{
			DMibError("Corrupt variant");
		}

		template <typename t_CType>
		struct TCIsVariant
		{
			constexpr static bool mc_Value = false;
		};

		template <typename t_CIndex, typename ...tp_CMembers>
		struct TCIsVariant<TCVariantCommon<t_CIndex, tp_CMembers...>>
		{
			constexpr static bool mc_Value = true;
		};

		template <typename ...tp_CTypes>
		struct TCIsVariant<TCVariant<tp_CTypes...>>
		{
			constexpr static bool mc_Value = true;
		};
	}

	template <typename t_CIndex, typename ...tp_CMembers>
	struct TCVariantCommon
	{
		static_assert(NTraits::TCIsSame<t_CIndex, NPrivate::CDummy>::mc_Value, "Mismatched index type and member index types");
	};

	template <typename t_CIndex, typename t_CType, t_CIndex t_Member>
	struct TCVariantMember
	{
		using CType = t_CType;
		static constexpr t_CIndex mc_Member = t_Member;

#ifdef DDebugger_VisualStudio
		static constexpr bool mc_bDebugIsVoid = NTraits::TCIsVoid<CType>::mc_Value;
		using CDebugType = typename TCChooseType<mc_bDebugIsVoid, uint8, t_CType>::CType;
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
			static constexpr bool mc_Value = t_Member0 != t_Member1
				&& ((t_Member0 != tp_Indices) && ...)
				&& TCAllAreUniqueIndex<t_CIndex, t_Member1, tp_Indices...>::mc_Value
			;
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
				, NTraits::TCCompileTimeTrue<NTraits::TCIsReference<t_CType0>::mc_Value || !NTraits::TCIsConstructorCallableWith<t_CType0, void ()>::mc_Value>
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
				, NTraits::TCCompileTimeTrue<NTraits::TCIsReference<t_CType0>::mc_Value || !NTraits::TCIsConstructorCallableWith<t_CType0, void ()>::mc_Value>
				, TCVariantMember<t_CIndex, t_CType0, t_Member0>
			>
			: public TCFirstDefaultConstructible<t_CIndex, NTraits::CCompileTimeTrue>
		{
		};

		template <typename t_CIndex, typename t_CType0, t_CIndex t_Member0, typename ...tp_CMembers>
		struct TCFirstDefaultConstructible
			<
				t_CIndex
				, NTraits::TCCompileTimeTrue<!NTraits::TCIsReference<t_CType0>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType0, void ()>::mc_Value>
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
				, NTraits::TCCompileTimeTrue<!NTraits::TCIsReference<t_CType0>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType0, void ()>::mc_Value>
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
					NTraits::TCIsReference<t_CType0>::mc_Value
					|| !NTraits::TCIsConstructorCallableWith<t_CType0, void ()>::mc_Value
					|| !NTraits::TCHasNothrowDefaultConstructor<t_CType0>::mc_Value
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
					NTraits::TCIsReference<t_CType0>::mc_Value
					|| !NTraits::TCIsConstructorCallableWith<t_CType0, void ()>::mc_Value
					|| !NTraits::TCHasNothrowDefaultConstructor<t_CType0>::mc_Value
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
				, NTraits::TCCompileTimeTrue
				<
					!NTraits::TCIsReference<t_CType0>::mc_Value
					&& NTraits::TCIsConstructorCallableWith<t_CType0, void ()>::mc_Value
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType0>::mc_Value
				>
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
				, NTraits::TCCompileTimeTrue
				<
					!NTraits::TCIsReference<t_CType0>::mc_Value
					&& NTraits::TCIsConstructorCallableWith<t_CType0, void ()>::mc_Value
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType0>::mc_Value
				>
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

		template <typename t_CIndex, typename t_FConstructorParams, typename t_CType0, t_CIndex t_Member0, typename ...tp_CMembers>
		struct TCFirstConstructibleWith
			<
				t_CIndex
				, t_FConstructorParams
				, NTraits::TCCompileTimeTrue<!NTraits::TCIsConstructorCallableWith<t_CType0, t_FConstructorParams>::mc_Value>
				, TCVariantMember<t_CIndex, t_CType0, t_Member0>
				, tp_CMembers...
			>
			: public TCFirstConstructibleWith<t_CIndex, t_FConstructorParams, NTraits::CCompileTimeTrue, tp_CMembers...>
		{
		};

		template <typename t_CIndex, typename t_FConstructorParams, typename t_CType0, t_CIndex t_Member0, typename ...tp_CMembers>
		struct TCFirstConstructibleWith
			<
				t_CIndex
				, t_FConstructorParams
				, NTraits::TCCompileTimeTrue<NTraits::TCIsConstructorCallableWith<t_CType0, t_FConstructorParams>::mc_Value>
				, TCVariantMember<t_CIndex, t_CType0, t_Member0>
				, tp_CMembers...
			>
		{
			static constexpr t_CIndex mc_Value = t_Member0;
		};

		template <typename t_CIndex, typename t_FConstructorParams, typename t_CType0, t_CIndex t_Member0>
		struct TCFirstConstructibleWith
			<
				t_CIndex
				, t_FConstructorParams
				, NTraits::TCCompileTimeTrue<NTraits::TCIsConstructorCallableWith<t_CType0, t_FConstructorParams>::mc_Value>
				, TCVariantMember<t_CIndex, t_CType0, t_Member0>
			>
		{
			static constexpr t_CIndex mc_Value = t_Member0;
		};

		template <typename t_CType>
		struct TCCheckVariantContracts
		{
			static_assert(!NTraits::TCIsArrayUnbounded<t_CType>::mc_Value, "You cannot store an unbounded array in a variant");
			static_assert(!NTraits::TCIsFunction<t_CType>::mc_Value, "You cannot store function types in a variant");
			constexpr static bool mc_Value = true;
		};

		template <typename t_CType>
		struct TCSizeOf
		{
			static constexpr mint mc_Value = sizeof(t_CType);
		};

		template <>
		struct TCSizeOf<void>
		{
			static constexpr mint mc_Value = 0;
		};

		template <typename t_CType>
		struct TCAlignOf
		{
			static constexpr mint mc_Value = alignof(t_CType);
		};

		template <>
		struct TCAlignOf<void>
		{
			static constexpr mint mc_Value = 0;
		};
	}

#ifdef DMibDebuggerHelpers
	template <smint t_Member, typename t_CType>
	struct TCVariantCommonDebugHelperMember
	{
	};
#endif

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	struct TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>
#ifdef DMibDebuggerHelpers
		: public TCVariantCommonDebugHelperMember<smint(tp_Member), tp_CTypes>...
#endif
	{
		using CIndexType = t_CIndex;
		using CIndexInteger = typename NTraits::TCIntFromSizeLarger<sizeof(t_CIndex)>::CType;
		using CIndexUnsignedInteger = typename NTraits::TCUnsigned<CIndexInteger>::CType;
		static constexpr mint mc_Length = sizeof...(tp_CTypes);

	private:

		template <typename ...tp_CTypes2>
		friend struct TCVariant;

		static_assert(((CIndexInteger(tp_Member) >= CIndexInteger(0)) && ...), "Member index value needs to be positive");
		static constexpr CIndexInteger mcp_MinIndex = fg_MinConstexpr(CIndexInteger(tp_Member)...);
		static constexpr CIndexInteger mcp_MaxIndex = fg_MaxConstexpr(CIndexInteger(tp_Member)...);

		static constexpr CIndexInteger mcp_Member0 = NMeta::TCIntegerSequence_Get<0, NMeta::TCIntegerSequence<CIndexInteger, CIndexInteger(tp_Member)...>>::mc_Value;
		static constexpr t_CIndex mcp_Member0Typed = t_CIndex(mcp_Member0);

		using CType0 = typename NMeta::TCTypeList_Get<0, NMeta::TCTypeList<tp_CTypes...>>::CType;

		static constexpr mint mcp_NeededBits = TCConstantMax
			<
				mint
				, TCHighestBitSet<CIndexInteger, mcp_MaxIndex>::mc_Value
				, TCHighestBitSet<CIndexInteger, mcp_MinIndex>::mc_Value
			>
			::mc_Value + 1
		;

		using CTypeIDStorageType = typename NTraits::TCIntFromSizeLarger<(mcp_NeededBits + 7) / 8>::CType;

		static_assert((NPrivate::TCCheckVariantContracts<tp_CTypes>::mc_Value && ...));

		static_assert(NPrivate::TCAllAreUniqueIndex<t_CIndex, tp_Member...>::mc_Value);

		template <CIndexInteger t_iMember>
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
			using CMemberType = TCTypeFromMemberInt<t_iMember>;
			using CType = typename TCChooseType
				<
					NTraits::TCIsReference<CMemberType>::mc_Value,
					typename NTraits::TCAddPointer<typename NTraits::TCRemoveReference<CMemberType>::CType>::CType,
					typename NTraits::TCRemoveQualifiers<CMemberType>::CType
				>::CType
			;
		};

		static constexpr mint mcp_MaxSize = fg_MaxConstexpr
			(
				NPrivate::TCSizeOf
				<
					typename TCChooseType
					<
						NTraits::TCIsReference<tp_CTypes>::mc_Value,
						typename NTraits::TCAddPointer<typename NTraits::TCRemoveReference<tp_CTypes>::CType>::CType,
						typename NTraits::TCRemoveQualifiers<tp_CTypes>::CType
					>::CType
				>::mc_Value...
			)
		;

		static constexpr mint mcp_MaxAlignment = fg_MaxConstexpr
			(
				NPrivate::TCAlignOf
				<
					typename TCChooseType
					<
						NTraits::TCIsReference<tp_CTypes>::mc_Value
						, typename NTraits::TCAddPointer<typename NTraits::TCRemoveReference<tp_CTypes>::CType>::CType
						, typename NTraits::TCRemoveQualifiers<tp_CTypes>::CType
					>::CType
				>::mc_Value...
			)
		;

		static constexpr CIndexInteger mcp_FirstDefaultConstructible = NTraits::TCIsVoid<CType0>::mc_Value
			? mcp_Member0
			: NPrivate::TCFirstDefaultConstructible<CIndexInteger, NTraits::CCompileTimeTrue, TCVariantMember<CIndexInteger, tp_CTypes, CIndexInteger(tp_Member)>...>::mc_Value
		;

		static constexpr CIndexInteger mcp_FirstNothrowDefaultConstructible = NTraits::TCIsVoid<CType0>::mc_Value
			? mcp_Member0
			: NPrivate::TCFirstNothrowDefaultConstructible<CIndexInteger, NTraits::CCompileTimeTrue, TCVariantMember<CIndexInteger, tp_CTypes, CIndexInteger(tp_Member)>...>::mc_Value
		;

		static constexpr bool mcp_bAllHasNothrowCopyConstructor = ((NTraits::cHasNothrowCopyConstructor<tp_CTypes> || NTraits::TCIsVoid<tp_CTypes>::mc_Value) && ...);
		static constexpr bool mcp_bAllHasNothrowMoveConstructor = ((NTraits::cHasNothrowMoveConstructor<tp_CTypes> || NTraits::TCIsVoid<tp_CTypes>::mc_Value) && ...);

		template <mint t_MaxSize, typename t_CDummy = void>
		struct TCDetermineStorageType
		{
			using CType = uint8[mcp_MaxSize];
		};

		template <typename t_CDummy>
		struct TCDetermineStorageType<0, t_CDummy>
		{
			struct CType {};
		};

		struct CStorageType
		{
			DMibNoUniqueAddress alignas(mcp_MaxAlignment) TCDetermineStorageType<mcp_MaxSize>::CType m_Storage = {};
			DMibNoUniqueAddress CTypeIDStorageType m_CurrentType;
		};

		inline_small void fp_SetTypeID(CIndexInteger const &_TypeID)
		{
			mp_Storage.m_CurrentType = _TypeID;
		}

		template <CIndexInteger t_iMember>
		struct TCEvalReturnType
		{
			using CMemberType = TCTypeFromMemberInt<t_iMember>;
			using CType = typename TCChooseType
				<
					NTraits::TCIsRValueReference<CMemberType>::mc_Value
					, typename NTraits::TCAddRValueReference<CMemberType>::CType
					, typename NTraits::TCAddLValueReference<CMemberType>::CType
				>
				::CType
			;
		};

		template <CIndexInteger t_iMember>
		struct TCEvalReturnTypeConst
		{
			using CMemberType = TCTypeFromMemberInt<t_iMember>;
			using CType =  typename TCChooseType
				<
					NTraits::TCIsRValueReference<CMemberType>::mc_Value
					, typename NTraits::TCAddRValueReference<typename NTraits::TCAddConst<typename NTraits::TCRemoveRValueReference<CMemberType>::CType>::CType>::CType
					, typename NTraits::TCAddLValueReference<typename NTraits::TCAddConst<typename NTraits::TCRemoveLValueReference<CMemberType>::CType>::CType>::CType
				>
				::CType
			;
		};

		template <CIndexInteger t_iMember>
		struct TCEvalTryGetReturnType
		{
			using CMemberType = TCTypeFromMemberInt<t_iMember>;
			using CType = typename NTraits::TCDecay<CMemberType>::CType *;
		};

		template <CIndexInteger t_iMember>
		struct TCEvalTryGetReturnTypeConst
		{
			using CMemberType = TCTypeFromMemberInt<t_iMember>;
			using CType = typename NTraits::TCAddConst<typename NTraits::TCDecay<CMemberType>::CType>::CType *;
		};

		template <CIndexInteger t_iMember, typename t_CReturnType = typename TCEvalReturnType<t_iMember>::CType>
		struct TCCallVisitor
		{
		public:
			template <typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static void fs_Call(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				(fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAs<t_iMember>());
			}

			template <typename t_CRet, typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static t_CRet fs_CallRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				return (fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAs<t_iMember>());
			}

			template <typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static void fs_CallFirst(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				(fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAs<t_iMember>());
			}

			template <typename t_CRet, typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static t_CRet fs_CallFirstRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				return (fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAs<t_iMember>());
			}
		};

		template <CIndexInteger t_iMember>
		struct TCCallVisitor<t_iMember, void>
		{
		public:
			template <typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static void fs_Call(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
			}

			template <typename t_CRet, typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static t_CRet fs_CallRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				return NPrivate::fg_InvalidVariant<t_CRet>();
			}

			template <typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static void fs_CallFirst(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				(fg_Forward<t_CVisitor>(_Visitor))(CVoidTag());
			}

			template <typename t_CRet, typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static t_CRet fs_CallFirstRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				return (fg_Forward<t_CVisitor>(_Visitor))(CVoidTag());
			}
		};

		template <CIndexInteger t_iMember, typename t_CReturnType = typename TCEvalReturnType<t_iMember>::CType>
		struct TCCallVisitorStorage
		{
		public:
			template <typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static void fs_Call(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				(fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>());
			}

			template <typename t_CRet, typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static t_CRet fs_CallRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				return (fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>());
			}

			template <typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static void fs_CallFirst(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				(fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>());
			}

			template <typename t_CRet, typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static t_CRet fs_CallFirstRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				return (fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>());
			}
		};

		template <CIndexInteger t_iMember>
		struct TCCallVisitorStorage<t_iMember, void>
		{
		public:
			template <typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static void fs_Call(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
			}

			template <typename t_CRet, typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static t_CRet fs_CallRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				return NPrivate::fg_InvalidVariant<t_CRet>();
			}

			template <typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static void fs_CallFirst(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				(fg_Forward<t_CVisitor>(_Visitor))(CVoidTag());
			}

			template <typename t_CRet, typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static t_CRet fs_CallFirstRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				return (fg_Forward<t_CVisitor>(_Visitor))(CVoidTag());
			}
		};

		template <CIndexInteger t_iMember, typename t_CReturnType = typename TCEvalReturnType<t_iMember>::CType>
		struct TCCallVisitorSet
		{
		public:
			template <typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static void fs_Call(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				(fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>());
			}

			template <typename t_CRet, typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static t_CRet fs_CallRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				return (fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>());
			}
			template <typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static void fs_CallFirst(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				(fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>());
			}

			template <typename t_CRet, typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static t_CRet fs_CallFirstRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				return (fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template f_Set<t_CIndex(t_iMember)>());
			}
		};

		template <CIndexInteger t_iMember>
		struct TCCallVisitorSet<t_iMember, void>
		{
		public:
			template <typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static void fs_Call(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				fg_Forward<t_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>();
			}

			template <typename t_CRet, typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static t_CRet fs_CallRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				fg_Forward<t_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>();
				return NPrivate::fg_InvalidVariant<t_CRet>();
			}

			template <typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static void fs_CallFirst(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				fg_Forward<t_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>();
				(fg_Forward<t_CVisitor>(_Visitor))(CVoidTag());
			}

			template <typename t_CRet, typename t_CThis, typename t_CVisitor>
			mark_artificial inline_small static t_CRet fs_CallFirstRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
			{
				fg_Forward<t_CThis>(_pThis)->template f_Set<t_CIndex(t_iMember)>();
				return (fg_Forward<t_CVisitor>(_Visitor))(CVoidTag());
			}
		};

		template <typename t_CType, bool t_bIsReference = NTraits::TCIsReference<t_CType>::mc_Value, bool t_bIsArray = NTraits::TCIsArray<t_CType>::mc_Value>
		struct TCEvalReturn
		{
		public:

			template <typename tf_CType0, typename tf_CType1>
			inline_small static auto fs_Value(tf_CType1 &&_pToRet) -> decltype(*_pToRet)
			{
				return *_pToRet;
			}
		};

		template <typename t_CType>
		struct TCEvalReturn<t_CType, false, true>
		{
		public:

			template <typename tf_CType0, typename tf_CType1>
			inline_small static t_CType &fs_Value(tf_CType1 &&_pToRet)
			{
				return (t_CType &)*_pToRet;
			}
		};

		template <typename t_CType>
		struct TCEvalReturn<t_CType, true, false>
		{
		public:

			template <typename tf_CType0, typename tf_CType1>
			inline_small static typename TCEnableIf<NTraits::TCIsLValueReference<tf_CType0>::mc_Value, tf_CType0>::CType fs_Value(tf_CType1 &&_pToRet)
			{
				return *(*_pToRet);
			}

			template <typename tf_CType0, typename tf_CType1>
			inline_small static typename TCEnableIf<!NTraits::TCIsLValueReference<tf_CType0>::mc_Value, tf_CType0>::CType fs_Value(tf_CType1 &&_pToRet)
			{
				return NMib::fg_Move(*(*_pToRet));
			}
		};

		template <CIndexInteger t_iMember>
		inline_small typename TCEnableIf<!NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, typename TCEvalReturnType<t_iMember>::CType>::CType fp_GetAs()
		{
			using CType = TCTypeFromMemberInt<t_iMember>;
			using CConstructType = typename TCEvalConstructType<t_iMember>::CType;
			CConstructType *pRet = (CConstructType *)mp_Storage.m_Storage;
			using CReturnType = typename TCEvalReturnType<t_iMember>::CType;
			return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
		}

		template <CIndexInteger t_iMember>
		inline_small typename TCEnableIf<NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, typename TCEvalReturnType<t_iMember>::CType>::CType fp_GetAs() const
		{
		}

		template <CIndexInteger t_iMember>
		inline_small typename TCEnableIf<!NTraits::TCIsVoid<typename TCEvalReturnTypeConst<t_iMember>::CType>::mc_Value, typename TCEvalReturnTypeConst<t_iMember>::CType>::CType fp_GetAs() const
		{
			using CType = TCTypeFromMemberInt<t_iMember>;
			using CConstructType = typename TCEvalConstructType<t_iMember>::CType;

			CConstructType const *pRet = (CConstructType const *)mp_Storage.m_Storage;

			using CReturnType = typename TCEvalReturnTypeConst<t_iMember>::CType;
			return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
		}

		template <CIndexInteger t_iMember>
		inline_small typename TCEnableIf<!NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, typename NTraits::TCAddLValueReference<typename TCEvalConstructType<t_iMember>::CType>::CType>::CType fp_GetAsStorage()
		{
			using CConstructType = typename TCEvalConstructType<t_iMember>::CType;

			CConstructType *pRet = (CConstructType *)mp_Storage.m_Storage;
			return *pRet;
		}

		template <CIndexInteger t_iMember>
		inline_small typename TCEnableIf<NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, typename TCEvalReturnType<t_iMember>::CType>::CType fp_GetAsStorage() const
		{
		}

		template <CIndexInteger t_iMember>
		inline_small typename TCEnableIf<!NTraits::TCIsVoid<typename TCEvalReturnTypeConst<t_iMember>::CType>::mc_Value, typename NTraits::TCAddLValueReference<typename NTraits::TCAddConst<typename TCEvalConstructType<t_iMember>::CType>::CType>::CType>::CType fp_GetAsStorage() const
		{
			using CConstructType = typename TCEvalConstructType<t_iMember>::CType;

			CConstructType const *pRet = (CConstructType const *)mp_Storage.m_Storage;
			return *pRet;
		}

		template <typename t_CVisitor>
		inline_always void fp_VisitStorage(t_CVisitor &&_Visitor)
		{
			auto TypeID = f_GetTypeID();

			if (TypeID == mcp_Member0Typed)
			{
				TCCallVisitorStorage<mcp_Member0>::fs_CallFirst(this, fg_Forward<t_CVisitor>(_Visitor));
				return;
			}

#if defined DMibContractConfigure_CheckEnabled
			bool bFound =
#endif
				(
					...
					||
					[&]() inline_always_lambda
					{
						if constexpr (tp_Member == mcp_Member0Typed)
							return false;
						else
						{
							if (tp_Member == TypeID)
							{
								TCCallVisitorStorage<CIndexInteger(tp_Member)>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
								return true;
							}
							return false;
						}
					}()
				)
			;

			DMibFastCheck(bFound);
		}

	public:
		template <typename t_CVisitor>
		inline_always void f_Visit(t_CVisitor &&_Visitor)
		{
			auto TypeID = f_GetTypeID();

			if (TypeID == mcp_Member0Typed)
			{
				TCCallVisitor<mcp_Member0>::fs_CallFirst(this, fg_Forward<t_CVisitor>(_Visitor));
				return;
			}

#if defined DMibContractConfigure_CheckEnabled
			bool bFound =
#endif
				(
					...
					||
					[&]() inline_always_lambda
					{
						if constexpr (tp_Member == mcp_Member0Typed)
							return false;
						else
						{
							if (tp_Member == TypeID)
							{
								TCCallVisitor<CIndexInteger(tp_Member)>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
								return true;
							}
							return false;
						}
					}()
				)
			;

			DMibFastCheck(bFound);
		}

		template <typename t_CVisitor>
		inline_always void f_Visit(t_CVisitor &&_Visitor) const
		{
			auto TypeID = f_GetTypeID();

			if (TypeID == mcp_Member0Typed)
			{
				TCCallVisitor<mcp_Member0>::fs_CallFirst(this, fg_Forward<t_CVisitor>(_Visitor));
				return;
			}

#if defined DMibContractConfigure_CheckEnabled
			bool bFound =
#endif
				(
					...
					||
					[&]() inline_always_lambda
					{
						if constexpr (tp_Member == mcp_Member0Typed)
							return false;
						else
						{
							if (tp_Member == TypeID)
							{
								TCCallVisitor<CIndexInteger(tp_Member)>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
								return true;
							}
							return false;
						}
					}()
				)
			;

			DMibFastCheck(bFound);
		}


		template <typename t_CReturn, typename t_CVisitor>
		inline_always t_CReturn f_VisitRet(t_CVisitor &&_Visitor)
		{
			auto TypeID = f_GetTypeID();

			if (TypeID == mcp_Member0Typed)
				return TCCallVisitor<mcp_Member0>::template fs_CallFirstRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));

			TCAggregateSimple<t_CReturn> Ret;

#if defined DMibContractConfigure_CheckEnabled
			bool bFound = false;
#endif
			auto Cleanup = g_OnScopeExit / [&]() inline_always_lambda
				{
#if defined DMibContractConfigure_CheckEnabled
					if (!bFound)
						return;
#endif
					Ret.f_Destruct();
				}
			;
#if defined DMibContractConfigure_CheckEnabled
			bFound =
#endif
				(
					...
					||
					[&]() inline_always_lambda
					{
						if constexpr (tp_Member == mcp_Member0Typed)
							return false;
						else
						{
							if (tp_Member == TypeID)
							{
								Ret.f_Construct(TCCallVisitor<CIndexInteger(tp_Member)>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor)));
								return true;
							}
							return false;
						}
					}()
				)
			;

			DMibFastCheck(bFound);

			return fg_Move(*Ret);
		}

		template <typename t_CReturn, typename t_CVisitor>
		inline_always t_CReturn f_VisitRet(t_CVisitor &&_Visitor) const
		{
			auto TypeID = f_GetTypeID();

			if (TypeID == mcp_Member0Typed)
				return TCCallVisitor<mcp_Member0>::template fs_CallFirstRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));

			TCAggregateSimple<t_CReturn> Ret;

#if defined DMibContractConfigure_CheckEnabled
			bool bFound = false;
#endif
			auto Cleanup = g_OnScopeExit / [&]() inline_always_lambda
				{
#if defined DMibContractConfigure_CheckEnabled
					if (!bFound)
						return;
#endif
					Ret.f_Destruct();
				}
			;
#if defined DMibContractConfigure_CheckEnabled
			bFound =
#endif
				(
					...
					||
					[&]() inline_always_lambda
					{
						if constexpr (tp_Member == mcp_Member0Typed)
							return false;
						else
						{
							if (tp_Member == TypeID)
							{
								Ret.f_Construct(TCCallVisitor<CIndexInteger(tp_Member)>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor)));
								return true;
							}
							return false;
						}
					}()
				)
			;

			DMibFastCheck(bFound);

			return fg_Move(*Ret);
		}

		template <typename t_CVisitor>
		inline_always void f_VisitCreate(t_CIndex const &_Index, t_CVisitor &&_Visitor)
		{
			if (_Index == mcp_Member0Typed)
				return TCCallVisitorSet<mcp_Member0>::fs_CallFirst(this, fg_Forward<t_CVisitor>(_Visitor));

			auto TypeID = _Index;

#if defined DMibContractConfigure_CheckEnabled
			bool bFound =
#endif
				(
					...
					||
					[&]() inline_always_lambda
					{
						if constexpr (tp_Member == mcp_Member0Typed)
							return false;
						else
						{
							if (tp_Member == TypeID)
							{
								TCCallVisitorSet<CIndexInteger(tp_Member)>::fs_CallFirst(this, fg_Forward<t_CVisitor>(_Visitor));
								return true;
							}
							return false;
						}
					}()
				)
			;

			DMibFastCheck(bFound);
		}

		template <typename t_CVisitor>
		inline_always bool f_TryVisitCreate(t_CIndex const &_Index, t_CVisitor &&_Visitor)
		{
			if (_Index == mcp_Member0Typed)
			{
				TCCallVisitorSet<mcp_Member0>::fs_CallFirst(this, fg_Forward<t_CVisitor>(_Visitor));
				return true;
			}

			auto TypeID = _Index;

			bool bFound =
				(
					...
					||
					[&]() inline_always_lambda
					{
						if constexpr (tp_Member == mcp_Member0Typed)
							return false;
						else
						{
							if (tp_Member == TypeID)
							{
								TCCallVisitorSet<CIndexInteger(tp_Member)>::fs_CallFirst(this, fg_Forward<t_CVisitor>(_Visitor));
								return true;
							}
							return false;
						}
					}()
				)
			;

			return bFound;
		}

		template <typename t_CReturn, typename t_CVisitor>
		inline_always t_CReturn f_VisitCreateReturn(t_CIndex const &_Index, t_CVisitor &&_Visitor)
		{
			if (_Index == mcp_Member0Typed)
				return TCCallVisitorSet<mcp_Member0>::template fs_CallFirstRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));

			auto TypeID = _Index;
			TCAggregateSimple<t_CReturn> Ret;

#if defined DMibContractConfigure_CheckEnabled
			bool bFound = false;
#endif
			auto Cleanup = g_OnScopeExit / [&]() inline_always_lambda
				{
#if defined DMibContractConfigure_CheckEnabled
					if (!bFound)
						return;
#endif
					Ret.f_Destruct();
				}
			;
#if defined DMibContractConfigure_CheckEnabled
			bFound =
#endif
				(
					...
					||
					[&]() inline_always_lambda
					{
						if constexpr (tp_Member == mcp_Member0Typed)
							return false;
						else
						{
							if (tp_Member == TypeID)
							{
								Ret.f_Construct(TCCallVisitorSet<CIndexInteger(tp_Member)>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor)));
								return true;
							}
							return false;
						}
					}()
				)
			;

			DMibFastCheck(bFound);

			return fg_Move(*Ret);
		}

		bool operator == (TCVariantCommon const &_Right) const;
		auto operator <=> (TCVariantCommon const &_Right) const;

	private:
		void fp_DestroyCurrent()
		{
			fp_VisitStorage(NPrivate::CVariantVisitor_Destruct());
		}

#ifdef DDebugger_VisualStudio
		void fp_ReferenceDebugInfo()
		{
			TCInitializerList<bool> Dumy =
				{
					[&]
					{
						[[maybe_unused]] TCVariantMember<t_CIndex, tp_CTypes, tp_Member> Member;
						return true;
					}
					()...
				}
			;
		}
#endif
	protected:
		template <typename t_CInType>
		struct TCEvalOneParamConstruction
		{
			using CInTypeNoRef = typename NTraits::TCRemoveReferenceStorable<t_CInType>::CType;
			using CInTypeNoRefNoQualifier = typename NTraits::TCRemoveQualifiers<CInTypeNoRef>::CType;

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
						, CIndexInteger(NPrivate::TCFirstConstructibleWith<CIndexInteger, void (t_CInType), NTraits::CCompileTimeTrue, TCVariantMember<CIndexInteger, tp_CTypes, CIndexInteger(tp_Member)>...>::mc_Value)
					>
					::mc_Value
				>
				::mc_Value
			;
		};

	private:
		template <typename t_CParam>
		struct TCIsNoThrowConstructibleWith
		{
			static constexpr CIndexInteger mc_ToConstruct = TCEvalOneParamConstruction<t_CParam>::mc_Value;

			using CTypeToConstruct = TCTypeFromMemberInt<mc_ToConstruct>;
			static constexpr bool mc_Value
				= mc_ToConstruct >= 0 && NTraits::cHasNothrowCopyConstructor<CTypeToConstruct>
				&&
				(
					NTraits::TCIsSame<typename NTraits::TCRemoveQualifiers<CTypeToConstruct>::CType, typename NTraits::TCRemoveQualifiers<t_CParam>::CType>::mc_Value
					||
					(
						!NTraits::TCIsReference<CTypeToConstruct>::mc_Value
						&& NTraits::TCIsReference<t_CParam>::mc_Value
						&& NTraits::TCIsSame<typename NTraits::TCRemoveQualifiers<CTypeToConstruct>::CType, typename NTraits::TCRemoveQualifiers<typename NTraits::TCRemoveReference<t_CParam>::CType>::CType>::mc_Value
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
		template <CIndexInteger t_iMember>
		typename TCEvalReturnType<t_iMember>::CType fp_Set()
		{
			if constexpr (NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value)
				fp_SetTypeID(t_iMember);
			else
			{
				using CConstructType = typename TCEvalConstructType<t_iMember>::CType;

				auto pRet = new(mp_Storage.m_Storage) CConstructType();

				fp_SetTypeID(t_iMember);
				using CReturnType = typename TCEvalReturnType<t_iMember>::CType;
				return TCEvalReturn<TCTypeFromMemberInt<t_iMember>>::template fs_Value<CReturnType>(pRet);
			}
		}

		template <CIndexInteger t_iMember, typename t_CParam0>
		typename TCEvalReturnType<t_iMember>::CType fp_Set(t_CParam0 &&_Param0)
			requires (NTraits::TCIsConstructorCallableWith<TCTypeFromMemberInt<t_iMember>, void (t_CParam0 &&)>::mc_Value)
		{
			using CType = TCTypeFromMemberInt<t_iMember>;
			using CConstructType = typename TCEvalConstructType<t_iMember>::CType;

			CConstructType *pRet;
			if constexpr (NTraits::TCIsReference<TCTypeFromMemberInt<t_iMember>>::mc_Value)
				pRet = new(mp_Storage.m_Storage) CConstructType(&_Param0);
			else
				pRet = new(mp_Storage.m_Storage) CConstructType(fg_Forward<t_CParam0>(_Param0));

			fp_SetTypeID(t_iMember);
			using CReturnType = typename TCEvalReturnType<t_iMember>::CType;
			return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
		}

		template <CIndexInteger t_iMember, typename t_CParam0, typename ...tp_CParams>
		typename TCEvalReturnType<t_iMember>::CType fp_Set(t_CParam0 &&_Param0, tp_CParams && ...p_Params)
			requires (NTraits::TCIsConstructorCallableWith<TCTypeFromMemberInt<t_iMember>, void (t_CParam0 &&, tp_CParams && ...)>::mc_Value)
		{
			using CType = TCTypeFromMemberInt<t_iMember>;
			using CConstructType = typename TCEvalConstructType<t_iMember>::CType;

			auto pRet = new(mp_Storage.m_Storage) CConstructType(fg_Forward<t_CParam0>(_Param0), fg_Forward<tp_CParams>(p_Params)...);
			fp_SetTypeID(t_iMember);
			using CReturnType = typename TCEvalReturnType<t_iMember>::CType;
			return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
		}

		template <CIndexInteger t_iMember>
		void fp_SetNoRet()
		{
			if constexpr (NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value)
				fp_SetTypeID(t_iMember);
			else
			{
				using CConstructType = typename TCEvalConstructType<t_iMember>::CType;
				new((void *)mp_Storage.m_Storage) CConstructType();
				fp_SetTypeID(t_iMember);
			}
		}

		template <CIndexInteger t_iMember, typename t_CParam0>
		void fp_SetNoRet(t_CParam0 &&_Param0)
			requires (NTraits::TCIsConstructorCallableWith<TCTypeFromMemberInt<t_iMember>, void (t_CParam0 &&)>::mc_Value)
		{
			using CConstructType = typename TCEvalConstructType<t_iMember>::CType ;

			if constexpr (NTraits::TCIsReference<TCTypeFromMemberInt<t_iMember>>::mc_Value)
				new(mp_Storage.m_Storage) CConstructType(&_Param0);
			else
				new(mp_Storage.m_Storage) CConstructType(fg_Forward<t_CParam0>(_Param0));

			fp_SetTypeID(t_iMember);
		}

		template <CIndexInteger t_iMember, typename t_CParam0, typename ...tp_CParams>
		void fp_SetNoRet(t_CParam0 &&_Param0, tp_CParams && ...p_Params)
			requires (NTraits::TCIsConstructorCallableWith<TCTypeFromMemberInt<t_iMember>, void (t_CParam0 &&, tp_CParams && ...)>::mc_Value)
		{
			using CConstructType = typename TCEvalConstructType<t_iMember>::CType;

			new(mp_Storage.m_Storage) CConstructType(fg_Forward<t_CParam0>(_Param0), fg_Forward<tp_CParams>(p_Params)...);
			fp_SetTypeID(t_iMember);
		}

		template <typename tf_CType, typename... tfp_CParams, mint... tfp_Indidies>
		void fp_AssignConstruct(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams, NMeta::TCIndices<tfp_Indidies...> const &)
			requires
			(
				TCEvalManyParamConstruction<void (tfp_CParams...)>::mc_Value >= 0 && mcp_FirstNothrowDefaultConstructible != -1
				&& requires()
				{
					this->fp_SetNoRet<TCEvalManyParamConstruction<void (tfp_CParams...)>::mc_Value>
						(
							fg_Forward<tfp_CParams>(fg_Get<tfp_Indidies>(_CreateParams.m_Params))...
						)
					;
				}
			)
		{

			fp_DestroyCurrent(); // Cannot throw

			try
			{
				fp_SetNoRet<TCEvalManyParamConstruction<void (tfp_CParams...)>::mc_Value>
					(
						fg_Forward<tfp_CParams>(fg_Get<tfp_Indidies>(_CreateParams.m_Params))...
					)
				;
			}
			catch (...)
			{
				fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
				throw;
			}
		}

		inline_small CIndexInteger fp_GetTypeID() const
		{
			return CIndexInteger(mp_Storage.m_CurrentType);
		}

	private:
		TCVariantCommon &fp_GetStreamable()
		{
			return *this;
		}

		TCVariantCommon const &fp_GetStreamable() const
		{
			return *this;
		}

		struct CVariantVisitor_Move
		{
			TCVariantCommon &m_This;
			CVariantVisitor_Move(TCVariantCommon &_This)
				: m_This(_This)
			{
			}

			void operator () (CVoidTag)
			{
				static constexpr CIndexInteger s_ToConstruct = TCMemberFromTypeInt<void>::mc_Value;

				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with void argument type");
				m_This.fp_SetNoRet<s_ToConstruct>();
			}

			template <typename t_CParam0>
			void operator () (t_CParam0 &&_Param0)
			{
				static constexpr CIndexInteger s_ToConstruct = TCEvalOneParamConstruction<typename NTraits::TCAddRValueReference<t_CParam0>::CType>::mc_Value;

				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with this argument type (move constructor)");
				m_This.fp_SetNoRet<s_ToConstruct>(fg_Move(_Param0));
			}
		};

		struct CVariantVisitor_Copy
		{
			TCVariantCommon &m_This;
			CVariantVisitor_Copy(TCVariantCommon &_This)
				: m_This(_This)
			{
			}

			void operator () (CVoidTag)
			{
				static constexpr CIndexInteger s_ToConstruct = TCMemberFromTypeInt<void>::mc_Value;

				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with void argument type");
				m_This.fp_SetNoRet<s_ToConstruct>();
			}

			template <typename t_CParam0>
			void operator () (t_CParam0 &&_Param0)
			{
				static constexpr CIndexInteger s_ToConstruct = TCEvalOneParamConstruction<t_CParam0>::mc_Value;

				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with this argument type (copy constructor)");

				m_This.fp_SetNoRet<s_ToConstruct>(fg_Forward<t_CParam0>(_Param0));
			}
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
				mcp_FirstNothrowDefaultConstructible != -1
				&& requires()
				{
					this->fp_SetNoRet<mcp_FirstDefaultConstructible>();
				}
			)
		{
			fp_SetNoRet<mcp_FirstDefaultConstructible>();
#ifdef DDebugger_VisualStudio
			TCVariantCommon::fp_ReferenceDebugInfo();
#endif
		}

		~TCVariantCommon()
		{
			fp_DestroyCurrent();
#ifdef DDebugger_VisualStudio
			TCVariantCommon::fp_ReferenceDebugInfo();
#endif
		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Copy/Move variant construction																	|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename tf_CIndex, typename ...tfp_CMembers>
		TCVariantCommon(TCVariantCommon<tf_CIndex, tfp_CMembers...> &&_Other)
		{
			_Other.f_Visit(CVariantVisitor_Move(*this));
#ifdef DDebugger_VisualStudio
			TCVariantCommon::fp_ReferenceDebugInfo();
#endif
		}

		TCVariantCommon(TCVariantCommon &&_Other)
		{
			_Other.f_Visit(CVariantVisitor_Move(*this));
#ifdef DDebugger_VisualStudio
			TCVariantCommon::fp_ReferenceDebugInfo();
#endif
		}

		template <typename tf_CIndex, typename ...tfp_CMembers>
		TCVariantCommon(TCVariantCommon<tf_CIndex, tfp_CMembers...> const &_Other)
		{
			_Other.f_Visit(CVariantVisitor_Copy(*this));
#ifdef DDebugger_VisualStudio
			TCVariantCommon::fp_ReferenceDebugInfo();
#endif
		}

		TCVariantCommon(TCVariantCommon const &_Other)
		{
			_Other.f_Visit(CVariantVisitor_Copy(*this));
#ifdef DDebugger_VisualStudio
			TCVariantCommon::fp_ReferenceDebugInfo();
#endif
		}

		TCVariantCommon(TCVariantCommon &_Other)
		{
			_Other.f_Visit(CVariantVisitor_Copy(*this));
#ifdef DDebugger_VisualStudio
			TCVariantCommon::fp_ReferenceDebugInfo();
#endif
		}

		template <typename tf_CIndex, typename ...tfp_CMembers>
		TCVariantCommon(TCVariantCommon<tf_CIndex, tfp_CMembers...> &_Other)
		{
			_Other.f_Visit(CVariantVisitor_Copy(*this));
#ifdef DDebugger_VisualStudio
			TCVariantCommon::fp_ReferenceDebugInfo();
#endif
		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Any other construction																			|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template
		<
			typename tf_CParam0
			, TCEnableIfType<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value >= 0> * = nullptr
		>
		TCVariantCommon(tf_CParam0 &&_Param0)
			requires requires()
			{
				this->fp_SetNoRet<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value>(fg_Forward<tf_CParam0>(_Param0));
			}
		{
			this->fp_SetNoRet<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value>(fg_Forward<tf_CParam0>(_Param0));
#ifdef DDebugger_VisualStudio
			TCVariantCommon::fp_ReferenceDebugInfo();
#endif
		}

		template
		<
			typename tf_CParam0
			, typename ...tfp_CParams
			, TCEnableIfType<TCEvalManyParamConstruction<void (tf_CParam0 &&, tfp_CParams...)>::mc_Value >= 0> * = nullptr
		>
		TCVariantCommon(tf_CParam0 &&_Param0, tfp_CParams && ...p_RestOfParams)
			requires requires()
			{
				this->fp_SetNoRet<TCEvalManyParamConstruction<void (tf_CParam0 &&, tfp_CParams...)>::mc_Value>
					(
						fg_Forward<tf_CParam0>(_Param0)
						, fg_Forward<tfp_CParams>(p_RestOfParams)...
					)
				;
			}
		{
			this->fp_SetNoRet<TCEvalManyParamConstruction<void (tf_CParam0 &&, tfp_CParams...)>::mc_Value>
				(
					fg_Forward<tf_CParam0>(_Param0)
					, fg_Forward<tfp_CParams>(p_RestOfParams)...
				)
			;
#ifdef DDebugger_VisualStudio
			TCVariantCommon::fp_ReferenceDebugInfo();
#endif
		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Copy/Move variant assignment																		|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename tf_CIndex, typename ...tfp_CMembers>
		TCVariantCommon &operator = (TCVariantCommon<tf_CIndex, tfp_CMembers...> &&_Other)
			requires (mcp_FirstNothrowDefaultConstructible != -1)
		{
			fp_DestroyCurrent(); // Cannot throw

			try
			{
				_Other.f_Visit(CVariantVisitor_Move(*this));
				return *this;
			}
			catch (...)
			{
				fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
				throw;
			}
		}

		TCVariantCommon &operator = (TCVariantCommon &&_Other)
			requires (mcp_FirstNothrowDefaultConstructible != -1 || mcp_bAllHasNothrowMoveConstructor)
		{
			fp_DestroyCurrent(); // Cannot throw

			if constexpr (mcp_bAllHasNothrowMoveConstructor)
			{
				_Other.f_Visit(CVariantVisitor_Move(*this));
				return *this;
			}
			else
			{
				try
				{
					_Other.f_Visit(CVariantVisitor_Move(*this));
					return *this;
				}
				catch (...)
				{
					fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}
		}

		template <typename tf_CIndex, typename ...tfp_CMembers>
		TCVariantCommon &operator = (TCVariantCommon<tf_CIndex, tfp_CMembers...> const &_Other)
			requires (mcp_FirstNothrowDefaultConstructible != -1)
		{
			fp_DestroyCurrent(); // Cannot throw
			try
			{
				_Other.f_Visit(CVariantVisitor_Copy(*this));
				return *this;
			}
			catch (...)
			{
				fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
				throw;
			}
		}

		TCVariantCommon &operator = (TCVariantCommon const &_Other)
			requires (mcp_FirstNothrowDefaultConstructible != -1 || mcp_bAllHasNothrowCopyConstructor)
		{
			fp_DestroyCurrent(); // Cannot throw

			if constexpr (mcp_bAllHasNothrowCopyConstructor)
			{
				_Other.f_Visit(CVariantVisitor_Copy(*this));
				return *this;
			}
			else
			{
				try
				{
					_Other.f_Visit(CVariantVisitor_Copy(*this));
					return *this;
				}
				catch (...)
				{
					fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}
		}

		TCVariantCommon &operator = (TCVariantCommon &_Other)
			requires (mcp_FirstNothrowDefaultConstructible != -1 || mcp_bAllHasNothrowCopyConstructor)
		{
			fp_DestroyCurrent(); // Cannot throw

			if constexpr (mcp_bAllHasNothrowCopyConstructor)
			{
				_Other.f_Visit(CVariantVisitor_Copy(*this));
				return *this;
			}
			else
			{
				try
				{
					_Other.f_Visit(CVariantVisitor_Copy(*this));
					return *this;
				}
				catch (...)
				{
					fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}
		}

		template <typename tf_CIndex, typename ...tfp_CMembers>
		TCVariantCommon &operator = (TCVariantCommon<tf_CIndex, tfp_CMembers...> &_Other)
			requires (mcp_FirstNothrowDefaultConstructible != -1)
		{
			fp_DestroyCurrent(); // Cannot throw
			try
			{
				_Other.f_Visit(CVariantVisitor_Copy(*this));
				return *this;
			}
			catch (...)
			{
				fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
				throw;
			}
		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Any other assignment																				|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename tf_CParam0, TCEnableIfType<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value >= 0> * = nullptr>
		TCVariantCommon &operator = (tf_CParam0 &&_Param)
			requires 
			(
				(TCIsNoThrowConstructibleWith<tf_CParam0 &&>::mc_Value || (mcp_FirstNothrowDefaultConstructible != -1))
				&& requires()
				{
					this->fp_SetNoRet<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value>(fg_Forward<tf_CParam0>(_Param)); // Cannot throw
				}
			)
		{
			if constexpr (TCIsNoThrowConstructibleWith<tf_CParam0 &&>::mc_Value)
			{
				fp_DestroyCurrent(); // Cannot throw
				fp_SetNoRet<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value>(fg_Forward<tf_CParam0>(_Param)); // Cannot throw
			}
			else
			{
				fp_DestroyCurrent(); // Cannot throw

				try
				{
					fp_SetNoRet<TCEvalOneParamConstruction<tf_CParam0 &&>::mc_Value>(fg_Forward<tf_CParam0>(_Param));
				}
				catch (...)
				{
					fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}

			return *this;
		}

		template <typename tf_CType, typename... tfp_CParams>
		TCVariantCommon &operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
			requires requires()
			{
				this->fp_AssignConstruct(fg_Move(_CreateParams), typename NMeta::TCMakeConsecutiveIndices<TCConstruct<tf_CType, tfp_CParams...>::mc_nParams>::CType());
			}
		{
			fp_AssignConstruct(fg_Move(_CreateParams), typename NMeta::TCMakeConsecutiveIndices<TCConstruct<tf_CType, tfp_CParams...>::mc_nParams>::CType());
			return *this;
		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Misc functions																					|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		inline_small t_CIndex f_GetTypeID() const
		{
			return (t_CIndex)mp_Storage.m_CurrentType;
		}

		template <typename t_CType>
		inline_small bool f_IsOfType() const
		{
			return fp_GetTypeID() == TCMemberFromTypeInt<t_CType>::mc_Value;
		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Get already known type																			|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <t_CIndex t_iMember>
		typename TCEvalReturnType<CIndexInteger(t_iMember)>::CType f_Get()
		{
			DMibFastCheck(f_GetTypeID() == t_iMember);

			return fp_GetAs<CIndexInteger(t_iMember)>();
		}

		template <t_CIndex t_iMember>
		typename TCEvalReturnTypeConst<CIndexInteger(t_iMember)>::CType f_Get() const
		{
			DMibFastCheck(f_GetTypeID() == t_iMember);

			return fp_GetAs<CIndexInteger(t_iMember)>();
		}

		template <typename t_CType>
		typename TCEvalReturnType<TCMemberFromTypeInt<t_CType>::mc_Value>::CType f_GetAsType()
			requires (TCMemberFromTypeInt<t_CType>::mc_Value >= 0)
		{
			static constexpr CIndexInteger c_ToGet = TCMemberFromTypeInt<t_CType>::mc_Value;

			DMibFastCheck(fp_GetTypeID() == c_ToGet);

			return fp_GetAs<c_ToGet>();
		}

		template <typename t_CType>
		typename TCEvalReturnTypeConst<TCMemberFromTypeInt<t_CType>::mc_Value>::CType f_GetAsType() const
			requires (TCMemberFromTypeInt<t_CType>::mc_Value >= 0)
		{
			static constexpr CIndexInteger c_ToGet = TCMemberFromTypeInt<t_CType>::mc_Value;

			DMibFastCheck(fp_GetTypeID() == c_ToGet);

			return fp_GetAs<c_ToGet>();
		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Try get already known type																		|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <t_CIndex t_iMember>
		typename TCEvalTryGetReturnType<CIndexInteger(t_iMember)>::CType f_TryGet()
		{
			if (f_GetTypeID() != t_iMember)
				return nullptr;

			return &fp_GetAs<CIndexInteger(t_iMember)>();
		}

		template <t_CIndex t_iMember>
		typename TCEvalTryGetReturnTypeConst<CIndexInteger(t_iMember)>::CType f_TryGet() const
		{
			if (f_GetTypeID() != t_iMember)
				return nullptr;

			return &fp_GetAs<CIndexInteger(t_iMember)>();
		}

		template <typename t_CType>
		typename TCEvalTryGetReturnType<TCMemberFromTypeInt<t_CType>::mc_Value>::CType f_TryGetAsType()
			requires (TCMemberFromTypeInt<t_CType>::mc_Value >= 0)
		{
			static constexpr CIndexInteger c_ToGet = TCMemberFromTypeInt<t_CType>::mc_Value;

			if (fp_GetTypeID() != c_ToGet)
				return nullptr;

			return &fp_GetAs<c_ToGet>();
		}

		template <typename t_CType>
		typename TCEvalTryGetReturnTypeConst<TCMemberFromTypeInt<t_CType>::mc_Value>::CType f_TryGetAsType() const
			requires (TCMemberFromTypeInt<t_CType>::mc_Value >= 0)
		{
			static constexpr CIndexInteger c_ToGet = TCMemberFromTypeInt<t_CType>::mc_Value;

			if (fp_GetTypeID() != c_ToGet)
				return nullptr;

			return &fp_GetAs<c_ToGet>();
		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Initialize specific member with value																|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <t_CIndex t_iMember>
		typename TCEvalReturnType<CIndexInteger(t_iMember)>::CType f_Set()
			requires
			(
				(
					NTraits::TCIsVoid<typename TCEvalReturnType<CIndexInteger(t_iMember)>::CType>::mc_Value
					|| NTraits::TCHasNothrowDefaultConstructor<TCTypeFromMemberInt<t_iMember>>::mc_Value
					|| mcp_FirstNothrowDefaultConstructible != -1
				)
				&& requires()
				{
					this->fp_Set<CIndexInteger(t_iMember)>();
				}
			)
		{
			fp_DestroyCurrent();

			if constexpr (NTraits::TCIsVoid<typename TCEvalReturnType<CIndexInteger(t_iMember)>::CType>::mc_Value)
				return fp_Set<CIndexInteger(t_iMember)>();
			else
			{
				try
				{
					return fp_Set<CIndexInteger(t_iMember)>();
				}
				catch (...)
				{
					fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}
		}

		template <t_CIndex t_iMember, typename ...tp_CParams>
		typename TCEvalReturnType<CIndexInteger(t_iMember)>::CType f_Set(tp_CParams && ...p_Params)
			requires 
			(
				mcp_FirstNothrowDefaultConstructible != -1
				&& requires()
				{
					this->fp_Set<CIndexInteger(t_iMember)>(fg_Forward<tp_CParams>(p_Params)...);
				}
			)
		{
			fp_DestroyCurrent();

			try
			{
				return fp_Set<CIndexInteger(t_iMember)>(fg_Forward<tp_CParams>(p_Params)...);
			}
			catch (...)
			{
				fp_SetNoRet<mcp_FirstNothrowDefaultConstructible>();
				throw;
			}
		}

		// Formatting

		template <typename tf_CStr>
		void f_Format(tf_CStr &o_Str) const
		{
			f_Visit
				(
					[&](auto const &_Value)
					{
						o_Str += typename tf_CStr::CFormat("{}") << _Value;
					}
				)
			;
		}


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
		template <typename t_CTypes, typename t_CIndices = typename NMeta::TCMakeConsecutiveIndices<NMeta::TCTypeList_Len<t_CTypes>::mc_Value>::CType>
		struct TCGetNonStreamableVariant
		{
		};

		template <typename ...tp_CTypes, mint ...tp_Indices>
		struct TCGetNonStreamableVariant<NMeta::TCTypeList<tp_CTypes...>, NMeta::TCIndices<tp_Indices...>>
		{
			using CType = TCVariantCommon
				<
					int32
					, TCVariantMember<int32, tp_CTypes, int32(tp_Indices)>...
				>
			;
		};
	}

	namespace NPrivate
	{
		template <typename t_CIndex, typename t_CTypes, typename t_CIndices = typename NMeta::TCMakeConsecutiveIndices<NMeta::TCTypeList_Len<t_CTypes>::mc_Value>::CType>
		struct TCGetStreamableVariant
		{
		};

		template <typename t_CIndex, typename ...tp_CTypes, mint ...tp_Indices>
		struct TCGetStreamableVariant<t_CIndex, NMeta::TCTypeList<tp_CTypes...>, NMeta::TCIndices<tp_Indices...>>
		{
			using CType = TCVariantCommon
				<
					t_CIndex
					, TCVariantMember<t_CIndex, tp_CTypes, t_CIndex(tp_Indices)>...
				>
			;
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

		TCVariant(TCVariant &&_Other)
			: CParent(fg_Move(_Other.fp_GetStreamable()))
		{

		}

		TCVariant(TCVariant &_Other)
			: CParent(_Other.fp_GetStreamable())
		{

		}

		TCVariant(TCVariant const &_Other)
			: CParent(_Other.fp_GetStreamable())
		{

		}

		TCVariant &operator = (TCVariant &&_Other)
			requires requires()
			{
				this->fp_GetStreamable() = fg_Move(_Other.fp_GetStreamable());
			}
		{
			this->fp_GetStreamable() = fg_Move(_Other.fp_GetStreamable());
			return *this;
		}

		TCVariant &operator = (TCVariant const &_Other)
			requires requires()
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
			}
		{
			this->fp_GetStreamable() = _Other.fp_GetStreamable();
			return *this;
		}

		TCVariant &operator = (TCVariant &_Other)
			requires requires()
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
			}
		{
			this->fp_GetStreamable() = _Other.fp_GetStreamable();
			return *this;
		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Any Construct																						|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename ...tfp_CParams>
		TCVariant(tfp_CParams && ...p_Param)
			: CParent(fg_Forward<tfp_CParams>(p_Param)...)
		{
		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Copy Construct																					|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename ...tfp_CParams>
		TCVariant(TCVariant<tfp_CParams...> const &_Other)
			: CParent(_Other.fp_GetStreamable())
		{
		}

		template <typename ...tfp_CParams>
		TCVariant(TCVariant<tfp_CParams...> &_Other)
			: CParent(_Other.fp_GetStreamable())
		{

		}

		template <typename ...tfp_CParams>
		TCVariant(TCVariant<tfp_CParams...> &&_Other)
			: CParent(fg_Move(_Other.fp_GetStreamable()))
		{

		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Assignment																						|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename ...tfp_CParams>
		TCVariant &operator = (TCVariant<tfp_CParams...> const &_Other)
			requires requires()
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
			}
		{
			this->fp_GetStreamable() = _Other.fp_GetStreamable();
			return *this;
		}

		template <typename ...tfp_CParams>
		TCVariant &operator = (TCVariant<tfp_CParams...> &_Other)
			requires requires()
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
			}
		{
			this->fp_GetStreamable() = _Other.fp_GetStreamable();
			return *this;
		}

		template <typename ...tfp_CParams>
		TCVariant &operator = (TCVariant<tfp_CParams...> &&_Other)
			requires requires()
			{
				this->fp_GetStreamable() = fg_Move(_Other.fp_GetStreamable());
			}
		{
			this->fp_GetStreamable() = fg_Move(_Other.fp_GetStreamable());
			return *this;
		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Any assignment																					|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename t_CParam>
		inline_small TCVariant &operator = (t_CParam &&_Param)
			requires requires()
			{
				this->CParent::operator = (fg_Forward<t_CParam>(_Param));
			}
		{
			this->CParent::operator = (fg_Forward<t_CParam>(_Param));
			return *this;
		}
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
			TCVariantVisitor_Feed(t_CStream &_Stream)
				: m_Stream(_Stream)
			{
			}

			void operator () (CVoidTag)
			{
			}

			template <typename t_CType>
			void operator () (t_CType &&_Data)
			{
				m_Stream << fg_Forward<t_CType>(_Data);
			}

			t_CStream &m_Stream;
		};

		template <typename t_CStream>
		struct TCVariantVisitor_FeedMove
		{
			TCVariantVisitor_FeedMove(t_CStream &_Stream)
				: m_Stream(_Stream)
			{
			}

			void operator () (CVoidTag)
			{
			}

			template <typename t_CType>
			void operator () (t_CType &&_Data)
			{
				m_Stream << fg_Move(_Data);
			}

			t_CStream &m_Stream;
		};

		template <typename t_CStream>
		struct TCVariantVisitor_Consume
		{
			TCVariantVisitor_Consume(t_CStream &_Stream)
				: m_Stream(_Stream)
			{
			}
			void operator () (CVoidTag)
			{
			}

			template <typename t_CType>
			void operator () (t_CType &&_Data)
			{
				m_Stream >> fg_Forward<t_CType>(_Data);
			}

			t_CStream &m_Stream;
		};
	}

	template <typename t_CStream, typename t_CIndex, typename ...tp_CMembers>
	class TCBinaryStreamTypeReference<t_CStream, NStorage::TCVariantCommon<t_CIndex, tp_CMembers...>>
	{
		using CStreamableVariant = NStorage::TCVariantCommon<t_CIndex, tp_CMembers...>;

	public:
		static constexpr void fs_Feed(t_CStream &_Stream, CStreamableVariant const &_Data)
		{
			_Stream << _Data.f_GetTypeID();
			_Data.f_Visit(NPrivate::TCVariantVisitor_Feed<t_CStream>(_Stream));
		}

		static constexpr void fs_Feed(t_CStream &_Stream, CStreamableVariant &&_Data)
		{
			_Stream << _Data.f_GetTypeID();
			_Data.f_Visit(NPrivate::TCVariantVisitor_FeedMove<t_CStream>(_Stream));
		}

		static constexpr void fs_Consume(t_CStream &_Stream, CStreamableVariant &_Data)
		{
			typename CStreamableVariant::CIndexType TypeID;
			_Stream >> TypeID;
			bool bSuccess = _Data.f_TryVisitCreate(TypeID, NPrivate::TCVariantVisitor_Consume<t_CStream>(_Stream));
			if (!bSuccess)
				DMibErrorStream(NStr::CStr::CFormat("Unsupported type '{}' in variant") << TypeID);
		}
	};
}

namespace NMib
{
	template <typename t_CVisitor, typename t_CToVisit0>
	void fg_Visit(t_CVisitor &&_Visitor, t_CToVisit0 &&_ToVisit0)
	{
		fg_Forward<t_CToVisit0>(_ToVisit0).f_Visit(fg_Forward<t_CVisitor>(_Visitor));
	}

	template <typename t_CReturn, typename t_CVisitor, typename t_CToVisit0>
	t_CReturn fg_VisitRet(t_CVisitor &&_Visitor, t_CToVisit0 &&_ToVisit0)
	{
		return fg_Forward<t_CToVisit0>(_ToVisit0).template f_VisitRet<t_CReturn>(fg_Forward<t_CVisitor>(_Visitor));
	}

	template <typename t_CRet, typename t_CVisitor, typename t_CToVisit>
	struct TCInnerVisitor
	{
		TCInnerVisitor(t_CVisitor _Visitor, t_CToVisit _ToVisit)
			: m_Visitor(_Visitor)
			, m_ToVisit(_ToVisit)
		{
		}

		template <typename t_CInnerVisitor, typename t_CValue>
		struct TCValueVisitor
		{
			TCValueVisitor(t_CInnerVisitor _Visitor, t_CValue _Value)
				: m_Visitor(_Visitor)
				, m_Value(_Value)
			{
			}

			template <typename t_CType>
			t_CRet operator () (t_CType &&_Type)
			{
				return m_Visitor(fg_Forward<t_CValue>(m_Value), fg_Forward<t_CType>(_Type));
			}

			t_CInnerVisitor m_Visitor;
			t_CValue m_Value;
		};

		template <typename t_CType>
		t_CRet operator () (t_CType &&_Value)
		{
			TCValueVisitor<t_CVisitor, t_CType> Visitor(m_Visitor, _Value);

			return fg_VisitRet<t_CRet>(Visitor, fg_Forward<t_CToVisit>(m_ToVisit));
		}

		t_CVisitor m_Visitor;
		t_CToVisit m_ToVisit;
	};

	template <typename t_CVisitor, typename t_CToVisit>
	struct TCInnerVisitor<void, t_CVisitor, t_CToVisit>
	{
		TCInnerVisitor(t_CVisitor _Visitor, t_CToVisit _ToVisit)
			: m_Visitor(_Visitor)
			, m_ToVisit(_ToVisit)
		{
		}

		template <typename t_CInnerVisitor, typename t_CValue>
		struct TCValueVisitor
		{
			TCValueVisitor(t_CInnerVisitor _Visitor, t_CValue _Value)
				: m_Visitor(_Visitor)
				, m_Value(_Value)
			{
			}

			template <typename t_CType>
			void operator () (t_CType &&_Type)
			{
				m_Visitor(fg_Forward<t_CValue>(m_Value), fg_Forward<t_CType>(_Type));
			}

			t_CInnerVisitor m_Visitor;
			t_CValue m_Value;
		};

		template <typename t_CType>
		void operator () (t_CType &&_Value)
		{
			TCValueVisitor<t_CVisitor, t_CType> Visitor(m_Visitor, _Value);

			fg_Visit(Visitor, fg_Forward<t_CToVisit>(m_ToVisit));
		}

		t_CVisitor m_Visitor;
		t_CToVisit m_ToVisit;
	};

	template <typename t_CVisitor, typename t_CToVisit0, typename t_CToVisit1>
	void fg_Visit(t_CVisitor &&_Visitor, t_CToVisit0 &&_ToVisit0, t_CToVisit1 &&_ToVisit1)
	{
		TCInnerVisitor<void, t_CVisitor, t_CToVisit1> Visitor(_Visitor, _ToVisit1);
		fg_Visit(Visitor, _ToVisit0);
	}

	template <typename t_CRet, typename t_CVisitor, typename t_CToVisit0, typename t_CToVisit1>
	t_CRet fg_VisitRet(t_CVisitor &&_Visitor, t_CToVisit0 &&_ToVisit0, t_CToVisit1 &&_ToVisit1)
	{
		TCInnerVisitor<t_CRet, t_CVisitor, t_CToVisit1> Visitor(_Visitor, _ToVisit1);
		return fg_VisitRet<t_CRet>(Visitor, _ToVisit0);
	}
}

namespace NMib::NStorage
{
	namespace NPrivate
	{
		struct CCompareVariant_Spaceship
		{
			template <typename tf_CLeft, typename tf_CRight>
			COrdering_Strong operator()(tf_CLeft const &_Left, tf_CRight const &_Right) const
			{
				return COrdering_Strong::equivalent;
			}

			template <typename tf_CSame>
			auto operator()(tf_CSame const &_Left, tf_CSame const &_Right) const
			{
				return _Left <=> _Right;
			}
		};

		struct CCompareVariant_Equal
		{
			template <typename tf_CLeft, typename tf_CRight>
			bool operator()(tf_CLeft const &_Left, tf_CRight const &_Right) const
			{
				return false;
			}

			template <typename tf_CSame>
			bool operator()(tf_CSame const &_Left, tf_CSame const &_Right) const
			{
				return _Left == _Right;
			}
		};

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
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	bool TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::operator == (TCVariantCommon const &_Right) const
	{
		if (f_GetTypeID() != _Right.f_GetTypeID())
			return false;

		return fg_VisitRet<bool>(NPrivate::CCompareVariant_Equal(), *this, _Right);
	}

	template <typename t_CIndex, typename ...tp_CTypes, t_CIndex ...tp_Member>
	auto TCVariantCommon<t_CIndex, TCVariantMember<t_CIndex, tp_CTypes, tp_Member>...>::operator <=> (TCVariantCommon const &_Right) const
	{
		using COrdering = TCCommonOrderingType
			<
				decltype
				(
					NPrivate::fg_GetTypeRefOrVoidTag<tp_CTypes>() <=> NPrivate::fg_GetTypeRefOrVoidTag<tp_CTypes>()
				)...
			>
		;

		if (auto Result = f_GetTypeID() <=> _Right.f_GetTypeID(); Result != 0)
			return COrdering(Result);

		return fg_VisitRet<COrdering>(NPrivate::CCompareVariant_Spaceship(), *this, _Right);
	}

}

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif
