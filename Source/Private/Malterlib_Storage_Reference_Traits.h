// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStorage::NReference::NPrivate
{
	template <typename t_CType, typename t_CTypeStripped = typename NTraits::TCRemoveQualifiers<typename NTraits::TCRemoveReference<t_CType>::CType>::CType>
	struct TCIsReferenceHelper
	{
		enum
		{
			mc_Value = false
		};
	};

	template <typename t_CType0, typename t_CType>
	struct TCIsReferenceHelper<t_CType0, TCReference<t_CType>>
	{
		enum
		{
			mc_Value = true
		};
	};
}
