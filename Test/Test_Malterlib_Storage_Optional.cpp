// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Storage/Optional>

namespace
{
	using namespace NMib;
	using namespace NMib::NStorage;

	struct CValue
	{
		CValue() = default;

		CValue(int32 _Value)
			: m_Value(_Value)
		{
		}

		CValue(CValue const &) = default;
		CValue &operator = (CValue const &) = default;

		CValue(CValue &&_Other)
			: m_Value(_Other.m_Value)
		{
			_Other.m_Value = -1;
		}

		CValue &operator = (CValue &&_Other)
		{
			m_Value = _Other.m_Value;
			_Other.m_Value = -1;

			return *this;
		}

		template <typename tf_CString>
		void f_Format(tf_CString &_String) const
		{
			_String += typename tf_CString::CFormat("{}") << m_Value;
		}

		int32 m_Value = 1;
	};

	struct COptionalOwner
	{
		COptionalOwner(int32 *_pDestructions)
			: m_pDestructions(_pDestructions)
			, m_Value(CValue(7))
		{
		}

		COptionalOwner(COptionalOwner &&) = default;

		~COptionalOwner()
		{
			if (m_Value)
				++*m_pDestructions;
		}

		int32 *m_pDestructions;
		TCOptionalClearOnMove<CValue> m_Value;
	};

	struct COptional_Tests : public NTest::CTest
	{
		void f_TestKeepEngaged()
		{
			TCOptional<CValue> Source = CValue(7);
			TCOptional<CValue> Destination = fg_Move(Source);

			DMibExpectTrue(Source);
			DMibExpect(Source->m_Value, ==, -1);
			DMibExpectTrue(Destination);
			DMibExpect(Destination->m_Value, ==, 7);

			TCOptional<CValue> AssignmentSource = CValue(8);
			TCOptional<CValue> AssignmentDestination;
			AssignmentDestination = fg_Move(AssignmentSource);

			DMibExpectTrue(AssignmentSource);
			DMibExpect(AssignmentSource->m_Value, ==, -1);
			DMibExpectTrue(AssignmentDestination);
			DMibExpect(AssignmentDestination->m_Value, ==, 8);
		}

		void f_TestClearOnMove()
		{
			TCOptionalClearOnMove<CValue> Source = CValue(7);
			TCOptionalClearOnMove<CValue> Destination = fg_Move(Source);

			DMibExpectFalse(Source);
			DMibExpectTrue(Destination);
			DMibExpect(Destination->m_Value, ==, 7);

			TCOptionalClearOnMove<CValue> AssignmentSource = CValue(8);
			TCOptionalClearOnMove<CValue> AssignmentDestination;
			AssignmentDestination = fg_Move(AssignmentSource);

			DMibExpectFalse(AssignmentSource);
			DMibExpectTrue(AssignmentDestination);
			DMibExpect(AssignmentDestination->m_Value, ==, 8);

			TCOptionalClearOnMove<CValue> CopySource = CValue(9);
			TCOptionalClearOnMove<CValue> CopyDestination = CopySource;

			DMibExpectTrue(CopySource);
			DMibExpect(CopySource->m_Value, ==, 9);
			DMibExpectTrue(CopyDestination);
			DMibExpect(CopyDestination->m_Value, ==, 9);
		}

		void f_TestCrossSemanticsMove()
		{
			TCOptionalClearOnMove<int32> ClearSource = 7;
			TCOptional<int64> KeepDestination = fg_Move(ClearSource);

			DMibExpectFalse(ClearSource);
			DMibExpect(*KeepDestination, ==, 7);

			TCOptional<int32> KeepSource = 8;
			TCOptionalClearOnMove<int64> ClearDestination = fg_Move(KeepSource);

			DMibExpectTrue(KeepSource);
			DMibExpect(*KeepSource, ==, 8);
			DMibExpect(*ClearDestination, ==, 8);
		}

		void f_TestCreate()
		{
			TCOptional<CValue> Value;
			CValue &Created = Value.f_GetOrCreate();

			DMibExpect(Created.m_Value, ==, 1);
			Created.m_Value = 7;

			CValue &Existing = Value.f_GetOrCreate();
			DMibExpect(&Existing, ==, &Created);
			DMibExpect(Existing.m_Value, ==, 7);

			CValue &New = Value.f_CreateNew();
			DMibExpect(New.m_Value, ==, 1);
		}

		void f_TestFormat()
		{
			TCOptional<int32> KeepEngaged = 7;
			TCOptionalClearOnMove<int32> ClearOnMove = 8;
			TCOptionalClearOnMove<int32> Empty;

			DMibExpect(NStr::CStr::fs_ToStr(KeepEngaged), ==, "{7}");
			DMibExpect(NStr::CStr::fs_ToStr(ClearOnMove), ==, "{8}");
			DMibExpect(NStr::CStr::fs_ToStr(Empty), ==, "not set");
		}

		void f_TestDefaultedOwnerMove()
		{
			int32 nDestructions = 0;
			{
				COptionalOwner Source(&nDestructions);
				{
					COptionalOwner Destination(fg_Move(Source));

					DMibExpectFalse(Source.m_Value);
					DMibExpectTrue(Destination.m_Value);
				}

				{
					DMibTestPath("Destination destruction");
					DMibExpect(nDestructions, ==, 1);
				}
			}

			{
				DMibTestPath("Source destruction");
				DMibExpect(nDestructions, ==, 1);
			}
		}

		void f_DoTests()
		{
			static_assert(cIsOptional<TCOptional<int32>>);
			static_assert(cIsOptional<TCOptionalClearOnMove<int32>>);
			static_assert(NTraits::cIsSame<TCOptionalType<TCOptionalClearOnMove<int32>>, int32>);

			DMibTestSuite("General")
			{
				DMibTestCategory("Keep engaged")
				{
					f_TestKeepEngaged();
				};
				DMibTestCategory("Clear on move")
				{
					f_TestClearOnMove();
					f_TestCrossSemanticsMove();
					f_TestDefaultedOwnerMove();
				};
				DMibTestCategory("Create")
				{
					f_TestCreate();
				};
				DMibTestCategory("Format")
				{
					f_TestFormat();
				};
			};
		}
	};

	DMibTestRegister(COptional_Tests, Malterlib::Storage);
}
