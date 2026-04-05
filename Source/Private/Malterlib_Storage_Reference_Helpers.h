// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>
#include <Mib/Function/Function>

namespace NMib::NStorage::NReference
{
#	define DMibTempImplementReferenceBinaryOperator(_Operator) \
		template <typename t_CLeft, typename t_CRight>\
		auto operator _Operator (t_CLeft &&_Left, t_CRight &&_Right) \
			-> TCEnableIf\
			<\
				cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CLeft>> && !cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CRight>>\
				, decltype(fg_Forward<t_CLeft>(_Left).f_Get() _Operator fg_Forward<t_CRight>(_Right))\
			>\
		{\
			return fg_Forward<t_CLeft>(_Left).f_Get() _Operator fg_Forward<t_CRight>(_Right);\
		}\
		template <typename t_CLeft, typename t_CRight>\
		auto operator _Operator (t_CLeft &&_Left, t_CRight &&_Right) \
			-> TCEnableIf\
			<\
				! cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CLeft>> && cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CRight>>\
				, decltype(fg_Forward<t_CLeft>(_Left) _Operator fg_Forward<t_CRight>(_Right).f_Get())\
			>\
		{\
			return fg_Forward<t_CLeft>(_Left) _Operator fg_Forward<t_CRight>(_Right).f_Get();\
		}\
		template <typename t_CLeft, typename t_CRight>\
		auto operator _Operator (t_CLeft &&_Left, t_CRight &&_Right) \
			-> TCEnableIf\
			<\
				cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CLeft>> && cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CRight>>\
				, decltype(fg_Forward<t_CLeft>(_Left).f_Get() _Operator fg_Forward<t_CRight>(_Right).f_Get())\
			>\
		{\
			return fg_Forward<t_CLeft>(_Left).f_Get() _Operator fg_Forward<t_CRight>(_Right).f_Get();\
		}

#	define DMibTempImplementReferenceUnaryOperator(_Operator) \
		template <typename t_CRight>\
		auto operator _Operator (t_CRight &&_Right) \
			-> TCEnableIf\
			<\
				cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CRight>>\
				, decltype(_Operator fg_Forward<t_CRight>(_Right).f_Get())\
			>\
		{\
			return _Operator fg_Forward<t_CRight>(_Right).f_Get();\
		}

#	define DMibTempImplementReferenceUnaryPostfixOperator(_Operator) \
		template <typename t_CRight>\
		auto operator _Operator (t_CRight &&_Right, int) \
			-> TCEnableIf\
			<\
				cIsStorageReference<NTraits::TCRemoveReferenceAndQualifiers<t_CRight>>\
				, decltype(fg_Forward<t_CRight>(_Right).f_Get() _Operator)\
			>\
		{\
			return fg_Forward<t_CRight>(_Right).f_Get() _Operator;\
		}

}
