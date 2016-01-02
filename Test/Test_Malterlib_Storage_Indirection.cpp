// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Storage/Indirection>

namespace
{
	using namespace NMib;
	using namespace NMib::NIndirection;
	namespace 
	{
		class CTestClass
		{
		public:
			class CTestUndefined;
			class CTestDefined
			{
			public:
				int m_Data;
				void operator () ()
				{
				}
				uint16 operator () () const
				{
					return 0;
				}
				uint32 operator () () volatile
				{
					return 0;
				}
				uint64 operator () () const volatile
				{
					return 0;
				}

				bint operator < (float _Value) const
				{
					return m_Data < _Value;
				}
				bint operator < (CTestUndefined const &_Other);
			};
			CTestClass();
			~CTestClass();
			TCIndirection<CTestUndefined> m_Undefined;
			TCIndirection<CTestDefined> m_Defined;
		};

		class CIndirection_Tests : public NTest::CTest
		{
		public:

			void f_DoDefinedTests(CTestClass &_Indirection);
			void f_DoTests()
			{
				CTestClass Indirection;
				f_DoDefinedTests(Indirection);
			}
				
		};

		class CTestClass::CTestUndefined
		{
		public:
			int m_Data;
			void operator () ()
			{
			}
			uint16 operator () () const
			{
				return 0;
			}
			uint32 operator () () volatile
			{
				return 0;
			}
			uint64 operator () () const volatile
			{
				return 0;
			}
			bint operator < (float _Value) const
			{
				return m_Data < _Value;
			}
			bint operator < (CTestDefined const &_Other)
			{
				return m_Data < _Other.m_Data;
			}
		};

		bint CTestClass::CTestDefined::operator < (CTestUndefined const &_Other)
		{
			return m_Data < _Other.m_Data;
		}
		bint operator < (float const &_Left, CTestClass::CTestDefined const &_Right)
		{
			return _Left < _Right.m_Data;
		}
		bint operator < (float const &_Left, CTestClass::CTestUndefined const &_Right)
		{
			return _Left < _Right.m_Data;
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

			//DMibStaticCheck(decltype(Test0));

			auto Test2 = fg_Const(_Indirection.m_Undefined)();
			auto Test3 = fg_Const(_Indirection.m_Defined)();

			auto Test4 = fg_Volatile(_Indirection.m_Undefined)();
			auto Test5 = fg_Volatile(_Indirection.m_Defined)();

			auto Test6 = fg_ConstVolatile(_Indirection.m_Undefined)();
			auto Test7 = fg_ConstVolatile(_Indirection.m_Defined)();

			auto Test8 = _Indirection.m_Undefined < 5.0f;
			auto Test9 = _Indirection.m_Defined < 5.0f;
			auto Test10 = 5.0f < _Indirection.m_Undefined;
			auto Test11 = 5.0f < _Indirection.m_Defined ;
			auto Test12 = _Indirection.m_Undefined < 5;
			auto Test13 = _Indirection.m_Defined < 5;
			auto Test14 = 5 < _Indirection.m_Undefined;
			auto Test15 = 5 < _Indirection.m_Defined ;
			auto Test16 = _Indirection.m_Defined < _Indirection.m_Undefined;
			auto Test17 = _Indirection.m_Undefined < _Indirection.m_Defined;

			TCIndirection<uint32> StreamTest = 50;

			struct CCCCC
			{
				uint32 TestInt:24;
			};
			CCCCC TestInt;
			TestInt.TestInt = 50;
			NStream::CBinaryStreamMemory<> Stream;
			Stream << StreamTest;
			uint32 Temp = TestInt.TestInt;
			Stream << Temp;

			TCIndirection<uint32> StreamTest2;
			Stream.f_SetPosition(0);
			Stream >> StreamTest2;



		}
	}
	
	DMibTestRegister(CIndirection_Tests, Malterlib::Storage);
}


