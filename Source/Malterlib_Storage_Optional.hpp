// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStorage
{
	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	TCOptional<t_CType, t_MoveSemantics>::TCOptional(CNullPtr) noexcept
	{
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	TCOptional<t_CType, t_MoveSemantics>::TCOptional(t_CType const &_Value)
		: CVariant(_Value)
	{
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CType, typename... tfp_CParams, umint... tfp_Indidies>
	TCOptional<t_CType, t_MoveSemantics>::TCOptional(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams, NMeta::TCIndices<tfp_Indidies...> const &)
		: CVariant
		(
			fg_Forward<tfp_CParams>(fg_Get<tfp_Indidies>(_CreateParams.m_Params))...
		)
	{
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CType, typename... tfp_CParams>
	TCOptional<t_CType, t_MoveSemantics>::TCOptional(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
		: TCOptional(fg_Move(_CreateParams), NMeta::TCConsecutiveIndices<TCConstruct<tf_CType, tfp_CParams...>::mc_nParams>())
	{
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	TCOptional<t_CType, t_MoveSemantics>::TCOptional(t_CType &&_Value)
		: CVariant(fg_Move(_Value))
	{
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
	TCOptional<t_CType, t_MoveSemantics>::TCOptional(TCOptional<tf_CType, tf_MoveSemantics> const &_Value)
	{
		if (_Value)
			static_cast<CVariant &>(*this) = *_Value;
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
	TCOptional<t_CType, t_MoveSemantics>::TCOptional(TCOptional<tf_CType, tf_MoveSemantics> &_Value)
	{
		if (_Value)
			static_cast<CVariant &>(*this) = *_Value;
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
	TCOptional<t_CType, t_MoveSemantics>::TCOptional(TCOptional<tf_CType, tf_MoveSemantics> &&_Value)
	{
		if (_Value)
		{
			static_cast<CVariant &>(*this) = fg_Move(*_Value);
			if constexpr (tf_MoveSemantics == EOptionalMoveSemantics::mc_Clear)
				_Value.f_Clear();
		}
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
	auto TCOptional<t_CType, t_MoveSemantics>::operator = (TCOptional<tf_CType, tf_MoveSemantics> const &_Value) -> TCOptional &
		requires requires ()
		{
			static_cast<CVariant &>(*this) = *_Value;
		}
	{
		if (_Value)
			static_cast<CVariant &>(*this) = *_Value;
		else
			static_cast<CVariant &>(*this) = CVariant();

		return *this;
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
	auto TCOptional<t_CType, t_MoveSemantics>::operator = (TCOptional<tf_CType, tf_MoveSemantics> &_Value) -> TCOptional &
		requires requires ()
		{
			static_cast<CVariant &>(*this) = *_Value;
		}
	{
		if (_Value)
			static_cast<CVariant &>(*this) = *_Value;
		else
			static_cast<CVariant &>(*this) = CVariant();

		return *this;
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
	auto TCOptional<t_CType, t_MoveSemantics>::operator = (TCOptional<tf_CType, tf_MoveSemantics> &&_Value) -> TCOptional &
		requires requires ()
		{
			static_cast<CVariant &>(*this) = fg_Move(*_Value);
		}
	{
		if (_Value)
		{
			static_cast<CVariant &>(*this) = fg_Move(*_Value);
			if constexpr (tf_MoveSemantics == EOptionalMoveSemantics::mc_Clear)
				_Value.f_Clear();
		}
		else
			static_cast<CVariant &>(*this) = CVariant();

		return *this;
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	TCOptional<t_CType, t_MoveSemantics>::TCOptional(TCOptional &&_Other)
		: CVariant(fg_Move(static_cast<CVariant &>(_Other)))
	{
		if constexpr (t_MoveSemantics == EOptionalMoveSemantics::mc_Clear)
			_Other.f_Clear();
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	auto TCOptional<t_CType, t_MoveSemantics>::operator = (TCOptional &&_Other) -> TCOptional &
	{
		if (this == &_Other)
			return *this;

		static_cast<CVariant &>(*this) = fg_Move(static_cast<CVariant &>(_Other));
		if constexpr (t_MoveSemantics == EOptionalMoveSemantics::mc_Clear)
			_Other.f_Clear();

		return *this;
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	auto TCOptional<t_CType, t_MoveSemantics>::operator = (t_CType const &_Value) -> TCOptional &
		requires requires ()
		{
			*((CVariant *)this) = _Value;
		}
	{
		*((CVariant *)this) = _Value;
		return *this;
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	auto TCOptional<t_CType, t_MoveSemantics>::operator = (t_CType &&_Value) -> TCOptional &
		requires requires ()
		{
			*((CVariant *)this) = fg_Move(_Value);
		}
	{
		*((CVariant *)this) = fg_Move(_Value);
		return *this;
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CType>
	auto TCOptional<t_CType, t_MoveSemantics>::operator = (tf_CType &&_Value) -> TCOptional &
		requires requires ()
		{
			*((CVariant *)this) = fg_Forward<tf_CType>(_Value);
		}
	{
		*((CVariant *)this) = fg_Forward<tf_CType>(_Value);
		return *this;
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CType, typename... tfp_CParams>
	auto TCOptional<t_CType, t_MoveSemantics>::operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams) -> TCOptional &
		requires requires ()
		{
			*((CVariant *)this) = (fg_Move(_CreateParams));
		}
	{
		*((CVariant *)this) = (fg_Move(_CreateParams));
		return *this;
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	void TCOptional<t_CType, t_MoveSemantics>::f_Clear()
	{
		this->template f_Set<0>();
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	TCOptional<t_CType, t_MoveSemantics>::operator bool() const
	{
		return this->f_GetTypeID() == 1;
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	t_CType const &TCOptional<t_CType, t_MoveSemantics>::f_Get() const
	{
		if (this->f_GetTypeID() != 1)
			fp_ThrowEmpty();
		return this->CVariant::template f_Get<1>();
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	t_CType const &TCOptional<t_CType, t_MoveSemantics>::f_Get(t_CType const &_Default) const
	{
		if (this->f_GetTypeID() == 1)
			return this->CVariant::template f_Get<1>();
		return _Default;
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	t_CType &TCOptional<t_CType, t_MoveSemantics>::f_GetOrCreate()
	{
		if (*this)
			return this->CVariant::template f_Get<1>();

		return this->template f_Set<1>();
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	t_CType &TCOptional<t_CType, t_MoveSemantics>::f_CreateNew()
	{
		return this->template f_Set<1>();
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	t_CType const *TCOptional<t_CType, t_MoveSemantics>::operator -> () const
	{
		if (this->f_GetTypeID() != 1)
			fp_ThrowEmpty();
		return &this->CVariant::template f_Get<1>();
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	t_CType const &TCOptional<t_CType, t_MoveSemantics>::operator * () const
	{
		if (this->f_GetTypeID() != 1)
			fp_ThrowEmpty();
		return this->CVariant::template f_Get<1>();
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	t_CType *TCOptional<t_CType, t_MoveSemantics>::operator -> ()
	{
		if (this->f_GetTypeID() != 1)
			fp_ThrowEmpty();
		return &this->CVariant::template f_Get<1>();
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	t_CType &TCOptional<t_CType, t_MoveSemantics>::operator * ()
	{
		if (this->f_GetTypeID() != 1)
			fp_ThrowEmpty();
		return this->CVariant::template f_Get<1>();
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CStream>
	void TCOptional<t_CType, t_MoveSemantics>::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << static_cast<CVariant const &>(*this);
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CStream>
	void TCOptional<t_CType, t_MoveSemantics>::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> static_cast<CVariant &>(*this);
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CString>
	void TCOptional<t_CType, t_MoveSemantics>::f_Format(tf_CString &_String) const
	{
		if (*this)
			_String += typename tf_CString::CFormat("{{{}}") << **this;
		else
			_String += "not set";
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	inline_never void TCOptional<t_CType, t_MoveSemantics>::fp_ThrowEmpty() const
	{
		DMibError("Empty optional access");
	}

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
	auto TCOptional<t_CType, t_MoveSemantics>::operator == (TCOptional<tf_CType, tf_MoveSemantics> const &_Right) const
		noexcept(noexcept(fg_GetType<t_CType const &>() == fg_GetType<tf_CType const &>()))
		-> bool
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

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
	template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
	auto TCOptional<t_CType, t_MoveSemantics>::operator <=> (TCOptional<tf_CType, tf_MoveSemantics> const &_Right) const
		noexcept(noexcept(fg_GetType<t_CType const &>() <=> fg_GetType<tf_CType const &>()))
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
