// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStorage::NReference
{
	template <typename t_CType>
	struct TCReference;
}

#include "Private/Malterlib_Storage_Reference_Traits.h"

namespace NMib::NStorage
{
	template <typename t_CType>
	concept cIsStorageReference = NReference::NPrivate::TCIsReferenceHelper<t_CType>::mc_Value;
}

#include "Private/Malterlib_Storage_Reference_Helpers.h"

namespace NMib::NStorage::NReference
{
	template <typename t_CType>
	struct TCReference
	{
	protected:
		struct CData
		{
			t_CType *m_pPointTo;
		};

		CData mp_Data;

	public:
		mark_artificial mark_nodebug inline_always t_CType &f_Get() const volatile;

	public:
		template <typename ...tfp_CParams>
		mark_artificial inline_always NTraits::TCCallableReturnTypeFor<t_CType, void (tfp_CParams && ...p_Params)> operator () (tfp_CParams && ...p_Params) const volatile
			requires (NTraits::cIsCallableWith<t_CType, void (tfp_CParams && ...p_Params)>)
		;

		///
		/// Member access
		/// =============

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always NFunction::TCMemberFunctionBoundFunctor<tf_CMemberPtr, t_CType *> operator ->* (tf_CMemberPtr const &_MemberPtr) const volatile
			requires (NTraits::cIsMemberFunctionPointer<tf_CMemberPtr>)
		;

		template <typename tf_CMemberPtr>
		mark_artificial mark_nodebug inline_always auto operator ->* (tf_CMemberPtr const &_MemberPtr) const volatile
			-> NTraits::TCAddLValueReference<NTraits::TCRemoveMemberObjectPointer<tf_CMemberPtr>>
			requires (NTraits::cIsMemberObjectPointer<tf_CMemberPtr>)
		;

	private:
		TCReference();
		TCReference &operator = (TCReference const &_Other);
		TCReference &operator = (TCReference volatile &_Other);
		TCReference &operator = (TCReference &_Other);
		TCReference &operator = (TCReference const volatile &_Other);
		TCReference &operator = (TCReference &&_Other);

	public:
		using CType = t_CType;

		explicit TCReference(t_CType &_Param0);
		TCReference(TCReference const &_Other);
		TCReference(TCReference volatile &_Other);
		TCReference(TCReference const volatile &_Other);
		TCReference(TCReference &_Other);
		TCReference(TCReference &&_Other);
		mark_artificial mark_nodebug inline_always operator t_CType & () const volatile;
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
	DMibTempImplementReferenceBinaryOperator(<=>);

	// DMibTempImplementReferenceBinaryOperator(->*); Has special implementation

#undef DMibTempImplementReferenceBinaryOperator

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

#undef DMibTempImplementReferenceUnaryOperator
#undef DMibTempImplementReferenceUnaryPostfixOperator
}

namespace NMib::NStorage
{
	template <typename t_CType>
	using TCReference = NReference::TCReference<t_CType>;
}

namespace NMib
{
	/***************************************************************************************************\
	|ﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯ|
	| Reference																							|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	template <typename tf_CType>
	NStorage::TCReference<tf_CType> fg_Reference(tf_CType &_Type)
	{
		return NStorage::TCReference<tf_CType>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConst<tf_CType>> fg_ConstReference(tf_CType const &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConst<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>> fg_VolatileReference(tf_CType volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>> fg_ConstVolatileReference(tf_CType const volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>>(_Type);
	}

	/***************************************************************************************************\
	|ﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯﾯ|
	| Recursive references optimized																	|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	template <typename tf_CType>
	NStorage::TCReference<tf_CType> fg_Reference(NStorage::TCReference<tf_CType> &&_Type)
	{
		return NStorage::TCReference<tf_CType>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<tf_CType> fg_Reference(NStorage::TCReference<tf_CType> &_Type)
	{
		return NStorage::TCReference<tf_CType>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<tf_CType> fg_Reference(NStorage::TCReference<tf_CType> const &_Type)
	{
		return NStorage::TCReference<tf_CType>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<tf_CType> fg_Reference(NStorage::TCReference<tf_CType> volatile &_Type)
	{
		return NStorage::TCReference<tf_CType>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<tf_CType> fg_Reference(NStorage::TCReference<tf_CType> const volatile &_Type)
	{
		return NStorage::TCReference<tf_CType>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConst<tf_CType>> fg_ConstReference(NStorage::TCReference<tf_CType> &&_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConst<tf_CType>>(fg_Move(_Type));
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConst<tf_CType>> fg_ConstReference(NStorage::TCReference<tf_CType> &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConst<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConst<tf_CType>> fg_ConstReference(NStorage::TCReference<tf_CType> const &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConst<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConst<tf_CType>> fg_ConstReference(NStorage::TCReference<tf_CType> volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConst<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConst<tf_CType>> fg_ConstReference(NStorage::TCReference<tf_CType> const volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConst<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>> fg_VolatileReference(NStorage::TCReference<tf_CType> &&_Type)
	{
		return NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>>(fg_Move(_Type));
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>> fg_VolatileReference(NStorage::TCReference<tf_CType> &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>> fg_VolatileReference(NStorage::TCReference<tf_CType> const &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>> fg_VolatileReference(NStorage::TCReference<tf_CType> volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>> fg_VolatileReference(NStorage::TCReference<tf_CType> const volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>> fg_ConstVolatileReference(NStorage::TCReference<tf_CType> &&_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>>(fg_Move(_Type));
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>> fg_ConstVolatileReference(NStorage::TCReference<tf_CType> &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>> fg_ConstVolatileReference(NStorage::TCReference<tf_CType> const &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>> fg_ConstVolatileReference(NStorage::TCReference<tf_CType> volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>>(_Type);
	}

	template <typename tf_CType>
	NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>> fg_ConstVolatileReference(NStorage::TCReference<tf_CType> const volatile &_Type)
	{
		return NStorage::TCReference<NTraits::TCAddConstVolatile<tf_CType>>(_Type);
	}
}

#include "Malterlib_Storage_Reference.hpp"

#ifndef DMibPNoShortCuts
using namespace NMib::NStorage;
#endif
