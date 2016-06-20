// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Storage/Variant>
#include <Mib/String/Mixed>

#include "../../Type/Test/Test_TypeTraits_TestTypes.h"


namespace
{

	struct COne {};
	struct CTwo {};
	struct CThree {};
	struct CFour {};

	typedef NMib::NContainer::TCStreamableVariant<int, COne, 0> CVarA;
	typedef NMib::NContainer::TCStreamableVariant<int, CTwo, 0> CVarB;

	int operator * (CVarA _A, int _B)
	{
		return _B;
	}

	int operator * (CVarB _A, int _B)
	{
		return _B;
	}

	int operator * (CThree _A, CFour _B)
	{
		return 0;
	}

	class CVariant_Tests : public NMib::NTest::CTest
	{
	public:

		class CTestWithManyInit
		{
		public:
			CTestWithManyInit(int, fp32, fp64)
			{
			}
		};
		enum EStreamID
		{
			EStreamID_void,
			EStreamID_Vector,
			EStreamID_fp32,
			EStreamID_fp64,
			EStreamID_int32,
			EStreamID_int64,
		};

		struct CTest0 { };
		struct CTest1 { };
		struct CTest2 { };
		struct CTest3 { };
		struct CTest4 { };
		struct CTest5 { };
		struct CTest6 { };
		struct CTest7 { };
		struct CTest8 { };
		struct CTest9 { };
		struct CTest10 { };
		struct CTest11 { };
		struct CTest12 { };
		struct CTest13 { };
		struct CTest14 { };
		struct CTest15 { };
		struct CTest16 { };
		struct CTest17 { };
		struct CTest18 { };
		struct CTest19 { };
		struct CTest20 { };
		struct CTest21 { };
		struct CTest22 { };
		struct CTest23 { };

		void f_DoTests()
		{
				
			{
				NMib::NContainer::TCVariant
					<
						CTest0
						, CTest1
						, CTest2
						, CTest3
						, CTest4
						, CTest5
						, CTest6
						, CTest7
#if DMibContainerVariantMany > 0
						, CTest8
						, CTest9
						, CTest10
						, CTest11
						, CTest12
						, CTest13
						, CTest14
						, CTest15
#if DMibContainerVariantMany > 1
						, CTest16
						, CTest17
						, CTest18
						, CTest19
						, CTest20
						, CTest21
						, CTest22
						, CTest23
#endif
#endif
					>
					TestMany
				;

				TestMany = CTest0();
				TestMany = CTest1();
				TestMany = CTest2();
				TestMany = CTest3();
				TestMany = CTest4();
				TestMany = CTest5();
				TestMany = CTest6();
				TestMany = CTest7();
#if DMibContainerVariantMany
				TestMany = CTest8();
				TestMany = CTest9();
				TestMany = CTest10();
				TestMany = CTest11();
				TestMany = CTest12();
				TestMany = CTest13();
				TestMany = CTest14();
				TestMany = CTest15();
#if DMibContainerVariantMany > 1
				TestMany = CTest16();
				TestMany = CTest17();
				TestMany = CTest18();
				TestMany = CTest19();
				TestMany = CTest20();
				TestMany = CTest21();
				TestMany = CTest22();
				TestMany = CTest23();
#endif
#endif
			}
			{
				CTestBase Test; 
				NMib::NContainer::TCVariant<void, CTestRRef> Variant(NMib::fg_Move(Test));
				auto &&test = Variant.f_Set<1>(NMib::fg_Move(Test));
				int ntheounheo = 0;
			}
			{
				CTestWithManyInit Test(6, 7, 8); 
				NMib::NContainer::TCVariant<void, CTestWithManyInit &&> Variant(NMib::fg_Move(Test));
				NMib::NContainer::TCVariant<void, CTestWithManyInit> Variant2(5, 6, 7);
			}

			NMib::NContainer::TCVector<int32> Test;
			Test.f_Insert(40);
			Test.f_Insert(41);
			Test.f_Insert(42);
			Test.f_Insert(43);

			NMib::NContainer::TCVector<int32> Test2 = Test;


			typedef NMib::NContainer::TCStreamableVariant<int, void, 0, NMib::NContainer::TCVector<int>, 1, fp32, 2, fp64, 3, int32, 4, int64, 5> CManyVariant3;
			
			typedef NMib::NContainer::TCVariant<void, NMib::NContainer::TCVector<int>, fp32, fp64, int32, int64> CManyVariant;
			typedef NMib::NContainer::TCVariant<void, NMib::NContainer::TCVector<int>, fp32, fp64, int32, int64, const ch8 *> CManyVariant2;
			CManyVariant ManyVariant;
			CManyVariant ManyVariantVoid;
			ManyVariant = fp128(fp64(0.0));

			{
				CManyVariant3 Test0 = Test;
				CManyVariant3 Test1 = Test0;
				CManyVariant3 Test2 = Test0;
			}

			CManyVariant3 ManyVariantHula(fp128(fp64(0.0)));

			CManyVariant ManyVariant2 = Test;

			CTestBase Test22; 
			CTestCVRef Testing22(Test22);
			
			CManyVariant2 ManyVariant3 = ManyVariant2;

			CManyVariant2 ManyVariant33 = NMib::fg_Const(ManyVariant2);

			CManyVariant2 ManyVariant34 = NMib::fg_Const(ManyVariant33);

			CManyVariant ManyVariant4 = NMib::fg_Move(ManyVariant2);

			CManyVariant2 ManyVariant5 = NMib::fg_Move(ManyVariant3);

			NMib::NContainer::TCVariant<const int> TestVarConst = 3;

			auto &Test32 = TestVarConst.f_Get<0>();
			auto &Test33 = TestVarConst.f_GetAsType<const int>();

			int notehuenothu = 0;

			NMib::NContainer::TCVariant<CTestWithManyInit> VarManyInit(0,0,0);
			NMib::NContainer::TCVariant<CTestWithManyInit> VarManyInit2(2.5,fp64(3.5),fp32(3.5f));

			NMib::NContainer::TCMap<NMib::NStr::CStr, NMib::NStr::CStr> TestMap;

			NMib::NStr::CStr StrTest = "Testing\nonteuhneotuh\nTNOehunoetuh\nnotheuneth";
			NMib::NStr::CWStr StrTest2 = StrTest;
			NMib::NStr::CUStr StrTest3 = StrTest;
			NMib::NStr::CMStrDeprecated MixedStr = StrTest2;
			NMib::NStr::CStr StrTestUTF8 = MixedStr;
			NMib::NStr::CStr Empty;

			NMib::NStr::CFStr256 FStrTest = "Testing\nonteuhneotuh\nTNOehunoetuh\nnotheuneth";
			NMib::NStr::CFWStr256 FStrTest2 = FStrTest;
			NMib::NStr::CFUStr256 FStrTest3 = FStrTest;
			NMib::NStr::CFStr256 FStrTestUTF8 = MixedStr;
			NMib::NStr::CFStr256 FEmpty;

			NMib::NRegistry::CRegistryPreserve_CStr TestingReg;
			TestingReg.f_SetValue("ntaoheunh/notehunoethu", "anoetuhoanehu");
			TestingReg.f_SetValue("ntaoheunh/notheuntoehu", "anoetuhoanehu");
			TestingReg.f_SetValue("ntaoheunh", "anoetuhoanehu");
			TestingReg.f_SetValue("notehunoethu/nnotehetuh", "anoetuhoanehu");

			TestMap["00555"] = "noteuhoenu";
			TestMap["00655"] = "noteuhoeeeeeenu";

			TestMap["00855"] = "noteuhoen4u5";

			NMib::NContainer::TCMap<NMib::NStr::CStr, NMib::NContainer::TCMap<NMib::NStr::CStr, NMib::NStr::CStr>> TestMapMap;
			TestMapMap["Heeuhu"] = TestMap;

			typedef NMib::NContainer::TCStreamableFixedVariant<EStreamID, void, NMib::NContainer::TCVector<int32>, fp32, fp64, int32, int64> CManyVariantStreamable;

			CManyVariantStreamable ManyVariantStream = Test2;

			NMib::NStream::CBinaryStreamMemory<> Stream;
			Stream << ManyVariantStream;
			Stream.f_SetPosition(0);

			CManyVariantStreamable ManyVariantRead;
			Stream >> ManyVariantRead;

			NMib::NMisc::fg_ForEach(ManyVariantRead.f_Get<EStreamID_Vector>(), [&] (int32 _Value)
			{
				//DMibDTrace("{}\r\n", _Value);
			});

			NMib::NContainer::TCVariant<void, uint8> EmptyVariant;

			CTest2DArray2V Blaha;
			NMib::fg_CallDestructor(Blaha);
//			Blaha.~CTest2DArray2V();
/*			{NMib::NContainer::TCVariant<CTest2DArray2> Variant;}
			{NMib::NContainer::TCVariant<CTest2DArray2C> Variant;}
			{NMib::NContainer::TCVariant<CTest2DArray2V> Variant;}
			{NMib::NContainer::TCVariant<CTest2DArray2CV> Variant;}*/

//			static_assert(NMib::NTraits::TCIsConstructorCallableWith<NMib::NContainer::TCVariant<FFunc0RRef>::TCTypeFromMember<0>::CType, void (decltype(NMib::fg_Move(fsg_FFunc0)))>::mc_Value, "hehe");
			
	//		DMibDTrace("{}\r\n", sizeof(EmptyVariant));


#if 1
			{NMib::NContainer::TCVariant<CTestUnion> Variant;}
			{NMib::NContainer::TCVariant<CTestClass0> Variant;}
			{NMib::NContainer::TCVariant<CTestClass1> Variant;}
			{NMib::NContainer::TCVariant<CTestStruct0> Variant;}
			{NMib::NContainer::TCVariant<CTestStruct1> Variant;}
			{NMib::NContainer::TCVariant<const CTestClass0> Variant;}
			{NMib::NContainer::TCVariant<const CTestClass1> Variant;}
			{NMib::NContainer::TCVariant<const CTestStruct0> Variant;}
			{NMib::NContainer::TCVariant<const CTestStruct1> Variant;}
			{NMib::NContainer::TCVariant<volatile CTestClass0> Variant;}
			{NMib::NContainer::TCVariant<volatile CTestClass1> Variant;}
			{NMib::NContainer::TCVariant<volatile CTestStruct0> Variant;}
			{NMib::NContainer::TCVariant<volatile CTestStruct1> Variant;}
			{NMib::NContainer::TCVariant<const volatile CTestClass0> Variant;}
			{NMib::NContainer::TCVariant<const volatile CTestClass1> Variant;}
			{NMib::NContainer::TCVariant<const volatile CTestStruct0> Variant;}
			{NMib::NContainer::TCVariant<const volatile CTestStruct1> Variant;}
			{NMib::NContainer::TCVariant<ETestEnum> Variant;}
			{NMib::NContainer::TCVariant<int> Variant;}
			{NMib::NContainer::TCVariant<CTestClass> Variant;}
			{NMib::NContainer::TCVariant<CTestC> Variant;}
			{NMib::NContainer::TCVariant<CTestV> Variant;}
			{NMib::NContainer::TCVariant<CTestCV> Variant;}
			{NMib::NContainer::TCVariant<CTestPtr> Variant;}
			{NMib::NContainer::TCVariant<CTestCPtr> Variant;}
			{NMib::NContainer::TCVariant<CTestVPtr> Variant;}
			{NMib::NContainer::TCVariant<CTestCVPtr> Variant;}
			{NMib::NContainer::TCVariant<CTestPtrC> Variant;}
			{NMib::NContainer::TCVariant<CTestCPtrC> Variant;}
			{NMib::NContainer::TCVariant<CTestVPtrC> Variant;}
			{NMib::NContainer::TCVariant<CTestCVPtrC> Variant;}
			{NMib::NContainer::TCVariant<CTestPtrV> Variant;}
			{NMib::NContainer::TCVariant<CTestCPtrV> Variant;}
			{NMib::NContainer::TCVariant<CTestVPtrV> Variant;}
			{NMib::NContainer::TCVariant<CTestCVPtrV> Variant;}
			{NMib::NContainer::TCVariant<CTestPtrCV> Variant;}
			{NMib::NContainer::TCVariant<CTestCPtrCV> Variant;}
			{NMib::NContainer::TCVariant<CTestVPtrCV> Variant;}
			{NMib::NContainer::TCVariant<CTestCVPtrCV> Variant;}
			{CTestBase Test; NMib::NContainer::TCVariant<CTestRef> Variant(Test);}
			{CTestBase Test; NMib::NContainer::TCVariant<CTestCRef> Variant(NMib::fg_Const(Test));}
			{CTestBase Test; NMib::NContainer::TCVariant<CTestVRef> Variant(NMib::fg_Volatile(Test));}
			{CTestBase Test; NMib::NContainer::TCVariant<CTestCVRef> Variant(NMib::fg_Volatile(NMib::fg_Const(Test)));}
			{CTestBase Test; NMib::NContainer::TCVariant<CTestRRef> Variant(NMib::fg_Move(Test));}
			{CTestBase Test; NMib::NContainer::TCVariant<CTestCRRef> Variant((CTestCRRef) NMib::fg_Move(Test));}
			{CTestBase Test; NMib::NContainer::TCVariant<CTestVRRef> Variant((CTestVRRef)NMib::fg_Move(Test));}
			{CTestBase Test; NMib::NContainer::TCVariant<CTestCVRRef> Variant((CTestCVRRef)NMib::fg_Move(Test));}
//			{NMib::NContainer::TCVariant<PFFunc0> Variant;}
//			{NMib::NContainer::TCVariant<PFFunc1> Variant;}
//			{NMib::NContainer::TCVariant<PFFunc2> Variant;}
#if !defined(DCompiler_MSVC) || DMibCompilerVersion >= 1700
//#ifndef DMibCompiler_GCC
			{NMib::NContainer::TCVariant<FFunc0Ref> Variant(fsg_FFunc0);}
			{NMib::NContainer::TCVariant<FFunc1Ref> Variant(fsg_FFunc1);}
			{NMib::NContainer::TCVariant<FFunc2Ref> Variant(fsg_FFunc2);}
			{NMib::NContainer::TCVariant<FFunc0RRef> Variant(NMib::fg_Move(fsg_FFunc0));}
			{NMib::NContainer::TCVariant<FFunc1RRef> Variant(NMib::fg_Move(fsg_FFunc1));}
			{NMib::NContainer::TCVariant<FFunc2RRef> Variant(NMib::fg_Move(fsg_FFunc2));}
//#endif
#endif
			{NMib::NContainer::TCVariant<FFunc0Ptr> Variant;}
			{NMib::NContainer::TCVariant<FFunc1Ptr> Variant;}
			{NMib::NContainer::TCVariant<FFunc2Ptr> Variant;}
			{NMib::NContainer::TCVariant<FFunc0PtrC> Variant;}
			{NMib::NContainer::TCVariant<FFunc1PtrC> Variant;}
			{NMib::NContainer::TCVariant<FFunc2PtrC> Variant;}
			{NMib::NContainer::TCVariant<FFunc0PtrV> Variant;}
			{NMib::NContainer::TCVariant<FFunc1PtrV> Variant;}
			{NMib::NContainer::TCVariant<FFunc2PtrV> Variant;}
			{NMib::NContainer::TCVariant<FFunc0PtrCV> Variant;}
			{NMib::NContainer::TCVariant<FFunc1PtrCV> Variant;}
			{NMib::NContainer::TCVariant<FFunc2PtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0Ptr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1Ptr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2Ptr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0PtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1PtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2PtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0PtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1PtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2PtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0PtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1PtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2PtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0CPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1CPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2CPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0CPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1CPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2CPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0CPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1CPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2CPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0CPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1CPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2CPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0VPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1VPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2VPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0VPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1VPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2VPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0VPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1VPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2VPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0VPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1VPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2VPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0CVPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1CVPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2CVPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0CVPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1CVPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2CVPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0CVPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1CVPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2CVPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0CVPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1CVPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2CVPtrCV> Variant;}
//			{NMib::NContainer::TCVariant<PFFunc0El> Variant;}
//			{NMib::NContainer::TCVariant<PFFunc1El> Variant;}
//			{NMib::NContainer::TCVariant<PFFunc2El> Variant;}
#if !defined(DCompiler_MSVC) || DMibCompilerVersion >= 1700
//#ifndef DMibCompiler_GCC
			{NMib::NContainer::TCVariant<FFunc0ElRef> Variant(fsg_FFunc0El);}
			{NMib::NContainer::TCVariant<FFunc1ElRef> Variant(fsg_FFunc1El);}
			{NMib::NContainer::TCVariant<FFunc2ElRef> Variant(fsg_FFunc2El);}
			{NMib::NContainer::TCVariant<FFunc0ElRRef> Variant(NMib::fg_Move(fsg_FFunc0El));}
			{NMib::NContainer::TCVariant<FFunc1ElRRef> Variant(NMib::fg_Move(fsg_FFunc1El));}
			{NMib::NContainer::TCVariant<FFunc2ElRRef> Variant(NMib::fg_Move(fsg_FFunc2El));}
//#endif
#endif
			{NMib::NContainer::TCVariant<FFunc0ElPtr> Variant;}
			{NMib::NContainer::TCVariant<FFunc1ElPtr> Variant;}
			{NMib::NContainer::TCVariant<FFunc2ElPtr> Variant;}
			{NMib::NContainer::TCVariant<FFunc0ElPtrC> Variant;}
			{NMib::NContainer::TCVariant<FFunc1ElPtrC> Variant;}
			{NMib::NContainer::TCVariant<FFunc2ElPtrC> Variant;}
			{NMib::NContainer::TCVariant<FFunc0ElPtrV> Variant;}
			{NMib::NContainer::TCVariant<FFunc1ElPtrV> Variant;}
			{NMib::NContainer::TCVariant<FFunc2ElPtrV> Variant;}
			{NMib::NContainer::TCVariant<FFunc0ElPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FFunc1ElPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FFunc2ElPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElCPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElCPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElCPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElCPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElCPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElCPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElCPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElCPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElCPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElCPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElCPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElCPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElVPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElVPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElVPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElVPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElVPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElVPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElVPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElVPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElVPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElVPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElVPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElVPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElCVPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElCVPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElCVPtr> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElCVPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElCVPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElCVPtrC> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElCVPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElCVPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElCVPtrV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc0ElCVPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc1ElCVPtrCV> Variant;}
			{NMib::NContainer::TCVariant<FMFunc2ElCVPtrCV> Variant;}
			{NMib::NContainer::TCVariant<CMPtr> Variant;}
			{NMib::NContainer::TCVariant<CMCPtr> Variant;}
			{NMib::NContainer::TCVariant<CMVPtr> Variant;}
			{NMib::NContainer::TCVariant<CMCVPtr> Variant;}
			{NMib::NContainer::TCVariant<CMPtrC> Variant;}
			{NMib::NContainer::TCVariant<CMCPtrC> Variant;}
			{NMib::NContainer::TCVariant<CMVPtrC> Variant;}
			{NMib::NContainer::TCVariant<CMCVPtrC> Variant;}
			{NMib::NContainer::TCVariant<CMPtrV> Variant;}
			{NMib::NContainer::TCVariant<CMCPtrV> Variant;}
			{NMib::NContainer::TCVariant<CMVPtrV> Variant;}
			{NMib::NContainer::TCVariant<CMCVPtrV> Variant;}
			{NMib::NContainer::TCVariant<CMPtrCV> Variant;}
			{NMib::NContainer::TCVariant<CMCPtrCV> Variant;}
			{NMib::NContainer::TCVariant<CMVPtrCV> Variant;}
			{NMib::NContainer::TCVariant<CMCVPtrCV> Variant;}
			{NMib::NContainer::TCVariant<CTestArray2> Variant;}
			{NMib::NContainer::TCVariant<CTestArray2C> Variant;}
			{NMib::NContainer::TCVariant<CTestArray2V> Variant;}
			{NMib::NContainer::TCVariant<CTestArray2CV> Variant;}
//			{NMib::NContainer::TCVariant<CTestArray> Variant;}
//			{NMib::NContainer::TCVariant<CTestArrayC> Variant;}
//			{NMib::NContainer::TCVariant<CTestArrayV> Variant;}
//			{NMib::NContainer::TCVariant<CTestArrayCV> Variant;}
			{NMib::NContainer::TCVariant<CTest2DArray2> Variant;}
			{NMib::NContainer::TCVariant<CTest2DArray2C> Variant;}
			{NMib::NContainer::TCVariant<CTest2DArray2V> Variant;}
			{NMib::NContainer::TCVariant<CTest2DArray2CV> Variant;}
//			{NMib::NContainer::TCVariant<CTest2DArray> Variant;}
//			{NMib::NContainer::TCVariant<CTest2DArrayC> Variant;}
//			{NMib::NContainer::TCVariant<CTest2DArrayV> Variant;}
//			{NMib::NContainer::TCVariant<CTest2DArrayCV> Variant;}
			{NMib::NContainer::TCVariant<CTest3DArray2> Variant;}
			{NMib::NContainer::TCVariant<CTest3DArray2C> Variant;}
			{NMib::NContainer::TCVariant<CTest3DArray2V> Variant;}
			{NMib::NContainer::TCVariant<CTest3DArray2CV> Variant;}
//			{NMib::NContainer::TCVariant<CTest3DArray> Variant;}
//			{NMib::NContainer::TCVariant<CTest3DArrayC> Variant;}
//			{NMib::NContainer::TCVariant<CTest3DArrayV> Variant;}
//			{NMib::NContainer::TCVariant<CTest3DArrayCV> Variant;}
			{NMib::NContainer::TCVariant<void *> Variant;}
			{NMib::NContainer::TCVariant<void> Variant;}
#endif

			if (0)
			{
				// This does not work... it's initialized as a char
				int Val = 5;
				NMib::NContainer::TCVariant<char, int const&> Var((int const&)Val);

				NMib::NContainer::TCVariant<char, int const&> const& VarRef = Var;

				struct CUtil
				{
					static void Do(char _V) {}
					static void Do(int const& _V) {}
				};


				int const& Ref = VarRef.f_Get<1>();
				CUtil::Do(VarRef.f_Get<1>());
			}

		}

	};

	DMibTestRegister(CVariant_Tests, Malterlib::Storage);
}

