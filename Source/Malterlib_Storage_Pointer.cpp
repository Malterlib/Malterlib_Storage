// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

namespace NMib::NStorage
{
	CAutoClearPtr::CAutoClearPtr() = default;
	CAutoClearPtr::~CAutoClearPtr() = default;

	CAutoClearPtrMember::CAutoClearPtrMember() = default;

	CAutoClearPtrMember::~CAutoClearPtrMember()
	{
		f_Clear();
	}

	void CAutoClearPtrMember::f_Clear()
	{
		CAutoClearPtr *pPtr = m_Linked.f_Pop();
		while (pPtr)
		{
			((CAutoClearPtrDefaultDummy *)pPtr)->m_pPointTo = nullptr;
			pPtr = m_Linked.f_Pop();
		}
	}

	CAutoClearPtrMember::CAutoClearPtrMember(CAutoClearPtrMember const &_Other)
	{
	}

	auto CAutoClearPtrMember::operator = (CAutoClearPtrMember const &_Other) -> CAutoClearPtrMember &
	{
		return *this;
	}

	CAutoClearPtrMemberDebug::CAutoClearPtrMemberDebug() = default;

	CAutoClearPtrMemberDebug::~CAutoClearPtrMemberDebug()
	{
		DMibCheck(m_Linked.f_IsEmpty())("There are still references to this pointer")(m_Linked.f_GetLen());
	}

	void CAutoClearPtrMemberDebug::f_Clear()
	{
		CAutoClearPtr *pPtr = m_Linked.f_Pop();
		while (pPtr)
		{
			((CAutoClearPtrDefaultDummy *)pPtr)->m_pPointTo = nullptr;
			pPtr = m_Linked.f_Pop();
		}
	}

	CAutoClearPtrMemberDebug::CAutoClearPtrMemberDebug(CAutoClearPtrMemberDebug const &_Other)
	{
	}

	auto CAutoClearPtrMemberDebug::operator = (CAutoClearPtrMemberDebug const &_Other) -> CAutoClearPtrMemberDebug &
	{
		return *this;
	}
}
