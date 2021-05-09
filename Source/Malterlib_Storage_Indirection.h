// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStorage::NIndirection
{
	template <typename t_CType, typename t_CAllocator>
	class TCIndirection;
}

#include "Private/Malterlib_Storage_Indirection_Traits.h"

namespace NMib::NStorage
{
	template <typename t_CType>
	struct TCIsIndirection : public NTraits::TCCompileTimeConstant<bool, NPrivate::TCIsIndirectionHelper<t_CType>::mc_Value>
	{
	};
}

#include "Private/Malterlib_Storage_Indirection_Helpers.h"

namespace NMib::NStorage::NIndirection
{
	template <typename t_CType, typename t_CAllocator = NMib::NMemory::CDefaultAllocator>
	class TCIndirection
	{
	protected:
		struct CData : public t_CAllocator
		{
			t_CType *m_pPointTo;
		};

		CData m_Data;

		t_CAllocator &fp_GetAllocator();

		template <typename t_CDummy>
		void fp_Delete();
		void fp_Delete();

		template <typename t_CDummy>
		void fp_Create();
		void fp_Create();

	public:

		mark_artificial inline_always t_CType const &f_Get() const;
		mark_artificial inline_always t_CType &f_Get();

	public:

		template <typename... tfp_CParams>
		mark_artificial inline_always auto operator () (tfp_CParams &&... p_Params);

		template <typename... tfp_CParams>
		mark_artificial inline_always auto operator () (tfp_CParams &&...p_Params) const;

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Member access																						|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename t_CMemberPtr>
		typename TCEnableIf
			<
				NTraits::TCIsMemberFunctionPointer<t_CMemberPtr>::mc_Value
				, NFunction::TCMemberFunctionBoundFunctor
				<
					t_CMemberPtr
					, t_CType *
				>
			>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr);

		template <typename t_CMemberPtr>
		typename TCEnableIf
		<
			NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
			, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
		>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr);

		template <typename t_CMemberPtr>
		typename TCEnableIf
			<
				NTraits::TCIsMemberFunctionPointer<t_CMemberPtr>::mc_Value
				, NFunction::TCMemberFunctionBoundFunctor
				<
					t_CMemberPtr
					, typename NTraits::TCAddConst<t_CType>::CType *
				>
			>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr) const;

		template <typename t_CMemberPtr>
		typename TCEnableIf
		<
			NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
			, typename NTraits::TCAddLValueReference<typename NTraits::TCAddConst<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType>::CType
		>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr) const;

	public:
		typedef t_CType CType;

		TCIndirection();
		~TCIndirection();

		template <typename tf_CParam0, typename... tfp_CParams>
		TCIndirection(tf_CParam0 &&_Param0, tfp_CParams && ... p_Params);

		TCIndirection(TCIndirection const &_Other);
		TCIndirection(TCIndirection &_Other);
		TCIndirection(TCIndirection &&_Other);
		template <typename t_CParam0>
		TCIndirection &operator =(t_CParam0 &&_Param0);
		TCIndirection &operator =(TCIndirection const &_Other);
		TCIndirection &operator =(TCIndirection &_Other);
		TCIndirection &operator =(TCIndirection &&_Other);
		mark_artificial inline_always operator t_CType const & () const;
		mark_artificial inline_always operator t_CType & ();

		template <typename tf_CStr>
		void f_Format(tf_CStr &o_String) const;
	};

	DMibTempImplementIndirectionBinaryOperator(==);
	DMibTempImplementIndirectionBinaryOperator(!=);
	DMibTempImplementIndirectionBinaryOperator(<);
	DMibTempImplementIndirectionBinaryOperator(<=);
	DMibTempImplementIndirectionBinaryOperator(>);
	DMibTempImplementIndirectionBinaryOperator(>=);

	/*
	DMibTempImplementIndirectionBinaryOperator(<<);
	DMibTempImplementIndirectionBinaryOperator(>>);
	DMibTempImplementIndirectionBinaryOperator(%);
	DMibTempImplementIndirectionBinaryOperator(&);
	DMibTempImplementIndirectionBinaryOperator(*);
	DMibTempImplementIndirectionBinaryOperator(+);
	DMibTempImplementIndirectionBinaryOperator(-);
	DMibTempImplementIndirectionBinaryOperator(/);
	DMibTempImplementIndirectionBinaryOperator(^);
	DMibTempImplementIndirectionBinaryOperator(|);
	DMibTempImplementIndirectionBinaryOperator(%=);
	DMibTempImplementIndirectionBinaryOperator(&=);
	DMibTempImplementIndirectionBinaryOperator(*=);
	DMibTempImplementIndirectionBinaryOperator(+=);
	DMibTempImplementIndirectionBinaryOperator(-=);
	DMibTempImplementIndirectionBinaryOperator(/=);
	DMibTempImplementIndirectionBinaryOperator(<<=);
	DMibTempImplementIndirectionBinaryOperator(>>=);
	DMibTempImplementIndirectionBinaryOperator(^=);
	DMibTempImplementIndirectionBinaryOperator(|=);

	// DMibTempImplementIndirectionBinaryOperator(->*); Has special implementation

#		undef DMibTempImplementIndirectionBinaryOperator

	DMibTempImplementIndirectionUnaryOperator(!);
	// DMibTempImplementIndirectionUnaryOperator(&); // Should not be overridden (unsafe)
	DMibTempImplementIndirectionUnaryOperator(~);
	DMibTempImplementIndirectionUnaryOperator(*);
	DMibTempImplementIndirectionUnaryOperator(+);
	DMibTempImplementIndirectionUnaryOperator(++);
	DMibTempImplementIndirectionUnaryPostfixOperator(++);
	DMibTempImplementIndirectionUnaryOperator(-);
	DMibTempImplementIndirectionUnaryOperator(--);
	DMibTempImplementIndirectionUnaryPostfixOperator(--);

#		undef DMibTempImplementIndirectionUnaryOperator
#		undef DMibTempImplementIndirectionUnaryPostfixOperator

*/

}

namespace NMib::NStorage
{
	template <typename t_CType, typename t_CAllocator = NMib::NMemory::CDefaultAllocator>
	using TCIndirection = NIndirection::TCIndirection<t_CType, t_CAllocator>;
}

namespace NMib
{
	template <typename t_CType>
	NStorage::TCIndirection<typename NTraits::TCDecay<t_CType>::CType> fg_Indirect(t_CType &&_Type)
	{
		return NStorage::TCIndirection<typename NTraits::TCDecay<t_CType>::CType>(fg_Forward<t_CType>(_Type));
	}
}

#include "Malterlib_Storage_Indirection.hpp"

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif
