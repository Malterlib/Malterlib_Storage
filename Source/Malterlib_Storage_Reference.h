// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStorage::NReference
{
	template <typename t_CType, typename t_CPtr>
	class TCReference;
}

#include "Private/Malterlib_Storage_Reference_Traits.h"

namespace NMib::NStorage
{
	template <typename t_CType>
	struct TCIsReference : public NTraits::TCCompileTimeConstant<bool, NReference::NPrivate::TCIsReferenceHelper<t_CType>::mc_Value>
	{
	};
}

#include "Private/Malterlib_Storage_Reference_Helpers.h"

namespace NMib::NStorage::NReference
{
	template <typename t_CType, typename t_CPtr = TCDynamicPtr<typename NMib::NMemory::CDefaultAllocator::CPtrHolder, t_CType>>
	class TCReference
	{
	protected:
		struct CData
		{
			t_CPtr m_pPointTo;
		};

		CData m_Data;

	public:

		t_CType &f_Get() const volatile;
	public:
		template <typename... tfp_CParams>
		typename TCEnableIf
		<
			NTraits::TCIsCallableWith<t_CType, void (tfp_CParams &&...)>::mc_Value
			, typename NTraits::TCIsCallableWith<t_CType, void (tfp_CParams &&...)>::CReturnType
		>::CType
		operator () (tfp_CParams &&...p_Params) const volatile;

		///
		/// Member access
		/// =============

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
		operator ->* (t_CMemberPtr const &_MemberPtr) const volatile;

		template <typename t_CMemberPtr>
		typename TCEnableIf
		<
			NTraits::TCIsMemberObjectPointer<t_CMemberPtr>::mc_Value
			, typename NTraits::TCAddLValueReference<typename NTraits::TCRemoveMemberObjectPointer<t_CMemberPtr>::CType>::CType
		>::CType
		operator ->* (t_CMemberPtr const &_MemberPtr) const volatile;

	private:
		TCReference();
		TCReference &operator = (TCReference const &_Other);
		TCReference &operator = (TCReference volatile &_Other);
		TCReference &operator = (TCReference &_Other);
		TCReference &operator = (TCReference const volatile &_Other);
		TCReference &operator = (TCReference &&_Other);
	public:
		typedef t_CType CType;

		explicit TCReference(t_CType &_Param0);
		TCReference(TCReference const &_Other);
		TCReference(TCReference volatile &_Other);
		TCReference(TCReference const volatile &_Other);
		TCReference(TCReference &_Other);
		TCReference(TCReference &&_Other);
		operator t_CType & () const volatile;
	};

	DMibTempImplementReferenceBinaryOperator(==);
	DMibTempImplementReferenceBinaryOperator(!=);
	DMibTempImplementReferenceBinaryOperator(<);
	DMibTempImplementReferenceBinaryOperator(<=);
	DMibTempImplementReferenceBinaryOperator(>);
	DMibTempImplementReferenceBinaryOperator(>=);
	DMibTempImplementReferenceBinaryOperator(<<);
	DMibTempImplementReferenceBinaryOperator(>>);
	DMibTempImplementReferenceBinaryOperator(%);
	DMibTempImplementReferenceBinaryOperator(&);
	DMibTempImplementReferenceBinaryOperator(*);
	DMibTempImplementReferenceBinaryOperator(+);
	DMibTempImplementReferenceBinaryOperator(-);
	DMibTempImplementReferenceBinaryOperator(/);
	DMibTempImplementReferenceBinaryOperator(^);
	DMibTempImplementReferenceBinaryOperator(|);
	DMibTempImplementReferenceBinaryOperator(%=);
	DMibTempImplementReferenceBinaryOperator(&=);
	DMibTempImplementReferenceBinaryOperator(*=);
	DMibTempImplementReferenceBinaryOperator(+=);
	DMibTempImplementReferenceBinaryOperator(-=);
	DMibTempImplementReferenceBinaryOperator(/=);
	DMibTempImplementReferenceBinaryOperator(<<=);
	DMibTempImplementReferenceBinaryOperator(>>=);
	DMibTempImplementReferenceBinaryOperator(^=);
	DMibTempImplementReferenceBinaryOperator(|=);

	// DMibTempImplementReferenceBinaryOperator(->*); Has special implementation

#		undef DMibTempImplementReferenceBinaryOperator

	DMibTempImplementReferenceUnaryOperator(!);
	// DMibTempImplementReferenceUnaryOperator(&); // Should not be overridden (unsafe)
	DMibTempImplementReferenceUnaryOperator(~);
	DMibTempImplementReferenceUnaryOperator(*);
	DMibTempImplementReferenceUnaryOperator(+);
	DMibTempImplementReferenceUnaryOperator(++);
	DMibTempImplementReferenceUnaryPostfixOperator(++);
	DMibTempImplementReferenceUnaryOperator(-);
	DMibTempImplementReferenceUnaryOperator(--);
	DMibTempImplementReferenceUnaryPostfixOperator(--);

#		undef DMibTempImplementReferenceUnaryOperator
#		undef DMibTempImplementReferenceUnaryPostfixOperator

}

namespace NMib::NStorage
{
	template <typename t_CType, typename t_CPtr = TCDynamicPtr<typename NMib::NMemory::CDefaultAllocator::CPtrHolder, t_CType>>
	using TCReference = NReference::TCReference<t_CType, t_CPtr>;
}

namespace NMib
{
	/***************************************************************************************************\
	|ﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯ|
	| Reference																							|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/


	template <typename t_CType>
	NStorage::TCReference<t_CType> fg_Reference(t_CType &_Type)
	{
		return NStorage::TCReference<t_CType>(_Type);
	}

	template <typename t_CType>
	NStorage::TCReference<typename NTraits::TCAddConst<t_CType>::CType> fg_ConstReference(t_CType const &_Type)
	{
		return NStorage::TCReference<typename NTraits::TCAddConst<t_CType>::CType>(_Type);
	}

	template <typename t_CType>
	NStorage::TCReference<typename NTraits::TCAddVolatile<t_CType>::CType> fg_VolatileReference(t_CType volatile &_Type)
	{
		return NStorage::TCReference<typename NTraits::TCAddVolatile<t_CType>::CType>(_Type);
	}


	template <typename t_CType>
	NStorage::TCReference
	<
		typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<t_CType>::CType>::CType
	> 
	fg_ConstVolatileReference(t_CType const volatile &_Type)
	{
		return NStorage::TCReference
			<
				typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<t_CType>::CType>::CType
			>
			(_Type);
	}

	/***************************************************************************************************\
	|ﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯ|
	| Recursive references optimized																	|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	template <typename t_CType>
	NStorage::TCReference<t_CType> fg_Reference(NStorage::TCReference<t_CType> &&_Type)
	{
		return NStorage::TCReference<t_CType>(_Type);
	}
	template <typename t_CType>
	NStorage::TCReference<t_CType> fg_Reference(NStorage::TCReference<t_CType> &_Type)
	{
		return NStorage::TCReference<t_CType>(_Type);
	}
	template <typename t_CType>
	NStorage::TCReference<t_CType> fg_Reference(NStorage::TCReference<t_CType> const &_Type)
	{
		return NStorage::TCReference<t_CType>(_Type);
	}
	template <typename t_CType>
	NStorage::TCReference<t_CType> fg_Reference(NStorage::TCReference<t_CType> volatile &_Type)
	{
		return NStorage::TCReference<t_CType>(_Type);
	}
	template <typename t_CType>
	NStorage::TCReference<t_CType> fg_Reference(NStorage::TCReference<t_CType> const volatile &_Type)
	{
		return NStorage::TCReference<t_CType>(_Type);
	}

	template <typename t_CType>
	NStorage::TCReference<typename NTraits::TCAddConst<t_CType>::CType> fg_ConstReference(NStorage::TCReference<t_CType> &&_Type)
	{
		return NStorage::TCReference<typename NTraits::TCAddConst<t_CType>::CType>(fg_Move(_Type));
	}
	template <typename t_CType>
	NStorage::TCReference<typename NTraits::TCAddConst<t_CType>::CType> fg_ConstReference(NStorage::TCReference<t_CType> &_Type)
	{
		return NStorage::TCReference<typename NTraits::TCAddConst<t_CType>::CType>(_Type);
	}
	template <typename t_CType>
	NStorage::TCReference<typename NTraits::TCAddConst<t_CType>::CType> fg_ConstReference(NStorage::TCReference<t_CType> const &_Type)
	{
		return NStorage::TCReference<typename NTraits::TCAddConst<t_CType>::CType>(_Type);
	}
	template <typename t_CType>
	NStorage::TCReference<typename NTraits::TCAddConst<t_CType>::CType> fg_ConstReference(NStorage::TCReference<t_CType> volatile &_Type)
	{
		return NStorage::TCReference<typename NTraits::TCAddConst<t_CType>::CType>(_Type);
	}
	template <typename t_CType>
	NStorage::TCReference<typename NTraits::TCAddConst<t_CType>::CType> fg_ConstReference(NStorage::TCReference<t_CType> const volatile &_Type)
	{
		return NStorage::TCReference<typename NTraits::TCAddConst<t_CType>::CType>(_Type);
	}

	template <typename t_CType>
	NStorage::TCReference<typename NTraits::TCAddVolatile<t_CType>::CType>
	fg_VolatileReference(NStorage::TCReference<t_CType> &&_Type)
	{
		return NStorage::TCReference<typename NTraits::TCAddVolatile<t_CType>::CType>(fg_Move(_Type));
	}
	template <typename t_CType>
	NStorage::TCReference<typename NTraits::TCAddVolatile<t_CType>::CType>
	fg_VolatileReference(NStorage::TCReference<t_CType> &_Type)
	{
		return NStorage::TCReference<typename NTraits::TCAddVolatile<t_CType>::CType>(_Type);
	}
	template <typename t_CType>
	NStorage::TCReference<typename NTraits::TCAddVolatile<t_CType>::CType>
	fg_VolatileReference(NStorage::TCReference<t_CType> const &_Type)
	{
		return NStorage::TCReference<typename NTraits::TCAddVolatile<t_CType>::CType>(_Type);
	}
	template <typename t_CType>
	NStorage::TCReference<typename NTraits::TCAddVolatile<t_CType>::CType>
	fg_VolatileReference(NStorage::TCReference<t_CType> volatile &_Type)
	{
		return NStorage::TCReference<typename NTraits::TCAddVolatile<t_CType>::CType>(_Type);
	}
	template <typename t_CType>
	NStorage::TCReference<typename NTraits::TCAddVolatile<t_CType>::CType>
	fg_VolatileReference(NStorage::TCReference<t_CType> const volatile &_Type)
	{
		return NStorage::TCReference<typename NTraits::TCAddVolatile<t_CType>::CType>(_Type);
	}

	template <typename t_CType>
	NStorage::TCReference
	<
		typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<t_CType>::CType>::CType
	> 
	fg_ConstVolatileReference(NStorage::TCReference<t_CType> &&_Type)
	{
		return NStorage::TCReference
			<
				typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<t_CType>::CType>::CType
			>
			(fg_Move(_Type));
	}
	template <typename t_CType>
	NStorage::TCReference
	<
		typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<t_CType>::CType>::CType
	> 
	fg_ConstVolatileReference(NStorage::TCReference<t_CType> &_Type)
	{
		return NStorage::TCReference
			<
				typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<t_CType>::CType>::CType
			>
			(_Type);
	}
	template <typename t_CType>
	NStorage::TCReference
	<
		typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<t_CType>::CType>::CType
	> 
	fg_ConstVolatileReference(NStorage::TCReference<t_CType> const &_Type)
	{
		return NStorage::TCReference
			<
				typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<t_CType>::CType>::CType
			>
			(_Type);
	}
	template <typename t_CType>
	NStorage::TCReference
	<
		typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<t_CType>::CType>::CType
	> 
	fg_ConstVolatileReference(NStorage::TCReference<t_CType> volatile &_Type)
	{
		return NStorage::TCReference
			<
				typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<t_CType>::CType>::CType
			>
			(_Type);
	}
	template <typename t_CType>
	NStorage::TCReference
	<
		typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<t_CType>::CType>::CType
	> 
	fg_ConstVolatileReference(NStorage::TCReference<t_CType> const volatile &_Type)
	{
		return NStorage::TCReference
			<
				typename NTraits::TCAddConst<typename NTraits::TCAddVolatile<t_CType>::CType>::CType
			>
			(_Type);
	}
}

#include "Malterlib_Storage_Reference.hpp"

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif
