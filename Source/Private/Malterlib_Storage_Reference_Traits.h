// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib
{
	namespace NReference
	{
		namespace NPrivate
		{
			template <typename t_CType, typename t_CTypeStripped = typename NTraits::TCRemoveQualifiers<typename NTraits::TCRemoveReference<t_CType>::CType>::CType>
			struct TCIsReferenceHelper
			{
				enum
				{
					mc_Value = false
				};
			};

			template <typename t_CType0, typename t_CType, typename t_CPtr>
			struct TCIsReferenceHelper<t_CType0, TCReference<t_CType, t_CPtr>>
			{
				enum
				{
					mc_Value = true
				};
			};
		}

	}
}

