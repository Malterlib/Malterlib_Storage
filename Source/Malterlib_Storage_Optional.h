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
		struct TCOptional : public TCStreamableVariant<int8, void, 0, t_CType, 1>
		{
			using CVariant = TCStreamableVariant<int8, void, 0, t_CType, 1>;
			
			TCOptional(t_CType const &_Value);
			TCOptional(t_CType &&_Value);
			TCOptional &operator = (t_CType const &_Value);
			TCOptional &operator = (t_CType &&_Value);
			
			TCOptional() = default;
			TCOptional(TCOptional const &) = default;
			TCOptional(TCOptional &&) = default;
			TCOptional &operator = (TCOptional const &) = default;
			TCOptional &operator = (TCOptional &&) = default;
			
			explicit operator bool() const;
			
			void f_Clear();
			t_CType const &f_Get() const;
			t_CType const &f_Get(t_CType const &_Default) const;
			t_CType const *operator -> () const;
			t_CType const &operator * () const;
			t_CType *operator -> ();
			t_CType &operator * ();

		private:
			inline_never void fp_ThrowEmpty() const;
		};
	}
}

#ifndef DMibPNoShortCuts
using namespace NMib::NStorage;
#endif

#include "Malterlib_Storage_Optional.hpp"
