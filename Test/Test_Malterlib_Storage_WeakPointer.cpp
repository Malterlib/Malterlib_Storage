// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

using namespace NMib::NCryptography;
using namespace NMib;
using namespace NMib::NMemory;
using namespace NMib::NStream;
using namespace NMib::NContainer;
using namespace NMib::NStorage;

#include <memory>

namespace NMib
{
	namespace NStorage
	{

	}
}

namespace
{
	class CWeakPointer_Tests : public NMib::NTest::CTest
	{
	public:

		struct CTestWeakIntrusive
		{
			NStorage::CIntrusiveRefCountWithWeak m_RefCount;
			umint m_Dummy = 0; // Will be overwritten after destructor is called
			uint32 m_Value;
			bool m_bDestroyed = false;
			CTestWeakIntrusive *m_pThis;
			CTestWeakIntrusive(uint32 _Value)
				: m_Value(_Value)
				, m_pThis(this)
			{
			}
			~CTestWeakIntrusive()
			{
				m_bDestroyed = true;
			}
		};

		struct CTestIntrusive
		{
			NStorage::CIntrusiveRefCount m_RefCount;

			uint32 m_Value;
			bool m_bDestroyed = false;
			CTestIntrusive *m_pThis;
			CTestIntrusive(uint32 _Value)
				: m_Value(_Value)
				, m_pThis(this)
			{
			}
			~CTestIntrusive()
			{
				m_bDestroyed = true;
			}
		};

		void f_TestRefCounting()
		{
			{
				DMibTestPath("Weak destroys");
				TCSharedPointer<CTestWeakIntrusive, CSupportWeakTag> pPointer = fg_Construct(5);
				auto pThis = pPointer->m_pThis;

				DMibTest(DMibExpr(pThis->m_RefCount.f_Get()) == DMibExpr(0));
				DMibTest(DMibExpr(pThis->m_RefCount.f_WeakGet()) == DMibExpr(0));

				TCWeakPointer<CTestWeakIntrusive> pWeakPointer = pPointer;
				{
					DMibTestPath("After weak");

					DMibTest(DMibExpr(pThis->m_RefCount.f_Get()) == DMibExpr(0));
					DMibTest(DMibExpr(pThis->m_RefCount.f_WeakGet()) == DMibExpr(1));
				}
				TCWeakPointer<CTestWeakIntrusive> pWeakPointer2 = pWeakPointer;
				{
					DMibTestPath("After weak 2");

					DMibTest(DMibExpr(pThis->m_RefCount.f_Get()) == DMibExpr(0));
					DMibTest(DMibExpr(pThis->m_RefCount.f_WeakGet()) == DMibExpr(2));
				}

				DMibTest(DMibExpr(!pThis->m_bDestroyed));
				pPointer.f_Clear();
				DMibTest(DMibExpr(!!pThis->m_bDestroyed));
				{
					DMibTestPath("After shared cleared");

					DMibTest(DMibExpr(pThis->m_RefCount.f_Get()) <= DMibExpr(-1));
					DMibTest(DMibExpr(pThis->m_RefCount.f_WeakGet()) == DMibExpr(1));
				}

				pWeakPointer.f_Clear();
				{
					DMibTestPath("After weak cleared");

					DMibTest(DMibExpr(pThis->m_RefCount.f_Get()) <= DMibExpr(-1));
					DMibTest(DMibExpr(pThis->m_RefCount.f_WeakGet()) == DMibExpr(0));
				}
				pWeakPointer2.f_Clear();
			}
			{
				DMibTestPath("Shared destroys");
				TCSharedPointer<CTestWeakIntrusive, CSupportWeakTag> pPointer = fg_Construct(5);

				auto pThis = pPointer->m_pThis;

				DMibTest(DMibExpr(pThis->m_RefCount.f_Get()) == DMibExpr(0));
				DMibTest(DMibExpr(pThis->m_RefCount.f_WeakGet()) == DMibExpr(0));

				TCWeakPointer<CTestWeakIntrusive> pWeakPointer = pPointer;

				{
					DMibTestPath("After weak");

					DMibTest(DMibExpr(pThis->m_RefCount.f_Get()) == DMibExpr(0));
					DMibTest(DMibExpr(pThis->m_RefCount.f_WeakGet()) == DMibExpr(1));
				}

				TCWeakPointer<CTestWeakIntrusive> pWeakPointer2 = pWeakPointer;
				{
					DMibTestPath("After weak 2");

					DMibTest(DMibExpr(pThis->m_RefCount.f_Get()) == DMibExpr(0));
					DMibTest(DMibExpr(pThis->m_RefCount.f_WeakGet()) == DMibExpr(2));
				}

				pWeakPointer.f_Clear();
				pWeakPointer2.f_Clear();
				{
					DMibTestPath("After weak cleared");

					DMibTest(DMibExpr(pThis->m_RefCount.f_Get()) == DMibExpr(0));
					DMibTest(DMibExpr(pThis->m_RefCount.f_WeakGet()) == DMibExpr(0));
				}

				DMibTest(DMibExpr(!pThis->m_bDestroyed));
				pPointer.f_Clear();
			}
			{
				DMibTestPath("No weak support");
				TCSharedPointer<CTestIntrusive> pPointer = fg_Construct(5);

				auto pThis = pPointer->m_pThis;

				DMibTest(DMibExpr(pThis->m_RefCount.f_Get()) == DMibExpr(0));
				DMibTest(DMibExpr(!pThis->m_bDestroyed));
				pPointer.f_Clear();
			}

				std::shared_ptr<int> pSharedPointer = std::make_shared<int>(5);
				std::weak_ptr<int> pWeakPointer = pSharedPointer;
				std::shared_ptr<int> pSharedPointer2 = pWeakPointer.lock();

				pSharedPointer = nullptr;
				pSharedPointer2 = nullptr;
				pWeakPointer = std::weak_ptr<int>();


		}

		void f_TestLock()
		{
			{
				DMibTestPath("Non-destroyed");
				TCSharedPointer<CTestWeakIntrusive, CSupportWeakTag> pPointer = fg_Construct(5);

				TCWeakPointer<CTestWeakIntrusive> pWeakPointer = pPointer;

				TCSharedPointer<CTestWeakIntrusive, CSupportWeakTag> pPointer2 = pWeakPointer.f_Lock();

				TCSharedPointer<CTestWeakIntrusive, NMib::NMemory::CDefaultAllocator, CSupportWeakTag> pPointerDifferentOrder = pWeakPointer.f_Lock();

				DMibTest(!DMibExpr(pPointer.f_IsEmpty()));
				DMibTest(!DMibExpr(pPointer2.f_IsEmpty()));
				DMibTest(!DMibExpr(pPointerDifferentOrder.f_IsEmpty()));
				DMibTest(DMibExpr(pPointer2->m_Value) == DMibExpr(5));
				DMibTest(DMibExpr(pPointer->m_Value) == DMibExpr(pPointer2->m_Value));
				DMibTest(DMibExpr(pPointerDifferentOrder->m_Value) == DMibExpr(5));
			}
			{
				DMibTestPath("Destroyed");
				TCSharedPointer<CTestWeakIntrusive, CSupportWeakTag> pPointer = fg_Construct(5);

				TCWeakPointer<CTestWeakIntrusive> pWeakPointer = pPointer;

				pPointer.f_Clear();

				TCSharedPointer<CTestWeakIntrusive, CSupportWeakTag> pPointer2 = pWeakPointer.f_Lock();

				TCSharedPointer<CTestWeakIntrusive, NMib::NMemory::CDefaultAllocator, CSupportWeakTag> pPointerDifferentOrder = pWeakPointer.f_Lock();

				DMibTest(DMibExpr(pPointer.f_IsEmpty()));
				DMibTest(DMibExpr(pPointer2.f_IsEmpty()));
				DMibTest(DMibExpr(pPointerDifferentOrder.f_IsEmpty()));
			}
		}

		void f_TestNonIntrusive()
		{
			{
				TCSharedPointer<int32, CSupportWeakTag> pPointer = fg_Construct(5);

				TCWeakPointer<int32> pWeakPointer = pPointer;

				TCSharedPointer<int32, CSupportWeakTag> pPointer2 = pWeakPointer.f_Lock();

				TCSharedPointer<int32, NMib::NMemory::CDefaultAllocator, CSupportWeakTag> pPointerDifferentOrder = pWeakPointer.f_Lock();

				DMibTest(!DMibExpr(pPointer.f_IsEmpty()));
				DMibTest(!DMibExpr(pPointer2.f_IsEmpty()));
				DMibTest(!DMibExpr(pPointerDifferentOrder.f_IsEmpty()));
				DMibTest(DMibExpr(*pPointer2) == DMibExpr(5));
				DMibTest(DMibExpr(*pPointer) == DMibExpr(*pPointer2));
				DMibTest(DMibExpr(*pPointerDifferentOrder) == DMibExpr(5));
			}
		}

		void f_DoTests()
		{
			DMibTestSuite("Ref counting")
			{
				f_TestRefCounting();
			};
			DMibTestSuite("Locking")
			{
				f_TestLock();
			};
			DMibTestSuite("Non-intrusive")
			{
				f_TestNonIntrusive();
			};

		}
	};

	DMibTestRegister(CWeakPointer_Tests, Malterlib::Storage);
}

