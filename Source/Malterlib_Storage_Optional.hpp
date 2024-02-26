// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStorage
{
	template <typename t_CType>
	TCOptional<t_CType>::TCOptional(CNullPtr) noexcept
	{
	}

	template <typename t_CType>
	TCOptional<t_CType>::TCOptional(t_CType const &_Value)
		: CVariant(_Value)
	{
	}

	template <typename t_CType>
	template <typename tf_CType, typename... tfp_CParams, mint... tfp_Indidies>
	TCOptional<t_CType>::TCOptional(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams, NMeta::TCIndices<tfp_Indidies...> const &)
		: CVariant
		(
			fg_Forward<tfp_CParams>(fg_Get<tfp_Indidies>(_CreateParams.m_Params))...
		)
	{
	}

	template <typename t_CType>
	template <typename tf_CType, typename... tfp_CParams>
	TCOptional<t_CType>::TCOptional(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
		: TCOptional(fg_Move(_CreateParams), typename NMeta::TCMakeConsecutiveIndices<TCConstruct<tf_CType, tfp_CParams...>::mc_nParams>::CType())
	{
	}

	template <typename t_CType>
	TCOptional<t_CType>::TCOptional(t_CType &&_Value)
		: CVariant(fg_Move(_Value))
	{
	}
	
	template <typename t_CType>
	template <typename tf_CType>
	TCOptional<t_CType>::TCOptional(TCOptional<tf_CType> const &_Value)
	{
		if (_Value)
			static_cast<CVariant &>(*this) = *_Value;
	}

	template <typename t_CType>
	template <typename tf_CType>
	TCOptional<t_CType>::TCOptional(TCOptional<tf_CType> &_Value)
	{
		if (_Value)
			static_cast<CVariant &>(*this) = *_Value;
	}

	template <typename t_CType>
	template <typename tf_CType>
	TCOptional<t_CType>::TCOptional(TCOptional<tf_CType> &&_Value)
	{
		if (_Value)
			static_cast<CVariant &>(*this) = fg_Move(*_Value);
	}
	
	template <typename t_CType>
	template <typename tf_CType>
	auto TCOptional<t_CType>::operator = (TCOptional<tf_CType> const &_Value) -> TCOptional &
		requires requires ()
		{
			static_cast<CVariant &>(*this) = *_Value;
		}
	{
		if (_Value)
			static_cast<CVariant &>(*this) = *_Value;
		else
			static_cast<CVariant &>(*this) = CVariant();
	}

	template <typename t_CType>
	template <typename tf_CType>
	auto TCOptional<t_CType>::operator = (TCOptional<tf_CType> &_Value) -> TCOptional &
		requires requires ()
		{
			static_cast<CVariant &>(*this) = *_Value;
		}
	{
		if (_Value)
			static_cast<CVariant &>(*this) = *_Value;
		else
			static_cast<CVariant &>(*this) = CVariant();
	}

	template <typename t_CType>
	template <typename tf_CType>
	auto TCOptional<t_CType>::operator = (TCOptional<tf_CType> &&_Value) -> TCOptional &
		requires requires ()
		{
			static_cast<CVariant &>(*this) = fg_Move(*_Value);
		}
	{
		if (_Value)
			static_cast<CVariant &>(*this) = fg_Move(*_Value);
		else
			static_cast<CVariant &>(*this) = CVariant();
	}

	template <typename t_CType>
	auto TCOptional<t_CType>::operator = (t_CType const &_Value) -> TCOptional &
		requires requires ()
		{
			*((CVariant *)this) = _Value;
		}
	{
		*((CVariant *)this) = _Value;
		return *this;
	}

	template <typename t_CType>
	auto TCOptional<t_CType>::operator = (t_CType &&_Value) -> TCOptional &
		requires requires ()
		{
			*((CVariant *)this) = fg_Move(_Value);
		}
	{
		*((CVariant *)this) = fg_Move(_Value);
		return *this;
	}
	
	template <typename t_CType>
	template <typename tf_CType>
	auto TCOptional<t_CType>::operator = (tf_CType &&_Value) -> TCOptional &
		requires requires ()
		{
			*((CVariant *)this) = fg_Forward<tf_CType>(_Value);
		}
	{
		*((CVariant *)this) = fg_Forward<tf_CType>(_Value);
		return *this;
	}

	template <typename t_CType>
	template <typename tf_CType, typename... tfp_CParams>
	auto TCOptional<t_CType>::operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams) -> TCOptional &
		requires requires ()
		{
			*((CVariant *)this) = (fg_Move(_CreateParams));
		}
	{
		*((CVariant *)this) = (fg_Move(_CreateParams));
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
		return this->CVariant::template f_Get<1>(); 
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
	template <typename tf_CStream>
	void TCOptional<t_CType>::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << static_cast<CVariant const &>(*this);
	}

	template <typename t_CType>
	template <typename tf_CStream>
	void TCOptional<t_CType>::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> static_cast<CVariant &>(*this);
	}

	template <typename t_CType>
	template <typename tf_CString>
	void TCOptional<t_CType>::f_Format(tf_CString &_String) const
	{
		if (*this)
			_String += typename tf_CString::CFormat("{{{}}") << **this;
		else
			_String += "not set";
	}
	
	template <typename t_CType>
	inline_never void TCOptional<t_CType>::fp_ThrowEmpty() const
	{
		DMibError("Empty optional access");
	}
			
	template <typename t_CType>
	template <typename tf_CType>
	bool TCOptional<t_CType>::operator == (TCOptional<tf_CType> const &_Right) const
	{
		if (!*this)
		{
			if (!_Right)
				return true;
			return false;
		}
		else if (!_Right)
			return false;

		return **this == *_Right;
	}
	
	template <typename t_CType>
	template <typename tf_CType>
	auto TCOptional<t_CType>::operator <=> (TCOptional<tf_CType> const &_Right) const
	{
		using COrdering = decltype(**this <=> *_Right);

		if (!*this)
		{
			if (!_Right)
				return COrdering::equivalent;
			else
				return COrdering::less;
		}
		else if (!_Right)
			return COrdering::greater;

		return **this <=> *_Right;
	}
}
