// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStorage
{
	template <typename t_CType>
	TCOptional<t_CType>::TCOptional(t_CType const &_Value)
		: CVariant(_Value)
	{
	}

	template <typename t_CType>
	TCOptional<t_CType>::TCOptional(t_CType &&_Value)
		: CVariant(fg_Move(_Value))
	{
	}

	template <typename t_CType>
	auto TCOptional<t_CType>::operator = (t_CType const &_Value) -> TCOptional &
	{
		*((CVariant *)this) = _Value;
		return *this;
	}

	template <typename t_CType>
	auto TCOptional<t_CType>::operator = (t_CType &&_Value) -> TCOptional &
	{
		*((CVariant *)this) = fg_Move(_Value);
		return *this;
	}
	
	template <typename t_CType>
	void TCOptional<t_CType>::f_Clear()
	{
		this->template f_Set<0>();
	}
	
	template <typename t_CType>
	TCOptional<t_CType>::operator bool() const
	{
		return this->f_GetTypeID() == 1;
	}
	
	template <typename t_CType>
	t_CType const &TCOptional<t_CType>::f_Get() const
	{
		if (this->f_GetTypeID() != 1)
			fp_ThrowEmpty();
		return &this->CVariant::template f_Get<1>(); 
	}

	template <typename t_CType>
	t_CType const &TCOptional<t_CType>::f_Get(t_CType const &_Default) const
	{
		if (this->f_GetTypeID() == 1)
			return this->CVariant::template f_Get<1>();
		return _Default;
	}
	
	template <typename t_CType>
	t_CType const *TCOptional<t_CType>::operator -> () const
	{
		if (this->f_GetTypeID() != 1)
			fp_ThrowEmpty();
		return &this->CVariant::template f_Get<1>(); 
	}

	template <typename t_CType>
	t_CType const &TCOptional<t_CType>::operator * () const
	{
		if (this->f_GetTypeID() != 1)
			fp_ThrowEmpty();
		return this->CVariant::template f_Get<1>(); 
	}
	
	template <typename t_CType>
	t_CType *TCOptional<t_CType>::operator -> ()
	{
		if (this->f_GetTypeID() != 1)
			fp_ThrowEmpty();
		return &this->CVariant::template f_Get<1>(); 
	}

	template <typename t_CType>
	t_CType &TCOptional<t_CType>::operator * ()
	{
		if (this->f_GetTypeID() != 1)
			fp_ThrowEmpty();
		return this->CVariant::template f_Get<1>(); 
	}

	template <typename t_CType>
	inline_never void TCOptional<t_CType>::fp_ThrowEmpty() const
	{
		DMibError("Empty optional access");
	}
}
