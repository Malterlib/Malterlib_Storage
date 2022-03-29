// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Storage/Tuple>

#include "../../Type/Test/Test_TypeTraits_TestTypes.h"

namespace
{
	
	int32 g_MovedEmpty = 0;
	class CTuple_Tests : public NMib::NTest::CTest
	{
	public:

		class CTestWithManyInit
		{
		public:
			CTestWithManyInit(int, fp32, fp64)
			{
			}
		};
		
		class CEmpty
		{
		public:
			operator int ()
			{
				return -1;
			}
			operator int () const
			{
				return -2;
			}
			operator int () volatile
			{
				return -3;
			}
			operator int () const volatile
			{
				return -4;
			}
		};
		class CNonEmpty
		{
			uint8 m_Member;
		public:
			operator int ()
			{
				return -1;
			}
			operator int () const
			{
				return -2;
			}
			operator int () volatile
			{
				return -3;
			}
			operator int () const volatile
			{
				return -4;
			}
		};
		
		class CNonCopyableEmpty
		{
			CNonCopyableEmpty(CNonCopyableEmpty const &);
			CNonCopyableEmpty &operator =(CNonCopyableEmpty const &);
		public:
			CNonCopyableEmpty()
			{
			}
		};
		
		class CNonCopyable
		{
			uint8 m_Test;
			CNonCopyable(CNonCopyable const &);
			CNonCopyable &operator =(CNonCopyable const &);
		public:
			CNonCopyable()
			{
			}
		};
		

		class CEmpty0
		{
		};
		class CEmpty1
		{
		};
		class CEmpty2
		{
		};
		
		class CEmptyAll : CEmpty0, CEmpty1, CEmpty2
		{
		};

		class CMovableOnly
		{
			CMovableOnly(CMovableOnly const &);
			CMovableOnly &operator =(CMovableOnly const &);
		public:
			zint32 m_Moved;
			zint32 m_MovedFrom;
			CMovableOnly()
			{
			}
			CMovableOnly(CMovableOnly &&_Other) noexcept
			{
				++m_Moved;
				++_Other.m_MovedFrom;
			}
		};

		class CMovableOnlyExcept
		{
			CMovableOnlyExcept(CMovableOnlyExcept const &);
			CMovableOnlyExcept &operator =(CMovableOnlyExcept const &);
		public:
			zint32 m_Moved;
			zint32 m_MovedFrom;
			CMovableOnlyExcept()
			{
			}
			CMovableOnlyExcept(CMovableOnlyExcept &&_Other)
			{
				++m_Moved;
				++_Other.m_MovedFrom;
			}
		};
		
		class CMovableAssignOnly
		{
			CMovableAssignOnly(CMovableAssignOnly const &);
			CMovableAssignOnly &operator =(CMovableAssignOnly const &);
		public:
			zint32 m_Moved;
			zint32 m_MovedFrom;
			CMovableAssignOnly()
			{
			}
			CMovableAssignOnly &operator =(CMovableAssignOnly &&_Other) noexcept
			{
				++m_Moved;
				++_Other.m_MovedFrom;
				return *this;
			}
		};
		
		class CMovableAssignOnlyExcept
		{
			CMovableAssignOnlyExcept(CMovableAssignOnlyExcept const &);
			CMovableAssignOnlyExcept &operator =(CMovableAssignOnlyExcept const &);
		public:
			zint32 m_Moved;
			zint32 m_MovedFrom;
			CMovableAssignOnlyExcept()
			{
			}
			CMovableAssignOnlyExcept &operator =(CMovableAssignOnlyExcept &&_Other)
			{
				++m_Moved;
				++_Other.m_MovedFrom;
				return *this;
			}
		};
		
		class CMovableOnlyEmpty
		{
			CMovableOnlyEmpty(CMovableOnlyEmpty const &);
			CMovableOnlyEmpty &operator =(CMovableOnlyEmpty const &);
		public:
			CMovableOnlyEmpty()
			{
			}
			CMovableOnlyEmpty(CMovableOnlyEmpty &&_Other) noexcept
			{
				++g_MovedEmpty;
			}
		};

		class CMovableOnlyEmptyExcept
		{
			CMovableOnlyEmptyExcept(CMovableOnlyEmptyExcept const &);
			CMovableOnlyEmptyExcept &operator =(CMovableOnlyEmptyExcept const &);
		public:
			CMovableOnlyEmptyExcept()
			{
			}
			CMovableOnlyEmptyExcept(CMovableOnlyEmptyExcept &&_Other)
			{
				++g_MovedEmpty;
			}
		};
		
		class CMovableAssignOnlyEmpty
		{
			CMovableAssignOnlyEmpty(CMovableAssignOnlyEmpty const &);
			CMovableAssignOnlyEmpty &operator =(CMovableAssignOnlyEmpty const &);
		public:
			CMovableAssignOnlyEmpty()
			{
			}
			CMovableAssignOnlyEmpty &operator =(CMovableAssignOnlyEmpty &&_Other) noexcept
			{
				++g_MovedEmpty;
				return *this;
			}
		};
		
		class CMovableAssignOnlyEmptyExcept
		{
			CMovableAssignOnlyEmptyExcept(CMovableAssignOnlyEmptyExcept const &);
			CMovableAssignOnlyEmptyExcept &operator =(CMovableAssignOnlyEmptyExcept const &);
		public:
			CMovableAssignOnlyEmptyExcept()
			{
			}
			CMovableAssignOnlyEmptyExcept &operator =(CMovableAssignOnlyEmptyExcept &&_Other)
			{
				++g_MovedEmpty;
				return *this;
			}
		};
		
		struct CCompare
		{
			int m_Value;
			mutable zint32 m_nCompares;
			
			CCompare(int _Value)
				: m_Value(_Value)
			{
			}
			
			auto operator <=> (CCompare const &_Right) const
			{
				++m_nCompares;
				return m_Value <=> _Right.m_Value;
			}
			bool operator == (CCompare const &_Right) const
			{
				++m_nCompares;
				return m_Value == _Right.m_Value;
			}
		};
/*
		template <typename... t_PCTypes>
		inline_always
		NMib::NStorage::NPrivate::TCTupleImp<NMib::NMeta::TCIndices<0>, t_PCTypes &...>
		fg_TupleReferences2(t_PCTypes &..._Params) noexcept
		{
			return NMib::NStorage::NPrivate::TCTupleImp<NMib::NMeta::TCIndices<0>, t_PCTypes &...>(_Params...);
		}
*/		
		void f_DoTests()
		{
			using namespace NMib::NStorage;
			using namespace NMib;
			
			// Check sizes
			{
				TCTuple<> Tuple;
				static_assert(sizeof(Tuple) == 1);
			}
			{
				TCTuple<CEmpty> Tuple;
				static_assert(sizeof(Tuple) == 1);
			}
			{
#ifdef DMibContainer_TupleInternal
				TCTuple<CEmpty, CEmpty, CEmpty> Tuple;
				static_assert(sizeof(Tuple) == 1);
#endif
			}
			{
				TCTuple<CEmpty0, CEmpty1, CEmpty2> Tuple;
#ifndef DCompiler_MSVC
				static_assert(sizeof(Tuple) == 1);
#endif
			}
			{
#ifdef DMibContainer_TupleInternal
				TCTuple<TCTuple<CEmpty, CEmpty>, TCTuple<CEmpty, CEmpty>> Tuple;
				static_assert(sizeof(Tuple) == 1);
#endif
			}
			{
				TCTuple<CNonEmpty> Tuple;
				static_assert(sizeof(Tuple) == 1);
			}
			{
				TCTuple<CNonEmpty, CNonEmpty, CNonEmpty> Tuple;
				static_assert(sizeof(Tuple) == 3);
			}
			{
				TCTuple<TCTuple<CNonEmpty, CNonEmpty>, TCTuple<CNonEmpty, CNonEmpty>> Tuple;
				static_assert(sizeof(Tuple) == 4);
			}
			{
				TCTuple<TCTuple<TCTuple<CNonEmpty, CNonEmpty>, TCTuple<CNonEmpty, CNonEmpty>>, TCTuple<TCTuple<CNonEmpty, CNonEmpty>, TCTuple<CNonEmpty, CNonEmpty>>> Tuple;
				static_assert(sizeof(Tuple) == 8);
			}
			
			DMibTestSuite("General")
			{
				TCTuple<int> Tuple(2);
				DMibTest(DMibExpr(fg_Get<0>(Tuple)) == DMibExpr(2));

				TCTuple<int> Tuple_1;
				
#ifdef DMibContainer_TupleInternal
				static_assert(NMib::NStorage::NPrivate::TCTuple_IsAssignable<TCTuple<int> const &, TCTuple<int>>::mc_Value);
				static_assert(NMib::NStorage::NPrivate::TCTuple_IsAssignable<TCTuple<int> &&, TCTuple<int>>::mc_Value);
#endif
				Tuple_1 = Tuple;
				DMibTest(DMibExpr(Tuple_1) == DMibExpr(Tuple))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<0>(Tuple_1)) == DMibExpr(2));

				TCTuple<int> Tuple_2(Tuple);
				DMibTest(DMibExpr(Tuple_2) == DMibExpr(Tuple))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<0>(Tuple_2)) == DMibExpr(2));
				
				TCTuple<int, int> Tuple1(2, 5);
				DMibTest(DMibExpr(fg_Get<0>(Tuple1)) == DMibExpr(2));
				DMibTest(DMibExpr(fg_Get<1>(Tuple1)) == DMibExpr(5));

				TCTuple<int, int> Tuple1_1;
				Tuple1_1 = Tuple1;
				DMibTest(DMibExpr(Tuple1_1) == DMibExpr(Tuple1))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<0>(Tuple1_1)) == DMibExpr(2));
				DMibTest(DMibExpr(fg_Get<1>(Tuple1_1)) == DMibExpr(5));

				TCTuple<int, int> Tuple1_2(Tuple1);
				DMibTest(DMibExpr(Tuple1_2) == DMibExpr(Tuple1))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<0>(Tuple1_2)) == DMibExpr(2));
				DMibTest(DMibExpr(fg_Get<1>(Tuple1_2)) == DMibExpr(5));
				
				TCTuple<int, CEmpty> Tuple2(2, fg_Default());
				DMibTest(DMibExpr(fg_Get<0>(Tuple2)) == DMibExpr(2));
				DMibTest(DMibExpr(fg_Get<1>(Tuple2)) == DMibExpr(-1))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_Const(Tuple2))) == DMibExpr(-2))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_Volatile(Tuple2))) == DMibExpr(-3))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_ConstVolatile(Tuple2))) == DMibExpr(-4))(ETestFlag_NoValues);
				
				TCTuple<int, CEmpty> Tuple2_1;
				Tuple2_1 = Tuple2;
				DMibTest(DMibExpr(Tuple2_1) == DMibExpr(Tuple2))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<0>(Tuple2_1)) == DMibExpr(2));
				DMibTest(DMibExpr(fg_Get<1>(Tuple2_1)) == DMibExpr(-1))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_Const(Tuple2_1))) == DMibExpr(-2))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_Volatile(Tuple2_1))) == DMibExpr(-3))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_ConstVolatile(Tuple2_1))) == DMibExpr(-4))(ETestFlag_NoValues);
				
				TCTuple<int, CEmpty> Tuple2_2(Tuple2);
				DMibTest(DMibExpr(Tuple2_2) == DMibExpr(Tuple2))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<0>(Tuple2_2)) == DMibExpr(2));
				DMibTest(DMibExpr(fg_Get<1>(Tuple2_2)) == DMibExpr(-1))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_Const(Tuple2_2))) == DMibExpr(-2))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_Volatile(Tuple2_2))) == DMibExpr(-3))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_ConstVolatile(Tuple2_2))) == DMibExpr(-4))(ETestFlag_NoValues);
				
				TCTuple<int, CNonEmpty> Tuple3(2, fg_Default());
				DMibTest(DMibExpr(fg_Get<0>(Tuple3)) == DMibExpr(2));
				DMibTest(DMibExpr(fg_Get<1>(Tuple3)) == DMibExpr(-1))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_Const(Tuple3))) == DMibExpr(-2))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_Volatile(Tuple3))) == DMibExpr(-3))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_ConstVolatile(Tuple3))) == DMibExpr(-4))(ETestFlag_NoValues);

				TCTuple<int, CNonEmpty> Tuple3_1;
				Tuple3_1 = Tuple3;
				DMibTest(DMibExpr(Tuple3_1) == DMibExpr(Tuple3))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<0>(Tuple3_1)) == DMibExpr(2));
				DMibTest(DMibExpr(fg_Get<1>(Tuple3_1)) == DMibExpr(-1))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_Const(Tuple3_1))) == DMibExpr(-2))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_Volatile(Tuple3_1))) == DMibExpr(-3))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_ConstVolatile(Tuple3_1))) == DMibExpr(-4))(ETestFlag_NoValues);

				TCTuple<int, CNonEmpty> Tuple3_2(Tuple3);
				DMibTest(DMibExpr(Tuple3_2) == DMibExpr(Tuple3))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<0>(Tuple3_2)) == DMibExpr(2));
				DMibTest(DMibExpr(fg_Get<1>(Tuple3_2)) == DMibExpr(-1))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_Const(Tuple3_2))) == DMibExpr(-2))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_Volatile(Tuple3_2))) == DMibExpr(-3))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(fg_ConstVolatile(Tuple3_2))) == DMibExpr(-4))(ETestFlag_NoValues);
				
				TCTuple<int, CNonCopyableEmpty> TupleNonCopyEmpty(2, fg_Default());
				TCTuple<int, CNonCopyable> TupleNonCopy(2, fg_Default());

				static_assert(!NTraits::TCIsConstructorCallableWith<TCTuple<int, CNonCopyable>, void (TCTuple<int, CNonCopyable> const &)>::mc_Value);
				static_assert(!NTraits::TCIsConstructorCallableWith<TCTuple<int, CNonCopyableEmpty>, void (TCTuple<int, CNonCopyableEmpty> const &)>::mc_Value);
				static_assert(!NTraits::TCIsConstructorCallableWith<TCTuple<int, CNonCopyableEmpty>, void (TCTuple<int, CNonCopyableEmpty> const &)>::mc_Value);
				
#if defined(DMibContainer_TupleInternal)
				TCTuple<int, CMovableOnly> TupleMovable(2, fg_Default());
#else
				TCTuple<int, CMovableOnly> TupleMovable;
#endif
				TCTuple<int, CMovableOnly> TupleMovable2(fg_Move(TupleMovable));
				DMibTest(DMibExpr(fg_Get<1>(TupleMovable).m_Moved) == DMibExpr(0))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(TupleMovable).m_MovedFrom) == DMibExpr(1))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(TupleMovable2).m_Moved) == DMibExpr(1))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(TupleMovable2).m_MovedFrom) == DMibExpr(0))(ETestFlag_NoValues);

				fg_Get<1>(TupleMovable2); // Check that there are no hidden moves when getting a value
				fg_Get<1>(fg_Move(TupleMovable2)); // Check that there are no hidden moves when getting a value
				DMibTest(DMibExpr(fg_Get<1>(TupleMovable2).m_MovedFrom) == DMibExpr(0) && DMibExpr("Should not be moved"))(ETestFlag_NoValues);
				auto Moved = fg_Get<1>(fg_Move(TupleMovable2)); // Check that there are no hidden moves when getting a value
				DMibTest(DMibExpr(fg_Get<1>(TupleMovable2).m_MovedFrom) == DMibExpr(1) && DMibExpr("Should be moved"))(ETestFlag_NoValues);

				static_assert(!NTraits::TCIsConstructorCallableWith<TCTuple<int, CMovableOnly>, void (TCTuple<int, CMovableOnly> const &)>::mc_Value);
				static_assert(NTraits::TCIsConstructorNothrowCallableWith<TCTuple<int, CMovableOnly>, void (TCTuple<int, CMovableOnly> &&)>::mc_Value);
				static_assert(!NTraits::TCIsConstructorCallableWith<TCTuple<int, CMovableOnlyEmpty>, void (TCTuple<int, CMovableOnlyEmpty> const &)>::mc_Value);
				static_assert(NTraits::TCIsConstructorNothrowCallableWith<TCTuple<int, CMovableOnlyEmpty>, void (TCTuple<int, CMovableOnlyEmpty> &&)>::mc_Value);
				
				g_MovedEmpty = 0;
				TCTuple<int, CMovableOnlyEmpty> TupleMovableEmpty(2, fg_Default());
				DMibTest(DMibExpr(g_MovedEmpty) == DMibExpr(0));
				g_MovedEmpty = 0;
				TCTuple<int, CMovableOnlyEmpty> TupleMovableEmpty2(fg_Move(TupleMovableEmpty));
				DMibTest(DMibExpr(g_MovedEmpty) == DMibExpr(1));
				
				TCTuple<int, CMovableAssignOnly> TupleMovableAssign(2, fg_Default());
				TCTuple<int, CMovableAssignOnly> TupleMovableAssign2;
				TupleMovableAssign2 = fg_Move(TupleMovableAssign);
				DMibTest(DMibExpr(fg_Get<1>(TupleMovableAssign).m_Moved) == DMibExpr(0))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(TupleMovableAssign).m_MovedFrom) == DMibExpr(1))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(TupleMovableAssign2).m_Moved) == DMibExpr(1))(ETestFlag_NoValues);
				DMibTest(DMibExpr(fg_Get<1>(TupleMovableAssign2).m_MovedFrom) == DMibExpr(0))(ETestFlag_NoValues);
				
				static_assert(NTraits::TCIsOperatorNothrowCallableWith_Assign<int, void (int)>::mc_Value);
				static_assert(NTraits::TCIsOperatorNothrowCallableWith_Assign<CMovableAssignOnly, void (CMovableAssignOnly &&)>::mc_Value);
#ifdef DMibContainer_TupleInternal
				static_assert(!NTraits::TCIsOperatorCallableWith_Assign<TCTuple<int, CMovableAssignOnly>, void (TCTuple<int, CMovableAssignOnly> const &)>::mc_Value);
#endif
				static_assert(NTraits::TCIsOperatorNothrowCallableWith_Assign<TCTuple<int, CMovableAssignOnly>, void (TCTuple<int, CMovableAssignOnly> &&)>::mc_Value);
#ifdef DMibContainer_TupleInternal
				static_assert(!NTraits::TCIsOperatorCallableWith_Assign<TCTuple<int, CMovableAssignOnlyEmpty>, void (TCTuple<int, CMovableAssignOnlyEmpty> const &)>::mc_Value);
#endif
				static_assert(NTraits::TCIsOperatorNothrowCallableWith_Assign<TCTuple<int, CMovableAssignOnlyEmpty>, void (TCTuple<int, CMovableAssignOnlyEmpty> &&)>::mc_Value);

				static_assert(NTraits::TCIsOperatorCallableWith_Assign<TCTuple<int, CMovableAssignOnlyExcept>, void (TCTuple<int, CMovableAssignOnlyExcept> &&)>::mc_Value);
				static_assert(!NTraits::TCIsOperatorNothrowCallableWith_Assign<TCTuple<int, CMovableAssignOnlyExcept>, void (TCTuple<int, CMovableAssignOnlyExcept> &&)>::mc_Value);

				static_assert(NTraits::TCIsOperatorCallableWith_Assign<TCTuple<int, CMovableAssignOnlyEmptyExcept>, void (TCTuple<int, CMovableAssignOnlyEmptyExcept> &&)>::mc_Value);
				static_assert(!NTraits::TCIsOperatorNothrowCallableWith_Assign<TCTuple<int, CMovableAssignOnlyEmptyExcept>, void (TCTuple<int, CMovableAssignOnlyEmptyExcept> &&)>::mc_Value);

				static_assert(NTraits::TCIsConstructorCallableWith<TCTuple<int, CMovableOnlyExcept>, void (TCTuple<int, CMovableOnlyExcept> &&)>::mc_Value);
				static_assert(!NTraits::TCIsConstructorNothrowCallableWith<TCTuple<int, CMovableOnlyExcept>, void (TCTuple<int, CMovableOnlyExcept> &&)>::mc_Value);
				
				static_assert(NTraits::TCIsConstructorCallableWith<TCTuple<int, CMovableOnlyEmptyExcept>, void (TCTuple<int, CMovableOnlyEmptyExcept> &&)>::mc_Value);
				static_assert(!NTraits::TCIsConstructorNothrowCallableWith<TCTuple<int, CMovableOnlyEmptyExcept>, void (TCTuple<int, CMovableOnlyEmptyExcept> &&)>::mc_Value);
				
				g_MovedEmpty = 0;
				TCTuple<int, CMovableAssignOnlyEmpty> TupleMovableAssignEmpty(2, fg_Default());
				DMibTest(DMibExpr(g_MovedEmpty) == DMibExpr(0) && DMibExpr("Assign"));
				g_MovedEmpty = 0;
				TCTuple<int, CMovableAssignOnlyEmpty> TupleMovableAssignEmpty2;
				TupleMovableAssignEmpty2 = fg_Move(TupleMovableAssignEmpty);
				DMibTest(DMibExpr(g_MovedEmpty) == DMibExpr(1) && DMibExpr("Assign"));			

				// LValue reference
				static_assert(TCIsLValueReference<decltype(fg_Get<1>(Tuple2))>::mc_Value);
				static_assert(!TCIsConst<TCRemoveReference<decltype(fg_Get<1>(Tuple2))>::CType>::mc_Value);
				static_assert(!TCIsVolatile<TCRemoveReference<decltype(fg_Get<1>(Tuple2))>::CType>::mc_Value);
				
				static_assert(TCIsLValueReference<decltype(fg_Get<1>(fg_Const(Tuple2)))>::mc_Value);
				static_assert(TCIsConst<TCRemoveReference<decltype(fg_Get<1>(fg_Const(Tuple2)))>::CType>::mc_Value);
				static_assert(!TCIsVolatile<TCRemoveReference<decltype(fg_Get<1>(fg_Const(Tuple2)))>::CType>::mc_Value);
				
				static_assert(TCIsLValueReference<decltype(fg_Get<1>(fg_Volatile(Tuple2)))>::mc_Value);
				static_assert(!TCIsConst<TCRemoveReference<decltype(fg_Get<1>(fg_Volatile(Tuple2)))>::CType>::mc_Value);
				static_assert(TCIsVolatile<TCRemoveReference<decltype(fg_Get<1>(fg_Volatile(Tuple2)))>::CType>::mc_Value);
				
				static_assert(TCIsLValueReference<decltype(fg_Get<1>(fg_ConstVolatile(Tuple2)))>::mc_Value);
				static_assert(TCIsConst<TCRemoveReference<decltype(fg_Get<1>(fg_ConstVolatile(Tuple2)))>::CType>::mc_Value);
				static_assert(TCIsVolatile<TCRemoveReference<decltype(fg_Get<1>(fg_ConstVolatile(Tuple2)))>::CType>::mc_Value);

				// RValue reference
				static_assert(TCIsRValueReference<decltype(fg_Get<1>(fg_Move(Tuple2)))>::mc_Value);
				static_assert(!TCIsConst<TCRemoveReference<decltype(fg_Get<1>(fg_Move(Tuple2)))>::CType>::mc_Value);
				static_assert(!TCIsVolatile<TCRemoveReference<decltype(fg_Get<1>(fg_Move(Tuple2)))>::CType>::mc_Value);
				
				static_assert(TCIsRValueReference<decltype(fg_Get<1>(fg_Move(fg_Const(Tuple2))))>::mc_Value);
				static_assert(TCIsConst<TCRemoveReference<decltype(fg_Get<1>(fg_Move(fg_Const(Tuple2))))>::CType>::mc_Value);
				static_assert(!TCIsVolatile<TCRemoveReference<decltype(fg_Get<1>(fg_Move(fg_Const(Tuple2))))>::CType>::mc_Value);
				
				static_assert(TCIsRValueReference<decltype(fg_Get<1>(fg_Move(fg_Volatile(Tuple2))))>::mc_Value);
				static_assert(!TCIsConst<TCRemoveReference<decltype(fg_Get<1>(fg_Move(fg_Volatile(Tuple2))))>::CType>::mc_Value);
				static_assert(TCIsVolatile<TCRemoveReference<decltype(fg_Get<1>(fg_Move(fg_Volatile(Tuple2))))>::CType>::mc_Value);
				
				static_assert(TCIsRValueReference<decltype(fg_Get<1>(fg_Move(fg_ConstVolatile(Tuple2))))>::mc_Value);
				static_assert(TCIsConst<TCRemoveReference<decltype(fg_Get<1>(fg_Move(fg_ConstVolatile(Tuple2))))>::CType>::mc_Value);
				static_assert(TCIsVolatile<TCRemoveReference<decltype(fg_Get<1>(fg_Move(fg_ConstVolatile(Tuple2))))>::CType>::mc_Value);

				// Check that all get paths compile
				fg_Get<1>(Tuple2);
				fg_Get<1>(fg_Const(Tuple2));
				fg_Get<1>(fg_Volatile(Tuple2));
				fg_Get<1>(fg_ConstVolatile(Tuple2));

				fg_Get<1>(fg_Move(Tuple2));
				fg_Get<1>(fg_MoveAllowConst(fg_Const(Tuple2)));
				fg_Get<1>(fg_Move(fg_Volatile(Tuple2)));
				fg_Get<1>(fg_MoveAllowConst(fg_ConstVolatile(Tuple2)));

				fg_Get<1>(Tuple3);
				fg_Get<1>(fg_Const(Tuple3));
				fg_Get<1>(fg_Volatile(Tuple3));
				fg_Get<1>(fg_ConstVolatile(Tuple3));
				
				fg_Get<1>(fg_Move(Tuple3));
				fg_Get<1>(fg_MoveAllowConst(fg_Const(Tuple3)));
				fg_Get<1>(fg_Move(fg_Volatile(Tuple3)));
				fg_Get<1>(fg_MoveAllowConst(fg_ConstVolatile(Tuple3)));
				
				
			};
			
			DMibTestSuite("Compare")
			{
				
				{
					DMibTestPath("Less than");
					{
						DMibTestPath("Differ first");
						TCTuple<CCompare, CCompare> Left(0, 1);
						TCTuple<CCompare, CCompare> Right(1, 0);
						
						DMibTest(DMibExpr(Left) < DMibExpr(Right))(ETestFlag_NoValues);
						
						DMibTest(DMibExpr(fg_Get<0>(Left).m_nCompares) == DMibExpr(1));
						DMibTest(DMibExpr(fg_Get<0>(Right).m_nCompares) == DMibExpr(0));
						DMibTest(DMibExpr(fg_Get<1>(Left).m_nCompares) == DMibExpr(0));
						DMibTest(DMibExpr(fg_Get<1>(Right).m_nCompares) == DMibExpr(0));
					}
					{
						DMibTestPath("Differ second");
						TCTuple<CCompare, CCompare> Left(0, 0);
						TCTuple<CCompare, CCompare> Right(0, 1);

						DMibTest(DMibExpr(Left) < DMibExpr(Right))(ETestFlag_NoValues);
						
						DMibTest(DMibExpr(fg_Get<0>(Left).m_nCompares) == DMibExpr(1));
						DMibTest(DMibExpr(fg_Get<0>(Right).m_nCompares) == DMibExpr(0));
						DMibTest(DMibExpr(fg_Get<1>(Left).m_nCompares) == DMibExpr(1));
						DMibTest(DMibExpr(fg_Get<1>(Right).m_nCompares) == DMibExpr(0));
					}
					{
						DMibTestPath("Equals");
						TCTuple<CCompare, CCompare> Left(0, 0);
						TCTuple<CCompare, CCompare> Right(0, 0);
						
						DMibTest(!(DMibExpr(Left) < DMibExpr(Right)))(ETestFlag_NoValues);
						
						DMibTest(DMibExpr(fg_Get<0>(Left).m_nCompares) == DMibExpr(1));
						DMibTest(DMibExpr(fg_Get<0>(Right).m_nCompares) == DMibExpr(0));
						DMibTest(DMibExpr(fg_Get<1>(Left).m_nCompares) == DMibExpr(1));
#ifdef DMibContainer_TupleInternal
						DMibTest(DMibExpr(fg_Get<1>(Right).m_nCompares) == DMibExpr(0));
#endif
					}
				}
				{
					DMibTestPath("Equality");
					{
						DMibTestPath("Differ first");
						TCTuple<CCompare, CCompare> Left(0, 1);
						TCTuple<CCompare, CCompare> Right(1, 0);
						
						DMibTest(DMibExpr(Left) != DMibExpr(Right))(ETestFlag_NoValues);
						
						DMibTest(DMibExpr(fg_Get<0>(Left).m_nCompares) == DMibExpr(1));
						DMibTest(DMibExpr(fg_Get<0>(Right).m_nCompares) == DMibExpr(0));
						DMibTest(DMibExpr(fg_Get<1>(Left).m_nCompares) == DMibExpr(0));
						DMibTest(DMibExpr(fg_Get<1>(Right).m_nCompares) == DMibExpr(0));
					}
					{
						DMibTestPath("Differ second");
						TCTuple<CCompare, CCompare> Left(0, 0);
						TCTuple<CCompare, CCompare> Right(0, 1);
						
						DMibTest(DMibExpr(Left) != DMibExpr(Right))(ETestFlag_NoValues);
						
						DMibTest(DMibExpr(fg_Get<0>(Left).m_nCompares) == DMibExpr(1));
						DMibTest(DMibExpr(fg_Get<0>(Right).m_nCompares) == DMibExpr(0));
						DMibTest(DMibExpr(fg_Get<1>(Left).m_nCompares) == DMibExpr(1));
						DMibTest(DMibExpr(fg_Get<1>(Right).m_nCompares) == DMibExpr(0));
					}
					{
						DMibTestPath("Equals");
						TCTuple<CCompare, CCompare> Left(0, 0);
						TCTuple<CCompare, CCompare> Right(0, 0);
						
						DMibTest(DMibExpr(Left) == DMibExpr(Right))(ETestFlag_NoValues);
						
						DMibTest(DMibExpr(fg_Get<0>(Left).m_nCompares) == DMibExpr(1));
						DMibTest(DMibExpr(fg_Get<0>(Right).m_nCompares) == DMibExpr(0));
						DMibTest(DMibExpr(fg_Get<1>(Left).m_nCompares) == DMibExpr(1));
						DMibTest(DMibExpr(fg_Get<1>(Right).m_nCompares) == DMibExpr(0));
					}
				}
			};
			
			DMibTestSuite("Create")
			{
				
				int x = 5;
				
				TCTuple<int &&> TupleRValueRef(fg_Move(x));
				++x;
				DMibTest(DMibExpr(fg_Get<0>(TupleRValueRef)) == DMibExpr(6));
				
				TCTuple<int &&> TupleRValueRef2(fg_Move(TupleRValueRef));
				++x;
				DMibTest(DMibExpr(fg_Get<0>(TupleRValueRef2)) == DMibExpr(7));

				TCTuple<int &> TupleLValueRef(x);
				++x;
				DMibTest(DMibExpr(fg_Get<0>(TupleLValueRef)) == DMibExpr(8));
				
				TCTuple<int &> TupleLValueRef2(TupleLValueRef);
				++x;
				DMibTest(DMibExpr(fg_Get<0>(TupleLValueRef2)) == DMibExpr(9));
				
				auto MadeTuple = fg_Tuple(x);
				++x;
				DMibTest(DMibExpr(fg_Get<0>(MadeTuple)) == DMibExpr(9));
				
				auto MadeTuple2 = fg_TupleReferences(x);
				++x;
				DMibTest(DMibExpr(fg_Get<0>(MadeTuple2)) == DMibExpr(11));
				
				auto MadeTuple3 = fg_TuplePerfectForward(fg_Move(x));
				static_assert(NMib::NTraits::TCIsSame<decltype(MadeTuple3), TCTuple<int &&>>::mc_Value);
				++x;
				int &&MadeTuple3Value = fg_GetForward<0>(fg_Move(MadeTuple3));
				DMibTest(DMibExpr(MadeTuple3Value) == DMibExpr(12));
				
			};
			
			
			DMibTestSuite("Concatenate")
			{

				int x = 5;
				int x2 = 6;
				
				TCTuple<int &&> TupleRValueRef(fg_Move(x));
				TCTuple<int &> TupleLValueRef(x2);
				TCTuple<int> Tuple(7);
				
				auto Concatenated0 = fg_TupleConcatenate(Tuple);
				DMibTest(DMibExpr(fg_Get<0>(Concatenated0)) == DMibExpr(7));
				static_assert(NMib::NTraits::TCIsSame<decltype(Concatenated0), TCTuple<int>>::mc_Value);

				auto Concatenated1 = fg_TupleConcatenate(Tuple, Tuple);
				DMibTest(DMibExpr(fg_Get<0>(Concatenated1)) == DMibExpr(7));
				DMibTest(DMibExpr(fg_Get<1>(Concatenated1)) == DMibExpr(7));
				static_assert(NMib::NTraits::TCIsSame<decltype(Concatenated1), TCTuple<int, int>>::mc_Value);

				auto Concatenated2 = fg_TupleConcatenate(TupleLValueRef, TupleLValueRef);
				DMibTest(DMibExpr(fg_Get<0>(Concatenated2)) == DMibExpr(6));
				DMibTest(DMibExpr(fg_Get<1>(Concatenated2)) == DMibExpr(6));
				static_assert(NMib::NTraits::TCIsSame<decltype(Concatenated2), TCTuple<int &, int &>>::mc_Value);
				
				auto Concatenated3 = fg_TupleConcatenate(Tuple, TupleLValueRef);
				DMibTest(DMibExpr(fg_Get<0>(Concatenated3)) == DMibExpr(7));
				DMibTest(DMibExpr(fg_Get<1>(Concatenated3)) == DMibExpr(6));
				static_assert(NMib::NTraits::TCIsSame<decltype(Concatenated3), TCTuple<int, int &>>::mc_Value);
				
				auto Concatenated4 = fg_TupleConcatenate(Tuple, fg_Move(TupleLValueRef));
				DMibTest(DMibExpr(fg_Get<0>(Concatenated4)) == DMibExpr(7));
				DMibTest(DMibExpr(fg_Get<1>(Concatenated4)) == DMibExpr(6));
				static_assert(NMib::NTraits::TCIsSame<decltype(Concatenated4), TCTuple<int, int &>>::mc_Value);

				auto Concatenated5 = fg_TupleConcatenate(Tuple, fg_Move(TupleRValueRef));
				DMibTest(DMibExpr(fg_Get<0>(Concatenated5)) == DMibExpr(7));
				DMibTest(DMibExpr(fg_Get<1>(Concatenated5)) == DMibExpr(5));
				static_assert(NMib::NTraits::TCIsSame<decltype(Concatenated5), TCTuple<int, int &&>>::mc_Value);

				auto Concatenated6 = fg_TupleConcatenate(Tuple, fg_Move(TupleLValueRef));
				DMibTest(DMibExpr(fg_Get<0>(Concatenated6)) == DMibExpr(7));
				DMibTest(DMibExpr(fg_Get<1>(Concatenated6)) == DMibExpr(6));
				static_assert(NMib::NTraits::TCIsSame<decltype(Concatenated6), TCTuple<int, int &>>::mc_Value);

				auto Concatenated7 = fg_TupleConcatenate(Tuple, fg_Move(TupleLValueRef), fg_Move(TupleRValueRef));
				DMibTest(DMibExpr(fg_Get<0>(Concatenated7)) == DMibExpr(7));
				DMibTest(DMibExpr(fg_Get<1>(Concatenated7)) == DMibExpr(6));
				DMibTest(DMibExpr(fg_Get<2>(Concatenated7)) == DMibExpr(5));
				static_assert(NMib::NTraits::TCIsSame<decltype(Concatenated7), TCTuple<int, int &, int &&>>::mc_Value);
				
			};
			
			{NMib::NStorage::TCTuple<CTestUnion> Tuple;}
			{NMib::NStorage::TCTuple<CTestClass0> Tuple;}
			{NMib::NStorage::TCTuple<CTestClass1> Tuple;}
			{NMib::NStorage::TCTuple<CTestStruct0> Tuple;}
			{NMib::NStorage::TCTuple<CTestStruct1> Tuple;}
			{NMib::NStorage::TCTuple<const CTestClass0> Tuple;}
			{NMib::NStorage::TCTuple<const CTestClass1> Tuple;}
			{NMib::NStorage::TCTuple<const CTestStruct0> Tuple;}
			{NMib::NStorage::TCTuple<const CTestStruct1> Tuple;}
			{NMib::NStorage::TCTuple<volatile CTestClass0> Tuple;}
			{NMib::NStorage::TCTuple<volatile CTestClass1> Tuple;}
			{NMib::NStorage::TCTuple<volatile CTestStruct0> Tuple;}
			{NMib::NStorage::TCTuple<volatile CTestStruct1> Tuple;}
			{NMib::NStorage::TCTuple<const volatile CTestClass0> Tuple;}
			{NMib::NStorage::TCTuple<const volatile CTestClass1> Tuple;}
			{NMib::NStorage::TCTuple<const volatile CTestStruct0> Tuple;}
			{NMib::NStorage::TCTuple<const volatile CTestStruct1> Tuple;}
			{NMib::NStorage::TCTuple<ETestEnum> Tuple;}
			{NMib::NStorage::TCTuple<int> Tuple;}
			{NMib::NStorage::TCTuple<CTestClass> Tuple;}
			{NMib::NStorage::TCTuple<CTestC> Tuple;}
			{NMib::NStorage::TCTuple<CTestPtr> Tuple;}
			{NMib::NStorage::TCTuple<CTestCPtr> Tuple;}
			{NMib::NStorage::TCTuple<CTestPtrC> Tuple;}
			{NMib::NStorage::TCTuple<CTestCPtrC> Tuple;}
			{CTestBase Test; NMib::NStorage::TCTuple<CTestRef> Variant(Test);}
			{CTestBase Test; NMib::NStorage::TCTuple<CTestCRef> Variant(Test);}
			{CTestBase Test; NMib::NStorage::TCTuple<CTestRRef> Variant(NMib::fg_Move(Test));}
			{CTestBase Test; NMib::NStorage::TCTuple<CTestCRRef> Variant(NMib::fg_Move(Test));}
//			{NMib::NStorage::TCTuple<PFFunc0> Tuple;}
//			{NMib::NStorage::TCTuple<PFFunc1> Tuple;}
//			{NMib::NStorage::TCTuple<PFFunc2> Tuple;}
			{NMib::NStorage::TCTuple<FFunc0Ref> Variant(fsg_FFunc0);}
			{NMib::NStorage::TCTuple<FFunc1Ref> Variant(fsg_FFunc1);}
			{NMib::NStorage::TCTuple<FFunc2Ref> Variant(fsg_FFunc2);}
#ifdef DMibContainer_TupleInternal
			{NMib::NStorage::TCTuple<FFunc0RRef> Variant(NMib::fg_Move(fsg_FFunc0));}
			{NMib::NStorage::TCTuple<FFunc1RRef> Variant(NMib::fg_Move(fsg_FFunc1));}
			{NMib::NStorage::TCTuple<FFunc2RRef> Variant(NMib::fg_Move(fsg_FFunc2));}
#endif
			{NMib::NStorage::TCTuple<FFunc0Ptr> Tuple;}
			{NMib::NStorage::TCTuple<FFunc1Ptr> Tuple;}
			{NMib::NStorage::TCTuple<FFunc2Ptr> Tuple;}
			{NMib::NStorage::TCTuple<FFunc0PtrC> Tuple;}
			{NMib::NStorage::TCTuple<FFunc1PtrC> Tuple;}
			{NMib::NStorage::TCTuple<FFunc2PtrC> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc0Ptr> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc1Ptr> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc2Ptr> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc0PtrC> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc1PtrC> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc2PtrC> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc0CPtr> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc1CPtr> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc2CPtr> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc0CPtrC> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc1CPtrC> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc2CPtrC> Tuple;}
//			{NMib::NStorage::TCTuple<PFFunc0El> Tuple;}
//			{NMib::NStorage::TCTuple<PFFunc1El> Tuple;}
//			{NMib::NStorage::TCTuple<PFFunc2El> Tuple;}
			{NMib::NStorage::TCTuple<FFunc0ElRef> Variant(fsg_FFunc0El);}
			{NMib::NStorage::TCTuple<FFunc1ElRef> Variant(fsg_FFunc1El);}
			{NMib::NStorage::TCTuple<FFunc2ElRef> Variant(fsg_FFunc2El);}
#ifdef DMibContainer_TupleInternal
			{NMib::NStorage::TCTuple<FFunc0ElRRef> Variant(NMib::fg_Move(fsg_FFunc0El));}
			{NMib::NStorage::TCTuple<FFunc1ElRRef> Variant(NMib::fg_Move(fsg_FFunc1El));}
			{NMib::NStorage::TCTuple<FFunc2ElRRef> Variant(NMib::fg_Move(fsg_FFunc2El));}
#endif
			{NMib::NStorage::TCTuple<FFunc0ElPtr> Tuple;}
			{NMib::NStorage::TCTuple<FFunc1ElPtr> Tuple;}
			{NMib::NStorage::TCTuple<FFunc2ElPtr> Tuple;}
			{NMib::NStorage::TCTuple<FFunc0ElPtrC> Tuple;}
			{NMib::NStorage::TCTuple<FFunc1ElPtrC> Tuple;}
			{NMib::NStorage::TCTuple<FFunc2ElPtrC> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc0ElPtr> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc1ElPtr> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc2ElPtr> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc0ElPtrC> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc1ElPtrC> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc2ElPtrC> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc0ElCPtr> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc1ElCPtr> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc2ElCPtr> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc0ElCPtrC> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc1ElCPtrC> Tuple;}
			{NMib::NStorage::TCTuple<FMFunc2ElCPtrC> Tuple;}
			{NMib::NStorage::TCTuple<CMPtr> Tuple;}
			{NMib::NStorage::TCTuple<CMCPtr> Tuple;}
			{NMib::NStorage::TCTuple<CMPtrC> Tuple;}
			{NMib::NStorage::TCTuple<CMCPtrC> Tuple;}
#ifndef DCompiler_MSVC_Workaround
			{NMib::NStorage::TCTuple<CTestArray2> Tuple;}
			{NMib::NStorage::TCTuple<CTestArray2C> Tuple;}
#endif
//			{NMib::NStorage::TCTuple<CTestArray> Tuple;}
//			{NMib::NStorage::TCTuple<CTestArrayC> Tuple;}
#ifdef DMibContainer_TupleInternal
			{NMib::NStorage::TCTuple<CTest2DArray2> Tuple;}
			{NMib::NStorage::TCTuple<CTest2DArray2C> Tuple;}
#endif
//			{NMib::NStorage::TCTuple<CTest2DArray> Tuple;}
//			{NMib::NStorage::TCTuple<CTest2DArrayC> Tuple;}
#ifdef DMibContainer_TupleInternal
			{NMib::NStorage::TCTuple<CTest3DArray2> Tuple;}
			{NMib::NStorage::TCTuple<CTest3DArray2C> Tuple;}
#endif
//			{NMib::NStorage::TCTuple<CTest3DArray> Tuple;}
//			{NMib::NStorage::TCTuple<CTest3DArrayC> Tuple;}
			{NMib::NStorage::TCTuple<void *> Tuple;}
//			{NMib::NStorage::TCTuple<void> Tuple;}
		}
	};

	DMibTestRegister(CTuple_Tests, Malterlib::Storage);
}

