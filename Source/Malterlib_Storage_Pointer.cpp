// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

namespace NMib
{
	namespace NPtr
	{

		CAutoClearPtrMemberDebug::CAutoClearPtrMemberDebug()
		{
		}
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


	}
}
