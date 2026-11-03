// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>
#include <Mib/Function/Function>

namespace NMib::NStorage::NReference
{
#define DMibTempImplementReferenceBinaryOperator(d_Operator) \
	template <typename tf_CLeft, typename tf_CRight>\
	auto operator d_Operator (tf_CLeft &&_Left, tf_CRight &&_Right) \
		-> TCEnableIf\
		<\
			cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<tf_CLeft>> && !cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<tf_CRight>>\
			, decltype(fg_Forward<tf_CLeft>(_Left).f_Get() d_Operator fg_Forward<tf_CRight>(_Right))\
		>\
	{\
		return fg_Forward<tf_CLeft>(_Left).f_Get() d_Operator fg_Forward<tf_CRight>(_Right);\
	}\
	template <typename tf_CLeft, typename tf_CRight>\
	auto operator d_Operator (tf_CLeft &&_Left, tf_CRight &&_Right) \
		-> TCEnableIf\
		<\
			! cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<tf_CLeft>> && cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<tf_CRight>>\
			, decltype(fg_Forward<tf_CLeft>(_Left) d_Operator fg_Forward<tf_CRight>(_Right).f_Get())\
		>\
	{\
		return fg_Forward<tf_CLeft>(_Left) d_Operator fg_Forward<tf_CRight>(_Right).f_Get();\
	}\
	template <typename tf_CLeft, typename tf_CRight>\
	auto operator d_Operator (tf_CLeft &&_Left, tf_CRight &&_Right) \
		-> TCEnableIf\
		<\
			cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<tf_CLeft>> && cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<tf_CRight>>\
			, decltype(fg_Forward<tf_CLeft>(_Left).f_Get() d_Operator fg_Forward<tf_CRight>(_Right).f_Get())\
		>\
	{\
		return fg_Forward<tf_CLeft>(_Left).f_Get() d_Operator fg_Forward<tf_CRight>(_Right).f_Get();\
	}

#define DMibTempImplementReferenceUnaryOperator(d_Operator) \
	template <typename tf_CRight>\
	auto operator d_Operator (tf_CRight &&_Right) \
		-> TCEnableIf\
		<\
			cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<tf_CRight>>\
			, decltype(d_Operator fg_Forward<tf_CRight>(_Right).f_Get())\
		>\
	{\
		return d_Operator fg_Forward<tf_CRight>(_Right).f_Get();\
	}

#define DMibTempImplementReferenceUnaryPostfixOperator(d_Operator) \
	template <typename tf_CRight>\
	auto operator d_Operator (tf_CRight &&_Right, int) \
		-> TCEnableIf\
		<\
			cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<tf_CRight>>\
			, decltype(fg_Forward<tf_CRight>(_Right).f_Get() d_Operator)\
		>\
	{\
		return fg_Forward<tf_CRight>(_Right).f_Get() d_Operator;\
	}
}
