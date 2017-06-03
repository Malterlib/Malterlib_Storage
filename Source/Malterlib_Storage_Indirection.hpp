// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib
{
	namespace NIndirection
	{

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		t_CAllocator &TCIndirection<t_CType, t_CAllocator, t_CPtr>::fp_GetAllocator()
		{
			return m_Data;
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		template <typename t_CDummy>
		void TCIndirection<t_CType, t_CAllocator, t_CPtr>::fp_Delete()
		{
			if (m_Data.m_pPointTo)
			{
				fg_DeleteObject(fp_GetAllocator(), (t_CType *)m_Data.m_pPointTo);
				m_Data.m_pPointTo = nullptr;
			}
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		void TCIndirection<t_CType, t_CAllocator, t_CPtr>::fp_Delete()
		{
			fp_Delete<t_CType>();
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		template <typename t_CDummy>
		void TCIndirection<t_CType, t_CAllocator, t_CPtr>::fp_Create()
		{
			m_Data.m_pPointTo = fg_ConstructObject<t_CType>(fp_GetAllocator());
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		void TCIndirection<t_CType, t_CAllocator, t_CPtr>::fp_Create()
		{
			fp_Create<t_CType>();
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		t_CType const &TCIndirection<t_CType, t_CAllocator, t_CPtr>::f_Get() const
		{
			return *m_Data.m_pPointTo;
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		t_CType volatile &TCIndirection<t_CType, t_CAllocator, t_CPtr>::f_Get() volatile
		{
			return *m_Data.m_pPointTo;
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		t_CType const volatile &TCIndirection<t_CType, t_CAllocator, t_CPtr>::f_Get() const volatile
		{
			return *m_Data.m_pPointTo;
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		t_CType &TCIndirection<t_CType, t_CAllocator, t_CPtr>::f_Get()
		{
			return *m_Data.m_pPointTo;
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		template <typename... tfp_CParams>
		typename TCEnableIf
		<
			NTraits::TCIsCallableWith<t_CType, void (tfp_CParams &&...)>::mc_Value
			, typename NTraits::TCIsCallableWith<t_CType, void (tfp_CParams &&...)>::CReturnType
		>::CType
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator () (tfp_CParams &&... p_Params)
		{
			return this->f_Get()(fg_Forward<tfp_CParams>(p_Params)...);
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		template <typename... tfp_CParams>
		typename TCEnableIf
		<
			NTraits::TCIsCallableWith<t_CType const, void (tfp_CParams &&...)>::mc_Value
			, typename NTraits::TCIsCallableWith<t_CType const, void (tfp_CParams &&...)>::CReturnType
		>::CType
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator () (tfp_CParams &&...p_Params) const
		{
			return this->f_Get()(fg_Forward<tfp_CParams>(p_Params)...);
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		template <typename... tfp_CParams>
		typename TCEnableIf
		<
			NTraits::TCIsCallableWith<t_CType volatile, void (tfp_CParams &&...)>::mc_Value
			, typename NTraits::TCIsCallableWith<t_CType volatile, void (tfp_CParams &&...)>::CReturnType
		>::CType
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator () (tfp_CParams &&...p_Params) volatile
		{
			return this->f_Get()(fg_Forward<tfp_CParams>(p_Params)...);
		}
		
		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		template <typename... tfp_CParams>
		typename TCEnableIf
		<
			NTraits::TCIsCallableWith<t_CType const volatile, void (tfp_CParams &&...)>::mc_Value
			, typename NTraits::TCIsCallableWith<t_CType const volatile, void (tfp_CParams &&...)>::CReturnType
		>::CType
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator () (tfp_CParams &&...p_Params) const volatile
		{
			return this->f_Get()(fg_Forward<tfp_CParams>(p_Params)...);
		}

#ifndef DDocumentation_Doxygen
		
		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
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
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator ->* (t_CMemberPtr const &_MemberPtr)
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, &(this->f_Get()));
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		template <typename t_CMemberPtr>
		typename TCEnableIf
		<
			NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
			, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
		>::CType
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator ->* (t_CMemberPtr const &_MemberPtr)
		{
			return (this->f_Get()).*_MemberPtr;
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
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
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, &(this->f_Get()));
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		template <typename t_CMemberPtr>
		typename TCEnableIf
		<
			NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
			, typename NTraits::TCAddLValueReference<typename NTraits::TCAddConst<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType>::CType
		>::CType
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator ->* (t_CMemberPtr const &_MemberPtr) const
		{
			return (this->f_Get()).*_MemberPtr;
		}


		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
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
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator ->* (t_CMemberPtr const &_MemberPtr) volatile
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, &(this->f_Get()));
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		template <typename t_CMemberPtr>
		typename TCEnableIf
		<
			NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
			, typename NTraits::TCAddLValueReference<typename NTraits::TCAddVolatile<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType>::CType
		>::CType
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator ->* (t_CMemberPtr const &_MemberPtr) volatile
		{
			return (this->f_Get()).*_MemberPtr;
		}


		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
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
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator ->* (t_CMemberPtr const &_MemberPtr) const volatile
		{
			return NFunction::fg_MemberFunctionFunctor(_MemberPtr, &(this->f_Get()));
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		template <typename t_CMemberPtr>
		typename TCEnableIf
		<
			NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
			, typename NTraits::TCAddLValueReference<typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType>::CType>::CType
		>::CType
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator ->* (t_CMemberPtr const &_MemberPtr) const volatile
		{
			return (this->f_Get()).*_MemberPtr;
		}
#endif

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::TCIndirection()
		{
			this->fp_Create();
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::~TCIndirection()
		{
			this->fp_Delete();
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		template <typename tf_CParam0, typename... tfp_CParams>
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::TCIndirection(tf_CParam0 &&_Param0, tfp_CParams && ... p_Params)
		{
			this->m_Data.m_pPointTo = fg_ConstructObject<t_CType>(this->fp_GetAllocator(), fg_Forward<tf_CParam0>(_Param0), fg_Forward<tfp_CParams>(p_Params)...);
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::TCIndirection(TCIndirection const &_Other)
		{
			this->m_Data.m_pPointTo = fg_ConstructObject<t_CType>(this->fp_GetAllocator(), _Other.f_Get());
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::TCIndirection(TCIndirection volatile &_Other)
		{
			this->m_Data.m_pPointTo = fg_ConstructObject<t_CType>(this->fp_GetAllocator(), _Other.f_Get());
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::TCIndirection(TCIndirection const volatile &_Other)
		{
			this->m_Data.m_pPointTo = fg_ConstructObject<t_CType>(this->fp_GetAllocator(), _Other.f_Get());
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::TCIndirection(TCIndirection &_Other)
		{
			this->m_Data.m_pPointTo = fg_ConstructObject<t_CType>(this->fp_GetAllocator(), _Other.f_Get());
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::TCIndirection(TCIndirection &&_Other)
		{
			this->m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
			_Other.m_Data.m_pPointTo = nullptr;
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		template <typename t_CParam0>
		TCIndirection<t_CType, t_CAllocator, t_CPtr> &TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator =(t_CParam0 &&_Param0)
		{
			this->f_Get() = fg_Forward<t_CParam0>(_Param0);
			return *this;
		}
		
		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr> &TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator =(TCIndirection const &_Other)
		{
			this->f_Get() = _Other.f_Get();
			return *this;
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr> &TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator =(TCIndirection volatile &_Other)
		{
			this->f_Get() = _Other.f_Get();
			return *this;
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr> &TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator =(TCIndirection const volatile &_Other)
		{
			this->f_Get() = _Other.f_Get();
			return *this;
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr> &TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator =(TCIndirection &_Other)
		{
			this->f_Get() = _Other.f_Get();
			return *this;
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr> &TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator =(TCIndirection &&_Other)
		{
			this->fp_Delete();
			this->m_Data.m_pPointTo = _Other.m_Data.m_pPointTo;
			_Other.m_Data.m_pPointTo = nullptr;
			return *this;
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator t_CType const & () const
		{
			return this->f_Get();
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator t_CType volatile & () volatile
		{
			return this->f_Get();
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator t_CType const volatile & () const volatile
		{
			return this->f_Get();
		}

		template <typename t_CType, typename t_CAllocator, typename t_CPtr>
		TCIndirection<t_CType, t_CAllocator, t_CPtr>::operator t_CType & ()
		{
			return this->f_Get();
		}
	}
}

