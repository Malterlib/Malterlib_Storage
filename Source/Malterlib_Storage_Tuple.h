// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#ifdef DMibContainer_TupleInternal

#define DMibTupleTemplate NMib::NStorage::TCTuple

#include <Mib/Storage/Reference>
#include <Mib/Meta/Meta>

namespace NMib::NStorage
{
	template <typename... t_PCTypes>
	class TCTuple;

	template <typename t_CTuple>
	class TCTuple_Len;

	// Support any qualifiers
	template <typename t_CType>
	class TCTuple_Len<t_CType const>
		: public TCTuple_Len<t_CType>
	{
	};
	template <typename t_CType>
	class TCTuple_Len<t_CType volatile>
		: public TCTuple_Len<t_CType>
	{
	};
	template <typename t_CType>
	class TCTuple_Len<t_CType const volatile>
		: public TCTuple_Len<t_CType>
	{
	};

	template <typename... t_PCTypes>
	class TCTuple_Len<TCTuple<t_PCTypes...>>
		: public NMeta::TCTypeList_Len<NMeta::TCTypeList<t_PCTypes...>>
	{
	};

	template <mint t_Index, typename t_CType>
	class TCTuple_Get;

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, TCTuple<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, const TCTuple<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, const NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, volatile TCTuple<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, volatile NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, const volatile TCTuple<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, const volatile NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, NMeta::TCTypeList<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, const NMeta::TCTypeList<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, const NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, volatile NMeta::TCTypeList<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, volatile NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, const volatile NMeta::TCTypeList<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, const volatile NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};
}

#include "Private/Malterlib_Storage_Tuple_Helpers.h"

namespace NMib::NStorage
{
	template <typename... t_PCTypes>
	class TCTuple
		: private NPrivate::TCDefaultCopy
		<
			NTraits::TCIsConstructorCallableWith
			<
				NPrivate::TCTupleImp<typename NMeta::TCMakeConsecutiveIndices<sizeof...(t_PCTypes)>::CType, t_PCTypes...>
				, void (TCTuple<t_PCTypes...> const &)
			>::mc_Value
			, t_PCTypes...
		>
		, private NPrivate::TCDefaultMove
		<
			NTraits::TCIsConstructorCallableWith
			<
				NPrivate::TCTupleImp<typename NMeta::TCMakeConsecutiveIndices<sizeof...(t_PCTypes)>::CType, t_PCTypes...>
				, void (TCTuple<t_PCTypes...> &&)
			>::mc_Value
			, t_PCTypes...
		>
		, private NPrivate::TCDefaultAssign
		<
			NTraits::TCIsOperatorCallableWith_Assign
			<
				NPrivate::TCTupleImp<typename NMeta::TCMakeConsecutiveIndices<sizeof...(t_PCTypes)>::CType, t_PCTypes...>
				, void (TCTuple<t_PCTypes...> const &)
			>::mc_Value
			, t_PCTypes...
		>
		, private NPrivate::TCDefaultMoveAssign
		<
			NTraits::TCIsOperatorCallableWith_Assign
			<
				NPrivate::TCTupleImp<typename NMeta::TCMakeConsecutiveIndices<sizeof...(t_PCTypes)>::CType, t_PCTypes...>
				, void (TCTuple<t_PCTypes...> &&)
			>::mc_Value
			, t_PCTypes...
		>
		, private NPrivate::TCTupleImp<typename NMeta::TCMakeConsecutiveIndices<sizeof...(t_PCTypes)>::CType, t_PCTypes...>
	{
		typedef NPrivate::TCTupleImp<typename NMeta::TCMakeConsecutiveIndices<sizeof...(t_PCTypes)>::CType, t_PCTypes...> CBase;

		template <mint tf_Index, typename tf_CType>
		typename NTraits::TCCopyQualifiersAndReference<tf_CType &&, typename TCTuple_Get<tf_Index, typename NPrivate::TCIsTuple<tf_CType &&>::CType>::CType>::CType
		friend NMib::fg_Get(tf_CType &&_Tuple) noexcept;

		template <mint tf_Index, typename tf_CType>
		typename NTraits::TCPromoteQualifiersAndReference<tf_CType &&, typename TCTuple_Get<tf_Index, typename NPrivate::TCIsTuple<tf_CType &&>::CType>::CType>::CType
		friend NMib::fg_GetForward(tf_CType &&_Tuple) noexcept;

	public:

		inline_always
		constexpr TCTuple()
			noexcept(NMeta::TCAllIsTrue<NTraits::TCHasNothrowDefaultConstructor<t_PCTypes>::mc_Value...>::mc_Value)
		{
		}

		// Free params constructible
		template
		<
			typename... tf_PCTypes
			, typename TCEnableIf
			<
				sizeof...(tf_PCTypes) <= sizeof...(t_PCTypes)
				&& NMeta::TCAllIsTrue
				<
					NTraits::TCIsConstructorCallableWith
					<
						NPrivate::TCTupleLeaf<0, t_PCTypes>
						, void
						(
							tf_PCTypes &&
						)
					>::mc_Value...
				>::mc_Value
				, bool
			>::CType = false
		>
		inline_always explicit
		TCTuple(tf_PCTypes &&..._Params)
			noexcept
			(
				NTraits::TCIsConstructorNothrowCallableWith
				<
					CBase
					, void
					(
						typename NMeta::TCMakeConsecutiveIndices<sizeof...(tf_PCTypes)>::CType
						, typename NPrivate::TCTuple_MakePromotedLValueRefList<TCTuple, sizeof...(tf_PCTypes)>::CType
						, typename NMeta::TCMakeConsecutiveIndices<sizeof...(t_PCTypes), sizeof...(tf_PCTypes)>::CType()
						, typename NPrivate::TCTuple_MakePromotedLValueRefList<TCTuple, sizeof...(t_PCTypes), sizeof...(tf_PCTypes)>::CType()
						, tf_PCTypes &&...
					)
				>::mc_Value
			)
			: CBase
			(
				typename NMeta::TCMakeConsecutiveIndices<sizeof...(tf_PCTypes)>::CType()
				, typename NPrivate::TCTuple_MakePromotedLValueRefList<TCTuple, sizeof...(tf_PCTypes)>::CType()
				, typename NMeta::TCMakeConsecutiveIndices<sizeof...(t_PCTypes), sizeof...(tf_PCTypes)>::CType()
				, typename NPrivate::TCTuple_MakePromotedLValueRefList<TCTuple, sizeof...(t_PCTypes), sizeof...(tf_PCTypes)>::CType()
				, fg_Forward<tf_PCTypes>(_Params)...
			)
		{
		}

		// Other tuple constructible
		template
		<
			typename tf_CTuple
			, typename TCEnableIf
			<
				NPrivate::TCTuple_IsConstructible<tf_CTuple &&, TCTuple>::mc_Value
				, bool
			>::CType = false
		>
		inline_always explicit
		TCTuple(tf_CTuple &&_Param)
			noexcept(NTraits::TCIsConstructorNothrowCallableWith<CBase, void (tf_CTuple &&)>::mc_Value)
			: CBase(fg_Forward<tf_CTuple>(_Param))
		{
		}

		// Other tuple assignable
		template
		<
			typename tf_CTuple
			, typename TCEnableIf
			<
				NPrivate::TCTuple_IsAssignable<tf_CTuple &&, TCTuple>::mc_Value
				, bool
			>::CType = false
		>
		inline_always
		TCTuple &operator =(tf_CTuple &&_Param)
			noexcept(NTraits::TCIsOperatorNothrowCallableWith_Assign<CBase, void (tf_CTuple &&)>::mc_Value)
		{
			CBase::operator =(fg_Forward<tf_CTuple>(_Param));
			return *this;
		}
	};

	template <>
	class TCTuple<>
	{
	public:
		inline_always
		constexpr TCTuple() noexcept
		{
		}
	};

	// fg_Get
}

namespace NMib
{

	template <mint tf_Index, typename tf_CType>
	typename NTraits::TCCopyQualifiersAndReference<tf_CType &&, typename NStorage::TCTuple_Get<tf_Index, typename NStorage::NPrivate::TCIsTuple<tf_CType &&>::CType>::CType>::CType
	fg_Get(tf_CType &&_Tuple) noexcept
	{
		typedef typename NStorage::TCTuple_Get<tf_Index, typename NStorage::NPrivate::TCIsTuple<tf_CType &&>::CType>::CType CType;
		return fg_Forward<typename NTraits::TCCopyQualifiersAndReference<tf_CType &&, CType>::CType >
			(
				static_cast
				<
					typename NTraits::TCCopyQualifiersAndReference<tf_CType &&, NStorage::NPrivate::TCTupleLeaf<tf_Index, CType>>::CType
				>(_Tuple).f_Get()
			)
		;
	}

	template <mint tf_Index, typename tf_CType>
	typename NTraits::TCPromoteQualifiersAndReference<tf_CType &&, typename NStorage::TCTuple_Get<tf_Index, typename NStorage::NPrivate::TCIsTuple<tf_CType &&>::CType>::CType>::CType
	fg_GetForward(tf_CType &&_Tuple) noexcept
	{
		typedef typename TCTuple_Get<tf_Index, typename NStorage::NPrivate::TCIsTuple<tf_CType &&>::CType>::CType CType;
		return fg_Forward<typename NTraits::TCPromoteQualifiersAndReference<tf_CType &&, CType>::CType >
			(
				static_cast
				<
					typename NTraits::TCCopyQualifiersAndReference<tf_CType &&, NStorage::NPrivate::TCTupleLeaf<tf_Index, CType>>::CType
				>(_Tuple).f_Get()
			)
		;
	}
}

namespace NMib::NStorage
{
	// fg_TupleReferences

	template <typename... t_PCTypes>
	inline_always
	TCTuple<t_PCTypes &...>
	fg_TupleReferences(t_PCTypes &..._Params) noexcept
	{
		return TCTuple<t_PCTypes &...>(_Params...);
	}

	namespace NPrivate
	{

		template <typename t_CType>
		struct TCMakeTupleReturnHelper0
		{
			typedef t_CType CType;
		};

		template <typename t_CType>
		struct TCMakeTupleReturnHelper0<NStorage::TCReference<t_CType>>
		{
			typedef t_CType& CType;
		};

		template <typename t_CType>
		struct TCMakeTupleReturnHelper
		{
			typedef typename TCMakeTupleReturnHelper0<typename NTraits::TCDecay<t_CType>::CType>::CType CType;
		};
	}

	template <typename... tf_PCTypes>
	inline_always
	TCTuple<typename NPrivate::TCMakeTupleReturnHelper<tf_PCTypes>::CType...>
	fg_Tuple(tf_PCTypes &&..._Params)
	{
		return TCTuple<typename NPrivate::TCMakeTupleReturnHelper<tf_PCTypes &&>::CType...>(fg_Forward<tf_PCTypes>(_Params)...);
	}

	template <typename... tf_PCTypes>
	inline_always
	TCTuple<tf_PCTypes &&...>
	fg_TuplePerfectForward(tf_PCTypes &&..._Params) noexcept
	{
		TCTuple<tf_PCTypes &&...> ToRet(fg_Forward<tf_PCTypes>(_Params)...);
		return ToRet;
	}

	template <typename tf_CTupleLeft, typename tf_CTupleRight>
	inline_always
	typename TCEnableIf
		<
			NPrivate::TCIsTuple<tf_CTupleLeft>::mc_Value
			&& NPrivate::TCIsTuple<tf_CTupleRight>::mc_Value
			&& NPrivate::TCIsTuple<tf_CTupleLeft>::mc_nTypes == NPrivate::TCIsTuple<tf_CTupleRight>::mc_nTypes
			, bool
		>::CType
	operator == (tf_CTupleLeft &&_Left, tf_CTupleRight &&_Right)
	{
		return NPrivate::TCTupleEqualImp
			<
				0
				, TCTuple_Len<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CTupleLeft>::CType>::mc_Value
			>
			()(fg_Forward<tf_CTupleLeft>(_Left), fg_Forward<tf_CTupleRight>(_Right))
		;
	}

	template <typename tf_CTupleLeft, typename tf_CTupleRight>
	inline_always
	typename TCEnableIf
		<
			NPrivate::TCIsTuple<tf_CTupleLeft>::mc_Value
			&& NPrivate::TCIsTuple<tf_CTupleRight>::mc_Value
			&& NPrivate::TCIsTuple<tf_CTupleLeft>::mc_nTypes == NPrivate::TCIsTuple<tf_CTupleRight>::mc_nTypes
			, bool
		>::CType
	operator < (tf_CTupleLeft &&_Left, tf_CTupleRight &&_Right)
	{
		return NPrivate::TCTupleLessImp
			<
				0
				, TCTuple_Len<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CTupleLeft>::CType>::mc_Value
			>
			()(fg_Forward<tf_CTupleLeft>(_Left), fg_Forward<tf_CTupleRight>(_Right))
		;
	}

	// tuple_cat

	namespace NPrivate
	{
		template <typename t_CType0, typename t_CType1>
		struct TCTupleCatImpType;

		template <typename... t_PCTypes0, typename... t_PCTypes1>
		struct TCTupleCatImpType<TCTuple<t_PCTypes0...>, NMeta::TCTypeList<t_PCTypes1...>>
		{
			typedef TCTuple<t_PCTypes0..., t_PCTypes1...> CType;
		};

		template <typename t_CResultTuple, bool t_bIsTupleCompatible, typename... t_PCOtherTuples>
		struct TCTupleCatReturnHelper_1
		{
		};

		template <typename... t_PCResultTypes, typename t_CTupleToAdd>
		struct TCTupleCatReturnHelper_1<TCTuple<t_PCResultTypes...>, true, t_CTupleToAdd>
		{
			typedef typename TCTupleCatImpType<TCTuple<t_PCResultTypes...>,
			typename NPrivate::TCTuple_MakePromotedLValueRefList<typename NTraits::TCRemoveReference<t_CTupleToAdd>::CType>::CType>::CType CType;
		};

		template <typename... t_PCResultTypes, typename t_CTupleToAdd0, typename t_CTupleToAdd1, typename... t_PCTuplesToAdd>
		struct TCTupleCatReturnHelper_1<TCTuple<t_PCResultTypes...>, true, t_CTupleToAdd0, t_CTupleToAdd1, t_PCTuplesToAdd...>
			: public TCTupleCatReturnHelper_1
			<
				typename TCTupleCatImpType
				<
					TCTuple<t_PCResultTypes...>
					, typename NPrivate::TCTuple_MakePromotedLValueRefList<typename NTraits::TCRemoveReference<t_CTupleToAdd0>::CType>::CType
				>::CType
				, NPrivate::TCTuple_CompatibleType<typename NTraits::TCRemoveReference<t_CTupleToAdd1>::CType>::mc_Value
				, t_CTupleToAdd1
				, t_PCTuplesToAdd...
			>
		{
		};

		template <typename... t_PCTuples>
		struct TCTupleCatReturnHelper;

		template <typename t_CTuple, typename... t_PCTuples>
		struct TCTupleCatReturnHelper<t_CTuple, t_PCTuples...>
			: public TCTupleCatReturnHelper_1
			<
				TCTuple<>,
				NPrivate::TCTuple_CompatibleType<typename NTraits::TCRemoveReference<t_CTuple>::CType>::mc_Value
				, t_CTuple
				, t_PCTuples...
			>
		{
		};

		template <>
		struct TCTupleCatReturnHelper<>
		{
			typedef TCTuple<> CType;
		};

		template <typename t_CReturnTuple, typename t_CReturnIndices, typename t_CTuple0, typename... t_PCTuples>
		struct TCTupleCatReturnHelperRefImp;

		template <typename... t_PReturnTypes, mint ...t_PReturnIndices, typename t_CTuple0>
		struct TCTupleCatReturnHelperRefImp<TCTuple<t_PReturnTypes...>, NMeta::TCIndices<t_PReturnIndices...>, t_CTuple0>
		{
			typedef typename NTraits::TCRemoveReference<t_CTuple0>::CType CTuple0NoRef;
			typedef TCTuple
				<
					t_PReturnTypes...
					, typename NTraits::TCPromoteQualifiersAndReference<t_CTuple0, typename TCTuple_Get<t_PReturnIndices, CTuple0NoRef>::CType>::CType...
				> CType
			;
		};

		template <typename... t_PReturnTypes, mint ...t_PReturnIndices, typename t_CTuple0, typename t_CTuple1, typename... t_PCTuples>
		struct TCTupleCatReturnHelperRefImp<TCTuple<t_PReturnTypes...>, NMeta::TCIndices<t_PReturnIndices...>, t_CTuple0, t_CTuple1, t_PCTuples...>
			: public TCTupleCatReturnHelperRefImp
			<
				TCTuple
				<
					t_PReturnTypes...
					, typename NTraits::TCPromoteQualifiersAndReference
					<
						t_CTuple0
						, typename TCTuple_Get<t_PReturnIndices, typename NTraits::TCRemoveReference<t_CTuple0>::CType>::CType
					>::CType...
				>
				, typename NMeta::TCMakeConsecutiveIndices<TCTuple_Len<typename NTraits::TCRemoveReference<t_CTuple1>::CType>::mc_Value>::CType
				, t_CTuple1
				, t_PCTuples...
			>
		{
		};

		template <typename t_CTuple0, typename... t_PCTuples>
		struct TCTupleCatReturnHelperRef
			: public TCTupleCatReturnHelperRefImp
			<
				TCTuple<>
				, typename NMeta::TCMakeConsecutiveIndices<TCTuple_Len<typename NTraits::TCRemoveReference<t_CTuple0>::CType>::mc_Value>::CType
				, t_CTuple0
				, t_PCTuples...
			>
		{
		};

		template <typename t_CTuple, typename t_CReturnIndices, typename t_CIndices1>
		struct TCTupleCatImp;

		template <typename... t_PReturnTypes, mint ...t_PReturnIndices, mint ...t_CIndices1>
		struct TCTupleCatImp<TCTuple<t_PReturnTypes...>, NMeta::TCIndices<t_PReturnIndices...>, NMeta::TCIndices<t_CIndices1...>>
		{
			template <typename tf_CTuple0>
			inline_always
			typename TCTupleCatReturnHelperRef<TCTuple<t_PReturnTypes...> &&, tf_CTuple0 &&>::CType
			operator()(TCTuple<t_PReturnTypes...> &&_Tuple, tf_CTuple0 &&_TupleToAdd)
			{
				return fg_TuplePerfectForward
					(
						fg_GetForward<t_PReturnIndices>(_Tuple)...
						, fg_GetForward<t_CIndices1>(fg_Forward<tf_CTuple0>(_TupleToAdd))...
					)
				;
			}

			template <typename tf_CTuple0, typename tf_CTuple1, typename... tf_PCTuples>
			inline_always
			typename TCTupleCatReturnHelperRef<TCTuple<t_PReturnTypes...> &&, tf_CTuple0 &&, tf_CTuple1 &&, tf_PCTuples &&...>::CType
			operator()(TCTuple<t_PReturnTypes...> &&_Tuple, tf_CTuple0 &&_TupleToAdd0, tf_CTuple1 &&_TupleToAdd1, tf_PCTuples &&..._OtherTuples)
			{
				typedef typename NTraits::TCRemoveReference<tf_CTuple0>::CType CTuple0NoRef;
				typedef typename NTraits::TCRemoveReference<tf_CTuple1>::CType CTuple1NoRef;
				return
					TCTupleCatImp
					<
						TCTuple
						<
							t_PReturnTypes...
							, typename NTraits::TCPromoteQualifiersAndReference<tf_CTuple0 &&, typename TCTuple_Get<t_CIndices1, CTuple0NoRef>::CType>::CType...
						>
						, typename NMeta::TCMakeConsecutiveIndices<sizeof...(t_PReturnTypes) + TCTuple_Len<CTuple0NoRef>::mc_Value>::CType
						, typename NMeta::TCMakeConsecutiveIndices<TCTuple_Len<CTuple1NoRef>::mc_Value>::CType
					>
					()
					(
						fg_TuplePerfectForward
						(
							fg_GetForward<t_PReturnIndices>(_Tuple)...
							, fg_GetForward<t_CIndices1>(fg_Forward<tf_CTuple0>(_TupleToAdd0))...
						)
						, fg_Forward<tf_CTuple1>(_TupleToAdd1)
						, fg_Forward<tf_PCTuples>(_OtherTuples)...
					)
				;
			}
		};
	}

	inline_always
	TCTuple<>
	fg_TupleConcatenate()
	{
		return TCTuple<>();
	}

	template <typename tf_CFirstTuple, typename... tf_PCOtherTuples>
	inline_always
	typename NPrivate::TCTupleCatReturnHelper<tf_CFirstTuple, tf_PCOtherTuples...>::CType
	fg_TupleConcatenate(tf_CFirstTuple &&_FirstTuple, tf_PCOtherTuples &&..._OtherTuples)
	{
		typedef typename NTraits::TCRemoveReference<tf_CFirstTuple>::CType CFirstTuple;

		return
			typename NPrivate::TCTupleCatReturnHelper<tf_CFirstTuple, tf_PCOtherTuples...>::CType
			(
				NPrivate::TCTupleCatImp
				<
					TCTuple<>
					, NMeta::TCIndices<>
					, typename NMeta::TCMakeConsecutiveIndices<TCTuple_Len<CFirstTuple>::mc_Value>::CType
				>
				()
				(
					TCTuple<>()
					, fg_Forward<tf_CFirstTuple>(_FirstTuple)
					, fg_Forward<tf_PCOtherTuples>(_OtherTuples)...
				)
			)
		;
	}

}

#else

#include <tuple>
#include <Mib/Meta/Meta>

namespace NMib::NStorage
{
	template <typename... tp_CTypes>
	using TCTuple = std::tuple<tp_CTypes...>;
#define DMibTupleTemplate std::tuple

	template <typename t_CTuple>
	class TCTuple_Len;

	// Support any qualifiers
	template <typename t_CType>
	class TCTuple_Len<t_CType const>
		: public TCTuple_Len<t_CType>
	{
	};
	template <typename t_CType>
	class TCTuple_Len<t_CType volatile>
		: public TCTuple_Len<t_CType>
	{
	};
	template <typename t_CType>
	class TCTuple_Len<t_CType const volatile>
		: public TCTuple_Len<t_CType>
	{
	};

	template <typename... t_PCTypes>
	class TCTuple_Len<TCTuple<t_PCTypes...>>
		: public NMeta::TCTypeList_Len<NMeta::TCTypeList<t_PCTypes...>>
	{
	};

	template <mint t_Index, typename t_CType>
	class TCTuple_Get;

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, TCTuple<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, const TCTuple<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, const NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, volatile TCTuple<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, volatile NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, const volatile TCTuple<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, const volatile NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, NMeta::TCTypeList<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, const NMeta::TCTypeList<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, const NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, volatile NMeta::TCTypeList<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, volatile NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};

	template <mint t_Index, typename... t_PCTypes>
	class TCTuple_Get<t_Index, const volatile NMeta::TCTypeList<t_PCTypes...>>
	{
	public:
		typedef typename NMeta::TCTypeList_Get<t_Index, const volatile NMeta::TCTypeList<t_PCTypes...>>::CType CType;
	};
}

namespace NMib
{
	template <mint tf_Index, typename tf_CType>
	mark_artificial inline_always auto fg_Get(tf_CType &&_Tuple) noexcept -> typename NTraits::TCPromoteQualifiers<tf_CType, decltype(std::get<tf_Index>(fg_RemoveQualifiers(fg_Forward<tf_CType>(_Tuple))))>::CType
	{
		return fg_Forward<typename NTraits::TCPromoteQualifiers<tf_CType, decltype(std::get<tf_Index>(fg_RemoveQualifiers(fg_Forward<tf_CType>(_Tuple))))>::CType >(std::get<tf_Index>(fg_RemoveQualifiers(fg_Forward<tf_CType>(_Tuple))));
	}

	template <mint tf_Index, typename tf_CType>
	mark_artificial inline_always auto fg_GetForward(tf_CType &&_Tuple) noexcept -> typename NTraits::TCPromoteQualifiersAndReference<tf_CType, decltype(std::get<tf_Index>(fg_Forward<tf_CType>(_Tuple)))>::CType
	{
		return fg_Forward<typename NTraits::TCPromoteQualifiersAndReference<tf_CType, decltype(std::get<tf_Index>(fg_Forward<tf_CType>(_Tuple)))>::CType >(std::get<tf_Index>(fg_Forward<tf_CType>(_Tuple)));
	}
}

namespace NMib::NStorage
{
	template <typename... t_PCTypes>
	inline_always TCTuple<t_PCTypes &...> fg_TupleReferences(t_PCTypes &...p_Params) noexcept
	{
		return TCTuple<t_PCTypes &...>(p_Params...);
	}

	template <typename... tfp_CParams>
	auto fg_TupleReferences(tfp_CParams &&... p_Params) -> decltype(std::tie(fg_Forward<tfp_CParams>(p_Params)...))
	{
		return std::tie(fg_Forward<tfp_CParams>(p_Params)...);
	}

	static inline_always TCTuple<> fg_TupleReferences() noexcept
	{
		return TCTuple<>();
	}

	template <typename... tfp_CParams>
	auto fg_Tuple(tfp_CParams &&... p_Params) -> decltype(std::make_tuple(fg_Forward<tfp_CParams>(p_Params)...))
	{
		return std::make_tuple(fg_Forward<tfp_CParams>(p_Params)...);
	}

	template <typename... tfp_CParams>
	auto fg_TuplePerfectForward(tfp_CParams &&... p_Params) -> decltype(std::forward_as_tuple(fg_Forward<tfp_CParams>(p_Params)...))
	{
		return std::forward_as_tuple(fg_Forward<tfp_CParams>(p_Params)...);
	}


	template <typename... tfp_CParams>
	auto fg_TupleConcatenate(tfp_CParams &&... p_Params) -> decltype(std::tuple_cat(fg_Forward<tfp_CParams>(p_Params)...))
	{
		return std::tuple_cat(fg_Forward<tfp_CParams>(p_Params)...);
	}

	template <typename tf_FFunctor, typename tf_CTuple>
	auto fg_TupleApply(tf_FFunctor &&_fFunctor, tf_CTuple &&_Tuple)
	{
		return std::apply(fg_Forward<tf_FFunctor>(_fFunctor), fg_Forward<tf_CTuple>(_Tuple));
	}

	namespace NPrivate
	{
		template <typename tf_FFunctor, typename tf_CTuple, typename ...tfp_CTypes, mint ...tfp_Indices>
		mark_artificial inline_always auto fg_TupleApplyAs(tf_FFunctor &&_fFunctor, tf_CTuple &&_Tuple, NMeta::TCTypeList<tfp_CTypes...> const &, NMeta::TCIndices<tfp_Indices...> const &)
		{
			return fg_Forward<tf_FFunctor>(_fFunctor)(fg_Forward<tfp_CTypes>(fg_Get<tfp_Indices>(_Tuple))...);
		}
	}

	template <typename tf_CTypeList, typename tf_FFunctor, typename tf_CTuple>
	mark_artificial inline_always auto fg_TupleApplyAs(tf_FFunctor &&_fFunctor, tf_CTuple &&_Tuple)
	{
		return NPrivate::fg_TupleApplyAs
			(
				fg_Forward<tf_FFunctor>(_fFunctor)
				, fg_Forward<tf_CTuple>(_Tuple)
				, tf_CTypeList()
				, typename NMeta::TCMakeConsecutiveIndices<TCTuple_Len<typename NTraits::TCRemoveReference<tf_CTuple>::CType>::mc_Value>::CType()
			)
		;
	}
}
			
#endif

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif
