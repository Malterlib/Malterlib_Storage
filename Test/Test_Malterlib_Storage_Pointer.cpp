// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <memory>

using namespace NMib::NCryptography;
using namespace NMib;
using namespace NMib::NMemory;
using namespace NMib::NStream;
using namespace NMib::NContainer;
using namespace NMib::NStorage;

namespace
{
	struct CSmartPtr_Tests : public NMib::NTest::CTest
	{
		struct CTestStruct
		{
			int m_Value0;
			int m_Value1;
			int m_Value2;
			int m_Value3;
			int m_Value4;
			int m_Value5;
			int m_Value6;
			int m_Value7;
			int m_Value8;
			int m_Value9;

			CTestStruct(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5, int _Value6, int _Value7, int _Value8, int _Value9)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(_Value4)
				, m_Value5(_Value5)
				, m_Value6(_Value6)
				, m_Value7(_Value7)
				, m_Value8(_Value8)
				, m_Value9(_Value9)
			{
			}

			CTestStruct(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5, int _Value6, int _Value7, int _Value8)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(_Value4)
				, m_Value5(_Value5)
				, m_Value6(_Value6)
				, m_Value7(_Value7)
				, m_Value8(_Value8)
				, m_Value9(0)
			{
			}

			CTestStruct(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5, int _Value6, int _Value7)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(_Value4)
				, m_Value5(_Value5)
				, m_Value6(_Value6)
				, m_Value7(_Value7)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStruct(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5, int _Value6)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(_Value4)
				, m_Value5(_Value5)
				, m_Value6(_Value6)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStruct(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(_Value4)
				, m_Value5(_Value5)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStruct(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(_Value4)
				, m_Value5(0)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStruct(int _Value0, int _Value1, int _Value2, int _Value3)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(0)
				, m_Value5(0)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStruct(int _Value0, int _Value1, int _Value2)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(0)
				, m_Value4(0)
				, m_Value5(0)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStruct(int _Value0, int _Value1)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(0)
				, m_Value3(0)
				, m_Value4(0)
				, m_Value5(0)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStruct(int _Value0)
				: m_Value0(_Value0)
				, m_Value1(0)
				, m_Value2(0)
				, m_Value3(0)
				, m_Value4(0)
				, m_Value5(0)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStruct()
				: m_Value0(0)
				, m_Value1(0)
				, m_Value2(0)
				, m_Value3(0)
				, m_Value4(0)
				, m_Value5(0)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			bool operator == (CTestStruct const &_Other) const noexcept
			{
				return m_Value0 == _Other.m_Value0
					&& m_Value1 == _Other.m_Value1
					&& m_Value2 == _Other.m_Value2
					&& m_Value3 == _Other.m_Value3
					&& m_Value4 == _Other.m_Value4
					&& m_Value5 == _Other.m_Value5
					&& m_Value6 == _Other.m_Value6
					&& m_Value7 == _Other.m_Value7
					&& m_Value8 == _Other.m_Value8
					&& m_Value9 == _Other.m_Value9
				;
			}
		};

		struct CTestStructVirtual
		{
			int m_Value0;
			int m_Value1;
			int m_Value2;
			int m_Value3;
			int m_Value4;
			int m_Value5;
			int m_Value6;
			int m_Value7;
			int m_Value8;
			int m_Value9;

			CTestStructVirtual(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5, int _Value6, int _Value7, int _Value8, int _Value9)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(_Value4)
				, m_Value5(_Value5)
				, m_Value6(_Value6)
				, m_Value7(_Value7)
				, m_Value8(_Value8)
				, m_Value9(_Value9)
			{
			}

			CTestStructVirtual(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5, int _Value6, int _Value7, int _Value8)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(_Value4)
				, m_Value5(_Value5)
				, m_Value6(_Value6)
				, m_Value7(_Value7)
				, m_Value8(_Value8)
				, m_Value9(0)
			{
			}

			CTestStructVirtual(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5, int _Value6, int _Value7)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(_Value4)
				, m_Value5(_Value5)
				, m_Value6(_Value6)
				, m_Value7(_Value7)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStructVirtual(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5, int _Value6)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(_Value4)
				, m_Value5(_Value5)
				, m_Value6(_Value6)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStructVirtual(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(_Value4)
				, m_Value5(_Value5)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStructVirtual(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(_Value4)
				, m_Value5(0)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStructVirtual(int _Value0, int _Value1, int _Value2, int _Value3)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(_Value3)
				, m_Value4(0)
				, m_Value5(0)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStructVirtual(int _Value0, int _Value1, int _Value2)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(_Value2)
				, m_Value3(0)
				, m_Value4(0)
				, m_Value5(0)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStructVirtual(int _Value0, int _Value1)
				: m_Value0(_Value0)
				, m_Value1(_Value1)
				, m_Value2(0)
				, m_Value3(0)
				, m_Value4(0)
				, m_Value5(0)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStructVirtual(int _Value0)
				: m_Value0(_Value0)
				, m_Value1(0)
				, m_Value2(0)
				, m_Value3(0)
				, m_Value4(0)
				, m_Value5(0)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			CTestStructVirtual()
				: m_Value0(0)
				, m_Value1(0)
				, m_Value2(0)
				, m_Value3(0)
				, m_Value4(0)
				, m_Value5(0)
				, m_Value6(0)
				, m_Value7(0)
				, m_Value8(0)
				, m_Value9(0)
			{
			}

			virtual ~CTestStructVirtual()
			{
			}

			bool operator == (CTestStructVirtual const &_Other) const noexcept
			{
				return m_Value0 == _Other.m_Value0
					&& m_Value1 == _Other.m_Value1
					&& m_Value2 == _Other.m_Value2
					&& m_Value3 == _Other.m_Value3
					&& m_Value4 == _Other.m_Value4
					&& m_Value5 == _Other.m_Value5
					&& m_Value6 == _Other.m_Value6
					&& m_Value7 == _Other.m_Value7
					&& m_Value8 == _Other.m_Value8
					&& m_Value9 == _Other.m_Value9
				;
			}
		};

		struct CTestStruct2 : public CTestStructVirtual
		{
			CTestStruct2()
				: CTestStructVirtual()
			{
			}

			CTestStruct2(int _Value0)
				: CTestStructVirtual(_Value0)
			{
			}

			CTestStruct2(int _Value0, int _Value1)
				: CTestStructVirtual(_Value0, _Value1)
			{
			}

			CTestStruct2(int _Value0, int _Value1, int _Value2)
				: CTestStructVirtual(_Value0, _Value1, _Value2)
			{
			}

			CTestStruct2(int _Value0, int _Value1, int _Value2, int _Value3)
				: CTestStructVirtual(_Value0, _Value1, _Value2, _Value3)
			{
			}

			CTestStruct2(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4)
				: CTestStructVirtual(_Value0, _Value1, _Value2, _Value3, _Value4)
			{
			}

			CTestStruct2(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5)
				: CTestStructVirtual(_Value0, _Value1, _Value2, _Value3, _Value4, _Value5)
			{
			}

			CTestStruct2(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5, int _Value6)
				: CTestStructVirtual(_Value0, _Value1, _Value2, _Value3, _Value4, _Value5, _Value6)
			{
			}

			CTestStruct2(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5, int _Value6, int _Value7)
				: CTestStructVirtual(_Value0, _Value1, _Value2, _Value3, _Value4, _Value5, _Value6, _Value7)
			{
			}

			CTestStruct2(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5, int _Value6, int _Value7, int _Value8)
				: CTestStructVirtual(_Value0, _Value1, _Value2, _Value3, _Value4, _Value5, _Value6, _Value7, _Value8)
			{
			}

			CTestStruct2(int _Value0, int _Value1, int _Value2, int _Value3, int _Value4, int _Value5, int _Value6, int _Value7, int _Value8, int _Value9)
				: CTestStructVirtual(_Value0, _Value1, _Value2, _Value3, _Value4, _Value5, _Value6, _Value7, _Value8, _Value9)
			{
			}
		};

		struct CCopyMove
		{
			int m_nMoves;
			int m_nCopies;
			CCopyMove()
				: m_nMoves(0)
				, m_nCopies(0)
			{
			}

			CCopyMove(CCopyMove &&_Other)
				: m_nMoves(_Other.m_nMoves + 1)
				, m_nCopies(_Other.m_nCopies)
			{
			}

			CCopyMove &operator = (CCopyMove &&_Other)
			{
				m_nMoves += _Other.m_nMoves + 1;
				m_nCopies += _Other.m_nCopies;
				return *this;
			}

			CCopyMove(CCopyMove const &_Other)
				: m_nMoves(_Other.m_nMoves)
				, m_nCopies(_Other.m_nCopies + 1)
			{
			}

			CCopyMove &operator = (CCopyMove const &_Other)
			{
				m_nMoves += _Other.m_nMoves;
				m_nCopies += _Other.m_nCopies + 1;
				return *this;
			}
		};

		struct CTestCopyMove
		{
			CCopyMove m_CopyMove0;
			CCopyMove m_CopyMove1;
			CCopyMove m_CopyMove2;
			CCopyMove m_CopyMove3;
			CCopyMove m_CopyMove4;
			CCopyMove m_CopyMove5;
			CCopyMove m_CopyMove6;
			CCopyMove m_CopyMove7;
			CCopyMove m_CopyMove8;
			CCopyMove m_CopyMove9;
			int f_GetNumMoves() const
			{
				return m_CopyMove0.m_nMoves
					+ m_CopyMove1.m_nMoves
					+ m_CopyMove2.m_nMoves
					+ m_CopyMove3.m_nMoves
					+ m_CopyMove4.m_nMoves
					+ m_CopyMove5.m_nMoves
					+ m_CopyMove6.m_nMoves
					+ m_CopyMove7.m_nMoves
					+ m_CopyMove8.m_nMoves
					+ m_CopyMove9.m_nMoves
				;
			}

			int f_GetNumCopies() const
			{
				return m_CopyMove0.m_nCopies
					+ m_CopyMove1.m_nCopies
					+ m_CopyMove2.m_nCopies
					+ m_CopyMove3.m_nCopies
					+ m_CopyMove4.m_nCopies
					+ m_CopyMove5.m_nCopies
					+ m_CopyMove6.m_nCopies
					+ m_CopyMove7.m_nCopies
					+ m_CopyMove8.m_nCopies
					+ m_CopyMove9.m_nCopies
				;
			}

			CTestCopyMove()
			{
			}

			CTestCopyMove(CCopyMove &&_CopyMove0)
				: m_CopyMove0(NMib::fg_Move(_CopyMove0))
			{
			}

			CTestCopyMove(CCopyMove &&_CopyMove0, CCopyMove &&_CopyMove1)
				: m_CopyMove0(NMib::fg_Move(_CopyMove0))
				, m_CopyMove1(NMib::fg_Move(_CopyMove1))
			{
			}

			CTestCopyMove(CCopyMove &&_CopyMove0, CCopyMove &&_CopyMove1, CCopyMove &&_CopyMove2)
				: m_CopyMove0(NMib::fg_Move(_CopyMove0))
				, m_CopyMove1(NMib::fg_Move(_CopyMove1))
				, m_CopyMove2(NMib::fg_Move(_CopyMove2))
			{
			}

			CTestCopyMove(CCopyMove &&_CopyMove0, CCopyMove &&_CopyMove1, CCopyMove &&_CopyMove2, CCopyMove &&_CopyMove3)
				: m_CopyMove0(NMib::fg_Move(_CopyMove0))
				, m_CopyMove1(NMib::fg_Move(_CopyMove1))
				, m_CopyMove2(NMib::fg_Move(_CopyMove2))
				, m_CopyMove3(NMib::fg_Move(_CopyMove3))
			{
			}

			CTestCopyMove(CCopyMove &&_CopyMove0, CCopyMove &&_CopyMove1, CCopyMove &&_CopyMove2, CCopyMove &&_CopyMove3, CCopyMove &&_CopyMove4)
				: m_CopyMove0(NMib::fg_Move(_CopyMove0))
				, m_CopyMove1(NMib::fg_Move(_CopyMove1))
				, m_CopyMove2(NMib::fg_Move(_CopyMove2))
				, m_CopyMove3(NMib::fg_Move(_CopyMove3))
				, m_CopyMove4(NMib::fg_Move(_CopyMove4))
			{
			}

			CTestCopyMove(CCopyMove &&_CopyMove0, CCopyMove &&_CopyMove1, CCopyMove &&_CopyMove2, CCopyMove &&_CopyMove3, CCopyMove &&_CopyMove4, CCopyMove &&_CopyMove5)
				: m_CopyMove0(NMib::fg_Move(_CopyMove0))
				, m_CopyMove1(NMib::fg_Move(_CopyMove1))
				, m_CopyMove2(NMib::fg_Move(_CopyMove2))
				, m_CopyMove3(NMib::fg_Move(_CopyMove3))
				, m_CopyMove4(NMib::fg_Move(_CopyMove4))
				, m_CopyMove5(NMib::fg_Move(_CopyMove5))
			{
			}

			CTestCopyMove
				(
					CCopyMove &&_CopyMove0
					, CCopyMove &&_CopyMove1
					, CCopyMove &&_CopyMove2
					, CCopyMove &&_CopyMove3
					, CCopyMove &&_CopyMove4
					, CCopyMove &&_CopyMove5
					, CCopyMove &&_CopyMove6
				)
				: m_CopyMove0(NMib::fg_Move(_CopyMove0))
				, m_CopyMove1(NMib::fg_Move(_CopyMove1))
				, m_CopyMove2(NMib::fg_Move(_CopyMove2))
				, m_CopyMove3(NMib::fg_Move(_CopyMove3))
				, m_CopyMove4(NMib::fg_Move(_CopyMove4))
				, m_CopyMove5(NMib::fg_Move(_CopyMove5))
				, m_CopyMove6(NMib::fg_Move(_CopyMove6))
			{
			}

			CTestCopyMove
				(
					CCopyMove &&_CopyMove0
					, CCopyMove &&_CopyMove1
					, CCopyMove &&_CopyMove2
					, CCopyMove &&_CopyMove3
					, CCopyMove &&_CopyMove4
					, CCopyMove &&_CopyMove5
					, CCopyMove &&_CopyMove6
					, CCopyMove &&_CopyMove7
				)
				: m_CopyMove0(NMib::fg_Move(_CopyMove0))
				, m_CopyMove1(NMib::fg_Move(_CopyMove1))
				, m_CopyMove2(NMib::fg_Move(_CopyMove2))
				, m_CopyMove3(NMib::fg_Move(_CopyMove3))
				, m_CopyMove4(NMib::fg_Move(_CopyMove4))
				, m_CopyMove5(NMib::fg_Move(_CopyMove5))
				, m_CopyMove6(NMib::fg_Move(_CopyMove6))
				, m_CopyMove7(NMib::fg_Move(_CopyMove7))
			{
			}

			CTestCopyMove
				(
					CCopyMove &&_CopyMove0
					, CCopyMove &&_CopyMove1
					, CCopyMove &&_CopyMove2
					, CCopyMove &&_CopyMove3
					, CCopyMove &&_CopyMove4
					, CCopyMove &&_CopyMove5
					, CCopyMove &&_CopyMove6
					, CCopyMove &&_CopyMove7
					, CCopyMove &&_CopyMove8
				)
				: m_CopyMove0(NMib::fg_Move(_CopyMove0))
				, m_CopyMove1(NMib::fg_Move(_CopyMove1))
				, m_CopyMove2(NMib::fg_Move(_CopyMove2))
				, m_CopyMove3(NMib::fg_Move(_CopyMove3))
				, m_CopyMove4(NMib::fg_Move(_CopyMove4))
				, m_CopyMove5(NMib::fg_Move(_CopyMove5))
				, m_CopyMove6(NMib::fg_Move(_CopyMove6))
				, m_CopyMove7(NMib::fg_Move(_CopyMove7))
				, m_CopyMove8(NMib::fg_Move(_CopyMove8))
			{
			}

			CTestCopyMove
				(
					CCopyMove &&_CopyMove0
					, CCopyMove &&_CopyMove1
					, CCopyMove &&_CopyMove2
					, CCopyMove &&_CopyMove3
					, CCopyMove &&_CopyMove4
					, CCopyMove &&_CopyMove5
					, CCopyMove &&_CopyMove6
					, CCopyMove &&_CopyMove7
					, CCopyMove &&_CopyMove8
					, CCopyMove &&_CopyMove9
				)
				: m_CopyMove0(NMib::fg_Move(_CopyMove0))
				, m_CopyMove1(NMib::fg_Move(_CopyMove1))
				, m_CopyMove2(NMib::fg_Move(_CopyMove2))
				, m_CopyMove3(NMib::fg_Move(_CopyMove3))
				, m_CopyMove4(NMib::fg_Move(_CopyMove4))
				, m_CopyMove5(NMib::fg_Move(_CopyMove5))
				, m_CopyMove6(NMib::fg_Move(_CopyMove6))
				, m_CopyMove7(NMib::fg_Move(_CopyMove7))
				, m_CopyMove8(NMib::fg_Move(_CopyMove8))
				, m_CopyMove9(NMib::fg_Move(_CopyMove9))
			{
			}

			CTestCopyMove(CCopyMove const &_CopyMove0)
				: m_CopyMove0(_CopyMove0)
			{
			}

			CTestCopyMove(CCopyMove const &_CopyMove0, CCopyMove const &_CopyMove1)
				: m_CopyMove0(_CopyMove0)
				, m_CopyMove1(_CopyMove1)
			{
			}

			CTestCopyMove(CCopyMove const &_CopyMove0, CCopyMove const &_CopyMove1, CCopyMove const &_CopyMove2)
				: m_CopyMove0(_CopyMove0)
				, m_CopyMove1(_CopyMove1)
				, m_CopyMove2(_CopyMove2)
			{
			}

			CTestCopyMove(CCopyMove const &_CopyMove0, CCopyMove const &_CopyMove1, CCopyMove const &_CopyMove2, CCopyMove const &_CopyMove3)
				: m_CopyMove0(_CopyMove0)
				, m_CopyMove1(_CopyMove1)
				, m_CopyMove2(_CopyMove2)
				, m_CopyMove3(_CopyMove3)
			{
			}

			CTestCopyMove(CCopyMove const &_CopyMove0, CCopyMove const &_CopyMove1, CCopyMove const &_CopyMove2, CCopyMove const &_CopyMove3, CCopyMove const &_CopyMove4)
				: m_CopyMove0(_CopyMove0)
				, m_CopyMove1(_CopyMove1)
				, m_CopyMove2(_CopyMove2)
				, m_CopyMove3(_CopyMove3)
				, m_CopyMove4(_CopyMove4)
			{
			}

			CTestCopyMove
				(
					CCopyMove const &_CopyMove0
					, CCopyMove const &_CopyMove1
					, CCopyMove const &_CopyMove2
					, CCopyMove const &_CopyMove3
					, CCopyMove const &_CopyMove4
					, CCopyMove const &_CopyMove5
				)
				: m_CopyMove0(_CopyMove0)
				, m_CopyMove1(_CopyMove1)
				, m_CopyMove2(_CopyMove2)
				, m_CopyMove3(_CopyMove3)
				, m_CopyMove4(_CopyMove4)
				, m_CopyMove5(_CopyMove5)
			{
			}

			CTestCopyMove
				(
					CCopyMove const &_CopyMove0
					, CCopyMove const &_CopyMove1
					, CCopyMove const &_CopyMove2
					, CCopyMove const &_CopyMove3
					, CCopyMove const &_CopyMove4
					, CCopyMove const &_CopyMove5
					, CCopyMove const &_CopyMove6
				)
				: m_CopyMove0(_CopyMove0)
				, m_CopyMove1(_CopyMove1)
				, m_CopyMove2(_CopyMove2)
				, m_CopyMove3(_CopyMove3)
				, m_CopyMove4(_CopyMove4)
				, m_CopyMove5(_CopyMove5)
				, m_CopyMove6(_CopyMove6)
			{
			}

			CTestCopyMove
				(
					CCopyMove const &_CopyMove0
					, CCopyMove const &_CopyMove1
					, CCopyMove const &_CopyMove2
					, CCopyMove const &_CopyMove3
					, CCopyMove const &_CopyMove4
					, CCopyMove const &_CopyMove5
					, CCopyMove const &_CopyMove6
					, CCopyMove const &_CopyMove7
				)
				: m_CopyMove0(_CopyMove0)
				, m_CopyMove1(_CopyMove1)
				, m_CopyMove2(_CopyMove2)
				, m_CopyMove3(_CopyMove3)
				, m_CopyMove4(_CopyMove4)
				, m_CopyMove5(_CopyMove5)
				, m_CopyMove6(_CopyMove6)
				, m_CopyMove7(_CopyMove7)
			{
			}

			CTestCopyMove
				(
					CCopyMove const &_CopyMove0
					, CCopyMove const &_CopyMove1
					, CCopyMove const &_CopyMove2
					, CCopyMove const &_CopyMove3
					, CCopyMove const &_CopyMove4
					, CCopyMove const &_CopyMove5
					, CCopyMove const &_CopyMove6
					, CCopyMove const &_CopyMove7
					, CCopyMove const &_CopyMove8
				)
				: m_CopyMove0(_CopyMove0)
				, m_CopyMove1(_CopyMove1)
				, m_CopyMove2(_CopyMove2)
				, m_CopyMove3(_CopyMove3)
				, m_CopyMove4(_CopyMove4)
				, m_CopyMove5(_CopyMove5)
				, m_CopyMove6(_CopyMove6)
				, m_CopyMove7(_CopyMove7)
				, m_CopyMove8(_CopyMove8)
			{
			}

			CTestCopyMove
				(
					CCopyMove const &_CopyMove0
					, CCopyMove const &_CopyMove1
					, CCopyMove const &_CopyMove2
					, CCopyMove const &_CopyMove3
					, CCopyMove const &_CopyMove4
					, CCopyMove const &_CopyMove5
					, CCopyMove const &_CopyMove6
					, CCopyMove const &_CopyMove7
					, CCopyMove const &_CopyMove8
					, CCopyMove const &_CopyMove9
				)
				: m_CopyMove0(_CopyMove0)
				, m_CopyMove1(_CopyMove1)
				, m_CopyMove2(_CopyMove2)
				, m_CopyMove3(_CopyMove3)
				, m_CopyMove4(_CopyMove4)
				, m_CopyMove5(_CopyMove5)
				, m_CopyMove6(_CopyMove6)
				, m_CopyMove7(_CopyMove7)
				, m_CopyMove8(_CopyMove8)
				, m_CopyMove9(_CopyMove9)
			{
			}
		};

		void f_TestUniquePointer()
		{
			TCUniquePointer<int> pTestInt(fg_Construct());
			TCUniquePointer<int> pTestInt2(fg_Construct(3));
			DMibTest(DMibExpr(*pTestInt2) == DMibExpr(3))(ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> pTest0(fg_Construct());
			DMibTest(DMibExpr(*pTest0) == DMibExpr(CSmartPtr_Tests::CTestStruct(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> pTest1(fg_Construct(1));
			DMibTest(DMibExpr(*pTest1) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 0, 0, 0, 0, 0, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> pTest2(fg_Construct(1, 2));
			DMibTest(DMibExpr(*pTest2) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 0, 0, 0, 0, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> pTest3(fg_Construct(1, 2, 3));
			DMibTest(DMibExpr(*pTest3) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 0, 0, 0, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> pTest4(fg_Construct(1, 2, 3, 4));
			DMibTest(DMibExpr(*pTest4) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 0, 0, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> pTest5(fg_Construct(1, 2, 3, 4, 5));
			DMibTest(DMibExpr(*pTest5) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 0, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> pTest6(fg_Construct(1, 2, 3, 4, 5, 6));
			DMibTest(DMibExpr(*pTest6) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> pTest7(fg_Construct(1, 2, 3, 4, 5, 6, 7));
			DMibTest(DMibExpr(*pTest7) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 0, 0, 0)))(ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> pTest8(fg_Construct(1, 2, 3, 4, 5, 6, 7, 8));
			DMibTest(DMibExpr(*pTest8) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 8, 0, 0)))(ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> pTest9(fg_Construct(1, 2, 3, 4, 5, 6, 7, 8, 9));
			DMibTest(DMibExpr(*pTest9) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 8, 9, 0)))(ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> pTest10(fg_Construct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
			DMibTest(DMibExpr(*pTest10) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)))(ETestFlag_NoValues);

			// Construct derived type
			TCUniquePointer<CTestStructVirtual> pTestDerived0(fg_Construct<CTestStruct2>());
			DMibTest(DMibExpr(*pTestDerived0) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual()))(ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> pTestDerived1(fg_Construct<CTestStruct2>(0));
			DMibTest(DMibExpr(*pTestDerived1) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0)))(ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> pTestDerived2(fg_Construct<CTestStruct2>(0, 1));
			DMibTest(DMibExpr(*pTestDerived2) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1)))(ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> pTestDerived3(fg_Construct<CTestStruct2>(0, 1, 2));
			DMibTest(DMibExpr(*pTestDerived3) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2)))(ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> pTestDerived4(fg_Construct<CTestStruct2>(0, 1, 2, 3));
			DMibTest(DMibExpr(*pTestDerived4) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3)))(ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> pTestDerived5(fg_Construct<CTestStruct2>(0, 1, 2, 3, 4));
			DMibTest(DMibExpr(*pTestDerived5) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3, 4)))(ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> pTestDerived6(fg_Construct<CTestStruct2>(0, 1, 2, 3, 4, 5));
			DMibTest(DMibExpr(*pTestDerived6) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3, 4, 5)))(ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> pTestDerived7(fg_Construct<CTestStruct2>(0, 1, 2, 3, 4, 5, 6));
			DMibTest(DMibExpr(*pTestDerived7) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3, 4, 5, 6)))(ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> pTestDerived8(fg_Construct<CTestStruct2>(0, 1, 2, 3, 4, 5, 6, 7));
			DMibTest(DMibExpr(*pTestDerived8) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3, 4, 5, 6, 7)))(ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> pTestDerived9(fg_Construct<CTestStruct2>(0, 1, 2, 3, 4, 5, 6, 7, 8));
			DMibTest(DMibExpr(*pTestDerived9) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3, 4, 5, 6, 7, 8)))(ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> pTestDerived10(fg_Construct<CTestStruct2>(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
			DMibTest(DMibExpr(*pTestDerived10) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)))(ETestFlag_NoValues);

			using CCopyMove = CSmartPtr_Tests::CCopyMove;

			// Moves
			TCUniquePointer<CTestCopyMove> pTestMove0(fg_Construct());
			DMibTest(DMibExpr(pTestMove0->f_GetNumMoves()) == DMibExpr(0));
			DMibTest(DMibExpr(pTestMove0->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMove1(fg_Construct(CCopyMove()));
			DMibTest(DMibExpr(pTestMove1->f_GetNumMoves()) == DMibExpr(1));
			DMibTest(DMibExpr(pTestMove1->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMove2(fg_Construct(CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove2->f_GetNumMoves()) == DMibExpr(2));
			DMibTest(DMibExpr(pTestMove2->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMove3(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove3->f_GetNumMoves()) == DMibExpr(3));
			DMibTest(DMibExpr(pTestMove3->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMove4(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove4->f_GetNumMoves()) == DMibExpr(4));
			DMibTest(DMibExpr(pTestMove4->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMove5(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove5->f_GetNumMoves()) == DMibExpr(5));
			DMibTest(DMibExpr(pTestMove5->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMove6(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove6->f_GetNumMoves()) == DMibExpr(6));
			DMibTest(DMibExpr(pTestMove6->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMove7(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove7->f_GetNumMoves()) == DMibExpr(7));
			DMibTest(DMibExpr(pTestMove7->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMove8(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove8->f_GetNumMoves()) == DMibExpr(8));
			DMibTest(DMibExpr(pTestMove8->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMove9(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove9->f_GetNumMoves()) == DMibExpr(9));
			DMibTest(DMibExpr(pTestMove9->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMove10
				(
					fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove())
				)
			;
			DMibTest(DMibExpr(pTestMove10->f_GetNumMoves()) == DMibExpr(10));
			DMibTest(DMibExpr(pTestMove10->f_GetNumCopies()) == DMibExpr(0));

			// Moves explicit
			TCUniquePointer<CTestCopyMove> pTestMoveExplicit0(fg_Construct<CTestCopyMove>());
			DMibTest(DMibExpr(pTestMoveExplicit0->f_GetNumMoves()) == DMibExpr(0));
			DMibTest(DMibExpr(pTestMoveExplicit0->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMoveExplicit1(fg_Construct<CTestCopyMove>(CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit1->f_GetNumMoves()) == DMibExpr(1));
			DMibTest(DMibExpr(pTestMoveExplicit1->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMoveExplicit2(fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit2->f_GetNumMoves()) == DMibExpr(2));
			DMibTest(DMibExpr(pTestMoveExplicit2->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMoveExplicit3(fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit3->f_GetNumMoves()) == DMibExpr(3));
			DMibTest(DMibExpr(pTestMoveExplicit3->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMoveExplicit4(fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit4->f_GetNumMoves()) == DMibExpr(4));
			DMibTest(DMibExpr(pTestMoveExplicit4->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMoveExplicit5(fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit5->f_GetNumMoves()) == DMibExpr(5));
			DMibTest(DMibExpr(pTestMoveExplicit5->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMoveExplicit6(fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit6->f_GetNumMoves()) == DMibExpr(6));
			DMibTest(DMibExpr(pTestMoveExplicit6->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMoveExplicit7(fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit7->f_GetNumMoves()) == DMibExpr(7));
			DMibTest(DMibExpr(pTestMoveExplicit7->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMoveExplicit8
				(
					fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove())
				)
			;
			DMibTest(DMibExpr(pTestMoveExplicit8->f_GetNumMoves()) == DMibExpr(8));
			DMibTest(DMibExpr(pTestMoveExplicit8->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMoveExplicit9
				(
					fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove())
				)
			;
			DMibTest(DMibExpr(pTestMoveExplicit9->f_GetNumMoves()) == DMibExpr(9));
			DMibTest(DMibExpr(pTestMoveExplicit9->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestMoveExplicit10
				(
					fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove())
				)
			;
			DMibTest(DMibExpr(pTestMoveExplicit10->f_GetNumMoves()) == DMibExpr(10));
			DMibTest(DMibExpr(pTestMoveExplicit10->f_GetNumCopies()) == DMibExpr(0));

			// Copies
			CCopyMove CopyFrom;
			TCUniquePointer<CTestCopyMove> pTestCopy0(fg_Construct());
			DMibTest(DMibExpr(pTestCopy0->f_GetNumCopies()) == DMibExpr(0));
			DMibTest(DMibExpr(pTestCopy0->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopy1(fg_Construct(CopyFrom));
			DMibTest(DMibExpr(pTestCopy1->f_GetNumCopies()) == DMibExpr(1));
			DMibTest(DMibExpr(pTestCopy1->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopy2(fg_Construct(CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy2->f_GetNumCopies()) == DMibExpr(2));
			DMibTest(DMibExpr(pTestCopy2->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopy3(fg_Construct(CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy3->f_GetNumCopies()) == DMibExpr(3));
			DMibTest(DMibExpr(pTestCopy3->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopy4(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy4->f_GetNumCopies()) == DMibExpr(4));
			DMibTest(DMibExpr(pTestCopy4->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopy5(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy5->f_GetNumCopies()) == DMibExpr(5));
			DMibTest(DMibExpr(pTestCopy5->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopy6(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy6->f_GetNumCopies()) == DMibExpr(6));
			DMibTest(DMibExpr(pTestCopy6->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopy7(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy7->f_GetNumCopies()) == DMibExpr(7));
			DMibTest(DMibExpr(pTestCopy7->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopy8(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy8->f_GetNumCopies()) == DMibExpr(8));
			DMibTest(DMibExpr(pTestCopy8->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopy9(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy9->f_GetNumCopies()) == DMibExpr(9));
			DMibTest(DMibExpr(pTestCopy9->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopy10(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy10->f_GetNumCopies()) == DMibExpr(10));
			DMibTest(DMibExpr(pTestCopy10->f_GetNumMoves()) == DMibExpr(0));

			// Copies explicit
			TCUniquePointer<CTestCopyMove> pTestCopyExplicit0(fg_Construct<CTestCopyMove>());
			DMibTest(DMibExpr(pTestCopyExplicit0->f_GetNumCopies()) == DMibExpr(0));
			DMibTest(DMibExpr(pTestCopyExplicit0->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopyExplicit1(fg_Construct<CTestCopyMove>(CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit1->f_GetNumCopies()) == DMibExpr(1));
			DMibTest(DMibExpr(pTestCopyExplicit1->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopyExplicit2(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit2->f_GetNumCopies()) == DMibExpr(2));
			DMibTest(DMibExpr(pTestCopyExplicit2->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopyExplicit3(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit3->f_GetNumCopies()) == DMibExpr(3));
			DMibTest(DMibExpr(pTestCopyExplicit3->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopyExplicit4(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit4->f_GetNumCopies()) == DMibExpr(4));
			DMibTest(DMibExpr(pTestCopyExplicit4->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopyExplicit5(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit5->f_GetNumCopies()) == DMibExpr(5));
			DMibTest(DMibExpr(pTestCopyExplicit5->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopyExplicit6(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit6->f_GetNumCopies()) == DMibExpr(6));
			DMibTest(DMibExpr(pTestCopyExplicit6->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopyExplicit7(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit7->f_GetNumCopies()) == DMibExpr(7));
			DMibTest(DMibExpr(pTestCopyExplicit7->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopyExplicit8(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit8->f_GetNumCopies()) == DMibExpr(8));
			DMibTest(DMibExpr(pTestCopyExplicit8->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopyExplicit9(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit9->f_GetNumCopies()) == DMibExpr(9));
			DMibTest(DMibExpr(pTestCopyExplicit9->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> pTestCopyExplicit10
				(
					fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom)
				)
			;
			DMibTest(DMibExpr(pTestCopyExplicit10->f_GetNumCopies()) == DMibExpr(10));
			DMibTest(DMibExpr(pTestCopyExplicit10->f_GetNumMoves()) == DMibExpr(0));

			// Deep copy
			TCUniquePointer<CTestStruct> pTestDeepCopy(fg_Copy(pTest10));
			DMibTest(DMibExpr(*pTestDeepCopy) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)))(ETestFlag_NoValues);

			// Deep copy assign
			pTestDeepCopy = fg_Copy(pTest10);
			DMibTest(DMibExpr(*pTestDeepCopy) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)) && DMibExpr(2))(ETestFlag_NoValues);

			// Construct assign
			pTest10 = fg_Construct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
			DMibTest(DMibExpr(*pTest10) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)) && DMibExpr(2))(ETestFlag_NoValues);
		}

		void f_TestSharedPointer()
		{
			TCSharedPointer<int> pTestInt(fg_Construct());
			TCSharedPointer<int> pTestInt2(fg_Construct(3));
			DMibTest(DMibExpr(*pTestInt2) == DMibExpr(3))(ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> pTest0(fg_Construct());
			DMibTest(DMibExpr(*pTest0) == DMibExpr(CSmartPtr_Tests::CTestStruct(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> pTest1(fg_Construct(1));
			DMibTest(DMibExpr(*pTest1) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 0, 0, 0, 0, 0, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> pTest2(fg_Construct(1, 2));
			DMibTest(DMibExpr(*pTest2) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 0, 0, 0, 0, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> pTest3(fg_Construct(1, 2, 3));
			DMibTest(DMibExpr(*pTest3) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 0, 0, 0, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> pTest4(fg_Construct(1, 2, 3, 4));
			DMibTest(DMibExpr(*pTest4) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 0, 0, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> pTest5(fg_Construct(1, 2, 3, 4, 5));
			DMibTest(DMibExpr(*pTest5) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 0, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> pTest6(fg_Construct(1, 2, 3, 4, 5, 6));
			DMibTest(DMibExpr(*pTest6) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 0, 0, 0, 0)))(ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> pTest7(fg_Construct(1, 2, 3, 4, 5, 6, 7));
			DMibTest(DMibExpr(*pTest7) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 0, 0, 0)))(ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> pTest8(fg_Construct(1, 2, 3, 4, 5, 6, 7, 8));
			DMibTest(DMibExpr(*pTest8) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 8, 0, 0)))(ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> pTest9(fg_Construct(1, 2, 3, 4, 5, 6, 7, 8, 9));
			DMibTest(DMibExpr(*pTest9) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 8, 9, 0)))(ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> pTest10(fg_Construct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
			DMibTest(DMibExpr(*pTest10) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)))(ETestFlag_NoValues);

			// Construct derived type
			TCSharedPointer<CTestStructVirtual> pTestDerived0(fg_Construct<CTestStruct2>());
			DMibTest(DMibExpr(*pTestDerived0) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual()))(ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> pTestDerived1(fg_Construct<CTestStruct2>(0));
			DMibTest(DMibExpr(*pTestDerived1) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0)))(ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> pTestDerived2(fg_Construct<CTestStruct2>(0, 1));
			DMibTest(DMibExpr(*pTestDerived2) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1)))(ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> pTestDerived3(fg_Construct<CTestStruct2>(0, 1, 2));
			DMibTest(DMibExpr(*pTestDerived3) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2)))(ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> pTestDerived4(fg_Construct<CTestStruct2>(0, 1, 2, 3));
			DMibTest(DMibExpr(*pTestDerived4) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3)))(ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> pTestDerived5(fg_Construct<CTestStruct2>(0, 1, 2, 3, 4));
			DMibTest(DMibExpr(*pTestDerived5) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3, 4)))(ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> pTestDerived6(fg_Construct<CTestStruct2>(0, 1, 2, 3, 4, 5));
			DMibTest(DMibExpr(*pTestDerived6) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3, 4, 5)))(ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> pTestDerived7(fg_Construct<CTestStruct2>(0, 1, 2, 3, 4, 5, 6));
			DMibTest(DMibExpr(*pTestDerived7) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3, 4, 5, 6)))(ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> pTestDerived8(fg_Construct<CTestStruct2>(0, 1, 2, 3, 4, 5, 6, 7));
			DMibTest(DMibExpr(*pTestDerived8) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3, 4, 5, 6, 7)))(ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> pTestDerived9(fg_Construct<CTestStruct2>(0, 1, 2, 3, 4, 5, 6, 7, 8));
			DMibTest(DMibExpr(*pTestDerived9) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3, 4, 5, 6, 7, 8)))(ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> pTestDerived10(fg_Construct<CTestStruct2>(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
			DMibTest(DMibExpr(*pTestDerived10) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)))(ETestFlag_NoValues);

			using CCopyMove = CSmartPtr_Tests::CCopyMove;

			// Moves
			TCSharedPointer<CTestCopyMove> pTestMove0(fg_Construct());
			DMibTest(DMibExpr(pTestMove0->f_GetNumMoves()) == DMibExpr(0));
			DMibTest(DMibExpr(pTestMove0->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMove1(fg_Construct(CCopyMove()));
			DMibTest(DMibExpr(pTestMove1->f_GetNumMoves()) == DMibExpr(1));
			DMibTest(DMibExpr(pTestMove1->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMove2(fg_Construct(CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove2->f_GetNumMoves()) == DMibExpr(2));
			DMibTest(DMibExpr(pTestMove2->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMove3(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove3->f_GetNumMoves()) == DMibExpr(3));
			DMibTest(DMibExpr(pTestMove3->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMove4(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove4->f_GetNumMoves()) == DMibExpr(4));
			DMibTest(DMibExpr(pTestMove4->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMove5(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove5->f_GetNumMoves()) == DMibExpr(5));
			DMibTest(DMibExpr(pTestMove5->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMove6(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove6->f_GetNumMoves()) == DMibExpr(6));
			DMibTest(DMibExpr(pTestMove6->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMove7(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove7->f_GetNumMoves()) == DMibExpr(7));
			DMibTest(DMibExpr(pTestMove7->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMove8(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove8->f_GetNumMoves()) == DMibExpr(8));
			DMibTest(DMibExpr(pTestMove8->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMove9(fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMove9->f_GetNumMoves()) == DMibExpr(9));
			DMibTest(DMibExpr(pTestMove9->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMove10
				(
					fg_Construct(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove())
				)
			;
			DMibTest(DMibExpr(pTestMove10->f_GetNumMoves()) == DMibExpr(10));
			DMibTest(DMibExpr(pTestMove10->f_GetNumCopies()) == DMibExpr(0));

			// Moves explicit
			TCSharedPointer<CTestCopyMove> pTestMoveExplicit0(fg_Construct<CTestCopyMove>());
			DMibTest(DMibExpr(pTestMoveExplicit0->f_GetNumMoves()) == DMibExpr(0));
			DMibTest(DMibExpr(pTestMoveExplicit0->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMoveExplicit1(fg_Construct<CTestCopyMove>(CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit1->f_GetNumMoves()) == DMibExpr(1));
			DMibTest(DMibExpr(pTestMoveExplicit1->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMoveExplicit2(fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit2->f_GetNumMoves()) == DMibExpr(2));
			DMibTest(DMibExpr(pTestMoveExplicit2->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMoveExplicit3(fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit3->f_GetNumMoves()) == DMibExpr(3));
			DMibTest(DMibExpr(pTestMoveExplicit3->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMoveExplicit4(fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit4->f_GetNumMoves()) == DMibExpr(4));
			DMibTest(DMibExpr(pTestMoveExplicit4->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMoveExplicit5(fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit5->f_GetNumMoves()) == DMibExpr(5));
			DMibTest(DMibExpr(pTestMoveExplicit5->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMoveExplicit6(fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit6->f_GetNumMoves()) == DMibExpr(6));
			DMibTest(DMibExpr(pTestMoveExplicit6->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMoveExplicit7(fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove()));
			DMibTest(DMibExpr(pTestMoveExplicit7->f_GetNumMoves()) == DMibExpr(7));
			DMibTest(DMibExpr(pTestMoveExplicit7->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMoveExplicit8
				(
					fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove())
				)
			;
			DMibTest(DMibExpr(pTestMoveExplicit8->f_GetNumMoves()) == DMibExpr(8));
			DMibTest(DMibExpr(pTestMoveExplicit8->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMoveExplicit9
				(
					fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove())
				)
			;
			DMibTest(DMibExpr(pTestMoveExplicit9->f_GetNumMoves()) == DMibExpr(9));
			DMibTest(DMibExpr(pTestMoveExplicit9->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestMoveExplicit10
				(
					fg_Construct<CTestCopyMove>(CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove(), CCopyMove())
				)
			;
			DMibTest(DMibExpr(pTestMoveExplicit10->f_GetNumMoves()) == DMibExpr(10));
			DMibTest(DMibExpr(pTestMoveExplicit10->f_GetNumCopies()) == DMibExpr(0));

			// Copies
			CCopyMove CopyFrom;
			TCSharedPointer<CTestCopyMove> pTestCopy0(fg_Construct());
			DMibTest(DMibExpr(pTestCopy0->f_GetNumCopies()) == DMibExpr(0));
			DMibTest(DMibExpr(pTestCopy0->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopy1(fg_Construct(CopyFrom));
			DMibTest(DMibExpr(pTestCopy1->f_GetNumCopies()) == DMibExpr(1));
			DMibTest(DMibExpr(pTestCopy1->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopy2(fg_Construct(CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy2->f_GetNumCopies()) == DMibExpr(2));
			DMibTest(DMibExpr(pTestCopy2->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopy3(fg_Construct(CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy3->f_GetNumCopies()) == DMibExpr(3));
			DMibTest(DMibExpr(pTestCopy3->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopy4(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy4->f_GetNumCopies()) == DMibExpr(4));
			DMibTest(DMibExpr(pTestCopy4->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopy5(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy5->f_GetNumCopies()) == DMibExpr(5));
			DMibTest(DMibExpr(pTestCopy5->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopy6(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy6->f_GetNumCopies()) == DMibExpr(6));
			DMibTest(DMibExpr(pTestCopy6->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopy7(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy7->f_GetNumCopies()) == DMibExpr(7));
			DMibTest(DMibExpr(pTestCopy7->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopy8(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy8->f_GetNumCopies()) == DMibExpr(8));
			DMibTest(DMibExpr(pTestCopy8->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopy9(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy9->f_GetNumCopies()) == DMibExpr(9));
			DMibTest(DMibExpr(pTestCopy9->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopy10(fg_Construct(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopy10->f_GetNumCopies()) == DMibExpr(10));
			DMibTest(DMibExpr(pTestCopy10->f_GetNumMoves()) == DMibExpr(0));

			// Copies explicit
			TCSharedPointer<CTestCopyMove> pTestCopyExplicit0(fg_Construct<CTestCopyMove>());
			DMibTest(DMibExpr(pTestCopyExplicit0->f_GetNumCopies()) == DMibExpr(0));
			DMibTest(DMibExpr(pTestCopyExplicit0->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopyExplicit1(fg_Construct<CTestCopyMove>(CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit1->f_GetNumCopies()) == DMibExpr(1));
			DMibTest(DMibExpr(pTestCopyExplicit1->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopyExplicit2(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit2->f_GetNumCopies()) == DMibExpr(2));
			DMibTest(DMibExpr(pTestCopyExplicit2->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopyExplicit3(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit3->f_GetNumCopies()) == DMibExpr(3));
			DMibTest(DMibExpr(pTestCopyExplicit3->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopyExplicit4(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit4->f_GetNumCopies()) == DMibExpr(4));
			DMibTest(DMibExpr(pTestCopyExplicit4->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopyExplicit5(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit5->f_GetNumCopies()) == DMibExpr(5));
			DMibTest(DMibExpr(pTestCopyExplicit5->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopyExplicit6(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit6->f_GetNumCopies()) == DMibExpr(6));
			DMibTest(DMibExpr(pTestCopyExplicit6->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopyExplicit7(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit7->f_GetNumCopies()) == DMibExpr(7));
			DMibTest(DMibExpr(pTestCopyExplicit7->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopyExplicit8(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit8->f_GetNumCopies()) == DMibExpr(8));
			DMibTest(DMibExpr(pTestCopyExplicit8->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopyExplicit9(fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom));
			DMibTest(DMibExpr(pTestCopyExplicit9->f_GetNumCopies()) == DMibExpr(9));
			DMibTest(DMibExpr(pTestCopyExplicit9->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> pTestCopyExplicit10
				(
					fg_Construct<CTestCopyMove>(CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom, CopyFrom)
				)
			;
			DMibTest(DMibExpr(pTestCopyExplicit10->f_GetNumCopies()) == DMibExpr(10));
			DMibTest(DMibExpr(pTestCopyExplicit10->f_GetNumMoves()) == DMibExpr(0));

			// Deep copy
			{
				TCSharedPointer<CTestStruct> pTestDeepCopy(fg_Copy(pTest10));
				DMibTest(DMibExpr(*pTestDeepCopy) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)))(ETestFlag_NoValues);

				// Deep copy assign
				pTestDeepCopy = fg_Copy(pTest10);
				DMibTest(DMibExpr(*pTestDeepCopy) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)) && DMibExpr(2))(ETestFlag_NoValues);
			}

			// Construct assign
			pTest10 = fg_Construct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
			DMibTest(DMibExpr(*pTest10) == DMibExpr(CSmartPtr_Tests::CTestStruct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)) && DMibExpr(2))(ETestFlag_NoValues);
		}

		void f_TestSharedPointerConstness()
		{
			struct CValue
			{
				int32 m_Value = 0;
			};

			DMibTestPath("Const pointee does not convert to mutable");

			static_assert(!NTraits::cIsConvertible<TCSharedPointer<CValue const>, TCSharedPointer<CValue>>);
			static_assert(!NTraits::cIsConstructibleWith<TCSharedPointer<CValue>, TCSharedPointer<CValue const>>);
			static_assert(!NTraits::cIsConstructibleWith<TCSharedPointer<CValue>, TCSharedPointer<CValue const> &&>);
			static_assert(!NTraits::cIsAssignableWith<TCSharedPointer<CValue> &, TCSharedPointer<CValue const>>);

			static_assert(!NTraits::cIsConvertible<TCSharedPointer<CValue>, TCSharedPointer<CValue const>>);
			static_assert(!NTraits::cIsConstructibleWith<TCSharedPointer<CValue const>, TCSharedPointer<CValue>>);
			static_assert(!NTraits::cIsAssignableWith<TCSharedPointer<CValue const> &, TCSharedPointer<CValue>>);

			// A unique-pointer move consumes the mutable handle, so adding const can remain implicit.
			static_assert(NTraits::cIsConstructibleWith<TCUniquePointer<CValue const>, TCUniquePointer<CValue> &&>);
			static_assert(!NTraits::cIsConstructibleWith<TCUniquePointer<CValue>, TCUniquePointer<CValue const> &&>);

			TCSharedPointer<CValue> pMutable = fg_Construct();
			pMutable->m_Value = 7;

			TCSharedPointer<CValue const> pConst = pMutable.f_ShareAsConst();
			DMibExpect(pConst->m_Value, ==, 7);
			DMibExpect(pConst.f_Get(), ==, pMutable.f_Get());

			constexpr bool c_bConstStrips = NTraits::cIsConvertible<TCSharedPointer<CValue const>, TCSharedPointer<CValue>>;
			DMibExpectFalse(c_bConstStrips);

			constexpr bool c_bConstAddsImplicitly = NTraits::cIsConvertible<TCSharedPointer<CValue>, TCSharedPointer<CValue const>>;
			DMibExpectFalse(c_bConstAddsImplicitly);

			using CWeak = TCWeakPointer<CValue, CAllocator_Heap>;
			using CWeakConst = TCWeakPointer<CValue const, CAllocator_Heap>;

			static_assert(!NTraits::cIsConvertible<CWeak, CWeakConst>);
			static_assert(!NTraits::cIsConvertible<CWeakConst, CWeak>);

			TCSharedPointer<CValue, CSupportWeakTag> pWeakable = fg_Construct();
			pWeakable->m_Value = 11;

			TCWeakPointer<CValue, CAllocator_Heap> pWeakMutable = pWeakable;
			auto pWeakFrozen = pWeakMutable.f_ShareAsConst();

			auto pLocked = pWeakFrozen.f_Lock();
			DMibExpectTrue(bool(pLocked));
			DMibExpect(pLocked->m_Value, ==, 11);
		}

		void f_TestSharedPointerInheritance()
		{
			static constexpr bool c_bReportMemory = false;

			using namespace NStr;

			struct CBaseNonVirtual
			{
				umint m_Value0 = 0;
			};

			struct CBase
			{
				virtual ~CBase()
				{
					//DMibTraceSafe("~CBase\n");
				}

				virtual umint f_GetValue()
				{
					return m_Value0;
				}

				umint m_Value0 = 0;
				//NStr::CStr m_StrValue = "Base";
			};

			struct CDerived : public CBase
			{
				~CDerived()
				{
					//DMibTraceSafe("~CDerived\n");
				}

				umint f_GetValue() override
				{
					return m_Value0;
				}

				umint m_Value0 = 1;
				//NStr::CStr m_StrValue = "Derived";
			};

			struct CDerivedVirtual : public virtual CBase
			{
				~CDerivedVirtual()
				{
					//DMibTraceSafe("~CDerived\n");
				}

				umint f_GetValue() override
				{
					return m_Value0;
				}

				umint m_Value0 = 1;
				//NStr::CStr m_StrValue = "Derived";
			};

			struct CDerived2Virtual : public virtual CBase
			{
				~CDerived2Virtual()
				{
					//DMibTraceSafe("~CDerived2\n");
				}

				umint f_GetValue() override
				{
					return m_Value0;
				}

				umint m_Value0 = 2;
				//NStr::CStr m_StrValue = "Derived2";
			};

			struct alignas(32) CAligned32DiamondDerivedVirtual : public CDerivedVirtual, CDerived2Virtual
			{
				~CAligned32DiamondDerivedVirtual()
				{
					//DMibTraceSafe("~CDerived3\n");
				}

				umint f_GetValue() override
				{
					return m_Value0;
				}

				umint m_Value0 = 3;
				//NStr::CStr m_StrValue = "Derived3";
			};

			struct CBaseIntrusive
			{
				virtual ~CBaseIntrusive()
				{
					//DMibTraceSafe("~CBase\n");
				}

				virtual umint f_GetValue()
				{
					return m_Value0;
				}

				NStorage::CIntrusiveRefCount m_RefCount;
				umint m_Value0 = 0;
				//NStr::CStr m_StrValue = "Base";
			};

			struct CBaseIntrusiveSupportWeak
			{
				virtual ~CBaseIntrusiveSupportWeak()
				{
					//DMibTraceSafe("~CBase\n");
				}

				virtual umint f_GetValue()
				{
					return m_Value0;
				}

				CIntrusiveRefCountWithWeak m_RefCount;
				umint m_Value0 = 0;
				//NStr::CStr m_StrValue = "Base";
			};

			struct CDerivedIntrusive : public CBaseIntrusive
			{
				~CDerivedIntrusive()
				{
					//DMibTraceSafe("~CDerived\n");
				}

				umint f_GetValue() override
				{
					return m_Value0;
				}

				umint m_Value0 = 1;
				//NStr::CStr m_StrValue = "Derived";
			};

			struct CDerivedIntrusiveSupportWeak : public CBaseIntrusiveSupportWeak
			{
				~CDerivedIntrusiveSupportWeak()
				{
					//DMibTraceSafe("~CDerived\n");
				}

				umint f_GetValue() override
				{
					return m_Value0;
				}

				umint m_Value0 = 1;
				//NStr::CStr m_StrValue = "Derived";
			};

			struct CDerivedVirtualIntrusive : public virtual CBaseIntrusive
			{
				~CDerivedVirtualIntrusive()
				{
					//DMibTraceSafe("~CDerived\n");
				}

				umint f_GetValue() override
				{
					return m_Value0;
				}

				umint m_Value0 = 1;
				//NStr::CStr m_StrValue = "Derived";
			};

			struct CDerived2VirtualIntrusive : public virtual CBaseIntrusive
			{
				~CDerived2VirtualIntrusive()
				{
					//DMibTraceSafe("~CDerived2\n");
				}

				umint f_GetValue() override
				{
					return m_Value0;
				}

				umint m_Value0 = 2;
				//NStr::CStr m_StrValue = "Derived2";
			};

			struct alignas(32) CAligned32DiamondDerivedVirtualIntrusive : public CDerivedVirtualIntrusive, CDerived2VirtualIntrusive
			{
				~CAligned32DiamondDerivedVirtualIntrusive()
				{
					//DMibTraceSafe("~CDerived3\n");
				}

				umint f_GetValue() override
				{
					return m_Value0;
				}

				umint m_Value0 = 3;
				//NStr::CStr m_StrValue = "Derived3";
			};

			struct CDerivedVirtualIntrusiveSupportWeak : public virtual CBaseIntrusiveSupportWeak
			{
				~CDerivedVirtualIntrusiveSupportWeak()
				{
					//DMibTraceSafe("~CDerived\n");
				}

				umint f_GetValue() override
				{
					return m_Value0;
				}

				umint m_Value0 = 1;
				//NStr::CStr m_StrValue = "Derived";
			};

			struct CDerived2VirtualIntrusiveSupportWeak : public virtual CBaseIntrusiveSupportWeak
			{
				~CDerived2VirtualIntrusiveSupportWeak()
				{
					//DMibTraceSafe("~CDerived2\n");
				}

				umint f_GetValue() override
				{
					return m_Value0;
				}

				umint m_Value0 = 2;
				//NStr::CStr m_StrValue = "Derived2";
			};

			struct alignas(32) CAligned32DiamondDerivedVirtualIntrusiveSupportWeak : public CDerivedVirtualIntrusiveSupportWeak, CDerived2VirtualIntrusiveSupportWeak
			{
				~CAligned32DiamondDerivedVirtualIntrusiveSupportWeak()
				{
					//DMibTraceSafe("~CDerived3\n");
				}

				umint f_GetValue() override
				{
					return m_Value0;
				}

				umint m_Value0 = 3;
				//NStr::CStr m_StrValue = "Derived3";
			};

			struct CReportScope : public CReportMemory
			{
				CReportScope(CFStr256 const &_Description, umint _Size)
					: m_Description(_Description)
					, m_Size(_Size)
				{
#if DMibConfig_Memory_Shims_Enable
					if constexpr (c_bReportMemory)
						m_pScope = fg_Construct(*this);
#endif
				}

				~CReportScope()
				{
					if constexpr (c_bReportMemory)
						DMibTraceSafe("{}   Total {sj3}   ({sj2} + Allocs {})\n", m_Description, m_Size + m_Allocated, m_Size, m_Allocations);
				}

				virtual void f_Alloc
					(
						umint _MemoryAllocator
						, umint _AllocatorDepth
						, ch8 const *_pAllocatorName
						, umint _Address
						, umint _RequestedAlignment
						, umint _RequestedSize
						, umint _ReturnedSize
						, fp32 _nBytesOverhead
						, void *_pAllocationInfo
					)
					override
				{
					if (NStr::fg_StrCmp(_pAllocatorName, "Main memory manager") != 0)
						return;

					if (m_Allocations.f_IsEmpty())
						m_Allocations = CFStr256::CFormat("{}") << _RequestedSize;
					else
						m_Allocations += CFStr256::CFormat(" + {}") << _RequestedSize;

					m_Allocated += _RequestedSize;
				}

				virtual void f_Resize
					(
						umint _MemoryAllocator
						, umint _AllocatorDepth
						, ch8 const *_pAllocatorName
						, umint _OldAddress
						, umint _OldSize
						, void const *_pOldAllocationInfo
						, umint _Address
						, umint _RequestedAlignment
						, umint _RequestedSize
						, umint _ReturnedSize
						, fp32 _nBytesOverhead
						, void *_pAllocationInfo
					)
					override
				{
				}

				virtual void f_Realloc
					(
						umint _MemoryAllocator
						, umint _AllocatorDepth
						, ch8 const *_pAllocatorName
						, umint _OldAddress
						, umint _OldSize
						, void const *_pOldAllocationInfo
						, umint _Address
						, umint _RequestedAlignment
						, umint _RequestedSize
						, umint _ReturnedSize
						, fp32 _nBytesOverhead
						, void *_pAllocationInfo
					)
					override
				{
				}

				virtual void f_Free(umint _MemoryAllocator, ch8 const *_pAllocatorName, umint _AllocatorDepth, umint _Address, umint _Size, void const *_pAllocationInfo) override
				{
				}

				virtual void f_GetSize(umint _MemoryAllocator, ch8 const *_pAllocatorName, umint _AllocatorDepth, umint _Address, umint _Size, void const *_pAllocationInfo) override
				{
				}

				virtual void f_Protect(umint _MemoryAllocator, ch8 const *_pAllocatorName, umint _AllocatorDepth, umint _Address, umint _Size, uaint _Protect) override
				{
				}

				virtual void f_Commit(umint _MemoryAllocator, ch8 const *_pAllocatorName, umint _AllocatorDepth, umint _Address, umint _Size) override
				{
				}

				virtual void f_Decommit(umint _MemoryAllocator, ch8 const *_pAllocatorName, umint _AllocatorDepth, umint _Address, umint _Size) override
				{
				}

				virtual void f_AllocatorDelete(umint _MemoryAllocator, ch8 const *_pAllocatorName, umint _AllocatorDepth) override
				{
				}

				CFStr256 m_Description;
				CFStr256 m_Allocations;
				umint m_Size = 0;
				umint m_Allocated = 0;
#if DMibConfig_Memory_Shims_Enable
				TCUniquePointer<CMemoryReportScope> m_pScope;
#endif
			};

			{
				DMibTestPath("BaseNonVirtual");
				{
					CReportScope ReportScope("TCUniquePointer            CBaseNonVirtual                                    ", sizeof(TCUniquePointer<CBaseNonVirtual>));
					TCUniquePointer<CBaseNonVirtual> pMalterlibUniquePointer(fg_Construct<CBaseNonVirtual>());
				}
				{
					CReportScope ReportScope("unique_ptr                 CBaseNonVirtual                                    ", sizeof(std::unique_ptr<CBaseNonVirtual>));
					std::unique_ptr<CBaseNonVirtual> pUniquePointer(std::make_unique<CBaseNonVirtual>());
				}
				{
					CReportScope ReportScope("TCSharedPointer            CBaseNonVirtual                                    ", sizeof(TCSharedPointer<CBaseNonVirtual>));
					TCSharedPointer<CBaseNonVirtual> pMalterlibSharedPointer(fg_Construct<CBaseNonVirtual>());
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CBaseNonVirtual                                    ", sizeof(TCSharedPointerSupportWeak<CBaseNonVirtual>));
					TCSharedPointerSupportWeak<CBaseNonVirtual> pMalterlibSharedPointerSupportWeak(fg_Construct<CBaseNonVirtual>());
				}
				{
					CReportScope ReportScope("make_shared                CBaseNonVirtual                                    ", sizeof(std::shared_ptr<CBaseNonVirtual>));
					std::shared_ptr<CBase> pMakeShared(std::make_shared<CBase>());
				}
				{
					CReportScope ReportScope("shared_ptr                 CBaseNonVirtual                                    ", sizeof(std::shared_ptr<CBaseNonVirtual>));
					std::shared_ptr<CBase> pSharedPointer(new CBase());
				}
			}
			if constexpr (c_bReportMemory)
				DMibTraceSafe("\n");

			{
				DMibTestPath("Base");
				{
					CReportScope ReportScope("TCUniquePointer            CBase                                              ", sizeof(TCUniquePointer<CBase>));
					TCUniquePointer<CBase> pMalterlibUniquePointer(fg_Construct<CBase>());

					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibUniquePointer->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("unique_ptr                 CBase                                              ", sizeof(std::unique_ptr<CBase>));
					std::unique_ptr<CBase> pUniquePointer(std::make_unique<CBase>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pUniquePointer->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CBaseIntrusive                                     ", sizeof(TCSharedPointer<CBaseIntrusive>));
					TCSharedPointer<CBaseIntrusive> pMalterlibSharedPointerIntrusive(fg_Construct<CBaseIntrusive>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusive->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CBaseIntrusiveSupportWeak                          ", sizeof(TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak>));
					TCSharedPointer<CBaseIntrusiveSupportWeak> pMalterlibSharedPointerIntrusiveSupportWeak(fg_Construct<CBaseIntrusiveSupportWeak>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusiveSupportWeak->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CBase                                              ", sizeof(TCSharedPointer<CBase>));
					TCSharedPointer<CBase> pMalterlibSharedPointer(fg_Construct<CBase>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointer->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CBase                                              ", sizeof(TCSharedPointerSupportWeak<CBase>));
					TCSharedPointerSupportWeak<CBase> pMalterlibSharedPointerSupportWeak(fg_Construct<CBase>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointerSupportWeak->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("make_shared                CBase                                              ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pMakeShared(std::make_shared<CBase>());

					if constexpr (!c_bReportMemory)
						DMibExpect(pMakeShared->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("shared_ptr                 CBase                                              ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pSharedPointer(new CBase());

					if constexpr (!c_bReportMemory)
						DMibExpect(pSharedPointer->f_GetValue(), ==, 0);
				}
			}
			if constexpr (c_bReportMemory)
				DMibTraceSafe("\n");

			{
				DMibTestPath("Derived");
				{
					CReportScope ReportScope("TCUniquePointer            CDerived                                           ", sizeof(TCUniquePointer<CBase>));
					TCUniquePointer<CBase> pMalterlibUniquePointer(fg_Construct<CDerived>());

					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibUniquePointer->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("unique_ptr                 CDerived                                           ", sizeof(std::unique_ptr<CBase>));
					std::unique_ptr<CBase> pUniquePointer(std::make_unique<CDerived>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pUniquePointer->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CDerivedIntrusive                                  ", sizeof(TCSharedPointer<CBaseIntrusive>));
					TCSharedPointer<CBaseIntrusive> pMalterlibSharedPointerIntrusive(fg_Construct<CDerivedIntrusive>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusive->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CDerivedIntrusiveSupportWeak                       ", sizeof(TCSharedPointer<CBaseIntrusiveSupportWeak>));
					TCSharedPointer<CBaseIntrusiveSupportWeak> pMalterlibSharedPointerIntrusiveSupportWeak(fg_Construct<CDerivedIntrusiveSupportWeak>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusiveSupportWeak->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CDerived                                           ", sizeof(TCSharedPointer<CBase>));
					TCSharedPointer<CBase> pMalterlibSharedPointer(fg_Construct<CDerived>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointer->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CDerived                                           ", sizeof(TCSharedPointerSupportWeak<CBase>));
					TCSharedPointerSupportWeak<CBase> pMalterlibSharedPointerSupportWeak(fg_Construct<CDerived>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointerSupportWeak->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("make_shared                CDerived                                           ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pMakeShared(std::make_shared<CDerived>());

					if constexpr (!c_bReportMemory)
						DMibExpect(pMakeShared->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("shared_ptr                 CDerived                                           ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pSharedPointer(new CDerived());

					if constexpr (!c_bReportMemory)
						DMibExpect(pSharedPointer->f_GetValue(), ==, 1);
				}
			}

			if constexpr (c_bReportMemory)
				DMibTraceSafe("\n");

			{
				DMibTestPath("DerivedVirtual");
				{
					CReportScope ReportScope("TCUniquePointer            CDerivedVirtual                                    ", sizeof(TCUniquePointer<CBase>));
					TCUniquePointer<CBase> pMalterlibUniquePointer(fg_Construct<CDerivedVirtual>());

					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibUniquePointer->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("unique_ptr                 CDerivedVirtual                                    ", sizeof(std::unique_ptr<CBase>));
					std::unique_ptr<CBase> pUniquePointer(std::make_unique<CDerivedVirtual>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pUniquePointer->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CDerivedVirtualIntrusive                           ", sizeof(TCSharedPointer<CBaseIntrusive>));
					TCSharedPointer<CBaseIntrusive> pMalterlibSharedPointerIntrusive(fg_Construct<CDerivedVirtualIntrusive>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusive->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CDerivedVirtualIntrusiveSupportWeak                ", sizeof(TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak>));
					TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak> pMalterlibSharedPointerSupportWeak(fg_Construct<CDerivedVirtualIntrusiveSupportWeak>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointerSupportWeak->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("make_shared                CDerivedVirtual                                    ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pMakeShared(std::make_shared<CDerivedVirtual>());

					if constexpr (!c_bReportMemory)
						DMibExpect(pMakeShared->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("shared_ptr                 CDerivedVirtual                                    ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pSharedPointer(new CDerivedVirtual());

					if constexpr (!c_bReportMemory)
						DMibExpect(pSharedPointer->f_GetValue(), ==, 1);
				}
			}
			if constexpr (c_bReportMemory)
				DMibTraceSafe("\n");

			{
				DMibTestPath("Derived2Virtual");
				{
					CReportScope ReportScope("TCUniquePointer            CDerived2Virtual                                   ", sizeof(TCUniquePointer<CBase>));
					TCUniquePointer<CBase> pMalterlibUniquePointer(fg_Construct<CDerived2Virtual>());

					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibUniquePointer->f_GetValue(), ==, 2);
				}
				{
					CReportScope ReportScope("unique_ptr                 CDerived2Virtual                                   ", sizeof(std::unique_ptr<CBase>));
					std::unique_ptr<CBase> pUniquePointer(std::make_unique<CDerived2Virtual>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pUniquePointer->f_GetValue(), ==, 2);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CDerived2VirtualIntrusive                          ", sizeof(TCSharedPointer<CBaseIntrusive>));
					TCSharedPointer<CBaseIntrusive> pMalterlibSharedPointerIntrusive(fg_Construct<CDerived2VirtualIntrusive>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusive->f_GetValue(), ==, 2);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CDerived2VirtualIntrusiveSupportWeak               ", sizeof(TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak>));
					TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak> pMalterlibSharedPointerSupportWeak(fg_Construct<CDerived2VirtualIntrusiveSupportWeak>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointerSupportWeak->f_GetValue(), ==, 2);
				}
				{
					CReportScope ReportScope("make_shared                CDerived2Virtual                                   ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pMakeShared(new CDerived2Virtual());

					if constexpr (!c_bReportMemory)
						DMibExpect(pMakeShared->f_GetValue(), ==, 2);
				}
				{
					CReportScope ReportScope("shared_ptr                 CDerived2Virtual                                   ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pSharedPointer(std::make_shared<CDerived2Virtual>());

					if constexpr (!c_bReportMemory)
						DMibExpect(pSharedPointer->f_GetValue(), ==, 2);
				}
			}
			if constexpr (c_bReportMemory)
				DMibTraceSafe("\n");

			{
				DMibTestPath("Derived3Virtual");
				{
					CReportScope ReportScope("TCUniquePointer            CAligned32DiamondDerivedVirtual                    ", sizeof(TCUniquePointer<CBase>));
					TCUniquePointer<CBase> pMalterlibUniquePointer(fg_Construct<CAligned32DiamondDerivedVirtual>());

					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibUniquePointer->f_GetValue(), ==, 3);
				}
				{
					CReportScope ReportScope("unique_ptr                 CAligned32DiamondDerivedVirtual                    ", sizeof(std::unique_ptr<CBase>));
					std::unique_ptr<CBase> pUniquePointer(std::make_unique<CAligned32DiamondDerivedVirtual>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pUniquePointer->f_GetValue(), ==, 3);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CAligned32DiamondDerivedVirtualIntrusive           ", sizeof(TCSharedPointer<CBaseIntrusive>));
					TCSharedPointer<CBaseIntrusive> pMalterlibSharedPointerIntrusive(fg_Construct<CAligned32DiamondDerivedVirtualIntrusive>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusive->f_GetValue(), ==, 3);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CAligned32DiamondDerivedVirtualIntrusiveSupportWeak", sizeof(TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak>));
					TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak> pMalterlibSharedPointerSupportWeak(fg_Construct<CAligned32DiamondDerivedVirtualIntrusiveSupportWeak>());
					if constexpr (!c_bReportMemory)
						DMibExpect(pMalterlibSharedPointerSupportWeak->f_GetValue(), ==, 3);
				}
				{
					CReportScope ReportScope("make_shared                CAligned32DiamondDerivedVirtual                    ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pMakeShared(std::make_shared<CAligned32DiamondDerivedVirtual>());

					if constexpr (!c_bReportMemory)
						DMibExpect(pMakeShared->f_GetValue(), ==, 3);
				}
				{
					CReportScope ReportScope("shared_ptr                 CAligned32DiamondDerivedVirtual                    ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pSharedPointer(new CAligned32DiamondDerivedVirtual());

					if constexpr (!c_bReportMemory)
						DMibExpect(pSharedPointer->f_GetValue(), ==, 3);
				}
			}
		}

		void f_DoTests()
		{
			DMibTestSuite("Unique Pointer")
			{
				f_TestUniquePointer();
			};
			DMibTestSuite("Shared Pointer")
			{
				f_TestSharedPointer();
			};
			DMibTestSuite("Shared Pointer Inheritance")
			{
				f_TestSharedPointerInheritance();
			};
			DMibTestSuite("Shared Pointer Constness")
			{
				f_TestSharedPointerConstness();
			};
		}
	};

	DMibTestRegister(CSmartPtr_Tests, Malterlib::Storage);
}
