// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <memory>

using namespace NMib::NCryptography;
using namespace NMib;
using namespace NMib::NMemory;
using namespace NMib::NStream;
using namespace NMib::NContainer;
using namespace NMib::NStorage;

namespace
{
	class CSmartPtr_Tests : public NMib::NTest::CTest
	{
	public:

		struct CTestStruct
		{
			int m_0; int m_1; int m_2; int m_3; int m_4; int m_5; int m_6; int m_7; int m_8; int m_9;

			CTestStruct(int _0, int _1, int _2, int _3, int _4, int _5, int _6, int _7, int _8, int _9)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(_4), m_5(_5), m_6(_6), m_7(_7), m_8(_8), m_9(_9)
			{
			}
			CTestStruct(int _0, int _1, int _2, int _3, int _4, int _5, int _6, int _7, int _8)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(_4), m_5(_5), m_6(_6), m_7(_7), m_8(_8), m_9(0)
			{
			}
			CTestStruct(int _0, int _1, int _2, int _3, int _4, int _5, int _6, int _7)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(_4), m_5(_5), m_6(_6), m_7(_7), m_8(0), m_9(0)
			{
			}
			CTestStruct(int _0, int _1, int _2, int _3, int _4, int _5, int _6)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(_4), m_5(_5), m_6(_6), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStruct(int _0, int _1, int _2, int _3, int _4, int _5)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(_4), m_5(_5), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStruct(int _0, int _1, int _2, int _3, int _4)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(_4), m_5(0), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStruct(int _0, int _1, int _2, int _3)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(0), m_5(0), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStruct(int _0, int _1, int _2)
				: m_0(_0), m_1(_1), m_2(_2), m_3(0), m_4(0), m_5(0), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStruct(int _0, int _1)
				: m_0(_0), m_1(_1), m_2(0), m_3(0), m_4(0), m_5(0), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStruct(int _0)
				: m_0(_0), m_1(0), m_2(0), m_3(0), m_4(0), m_5(0), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStruct()
				: m_0(0), m_1(0), m_2(0), m_3(0), m_4(0), m_5(0), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}


			bool operator == (CTestStruct const &_Other) const
			{
				return m_0 == _Other.m_0
					&& m_1 == _Other.m_1
					&& m_2 == _Other.m_2
					&& m_3 == _Other.m_3
					&& m_4 == _Other.m_4
					&& m_5 == _Other.m_5
					&& m_6 == _Other.m_6
					&& m_7 == _Other.m_7
					&& m_8 == _Other.m_8
					&& m_9 == _Other.m_9;
			}
		};

		struct CTestStructVirtual
		{
			int m_0; int m_1; int m_2; int m_3; int m_4; int m_5; int m_6; int m_7; int m_8; int m_9;

			CTestStructVirtual(int _0, int _1, int _2, int _3, int _4, int _5, int _6, int _7, int _8, int _9)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(_4), m_5(_5), m_6(_6), m_7(_7), m_8(_8), m_9(_9)
			{
			}
			CTestStructVirtual(int _0, int _1, int _2, int _3, int _4, int _5, int _6, int _7, int _8)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(_4), m_5(_5), m_6(_6), m_7(_7), m_8(_8), m_9(0)
			{
			}
			CTestStructVirtual(int _0, int _1, int _2, int _3, int _4, int _5, int _6, int _7)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(_4), m_5(_5), m_6(_6), m_7(_7), m_8(0), m_9(0)
			{
			}
			CTestStructVirtual(int _0, int _1, int _2, int _3, int _4, int _5, int _6)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(_4), m_5(_5), m_6(_6), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStructVirtual(int _0, int _1, int _2, int _3, int _4, int _5)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(_4), m_5(_5), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStructVirtual(int _0, int _1, int _2, int _3, int _4)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(_4), m_5(0), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStructVirtual(int _0, int _1, int _2, int _3)
				: m_0(_0), m_1(_1), m_2(_2), m_3(_3), m_4(0), m_5(0), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStructVirtual(int _0, int _1, int _2)
				: m_0(_0), m_1(_1), m_2(_2), m_3(0), m_4(0), m_5(0), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStructVirtual(int _0, int _1)
				: m_0(_0), m_1(_1), m_2(0), m_3(0), m_4(0), m_5(0), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStructVirtual(int _0)
				: m_0(_0), m_1(0), m_2(0), m_3(0), m_4(0), m_5(0), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}
			CTestStructVirtual()
				: m_0(0), m_1(0), m_2(0), m_3(0), m_4(0), m_5(0), m_6(0), m_7(0), m_8(0), m_9(0)
			{
			}

			virtual ~CTestStructVirtual()
			{
			}


			bool operator == (CTestStructVirtual const &_Other) const
			{
				return m_0 == _Other.m_0
					&& m_1 == _Other.m_1
					&& m_2 == _Other.m_2
					&& m_3 == _Other.m_3
					&& m_4 == _Other.m_4
					&& m_5 == _Other.m_5
					&& m_6 == _Other.m_6
					&& m_7 == _Other.m_7
					&& m_8 == _Other.m_8
					&& m_9 == _Other.m_9;
			}
		};


		struct CTestStruct2 : public CTestStructVirtual
		{
			CTestStruct2()
				: CTestStructVirtual()
			{
			}
			CTestStruct2(int _0)
				: CTestStructVirtual(_0)
			{
			}
			CTestStruct2(int _0, int _1)
				: CTestStructVirtual(_0, _1)
			{
			}
			CTestStruct2(int _0, int _1, int _2)
				: CTestStructVirtual(_0, _1, _2)
			{
			}
			CTestStruct2(int _0, int _1, int _2, int _3)
				: CTestStructVirtual(_0, _1, _2, _3)
			{
			}
			CTestStruct2(int _0, int _1, int _2, int _3, int _4)
				: CTestStructVirtual(_0, _1, _2, _3, _4)
			{
			}
			CTestStruct2(int _0, int _1, int _2, int _3, int _4, int _5)
				: CTestStructVirtual(_0, _1, _2, _3, _4, _5)
			{
			}
			CTestStruct2(int _0, int _1, int _2, int _3, int _4, int _5, int _6)
				: CTestStructVirtual(_0, _1, _2, _3, _4, _5, _6)
			{
			}
			CTestStruct2(int _0, int _1, int _2, int _3, int _4, int _5, int _6, int _7)
				: CTestStructVirtual(_0, _1, _2, _3, _4, _5, _6, _7)
			{
			}
			CTestStruct2(int _0, int _1, int _2, int _3, int _4, int _5, int _6, int _7, int _8)
				: CTestStructVirtual(_0, _1, _2, _3, _4, _5, _6, _7, _8)
			{
			}
			CTestStruct2(int _0, int _1, int _2, int _3, int _4, int _5, int _6, int _7, int _8, int _9)
				: CTestStructVirtual(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9)
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
				m_nMoves += _Other.m_nMoves ;
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
				return m_CopyMove0.m_nMoves + m_CopyMove1.m_nMoves + m_CopyMove2.m_nMoves + m_CopyMove3.m_nMoves + m_CopyMove4.m_nMoves + m_CopyMove5.m_nMoves + m_CopyMove6.m_nMoves + m_CopyMove7.m_nMoves + m_CopyMove8.m_nMoves + m_CopyMove9.m_nMoves;
			}
			int f_GetNumCopies() const
			{
				return m_CopyMove0.m_nCopies + m_CopyMove1.m_nCopies + m_CopyMove2.m_nCopies + m_CopyMove3.m_nCopies + m_CopyMove4.m_nCopies + m_CopyMove5.m_nCopies + m_CopyMove6.m_nCopies + m_CopyMove7.m_nCopies + m_CopyMove8.m_nCopies + m_CopyMove9.m_nCopies;
			}

			CTestCopyMove()
			{
			}
			CTestCopyMove(CCopyMove &&_0)
				: m_CopyMove0(NMib::fg_Move(_0))
			{
			}
			CTestCopyMove(CCopyMove &&_0, CCopyMove &&_1)
				: m_CopyMove0(NMib::fg_Move(_0))
				, m_CopyMove1(NMib::fg_Move(_1))
			{
			}
			CTestCopyMove(CCopyMove &&_0, CCopyMove &&_1, CCopyMove &&_2)
				: m_CopyMove0(NMib::fg_Move(_0))
				, m_CopyMove1(NMib::fg_Move(_1))
				, m_CopyMove2(NMib::fg_Move(_2))
			{
			}
			CTestCopyMove(CCopyMove &&_0, CCopyMove &&_1, CCopyMove &&_2, CCopyMove &&_3)
				: m_CopyMove0(NMib::fg_Move(_0))
				, m_CopyMove1(NMib::fg_Move(_1))
				, m_CopyMove2(NMib::fg_Move(_2))
				, m_CopyMove3(NMib::fg_Move(_3))
			{
			}
			CTestCopyMove(CCopyMove &&_0, CCopyMove &&_1, CCopyMove &&_2, CCopyMove &&_3, CCopyMove &&_4)
				: m_CopyMove0(NMib::fg_Move(_0))
				, m_CopyMove1(NMib::fg_Move(_1))
				, m_CopyMove2(NMib::fg_Move(_2))
				, m_CopyMove3(NMib::fg_Move(_3))
				, m_CopyMove4(NMib::fg_Move(_4))
			{
			}
			CTestCopyMove(CCopyMove &&_0, CCopyMove &&_1, CCopyMove &&_2, CCopyMove &&_3, CCopyMove &&_4, CCopyMove &&_5)
				: m_CopyMove0(NMib::fg_Move(_0))
				, m_CopyMove1(NMib::fg_Move(_1))
				, m_CopyMove2(NMib::fg_Move(_2))
				, m_CopyMove3(NMib::fg_Move(_3))
				, m_CopyMove4(NMib::fg_Move(_4))
				, m_CopyMove5(NMib::fg_Move(_5))
			{
			}
			CTestCopyMove(CCopyMove &&_0, CCopyMove &&_1, CCopyMove &&_2, CCopyMove &&_3, CCopyMove &&_4, CCopyMove &&_5, CCopyMove &&_6)
				: m_CopyMove0(NMib::fg_Move(_0))
				, m_CopyMove1(NMib::fg_Move(_1))
				, m_CopyMove2(NMib::fg_Move(_2))
				, m_CopyMove3(NMib::fg_Move(_3))
				, m_CopyMove4(NMib::fg_Move(_4))
				, m_CopyMove5(NMib::fg_Move(_5))
				, m_CopyMove6(NMib::fg_Move(_6))
			{
			}
			CTestCopyMove(CCopyMove &&_0, CCopyMove &&_1, CCopyMove &&_2, CCopyMove &&_3, CCopyMove &&_4, CCopyMove &&_5, CCopyMove &&_6, CCopyMove &&_7)
				: m_CopyMove0(NMib::fg_Move(_0))
				, m_CopyMove1(NMib::fg_Move(_1))
				, m_CopyMove2(NMib::fg_Move(_2))
				, m_CopyMove3(NMib::fg_Move(_3))
				, m_CopyMove4(NMib::fg_Move(_4))
				, m_CopyMove5(NMib::fg_Move(_5))
				, m_CopyMove6(NMib::fg_Move(_6))
				, m_CopyMove7(NMib::fg_Move(_7))
			{
			}
			CTestCopyMove(CCopyMove &&_0, CCopyMove &&_1, CCopyMove &&_2, CCopyMove &&_3, CCopyMove &&_4, CCopyMove &&_5, CCopyMove &&_6, CCopyMove &&_7, CCopyMove &&_8)
				: m_CopyMove0(NMib::fg_Move(_0))
				, m_CopyMove1(NMib::fg_Move(_1))
				, m_CopyMove2(NMib::fg_Move(_2))
				, m_CopyMove3(NMib::fg_Move(_3))
				, m_CopyMove4(NMib::fg_Move(_4))
				, m_CopyMove5(NMib::fg_Move(_5))
				, m_CopyMove6(NMib::fg_Move(_6))
				, m_CopyMove7(NMib::fg_Move(_7))
				, m_CopyMove8(NMib::fg_Move(_8))
			{
			}
			CTestCopyMove(CCopyMove &&_0, CCopyMove &&_1, CCopyMove &&_2, CCopyMove &&_3, CCopyMove &&_4, CCopyMove &&_5, CCopyMove &&_6, CCopyMove &&_7, CCopyMove &&_8, CCopyMove &&_9)
				: m_CopyMove0(NMib::fg_Move(_0))
				, m_CopyMove1(NMib::fg_Move(_1))
				, m_CopyMove2(NMib::fg_Move(_2))
				, m_CopyMove3(NMib::fg_Move(_3))
				, m_CopyMove4(NMib::fg_Move(_4))
				, m_CopyMove5(NMib::fg_Move(_5))
				, m_CopyMove6(NMib::fg_Move(_6))
				, m_CopyMove7(NMib::fg_Move(_7))
				, m_CopyMove8(NMib::fg_Move(_8))
				, m_CopyMove9(NMib::fg_Move(_9))
			{
			}

			CTestCopyMove(CCopyMove const &_0)
				: m_CopyMove0(_0)
			{
			}
			CTestCopyMove(CCopyMove const &_0, CCopyMove const &_1)
				: m_CopyMove0(_0)
				, m_CopyMove1(_1)
			{
			}
			CTestCopyMove(CCopyMove const &_0, CCopyMove const &_1, CCopyMove const &_2)
				: m_CopyMove0(_0)
				, m_CopyMove1(_1)
				, m_CopyMove2(_2)
			{
			}
			CTestCopyMove(CCopyMove const &_0, CCopyMove const &_1, CCopyMove const &_2, CCopyMove const &_3)
				: m_CopyMove0(_0)
				, m_CopyMove1(_1)
				, m_CopyMove2(_2)
				, m_CopyMove3(_3)
			{
			}
			CTestCopyMove(CCopyMove const &_0, CCopyMove const &_1, CCopyMove const &_2, CCopyMove const &_3, CCopyMove const &_4)
				: m_CopyMove0(_0)
				, m_CopyMove1(_1)
				, m_CopyMove2(_2)
				, m_CopyMove3(_3)
				, m_CopyMove4(_4)
			{
			}
			CTestCopyMove(CCopyMove const &_0, CCopyMove const &_1, CCopyMove const &_2, CCopyMove const &_3, CCopyMove const &_4, CCopyMove const &_5)
				: m_CopyMove0(_0)
				, m_CopyMove1(_1)
				, m_CopyMove2(_2)
				, m_CopyMove3(_3)
				, m_CopyMove4(_4)
				, m_CopyMove5(_5)
			{
			}
			CTestCopyMove(CCopyMove const &_0, CCopyMove const &_1, CCopyMove const &_2, CCopyMove const &_3, CCopyMove const &_4, CCopyMove const &_5, CCopyMove const &_6)
				: m_CopyMove0(_0)
				, m_CopyMove1(_1)
				, m_CopyMove2(_2)
				, m_CopyMove3(_3)
				, m_CopyMove4(_4)
				, m_CopyMove5(_5)
				, m_CopyMove6(_6)
			{
			}
			CTestCopyMove(CCopyMove const &_0, CCopyMove const &_1, CCopyMove const &_2, CCopyMove const &_3, CCopyMove const &_4, CCopyMove const &_5, CCopyMove const &_6, CCopyMove const &_7)
				: m_CopyMove0(_0)
				, m_CopyMove1(_1)
				, m_CopyMove2(_2)
				, m_CopyMove3(_3)
				, m_CopyMove4(_4)
				, m_CopyMove5(_5)
				, m_CopyMove6(_6)
				, m_CopyMove7(_7)
			{
			}
			CTestCopyMove(CCopyMove const &_0, CCopyMove const &_1, CCopyMove const &_2, CCopyMove const &_3, CCopyMove const &_4, CCopyMove const &_5, CCopyMove const &_6, CCopyMove const &_7, CCopyMove const &_8)
				: m_CopyMove0(_0)
				, m_CopyMove1(_1)
				, m_CopyMove2(_2)
				, m_CopyMove3(_3)
				, m_CopyMove4(_4)
				, m_CopyMove5(_5)
				, m_CopyMove6(_6)
				, m_CopyMove7(_7)
				, m_CopyMove8(_8)
			{
			}
			CTestCopyMove(CCopyMove const &_0, CCopyMove const &_1, CCopyMove const &_2, CCopyMove const &_3, CCopyMove const &_4, CCopyMove const &_5, CCopyMove const &_6, CCopyMove const &_7, CCopyMove const &_8, CCopyMove const &_9)
				: m_CopyMove0(_0)
				, m_CopyMove1(_1)
				, m_CopyMove2(_2)
				, m_CopyMove3(_3)
				, m_CopyMove4(_4)
				, m_CopyMove5(_5)
				, m_CopyMove6(_6)
				, m_CopyMove7(_7)
				, m_CopyMove8(_8)
				, m_CopyMove9(_9)
			{
			}
		};

		void f_TestUniquePointer()
		{
			TCUniquePointer<int> TestInt(fg_Construct());
			TCUniquePointer<int> TestInt2(fg_Construct(3));
			DMibTest(DMibExpr(*TestInt2) == DMibExpr(3)) (ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> Test0(fg_Construct());
			DMibTest(DMibExpr(*Test0) == DMibExpr(CSmartPtr_Tests::CTestStruct(0,0,0,0,0,0,0,0,0,0))) (ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> Test1(fg_Construct(1));
			DMibTest(DMibExpr(*Test1) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,0,0,0,0,0,0,0,0,0))) (ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> Test2(fg_Construct(1, 2));
			DMibTest(DMibExpr(*Test2) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,0,0,0,0,0,0,0,0))) (ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> Test3(fg_Construct(1, 2, 3));
			DMibTest(DMibExpr(*Test3) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,0,0,0,0,0,0,0))) (ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> Test4(fg_Construct(1, 2, 3, 4));
			DMibTest(DMibExpr(*Test4) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,0,0,0,0,0,0))) (ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> Test5(fg_Construct(1, 2, 3, 4, 5));
			DMibTest(DMibExpr(*Test5) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,0,0,0,0,0))) (ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> Test6(fg_Construct(1, 2, 3, 4, 5, 6));
			DMibTest(DMibExpr(*Test6) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,0,0,0,0))) (ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> Test7(fg_Construct(1, 2, 3, 4, 5, 6, 7));
			DMibTest(DMibExpr(*Test7) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,0,0,0))) (ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> Test8(fg_Construct(1, 2, 3, 4, 5, 6, 7, 8));
			DMibTest(DMibExpr(*Test8) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,8,0,0))) (ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> Test9(fg_Construct(1, 2, 3, 4, 5, 6, 7, 8, 9));
			DMibTest(DMibExpr(*Test9) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,8,9,0))) (ETestFlag_NoValues);

			TCUniquePointer<CTestStruct> Test10(fg_Construct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
			DMibTest(DMibExpr(*Test10) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,8,9,10))) (ETestFlag_NoValues);

			// Construct derived type
			TCUniquePointer<CTestStructVirtual> TestDerived0(fg_Construct<CTestStruct2>());
			DMibTest(DMibExpr(*TestDerived0) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual())) (ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> TestDerived1(fg_Construct<CTestStruct2>(0));
			DMibTest(DMibExpr(*TestDerived1) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0))) (ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> TestDerived2(fg_Construct<CTestStruct2>(0,1));
			DMibTest(DMibExpr(*TestDerived2) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1))) (ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> TestDerived3(fg_Construct<CTestStruct2>(0,1,2));
			DMibTest(DMibExpr(*TestDerived3) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2))) (ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> TestDerived4(fg_Construct<CTestStruct2>(0,1,2,3));
			DMibTest(DMibExpr(*TestDerived4) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3))) (ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> TestDerived5(fg_Construct<CTestStruct2>(0,1,2,3,4));
			DMibTest(DMibExpr(*TestDerived5) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3,4))) (ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> TestDerived6(fg_Construct<CTestStruct2>(0,1,2,3,4,5));
			DMibTest(DMibExpr(*TestDerived6) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3,4,5))) (ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> TestDerived7(fg_Construct<CTestStruct2>(0,1,2,3,4,5,6));
			DMibTest(DMibExpr(*TestDerived7) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3,4,5,6))) (ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> TestDerived8(fg_Construct<CTestStruct2>(0,1,2,3,4,5,6,7));
			DMibTest(DMibExpr(*TestDerived8) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3,4,5,6,7))) (ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> TestDerived9(fg_Construct<CTestStruct2>(0,1,2,3,4,5,6,7,8));
			DMibTest(DMibExpr(*TestDerived9) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3,4,5,6,7,8))) (ETestFlag_NoValues);
			TCUniquePointer<CTestStructVirtual> TestDerived10(fg_Construct<CTestStruct2>(0,1,2,3,4,5,6,7,8,9));
			DMibTest(DMibExpr(*TestDerived10) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3,4,5,6,7,8,9))) (ETestFlag_NoValues);

			using CCopyMove = CSmartPtr_Tests::CCopyMove;

			// Moves
			TCUniquePointer<CTestCopyMove> TestMove0(fg_Construct());
			DMibTest(DMibExpr(TestMove0->f_GetNumMoves()) == DMibExpr(0));
			DMibTest(DMibExpr(TestMove0->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMove1(fg_Construct(CCopyMove()));
			DMibTest(DMibExpr(TestMove1->f_GetNumMoves()) == DMibExpr(1));
			DMibTest(DMibExpr(TestMove1->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMove2(fg_Construct(CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove2->f_GetNumMoves()) == DMibExpr(2));
			DMibTest(DMibExpr(TestMove2->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMove3(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove3->f_GetNumMoves()) == DMibExpr(3));
			DMibTest(DMibExpr(TestMove3->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMove4(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove4->f_GetNumMoves()) == DMibExpr(4));
			DMibTest(DMibExpr(TestMove4->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMove5(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove5->f_GetNumMoves()) == DMibExpr(5));
			DMibTest(DMibExpr(TestMove5->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMove6(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove6->f_GetNumMoves()) == DMibExpr(6));
			DMibTest(DMibExpr(TestMove6->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMove7(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove7->f_GetNumMoves()) == DMibExpr(7));
			DMibTest(DMibExpr(TestMove7->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMove8(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove8->f_GetNumMoves()) == DMibExpr(8));
			DMibTest(DMibExpr(TestMove8->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMove9(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove9->f_GetNumMoves()) == DMibExpr(9));
			DMibTest(DMibExpr(TestMove9->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMove10(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove10->f_GetNumMoves()) == DMibExpr(10));
			DMibTest(DMibExpr(TestMove10->f_GetNumCopies()) == DMibExpr(0));

			// Moves explicit
			TCUniquePointer<CTestCopyMove> TestMoveExplicit0(fg_Construct<CTestCopyMove>());
			DMibTest(DMibExpr(TestMoveExplicit0->f_GetNumMoves()) == DMibExpr(0));
			DMibTest(DMibExpr(TestMoveExplicit0->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMoveExplicit1(fg_Construct<CTestCopyMove>(CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit1->f_GetNumMoves()) == DMibExpr(1));
			DMibTest(DMibExpr(TestMoveExplicit1->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMoveExplicit2(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit2->f_GetNumMoves()) == DMibExpr(2));
			DMibTest(DMibExpr(TestMoveExplicit2->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMoveExplicit3(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit3->f_GetNumMoves()) == DMibExpr(3));
			DMibTest(DMibExpr(TestMoveExplicit3->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMoveExplicit4(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit4->f_GetNumMoves()) == DMibExpr(4));
			DMibTest(DMibExpr(TestMoveExplicit4->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMoveExplicit5(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit5->f_GetNumMoves()) == DMibExpr(5));
			DMibTest(DMibExpr(TestMoveExplicit5->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMoveExplicit6(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit6->f_GetNumMoves()) == DMibExpr(6));
			DMibTest(DMibExpr(TestMoveExplicit6->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMoveExplicit7(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit7->f_GetNumMoves()) == DMibExpr(7));
			DMibTest(DMibExpr(TestMoveExplicit7->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMoveExplicit8(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit8->f_GetNumMoves()) == DMibExpr(8));
			DMibTest(DMibExpr(TestMoveExplicit8->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMoveExplicit9(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit9->f_GetNumMoves()) == DMibExpr(9));
			DMibTest(DMibExpr(TestMoveExplicit9->f_GetNumCopies()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestMoveExplicit10(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit10->f_GetNumMoves()) == DMibExpr(10));
			DMibTest(DMibExpr(TestMoveExplicit10->f_GetNumCopies()) == DMibExpr(0));

			// Copies
			CCopyMove CopyFrom;
			TCUniquePointer<CTestCopyMove> TestCopy0(fg_Construct());
			DMibTest(DMibExpr(TestCopy0->f_GetNumCopies()) == DMibExpr(0));
			DMibTest(DMibExpr(TestCopy0->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopy1(fg_Construct(CopyFrom));
			DMibTest(DMibExpr(TestCopy1->f_GetNumCopies()) == DMibExpr(1));
			DMibTest(DMibExpr(TestCopy1->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopy2(fg_Construct(CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy2->f_GetNumCopies()) == DMibExpr(2));
			DMibTest(DMibExpr(TestCopy2->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopy3(fg_Construct(CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy3->f_GetNumCopies()) == DMibExpr(3));
			DMibTest(DMibExpr(TestCopy3->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopy4(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy4->f_GetNumCopies()) == DMibExpr(4));
			DMibTest(DMibExpr(TestCopy4->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopy5(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy5->f_GetNumCopies()) == DMibExpr(5));
			DMibTest(DMibExpr(TestCopy5->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopy6(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy6->f_GetNumCopies()) == DMibExpr(6));
			DMibTest(DMibExpr(TestCopy6->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopy7(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy7->f_GetNumCopies()) == DMibExpr(7));
			DMibTest(DMibExpr(TestCopy7->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopy8(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy8->f_GetNumCopies()) == DMibExpr(8));
			DMibTest(DMibExpr(TestCopy8->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopy9(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy9->f_GetNumCopies()) == DMibExpr(9));
			DMibTest(DMibExpr(TestCopy9->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopy10(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy10->f_GetNumCopies()) == DMibExpr(10));
			DMibTest(DMibExpr(TestCopy10->f_GetNumMoves()) == DMibExpr(0));

			// Copies explicit
			TCUniquePointer<CTestCopyMove> TestCopyExplicit0(fg_Construct<CTestCopyMove>());
			DMibTest(DMibExpr(TestCopyExplicit0->f_GetNumCopies()) == DMibExpr(0));
			DMibTest(DMibExpr(TestCopyExplicit0->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopyExplicit1(fg_Construct<CTestCopyMove>(CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit1->f_GetNumCopies()) == DMibExpr(1));
			DMibTest(DMibExpr(TestCopyExplicit1->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopyExplicit2(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit2->f_GetNumCopies()) == DMibExpr(2));
			DMibTest(DMibExpr(TestCopyExplicit2->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopyExplicit3(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit3->f_GetNumCopies()) == DMibExpr(3));
			DMibTest(DMibExpr(TestCopyExplicit3->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopyExplicit4(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit4->f_GetNumCopies()) == DMibExpr(4));
			DMibTest(DMibExpr(TestCopyExplicit4->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopyExplicit5(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit5->f_GetNumCopies()) == DMibExpr(5));
			DMibTest(DMibExpr(TestCopyExplicit5->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopyExplicit6(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit6->f_GetNumCopies()) == DMibExpr(6));
			DMibTest(DMibExpr(TestCopyExplicit6->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopyExplicit7(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit7->f_GetNumCopies()) == DMibExpr(7));
			DMibTest(DMibExpr(TestCopyExplicit7->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopyExplicit8(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit8->f_GetNumCopies()) == DMibExpr(8));
			DMibTest(DMibExpr(TestCopyExplicit8->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopyExplicit9(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit9->f_GetNumCopies()) == DMibExpr(9));
			DMibTest(DMibExpr(TestCopyExplicit9->f_GetNumMoves()) == DMibExpr(0));
			TCUniquePointer<CTestCopyMove> TestCopyExplicit10(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit10->f_GetNumCopies()) == DMibExpr(10));
			DMibTest(DMibExpr(TestCopyExplicit10->f_GetNumMoves()) == DMibExpr(0));


			// Deep copy
			TCUniquePointer<CTestStruct> TestDeepCopy(fg_Copy(Test10));
			DMibTest(DMibExpr(*TestDeepCopy) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,8,9,10))) (ETestFlag_NoValues);

			// Deep copy assign
			TestDeepCopy = fg_Copy(Test10);
			DMibTest(DMibExpr(*TestDeepCopy) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,8,9,10)) && DMibExpr(2)) (ETestFlag_NoValues);

			// Construct assign
			Test10 = fg_Construct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
			DMibTest(DMibExpr(*Test10) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,8,9,10)) && DMibExpr(2)) (ETestFlag_NoValues);
		}

		void f_TestSharedPointer()
		{
			TCSharedPointer<int> TestInt(fg_Construct());
			TCSharedPointer<int> TestInt2(fg_Construct(3));
			DMibTest(DMibExpr(*TestInt2) == DMibExpr(3)) (ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> Test0(fg_Construct());
			DMibTest(DMibExpr(*Test0) == DMibExpr(CSmartPtr_Tests::CTestStruct(0,0,0,0,0,0,0,0,0,0))) (ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> Test1(fg_Construct(1));
			DMibTest(DMibExpr(*Test1) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,0,0,0,0,0,0,0,0,0))) (ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> Test2(fg_Construct(1, 2));
			DMibTest(DMibExpr(*Test2) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,0,0,0,0,0,0,0,0))) (ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> Test3(fg_Construct(1, 2, 3));
			DMibTest(DMibExpr(*Test3) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,0,0,0,0,0,0,0))) (ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> Test4(fg_Construct(1, 2, 3, 4));
			DMibTest(DMibExpr(*Test4) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,0,0,0,0,0,0))) (ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> Test5(fg_Construct(1, 2, 3, 4, 5));
			DMibTest(DMibExpr(*Test5) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,0,0,0,0,0))) (ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> Test6(fg_Construct(1, 2, 3, 4, 5, 6));
			DMibTest(DMibExpr(*Test6) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,0,0,0,0))) (ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> Test7(fg_Construct(1, 2, 3, 4, 5, 6, 7));
			DMibTest(DMibExpr(*Test7) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,0,0,0))) (ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> Test8(fg_Construct(1, 2, 3, 4, 5, 6, 7, 8));
			DMibTest(DMibExpr(*Test8) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,8,0,0))) (ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> Test9(fg_Construct(1, 2, 3, 4, 5, 6, 7, 8, 9));
			DMibTest(DMibExpr(*Test9) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,8,9,0))) (ETestFlag_NoValues);

			TCSharedPointer<CTestStruct> Test10(fg_Construct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
			DMibTest(DMibExpr(*Test10) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,8,9,10))) (ETestFlag_NoValues);

			// Construct derived type
			TCSharedPointer<CTestStructVirtual> TestDerived0(fg_Construct<CTestStruct2>());
			DMibTest(DMibExpr(*TestDerived0) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual())) (ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> TestDerived1(fg_Construct<CTestStruct2>(0));
			DMibTest(DMibExpr(*TestDerived1) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0))) (ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> TestDerived2(fg_Construct<CTestStruct2>(0,1));
			DMibTest(DMibExpr(*TestDerived2) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1))) (ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> TestDerived3(fg_Construct<CTestStruct2>(0,1,2));
			DMibTest(DMibExpr(*TestDerived3) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2))) (ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> TestDerived4(fg_Construct<CTestStruct2>(0,1,2,3));
			DMibTest(DMibExpr(*TestDerived4) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3))) (ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> TestDerived5(fg_Construct<CTestStruct2>(0,1,2,3,4));
			DMibTest(DMibExpr(*TestDerived5) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3,4))) (ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> TestDerived6(fg_Construct<CTestStruct2>(0,1,2,3,4,5));
			DMibTest(DMibExpr(*TestDerived6) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3,4,5))) (ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> TestDerived7(fg_Construct<CTestStruct2>(0,1,2,3,4,5,6));
			DMibTest(DMibExpr(*TestDerived7) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3,4,5,6))) (ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> TestDerived8(fg_Construct<CTestStruct2>(0,1,2,3,4,5,6,7));
			DMibTest(DMibExpr(*TestDerived8) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3,4,5,6,7))) (ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> TestDerived9(fg_Construct<CTestStruct2>(0,1,2,3,4,5,6,7,8));
			DMibTest(DMibExpr(*TestDerived9) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3,4,5,6,7,8))) (ETestFlag_NoValues);
			TCSharedPointer<CTestStructVirtual> TestDerived10(fg_Construct<CTestStruct2>(0,1,2,3,4,5,6,7,8,9));
			DMibTest(DMibExpr(*TestDerived10) == DMibExpr(CSmartPtr_Tests::CTestStructVirtual(0,1,2,3,4,5,6,7,8,9))) (ETestFlag_NoValues);

			using CCopyMove = CSmartPtr_Tests::CCopyMove;

			// Moves
			TCSharedPointer<CTestCopyMove> TestMove0(fg_Construct());
			DMibTest(DMibExpr(TestMove0->f_GetNumMoves()) == DMibExpr(0));
			DMibTest(DMibExpr(TestMove0->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMove1(fg_Construct(CCopyMove()));
			DMibTest(DMibExpr(TestMove1->f_GetNumMoves()) == DMibExpr(1));
			DMibTest(DMibExpr(TestMove1->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMove2(fg_Construct(CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove2->f_GetNumMoves()) == DMibExpr(2));
			DMibTest(DMibExpr(TestMove2->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMove3(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove3->f_GetNumMoves()) == DMibExpr(3));
			DMibTest(DMibExpr(TestMove3->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMove4(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove4->f_GetNumMoves()) == DMibExpr(4));
			DMibTest(DMibExpr(TestMove4->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMove5(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove5->f_GetNumMoves()) == DMibExpr(5));
			DMibTest(DMibExpr(TestMove5->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMove6(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove6->f_GetNumMoves()) == DMibExpr(6));
			DMibTest(DMibExpr(TestMove6->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMove7(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove7->f_GetNumMoves()) == DMibExpr(7));
			DMibTest(DMibExpr(TestMove7->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMove8(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove8->f_GetNumMoves()) == DMibExpr(8));
			DMibTest(DMibExpr(TestMove8->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMove9(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove9->f_GetNumMoves()) == DMibExpr(9));
			DMibTest(DMibExpr(TestMove9->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMove10(fg_Construct(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMove10->f_GetNumMoves()) == DMibExpr(10));
			DMibTest(DMibExpr(TestMove10->f_GetNumCopies()) == DMibExpr(0));

			// Moves explicit
			TCSharedPointer<CTestCopyMove> TestMoveExplicit0(fg_Construct<CTestCopyMove>());
			DMibTest(DMibExpr(TestMoveExplicit0->f_GetNumMoves()) == DMibExpr(0));
			DMibTest(DMibExpr(TestMoveExplicit0->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMoveExplicit1(fg_Construct<CTestCopyMove>(CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit1->f_GetNumMoves()) == DMibExpr(1));
			DMibTest(DMibExpr(TestMoveExplicit1->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMoveExplicit2(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit2->f_GetNumMoves()) == DMibExpr(2));
			DMibTest(DMibExpr(TestMoveExplicit2->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMoveExplicit3(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit3->f_GetNumMoves()) == DMibExpr(3));
			DMibTest(DMibExpr(TestMoveExplicit3->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMoveExplicit4(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit4->f_GetNumMoves()) == DMibExpr(4));
			DMibTest(DMibExpr(TestMoveExplicit4->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMoveExplicit5(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit5->f_GetNumMoves()) == DMibExpr(5));
			DMibTest(DMibExpr(TestMoveExplicit5->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMoveExplicit6(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit6->f_GetNumMoves()) == DMibExpr(6));
			DMibTest(DMibExpr(TestMoveExplicit6->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMoveExplicit7(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit7->f_GetNumMoves()) == DMibExpr(7));
			DMibTest(DMibExpr(TestMoveExplicit7->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMoveExplicit8(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit8->f_GetNumMoves()) == DMibExpr(8));
			DMibTest(DMibExpr(TestMoveExplicit8->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMoveExplicit9(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit9->f_GetNumMoves()) == DMibExpr(9));
			DMibTest(DMibExpr(TestMoveExplicit9->f_GetNumCopies()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestMoveExplicit10(fg_Construct<CTestCopyMove>(CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove(),CCopyMove()));
			DMibTest(DMibExpr(TestMoveExplicit10->f_GetNumMoves()) == DMibExpr(10));
			DMibTest(DMibExpr(TestMoveExplicit10->f_GetNumCopies()) == DMibExpr(0));

			// Copies
			CCopyMove CopyFrom;
			TCSharedPointer<CTestCopyMove> TestCopy0(fg_Construct());
			DMibTest(DMibExpr(TestCopy0->f_GetNumCopies()) == DMibExpr(0));
			DMibTest(DMibExpr(TestCopy0->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopy1(fg_Construct(CopyFrom));
			DMibTest(DMibExpr(TestCopy1->f_GetNumCopies()) == DMibExpr(1));
			DMibTest(DMibExpr(TestCopy1->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopy2(fg_Construct(CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy2->f_GetNumCopies()) == DMibExpr(2));
			DMibTest(DMibExpr(TestCopy2->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopy3(fg_Construct(CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy3->f_GetNumCopies()) == DMibExpr(3));
			DMibTest(DMibExpr(TestCopy3->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopy4(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy4->f_GetNumCopies()) == DMibExpr(4));
			DMibTest(DMibExpr(TestCopy4->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopy5(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy5->f_GetNumCopies()) == DMibExpr(5));
			DMibTest(DMibExpr(TestCopy5->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopy6(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy6->f_GetNumCopies()) == DMibExpr(6));
			DMibTest(DMibExpr(TestCopy6->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopy7(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy7->f_GetNumCopies()) == DMibExpr(7));
			DMibTest(DMibExpr(TestCopy7->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopy8(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy8->f_GetNumCopies()) == DMibExpr(8));
			DMibTest(DMibExpr(TestCopy8->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopy9(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy9->f_GetNumCopies()) == DMibExpr(9));
			DMibTest(DMibExpr(TestCopy9->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopy10(fg_Construct(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopy10->f_GetNumCopies()) == DMibExpr(10));
			DMibTest(DMibExpr(TestCopy10->f_GetNumMoves()) == DMibExpr(0));

			// Copies explicit
			TCSharedPointer<CTestCopyMove> TestCopyExplicit0(fg_Construct<CTestCopyMove>());
			DMibTest(DMibExpr(TestCopyExplicit0->f_GetNumCopies()) == DMibExpr(0));
			DMibTest(DMibExpr(TestCopyExplicit0->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopyExplicit1(fg_Construct<CTestCopyMove>(CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit1->f_GetNumCopies()) == DMibExpr(1));
			DMibTest(DMibExpr(TestCopyExplicit1->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopyExplicit2(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit2->f_GetNumCopies()) == DMibExpr(2));
			DMibTest(DMibExpr(TestCopyExplicit2->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopyExplicit3(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit3->f_GetNumCopies()) == DMibExpr(3));
			DMibTest(DMibExpr(TestCopyExplicit3->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopyExplicit4(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit4->f_GetNumCopies()) == DMibExpr(4));
			DMibTest(DMibExpr(TestCopyExplicit4->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopyExplicit5(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit5->f_GetNumCopies()) == DMibExpr(5));
			DMibTest(DMibExpr(TestCopyExplicit5->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopyExplicit6(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit6->f_GetNumCopies()) == DMibExpr(6));
			DMibTest(DMibExpr(TestCopyExplicit6->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopyExplicit7(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit7->f_GetNumCopies()) == DMibExpr(7));
			DMibTest(DMibExpr(TestCopyExplicit7->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopyExplicit8(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit8->f_GetNumCopies()) == DMibExpr(8));
			DMibTest(DMibExpr(TestCopyExplicit8->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopyExplicit9(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit9->f_GetNumCopies()) == DMibExpr(9));
			DMibTest(DMibExpr(TestCopyExplicit9->f_GetNumMoves()) == DMibExpr(0));
			TCSharedPointer<CTestCopyMove> TestCopyExplicit10(fg_Construct<CTestCopyMove>(CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom,CopyFrom));
			DMibTest(DMibExpr(TestCopyExplicit10->f_GetNumCopies()) == DMibExpr(10));
			DMibTest(DMibExpr(TestCopyExplicit10->f_GetNumMoves()) == DMibExpr(0));


			// Deep copy
			{
				TCSharedPointer<CTestStruct> TestDeepCopy(fg_Copy(Test10));
				DMibTest(DMibExpr(*TestDeepCopy) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,8,9,10))) (ETestFlag_NoValues);

				// Deep copy assign
				TestDeepCopy = fg_Copy(Test10);
				DMibTest(DMibExpr(*TestDeepCopy) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,8,9,10)) && DMibExpr(2)) (ETestFlag_NoValues);
			}

			// Construct assign
			Test10 = fg_Construct(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
			DMibTest(DMibExpr(*Test10) == DMibExpr(CSmartPtr_Tests::CTestStruct(1,2,3,4,5,6,7,8,9,10)) && DMibExpr(2)) (ETestFlag_NoValues);
		}

		void f_TestSharedPointerInheritance()
		{
			static constexpr bool s_bReportMemory = false;

			using namespace NStr;

			struct CBaseNonVirtual
			{
				mint m_Value0 = 0;
			};

			struct CBase
			{
				virtual ~CBase()
				{
					//DMibTraceSafe2("~CBase\n");
				}

				virtual mint f_GetValue()
				{
					return m_Value0;
				}

				mint m_Value0 = 0;
				//NStr::CStr m_StrValue = "Base";
			};

			struct CDerived : public CBase
			{
				~CDerived()
				{
					//DMibTraceSafe2("~CDerived\n");
				}

				mint f_GetValue() override
				{
					return m_Value0;
				}

				mint m_Value0 = 1;
				//NStr::CStr m_StrValue = "Derived";
			};

			struct CDerivedVirtual : public virtual CBase
			{
				~CDerivedVirtual()
				{
					//DMibTraceSafe2("~CDerived\n");
				}

				mint f_GetValue() override
				{
					return m_Value0;
				}

				mint m_Value0 = 1;
				//NStr::CStr m_StrValue = "Derived";
			};

			struct CDerived2Virtual : public virtual CBase
			{
				~CDerived2Virtual()
				{
					//DMibTraceSafe2("~CDerived2\n");
				}

				mint f_GetValue() override
				{
					return m_Value0;
				}

				mint m_Value0 = 2;
				//NStr::CStr m_StrValue = "Derived2";
			};

			struct alignas(32) CAligned32DiamondDerivedVirtual : public CDerivedVirtual, CDerived2Virtual
			{
				~CAligned32DiamondDerivedVirtual()
				{
					//DMibTraceSafe2("~CDerived3\n");
				}

				mint f_GetValue() override
				{
					return m_Value0;
				}

				mint m_Value0 = 3;
				//NStr::CStr m_StrValue = "Derived3";
			};


			struct CBaseIntrusive
			{
				virtual ~CBaseIntrusive()
				{
					//DMibTraceSafe2("~CBase\n");
				}

				virtual mint f_GetValue()
				{
					return m_Value0;
				}

				NStorage::CIntrusiveRefCount m_RefCount;
				mint m_Value0 = 0;
				//NStr::CStr m_StrValue = "Base";
			};

			struct CBaseIntrusiveSupportWeak
			{
				virtual ~CBaseIntrusiveSupportWeak()
				{
					//DMibTraceSafe2("~CBase\n");
				}

				virtual mint f_GetValue()
				{
					return m_Value0;
				}

				CIntrusiveRefCountWithWeak m_RefCount;
				mint m_Value0 = 0;
				//NStr::CStr m_StrValue = "Base";
			};

			struct CDerivedIntrusive : public CBaseIntrusive
			{
				~CDerivedIntrusive()
				{
					//DMibTraceSafe2("~CDerived\n");
				}

				mint f_GetValue() override
				{
					return m_Value0;
				}

				mint m_Value0 = 1;
				//NStr::CStr m_StrValue = "Derived";
			};

			struct CDerivedIntrusiveSupportWeak : public CBaseIntrusiveSupportWeak
			{
				~CDerivedIntrusiveSupportWeak()
				{
					//DMibTraceSafe2("~CDerived\n");
				}

				mint f_GetValue() override
				{
					return m_Value0;
				}

				mint m_Value0 = 1;
				//NStr::CStr m_StrValue = "Derived";
			};

			struct CDerivedVirtualIntrusive : public virtual CBaseIntrusive
			{
				~CDerivedVirtualIntrusive()
				{
					//DMibTraceSafe2("~CDerived\n");
				}

				mint f_GetValue() override
				{
					return m_Value0;
				}

				mint m_Value0 = 1;
				//NStr::CStr m_StrValue = "Derived";
			};

			struct CDerived2VirtualIntrusive : public virtual CBaseIntrusive
			{
				~CDerived2VirtualIntrusive()
				{
					//DMibTraceSafe2("~CDerived2\n");
				}

				mint f_GetValue() override
				{
					return m_Value0;
				}

				mint m_Value0 = 2;
				//NStr::CStr m_StrValue = "Derived2";
			};

			struct alignas(32) CAligned32DiamondDerivedVirtualIntrusive : public CDerivedVirtualIntrusive, CDerived2VirtualIntrusive
			{
				~CAligned32DiamondDerivedVirtualIntrusive()
				{
					//DMibTraceSafe2("~CDerived3\n");
				}

				mint f_GetValue() override
				{
					return m_Value0;
				}

				mint m_Value0 = 3;
				//NStr::CStr m_StrValue = "Derived3";
			};

			struct CDerivedVirtualIntrusiveSupportWeak : public virtual CBaseIntrusiveSupportWeak
			{
				~CDerivedVirtualIntrusiveSupportWeak()
				{
					//DMibTraceSafe2("~CDerived\n");
				}

				mint f_GetValue() override
				{
					return m_Value0;
				}

				mint m_Value0 = 1;
				//NStr::CStr m_StrValue = "Derived";
			};

			struct CDerived2VirtualIntrusiveSupportWeak : public virtual CBaseIntrusiveSupportWeak
			{
				~CDerived2VirtualIntrusiveSupportWeak()
				{
					//DMibTraceSafe2("~CDerived2\n");
				}

				mint f_GetValue() override
				{
					return m_Value0;
				}

				mint m_Value0 = 2;
				//NStr::CStr m_StrValue = "Derived2";
			};

			struct alignas(32) CAligned32DiamondDerivedVirtualIntrusiveSupportWeak : public CDerivedVirtualIntrusiveSupportWeak, CDerived2VirtualIntrusiveSupportWeak
			{
				~CAligned32DiamondDerivedVirtualIntrusiveSupportWeak()
				{
					//DMibTraceSafe2("~CDerived3\n");
				}

				mint f_GetValue() override
				{
					return m_Value0;
				}

				mint m_Value0 = 3;
				//NStr::CStr m_StrValue = "Derived3";
			};

			struct CReportScope : public CReportMemory
			{
				CReportScope(CFStr256 const &_Description, mint _Size)
					: m_Description(_Description)
					, m_Size(_Size)
				{
#if DMibConfig_Memory_Shims_Enable
					if constexpr (s_bReportMemory)
						m_pScope = fg_Construct(*this);
#endif
				}
				~CReportScope()
				{
					if constexpr (s_bReportMemory)
						DMibTraceSafe2("{}   Total {sj3}   ({sj2} + Allocs {})\n", m_Description, m_Size + m_Allocated, m_Size, m_Allocations);
				}

				virtual void f_Alloc
					(
						mint _MemoryAllocator
						, mint _AllocatorDepth
						, ch8 const *_pAllocatorName
						, mint _Address
						, mint _RequestedAlignment
						, mint _RequestedSize
						, mint _ReturnedSize
						, fp32 _nBytesOverhead
						, void *_pAllocationInfo
					) override
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
						mint _MemoryAllocator
						, mint _AllocatorDepth
						, ch8 const *_pAllocatorName
						, mint _OldAddress
						, mint _OldSize
						, void const *_pOldAllocationInfo
						, mint _Address
						, mint _RequestedAlignment
						, mint _RequestedSize
						, mint _ReturnedSize
						, fp32 _nBytesOverhead
						, void *_pAllocationInfo
					) override
				{
				}

				virtual void f_Realloc
					(
						mint _MemoryAllocator
						, mint _AllocatorDepth
						, ch8 const *_pAllocatorName
						, mint _OldAddress
						, mint _OldSize
						, void const *_pOldAllocationInfo
						, mint _Address
						, mint _RequestedAlignment
						, mint _RequestedSize
						, mint _ReturnedSize
						, fp32 _nBytesOverhead
						, void *_pAllocationInfo
					) override
				{
				}

				virtual void f_Free(mint _MemoryAllocator, ch8 const *_pAllocatorName, mint _AllocatorDepth, mint _Address, mint _Size, void const *_pAllocationInfo) override
				{
				}

				virtual void f_GetSize(mint _MemoryAllocator, ch8 const *_pAllocatorName, mint _AllocatorDepth, mint _Address, mint _Size, void const *_pAllocationInfo) override
				{
				}

				virtual void f_Protect(mint _MemoryAllocator, ch8 const *_pAllocatorName, mint _AllocatorDepth, mint _Address, mint _Size, uaint _Protect) override
				{
				}

				virtual void f_Commit(mint _MemoryAllocator, ch8 const *_pAllocatorName, mint _AllocatorDepth, mint _Address, mint _Size) override
				{
				}

				virtual void f_Decommit(mint _MemoryAllocator, ch8 const *_pAllocatorName, mint _AllocatorDepth, mint _Address, mint _Size) override
				{
				}

				virtual void f_AllocatorDelete(mint _MemoryAllocator, ch8 const *_pAllocatorName, mint _AllocatorDepth) override
				{
				}

				CFStr256 m_Description;
				CFStr256 m_Allocations;
				mint m_Size = 0;
				mint m_Allocated = 0;
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
			if constexpr (s_bReportMemory)
				DMibTraceSafe2("\n");

			{
				DMibTestPath("Base");
				{
					CReportScope ReportScope("TCUniquePointer            CBase                                              ", sizeof(TCUniquePointer<CBase>));
					TCUniquePointer<CBase> pMalterlibUniquePointer(fg_Construct<CBase>());

					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibUniquePointer->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("unique_ptr                 CBase                                              ", sizeof(std::unique_ptr<CBase>));
					std::unique_ptr<CBase> pUniquePointer(std::make_unique<CBase>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pUniquePointer->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CBaseIntrusive                                     ", sizeof(TCSharedPointer<CBaseIntrusive>));
					TCSharedPointer<CBaseIntrusive> pMalterlibSharedPointerIntrusive(fg_Construct<CBaseIntrusive>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusive->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CBaseIntrusiveSupportWeak                          ", sizeof(TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak>));
					TCSharedPointer<CBaseIntrusiveSupportWeak> pMalterlibSharedPointerIntrusiveSupportWeak(fg_Construct<CBaseIntrusiveSupportWeak>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusiveSupportWeak->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CBase                                              ", sizeof(TCSharedPointer<CBase>));
					TCSharedPointer<CBase> pMalterlibSharedPointer(fg_Construct<CBase>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointer->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CBase                                              ", sizeof(TCSharedPointerSupportWeak<CBase>));
					TCSharedPointerSupportWeak<CBase> pMalterlibSharedPointerSupportWeak(fg_Construct<CBase>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointerSupportWeak->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("make_shared                CBase                                              ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pMakeShared(std::make_shared<CBase>());

					if constexpr (!s_bReportMemory)
						DMibExpect(pMakeShared->f_GetValue(), ==, 0);
				}
				{
					CReportScope ReportScope("shared_ptr                 CBase                                              ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pSharedPointer(new CBase());

					if constexpr (!s_bReportMemory)
						DMibExpect(pSharedPointer->f_GetValue(), ==, 0);
				}
			}
			if constexpr (s_bReportMemory)
				DMibTraceSafe2("\n");

			{
				DMibTestPath("Derived");
				{
					CReportScope ReportScope("TCUniquePointer            CDerived                                           ", sizeof(TCUniquePointer<CBase>));
					TCUniquePointer<CBase> pMalterlibUniquePointer(fg_Construct<CDerived>());

					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibUniquePointer->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("unique_ptr                 CDerived                                           ", sizeof(std::unique_ptr<CBase>));
					std::unique_ptr<CBase> pUniquePointer(std::make_unique<CDerived>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pUniquePointer->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CDerivedIntrusive                                  ", sizeof(TCSharedPointer<CBaseIntrusive>));
					TCSharedPointer<CBaseIntrusive> pMalterlibSharedPointerIntrusive(fg_Construct<CDerivedIntrusive>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusive->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CDerivedIntrusiveSupportWeak                       ", sizeof(TCSharedPointer<CBaseIntrusiveSupportWeak>));
					TCSharedPointer<CBaseIntrusiveSupportWeak> pMalterlibSharedPointerIntrusiveSupportWeak(fg_Construct<CDerivedIntrusiveSupportWeak>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusiveSupportWeak->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CDerived                                           ", sizeof(TCSharedPointer<CBase>));
					TCSharedPointer<CBase> pMalterlibSharedPointer(fg_Construct<CDerived>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointer->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CDerived                                           ", sizeof(TCSharedPointerSupportWeak<CBase>));
					TCSharedPointerSupportWeak<CBase> pMalterlibSharedPointerSupportWeak(fg_Construct<CDerived>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointerSupportWeak->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("make_shared                CDerived                                           ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pMakeShared(std::make_shared<CDerived>());

					if constexpr (!s_bReportMemory)
						DMibExpect(pMakeShared->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("shared_ptr                 CDerived                                           ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pSharedPointer(new CDerived());

					if constexpr (!s_bReportMemory)
						DMibExpect(pSharedPointer->f_GetValue(), ==, 1);
				}
			}

			if constexpr (s_bReportMemory)
				DMibTraceSafe2("\n");

			{
				DMibTestPath("DerivedVirtual");
				{
					CReportScope ReportScope("TCUniquePointer            CDerivedVirtual                                    ", sizeof(TCUniquePointer<CBase>));
					TCUniquePointer<CBase> pMalterlibUniquePointer(fg_Construct<CDerivedVirtual>());

					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibUniquePointer->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("unique_ptr                 CDerivedVirtual                                    ", sizeof(std::unique_ptr<CBase>));
					std::unique_ptr<CBase> pUniquePointer(std::make_unique<CDerivedVirtual>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pUniquePointer->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CDerivedVirtualIntrusive                           ", sizeof(TCSharedPointer<CBaseIntrusive>));
					TCSharedPointer<CBaseIntrusive> pMalterlibSharedPointerIntrusive(fg_Construct<CDerivedVirtualIntrusive>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusive->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CDerivedVirtualIntrusiveSupportWeak                ", sizeof(TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak>));
					TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak> pMalterlibSharedPointerSupportWeak(fg_Construct<CDerivedVirtualIntrusiveSupportWeak>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointerSupportWeak->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("make_shared                CDerivedVirtual                                    ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pMakeShared(std::make_shared<CDerivedVirtual>());

					if constexpr (!s_bReportMemory)
						DMibExpect(pMakeShared->f_GetValue(), ==, 1);
				}
				{
					CReportScope ReportScope("shared_ptr                 CDerivedVirtual                                    ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pSharedPointer(new CDerivedVirtual());

					if constexpr (!s_bReportMemory)
						DMibExpect(pSharedPointer->f_GetValue(), ==, 1);
				}
			}
			if constexpr (s_bReportMemory)
				DMibTraceSafe2("\n");

			{
				DMibTestPath("Derived2Virtual");
				{
					CReportScope ReportScope("TCUniquePointer            CDerived2Virtual                                   ", sizeof(TCUniquePointer<CBase>));
					TCUniquePointer<CBase> pMalterlibUniquePointer(fg_Construct<CDerived2Virtual>());

					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibUniquePointer->f_GetValue(), ==, 2);
				}
				{
					CReportScope ReportScope("unique_ptr                 CDerived2Virtual                                   ", sizeof(std::unique_ptr<CBase>));
					std::unique_ptr<CBase> pUniquePointer(std::make_unique<CDerived2Virtual>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pUniquePointer->f_GetValue(), ==, 2);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CDerived2VirtualIntrusive                          ", sizeof(TCSharedPointer<CBaseIntrusive>));
					TCSharedPointer<CBaseIntrusive> pMalterlibSharedPointerIntrusive(fg_Construct<CDerived2VirtualIntrusive>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusive->f_GetValue(), ==, 2);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CDerived2VirtualIntrusiveSupportWeak               ", sizeof(TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak>));
					TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak> pMalterlibSharedPointerSupportWeak(fg_Construct<CDerived2VirtualIntrusiveSupportWeak>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointerSupportWeak->f_GetValue(), ==, 2);
				}
				{
					CReportScope ReportScope("make_shared                CDerived2Virtual                                   ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pMakeShared(new CDerived2Virtual());

					if constexpr (!s_bReportMemory)
						DMibExpect(pMakeShared->f_GetValue(), ==, 2);
				}
				{
					CReportScope ReportScope("shared_ptr                 CDerived2Virtual                                   ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pSharedPointer(std::make_shared<CDerived2Virtual>());

					if constexpr (!s_bReportMemory)
						DMibExpect(pSharedPointer->f_GetValue(), ==, 2);
				}
			}
			if constexpr (s_bReportMemory)
				DMibTraceSafe2("\n");

			{
				DMibTestPath("Derived3Virtual");
				{
					CReportScope ReportScope("TCUniquePointer            CAligned32DiamondDerivedVirtual                    ", sizeof(TCUniquePointer<CBase>));
					TCUniquePointer<CBase> pMalterlibUniquePointer(fg_Construct<CAligned32DiamondDerivedVirtual>());

					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibUniquePointer->f_GetValue(), ==, 3);
				}
				{
					CReportScope ReportScope("unique_ptr                 CAligned32DiamondDerivedVirtual                    ", sizeof(std::unique_ptr<CBase>));
					std::unique_ptr<CBase> pUniquePointer(std::make_unique<CAligned32DiamondDerivedVirtual>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pUniquePointer->f_GetValue(), ==, 3);
				}
				{
					CReportScope ReportScope("TCSharedPointer            CAligned32DiamondDerivedVirtualIntrusive           ", sizeof(TCSharedPointer<CBaseIntrusive>));
					TCSharedPointer<CBaseIntrusive> pMalterlibSharedPointerIntrusive(fg_Construct<CAligned32DiamondDerivedVirtualIntrusive>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointerIntrusive->f_GetValue(), ==, 3);
				}
				{
					CReportScope ReportScope("TCSharedPointerSupportWeak CAligned32DiamondDerivedVirtualIntrusiveSupportWeak", sizeof(TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak>));
					TCSharedPointerSupportWeak<CBaseIntrusiveSupportWeak> pMalterlibSharedPointerSupportWeak(fg_Construct<CAligned32DiamondDerivedVirtualIntrusiveSupportWeak>());
					if constexpr (!s_bReportMemory)
						DMibExpect(pMalterlibSharedPointerSupportWeak->f_GetValue(), ==, 3);
				}
				{
					CReportScope ReportScope("make_shared                CAligned32DiamondDerivedVirtual                    ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pMakeShared(std::make_shared<CAligned32DiamondDerivedVirtual>());

					if constexpr (!s_bReportMemory)
						DMibExpect(pMakeShared->f_GetValue(), ==, 3);
				}
				{
					CReportScope ReportScope("shared_ptr                 CAligned32DiamondDerivedVirtual                    ", sizeof(std::shared_ptr<CBase>));
					std::shared_ptr<CBase> pSharedPointer(new CAligned32DiamondDerivedVirtual());

					if constexpr (!s_bReportMemory)
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
		}
	};

	DMibTestRegister(CSmartPtr_Tests, Malterlib::Storage);
}
