// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib
{
	template <umint tf_Index, typename tf_CType>
	mark_artificial mark_nodebug inline_always auto fg_Get(tf_CType &&_Tuple) noexcept
		-> NTraits::TCPromoteQualifiers<tf_CType, decltype(std::get<tf_Index>(fg_RemoveQualifiers(fg_Forward<tf_CType>(_Tuple))))>
	{
		return fg_Forward<NTraits::TCPromoteQualifiers<tf_CType, decltype(std::get<tf_Index>(fg_RemoveQualifiers(fg_Forward<tf_CType>(_Tuple))))>>
			(
				std::get<tf_Index>(fg_RemoveQualifiers(fg_Forward<tf_CType>(_Tuple)))
			)
		;
	}

	template <umint tf_Index, typename tf_CType>
	mark_artificial mark_nodebug inline_always auto fg_GetForward(tf_CType &&_Tuple) noexcept
		-> NTraits::TCPromoteQualifiersAndReference<tf_CType, decltype(std::get<tf_Index>(fg_Forward<tf_CType>(_Tuple)))>
	{
		return fg_Forward<NTraits::TCPromoteQualifiersAndReference<tf_CType, decltype(std::get<tf_Index>(fg_Forward<tf_CType>(_Tuple)))>>(std::get<tf_Index>(fg_Forward<tf_CType>(_Tuple)));
	}
}

namespace NMib::NStorage
{
	template <typename ...tfp_CTypes>
	constexpr inline_always TCTuple<tfp_CTypes & ...> fg_TupleReferences(tfp_CTypes & ...p_Params) noexcept
	{
		return TCTuple<tfp_CTypes & ...>(p_Params...);
	}

	template <typename ...tfp_CParams>
	constexpr auto fg_TupleReferences(tfp_CParams && ...p_Params) -> decltype(std::tie(fg_Forward<tfp_CParams>(p_Params)...))
	{
		return std::tie(fg_Forward<tfp_CParams>(p_Params)...);
	}

	static constexpr inline_always TCTuple<> fg_TupleReferences() noexcept
	{
		return TCTuple<>();
	}

	template <typename ...tfp_CParams>
	constexpr auto fg_Tuple(tfp_CParams && ...p_Params) -> decltype(std::make_tuple(fg_Forward<tfp_CParams>(p_Params)...))
	{
		return std::make_tuple(fg_Forward<tfp_CParams>(p_Params)...);
	}

	template <typename ...tfp_CParams>
	constexpr auto fg_TuplePerfectForward(tfp_CParams && ...p_Params) -> decltype(std::forward_as_tuple(fg_Forward<tfp_CParams>(p_Params)...))
	{
		return std::forward_as_tuple(fg_Forward<tfp_CParams>(p_Params)...);
	}

	template <typename ...tfp_CParams>
	constexpr auto fg_TupleConcatenate(tfp_CParams && ...p_Params) -> decltype(std::tuple_cat(fg_Forward<tfp_CParams>(p_Params)...))
	{
		return std::tuple_cat(fg_Forward<tfp_CParams>(p_Params)...);
	}

	template <typename tf_FFunctor, typename tf_CTuple>
	constexpr auto fg_TupleApply(tf_FFunctor &&_fFunctor, tf_CTuple &&_Tuple)
	{
		return std::apply(fg_Forward<tf_FFunctor>(_fFunctor), fg_Forward<tf_CTuple>(_Tuple));
	}

	namespace NPrivate
	{
		template <typename tf_FFunctor, typename tf_CTuple, typename ...tfp_CTypes, umint ...tfp_Indices>
		mark_artificial constexpr inline_always auto fg_TupleApplyAs
			(
				tf_FFunctor &&_fFunctor
				, tf_CTuple &&_Tuple
				, NMeta::TCTypeList<tfp_CTypes...> const &_TypeList
				, NMeta::TCIndices<tfp_Indices...> const &_Indices
			)
		{
			return fg_Forward<tf_FFunctor>(_fFunctor)(fg_Forward<tfp_CTypes>(fg_Get<tfp_Indices>(_Tuple))...);
		}
	}

	template <typename tf_CTypeList, typename tf_FFunctor, typename tf_CTuple>
	mark_artificial constexpr inline_always auto fg_TupleApplyAs(tf_FFunctor &&_fFunctor, tf_CTuple &&_Tuple)
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
