// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
namespace NMib::NStorage::NIndirection
{
#	define DMibTempImplementIndirectionBinaryOperator(_Operator) \
		template <typename t_CLeft, typename t_CRight>\
		auto operator _Operator (t_CLeft &&_Left, t_CRight &&_Right) \
			-> typename TCEnableIf\
			<\
				TCIsIndirection\
				<\
					typename NTraits::TCRemoveQualifiers\
					<\
						typename NTraits::TCRemoveReference<t_CLeft>::CType\
					>::CType\
				>::mc_Value\
				&& !TCIsIndirection\
				<\
					typename NTraits::TCRemoveQualifiers\
					<\
						typename NTraits::TCRemoveReference<t_CRight>::CType\
					>::CType\
				>::mc_Value\
				, decltype(fg_Forward<t_CLeft>(_Left).f_Get() _Operator fg_Forward<t_CRight>(_Right))\
			>::CType\
		{\
			return fg_Forward<t_CLeft>(_Left).f_Get() _Operator fg_Forward<t_CRight>(_Right);\
		}\
		template <typename t_CLeft, typename t_CRight>\
		auto operator _Operator (t_CLeft &&_Left, t_CRight &&_Right) \
			-> typename TCEnableIf\
			<\
				! TCIsIndirection\
				<\
					typename NTraits::TCRemoveQualifiers\
					<\
						typename NTraits::TCRemoveReference<t_CLeft>::CType\
					>::CType\
				>::mc_Value\
				&& TCIsIndirection\
				<\
					typename NTraits::TCRemoveQualifiers\
					<\
						typename NTraits::TCRemoveReference<t_CRight>::CType\
					>::CType\
				>::mc_Value\
				, decltype(fg_Forward<t_CLeft>(_Left) _Operator fg_Forward<t_CRight>(_Right).f_Get())\
			>::CType\
		{\
			return fg_Forward<t_CLeft>(_Left) _Operator fg_Forward<t_CRight>(_Right).f_Get();\
		}\
		template <typename t_CLeft, typename t_CRight>\
		auto operator _Operator (t_CLeft &&_Left, t_CRight &&_Right) \
			-> typename TCEnableIf\
			<\
				TCIsIndirection\
				<\
					typename NTraits::TCRemoveQualifiers\
					<\
						typename NTraits::TCRemoveReference<t_CLeft>::CType\
					>::CType\
				>::mc_Value\
				&& TCIsIndirection\
				<\
					typename NTraits::TCRemoveQualifiers\
					<\
						typename NTraits::TCRemoveReference<t_CRight>::CType\
					>::CType\
				>::mc_Value\
				, decltype(fg_Forward<t_CLeft>(_Left).f_Get() _Operator fg_Forward<t_CRight>(_Right).f_Get())\
			>::CType\
		{\
			return fg_Forward<t_CLeft>(_Left).f_Get() _Operator fg_Forward<t_CRight>(_Right).f_Get();\
		}

#	define DMibTempImplementIndirectionUnaryOperator(_Operator) \
		template <typename t_CRight>\
		auto operator _Operator (t_CRight &&_Right) \
			-> typename TCEnableIf\
			<\
				TCIsIndirection\
				<\
					typename NTraits::TCRemoveQualifiers\
					<\
						typename NTraits::TCRemoveReference<t_CRight>::CType\
					>::CType\
				>::mc_Value\
				, decltype(_Operator fg_Forward<t_CRight>(_Right).f_Get())\
			>::CType\
		{\
			return _Operator fg_Forward<t_CRight>(_Right).f_Get();\
		}

#	define DMibTempImplementIndirectionUnaryPostfixOperator(_Operator) \
		template <typename t_CRight>\
		auto operator _Operator (t_CRight &&_Right, int) \
			-> typename TCEnableIf\
			<\
				TCIsIndirection\
				<\
					typename NTraits::TCRemoveQualifiers\
					<\
						typename NTraits::TCRemoveReference<t_CRight>::CType\
					>::CType\
				>::mc_Value\
				, decltype(fg_Forward<t_CRight>(_Right).f_Get() _Operator)\
			>::CType\
		{\
			return fg_Forward<t_CRight>(_Right).f_Get() _Operator;\
		}
}
