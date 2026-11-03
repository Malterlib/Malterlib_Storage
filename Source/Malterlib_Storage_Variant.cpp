// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Storage_Variant.h"

namespace NMib::NStorage::NPrivate
{
	inline_always_lto void CVariantVisitor_Destruct::operator () (CVoidTag _Tag)
	{
	}
}
