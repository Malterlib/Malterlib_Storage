// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Storage/Variant>
#include <Mib/String/Mixed>
#include <Mib/Numeric/fp128>

#include "../../Type/Test/Test_TypeTraits_TestTypes.h"


namespace
{
	struct COne {};
	struct CTwo {};
	struct CThree {};
	struct CFour {};

	typedef NMib::NStorage::TCStreamableVariant<int, NMib::NStorage::TCMember<COne, 0>> CVarA;
	typedef NMib::NStorage::TCStreamableVariant<int, NMib::NStorage::TCMember<CTwo, 0>> CVarB;

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

		void f_DoTests()
		{
			DMibTestSuite("General")
			{
				{
					NMib::NStorage::TCVariant
						<
							CTest0
							, CTest1
							, CTest2
							, CTest3
							, CTest4
							, CTest5
							, CTest6
							, CTest7
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
				}
				{
					CTestBase Test;
					NMib::NStorage::TCVariant<void, CTestRRef> Variant(NMib::fg_Move(Test));
					auto &&test = Variant.f_Set<1>(NMib::fg_Move(Test));
					int ntheounheo = 0;
				}
				{
					CTestWithManyInit Test(6, 7, 8);
					NMib::NStorage::TCVariant<void, CTestWithManyInit &&> Variant(NMib::fg_Move(Test));
					NMib::NStorage::TCVariant<void, CTestWithManyInit> Variant2(5, 6, 7);
				}

				NMib::NContainer::TCVector<int32> Test;
				Test.f_Insert(40);
				Test.f_Insert(41);
				Test.f_Insert(42);
				Test.f_Insert(43);

				NMib::NContainer::TCVector<int32> Test2 = Test;

				typedef NMib::NStorage::TCStreamableVariant
					<
						int32
						, NMib::NStorage::TCMember<void, int32(0)>
						, NMib::NStorage::TCMember<NMib::NContainer::TCVector<int>, int32(1)>
						, NMib::NStorage::TCMember<fp32, int32(2)>
						, NMib::NStorage::TCMember<fp64, int32(3)>
						, NMib::NStorage::TCMember<int32, int32(4)>
						, NMib::NStorage::TCMember<int64, int32(5)>
					>
					CManyVariant3
				;

				typedef NMib::NStorage::TCVariant<void, NMib::NContainer::TCVector<int>, fp32, fp64, int32, int64> CManyVariant;
				typedef NMib::NStorage::TCVariant<void, NMib::NContainer::TCVector<int>, fp32, fp64, int32, int64, const ch8 *> CManyVariant2;
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

				NMib::NStorage::TCVariant<const int> TestVarConst = 3;

				auto &Test32 = TestVarConst.f_Get<0>();
				auto &Test33 = TestVarConst.f_GetAsType<const int>();

				int notehuenothu = 0;

				NMib::NStorage::TCVariant<CTestWithManyInit> VarManyInit(0,0,0);
				NMib::NStorage::TCVariant<CTestWithManyInit> VarManyInit2(2.5,fp64(3.5),fp32(3.5f));

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

				NMib::NContainer::CRegistryPreserveWhitespace TestingReg;
				TestingReg.f_SetValue("ntaoheunh/notehunoethu", "anoetuhoanehu");
				TestingReg.f_SetValue("ntaoheunh/notheuntoehu", "anoetuhoanehu");
				TestingReg.f_SetValue("ntaoheunh", "anoetuhoanehu");
				TestingReg.f_SetValue("notehunoethu/nnotehetuh", "anoetuhoanehu");

				TestMap["00555"] = "noteuhoenu";
				TestMap["00655"] = "noteuhoeeeeeenu";

				TestMap["00855"] = "noteuhoen4u5";

				NMib::NContainer::TCMap<NMib::NStr::CStr, NMib::NContainer::TCMap<NMib::NStr::CStr, NMib::NStr::CStr>> TestMapMap;
				TestMapMap["Heeuhu"] = TestMap;

				typedef NMib::NStorage::TCStreamableFixedVariant<EStreamID, void, NMib::NContainer::TCVector<int32>, fp32, fp64, int32, int64> CManyVariantStreamable;

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

				NMib::NStorage::TCVariant<void, uint8> EmptyVariant;

				EmptyVariant = 5;

				NMib::NStorage::TCVariant<void, NMib::NStorage::TCVariant<void, uint8>, int> RecursiveVariant{EmptyVariant};

				RecursiveVariant = EmptyVariant;
				RecursiveVariant = NMib::fg_Move(EmptyVariant);

				DMibExpect(RecursiveVariant.f_Get<1>().f_Get<1>(), ==, 5);

				CTest2DArray2V Blaha;
				NMib::fg_CallDestructor(Blaha);
	//			Blaha.~CTest2DArray2V();
	/*			{NMib::NStorage::TCVariant<CTest2DArray2> Variant;}
				{NMib::NStorage::TCVariant<CTest2DArray2C> Variant;}
				{NMib::NStorage::TCVariant<CTest2DArray2V> Variant;}
				{NMib::NStorage::TCVariant<CTest2DArray2CV> Variant;}*/

	//			static_assert(NMib::NTraits::TCIsConstructorCallableWith<NMib::NStorage::TCVariant<FFunc0RRef>::TCTypeFromMember<0>, void (decltype(NMib::fg_Move(fsg_FFunc0)))>::mc_Value, "hehe");

		//		DMibDTrace("{}\r\n", sizeof(EmptyVariant));


	#if 1
				{NMib::NStorage::TCVariant<CTestUnion> Variant;}
				{NMib::NStorage::TCVariant<CTestClass0> Variant;}
				{NMib::NStorage::TCVariant<CTestClass1> Variant;}
				{NMib::NStorage::TCVariant<CTestStruct0> Variant;}
				{NMib::NStorage::TCVariant<CTestStruct1> Variant;}
				{NMib::NStorage::TCVariant<const CTestClass0> Variant;}
				{NMib::NStorage::TCVariant<const CTestClass1> Variant;}
				{NMib::NStorage::TCVariant<const CTestStruct0> Variant;}
				{NMib::NStorage::TCVariant<const CTestStruct1> Variant;}
				{NMib::NStorage::TCVariant<volatile CTestClass0> Variant;}
				{NMib::NStorage::TCVariant<volatile CTestClass1> Variant;}
				{NMib::NStorage::TCVariant<volatile CTestStruct0> Variant;}
				{NMib::NStorage::TCVariant<volatile CTestStruct1> Variant;}
				{NMib::NStorage::TCVariant<const volatile CTestClass0> Variant;}
				{NMib::NStorage::TCVariant<const volatile CTestClass1> Variant;}
				{NMib::NStorage::TCVariant<const volatile CTestStruct0> Variant;}
				{NMib::NStorage::TCVariant<const volatile CTestStruct1> Variant;}
				{NMib::NStorage::TCVariant<ETestEnum> Variant;}
				{NMib::NStorage::TCVariant<int> Variant;}
				{NMib::NStorage::TCVariant<CTestClass> Variant;}
				{NMib::NStorage::TCVariant<CTestC> Variant;}
				{NMib::NStorage::TCVariant<CTestV> Variant;}
				{NMib::NStorage::TCVariant<CTestCV> Variant;}
				{NMib::NStorage::TCVariant<CTestPtr> Variant;}
				{NMib::NStorage::TCVariant<CTestCPtr> Variant;}
				{NMib::NStorage::TCVariant<CTestVPtr> Variant;}
				{NMib::NStorage::TCVariant<CTestCVPtr> Variant;}
				{NMib::NStorage::TCVariant<CTestPtrC> Variant;}
				{NMib::NStorage::TCVariant<CTestCPtrC> Variant;}
				{NMib::NStorage::TCVariant<CTestVPtrC> Variant;}
				{NMib::NStorage::TCVariant<CTestCVPtrC> Variant;}
				{NMib::NStorage::TCVariant<CTestPtrV> Variant;}
				{NMib::NStorage::TCVariant<CTestCPtrV> Variant;}
				{NMib::NStorage::TCVariant<CTestVPtrV> Variant;}
				{NMib::NStorage::TCVariant<CTestCVPtrV> Variant;}
				{NMib::NStorage::TCVariant<CTestPtrCV> Variant;}
				{NMib::NStorage::TCVariant<CTestCPtrCV> Variant;}
				{NMib::NStorage::TCVariant<CTestVPtrCV> Variant;}
				{NMib::NStorage::TCVariant<CTestCVPtrCV> Variant;}
				{CTestBase Test; NMib::NStorage::TCVariant<CTestRef> Variant(Test);}
				{CTestBase Test; NMib::NStorage::TCVariant<CTestCRef> Variant(NMib::fg_Const(Test));}
				{CTestBase Test; NMib::NStorage::TCVariant<CTestVRef> Variant(NMib::fg_Volatile(Test));}
				{CTestBase Test; NMib::NStorage::TCVariant<CTestCVRef> Variant(NMib::fg_Volatile(NMib::fg_Const(Test)));}
				{CTestBase Test; NMib::NStorage::TCVariant<CTestRRef> Variant(NMib::fg_Move(Test));}
				{CTestBase Test; NMib::NStorage::TCVariant<CTestCRRef> Variant((CTestCRRef) NMib::fg_Move(Test));}
				{CTestBase Test; NMib::NStorage::TCVariant<CTestVRRef> Variant((CTestVRRef)NMib::fg_Move(Test));}
				{CTestBase Test; NMib::NStorage::TCVariant<CTestCVRRef> Variant((CTestCVRRef)NMib::fg_Move(Test));}
	//			{NMib::NStorage::TCVariant<PFFunc0> Variant;}
	//			{NMib::NStorage::TCVariant<PFFunc1> Variant;}
	//			{NMib::NStorage::TCVariant<PFFunc2> Variant;}
				{NMib::NStorage::TCVariant<FFunc0Ref> Variant(fsg_FFunc0);}
				{NMib::NStorage::TCVariant<FFunc1Ref> Variant(fsg_FFunc1);}
				{NMib::NStorage::TCVariant<FFunc2Ref> Variant(fsg_FFunc2);}
				{NMib::NStorage::TCVariant<FFunc0RRef> Variant(NMib::fg_Move(fsg_FFunc0));}
				{NMib::NStorage::TCVariant<FFunc1RRef> Variant(NMib::fg_Move(fsg_FFunc1));}
				{NMib::NStorage::TCVariant<FFunc2RRef> Variant(NMib::fg_Move(fsg_FFunc2));}
				{NMib::NStorage::TCVariant<FFunc0Ptr> Variant;}
				{NMib::NStorage::TCVariant<FFunc1Ptr> Variant;}
				{NMib::NStorage::TCVariant<FFunc2Ptr> Variant;}
				{NMib::NStorage::TCVariant<FFunc0PtrC> Variant;}
				{NMib::NStorage::TCVariant<FFunc1PtrC> Variant;}
				{NMib::NStorage::TCVariant<FFunc2PtrC> Variant;}
				{NMib::NStorage::TCVariant<FFunc0PtrV> Variant;}
				{NMib::NStorage::TCVariant<FFunc1PtrV> Variant;}
				{NMib::NStorage::TCVariant<FFunc2PtrV> Variant;}
				{NMib::NStorage::TCVariant<FFunc0PtrCV> Variant;}
				{NMib::NStorage::TCVariant<FFunc1PtrCV> Variant;}
				{NMib::NStorage::TCVariant<FFunc2PtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0Ptr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1Ptr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2Ptr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0PtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1PtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2PtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0PtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1PtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2PtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0PtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1PtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2PtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0CPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1CPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2CPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0CPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1CPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2CPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0CPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1CPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2CPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0CPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1CPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2CPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0VPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1VPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2VPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0VPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1VPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2VPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0VPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1VPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2VPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0VPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1VPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2VPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0CVPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1CVPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2CVPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0CVPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1CVPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2CVPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0CVPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1CVPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2CVPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0CVPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1CVPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2CVPtrCV> Variant;}
	//			{NMib::NStorage::TCVariant<PFFunc0El> Variant;}
	//			{NMib::NStorage::TCVariant<PFFunc1El> Variant;}
	//			{NMib::NStorage::TCVariant<PFFunc2El> Variant;}
				{NMib::NStorage::TCVariant<FFunc0ElRef> Variant(fsg_FFunc0El);}
				{NMib::NStorage::TCVariant<FFunc1ElRef> Variant(fsg_FFunc1El);}
				{NMib::NStorage::TCVariant<FFunc2ElRef> Variant(fsg_FFunc2El);}
				{NMib::NStorage::TCVariant<FFunc0ElRRef> Variant(NMib::fg_Move(fsg_FFunc0El));}
				{NMib::NStorage::TCVariant<FFunc1ElRRef> Variant(NMib::fg_Move(fsg_FFunc1El));}
				{NMib::NStorage::TCVariant<FFunc2ElRRef> Variant(NMib::fg_Move(fsg_FFunc2El));}
				{NMib::NStorage::TCVariant<FFunc0ElPtr> Variant;}
				{NMib::NStorage::TCVariant<FFunc1ElPtr> Variant;}
				{NMib::NStorage::TCVariant<FFunc2ElPtr> Variant;}
				{NMib::NStorage::TCVariant<FFunc0ElPtrC> Variant;}
				{NMib::NStorage::TCVariant<FFunc1ElPtrC> Variant;}
				{NMib::NStorage::TCVariant<FFunc2ElPtrC> Variant;}
				{NMib::NStorage::TCVariant<FFunc0ElPtrV> Variant;}
				{NMib::NStorage::TCVariant<FFunc1ElPtrV> Variant;}
				{NMib::NStorage::TCVariant<FFunc2ElPtrV> Variant;}
				{NMib::NStorage::TCVariant<FFunc0ElPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FFunc1ElPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FFunc2ElPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElCPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElCPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElCPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElCPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElCPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElCPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElCPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElCPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElCPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElCPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElCPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElCPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElVPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElVPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElVPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElVPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElVPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElVPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElVPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElVPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElVPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElVPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElVPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElVPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElCVPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElCVPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElCVPtr> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElCVPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElCVPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElCVPtrC> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElCVPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElCVPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElCVPtrV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc0ElCVPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc1ElCVPtrCV> Variant;}
				{NMib::NStorage::TCVariant<FMFunc2ElCVPtrCV> Variant;}
				{NMib::NStorage::TCVariant<CMPtr> Variant;}
				{NMib::NStorage::TCVariant<CMCPtr> Variant;}
				{NMib::NStorage::TCVariant<CMVPtr> Variant;}
				{NMib::NStorage::TCVariant<CMCVPtr> Variant;}
				{NMib::NStorage::TCVariant<CMPtrC> Variant;}
				{NMib::NStorage::TCVariant<CMCPtrC> Variant;}
				{NMib::NStorage::TCVariant<CMVPtrC> Variant;}
				{NMib::NStorage::TCVariant<CMCVPtrC> Variant;}
				{NMib::NStorage::TCVariant<CMPtrV> Variant;}
				{NMib::NStorage::TCVariant<CMCPtrV> Variant;}
				{NMib::NStorage::TCVariant<CMVPtrV> Variant;}
				{NMib::NStorage::TCVariant<CMCVPtrV> Variant;}
				{NMib::NStorage::TCVariant<CMPtrCV> Variant;}
				{NMib::NStorage::TCVariant<CMCPtrCV> Variant;}
				{NMib::NStorage::TCVariant<CMVPtrCV> Variant;}
				{NMib::NStorage::TCVariant<CMCVPtrCV> Variant;}
				{NMib::NStorage::TCVariant<CTestArray2> Variant;}
				{NMib::NStorage::TCVariant<CTestArray2C> Variant;}
				{NMib::NStorage::TCVariant<CTestArray2V> Variant;}
				{NMib::NStorage::TCVariant<CTestArray2CV> Variant;}
	//			{NMib::NStorage::TCVariant<CTestArray> Variant;}
	//			{NMib::NStorage::TCVariant<CTestArrayC> Variant;}
	//			{NMib::NStorage::TCVariant<CTestArrayV> Variant;}
	//			{NMib::NStorage::TCVariant<CTestArrayCV> Variant;}
				{NMib::NStorage::TCVariant<CTest2DArray2> Variant;}
				{NMib::NStorage::TCVariant<CTest2DArray2C> Variant;}
				{NMib::NStorage::TCVariant<CTest2DArray2V> Variant;}
				{NMib::NStorage::TCVariant<CTest2DArray2CV> Variant;}
	//			{NMib::NStorage::TCVariant<CTest2DArray> Variant;}
	//			{NMib::NStorage::TCVariant<CTest2DArrayC> Variant;}
	//			{NMib::NStorage::TCVariant<CTest2DArrayV> Variant;}
	//			{NMib::NStorage::TCVariant<CTest2DArrayCV> Variant;}
				{NMib::NStorage::TCVariant<CTest3DArray2> Variant;}
				{NMib::NStorage::TCVariant<CTest3DArray2C> Variant;}
				{NMib::NStorage::TCVariant<CTest3DArray2V> Variant;}
				{NMib::NStorage::TCVariant<CTest3DArray2CV> Variant;}
	//			{NMib::NStorage::TCVariant<CTest3DArray> Variant;}
	//			{NMib::NStorage::TCVariant<CTest3DArrayC> Variant;}
	//			{NMib::NStorage::TCVariant<CTest3DArrayV> Variant;}
	//			{NMib::NStorage::TCVariant<CTest3DArrayCV> Variant;}
				{NMib::NStorage::TCVariant<void *> Variant;}
				{NMib::NStorage::TCVariant<void> Variant;}
	#endif

				if (0)
				{
					// This does not work... it's initialized as a char
					int Val = 5;
					NMib::NStorage::TCVariant<char, int const&> Var((int const&)Val);

					NMib::NStorage::TCVariant<char, int const&> const& VarRef = Var;

					struct CUtil
					{
						static void Do(char _V) {}
						static void Do(int const& _V) {}
					};


					int const& Ref = VarRef.f_Get<1>();
					CUtil::Do(VarRef.f_Get<1>());
				}
			};
		}

	};

	DMibTestRegister(CVariant_Tests, Malterlib::Storage);
}

