// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>
#include <Mib/Storage/Variant>

namespace NMib::NStorage
{
	enum class EOptionalMoveSemantics
	{
		mc_KeepEngaged
		, mc_Clear
	};

	template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics = EOptionalMoveSemantics::mc_KeepEngaged>
	struct TCOptional : public NStorage::TCStreamableVariant
		<
			int8
			, NStorage::TCMember<void, int8(0)>
			, NStorage::TCMember<t_CType, int8(1)>
		>
	{
		using CType = t_CType;
		using CVariant = NStorage::TCStreamableVariant
			<
				int8
				, NStorage::TCMember<void, int8(0)>
				, NStorage::TCMember<t_CType, int8(1)>
			>
		;

		template <typename tf_CType, typename... tfp_CParams, umint... tfp_Indidies>
		TCOptional(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams, NMeta::TCIndices<tfp_Indidies...> const &);

		template <typename tf_CType, typename... tfp_CParams>
		TCOptional(TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams);

		TCOptional(t_CType const &_Value);
		TCOptional(t_CType &&_Value);
		TCOptional &operator = (t_CType const &_Value)
			requires requires ()
			{
				*((CVariant *)this) = _Value;
			}
		;
		TCOptional &operator = (t_CType &&_Value)
			requires requires ()
			{
				*((CVariant *)this) = fg_Move(_Value);
			}
		;

		template <typename tf_CType>
		TCOptional &operator = (tf_CType &&_Value)
			requires requires ()
			{
				*((CVariant *)this) = fg_Forward<tf_CType>(_Value);
			}
		;

		template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
		TCOptional(TCOptional<tf_CType, tf_MoveSemantics> const &_Value);
		template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
		TCOptional(TCOptional<tf_CType, tf_MoveSemantics> &_Value);
		template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
		TCOptional(TCOptional<tf_CType, tf_MoveSemantics> &&_Value);

		template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
		TCOptional &operator = (TCOptional<tf_CType, tf_MoveSemantics> const &_Value)
			requires requires ()
			{
				static_cast<CVariant &>(*this) = *_Value;
			}
		;
		template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
		TCOptional &operator = (TCOptional<tf_CType, tf_MoveSemantics> &_Value)
			requires requires ()
			{
				static_cast<CVariant &>(*this) = *_Value;
			}
		;
		template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
		TCOptional &operator = (TCOptional<tf_CType, tf_MoveSemantics> &&_Value)
			requires requires ()
			{
				static_cast<CVariant &>(*this) = fg_Move(*_Value);
			}
		;

		template <typename tf_CType, typename... tfp_CParams>
		TCOptional &operator = (TCConstruct<tf_CType, tfp_CParams...> &&_CreateParams)
			requires requires ()
			{
				*((CVariant *)this) = (fg_Move(_CreateParams));
			}
		;

		TCOptional() noexcept = default;
		TCOptional(CNullPtr) noexcept;
		TCOptional(TCOptional const &) = default;
		TCOptional(TCOptional &) = default;
		TCOptional(TCOptional &&_Other);
		TCOptional &operator = (TCOptional const &) = default;
		TCOptional &operator = (TCOptional &) = default;
		TCOptional &operator = (TCOptional &&_Other);

		template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
		bool operator == (TCOptional<tf_CType, tf_MoveSemantics> const &_Right) const noexcept(noexcept(fg_GetType<t_CType const &>() == fg_GetType<tf_CType const &>()));
		template <typename tf_CType, EOptionalMoveSemantics tf_MoveSemantics>
		auto operator <=> (TCOptional<tf_CType, tf_MoveSemantics> const &_Right) const noexcept(noexcept(fg_GetType<t_CType const &>() <=> fg_GetType<tf_CType const &>()));

		explicit operator bool() const;

		void f_Clear();
		t_CType const &f_Get() const;
		t_CType const &f_Get(t_CType const &_Default) const;
		t_CType const *operator -> () const;
		t_CType const &operator * () const;
		t_CType *operator -> ();
		t_CType &operator * ();

		t_CType &f_GetOrCreate();
		t_CType &f_CreateNew();

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

		template <typename tf_CString>
		void f_Format(tf_CString &_String) const;

	private:
		inline_never void fp_ThrowEmpty() const;
	};

	template <typename t_CType>
	using TCOptionalClearOnMove = TCOptional<t_CType, EOptionalMoveSemantics::mc_Clear>;

	namespace NPrivate
	{
		template <typename t_CType>
		struct TCIsOptional
		{
			constexpr static bool mc_bValue = false;
			using CType = t_CType;
		};

		template <typename t_CType, EOptionalMoveSemantics t_MoveSemantics>
		struct TCIsOptional<TCOptional<t_CType, t_MoveSemantics>>
		{
			constexpr static bool mc_bValue = true;
			using CType = t_CType;
		};
	}

	template <typename t_CType>
	concept cIsOptional = NPrivate::TCIsOptional<t_CType>::mc_bValue;

	template <typename t_CType>
	using TCOptionalType = typename NPrivate::TCIsOptional<t_CType>::CType;
}

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif

#include "Malterlib_Storage_Optional.hpp"
