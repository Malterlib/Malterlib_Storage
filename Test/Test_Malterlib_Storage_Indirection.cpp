// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Storage/Indirection>
#include <Mib/Stream/Streams/Indirection>

namespace
{
	using namespace NMib;
	using namespace NMib::NStorage;
	namespace
	{
		struct CTestClass
		{
			struct CTestUndefined;
			struct CTestDefined
			{
				void operator () ();

				uint16 operator () () const;

				uint32 operator () () volatile;

				uint64 operator () () const volatile;

				auto operator <=> (float _Value) const noexcept;

				COrdering_Weak operator <=> (CTestUndefined const &_Other) const noexcept;

				int m_Data;
			};

			CTestClass();
			~CTestClass();
			TCIndirection<CTestUndefined> m_Undefined;
			TCIndirection<CTestDefined> m_Defined;
		};

		void CTestClass::CTestDefined::operator () ()
		{
		}

		uint16 CTestClass::CTestDefined::operator () () const
		{
			return 0;
		}

		uint32 CTestClass::CTestDefined::operator () () volatile
		{
			return 0;
		}

		uint64 CTestClass::CTestDefined::operator () () const volatile
		{
			return 0;
		}

		auto CTestClass::CTestDefined::operator <=> (float _Value) const noexcept
		{
			return m_Data <=> _Value;
		}

		struct CIndirection_Tests : public NTest::CTest
		{
			void f_DoDefinedTests(CTestClass &_Indirection);
			void f_DoTests();
		};

		void CIndirection_Tests::f_DoTests()
		{
			CTestClass Indirection;
			f_DoDefinedTests(Indirection);
		}

		struct CTestClass::CTestUndefined
		{
			void operator () ();

			uint16 operator () () const;

			uint32 operator () () volatile;

			uint64 operator () () const volatile;

			auto operator <=> (float _Value) const noexcept;

			auto operator <=> (CTestDefined const &_Other) noexcept;

			int m_Data;
		};

		void CTestClass::CTestUndefined::operator () ()
		{
		}

		uint16 CTestClass::CTestUndefined::operator () () const
		{
			return 0;
		}

		uint32 CTestClass::CTestUndefined::operator () () volatile
		{
			return 0;
		}

		uint64 CTestClass::CTestUndefined::operator () () const volatile
		{
			return 0;
		}

		auto CTestClass::CTestUndefined::operator <=> (float _Value) const noexcept
		{
			return m_Data <=> _Value;
		}

		auto CTestClass::CTestUndefined::operator <=> (CTestDefined const &_Other) noexcept
		{
			return m_Data <=> _Other.m_Data;
		}

		COrdering_Weak CTestClass::CTestDefined::operator <=> (CTestUndefined const &_Other) const noexcept
		{
			return m_Data <=> _Other.m_Data;
		}

		auto operator <=> (float const &_Left, CTestClass::CTestDefined const &_Right) noexcept
		{
			return _Left <=> _Right.m_Data;
		}

		auto operator <=> (float const &_Left, CTestClass::CTestUndefined const &_Right) noexcept
		{
			return _Left <=> _Right.m_Data;
		}

		CTestClass::CTestClass()
		{
		}

		CTestClass::~CTestClass()
		{
		}

		void CIndirection_Tests::f_DoDefinedTests(CTestClass &_Indirection)
		{
			_Indirection.m_Undefined();
			_Indirection.m_Defined();

			//static_assert(decltype(Test0));

			[[maybe_unused]] auto Test2 = fg_Const(_Indirection.m_Undefined)();
			[[maybe_unused]] auto Test3 = fg_Const(_Indirection.m_Defined)();

			[[maybe_unused]] auto bTest8 = _Indirection.m_Undefined < 5.0f;
			[[maybe_unused]] auto bTest9 = _Indirection.m_Defined < 5.0f;
			[[maybe_unused]] auto bTest10 = 5.0f < _Indirection.m_Undefined;
			[[maybe_unused]] auto bTest11 = 5.0f < _Indirection.m_Defined;
			[[maybe_unused]] auto bTest12 = _Indirection.m_Undefined < 5;
			[[maybe_unused]] auto bTest13 = _Indirection.m_Defined < 5;
			[[maybe_unused]] auto bTest14 = 5 < _Indirection.m_Undefined;
			[[maybe_unused]] auto bTest15 = 5 < _Indirection.m_Defined;
			[[maybe_unused]] auto bTest16 = _Indirection.m_Defined < _Indirection.m_Undefined;
			[[maybe_unused]] auto bTest17 = _Indirection.m_Undefined < _Indirection.m_Defined;

			TCIndirection<uint32> StreamTest = 50;

			struct CCCCC
			{
				uint32 m_TestInt:24;
			};

			CCCCC TestInt;
			TestInt.m_TestInt = 50;
			NStream::TCBinaryStreamMemory<> Stream;
			Stream << StreamTest;
			uint32 Temp = TestInt.m_TestInt;
			Stream << Temp;

			TCIndirection<uint32> StreamTest2;
			Stream.f_SetPosition(0);
			Stream >> StreamTest2;
		}
	}

	DMibTestRegister(CIndirection_Tests, Malterlib::Storage);
}

