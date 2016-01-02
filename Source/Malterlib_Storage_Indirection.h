// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib
{
	namespace NIndirection
	{
		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		class TCIndirection;
	}
}

#include "Private/Malterlib_Storage_Indirection_Traits.h"

namespace NMib
{
	namespace NIndirection
	{
		template <typename t_CType>
		struct TCIsIndirection : public NTraits::TCCompileTimeConstant<bool, NPrivate::TCIsIndirectionHelper<t_CType>::mc_Value>
		{
		};

	}
}

#include "Private/Malterlib_Storage_Indirection_Helpers.h"


namespace NMib
{
	namespace NIndirection
	{

		template <typename t_CType, typename t_CAllocator = NMib::NMem::CDefaultAllocator, typename t_CPtr = TCDynamicPtr<typename t_CAllocator::CPtrHolder, t_CType>>
		class TCIndirection
		{
		protected:
			struct CData : public t_CAllocator
			{
				t_CPtr m_pPointTo;
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

			t_CType const &f_Get() const;
			t_CType volatile &f_Get() volatile;
			t_CType const volatile &f_Get() const volatile;
			t_CType &f_Get();

		public:

			template <typename... tfp_CParams>
			typename TCEnableIf
			<
				NTraits::TCIsCallableWith<t_CType, void (tfp_CParams &&...)>::mc_Value
				, typename NTraits::TCIsCallableWith<t_CType, void (tfp_CParams &&...)>::CReturnType
			>::CType
			operator () (tfp_CParams &&... p_Params);
			
			template <typename... tfp_CParams>
			typename TCEnableIf
			<
				NTraits::TCIsCallableWith<t_CType const, void (tfp_CParams &&...)>::mc_Value
				, typename NTraits::TCIsCallableWith<t_CType const, void (tfp_CParams &&...)>::CReturnType
			>::CType
			operator () (tfp_CParams &&...p_Params) const;
			
			template <typename... tfp_CParams>
			typename TCEnableIf
			<
				NTraits::TCIsCallableWith<t_CType volatile, void (tfp_CParams &&...)>::mc_Value
				, typename NTraits::TCIsCallableWith<t_CType volatile, void (tfp_CParams &&...)>::CReturnType
			>::CType
			operator () (tfp_CParams &&...p_Params) volatile;
			
			template <typename... tfp_CParams>
			typename TCEnableIf
			<
				NTraits::TCIsCallableWith<t_CType const volatile, void (tfp_CParams &&...)>::mc_Value
				, typename NTraits::TCIsCallableWith<t_CType const volatile, void (tfp_CParams &&...)>::CReturnType
			>::CType
			operator () (tfp_CParams &&...p_Params) const volatile;

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


			template <typename t_CMemberPtr>
			typename TCEnableIf
				<
					NTraits::TCIsMemberFunctionPointer<t_CMemberPtr>::mc_Value
					, NFunction::TCMemberFunctionBoundFunctor
					<
						t_CMemberPtr
						, typename NTraits::TCAddVolatile<t_CType>::CType *
					>
				>::CType
			operator ->* (t_CMemberPtr const &_MemberPtr) volatile;

			template <typename t_CMemberPtr>
			typename TCEnableIf
			<
				NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
				, typename NTraits::TCAddLValueReference<typename NTraits::TCAddVolatile<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType>::CType
			>::CType
			operator ->* (t_CMemberPtr const &_MemberPtr) volatile;


			template <typename t_CMemberPtr>
			typename TCEnableIf
				<
					NTraits::TCIsMemberFunctionPointer<t_CMemberPtr>::mc_Value
					, NFunction::TCMemberFunctionBoundFunctor
					<
						t_CMemberPtr
						, typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<t_CType>::CType>::CType *
					>
				>::CType
			operator ->* (t_CMemberPtr const &_MemberPtr) const volatile;

			template <typename t_CMemberPtr>
			typename TCEnableIf
			<
				NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
				, typename NTraits::TCAddLValueReference<typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType>::CType>::CType
			>::CType
			operator ->* (t_CMemberPtr const &_MemberPtr) const volatile;
		public:
			typedef t_CType CType;

			TCIndirection();
			~TCIndirection();

			template <typename tf_CParam0, typename... tfp_CParams>
			TCIndirection(tf_CParam0 &&_Param0, tfp_CParams && ... p_Params);

			TCIndirection(TCIndirection const &_Other);
			TCIndirection(TCIndirection volatile &_Other);
			TCIndirection(TCIndirection const volatile &_Other);
			TCIndirection(TCIndirection &_Other);
			TCIndirection(TCIndirection &&_Other);
			template <typename t_CParam0>
			TCIndirection &operator =(t_CParam0 &&_Param0);
			TCIndirection &operator =(TCIndirection const &_Other);
			TCIndirection &operator =(TCIndirection volatile &_Other);
			TCIndirection &operator =(TCIndirection const volatile &_Other);
			TCIndirection &operator =(TCIndirection &_Other);
			TCIndirection &operator =(TCIndirection &&_Other);
			operator t_CType const & () const;
			operator t_CType volatile & () volatile;
			operator t_CType const volatile & () const volatile;
			operator t_CType & ();
		};

		DMibTempImplementIndirectionBinaryOperator(==);
		DMibTempImplementIndirectionBinaryOperator(!=);
		DMibTempImplementIndirectionBinaryOperator(<);
		DMibTempImplementIndirectionBinaryOperator(<=);
		DMibTempImplementIndirectionBinaryOperator(>);
		DMibTempImplementIndirectionBinaryOperator(>=);
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

	}
	template <typename t_CType>
	NIndirection::TCIndirection<typename NTraits::TCDecay<t_CType>::CType> fg_Indirect(t_CType &&_Type)
	{
		return NIndirection::TCIndirection<typename NTraits::TCDecay<t_CType>::CType>(fg_Forward<t_CType>(_Type));
	}
}

#include "Malterlib_Storage_Indirection.hpp"
