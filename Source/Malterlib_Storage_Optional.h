// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
#include <Mib/Storage/Variant>

namespace NMib
{
	namespace NStorage
	{
		template <typename t_CType>
		struct TCOptional : public NContainer::TCStreamableVariant<int8, void, 0, t_CType, 1>
		{
			using CVariant = NContainer::TCStreamableVariant<int8, void, 0, t_CType, 1>;
			
			TCOptional(t_CType const &_Value);
			TCOptional(t_CType &&_Value);
			TCOptional &operator = (t_CType const &_Value);
			TCOptional &operator = (t_CType &&_Value);

			template <typename tf_CType>
			TCOptional &operator = (tf_CType &&_Value);

			template <typename tf_CType>
			TCOptional(TCOptional<tf_CType> const &_Value);
			template <typename tf_CType>
			TCOptional(TCOptional<tf_CType> &&_Value);

			template <typename tf_CType>
			TCOptional &operator = (TCOptional<tf_CType> const &_Value);
			template <typename tf_CType>
			TCOptional &operator = (TCOptional<tf_CType> &&_Value);
			
			TCOptional() = default;
			TCOptional(TCOptional const &) = default;
			TCOptional(TCOptional &&) = default;
			TCOptional &operator = (TCOptional const &) = default;
			TCOptional &operator = (TCOptional &&) = default;
			
			template <typename tf_CType>
			bool operator == (TCOptional<tf_CType> const &_Right) const;
			template <typename tf_CType>
			bool operator < (TCOptional<tf_CType> const &_Right) const;
			
			explicit operator bool() const;
			
			void f_Clear();
			t_CType const &f_Get() const;
			t_CType const &f_Get(t_CType const &_Default) const;
			t_CType const *operator -> () const;
			t_CType const &operator * () const;
			t_CType *operator -> ();
			t_CType &operator * ();
			
			template <typename tf_CStream>
			void f_Feed(tf_CStream &_Stream) const;
			template <typename tf_CStream>
			void f_Consume(tf_CStream &_Stream);

		private:
			inline_never void fp_ThrowEmpty() const;
		};
	}
}

#ifndef DMibPNoShortCuts
using namespace NMib::NStorage;
#endif

#include "Malterlib_Storage_Optional.hpp"
