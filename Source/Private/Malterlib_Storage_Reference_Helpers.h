// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>
#include <Mib/Function/Function>

namespace NMib::NStorage::NReference
{
#define DMibTempImplementReferenceBinaryOperator(d_Operator) \
	template <typename t_CLeft, typename t_CRight>\
	auto operator d_Operator (t_CLeft &&_Left, t_CRight &&_Right) \
		-> TCEnableIf\
		<\
			cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CLeft>> && !cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CRight>>\
			, decltype(fg_Forward<t_CLeft>(_Left).f_Get() d_Operator fg_Forward<t_CRight>(_Right))\
		>\
	{\
		return fg_Forward<t_CLeft>(_Left).f_Get() d_Operator fg_Forward<t_CRight>(_Right);\
	}\
	template <typename t_CLeft, typename t_CRight>\
	auto operator d_Operator (t_CLeft &&_Left, t_CRight &&_Right) \
		-> TCEnableIf\
		<\
			! cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CLeft>> && cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CRight>>\
			, decltype(fg_Forward<t_CLeft>(_Left) d_Operator fg_Forward<t_CRight>(_Right).f_Get())\
		>\
	{\
		return fg_Forward<t_CLeft>(_Left) d_Operator fg_Forward<t_CRight>(_Right).f_Get();\
	}\
	template <typename t_CLeft, typename t_CRight>\
	auto operator d_Operator (t_CLeft &&_Left, t_CRight &&_Right) \
		-> TCEnableIf\
		<\
			cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CLeft>> && cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CRight>>\
			, decltype(fg_Forward<t_CLeft>(_Left).f_Get() d_Operator fg_Forward<t_CRight>(_Right).f_Get())\
		>\
	{\
		return fg_Forward<t_CLeft>(_Left).f_Get() d_Operator fg_Forward<t_CRight>(_Right).f_Get();\
	}

#define DMibTempImplementReferenceUnaryOperator(d_Operator) \
	template <typename t_CRight>\
	auto operator d_Operator (t_CRight &&_Right) \
		-> TCEnableIf\
		<\
			cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CRight>>\
			, decltype(d_Operator fg_Forward<t_CRight>(_Right).f_Get())\
		>\
	{\
		return d_Operator fg_Forward<t_CRight>(_Right).f_Get();\
	}

#define DMibTempImplementReferenceUnaryPostfixOperator(d_Operator) \
	template <typename t_CRight>\
	auto operator d_Operator (t_CRight &&_Right, int) \
		-> TCEnableIf\
		<\
			cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CRight>>\
			, decltype(fg_Forward<t_CRight>(_Right).f_Get() d_Operator)\
		>\
	{\
		return fg_Forward<t_CRight>(_Right).f_Get() d_Operator;\
	}
}
