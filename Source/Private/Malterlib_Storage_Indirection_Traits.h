// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStorage::NPrivate
{
	template <typename t_CType, typename t_CTypeStripped = NTraits::TCRemoveReferenceAndQualifiers<t_CType>>
	struct TCIsIndirectionHelper
	{
		constexpr static bool mc_Value = false;
	};

	template <typename t_CType0, typename t_CType, typename t_CAllocator>
	struct TCIsIndirectionHelper<t_CType0, NStorage::NIndirection::TCIndirection<t_CType, t_CAllocator>>
	{
		constexpr static bool mc_Value = true;
	};
}
