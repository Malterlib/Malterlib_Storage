// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <tuple>
#include <Mib/Meta/Meta>

namespace NMib::NStorage
{
	template <typename... tp_CTypes>
	using TCTuple = std::tuple<tp_CTypes...>;

	namespace NPrivate
	{
		template <typename t_CTuple>
		struct TCTuple_Len;

		// Support any qualifiers
		template <typename t_CType>
		struct TCTuple_Len<t_CType const>
			: public TCTuple_Len<t_CType>
		{
		};

		template <typename t_CType>
		struct TCTuple_Len<t_CType volatile>
			: public TCTuple_Len<t_CType>
		{
		};

		template <typename t_CType>
		struct TCTuple_Len<t_CType const volatile>
			: public TCTuple_Len<t_CType>
		{
		};

		template <typename... tp_CTypes>
		struct TCTuple_Len<TCTuple<tp_CTypes...>>
			: public NMeta::NPrivate::TCTypeList_Len<NMeta::TCTypeList<tp_CTypes...>>
		{
		};
	}

	template <typename t_CType>
	inline constexpr mint gc_Tuple_Len = NPrivate::TCTuple_Len<t_CType>::mc_Value;

	namespace NPrivate
	{
		template <mint t_Index, typename t_CType>
		struct TCTuple_Get;

		template <mint t_Index, typename... tp_CTypes>
		struct TCTuple_Get<t_Index, TCTuple<tp_CTypes...>>
		{
			using CType = NMeta::TCTypeList_Get<t_Index, NMeta::TCTypeList<tp_CTypes...>>;
		};

		template <mint t_Index, typename... tp_CTypes>
		struct TCTuple_Get<t_Index, const TCTuple<tp_CTypes...>>
		{
			using CType = NMeta::TCTypeList_Get<t_Index, const NMeta::TCTypeList<tp_CTypes...>>;
		};

		template <mint t_Index, typename... tp_CTypes>
		struct TCTuple_Get<t_Index, volatile TCTuple<tp_CTypes...>>
		{
			using CType = NMeta::TCTypeList_Get<t_Index, volatile NMeta::TCTypeList<tp_CTypes...>>;
		};

		template <mint t_Index, typename... tp_CTypes>
		struct TCTuple_Get<t_Index, const volatile TCTuple<tp_CTypes...>>
		{
			using CType = NMeta::TCTypeList_Get<t_Index, const volatile NMeta::TCTypeList<tp_CTypes...>>;
		};

		template <mint t_Index, typename... tp_CTypes>
		struct TCTuple_Get<t_Index, NMeta::TCTypeList<tp_CTypes...>>
		{
			using CType = NMeta::TCTypeList_Get<t_Index, NMeta::TCTypeList<tp_CTypes...>>;
		};

		template <mint t_Index, typename... tp_CTypes>
		struct TCTuple_Get<t_Index, const NMeta::TCTypeList<tp_CTypes...>>
		{
			using CType = NMeta::TCTypeList_Get<t_Index, const NMeta::TCTypeList<tp_CTypes...>>;
		};

		template <mint t_Index, typename... tp_CTypes>
		struct TCTuple_Get<t_Index, volatile NMeta::TCTypeList<tp_CTypes...>>
		{
			using CType = NMeta::TCTypeList_Get<t_Index, volatile NMeta::TCTypeList<tp_CTypes...>>;
		};

		template <mint t_Index, typename... tp_CTypes>
		struct TCTuple_Get<t_Index, const volatile NMeta::TCTypeList<tp_CTypes...>>
		{
			using CType = NMeta::TCTypeList_Get<t_Index, const volatile NMeta::TCTypeList<tp_CTypes...>>;
		};
	}

	template <mint t_Index, typename t_CType>
	using TCTuple_Get = NPrivate::TCTuple_Get<t_Index, t_CType>::CType;
}

namespace NMib
{
	template <mint tf_Index, typename tf_CType>
	mark_artificial mark_nodebug inline_always auto fg_Get(tf_CType &&_Tuple) noexcept -> NTraits::TCPromoteQualifiers<tf_CType, decltype(std::get<tf_Index>(fg_RemoveQualifiers(fg_Forward<tf_CType>(_Tuple))))>
	{
		return fg_Forward<NTraits::TCPromoteQualifiers<tf_CType, decltype(std::get<tf_Index>(fg_RemoveQualifiers(fg_Forward<tf_CType>(_Tuple))))>>(std::get<tf_Index>(fg_RemoveQualifiers(fg_Forward<tf_CType>(_Tuple))));
	}

	template <mint tf_Index, typename tf_CType>
	mark_artificial mark_nodebug inline_always auto fg_GetForward(tf_CType &&_Tuple) noexcept -> NTraits::TCPromoteQualifiersAndReference<tf_CType, decltype(std::get<tf_Index>(fg_Forward<tf_CType>(_Tuple)))>
	{
		return fg_Forward<NTraits::TCPromoteQualifiersAndReference<tf_CType, decltype(std::get<tf_Index>(fg_Forward<tf_CType>(_Tuple)))>>(std::get<tf_Index>(fg_Forward<tf_CType>(_Tuple)));
	}
}

namespace NMib::NStorage
{
	template <typename... tp_CTypes>
	inline_always TCTuple<tp_CTypes &...> fg_TupleReferences(tp_CTypes &...p_Params) noexcept
	{
		return TCTuple<tp_CTypes &...>(p_Params...);
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
				, NMeta::TCConsecutiveIndices<gc_Tuple_Len<NTraits::TCRemoveReference<tf_CTuple>>>()
			)
		;
	}
}

#if DMalterlibUseLibCxx && _LIBCPP_VERSION < 14000
namespace std
{
	template <typename... tfp_CParamsLeft, typename... tfp_CParamsRight>
	NMib::COrdering_Weak operator <=> (tuple<tfp_CParamsLeft...> const &_Left, tuple<tfp_CParamsRight...> const &_Right)
	{
		if (_Left < _Right)
			return NMib::COrdering_Weak::less;
		else if (_Left > _Right)
			return NMib::COrdering_Weak::greater;

		return NMib::COrdering_Weak::equivalent;
	}
}
#endif

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif
