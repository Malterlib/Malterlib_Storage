// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStorage::NPrivate
{
	template <typename t_CType, typename t_CTypeStripped = typename NTraits::TCRemoveQualifiers<typename NTraits::TCRemoveReference<t_CType>::CType>::CType>
	struct TCIsIndirectionHelper
	{
		enum
		{
			mc_Value = false
		};
	};
	template <typename t_CType0, typename t_CType, typename t_CAllocator, typename t_CPtr>
	struct TCIsIndirectionHelper<t_CType0, NStorage::NIndirection::TCIndirection<t_CType, t_CAllocator, t_CPtr>>
	{
		enum
		{
			mc_Value = true
		};
	};
}
