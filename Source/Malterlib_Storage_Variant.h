// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#ifndef DMibContainerVariantMany
#define DMibContainerVariantMany 1
#endif

namespace NMib
{
	namespace NContainer
	{

		namespace NPrivate
		{
			struct CVariantVisitor_Destruct
			{
				void operator () (CVoidTag)
				{
				}

				template <typename tf_CType>
				void operator () (tf_CType &_Type)
				{
					fg_CallDestructor(_Type);
				}
			};

			struct CDummy
			{
			};
			
			template <typename t_CReturn>
			function_does_not_return inline_never typename TCEnableIf<!NTraits::TCIsVoid<t_CReturn>::mc_Value, t_CReturn &>::CType fg_InvalidVariant()
			{
				DMibError("Corrupt variant");
			}

			template <typename t_CReturn>
			function_does_not_return inline_never typename TCEnableIf<NTraits::TCIsVoid<t_CReturn>::mc_Value, void>::CType fg_InvalidVariant()
			{
				DMibError("Corrupt variant");
			}

		}

		template 
		<
			typename t_CType0 = void
			, typename t_CType1 = void
			, typename t_CType2 = void
			, typename t_CType3 = void
			, typename t_CType4 = void
			, typename t_CType5 = void
			, typename t_CType6 = void
			, typename t_CType7 = void
#if DMibContainerVariantMany > 0
			, typename t_CType8 = void
			, typename t_CType9 = void
			, typename t_CType10 = void
			, typename t_CType11 = void
			, typename t_CType12 = void
			, typename t_CType13 = void
			, typename t_CType14 = void
			, typename t_CType15 = void
#if DMibContainerVariantMany > 1
			, typename t_CType16 = void
			, typename t_CType17 = void
			, typename t_CType18 = void
			, typename t_CType19 = void
			, typename t_CType20 = void
			, typename t_CType21 = void
			, typename t_CType22 = void
			, typename t_CType23 = void
#endif
#endif
		>
		class TCVariant;

		template 
		<
			typename t_CEnum
			, typename t_CType0 = void
			, typename t_CType1 = void
			, typename t_CType2 = void
			, typename t_CType3 = void
			, typename t_CType4 = void
			, typename t_CType5 = void
			, typename t_CType6 = void
			, typename t_CType7 = void
#if DMibContainerVariantMany > 0
			, typename t_CType8 = void
			, typename t_CType9 = void
			, typename t_CType10 = void
			, typename t_CType11 = void
			, typename t_CType12 = void
			, typename t_CType13 = void
			, typename t_CType14 = void
			, typename t_CType15 = void
#if DMibContainerVariantMany > 1
			, typename t_CType16 = void
			, typename t_CType17 = void
			, typename t_CType18 = void
			, typename t_CType19 = void
			, typename t_CType20 = void
			, typename t_CType21 = void
			, typename t_CType22 = void
			, typename t_CType23 = void
#endif
#endif
		>
		class TCStreamableFixedVariant;
		
		template 
		<
			typename t_CIndexType
			, typename t_CType0, t_CIndexType t_iMember0
			, typename t_CType1 = void, t_CIndexType t_iMember1 = t_CIndexType(-2)
			, typename t_CType2 = void, t_CIndexType t_iMember2 = t_CIndexType(-3)
			, typename t_CType3 = void, t_CIndexType t_iMember3 = t_CIndexType(-4)
			, typename t_CType4 = void, t_CIndexType t_iMember4 = t_CIndexType(-5)
			, typename t_CType5 = void, t_CIndexType t_iMember5 = t_CIndexType(-6)
			, typename t_CType6 = void, t_CIndexType t_iMember6 = t_CIndexType(-7)
			, typename t_CType7 = void, t_CIndexType t_iMember7 = t_CIndexType(-8)
#if DMibContainerVariantMany > 0
			, typename t_CType8 = void, t_CIndexType t_iMember8 = t_CIndexType(-9)
			, typename t_CType9 = void, t_CIndexType t_iMember9 = t_CIndexType(-10)
			, typename t_CType10 = void, t_CIndexType t_iMember10 = t_CIndexType(-11)
			, typename t_CType11 = void, t_CIndexType t_iMember11 = t_CIndexType(-12)
			, typename t_CType12 = void, t_CIndexType t_iMember12 = t_CIndexType(-13)
			, typename t_CType13 = void, t_CIndexType t_iMember13 = t_CIndexType(-14)
			, typename t_CType14 = void, t_CIndexType t_iMember14 = t_CIndexType(-15)
			, typename t_CType15 = void, t_CIndexType t_iMember15 = t_CIndexType(-16)
#if DMibContainerVariantMany > 1
			, typename t_CType16 = void, t_CIndexType t_iMember16 = t_CIndexType(-17)
			, typename t_CType17 = void, t_CIndexType t_iMember17 = t_CIndexType(-18)
			, typename t_CType18 = void, t_CIndexType t_iMember18 = t_CIndexType(-19)
			, typename t_CType19 = void, t_CIndexType t_iMember19 = t_CIndexType(-20)
			, typename t_CType20 = void, t_CIndexType t_iMember20 = t_CIndexType(-21)
			, typename t_CType21 = void, t_CIndexType t_iMember21 = t_CIndexType(-22)
			, typename t_CType22 = void, t_CIndexType t_iMember22 = t_CIndexType(-23)
			, typename t_CType23 = void, t_CIndexType t_iMember23 = t_CIndexType(-24)
#endif
#endif
			, bint t_bStreamable = true
		>
		class TCStreamableVariant
		{
		public:
			typedef t_CIndexType CIndexType;

			static_assert(sizeof(t_CIndexType) <= sizeof(int), "Index type must fit in enum");
			static_assert(NTraits::TCIsSigned<t_CIndexType>::mc_Value || NTraits::TCIsEnum<t_CIndexType>::mc_Value, "Index type must be signed");
#ifdef DMibDebuggerHelpers
			struct CMemberValues
			{
				t_CIndexType m_Values
				[
	#if DMibContainerVariantMany > 1
					24
	#elif DMibContainerVariantMany > 0
					16
	#else
					8
	#endif
				];
			};
			static CMemberValues ms_MemberValues;
#endif
		private:
			template 
			<
				typename t_CType2_0
				, typename t_CType2_1
				, typename t_CType2_2
				, typename t_CType2_3
				, typename t_CType2_4
				, typename t_CType2_5
				, typename t_CType2_6
				, typename t_CType2_7
#if DMibContainerVariantMany > 0
				, typename t_CType2_8
				, typename t_CType2_9
				, typename t_CType2_10
				, typename t_CType2_11
				, typename t_CType2_12
				, typename t_CType2_13
				, typename t_CType2_14
				, typename t_CType2_15
#if DMibContainerVariantMany > 1
				, typename t_CType2_16
				, typename t_CType2_17
				, typename t_CType2_18
				, typename t_CType2_19
				, typename t_CType2_20
				, typename t_CType2_21
				, typename t_CType2_22
				, typename t_CType2_23
#endif
#endif
			>
			friend class TCVariant;

			template 
			<
				typename t_CEnum2
				, typename t_CType2_0
				, typename t_CType2_1
				, typename t_CType2_2
				, typename t_CType2_3
				, typename t_CType2_4
				, typename t_CType2_5
				, typename t_CType2_6
				, typename t_CType2_7
#if DMibContainerVariantMany > 0
				, typename t_CType2_8
				, typename t_CType2_9
				, typename t_CType2_10
				, typename t_CType2_11
				, typename t_CType2_12
				, typename t_CType2_13
				, typename t_CType2_14
				, typename t_CType2_15
#if DMibContainerVariantMany > 1
				, typename t_CType2_16
				, typename t_CType2_17
				, typename t_CType2_18
				, typename t_CType2_19
				, typename t_CType2_20
				, typename t_CType2_21
				, typename t_CType2_22
				, typename t_CType2_23
#endif
#endif
			>
			friend class TCStreamableFixedVariant;

			template <typename t_CType>
			struct TCCheckContracts
			{
				static_assert(!NTraits::TCIsArrayUnbounded<t_CType>::mc_Value, "You cannot store an unbounded array in a variant");
				static_assert(!NTraits::TCIsFunction<t_CType>::mc_Value, "You cannot store function types in a variant");
				enum
				{
					mc_Value = true
				};
			};

			enum
			{
				EDebugHelper_Member0 = t_iMember0
				,EDebugHelper_Member1 = t_iMember1
				,EDebugHelper_Member2 = t_iMember2
				,EDebugHelper_Member3 = t_iMember3
				,EDebugHelper_Member4 = t_iMember4
				,EDebugHelper_Member5 = t_iMember5
				,EDebugHelper_Member6 = t_iMember6
				,EDebugHelper_Member7 = t_iMember7
#if DMibContainerVariantMany > 0
				,EDebugHelper_Member8 = t_iMember8
				,EDebugHelper_Member9 = t_iMember9
				,EDebugHelper_Member10 = t_iMember10
				,EDebugHelper_Member11 = t_iMember11
				,EDebugHelper_Member12 = t_iMember12
				,EDebugHelper_Member13 = t_iMember13
				,EDebugHelper_Member14 = t_iMember14
				,EDebugHelper_Member15 = t_iMember15
#if DMibContainerVariantMany > 1
				,EDebugHelper_Member16 = t_iMember16
				,EDebugHelper_Member17 = t_iMember17
				,EDebugHelper_Member18 = t_iMember18
				,EDebugHelper_Member19 = t_iMember19
				,EDebugHelper_Member20 = t_iMember20
				,EDebugHelper_Member21 = t_iMember21
				,EDebugHelper_Member22 = t_iMember22
				,EDebugHelper_Member23 = t_iMember23
#endif
#endif
#if DMibContainerVariantMany > 1
				,EDebugHelper_MaxMembers = 24
#elif DMibContainerVariantMany > 0
				,EDebugHelper_MaxMembers = 16
#else
				,EDebugHelper_MaxMembers = 8
#endif

			};

			enum
			{
				mcp_MinIndex 
				=
				TCConstantMin
				<
					int
					, t_iMember0
					, TCConstantMin
					<
						int
						, t_iMember1
						, TCConstantMin
						<
							int
							, t_iMember2
							, TCConstantMin
							<
								int
								, t_iMember3
								, TCConstantMin
								<
									int
									, t_iMember4
									, TCConstantMin
									<
										int
										, t_iMember5
										, TCConstantMin
										<
											int
											, t_iMember6
#if DMibContainerVariantMany > 0
											, TCConstantMin
											<
												int
												, t_iMember7
												, TCConstantMin
												<
													int
													, t_iMember8
													, TCConstantMin
													<
														int
														, t_iMember9
														, TCConstantMin
														<
															int
															, t_iMember10
															, TCConstantMin
															<
																int
																, t_iMember11
																, TCConstantMin
																<
																	int
																	, t_iMember12
																	, TCConstantMin
																	<
																		int
																		, t_iMember13
																		, TCConstantMin
																		<
																			int
																			, t_iMember14
#if DMibContainerVariantMany > 1
																			, TCConstantMin
																			<
																				int
																				, t_iMember15
																				, TCConstantMin
																				<
																					int
																					, t_iMember16
																					, TCConstantMin
																					<
																						int
																						, t_iMember17
																						, TCConstantMin
																						<
																							int
																							, t_iMember18
																							, TCConstantMin
																							<
																								int
																								, t_iMember19
																								, TCConstantMin
																								<
																									int
																									, t_iMember20
																									, TCConstantMin
																									<
																										int
																										, t_iMember21
																										, TCConstantMin
																										<
																											int
																											, t_iMember22
																											, t_iMember23
																										>::mc_Value
																									>::mc_Value
																								>::mc_Value
																							>::mc_Value
																						>::mc_Value
																					>::mc_Value
																				>::mc_Value
																			>::mc_Value
#else
																			, t_iMember15
#endif
																		>::mc_Value
																	>::mc_Value
																>::mc_Value
															>::mc_Value
														>::mc_Value
													>::mc_Value
												>::mc_Value
											>::mc_Value
#else
											, t_iMember7
#endif
										>::mc_Value
									>::mc_Value
								>::mc_Value
							>::mc_Value
						>::mc_Value
					>::mc_Value
				>::mc_Value

				, mcp_MaxIndex 
				=
				TCConstantMax
				<
					int
					, t_iMember0
					, TCConstantMax
					<
						int
						, t_iMember1
						, TCConstantMax
						<
							int
							, t_iMember2
							, TCConstantMax
							<
								int
								, t_iMember3
								, TCConstantMax
								<
									int
									, t_iMember4
									, TCConstantMax
									<
										int
										, t_iMember5
										, TCConstantMax
										<
											int
											, t_iMember6
#if DMibContainerVariantMany > 0
											, TCConstantMax
											<
												int
												, t_iMember7
												, TCConstantMax
												<
													int
													, t_iMember8
													, TCConstantMax
													<
														int
														, t_iMember9
														, TCConstantMax
														<
															int
															, t_iMember10
															, TCConstantMax
															<
																int
																, t_iMember11
																, TCConstantMax
																<
																	int
																	, t_iMember12
																	, TCConstantMax
																	<
																		int
																		, t_iMember13
																		, TCConstantMax
																		<
																			int
																			, t_iMember14
#if DMibContainerVariantMany > 1
																			, TCConstantMax
																			<
																				int
																				, t_iMember15
																				, TCConstantMax
																				<
																					int
																					, t_iMember16
																					, TCConstantMax
																					<
																						int
																						, t_iMember17
																						, TCConstantMax
																						<
																							int
																							, t_iMember18
																							, TCConstantMax
																							<
																								int
																								, t_iMember19
																								, TCConstantMax
																								<
																									int
																									, t_iMember20
																									, TCConstantMax
																									<
																										int
																										, t_iMember21
																										, TCConstantMax
																										<
																											int
																											, t_iMember22
																											, t_iMember23
																										>::mc_Value
																									>::mc_Value
																								>::mc_Value
																							>::mc_Value
																						>::mc_Value
																					>::mc_Value
																				>::mc_Value
																			>::mc_Value
#else
																			, t_iMember15
#endif
																		>::mc_Value
																	>::mc_Value
																>::mc_Value
															>::mc_Value
														>::mc_Value
													>::mc_Value
												>::mc_Value
											>::mc_Value
#else
											, t_iMember7
#endif
										>::mc_Value
									>::mc_Value
								>::mc_Value
							>::mc_Value
						>::mc_Value
					>::mc_Value
				>::mc_Value
			};

			enum
			{
				mcp_NeededBits = TCConstantMax<mint, TCHighestBitSet<int, TCConstantAbs<int, mcp_MaxIndex>::mc_Value>::mc_Value, TCHighestBitSet<int, TCConstantAbs<int, mcp_MinIndex>::mc_Value>::mc_Value>::mc_Value + 1
			};
			typedef typename NTraits::TCIntFromSizeLarger<(mcp_NeededBits + 7) / 8>::CType CTypeIDStorageType;			

			static_assert(TCCheckContracts<t_CType0>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType1>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType2>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType3>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType4>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType5>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType6>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType7>::mc_Value, "");
#if DMibContainerVariantMany > 0
			static_assert(TCCheckContracts<t_CType8>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType9>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType10>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType11>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType12>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType13>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType14>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType15>::mc_Value, "");
#if DMibContainerVariantMany > 1
			static_assert(TCCheckContracts<t_CType16>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType17>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType18>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType19>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType20>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType21>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType22>::mc_Value, "");
			static_assert(TCCheckContracts<t_CType23>::mc_Value, "");
#endif
#endif

public:

			template <t_CIndexType t_iMember>
			struct TCTypeFromMember
			{
				typedef 
					typename TCChooseType<t_iMember == t_iMember0, t_CType0, 
					typename TCChooseType<t_iMember == t_iMember1, t_CType1, 
					typename TCChooseType<t_iMember == t_iMember2, t_CType2, 
					typename TCChooseType<t_iMember == t_iMember3, t_CType3, 
					typename TCChooseType<t_iMember == t_iMember4, t_CType4, 
					typename TCChooseType<t_iMember == t_iMember5, t_CType5, 
					typename TCChooseType<t_iMember == t_iMember6, t_CType6, 
					typename TCChooseType<t_iMember == t_iMember7, t_CType7, 
#if DMibContainerVariantMany > 0
					typename TCChooseType<t_iMember == t_iMember8, t_CType8, 
					typename TCChooseType<t_iMember == t_iMember9, t_CType9, 
					typename TCChooseType<t_iMember == t_iMember10, t_CType10, 
					typename TCChooseType<t_iMember == t_iMember11, t_CType11, 
					typename TCChooseType<t_iMember == t_iMember12, t_CType12, 
					typename TCChooseType<t_iMember == t_iMember13, t_CType13, 
					typename TCChooseType<t_iMember == t_iMember14, t_CType14, 
					typename TCChooseType<t_iMember == t_iMember15, t_CType15, 
#if DMibContainerVariantMany > 1
					typename TCChooseType<t_iMember == t_iMember16, t_CType16, 
					typename TCChooseType<t_iMember == t_iMember17, t_CType17, 
					typename TCChooseType<t_iMember == t_iMember18, t_CType18, 
					typename TCChooseType<t_iMember == t_iMember19, t_CType19, 
					typename TCChooseType<t_iMember == t_iMember20, t_CType20, 
					typename TCChooseType<t_iMember == t_iMember21, t_CType21, 
					typename TCChooseType<t_iMember == t_iMember22, t_CType22, 
					typename TCChooseType<t_iMember == t_iMember23, t_CType23, 
#endif
#endif
					void >::CType>::CType>::CType>::CType>::CType>::CType>::CType>::CType
#if DMibContainerVariantMany > 0
					>::CType>::CType>::CType>::CType>::CType>::CType>::CType>::CType
#if DMibContainerVariantMany > 1
					>::CType>::CType>::CType>::CType>::CType>::CType>::CType>::CType
#endif
#endif
					CType;
			};

			template <int t_iIndex>
			struct TCTypeFromIndex
			{
				typedef typename TCChooseType<t_iIndex == 0, t_CType0, 
					typename TCChooseType<t_iIndex == 1, t_CType1, 
					typename TCChooseType<t_iIndex == 2, t_CType2, 
					typename TCChooseType<t_iIndex == 3, t_CType3, 
					typename TCChooseType<t_iIndex == 4, t_CType4, 
					typename TCChooseType<t_iIndex == 5, t_CType5, 
					typename TCChooseType<t_iIndex == 6, t_CType6, 
					typename TCChooseType<t_iIndex == 7, t_CType7, 
#if DMibContainerVariantMany > 0
					typename TCChooseType<t_iIndex == 8, t_CType8, 
					typename TCChooseType<t_iIndex == 9, t_CType9, 
					typename TCChooseType<t_iIndex == 10, t_CType10, 
					typename TCChooseType<t_iIndex == 11, t_CType11, 
					typename TCChooseType<t_iIndex == 12, t_CType12, 
					typename TCChooseType<t_iIndex == 13, t_CType13, 
					typename TCChooseType<t_iIndex == 14, t_CType14, 
					typename TCChooseType<t_iIndex == 15, t_CType15, 
#if DMibContainerVariantMany > 1
					typename TCChooseType<t_iIndex == 16, t_CType16, 
					typename TCChooseType<t_iIndex == 17, t_CType17, 
					typename TCChooseType<t_iIndex == 18, t_CType18, 
					typename TCChooseType<t_iIndex == 19, t_CType19, 
					typename TCChooseType<t_iIndex == 20, t_CType20, 
					typename TCChooseType<t_iIndex == 21, t_CType21, 
					typename TCChooseType<t_iIndex == 22, t_CType22, 
					typename TCChooseType<t_iIndex == 23, t_CType23, 
#endif
#endif
					void >::CType>::CType>::CType>::CType>::CType>::CType>::CType>::CType 
#if DMibContainerVariantMany > 0
					>::CType>::CType>::CType>::CType>::CType>::CType>::CType>::CType
#if DMibContainerVariantMany > 1
					>::CType>::CType>::CType>::CType>::CType>::CType>::CType>::CType
#endif
#endif
					CType;
			};

			template <typename t_CType>
			struct TCMemberFromType
			{
				enum
				{
					mc_Value 
					= 
					NTraits::TCIsSame<t_CType, t_CType0>::mc_Value ? t_iMember0 :
					NTraits::TCIsSame<t_CType, t_CType1>::mc_Value ? t_iMember1 :
					NTraits::TCIsSame<t_CType, t_CType2>::mc_Value ? t_iMember2 :
					NTraits::TCIsSame<t_CType, t_CType3>::mc_Value ? t_iMember3 :
					NTraits::TCIsSame<t_CType, t_CType4>::mc_Value ? t_iMember4 :
					NTraits::TCIsSame<t_CType, t_CType5>::mc_Value ? t_iMember5 :
					NTraits::TCIsSame<t_CType, t_CType6>::mc_Value ? t_iMember6 :
					NTraits::TCIsSame<t_CType, t_CType7>::mc_Value ? t_iMember7 :
#if DMibContainerVariantMany > 0
					NTraits::TCIsSame<t_CType, t_CType8>::mc_Value ? t_iMember8 :
					NTraits::TCIsSame<t_CType, t_CType9>::mc_Value ? t_iMember9 :
					NTraits::TCIsSame<t_CType, t_CType10>::mc_Value ? t_iMember10 :
					NTraits::TCIsSame<t_CType, t_CType11>::mc_Value ? t_iMember11 :
					NTraits::TCIsSame<t_CType, t_CType12>::mc_Value ? t_iMember12 :
					NTraits::TCIsSame<t_CType, t_CType13>::mc_Value ? t_iMember13 :
					NTraits::TCIsSame<t_CType, t_CType14>::mc_Value ? t_iMember14 :
					NTraits::TCIsSame<t_CType, t_CType15>::mc_Value ? t_iMember15 :
#if DMibContainerVariantMany > 1
					NTraits::TCIsSame<t_CType, t_CType16>::mc_Value ? t_iMember16 :
					NTraits::TCIsSame<t_CType, t_CType17>::mc_Value ? t_iMember17 :
					NTraits::TCIsSame<t_CType, t_CType18>::mc_Value ? t_iMember18 :
					NTraits::TCIsSame<t_CType, t_CType19>::mc_Value ? t_iMember19 :
					NTraits::TCIsSame<t_CType, t_CType20>::mc_Value ? t_iMember20 :
					NTraits::TCIsSame<t_CType, t_CType21>::mc_Value ? t_iMember21 :
					NTraits::TCIsSame<t_CType, t_CType22>::mc_Value ? t_iMember22 :
					NTraits::TCIsSame<t_CType, t_CType23>::mc_Value ? t_iMember23 :
#endif
#endif
					-1
				};
			};

private:
	
			template <t_CIndexType t_iMember>
			struct TCEvalConstructType
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CMemberType;
				typedef typename TCChooseType
					<
						NTraits::TCIsReference<CMemberType>::mc_Value, 
						typename NTraits::TCAddPointer<typename NTraits::TCRemoveReference<CMemberType>::CType>::CType,
						typename NTraits::TCRemoveQualifiers<CMemberType>::CType
					>::CType CType;
			};

			typedef typename TCEvalConstructType<t_iMember0>::CType CConstructType0;
			typedef typename TCEvalConstructType<t_iMember1>::CType CConstructType1;
			typedef typename TCEvalConstructType<t_iMember2>::CType CConstructType2;
			typedef typename TCEvalConstructType<t_iMember3>::CType CConstructType3;
			typedef typename TCEvalConstructType<t_iMember4>::CType CConstructType4;
			typedef typename TCEvalConstructType<t_iMember5>::CType CConstructType5;
			typedef typename TCEvalConstructType<t_iMember6>::CType CConstructType6;
			typedef typename TCEvalConstructType<t_iMember7>::CType CConstructType7;
#if DMibContainerVariantMany > 0
			typedef typename TCEvalConstructType<t_iMember8>::CType CConstructType8;
			typedef typename TCEvalConstructType<t_iMember9>::CType CConstructType9;
			typedef typename TCEvalConstructType<t_iMember10>::CType CConstructType10;
			typedef typename TCEvalConstructType<t_iMember11>::CType CConstructType11;
			typedef typename TCEvalConstructType<t_iMember12>::CType CConstructType12;
			typedef typename TCEvalConstructType<t_iMember13>::CType CConstructType13;
			typedef typename TCEvalConstructType<t_iMember14>::CType CConstructType14;
			typedef typename TCEvalConstructType<t_iMember15>::CType CConstructType15;
#if DMibContainerVariantMany > 1
			typedef typename TCEvalConstructType<t_iMember16>::CType CConstructType16;
			typedef typename TCEvalConstructType<t_iMember17>::CType CConstructType17;
			typedef typename TCEvalConstructType<t_iMember18>::CType CConstructType18;
			typedef typename TCEvalConstructType<t_iMember19>::CType CConstructType19;
			typedef typename TCEvalConstructType<t_iMember20>::CType CConstructType20;
			typedef typename TCEvalConstructType<t_iMember21>::CType CConstructType21;
			typedef typename TCEvalConstructType<t_iMember22>::CType CConstructType22;
			typedef typename TCEvalConstructType<t_iMember23>::CType CConstructType23;
#endif
#endif

			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType0>::mc_Value, CVoidTag, CConstructType0>::CType CDbgConstructType0;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType1>::mc_Value, CVoidTag, CConstructType1>::CType CDbgConstructType1;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType2>::mc_Value, CVoidTag, CConstructType2>::CType CDbgConstructType2;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType3>::mc_Value, CVoidTag, CConstructType3>::CType CDbgConstructType3;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType4>::mc_Value, CVoidTag, CConstructType4>::CType CDbgConstructType4;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType5>::mc_Value, CVoidTag, CConstructType5>::CType CDbgConstructType5;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType6>::mc_Value, CVoidTag, CConstructType6>::CType CDbgConstructType6;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType7>::mc_Value, CVoidTag, CConstructType7>::CType CDbgConstructType7;
#if DMibContainerVariantMany > 0
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType8>::mc_Value, CVoidTag, CConstructType8>::CType CDbgConstructType8;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType9>::mc_Value, CVoidTag, CConstructType9>::CType CDbgConstructType9;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType10>::mc_Value, CVoidTag, CConstructType10>::CType CDbgConstructType10;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType11>::mc_Value, CVoidTag, CConstructType11>::CType CDbgConstructType11;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType12>::mc_Value, CVoidTag, CConstructType12>::CType CDbgConstructType12;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType13>::mc_Value, CVoidTag, CConstructType13>::CType CDbgConstructType13;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType14>::mc_Value, CVoidTag, CConstructType14>::CType CDbgConstructType14;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType15>::mc_Value, CVoidTag, CConstructType15>::CType CDbgConstructType15;
#if DMibContainerVariantMany > 1
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType16>::mc_Value, CVoidTag, CConstructType16>::CType CDbgConstructType16;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType17>::mc_Value, CVoidTag, CConstructType17>::CType CDbgConstructType17;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType18>::mc_Value, CVoidTag, CConstructType18>::CType CDbgConstructType18;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType19>::mc_Value, CVoidTag, CConstructType19>::CType CDbgConstructType19;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType20>::mc_Value, CVoidTag, CConstructType20>::CType CDbgConstructType20;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType21>::mc_Value, CVoidTag, CConstructType21>::CType CDbgConstructType21;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType22>::mc_Value, CVoidTag, CConstructType22>::CType CDbgConstructType22;
			typedef typename TCChooseType<NTraits::TCIsVoid<CConstructType23>::mc_Value, CVoidTag, CConstructType23>::CType CDbgConstructType23;
#endif
#endif


#if DMibContainerVariantMany > 0
			const static mint mcp_MaxSize = 
				TCConstantMax
				<
					mint
					, TCConstantMax
					<
						mint
						, TCConstantMax
						<
							mint
							, TCConstantMax
							<
								mint
								, TCConstantMax
								<
									mint
									,NTraits::TCSizeOf<CConstructType0>::mc_Value
									,NTraits::TCSizeOf<CConstructType1>::mc_Value
								>::mc_Value
								, TCConstantMax
								<
									mint
									, NTraits::TCSizeOf<CConstructType2>::mc_Value 
									, NTraits::TCSizeOf<CConstructType3>::mc_Value
								>::mc_Value
							>::mc_Value
							, TCConstantMax
							<
								mint
								, TCConstantMax
								<
									mint
									,NTraits::TCSizeOf<CConstructType4>::mc_Value
									,NTraits::TCSizeOf<CConstructType5>::mc_Value
								>::mc_Value
								, TCConstantMax
								<
									mint
									, NTraits::TCSizeOf<CConstructType6>::mc_Value 
									, NTraits::TCSizeOf<CConstructType7>::mc_Value
								>::mc_Value
							>::mc_Value
						>::mc_Value
						, TCConstantMax
						<
							mint
							, TCConstantMax
							<
								mint
								, TCConstantMax
								<
									mint
									,NTraits::TCSizeOf<CConstructType8>::mc_Value
									,NTraits::TCSizeOf<CConstructType9>::mc_Value
								>::mc_Value
								, TCConstantMax
								<
									mint
									, NTraits::TCSizeOf<CConstructType10>::mc_Value 
									, NTraits::TCSizeOf<CConstructType11>::mc_Value
								>::mc_Value
							>::mc_Value
							, TCConstantMax
							<
								mint
								, TCConstantMax
								<
									mint
									,NTraits::TCSizeOf<CConstructType12>::mc_Value
									,NTraits::TCSizeOf<CConstructType13>::mc_Value
								>::mc_Value
								, TCConstantMax
								<
									mint
									, NTraits::TCSizeOf<CConstructType14>::mc_Value 
									, NTraits::TCSizeOf<CConstructType15>::mc_Value
								>::mc_Value
							>::mc_Value
						>::mc_Value
					>::mc_Value
#if DMibContainerVariantMany > 1
					, TCConstantMax
					<
						mint
						, TCConstantMax
						<
							mint
							, TCConstantMax
							<
								mint
								,NTraits::TCSizeOf<CConstructType16>::mc_Value
								,NTraits::TCSizeOf<CConstructType17>::mc_Value
							>::mc_Value
							, TCConstantMax
							<
								mint
								, NTraits::TCSizeOf<CConstructType18>::mc_Value 
								, NTraits::TCSizeOf<CConstructType19>::mc_Value
							>::mc_Value
						>::mc_Value
						, TCConstantMax
						<
							mint
							, TCConstantMax
							<
								mint
								,NTraits::TCSizeOf<CConstructType20>::mc_Value
								,NTraits::TCSizeOf<CConstructType21>::mc_Value
							>::mc_Value
							, TCConstantMax
							<
								mint
								, NTraits::TCSizeOf<CConstructType22>::mc_Value 
								, NTraits::TCSizeOf<CConstructType23>::mc_Value
							>::mc_Value
						>::mc_Value
					>::mc_Value
#else
					, 0u
#endif
				>::mc_Value
			;

			const static mint mcp_MaxAlignment = 
				TCConstantMax
				<
					mint, 
					TCConstantMax
					<
						mint, 
						TCConstantMax
						<
							mint, 
							TCConstantMax
							<
								mint, 
								TCConstantMax
								<
									mint, 
									TCConstantMax
									<
										mint, 
										NTraits::TCAlignmentOf<CConstructType0>::mc_Value, 
										NTraits::TCAlignmentOf<CConstructType1>::mc_Value
									>::mc_Value
									, TCConstantMax
									<
										mint, 
										NTraits::TCAlignmentOf<CConstructType2>::mc_Value, 
										NTraits::TCAlignmentOf<CConstructType3>::mc_Value
									>::mc_Value
								>::mc_Value
								, TCConstantMax
								<
									mint, 
									TCConstantMax
									<
										mint, 
										NTraits::TCAlignmentOf<CConstructType4>::mc_Value, 
										NTraits::TCAlignmentOf<CConstructType5>::mc_Value
									>::mc_Value
									, TCConstantMax
									<
										mint, 
										NTraits::TCAlignmentOf<CConstructType6>::mc_Value, 
										NTraits::TCAlignmentOf<CConstructType7>::mc_Value
									>::mc_Value
								>::mc_Value
							>::mc_Value
							, TCConstantMax
							<
								mint, 
								TCConstantMax
								<
									mint, 
									TCConstantMax
									<
										mint, 
										NTraits::TCAlignmentOf<CConstructType8>::mc_Value, 
										NTraits::TCAlignmentOf<CConstructType9>::mc_Value
									>::mc_Value
									, TCConstantMax
									<
										mint, 
										NTraits::TCAlignmentOf<CConstructType10>::mc_Value, 
										NTraits::TCAlignmentOf<CConstructType11>::mc_Value
									>::mc_Value
								>::mc_Value
								, TCConstantMax
								<
									mint, 
									TCConstantMax
									<
										mint, 
										NTraits::TCAlignmentOf<CConstructType12>::mc_Value, 
										NTraits::TCAlignmentOf<CConstructType13>::mc_Value
									>::mc_Value
									, TCConstantMax
									<
										mint, 
										NTraits::TCAlignmentOf<CConstructType14>::mc_Value, 
										NTraits::TCAlignmentOf<CConstructType15>::mc_Value
									>::mc_Value
								>::mc_Value
							>::mc_Value
						>::mc_Value
#if DMibContainerVariantMany > 1
						, TCConstantMax
						<
							mint, 
							TCConstantMax
							<
								mint, 
								TCConstantMax
								<
									mint, 
									NTraits::TCAlignmentOf<CConstructType16>::mc_Value, 
									NTraits::TCAlignmentOf<CConstructType17>::mc_Value
								>::mc_Value
								, TCConstantMax
								<
									mint, 
									NTraits::TCAlignmentOf<CConstructType18>::mc_Value, 
									NTraits::TCAlignmentOf<CConstructType19>::mc_Value
								>::mc_Value
							>::mc_Value
							, TCConstantMax
							<
								mint, 
								TCConstantMax
								<
									mint, 
									NTraits::TCAlignmentOf<CConstructType20>::mc_Value, 
									NTraits::TCAlignmentOf<CConstructType21>::mc_Value
								>::mc_Value
								, TCConstantMax
								<
									mint, 
									NTraits::TCAlignmentOf<CConstructType22>::mc_Value, 
									NTraits::TCAlignmentOf<CConstructType23>::mc_Value
								>::mc_Value
							>::mc_Value
						>::mc_Value
#else
						, 0u
#endif
					>::mc_Value
				, 1>::mc_Value
			;
#else
			const static mint mcp_MaxSize = 
				TCConstantMax
				<
					mint
					, TCConstantMax
					<
						mint
						, TCConstantMax
						<
							mint
							,NTraits::TCSizeOf<CConstructType0>::mc_Value
							,NTraits::TCSizeOf<CConstructType1>::mc_Value
						>::mc_Value
						, TCConstantMax
						<
							mint
							, NTraits::TCSizeOf<CConstructType2>::mc_Value 
							, NTraits::TCSizeOf<CConstructType3>::mc_Value
						>::mc_Value
					>::mc_Value
					, TCConstantMax
					<
						mint
						, TCConstantMax
						<
							mint
							, NTraits::TCSizeOf<CConstructType4>::mc_Value
							, NTraits::TCSizeOf<CConstructType5>::mc_Value
						>::mc_Value
						, TCConstantMax
						<
							mint
							, NTraits::TCSizeOf<CConstructType6>::mc_Value
							, NTraits::TCSizeOf<CConstructType7>::mc_Value
						>::mc_Value
					>::mc_Value
				>::mc_Value
			;

			const static mint mcp_MaxAlignment = 
				TCConstantMax
				<
					mint, 
					TCConstantMax
					<
						mint, 
						TCConstantMax
						<
							mint, 
							TCConstantMax
							<
								mint, 
								NTraits::TCAlignmentOf<CConstructType0>::mc_Value, 
								NTraits::TCAlignmentOf<CConstructType1>::mc_Value
							>::mc_Value
							, TCConstantMax
							<
								mint, 
								NTraits::TCAlignmentOf<CConstructType2>::mc_Value, 
								NTraits::TCAlignmentOf<CConstructType3>::mc_Value
							>::mc_Value
						>::mc_Value
						, TCConstantMax
						<
							mint, 
							TCConstantMax
							<
								mint, 
								NTraits::TCAlignmentOf<CConstructType4>::mc_Value, 
								NTraits::TCAlignmentOf<CConstructType5>::mc_Value
							>::mc_Value
							, TCConstantMax
							<
								mint, 
								NTraits::TCAlignmentOf<CConstructType6>::mc_Value, 
								NTraits::TCAlignmentOf<CConstructType7>::mc_Value
							>::mc_Value
						>::mc_Value
					>::mc_Value
				, 1>::mc_Value
			;
#endif

			enum
			{
				mcp_FirstDefaultConstructible = 
				!NTraits::TCIsReference<t_CType0>::mc_Value && (NTraits::TCIsConstructorCallableWith<t_CType0, void ()>::mc_Value || NTraits::TCIsVoid<t_CType0>::mc_Value) ? t_iMember0 :
				!NTraits::TCIsReference<t_CType1>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType1, void ()>::mc_Value ? t_iMember1 :
				!NTraits::TCIsReference<t_CType2>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType2, void ()>::mc_Value ? t_iMember2 :
				!NTraits::TCIsReference<t_CType3>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType3, void ()>::mc_Value ? t_iMember3 :
				!NTraits::TCIsReference<t_CType4>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType4, void ()>::mc_Value ? t_iMember4 :
				!NTraits::TCIsReference<t_CType5>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType5, void ()>::mc_Value ? t_iMember5 :
				!NTraits::TCIsReference<t_CType6>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType6, void ()>::mc_Value ? t_iMember6 :
				!NTraits::TCIsReference<t_CType7>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType7, void ()>::mc_Value ? t_iMember7 :
#if DMibContainerVariantMany > 0
				!NTraits::TCIsReference<t_CType8>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType8, void ()>::mc_Value ? t_iMember8 :
				!NTraits::TCIsReference<t_CType9>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType9, void ()>::mc_Value ? t_iMember9 :
				!NTraits::TCIsReference<t_CType10>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType10, void ()>::mc_Value ? t_iMember10 :
				!NTraits::TCIsReference<t_CType11>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType11, void ()>::mc_Value ? t_iMember11 :
				!NTraits::TCIsReference<t_CType12>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType12, void ()>::mc_Value ? t_iMember12 :
				!NTraits::TCIsReference<t_CType13>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType13, void ()>::mc_Value ? t_iMember13 :
				!NTraits::TCIsReference<t_CType14>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType14, void ()>::mc_Value ? t_iMember14 :
				!NTraits::TCIsReference<t_CType15>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType15, void ()>::mc_Value ? t_iMember15 :
#if DMibContainerVariantMany > 1
				!NTraits::TCIsReference<t_CType16>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType16, void ()>::mc_Value ? t_iMember16 :
				!NTraits::TCIsReference<t_CType17>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType17, void ()>::mc_Value ? t_iMember17 :
				!NTraits::TCIsReference<t_CType18>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType18, void ()>::mc_Value ? t_iMember18 :
				!NTraits::TCIsReference<t_CType19>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType19, void ()>::mc_Value ? t_iMember19 :
				!NTraits::TCIsReference<t_CType20>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType20, void ()>::mc_Value ? t_iMember20 :
				!NTraits::TCIsReference<t_CType21>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType21, void ()>::mc_Value ? t_iMember21 :
				!NTraits::TCIsReference<t_CType22>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType22, void ()>::mc_Value ? t_iMember22 :
				!NTraits::TCIsReference<t_CType23>::mc_Value && NTraits::TCIsConstructorCallableWith<t_CType23, void ()>::mc_Value ? t_iMember23 :
#endif
#endif
				-1
				, mcp_FirstNothrowDefaultConstructible = 
				(
					!NTraits::TCIsReference<t_CType0>::mc_Value 
					&& (NTraits::TCIsConstructorCallableWith<t_CType0, void ()>::mc_Value || NTraits::TCIsVoid<t_CType0>::mc_Value) 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType0>::mc_Value
				) 
				? t_iMember0 :
				(
					!NTraits::TCIsReference<t_CType1>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType1, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType1>::mc_Value
				) 
				? t_iMember1 :
				(
					!NTraits::TCIsReference<t_CType2>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType2, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType2>::mc_Value
				) 
				? t_iMember2 :
				(
					!NTraits::TCIsReference<t_CType3>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType3, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType3>::mc_Value
				) 
				? t_iMember3 :
				(
					!NTraits::TCIsReference<t_CType4>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType4, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType4>::mc_Value
				) 
				? t_iMember4 :
				(
					!NTraits::TCIsReference<t_CType5>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType5, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType5>::mc_Value
				) 
				? t_iMember5 :
				(
					!NTraits::TCIsReference<t_CType6>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType6, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType6>::mc_Value
				) 
				? t_iMember6 :
				(
					!NTraits::TCIsReference<t_CType7>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType7, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType7>::mc_Value
				) 
				? t_iMember7 :
#if DMibContainerVariantMany > 0
				(
					!NTraits::TCIsReference<t_CType8>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType8, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType8>::mc_Value
				) 
				? t_iMember8 :
				(
					!NTraits::TCIsReference<t_CType9>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType9, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType9>::mc_Value
				) 
				? t_iMember9 :
				(
					!NTraits::TCIsReference<t_CType10>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType10, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType10>::mc_Value
				) 
				? t_iMember10 :
				(
					!NTraits::TCIsReference<t_CType11>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType11, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType11>::mc_Value
				) 
				? t_iMember11 :
				(
					!NTraits::TCIsReference<t_CType12>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType12, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType12>::mc_Value
				) 
				? t_iMember12 :
				(
					!NTraits::TCIsReference<t_CType13>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType13, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType13>::mc_Value
				) 
				? t_iMember13 :
				(
					!NTraits::TCIsReference<t_CType14>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType14, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType14>::mc_Value
				) 
				? t_iMember14 :
				(
					!NTraits::TCIsReference<t_CType15>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType15, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType15>::mc_Value
				) 
				? t_iMember15 :
#if DMibContainerVariantMany > 1
				(
					!NTraits::TCIsReference<t_CType16>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType16, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType16>::mc_Value
				) 
				? t_iMember16 :
				(
					!NTraits::TCIsReference<t_CType17>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType17, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType17>::mc_Value
				) 
				? t_iMember17 :
				(
					!NTraits::TCIsReference<t_CType18>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType18, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType18>::mc_Value
				) 
				? t_iMember18 :
				(
					!NTraits::TCIsReference<t_CType19>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType19, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType19>::mc_Value
				) 
				? t_iMember19 :
				(
					!NTraits::TCIsReference<t_CType20>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType20, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType20>::mc_Value
				) 
				? t_iMember20 :
				(
					!NTraits::TCIsReference<t_CType21>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType21, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType21>::mc_Value
				) 
				? t_iMember21 :
				(
					!NTraits::TCIsReference<t_CType22>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType22, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType22>::mc_Value
				) 
				? t_iMember22 :
				(
					!NTraits::TCIsReference<t_CType23>::mc_Value 
					&& NTraits::TCIsConstructorCallableWith<t_CType23, void ()>::mc_Value 
					&& NTraits::TCHasNothrowDefaultConstructor<t_CType23>::mc_Value
				) 
				? t_iMember23 :
#endif
#endif
				-1
				, mcp_AllHasNothrowCopyConstructor = (NTraits::TCHasNothrowCopyConstructor<t_CType0>::mc_Value || NTraits::TCIsVoid<t_CType0>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType1>::mc_Value || NTraits::TCIsVoid<t_CType1>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType2>::mc_Value || NTraits::TCIsVoid<t_CType2>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType3>::mc_Value || NTraits::TCIsVoid<t_CType3>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType4>::mc_Value || NTraits::TCIsVoid<t_CType4>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType5>::mc_Value || NTraits::TCIsVoid<t_CType5>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType6>::mc_Value || NTraits::TCIsVoid<t_CType6>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType7>::mc_Value || NTraits::TCIsVoid<t_CType7>::mc_Value)
#if DMibContainerVariantMany > 0
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType8>::mc_Value || NTraits::TCIsVoid<t_CType8>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType9>::mc_Value || NTraits::TCIsVoid<t_CType9>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType10>::mc_Value || NTraits::TCIsVoid<t_CType10>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType11>::mc_Value || NTraits::TCIsVoid<t_CType11>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType12>::mc_Value || NTraits::TCIsVoid<t_CType12>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType13>::mc_Value || NTraits::TCIsVoid<t_CType13>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType14>::mc_Value || NTraits::TCIsVoid<t_CType14>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType15>::mc_Value || NTraits::TCIsVoid<t_CType15>::mc_Value)
#if DMibContainerVariantMany > 1
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType16>::mc_Value || NTraits::TCIsVoid<t_CType16>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType17>::mc_Value || NTraits::TCIsVoid<t_CType17>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType18>::mc_Value || NTraits::TCIsVoid<t_CType18>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType19>::mc_Value || NTraits::TCIsVoid<t_CType19>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType20>::mc_Value || NTraits::TCIsVoid<t_CType20>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType21>::mc_Value || NTraits::TCIsVoid<t_CType21>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType22>::mc_Value || NTraits::TCIsVoid<t_CType22>::mc_Value)
				&& (NTraits::TCHasNothrowCopyConstructor<t_CType23>::mc_Value || NTraits::TCIsVoid<t_CType23>::mc_Value)
#endif
#endif
			};

			template <mint t_MaxSize, mint t_MaxAlignment, typename t_CDummy = void>
			struct TCDetermineStorageType
			{
				typedef uint8 CSizedType [mcp_MaxSize];
				typedef typename NTraits::TCAlign<CSizedType, t_MaxAlignment>::CType CType;
			};

			template <typename t_CDummy, mint t_MaxAlignment>
			struct TCDetermineStorageType<0, t_MaxAlignment, t_CDummy>
			{
				struct CType {};
			};

			
			struct CStorageType : public TCDetermineStorageType<mcp_MaxSize, mcp_MaxAlignment>::CType
			{
				CTypeIDStorageType m_CurrentType;
			};


			CStorageType m_Storage;

			inline_small void fp_SetTypeID(t_CIndexType const &_TypeID)
			{
				m_Storage.m_CurrentType = _TypeID;
			}


			template <t_CIndexType t_iMember>
			struct TCEvalReturnType
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CMemberType;
				typedef 
					typename TCChooseType
					<
						NTraits::TCIsRValueReference<CMemberType>::mc_Value
						, typename NTraits::TCAddRValueReference<CMemberType>::CType
						, typename NTraits::TCAddLValueReference<CMemberType>::CType
					>::CType 
				CType;
			};

			template <t_CIndexType t_iMember>
			struct TCEvalReturnTypeConst
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CMemberType;
				typedef 
					typename TCChooseType
					<
						NTraits::TCIsRValueReference<CMemberType>::mc_Value
						, typename NTraits::TCAddRValueReference<typename NTraits::TCAddConst<typename NTraits::TCRemoveRValueReference<CMemberType>::CType>::CType>::CType
						, typename NTraits::TCAddLValueReference<typename NTraits::TCAddConst<typename NTraits::TCRemoveLValueReference<CMemberType>::CType>::CType>::CType
					>::CType
				CType;
			};

			template <t_CIndexType t_iMember, typename t_CReturnType = typename TCEvalReturnType<t_iMember>::CType>
			struct TCCallVisitor
			{
			public:
				template <typename t_CThis, typename t_CVisitor>
				inline_small static void fs_Call(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					(fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAs<t_iMember>());
				}

				template <typename t_CRet, typename t_CThis, typename t_CVisitor>
				inline_small static t_CRet fs_CallRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					return (fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAs<t_iMember>());
				}

				template <typename t_CThis, typename t_CVisitor>
				inline_small static void fs_CallFirst(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					(fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAs<t_iMember>());
				}

				template <typename t_CRet, typename t_CThis, typename t_CVisitor>
				inline_small static t_CRet fs_CallFirstRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					return (fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAs<t_iMember>());
				}
			};

			template <t_CIndexType t_iMember>
			struct TCCallVisitor<t_iMember, void>
			{
			public:
				template <typename t_CThis, typename t_CVisitor>
				inline_small static void fs_Call(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					
				}

				template <typename t_CRet, typename t_CThis, typename t_CVisitor>
				inline_small static t_CRet fs_CallRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					return NPrivate::fg_InvalidVariant<t_CRet>();
				}
				template <typename t_CThis, typename t_CVisitor>
				inline_small static void fs_CallFirst(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					(fg_Forward<t_CVisitor>(_Visitor))(CVoidTag());
				}

				template <typename t_CRet, typename t_CThis, typename t_CVisitor>
				inline_small static t_CRet fs_CallFirstRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					return (fg_Forward<t_CVisitor>(_Visitor))(CVoidTag());
				}
			};

			template <t_CIndexType t_iMember, typename t_CReturnType = typename TCEvalReturnType<t_iMember>::CType>
			struct TCCallVisitorStorage
			{
			public:
				template <typename t_CThis, typename t_CVisitor>
				inline_small static void fs_Call(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					(fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>());
				}

				template <typename t_CRet, typename t_CThis, typename t_CVisitor>
				inline_small static t_CRet fs_CallRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					return (fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>());
				}

				template <typename t_CThis, typename t_CVisitor>
				inline_small static void fs_CallFirst(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					(fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>());
				}

				template <typename t_CRet, typename t_CThis, typename t_CVisitor>
				inline_small static t_CRet fs_CallFirstRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					return (fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template fp_GetAsStorage<t_iMember>());
				}
			};

			template <t_CIndexType t_iMember>
			struct TCCallVisitorStorage<t_iMember, void>
			{
			public:
				template <typename t_CThis, typename t_CVisitor>
				inline_small static void fs_Call(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					
				}

				template <typename t_CRet, typename t_CThis, typename t_CVisitor>
				inline_small static t_CRet fs_CallRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					return NPrivate::fg_InvalidVariant<t_CRet>();
				}
				template <typename t_CThis, typename t_CVisitor>
				inline_small static void fs_CallFirst(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					(fg_Forward<t_CVisitor>(_Visitor))(CVoidTag());
				}

				template <typename t_CRet, typename t_CThis, typename t_CVisitor>
				inline_small static t_CRet fs_CallFirstRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					return (fg_Forward<t_CVisitor>(_Visitor))(CVoidTag());
				}
			};
			
			template <t_CIndexType t_iMember, typename t_CReturnType = typename TCEvalReturnType<t_iMember>::CType>
			struct TCCallVisitorSet
			{
			public:
				template <typename t_CThis, typename t_CVisitor>
				inline_small static void fs_Call(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					(fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template f_Set<t_iMember>());
				}

				template <typename t_CRet, typename t_CThis, typename t_CVisitor>
				inline_small static t_CRet fs_CallRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					return (fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template f_Set<t_iMember>());
				}
				template <typename t_CThis, typename t_CVisitor>
				inline_small static void fs_CallFirst(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					(fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template f_Set<t_iMember>());
				}

				template <typename t_CRet, typename t_CThis, typename t_CVisitor>
				inline_small static t_CRet fs_CallFirstRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					return (fg_Forward<t_CVisitor>(_Visitor))((fg_Forward<t_CThis>(_pThis))->template f_Set<t_iMember>());
				}
			};

			template <t_CIndexType t_iMember>
			struct TCCallVisitorSet<t_iMember, void>
			{
			public:
				template <typename t_CThis, typename t_CVisitor>
				inline_small static void fs_Call(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					fg_Forward<t_CThis>(_pThis)->template f_Set<t_iMember>();
				}

				template <typename t_CRet, typename t_CThis, typename t_CVisitor>
				inline_small static t_CRet fs_CallRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					fg_Forward<t_CThis>(_pThis)->template f_Set<t_iMember>();
					return NPrivate::fg_InvalidVariant<t_CRet>();
				}
				template <typename t_CThis, typename t_CVisitor>
				inline_small static void fs_CallFirst(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					fg_Forward<t_CThis>(_pThis)->template f_Set<t_iMember>();
					(fg_Forward<t_CVisitor>(_Visitor))(CVoidTag());
				}

				template <typename t_CRet, typename t_CThis, typename t_CVisitor>
				inline_small static t_CRet fs_CallFirstRet(t_CThis &&_pThis, t_CVisitor &&_Visitor)
				{
					fg_Forward<t_CThis>(_pThis)->template f_Set<t_iMember>();
					return (fg_Forward<t_CVisitor>(_Visitor))(CVoidTag());
				}
			};

			template <typename t_CType, bint t_bIsReference = NTraits::TCIsReference<t_CType>::mc_Value, bint t_bIsArray = NTraits::TCIsArray<t_CType>::mc_Value>
			struct TCEvalReturn
			{
			public:

				template <typename tf_CType0, typename tf_CType1>
				inline_small static auto fs_Value(tf_CType1 &&_pToRet) -> decltype(*_pToRet)
				{
					return *_pToRet;
				}
			};

			template <typename t_CType>
			struct TCEvalReturn<t_CType, false, true>
			{
			public:

				template <typename tf_CType0, typename tf_CType1>
				inline_small static t_CType &fs_Value(tf_CType1 &&_pToRet)
				{
					return (t_CType &)*_pToRet;
				}
			};

			template <typename t_CType>
			struct TCEvalReturn<t_CType, true, false>
			{
			public:

				template <typename tf_CType0, typename tf_CType1>
				inline_small static typename TCEnableIf<NTraits::TCIsLValueReference<tf_CType0>::mc_Value, tf_CType0>::CType fs_Value(tf_CType1 &&_pToRet)
				{
					return *(*_pToRet);
				}

				template <typename tf_CType0, typename tf_CType1>
				inline_small static typename TCEnableIf<!NTraits::TCIsLValueReference<tf_CType0>::mc_Value, tf_CType0>::CType fs_Value(tf_CType1 &&_pToRet)
				{
					return NMib::fg_Move(*(*_pToRet));
				}
			};

			template <t_CIndexType t_iMember>
			inline_small typename TCEnableIf<!NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, typename TCEvalReturnType<t_iMember>::CType>::CType fp_GetAs()
			{
				// && !NTraits::TCIsReference<typename TCTypeFromMember<t_iMember>::CType>::mc_Value
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				CConstructType *pRet = (CConstructType *)&m_Storage;
				typedef typename TCEvalReturnType<t_iMember>::CType CReturnType;
				return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
			}

			template <t_CIndexType t_iMember>
			inline_small typename TCEnableIf<NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, typename TCEvalReturnType<t_iMember>::CType>::CType fp_GetAs() const
			{
			}

			template <t_CIndexType t_iMember>
			inline_small typename TCEnableIf<!NTraits::TCIsVoid<typename TCEvalReturnTypeConst<t_iMember>::CType>::mc_Value, typename TCEvalReturnTypeConst<t_iMember>::CType>::CType fp_GetAs() const
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				CConstructType const *pRet = (CConstructType const *)&m_Storage;
				typedef typename TCEvalReturnTypeConst<t_iMember>::CType CReturnType;
				return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
			}
			
			///
			
			template <t_CIndexType t_iMember>
			inline_small typename TCEnableIf<!NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, typename NTraits::TCAddLValueReference<typename TCEvalConstructType<t_iMember>::CType>::CType>::CType fp_GetAsStorage()
			{
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				CConstructType *pRet = (CConstructType *)&m_Storage;
				return *pRet;
			}

			template <t_CIndexType t_iMember>
			inline_small typename TCEnableIf<NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, typename TCEvalReturnType<t_iMember>::CType>::CType fp_GetAsStorage() const
			{
			}

			template <t_CIndexType t_iMember>
			inline_small typename TCEnableIf<!NTraits::TCIsVoid<typename TCEvalReturnTypeConst<t_iMember>::CType>::mc_Value, typename NTraits::TCAddLValueReference<typename NTraits::TCAddConst<typename TCEvalConstructType<t_iMember>::CType>::CType>::CType>::CType fp_GetAsStorage() const
			{
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				CConstructType const *pRet = (CConstructType const *)&m_Storage;
				return *pRet;
			}
		
			
			///

			template <typename t_CVisitor>
			void fp_VisitStorage(t_CVisitor &&_Visitor)
			{
				if (f_GetTypeID() == t_iMember0)
					TCCallVisitorStorage<t_iMember0>::fs_CallFirst(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember1)
					TCCallVisitorStorage<t_iMember1>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember2)
					TCCallVisitorStorage<t_iMember2>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember3)
					TCCallVisitorStorage<t_iMember3>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember4)
					TCCallVisitorStorage<t_iMember4>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember5)
					TCCallVisitorStorage<t_iMember5>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember6)
					TCCallVisitorStorage<t_iMember6>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember7)
					TCCallVisitorStorage<t_iMember7>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 0
				else if (f_GetTypeID() == t_iMember8)
					TCCallVisitorStorage<t_iMember8>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember9)
					TCCallVisitorStorage<t_iMember9>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember10)
					TCCallVisitorStorage<t_iMember10>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember11)
					TCCallVisitorStorage<t_iMember11>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember12)
					TCCallVisitorStorage<t_iMember12>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember13)
					TCCallVisitorStorage<t_iMember13>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember14)
					TCCallVisitorStorage<t_iMember14>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember15)
					TCCallVisitorStorage<t_iMember15>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 1
				else if (f_GetTypeID() == t_iMember16)
					TCCallVisitorStorage<t_iMember16>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember17)
					TCCallVisitorStorage<t_iMember17>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember18)
					TCCallVisitorStorage<t_iMember18>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember19)
					TCCallVisitorStorage<t_iMember19>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember20)
					TCCallVisitorStorage<t_iMember20>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember21)
					TCCallVisitorStorage<t_iMember21>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember22)
					TCCallVisitorStorage<t_iMember22>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember23)
					TCCallVisitorStorage<t_iMember23>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
#endif
#endif
				else
				{
					DMibNeverGetHere;
				}
			}
			
		public:
		
			template <typename t_CVisitor>
			void f_Visit(t_CVisitor &&_Visitor)
			{
				if (f_GetTypeID() == t_iMember0)
					TCCallVisitor<t_iMember0>::fs_CallFirst(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember1)
					TCCallVisitor<t_iMember1>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember2)
					TCCallVisitor<t_iMember2>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember3)
					TCCallVisitor<t_iMember3>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember4)
					TCCallVisitor<t_iMember4>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember5)
					TCCallVisitor<t_iMember5>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember6)
					TCCallVisitor<t_iMember6>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember7)
					TCCallVisitor<t_iMember7>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 0
				else if (f_GetTypeID() == t_iMember8)
					TCCallVisitor<t_iMember8>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember9)
					TCCallVisitor<t_iMember9>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember10)
					TCCallVisitor<t_iMember10>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember11)
					TCCallVisitor<t_iMember11>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember12)
					TCCallVisitor<t_iMember12>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember13)
					TCCallVisitor<t_iMember13>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember14)
					TCCallVisitor<t_iMember14>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember15)
					TCCallVisitor<t_iMember15>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 1
				else if (f_GetTypeID() == t_iMember16)
					TCCallVisitor<t_iMember16>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember17)
					TCCallVisitor<t_iMember17>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember18)
					TCCallVisitor<t_iMember18>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember19)
					TCCallVisitor<t_iMember19>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember20)
					TCCallVisitor<t_iMember20>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember21)
					TCCallVisitor<t_iMember21>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember22)
					TCCallVisitor<t_iMember22>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember23)
					TCCallVisitor<t_iMember23>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
#endif
#endif
				else
				{
					DMibNeverGetHere;
				}
			}

			template <typename t_CVisitor>
			void f_Visit(t_CVisitor &&_Visitor) const
			{
				if (f_GetTypeID() == t_iMember0)
					TCCallVisitor<t_iMember0>::fs_CallFirst(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember1)
					TCCallVisitor<t_iMember1>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember2)
					TCCallVisitor<t_iMember2>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember3)
					TCCallVisitor<t_iMember3>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember4)
					TCCallVisitor<t_iMember4>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember5)
					TCCallVisitor<t_iMember5>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember6)
					TCCallVisitor<t_iMember6>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember7)
					TCCallVisitor<t_iMember7>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 0
				else if (f_GetTypeID() == t_iMember8)
					TCCallVisitor<t_iMember8>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember9)
					TCCallVisitor<t_iMember9>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember10)
					TCCallVisitor<t_iMember10>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember11)
					TCCallVisitor<t_iMember11>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember12)
					TCCallVisitor<t_iMember12>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember13)
					TCCallVisitor<t_iMember13>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember14)
					TCCallVisitor<t_iMember14>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember15)
					TCCallVisitor<t_iMember15>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 1
				else if (f_GetTypeID() == t_iMember16)
					TCCallVisitor<t_iMember16>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember17)
					TCCallVisitor<t_iMember17>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember18)
					TCCallVisitor<t_iMember18>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember19)
					TCCallVisitor<t_iMember19>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember20)
					TCCallVisitor<t_iMember20>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember21)
					TCCallVisitor<t_iMember21>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember22)
					TCCallVisitor<t_iMember22>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember23)
					TCCallVisitor<t_iMember23>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
#endif
#endif
				else
				{
					DMibNeverGetHere;
				}
			}


			template <typename t_CReturn, typename t_CVisitor>
			t_CReturn f_VisitRet(t_CVisitor &&_Visitor)
			{
				if (f_GetTypeID() == t_iMember0)
					return TCCallVisitor<t_iMember0>::template fs_CallFirstRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember1)
					return TCCallVisitor<t_iMember1>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember2)
					return TCCallVisitor<t_iMember2>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember3)
					return TCCallVisitor<t_iMember3>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember4)
					return TCCallVisitor<t_iMember4>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember5)
					return TCCallVisitor<t_iMember5>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember6)
					return TCCallVisitor<t_iMember6>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember7)
					return TCCallVisitor<t_iMember7>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 0
				else if (f_GetTypeID() == t_iMember8)
					return TCCallVisitor<t_iMember8>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember9)
					return TCCallVisitor<t_iMember9>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember10)
					return TCCallVisitor<t_iMember10>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember11)
					return TCCallVisitor<t_iMember11>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember12)
					return TCCallVisitor<t_iMember12>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember13)
					return TCCallVisitor<t_iMember13>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember14)
					return TCCallVisitor<t_iMember14>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember15)
					return TCCallVisitor<t_iMember15>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 1
				else if (f_GetTypeID() == t_iMember16)
					return TCCallVisitor<t_iMember16>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember17)
					return TCCallVisitor<t_iMember17>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember18)
					return TCCallVisitor<t_iMember18>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember19)
					return TCCallVisitor<t_iMember19>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember20)
					return TCCallVisitor<t_iMember20>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember21)
					return TCCallVisitor<t_iMember21>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember22)
					return TCCallVisitor<t_iMember22>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember23)
					return TCCallVisitor<t_iMember23>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
#endif
#endif
				else
				{
					DMibNeverGetHere;
				}
				return NPrivate::fg_InvalidVariant<t_CReturn>();
			}

			template <typename t_CReturn, typename t_CVisitor>
			t_CReturn f_VisitRet(t_CVisitor &&_Visitor) const
			{
				if (f_GetTypeID() == t_iMember0)
					return TCCallVisitor<t_iMember0>::template fs_CallFirstRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember1)
					return TCCallVisitor<t_iMember1>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember2)
					return TCCallVisitor<t_iMember2>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember3)
					return TCCallVisitor<t_iMember3>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember4)
					return TCCallVisitor<t_iMember4>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember5)
					return TCCallVisitor<t_iMember5>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember6)
					return TCCallVisitor<t_iMember6>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember7)
					return TCCallVisitor<t_iMember7>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 0
				else if (f_GetTypeID() == t_iMember8)
					return TCCallVisitor<t_iMember8>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember9)
					return TCCallVisitor<t_iMember9>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember10)
					return TCCallVisitor<t_iMember10>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember11)
					return TCCallVisitor<t_iMember11>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember12)
					return TCCallVisitor<t_iMember12>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember13)
					return TCCallVisitor<t_iMember13>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember14)
					return TCCallVisitor<t_iMember14>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember15)
					return TCCallVisitor<t_iMember15>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 1
				else if (f_GetTypeID() == t_iMember16)
					return TCCallVisitor<t_iMember16>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember17)
					return TCCallVisitor<t_iMember17>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember18)
					return TCCallVisitor<t_iMember18>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember19)
					return TCCallVisitor<t_iMember19>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember20)
					return TCCallVisitor<t_iMember20>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember21)
					return TCCallVisitor<t_iMember21>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember22)
					return TCCallVisitor<t_iMember22>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (f_GetTypeID() == t_iMember23)
					return TCCallVisitor<t_iMember23>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
#endif
#endif
				else
				{
					DMibNeverGetHere;
				}
				return NPrivate::fg_InvalidVariant<t_CReturn>();
			}

			template <typename t_CVisitor>
			void f_VisitCreate(t_CIndexType const &_Index, t_CVisitor &&_Visitor)
			{
				if (_Index == t_iMember0)
					TCCallVisitorSet<t_iMember0>::fs_CallFirst(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember1)
					TCCallVisitorSet<t_iMember1>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember2)
					TCCallVisitorSet<t_iMember2>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember3)
					TCCallVisitorSet<t_iMember3>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember4)
					TCCallVisitorSet<t_iMember4>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember5)
					TCCallVisitorSet<t_iMember5>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember6)
					TCCallVisitorSet<t_iMember6>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember7)
					TCCallVisitorSet<t_iMember7>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 0
				else if (_Index == t_iMember8)
					TCCallVisitorSet<t_iMember8>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember9)
					TCCallVisitorSet<t_iMember9>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember10)
					TCCallVisitorSet<t_iMember10>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember11)
					TCCallVisitorSet<t_iMember11>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember12)
					TCCallVisitorSet<t_iMember12>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember13)
					TCCallVisitorSet<t_iMember13>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember14)
					TCCallVisitorSet<t_iMember14>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember15)
					TCCallVisitorSet<t_iMember15>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 1
				else if (_Index == t_iMember16)
					TCCallVisitorSet<t_iMember16>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember17)
					TCCallVisitorSet<t_iMember17>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember18)
					TCCallVisitorSet<t_iMember18>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember19)
					TCCallVisitorSet<t_iMember19>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember20)
					TCCallVisitorSet<t_iMember20>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember21)
					TCCallVisitorSet<t_iMember21>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember22)
					TCCallVisitorSet<t_iMember22>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember23)
					TCCallVisitorSet<t_iMember23>::fs_Call(this, fg_Forward<t_CVisitor>(_Visitor));
#endif
#endif
				else
				{
					DMibNeverGetHere;
				}				
			}

			template <typename t_CReturn, typename t_CVisitor>
			t_CReturn f_VisitCreateReturn(t_CIndexType const &_Index, t_CVisitor &&_Visitor)
			{
				if (_Index == t_iMember0)
					return TCCallVisitorSet<t_iMember0>::template fs_CallFirstRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember1)
					return TCCallVisitorSet<t_iMember1>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember2)
					return TCCallVisitorSet<t_iMember2>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember3)
					return TCCallVisitorSet<t_iMember3>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember4)
					return TCCallVisitorSet<t_iMember4>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember5)
					return TCCallVisitorSet<t_iMember5>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember6)
					return TCCallVisitorSet<t_iMember6>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember7)
					return TCCallVisitorSet<t_iMember7>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 0
				else if (_Index == t_iMember8)
					return TCCallVisitorSet<t_iMember8>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember9)
					return TCCallVisitorSet<t_iMember9>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember10)
					return TCCallVisitorSet<t_iMember10>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember11)
					return TCCallVisitorSet<t_iMember11>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember12)
					return TCCallVisitorSet<t_iMember12>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember13)
					return TCCallVisitorSet<t_iMember13>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember14)
					return TCCallVisitorSet<t_iMember14>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember15)
					return TCCallVisitorSet<t_iMember15>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
#if DMibContainerVariantMany > 1
				else if (_Index == t_iMember16)
					return TCCallVisitorSet<t_iMember16>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember17)
					return TCCallVisitorSet<t_iMember17>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember18)
					return TCCallVisitorSet<t_iMember18>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember19)
					return TCCallVisitorSet<t_iMember19>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember20)
					return TCCallVisitorSet<t_iMember20>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember21)
					return TCCallVisitorSet<t_iMember21>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember22)
					return TCCallVisitorSet<t_iMember22>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
				else if (_Index == t_iMember23)
					return TCCallVisitorSet<t_iMember23>::template fs_CallRet<t_CReturn>(this, fg_Forward<t_CVisitor>(_Visitor));
#endif
#endif
				else
				{
					DMibNeverGetHere;
				}				
				return NPrivate::fg_InvalidVariant<t_CReturn>();
			}

		private:

			void fp_DestroyCurrent()
			{
				fp_VisitStorage(NPrivate::CVariantVisitor_Destruct());
			}

			////////////////////////////////////////
			//
			template <t_CIndexType t_iMember>
			typename TCEnableIf<!NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, typename TCEvalReturnType<t_iMember>::CType>::CType fp_Set()
			{
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				auto pRet = new(&m_Storage) CConstructType();
				fp_SetTypeID(t_iMember);
				typedef typename TCEvalReturnType<t_iMember>::CType CReturnType;
				return TCEvalReturn<typename TCTypeFromMember<t_iMember>::CType>::template fs_Value<CReturnType>(pRet);
			}

			template <t_CIndexType t_iMember>
			typename TCEnableIf<NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, typename TCEvalReturnType<t_iMember>::CType>::CType fp_Set()
			{
				fp_SetTypeID(t_iMember);
			}

			template <t_CIndexType t_iMember, typename t_CParam0>
			typename TCEnableIf<!NTraits::TCIsReference<typename TCTypeFromMember<t_iMember>::CType>::mc_Value , typename TCEvalReturnType<t_iMember>::CType>::CType 
			fp_Set
			(
				t_CParam0 &&_Param0
			)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert(NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&)>::mc_Value, "This type cannot be constructed with the arguments suppied");
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				auto pRet = new(&m_Storage) CConstructType(fg_Forward<t_CParam0>(_Param0));
				fp_SetTypeID(t_iMember);
				typedef typename TCEvalReturnType<t_iMember>::CType CReturnType;
				return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
			}

			template <t_CIndexType t_iMember, typename t_CParam0>
			typename TCEnableIf<NTraits::TCIsReference<typename TCTypeFromMember<t_iMember>::CType>::mc_Value, typename TCEvalReturnType<t_iMember>::CType>::CType 
			fp_Set
			(
				t_CParam0 &&_Param0
			)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert(NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&)>::mc_Value, "This type cannot be constructed with the arguments suppied");
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				auto pRet = new(&m_Storage) CConstructType(&_Param0);
				fp_SetTypeID(t_iMember);
				typedef typename TCEvalReturnType<t_iMember>::CType CReturnType;
				return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1>
			typename TCEvalReturnType<t_iMember>::CType fp_Set(t_CParam0 &&_Param0, t_CParam1 &&_Param1)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert(NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&, t_CParam1 &&)>::mc_Value, "This type cannot be constructed with the arguments suppied");
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				auto pRet = new(&m_Storage) CConstructType(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1));
				fp_SetTypeID(t_iMember);
				typedef typename TCEvalReturnType<t_iMember>::CType CReturnType;
				return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2>
			typename TCEvalReturnType<t_iMember>::CType fp_Set(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert(NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&)>::mc_Value, "This type cannot be constructed with the arguments suppied");
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				auto pRet = new(&m_Storage) CConstructType(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2));
				fp_SetTypeID(t_iMember);
				typedef typename TCEvalReturnType<t_iMember>::CType CReturnType;
				return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3>
			typename TCEvalReturnType<t_iMember>::CType fp_Set(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert(NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&, t_CParam3 &&)>::mc_Value, "This type cannot be constructed with the arguments suppied");
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				auto pRet = new(&m_Storage) CConstructType(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3));
				fp_SetTypeID(t_iMember);
				typedef typename TCEvalReturnType<t_iMember>::CType CReturnType;
				return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4>
			typename TCEvalReturnType<t_iMember>::CType fp_Set(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert
				(	
					NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&, t_CParam3 &&, t_CParam4 &&)>::mc_Value
					, "This type cannot be constructed with the arguments suppied"
				);
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				auto pRet = new(&m_Storage) 
					CConstructType
					(
						fg_Forward<t_CParam0>(_Param0), 
						fg_Forward<t_CParam1>(_Param1), 
						fg_Forward<t_CParam2>(_Param2), 
						fg_Forward<t_CParam3>(_Param3), 
						fg_Forward<t_CParam4>(_Param4)
					);
				fp_SetTypeID(t_iMember);
				typedef typename TCEvalReturnType<t_iMember>::CType CReturnType;
				return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5>
			typename TCEvalReturnType<t_iMember>::CType fp_Set(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4, t_CParam5 &&_Param5)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert
				(
					NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&, t_CParam3 &&, t_CParam4 &&, t_CParam5 &&)>::mc_Value
					, "This type cannot be constructed with the arguments suppied"
				);
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				auto pRet = new(&m_Storage) 
					CConstructType
					(
						fg_Forward<t_CParam0>(_Param0)
						, fg_Forward<t_CParam1>(_Param1)
						, fg_Forward<t_CParam2>(_Param2)
						, fg_Forward<t_CParam3>(_Param3)
						, fg_Forward<t_CParam4>(_Param4)
						, fg_Forward<t_CParam5>(_Param5)
					);
				fp_SetTypeID(t_iMember);
				typedef typename TCEvalReturnType<t_iMember>::CType CReturnType;
				return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5, typename t_CParam6>
			typename TCEvalReturnType<t_iMember>::CType 
			fp_Set
			(
				t_CParam0 &&_Param0
				, t_CParam1 &&_Param1
				, t_CParam2 &&_Param2
				, t_CParam3 &&_Param3
				, t_CParam4 &&_Param4
				, t_CParam5 &&_Param5
				, t_CParam6 &&_Param6
			)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert
				(
					NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&, t_CParam3 &&, t_CParam4 &&, t_CParam5 &&, t_CParam6 &&)>::mc_Value
					, "This type cannot be constructed with the arguments suppied"
				);
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				auto pRet = new(&m_Storage) 
					CConstructType
					(
						fg_Forward<t_CParam0>(_Param0)
						, fg_Forward<t_CParam1>(_Param1)
						, fg_Forward<t_CParam2>(_Param2)
						, fg_Forward<t_CParam3>(_Param3)
						, fg_Forward<t_CParam4>(_Param4)
						, fg_Forward<t_CParam5>(_Param5)
						, fg_Forward<t_CParam6>(_Param6)
					);
				fp_SetTypeID(t_iMember);
				typedef typename TCEvalReturnType<t_iMember>::CType CReturnType;
				return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
			}

			template 
			<
				t_CIndexType t_iMember
				, typename t_CParam0
				, typename t_CParam1
				, typename t_CParam2
				, typename t_CParam3
				, typename t_CParam4
				, typename t_CParam5
				, typename t_CParam6
				, typename t_CParam7
			>
			typename TCEvalReturnType<t_iMember>::CType 
			fp_Set
			(
				t_CParam0 &&_Param0
				, t_CParam1 &&_Param1
				, t_CParam2 &&_Param2
				, t_CParam3 &&_Param3
				, t_CParam4 &&_Param4
				, t_CParam5 &&_Param5
				, t_CParam6 &&_Param6
				, t_CParam6 &&_Param7
			)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert
				(
					NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&, t_CParam3 &&, t_CParam4 &&, t_CParam5 &&, t_CParam6 &&, t_CParam7 &&)>::mc_Value
					, "This type cannot be constructed with the arguments suppied"
				);
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				auto pRet = new(&m_Storage) 
					CConstructType
					(
						fg_Forward<t_CParam0>(_Param0)
						, fg_Forward<t_CParam1>(_Param1)
						, fg_Forward<t_CParam2>(_Param2)
						, fg_Forward<t_CParam3>(_Param3)
						, fg_Forward<t_CParam4>(_Param4)
						, fg_Forward<t_CParam5>(_Param5)
						, fg_Forward<t_CParam6>(_Param6)
						, fg_Forward<t_CParam7>(_Param7)
					);
				fp_SetTypeID(t_iMember);
				typedef typename TCEvalReturnType<t_iMember>::CType CReturnType;
				return TCEvalReturn<CType>::template fs_Value<CReturnType>(pRet);
			}

			////////////////////////////////////////
			//
			template <t_CIndexType t_iMember>
			typename TCEnableIf<!NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, void>::CType fp_SetNoRet()
			{
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				new((void *)&m_Storage) CConstructType();
				fp_SetTypeID(t_iMember);
			}

			template <t_CIndexType t_iMember>
			typename TCEnableIf<NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, void>::CType fp_SetNoRet()
			{
				fp_SetTypeID(t_iMember);
			}

			template <t_CIndexType t_iMember, typename t_CParam0>
			typename TCEnableIf<!NTraits::TCIsReference<typename TCTypeFromMember<t_iMember>::CType>::mc_Value, void>::CType 
			fp_SetNoRet
			(
				t_CParam0 &&_Param0
			)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert(NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&)>::mc_Value, "This type cannot be constructed with the arguments suppied");
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				new(&m_Storage) CConstructType(fg_Forward<t_CParam0>(_Param0));
				fp_SetTypeID(t_iMember);
			}

			template <t_CIndexType t_iMember, typename t_CParam0>
			typename TCEnableIf<NTraits::TCIsReference<typename TCTypeFromMember<t_iMember>::CType>::mc_Value, void>::CType 
			fp_SetNoRet
			(
				t_CParam0 &&_Param0
			)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert(NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&)>::mc_Value, "This type cannot be constructed with the arguments suppied");
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				new(&m_Storage) CConstructType(&_Param0);
				fp_SetTypeID(t_iMember);
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1>
			void fp_SetNoRet(t_CParam0 &&_Param0, t_CParam1 &&_Param1)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert(NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&, t_CParam1 &&)>::mc_Value, "This type cannot be constructed with the arguments suppied");
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				new(&m_Storage) CConstructType(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1));
				fp_SetTypeID(t_iMember);
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2>
			void fp_SetNoRet(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert(NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&)>::mc_Value, "This type cannot be constructed with the arguments suppied");
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				new(&m_Storage) CConstructType(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2));
				fp_SetTypeID(t_iMember);
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3>
			void fp_SetNoRet(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert(NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 && , t_CParam1 &&, t_CParam2 &&, t_CParam3 &&)>::mc_Value, "This type cannot be constructed with the arguments suppied");
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				new(&m_Storage) CConstructType(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3));
				fp_SetTypeID(t_iMember);
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4>
			void fp_SetNoRet(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert
				(	
					NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&, t_CParam3 &&, t_CParam4 &&)>::mc_Value
					, "This type cannot be constructed with the arguments suppied"
				);
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				new(&m_Storage) 
					CConstructType
					(
						fg_Forward<t_CParam0>(_Param0), 
						fg_Forward<t_CParam1>(_Param1), 
						fg_Forward<t_CParam2>(_Param2), 
						fg_Forward<t_CParam3>(_Param3), 
						fg_Forward<t_CParam4>(_Param4)
					);
				fp_SetTypeID(t_iMember);
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5>
			void fp_SetNoRet(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4, t_CParam5 &&_Param5)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert
				(
					NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&, t_CParam3 &&, t_CParam4 &&, t_CParam5 &&)>::mc_Value
					, "This type cannot be constructed with the arguments suppied"
				);
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				new(&m_Storage) 
					CConstructType
					(
						fg_Forward<t_CParam0>(_Param0)
						, fg_Forward<t_CParam1>(_Param1)
						, fg_Forward<t_CParam2>(_Param2)
						, fg_Forward<t_CParam3>(_Param3)
						, fg_Forward<t_CParam4>(_Param4)
						, fg_Forward<t_CParam5>(_Param5)
					);
				fp_SetTypeID(t_iMember);
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5, typename t_CParam6>
			void
			fp_SetNoRet
			(
				t_CParam0 &&_Param0
				, t_CParam1 &&_Param1
				, t_CParam2 &&_Param2
				, t_CParam3 &&_Param3
				, t_CParam4 &&_Param4
				, t_CParam5 &&_Param5
				, t_CParam6 &&_Param6
			)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert
				(
					NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&, t_CParam3 &&, t_CParam4 &&, t_CParam5 &&, t_CParam6 &&)>::mc_Value
					, "This type cannot be constructed with the arguments suppied"
				);
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				new(&m_Storage) 
					CConstructType
					(
						fg_Forward<t_CParam0>(_Param0)
						, fg_Forward<t_CParam1>(_Param1)
						, fg_Forward<t_CParam2>(_Param2)
						, fg_Forward<t_CParam3>(_Param3)
						, fg_Forward<t_CParam4>(_Param4)
						, fg_Forward<t_CParam5>(_Param5)
						, fg_Forward<t_CParam6>(_Param6)
					);
				fp_SetTypeID(t_iMember);
			}

			template 
			<
				t_CIndexType t_iMember
				, typename t_CParam0
				, typename t_CParam1
				, typename t_CParam2
				, typename t_CParam3
				, typename t_CParam4
				, typename t_CParam5
				, typename t_CParam6
				, typename t_CParam7
			>
			void
			fp_SetNoRet
			(
				t_CParam0 &&_Param0
				, t_CParam1 &&_Param1
				, t_CParam2 &&_Param2
				, t_CParam3 &&_Param3
				, t_CParam4 &&_Param4
				, t_CParam5 &&_Param5
				, t_CParam6 &&_Param6
				, t_CParam6 &&_Param7
			)
			{
				typedef typename TCTypeFromMember<t_iMember>::CType CType;
				static_assert
				(
					NTraits::TCIsConstructorCallableWith<CType, void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&, t_CParam3 &&, t_CParam4 &&, t_CParam5 &&, t_CParam6 &&, t_CParam7 &&)>::mc_Value
					, "This type cannot be constructed with the arguments suppied"
				);
				typedef typename TCEvalConstructType<t_iMember>::CType CConstructType;
				new(&m_Storage) 
					CConstructType
					(
						fg_Forward<t_CParam0>(_Param0)
						, fg_Forward<t_CParam1>(_Param1)
						, fg_Forward<t_CParam2>(_Param2)
						, fg_Forward<t_CParam3>(_Param3)
						, fg_Forward<t_CParam4>(_Param4)
						, fg_Forward<t_CParam5>(_Param5)
						, fg_Forward<t_CParam6>(_Param6)
						, fg_Forward<t_CParam7>(_Param7)
					);
				fp_SetTypeID(t_iMember);
			}

			///////////////////////////////////
			///////////////////////////////////
			///////////////////////////////////
		protected:
			template <typename t_CInType>
			class TCEvalOneParamConstruction
			{
			public:
				typedef typename NTraits::TCRemoveReferenceStorable<t_CInType>::CType CInTypeNoRef;
				typedef typename NTraits::TCRemoveQualifiers<CInTypeNoRef>::CType CInTypeNoRefNoQualifier;
				enum
				{
					mc_Value = TCChooseInt
					<
						int
						, (TCMemberFromType<CInTypeNoRef>::mc_Value >= 0) && NTraits::TCIsConstructorCallableWith<CInTypeNoRef, void (t_CInType)>::mc_Value
						, TCMemberFromType<CInTypeNoRef>::mc_Value
						, TCChooseInt
						<
							int
							, (TCMemberFromType<CInTypeNoRefNoQualifier>::mc_Value >= 0) && NTraits::TCIsConstructorCallableWith<CInTypeNoRefNoQualifier, void (t_CInType)>::mc_Value
							, TCMemberFromType<CInTypeNoRefNoQualifier>::mc_Value
							, TCChooseInt
							<
								int
								, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember0>::CType, void (t_CInType)>::mc_Value
								, t_iMember0
								, TCChooseInt
								<
									int
									, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember1>::CType, void (t_CInType)>::mc_Value
									, t_iMember1
									, TCChooseInt
									<
										int
										, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember2>::CType, void (t_CInType)>::mc_Value
										, t_iMember2
										, TCChooseInt
										<
											int
											, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember3>::CType, void (t_CInType)>::mc_Value
											, t_iMember3
											, TCChooseInt
											<
												int
												, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember4>::CType, void (t_CInType)>::mc_Value
												, t_iMember4
												, TCChooseInt
												<
													int
													, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember5>::CType, void (t_CInType)>::mc_Value
													, t_iMember5
													, TCChooseInt
													<
														int
														, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember6>::CType, void (t_CInType)>::mc_Value
														, t_iMember6
														, TCChooseInt
														<
															int
															, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember7>::CType, void (t_CInType)>::mc_Value
															, t_iMember7
	#if DMibContainerVariantMany > 0
															, TCChooseInt
															<
																int
																, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember8>::CType, void (t_CInType)>::mc_Value
																, t_iMember8
																, TCChooseInt
																<
																	int
																	, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember9>::CType, void (t_CInType)>::mc_Value
																	, t_iMember9
																	, TCChooseInt
																	<
																		int
																		, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember10>::CType, void (t_CInType)>::mc_Value
																		, t_iMember10
																		, TCChooseInt
																		<
																			int
																			, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember11>::CType, void (t_CInType)>::mc_Value
																			, t_iMember11
																			, TCChooseInt
																			<
																				int
																				, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember12>::CType, void (t_CInType)>::mc_Value
																				, t_iMember12
																				, TCChooseInt
																				<
																					int
																					, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember13>::CType, void (t_CInType)>::mc_Value
																					, t_iMember13
																					, TCChooseInt
																					<
																						int
																						, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember14>::CType, void (t_CInType)>::mc_Value
																						, t_iMember14
																						, TCChooseInt
																						<
																							int
																							, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember15>::CType, void (t_CInType)>::mc_Value
																							, t_iMember15
	#if DMibContainerVariantMany > 1
																							, TCChooseInt
																							<
																								int
																								, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember16>::CType, void (t_CInType)>::mc_Value
																								, t_iMember16
																								, TCChooseInt
																								<
																									int
																									, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember17>::CType, void (t_CInType)>::mc_Value
																									, t_iMember17
																									, TCChooseInt
																									<
																										int
																										, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember18>::CType, void (t_CInType)>::mc_Value
																										, t_iMember18
																										, TCChooseInt
																										<
																											int
																											, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember19>::CType, void (t_CInType)>::mc_Value
																											, t_iMember19
																											, TCChooseInt
																											<
																												int
																												, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember20>::CType, void (t_CInType)>::mc_Value
																												, t_iMember20
																												, TCChooseInt
																												<
																													int
																													, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember21>::CType, void (t_CInType)>::mc_Value
																													, t_iMember21
																													, TCChooseInt
																													<
																														int
																														, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember22>::CType, void (t_CInType)>::mc_Value
																														, t_iMember22
																														, TCChooseInt
																														<
																															int
																															, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember23>::CType, void (t_CInType)>::mc_Value
																															, t_iMember23
																															, -1
																														>::mc_Value
																													>::mc_Value
																												>::mc_Value
																											>::mc_Value
																										>::mc_Value
																									>::mc_Value
																								>::mc_Value
																							>::mc_Value
	#else
																							, -1
	#endif
																						>::mc_Value
																					>::mc_Value
																				>::mc_Value
																			>::mc_Value
																		>::mc_Value
																	>::mc_Value
																>::mc_Value
															>::mc_Value
	#else
															, -1
	#endif
														>::mc_Value
													>::mc_Value
												>::mc_Value
											>::mc_Value
										>::mc_Value
									>::mc_Value
								>::mc_Value
							>::mc_Value
						>::mc_Value
					>::mc_Value
				};
			};

		private:
			template <typename t_CParam>
			struct TCIsNoThrowConstructibleWith
			{
				enum
				{
					mc_ToConstruct = TCEvalOneParamConstruction<t_CParam>::mc_Value
				};

				typedef typename TCTypeFromMember<(t_CIndexType)mc_ToConstruct>::CType CTypeToConstruct;
				enum
				{
					mc_Value 
					= mc_ToConstruct >= 0 && NTraits::TCHasNothrowCopyConstructor<CTypeToConstruct>::mc_Value 
					&& 
					(
						NTraits::TCIsSame<typename NTraits::TCRemoveQualifiers<CTypeToConstruct>::CType, typename NTraits::TCRemoveQualifiers<t_CParam>::CType>::mc_Value
						|| 
						(
							!NTraits::TCIsReference<CTypeToConstruct>::mc_Value 
							&& NTraits::TCIsReference<t_CParam>::mc_Value 
							&& NTraits::TCIsSame<typename NTraits::TCRemoveQualifiers<CTypeToConstruct>::CType, typename NTraits::TCRemoveQualifiers<typename NTraits::TCRemoveReference<t_CParam>::CType>::CType>::mc_Value
						)
					)
				};
			};
		
			template <typename t_CInType>
			class TCEvalManyParamConstruction
			{
			public:
				enum
				{
					mc_Value = TCChooseInt
					<
						int
						, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember0>::CType, t_CInType>::mc_Value
						, t_iMember0
						, TCChooseInt
						<
							int
							, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember1>::CType, t_CInType>::mc_Value
							, t_iMember1
							, TCChooseInt
							<
								int
								, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember2>::CType, t_CInType>::mc_Value
								, t_iMember2
								, TCChooseInt
								<
									int
									, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember3>::CType, t_CInType>::mc_Value
									, t_iMember3
									, TCChooseInt
									<
										int
										, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember4>::CType, t_CInType>::mc_Value
										, t_iMember4
										, TCChooseInt
										<
											int
											, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember5>::CType, t_CInType>::mc_Value
											, t_iMember5
											, TCChooseInt
											<
												int
												, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember6>::CType, t_CInType>::mc_Value
												, t_iMember6
												, TCChooseInt
												<
													int
													, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember7>::CType, t_CInType>::mc_Value
													, t_iMember7
	#if DMibContainerVariantMany > 0
													, TCChooseInt
													<
														int
														, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember8>::CType, t_CInType>::mc_Value
														, t_iMember8
														, TCChooseInt
														<
															int
															, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember9>::CType, t_CInType>::mc_Value
															, t_iMember9
															, TCChooseInt
															<
																int
																, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember10>::CType, t_CInType>::mc_Value
																, t_iMember10
																, TCChooseInt
																<
																	int
																	, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember11>::CType, t_CInType>::mc_Value
																	, t_iMember11
																	, TCChooseInt
																	<
																		int
																		, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember12>::CType, t_CInType>::mc_Value
																		, t_iMember12
																		, TCChooseInt
																		<
																			int
																			, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember13>::CType, t_CInType>::mc_Value
																			, t_iMember13
																			, TCChooseInt
																			<
																				int
																				, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember14>::CType, t_CInType>::mc_Value
																				, t_iMember14
																				, TCChooseInt
																				<
																					int
																					, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember15>::CType, t_CInType>::mc_Value
																					, t_iMember15
	#if DMibContainerVariantMany > 1
																					, TCChooseInt
																					<
																						int
																						, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember16>::CType, t_CInType>::mc_Value
																						, t_iMember16
																						, TCChooseInt
																						<
																							int
																							, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember17>::CType, t_CInType>::mc_Value
																							, t_iMember17
																							, TCChooseInt
																							<
																								int
																								, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember18>::CType, t_CInType>::mc_Value
																								, t_iMember18
																								, TCChooseInt
																								<
																									int
																									, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember19>::CType, t_CInType>::mc_Value
																									, t_iMember19
																									, TCChooseInt
																									<
																										int
																										, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember20>::CType, t_CInType>::mc_Value
																										, t_iMember20
																										, TCChooseInt
																										<
																											int
																											, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember21>::CType, t_CInType>::mc_Value
																											, t_iMember21
																											, TCChooseInt
																											<
																												int
																												, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember22>::CType, t_CInType>::mc_Value
																												, t_iMember22
																												, TCChooseInt
																												<
																													int
																													, NTraits::TCIsConstructorCallableWith<typename TCTypeFromMember<t_iMember23>::CType, t_CInType>::mc_Value
																													, t_iMember23
																													, -1
																												>::mc_Value
																											>::mc_Value
																										>::mc_Value
																									>::mc_Value
																								>::mc_Value
																							>::mc_Value
																						>::mc_Value
																					>::mc_Value
	#else
																					, -1
	#endif
																				>::mc_Value
																			>::mc_Value
																		>::mc_Value
																	>::mc_Value
																>::mc_Value
															>::mc_Value
														>::mc_Value
													>::mc_Value
	#else
													, -1
	#endif
												>::mc_Value
											>::mc_Value
										>::mc_Value
									>::mc_Value
								>::mc_Value
							>::mc_Value
						>::mc_Value
					>::mc_Value
				};
			};

			TCStreamableVariant &fp_GetStreamable()
			{
				return *this;
			}

			TCStreamableVariant const &fp_GetStreamable() const
			{
				return *this;
			}

			struct CVariantVisitor_Move
			{
				TCStreamableVariant &m_This;
				CVariantVisitor_Move(TCStreamableVariant &_This)
					: m_This(_This)
				{
				}

				void operator () (CVoidTag)
				{
					enum
					{
						s_ToConstruct = TCMemberFromType<void>::mc_Value
					};
					static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with void argument type");
					m_This.fp_SetNoRet<(t_CIndexType)s_ToConstruct>();
				}

				template <typename t_CParam0>
				void operator () (t_CParam0 &&_Param0)
				{
					enum
					{
						s_ToConstruct = TCEvalOneParamConstruction<typename NTraits::TCAddRValueReference<t_CParam0>::CType>::mc_Value
					};
					static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with this argument type (move constructor)");
					m_This.fp_SetNoRet<(t_CIndexType)s_ToConstruct>(fg_Move(_Param0));
				}
			};
			struct CVariantVisitor_Copy
			{
				TCStreamableVariant &m_This;
				CVariantVisitor_Copy(TCStreamableVariant &_This)
					: m_This(_This)
				{
				}

				void operator () (CVoidTag)
				{
					enum
					{
						s_ToConstruct = TCMemberFromType<void>::mc_Value
					};
					static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with void argument type");
					m_This.fp_SetNoRet<(t_CIndexType)s_ToConstruct>();
				}

				template <typename t_CParam0>
				void operator () (t_CParam0 &&_Param0)
				{
					enum
					{
						s_ToConstruct = TCEvalOneParamConstruction<t_CParam0 &&>::mc_Value
					};
					static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with this argument type (copy constructor)");
					m_This.fp_SetNoRet<(t_CIndexType)s_ToConstruct>(fg_Forward<t_CParam0>(_Param0));
				}
			};

		public:

			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Default construction / destruction																|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/


			TCStreamableVariant()
			{
#ifdef DMibDebuggerHelpers
				(void)&ms_MemberValues;
#endif
				static_assert(mcp_FirstDefaultConstructible != -1, "No suitable default constructible type exists in variant, variant cannot be default constructed.");
				fp_SetNoRet<(t_CIndexType)mcp_FirstDefaultConstructible>();
			}

			~TCStreamableVariant()
			{
				fp_DestroyCurrent();
			}

			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Copy/Move variant construction																	|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/

			template 
			<
				typename t_CIndexTypeOther
				, typename t_CType0Other, t_CIndexTypeOther t_iMember0Other
				, typename t_CType1Other, t_CIndexTypeOther t_iMember1Other
				, typename t_CType2Other, t_CIndexTypeOther t_iMember2Other
				, typename t_CType3Other, t_CIndexTypeOther t_iMember3Other
				, typename t_CType4Other, t_CIndexTypeOther t_iMember4Other
				, typename t_CType5Other, t_CIndexTypeOther t_iMember5Other
				, typename t_CType6Other, t_CIndexTypeOther t_iMember6Other
				, typename t_CType7Other, t_CIndexTypeOther t_iMember7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other, t_CIndexTypeOther t_iMember8Other
				, typename t_CType9Other, t_CIndexTypeOther t_iMember9Other
				, typename t_CType10Other, t_CIndexTypeOther t_iMember10Other
				, typename t_CType11Other, t_CIndexTypeOther t_iMember11Other
				, typename t_CType12Other, t_CIndexTypeOther t_iMember12Other
				, typename t_CType13Other, t_CIndexTypeOther t_iMember13Other
				, typename t_CType14Other, t_CIndexTypeOther t_iMember14Other
				, typename t_CType15Other, t_CIndexTypeOther t_iMember15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other, t_CIndexTypeOther t_iMember16Other
				, typename t_CType17Other, t_CIndexTypeOther t_iMember17Other
				, typename t_CType18Other, t_CIndexTypeOther t_iMember18Other
				, typename t_CType19Other, t_CIndexTypeOther t_iMember19Other
				, typename t_CType20Other, t_CIndexTypeOther t_iMember20Other
				, typename t_CType21Other, t_CIndexTypeOther t_iMember21Other
				, typename t_CType22Other, t_CIndexTypeOther t_iMember22Other
				, typename t_CType23Other, t_CIndexTypeOther t_iMember23Other
#endif
#endif
				, bint t_bStreamableOther
			>
			TCStreamableVariant
			(
				TCStreamableVariant
				<
					t_CIndexTypeOther, 
					t_CType0Other, t_iMember0Other, 
					t_CType1Other, t_iMember1Other, 
					t_CType2Other, t_iMember2Other, 
					t_CType3Other, t_iMember3Other, 
					t_CType4Other, t_iMember4Other, 
					t_CType5Other, t_iMember5Other,
					t_CType6Other, t_iMember6Other,
					t_CType7Other, t_iMember7Other,
#if DMibContainerVariantMany > 0
					t_CType8Other, t_iMember8Other,
					t_CType9Other, t_iMember9Other,
					t_CType10Other, t_iMember10Other,
					t_CType11Other, t_iMember11Other,
					t_CType12Other, t_iMember12Other,
					t_CType13Other, t_iMember13Other,
					t_CType14Other, t_iMember14Other,
					t_CType15Other, t_iMember15Other,
#if DMibContainerVariantMany > 1
					t_CType16Other, t_iMember16Other,
					t_CType17Other, t_iMember17Other,
					t_CType18Other, t_iMember18Other,
					t_CType19Other, t_iMember19Other,
					t_CType20Other, t_iMember20Other,
					t_CType21Other, t_iMember21Other,
					t_CType22Other, t_iMember22Other,
					t_CType23Other, t_iMember23Other,
#endif
#endif
					t_bStreamableOther
				> &&_Other
			)
			{
				_Other.f_Visit(CVariantVisitor_Move(*this));
			}			

			TCStreamableVariant(TCStreamableVariant &&_Other)
			{
#ifdef DMibDebuggerHelpers
				(void)&ms_MemberValues;
#endif
				_Other.f_Visit(CVariantVisitor_Move(*this));
			}

			template 
			<
				typename t_CIndexTypeOther
				, typename t_CType0Other, t_CIndexTypeOther t_iMember0Other
				, typename t_CType1Other, t_CIndexTypeOther t_iMember1Other
				, typename t_CType2Other, t_CIndexTypeOther t_iMember2Other
				, typename t_CType3Other, t_CIndexTypeOther t_iMember3Other
				, typename t_CType4Other, t_CIndexTypeOther t_iMember4Other
				, typename t_CType5Other, t_CIndexTypeOther t_iMember5Other
				, typename t_CType6Other, t_CIndexTypeOther t_iMember6Other
				, typename t_CType7Other, t_CIndexTypeOther t_iMember7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other, t_CIndexTypeOther t_iMember8Other
				, typename t_CType9Other, t_CIndexTypeOther t_iMember9Other
				, typename t_CType10Other, t_CIndexTypeOther t_iMember10Other
				, typename t_CType11Other, t_CIndexTypeOther t_iMember11Other
				, typename t_CType12Other, t_CIndexTypeOther t_iMember12Other
				, typename t_CType13Other, t_CIndexTypeOther t_iMember13Other
				, typename t_CType14Other, t_CIndexTypeOther t_iMember14Other
				, typename t_CType15Other, t_CIndexTypeOther t_iMember15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other, t_CIndexTypeOther t_iMember16Other
				, typename t_CType17Other, t_CIndexTypeOther t_iMember17Other
				, typename t_CType18Other, t_CIndexTypeOther t_iMember18Other
				, typename t_CType19Other, t_CIndexTypeOther t_iMember19Other
				, typename t_CType20Other, t_CIndexTypeOther t_iMember20Other
				, typename t_CType21Other, t_CIndexTypeOther t_iMember21Other
				, typename t_CType22Other, t_CIndexTypeOther t_iMember22Other
				, typename t_CType23Other, t_CIndexTypeOther t_iMember23Other
#endif
#endif
				, bint t_bStreamableOther
			>
			TCStreamableVariant
			(
				TCStreamableVariant
				<
					t_CIndexTypeOther, 
					t_CType0Other, t_iMember0Other, 
					t_CType1Other, t_iMember1Other, 
					t_CType2Other, t_iMember2Other, 
					t_CType3Other, t_iMember3Other, 
					t_CType4Other, t_iMember4Other, 
					t_CType5Other, t_iMember5Other,
					t_CType6Other, t_iMember6Other,
					t_CType7Other, t_iMember7Other,
#if DMibContainerVariantMany > 0
					t_CType8Other, t_iMember8Other,
					t_CType9Other, t_iMember9Other,
					t_CType10Other, t_iMember10Other,
					t_CType11Other, t_iMember11Other,
					t_CType12Other, t_iMember12Other,
					t_CType13Other, t_iMember13Other,
					t_CType14Other, t_iMember14Other,
					t_CType15Other, t_iMember15Other,
#if DMibContainerVariantMany > 1
					t_CType16Other, t_iMember16Other,
					t_CType17Other, t_iMember17Other,
					t_CType18Other, t_iMember18Other,
					t_CType19Other, t_iMember19Other,
					t_CType20Other, t_iMember20Other,
					t_CType21Other, t_iMember21Other,
					t_CType22Other, t_iMember22Other,
					t_CType23Other, t_iMember23Other,
#endif
#endif
					t_bStreamableOther
				> const &_Other
			)
			{
				_Other.f_Visit(CVariantVisitor_Copy(*this));
			}		

			TCStreamableVariant(TCStreamableVariant const &_Other)
			{
#ifdef DMibDebuggerHelpers
				(void)&ms_MemberValues;
#endif
				_Other.f_Visit(CVariantVisitor_Copy(*this));
			}

			TCStreamableVariant(TCStreamableVariant &_Other)
			{
#ifdef DMibDebuggerHelpers
				(void)&ms_MemberValues;
#endif
				_Other.f_Visit(CVariantVisitor_Copy(*this));
			}

			template 
			<
				typename t_CIndexTypeOther
				, typename t_CType0Other, t_CIndexTypeOther t_iMember0Other
				, typename t_CType1Other, t_CIndexTypeOther t_iMember1Other
				, typename t_CType2Other, t_CIndexTypeOther t_iMember2Other
				, typename t_CType3Other, t_CIndexTypeOther t_iMember3Other
				, typename t_CType4Other, t_CIndexTypeOther t_iMember4Other
				, typename t_CType5Other, t_CIndexTypeOther t_iMember5Other
				, typename t_CType6Other, t_CIndexTypeOther t_iMember6Other
				, typename t_CType7Other, t_CIndexTypeOther t_iMember7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other, t_CIndexTypeOther t_iMember8Other
				, typename t_CType9Other, t_CIndexTypeOther t_iMember9Other
				, typename t_CType10Other, t_CIndexTypeOther t_iMember10Other
				, typename t_CType11Other, t_CIndexTypeOther t_iMember11Other
				, typename t_CType12Other, t_CIndexTypeOther t_iMember12Other
				, typename t_CType13Other, t_CIndexTypeOther t_iMember13Other
				, typename t_CType14Other, t_CIndexTypeOther t_iMember14Other
				, typename t_CType15Other, t_CIndexTypeOther t_iMember15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other, t_CIndexTypeOther t_iMember16Other
				, typename t_CType17Other, t_CIndexTypeOther t_iMember17Other
				, typename t_CType18Other, t_CIndexTypeOther t_iMember18Other
				, typename t_CType19Other, t_CIndexTypeOther t_iMember19Other
				, typename t_CType20Other, t_CIndexTypeOther t_iMember20Other
				, typename t_CType21Other, t_CIndexTypeOther t_iMember21Other
				, typename t_CType22Other, t_CIndexTypeOther t_iMember22Other
				, typename t_CType23Other, t_CIndexTypeOther t_iMember23Other
#endif
#endif
				, bint t_bStreamableOther
			>
			TCStreamableVariant
			(
				TCStreamableVariant
				<
					t_CIndexTypeOther, 
					t_CType0Other, t_iMember0Other, 
					t_CType1Other, t_iMember1Other, 
					t_CType2Other, t_iMember2Other, 
					t_CType3Other, t_iMember3Other, 
					t_CType4Other, t_iMember4Other, 
					t_CType5Other, t_iMember5Other,
					t_CType6Other, t_iMember6Other,
					t_CType7Other, t_iMember7Other,
#if DMibContainerVariantMany > 0
					t_CType8Other, t_iMember8Other,
					t_CType9Other, t_iMember9Other,
					t_CType10Other, t_iMember10Other,
					t_CType11Other, t_iMember11Other,
					t_CType12Other, t_iMember12Other,
					t_CType13Other, t_iMember13Other,
					t_CType14Other, t_iMember14Other,
					t_CType15Other, t_iMember15Other,
#if DMibContainerVariantMany > 1
					t_CType16Other, t_iMember16Other,
					t_CType17Other, t_iMember17Other,
					t_CType18Other, t_iMember18Other,
					t_CType19Other, t_iMember19Other,
					t_CType20Other, t_iMember20Other,
					t_CType21Other, t_iMember21Other,
					t_CType22Other, t_iMember22Other,
					t_CType23Other, t_iMember23Other,
#endif
#endif
					t_bStreamableOther
				> &_Other
			)
			{
				_Other.f_Visit(CVariantVisitor_Copy(*this));
			}		

			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Any other construction																			|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/

			template <typename t_CParam0>
			TCStreamableVariant(t_CParam0 &&_Param0)
			{
#ifdef DMibDebuggerHelpers
				(void)&ms_MemberValues;
#endif
				enum
				{
					s_ToConstruct = TCEvalOneParamConstruction<t_CParam0 &&>::mc_Value
				};
				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with this argument type (general constructor 1)");
				fp_SetNoRet<(t_CIndexType)s_ToConstruct>(fg_Forward<t_CParam0>(_Param0));
			}


			template <typename t_CParam0, typename t_CParam1>
			TCStreamableVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1)
			{
#ifdef DMibDebuggerHelpers
				(void)&ms_MemberValues;
#endif
				enum
				{
					s_ToConstruct = TCEvalManyParamConstruction<void (t_CParam0 &&, t_CParam1 &&)>::mc_Value
				};
				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with these argument types");
				fp_SetNoRet<(t_CIndexType)s_ToConstruct>(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1));
			}			

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2>
			TCStreamableVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2)
			{
#ifdef DMibDebuggerHelpers
				(void)&ms_MemberValues;
#endif
				enum
				{
					s_ToConstruct = TCEvalManyParamConstruction<void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&)>::mc_Value
				};
				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with these argument types");
				fp_SetNoRet<(t_CIndexType)s_ToConstruct>(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2));
			}			

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3>
			TCStreamableVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3)
			{
#ifdef DMibDebuggerHelpers
				(void)&ms_MemberValues;
#endif
				enum
				{
					s_ToConstruct = TCEvalManyParamConstruction<void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&, t_CParam3 &&)>::mc_Value
				};
				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with these argument types");
				fp_SetNoRet<(t_CIndexType)s_ToConstruct>(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3));
			}			

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4>
			TCStreamableVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4)
			{
#ifdef DMibDebuggerHelpers
				(void)&ms_MemberValues;
#endif
				enum
				{
					s_ToConstruct = TCEvalManyParamConstruction<void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&, t_CParam3 &&, t_CParam4 &&)>::mc_Value
				};
				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with these argument types");
				fp_SetNoRet<(t_CIndexType)s_ToConstruct>
					(
						fg_Forward<t_CParam0>(_Param0)
						, fg_Forward<t_CParam1>(_Param1)
						, fg_Forward<t_CParam2>(_Param2)
						, fg_Forward<t_CParam3>(_Param3)
						, fg_Forward<t_CParam4>(_Param4)
					);
			}			

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5>
			TCStreamableVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4, t_CParam5 &&_Param5)
			{
#ifdef DMibDebuggerHelpers
				(void)&ms_MemberValues;
#endif
				enum
				{
					s_ToConstruct = TCEvalManyParamConstruction<void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&, t_CParam3 &&, t_CParam4 &&, t_CParam5 &&)>::mc_Value
				};
				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with these argument types");
				fp_SetNoRet<(t_CIndexType)s_ToConstruct>
					(
						fg_Forward<t_CParam0>(_Param0)
						, fg_Forward<t_CParam1>(_Param1)
						, fg_Forward<t_CParam2>(_Param2)
						, fg_Forward<t_CParam3>(_Param3)
						, fg_Forward<t_CParam4>(_Param4)
						, fg_Forward<t_CParam5>(_Param5)
					);
			}			

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5, typename t_CParam6>
			TCStreamableVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4, t_CParam5 &&_Param5, t_CParam6 &&_Param6)
			{
#ifdef DMibDebuggerHelpers
				(void)&ms_MemberValues;
#endif
				enum
				{
					s_ToConstruct = TCEvalManyParamConstruction<void (t_CParam0 &&, t_CParam1 &&, t_CParam2 &&, t_CParam3 &&, t_CParam4 &&, t_CParam5 &&, t_CParam6 &&)>::mc_Value
				};
				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with these argument types");
				fp_SetNoRet<(t_CIndexType)s_ToConstruct>
					(
						fg_Forward<t_CParam0>(_Param0)
						, fg_Forward<t_CParam1>(_Param1)
						, fg_Forward<t_CParam2>(_Param2)
						, fg_Forward<t_CParam3>(_Param3)
						, fg_Forward<t_CParam4>(_Param4)
						, fg_Forward<t_CParam5>(_Param5)
						, fg_Forward<t_CParam6>(_Param6)
					);
			}			

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5, typename t_CParam6, typename t_CParam7>
			TCStreamableVariant
			(
				t_CParam0 &&_Param0
				, t_CParam1 &&_Param1
				, t_CParam2 &&_Param2
				, t_CParam3 &&_Param3
				, t_CParam4 &&_Param4
				, t_CParam5 &&_Param5
				, t_CParam6 &&_Param6
				, t_CParam7 &&_Param7
			)
			{
				enum
				{
					s_ToConstruct = TCEvalManyParamConstruction
					<
						void 
						(
							t_CParam0 &&
							, t_CParam1 &&
							, t_CParam2 &&
							, t_CParam3 &&
							, t_CParam4 &&
							, t_CParam5 &&
							, t_CParam6 &&
							, t_CParam7 &&
						)
					>::mc_Value
				};
				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with these argument types");
				fp_SetNoRet<(t_CIndexType)s_ToConstruct>
					(
						fg_Forward<t_CParam0>(_Param0)
						, fg_Forward<t_CParam1>(_Param1)
						, fg_Forward<t_CParam2>(_Param2)
						, fg_Forward<t_CParam3>(_Param3)
						, fg_Forward<t_CParam4>(_Param4)
						, fg_Forward<t_CParam5>(_Param5)
						, fg_Forward<t_CParam6>(_Param6)
						, fg_Forward<t_CParam7>(_Param7)
					);
			}			

			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Copy/Move variant assignment																		|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/

			template 
			<
				typename t_CIndexTypeOther
				, typename t_CType0Other, t_CIndexTypeOther t_iMember0Other
				, typename t_CType1Other, t_CIndexTypeOther t_iMember1Other
				, typename t_CType2Other, t_CIndexTypeOther t_iMember2Other
				, typename t_CType3Other, t_CIndexTypeOther t_iMember3Other
				, typename t_CType4Other, t_CIndexTypeOther t_iMember4Other
				, typename t_CType5Other, t_CIndexTypeOther t_iMember5Other
				, typename t_CType6Other, t_CIndexTypeOther t_iMember6Other
				, typename t_CType7Other, t_CIndexTypeOther t_iMember7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other, t_CIndexTypeOther t_iMember8Other
				, typename t_CType9Other, t_CIndexTypeOther t_iMember9Other
				, typename t_CType10Other, t_CIndexTypeOther t_iMember10Other
				, typename t_CType11Other, t_CIndexTypeOther t_iMember11Other
				, typename t_CType12Other, t_CIndexTypeOther t_iMember12Other
				, typename t_CType13Other, t_CIndexTypeOther t_iMember13Other
				, typename t_CType14Other, t_CIndexTypeOther t_iMember14Other
				, typename t_CType15Other, t_CIndexTypeOther t_iMember15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other, t_CIndexTypeOther t_iMember16Other
				, typename t_CType17Other, t_CIndexTypeOther t_iMember17Other
				, typename t_CType18Other, t_CIndexTypeOther t_iMember18Other
				, typename t_CType19Other, t_CIndexTypeOther t_iMember19Other
				, typename t_CType20Other, t_CIndexTypeOther t_iMember20Other
				, typename t_CType21Other, t_CIndexTypeOther t_iMember21Other
				, typename t_CType22Other, t_CIndexTypeOther t_iMember22Other
				, typename t_CType23Other, t_CIndexTypeOther t_iMember23Other
#endif
#endif
				, bint t_bStreamableOther
			>
			
			TCStreamableVariant & operator =
			(
				TCStreamableVariant
				<
					t_CIndexTypeOther, 
					t_CType0Other, t_iMember0Other, 
					t_CType1Other, t_iMember1Other, 
					t_CType2Other, t_iMember2Other, 
					t_CType3Other, t_iMember3Other, 
					t_CType4Other, t_iMember4Other, 
					t_CType5Other, t_iMember5Other,
					t_CType6Other, t_iMember6Other,
					t_CType7Other, t_iMember7Other,
#if DMibContainerVariantMany > 0
					t_CType8Other, t_iMember8Other,
					t_CType9Other, t_iMember9Other,
					t_CType10Other, t_iMember10Other,
					t_CType11Other, t_iMember11Other,
					t_CType12Other, t_iMember12Other,
					t_CType13Other, t_iMember13Other,
					t_CType14Other, t_iMember14Other,
					t_CType15Other, t_iMember15Other,
#if DMibContainerVariantMany > 1
					t_CType16Other, t_iMember16Other,
					t_CType17Other, t_iMember17Other,
					t_CType18Other, t_iMember18Other,
					t_CType19Other, t_iMember19Other,
					t_CType20Other, t_iMember20Other,
					t_CType21Other, t_iMember21Other,
					t_CType22Other, t_iMember22Other,
					t_CType23Other, t_iMember23Other,
#endif
#endif
					t_bStreamableOther
				> &&_Other
			)
			{
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1 || mcp_AllHasNothrowCopyConstructor
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);
				fp_DestroyCurrent(); // Cannot throw
				try
				{
					_Other.f_Visit(CVariantVisitor_Move(*this));
					return *this;
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}		

			TCStreamableVariant & operator = (TCStreamableVariant &&_Other)
			{
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1 || mcp_AllHasNothrowCopyConstructor
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);
				fp_DestroyCurrent(); // Cannot throw
				try
				{
					_Other.f_Visit(CVariantVisitor_Move(*this));
					return *this;
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}			

			template 
			<
				typename t_CIndexTypeOther
				, typename t_CType0Other, t_CIndexTypeOther t_iMember0Other
				, typename t_CType1Other, t_CIndexTypeOther t_iMember1Other
				, typename t_CType2Other, t_CIndexTypeOther t_iMember2Other
				, typename t_CType3Other, t_CIndexTypeOther t_iMember3Other
				, typename t_CType4Other, t_CIndexTypeOther t_iMember4Other
				, typename t_CType5Other, t_CIndexTypeOther t_iMember5Other
				, typename t_CType6Other, t_CIndexTypeOther t_iMember6Other
				, typename t_CType7Other, t_CIndexTypeOther t_iMember7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other, t_CIndexTypeOther t_iMember8Other
				, typename t_CType9Other, t_CIndexTypeOther t_iMember9Other
				, typename t_CType10Other, t_CIndexTypeOther t_iMember10Other
				, typename t_CType11Other, t_CIndexTypeOther t_iMember11Other
				, typename t_CType12Other, t_CIndexTypeOther t_iMember12Other
				, typename t_CType13Other, t_CIndexTypeOther t_iMember13Other
				, typename t_CType14Other, t_CIndexTypeOther t_iMember14Other
				, typename t_CType15Other, t_CIndexTypeOther t_iMember15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other, t_CIndexTypeOther t_iMember16Other
				, typename t_CType17Other, t_CIndexTypeOther t_iMember17Other
				, typename t_CType18Other, t_CIndexTypeOther t_iMember18Other
				, typename t_CType19Other, t_CIndexTypeOther t_iMember19Other
				, typename t_CType20Other, t_CIndexTypeOther t_iMember20Other
				, typename t_CType21Other, t_CIndexTypeOther t_iMember21Other
				, typename t_CType22Other, t_CIndexTypeOther t_iMember22Other
				, typename t_CType23Other, t_CIndexTypeOther t_iMember23Other
#endif
#endif
				, bint t_bStreamableOther
			>
			TCStreamableVariant & operator =
			(
				TCStreamableVariant
				<
					t_CIndexTypeOther, 
					t_CType0Other, t_iMember0Other, 
					t_CType1Other, t_iMember1Other, 
					t_CType2Other, t_iMember2Other, 
					t_CType3Other, t_iMember3Other, 
					t_CType4Other, t_iMember4Other, 
					t_CType5Other, t_iMember5Other,
					t_CType6Other, t_iMember6Other,
					t_CType7Other, t_iMember7Other,
#if DMibContainerVariantMany > 0
					t_CType8Other, t_iMember8Other,
					t_CType9Other, t_iMember9Other,
					t_CType10Other, t_iMember10Other,
					t_CType11Other, t_iMember11Other,
					t_CType12Other, t_iMember12Other,
					t_CType13Other, t_iMember13Other,
					t_CType14Other, t_iMember14Other,
					t_CType15Other, t_iMember15Other,
#if DMibContainerVariantMany > 1
					t_CType16Other, t_iMember16Other,
					t_CType17Other, t_iMember17Other,
					t_CType18Other, t_iMember18Other,
					t_CType19Other, t_iMember19Other,
					t_CType20Other, t_iMember20Other,
					t_CType21Other, t_iMember21Other,
					t_CType22Other, t_iMember22Other,
					t_CType23Other, t_iMember23Other,
#endif
#endif
					t_bStreamableOther
				> const &_Other
			)
			{
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1 || mcp_AllHasNothrowCopyConstructor
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);
				fp_DestroyCurrent(); // Cannot throw
				try
				{
					_Other.f_Visit(CVariantVisitor_Copy(*this));
					return *this;
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}			

			TCStreamableVariant & operator =(TCStreamableVariant const &_Other)
			{
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1 || mcp_AllHasNothrowCopyConstructor
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);
				fp_DestroyCurrent(); // Cannot throw
				try
				{
					_Other.f_Visit(CVariantVisitor_Copy(*this));
					return *this;
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}			

			TCStreamableVariant & operator =(TCStreamableVariant &_Other)
			{
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1 || mcp_AllHasNothrowCopyConstructor
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);
				fp_DestroyCurrent(); // Cannot throw
				try
				{
					_Other.f_Visit(CVariantVisitor_Copy(*this));
					return *this;
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}			

			template 
			<
				typename t_CIndexTypeOther
				, typename t_CType0Other, t_CIndexTypeOther t_iMember0Other
				, typename t_CType1Other, t_CIndexTypeOther t_iMember1Other
				, typename t_CType2Other, t_CIndexTypeOther t_iMember2Other
				, typename t_CType3Other, t_CIndexTypeOther t_iMember3Other
				, typename t_CType4Other, t_CIndexTypeOther t_iMember4Other
				, typename t_CType5Other, t_CIndexTypeOther t_iMember5Other
				, typename t_CType6Other, t_CIndexTypeOther t_iMember6Other
				, typename t_CType7Other, t_CIndexTypeOther t_iMember7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other, t_CIndexTypeOther t_iMember8Other
				, typename t_CType9Other, t_CIndexTypeOther t_iMember9Other
				, typename t_CType10Other, t_CIndexTypeOther t_iMember10Other
				, typename t_CType11Other, t_CIndexTypeOther t_iMember11Other
				, typename t_CType12Other, t_CIndexTypeOther t_iMember12Other
				, typename t_CType13Other, t_CIndexTypeOther t_iMember13Other
				, typename t_CType14Other, t_CIndexTypeOther t_iMember14Other
				, typename t_CType15Other, t_CIndexTypeOther t_iMember15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other, t_CIndexTypeOther t_iMember16Other
				, typename t_CType17Other, t_CIndexTypeOther t_iMember17Other
				, typename t_CType18Other, t_CIndexTypeOther t_iMember18Other
				, typename t_CType19Other, t_CIndexTypeOther t_iMember19Other
				, typename t_CType20Other, t_CIndexTypeOther t_iMember20Other
				, typename t_CType21Other, t_CIndexTypeOther t_iMember21Other
				, typename t_CType22Other, t_CIndexTypeOther t_iMember22Other
				, typename t_CType23Other, t_CIndexTypeOther t_iMember23Other
#endif
#endif
				, bint t_bStreamableOther
			>
			TCStreamableVariant & operator =
			(
				TCStreamableVariant
				<
					t_CIndexTypeOther, 
					t_CType0Other, t_iMember0Other, 
					t_CType1Other, t_iMember1Other, 
					t_CType2Other, t_iMember2Other, 
					t_CType3Other, t_iMember3Other, 
					t_CType4Other, t_iMember4Other, 
					t_CType5Other, t_iMember5Other,
					t_CType6Other, t_iMember6Other,
					t_CType7Other, t_iMember7Other,
#if DMibContainerVariantMany > 0
					t_CType8Other, t_iMember8Other,
					t_CType9Other, t_iMember9Other,
					t_CType10Other, t_iMember10Other,
					t_CType11Other, t_iMember11Other,
					t_CType12Other, t_iMember12Other,
					t_CType13Other, t_iMember13Other,
					t_CType14Other, t_iMember14Other,
					t_CType15Other, t_iMember15Other,
#if DMibContainerVariantMany > 1
					t_CType16Other, t_iMember16Other,
					t_CType17Other, t_iMember17Other,
					t_CType18Other, t_iMember18Other,
					t_CType19Other, t_iMember19Other,
					t_CType20Other, t_iMember20Other,
					t_CType21Other, t_iMember21Other,
					t_CType22Other, t_iMember22Other,
					t_CType23Other, t_iMember23Other,
#endif
#endif
					t_bStreamableOther
				> &_Other
			)
			{
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1 || mcp_AllHasNothrowCopyConstructor
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);
				fp_DestroyCurrent(); // Cannot throw
				try
				{
					_Other.f_Visit(CVariantVisitor_Copy(*this));
					return *this;
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}	

			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Any other assignment																				|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/

			template <typename t_CParam>
			typename TCEnableIf<TCIsNoThrowConstructibleWith<t_CParam &&>::mc_Value, TCStreamableVariant &>::CType operator = (t_CParam &&_Param)
			{
				enum
				{
					s_ToConstruct = TCEvalOneParamConstruction<t_CParam &&>::mc_Value
				};
				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with this argument type (general assign operator 1)");

				fp_DestroyCurrent(); // Cannot throw
				fp_SetNoRet<(t_CIndexType)s_ToConstruct>(fg_Forward<t_CParam>(_Param)); // Cannot throw

				return *this;
			}

			template <typename t_CParam>
			typename TCEnableIf<!TCIsNoThrowConstructibleWith<t_CParam &&>::mc_Value, TCStreamableVariant &>::CType operator = (t_CParam &&_Param)
			{
				enum
				{
					s_ToConstruct = TCEvalOneParamConstruction<t_CParam &&>::mc_Value
				};
				static_assert(s_ToConstruct >= 0, "No type in the variant can be constructed with this argument type (general assign operator 2)");

				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);

				fp_DestroyCurrent(); // Cannot throw

				try
				{
					fp_SetNoRet<(t_CIndexType)s_ToConstruct>(fg_Forward<t_CParam>(_Param));
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}

				return *this;
			}
			 
			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Misc functions																					|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/

			inline_small t_CIndexType f_GetTypeID() const
			{
				return (t_CIndexType)m_Storage.m_CurrentType;
			}

			template <typename t_CType>
			inline_small bint f_IsOfType() const
			{
				return f_GetTypeID() == TCMemberFromType<t_CType>::mc_Value;
			}

			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Get already known type																			|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/

			template <t_CIndexType t_iMember>
			typename TCEvalReturnType<t_iMember>::CType f_Get()
			{
				DMibRequire(f_GetTypeID() == t_iMember);
				return fp_GetAs<t_iMember>();
			}

			template <t_CIndexType t_iMember>
			typename TCEvalReturnTypeConst<t_iMember>::CType f_Get() const
			{
				DMibRequire(f_GetTypeID() == t_iMember);
				return fp_GetAs<t_iMember>();
			}

			template <typename t_CType>
			typename TCEvalReturnType<TCMemberFromType<t_CType>::mc_Value>::CType f_GetAsType()
			{
				enum
				{
					s_ToGet = TCMemberFromType<t_CType>::mc_Value
				};
				static_assert(s_ToGet >= 0, "The variant contains no such type");
				DMibRequire(f_GetTypeID() == s_ToGet);
				return fp_GetAs<(t_CIndexType)s_ToGet>();
			}

			template <typename t_CType>
			typename TCEvalReturnTypeConst<TCMemberFromType<t_CType>::mc_Value>::CType f_GetAsType() const
			{
				enum
				{
					s_ToGet = TCMemberFromType<t_CType>::mc_Value
				};
				static_assert(s_ToGet >= 0, "The variant contains no such type");
				DMibRequire(f_GetTypeID() == s_ToGet);
				return fp_GetAs<(t_CIndexType)s_ToGet>();
			}

			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Initialize specific member with value																|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/

			template <t_CIndexType t_iMember>
			typename TCEnableIf<!NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, typename TCEvalReturnType<t_iMember>::CType>::CType f_Set()
			{
				fp_DestroyCurrent();
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1 || NTraits::TCHasNothrowDefaultConstructor<typename TCTypeFromMember<t_iMember>::CType>::mc_Value
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);
				try
				{
					return fp_Set<t_iMember>();
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}

			template <t_CIndexType t_iMember>
			typename TCEnableIf<NTraits::TCIsVoid<typename TCEvalReturnType<t_iMember>::CType>::mc_Value, typename TCEvalReturnType<t_iMember>::CType>::CType f_Set()
			{
				fp_DestroyCurrent();
				return fp_Set<t_iMember>();
			}

			template <t_CIndexType t_iMember, typename t_CParam0>
			typename TCEvalReturnType<t_iMember>::CType f_Set(t_CParam0 &&_Param0)
			{
				fp_DestroyCurrent();
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);

				try
				{
					return fp_Set<t_iMember>(fg_Forward<t_CParam0>(_Param0));
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1>
			typename TCEvalReturnType<t_iMember>::CType f_Set(t_CParam0 &&_Param0, t_CParam1 &&_Param1)
			{
				fp_DestroyCurrent();
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);

				try
				{
					return fp_Set<t_iMember>(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1));
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2>
			typename TCEvalReturnType<t_iMember>::CType f_Set(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2)
			{
				fp_DestroyCurrent();
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);

				try
				{
					return fp_Set<t_iMember>(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2));
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3>
			typename TCEvalReturnType<t_iMember>::CType f_Set(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3)
			{
				fp_DestroyCurrent();
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);

				try
				{
					return fp_Set<t_iMember>(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3));
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4>
			typename TCEvalReturnType<t_iMember>::CType f_Set(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4)
			{
				fp_DestroyCurrent();
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);

				try
				{
					return fp_Set<t_iMember>
						(
							fg_Forward<t_CParam0>(_Param0)
							, fg_Forward<t_CParam1>(_Param1)
							, fg_Forward<t_CParam2>(_Param2)
							, fg_Forward<t_CParam3>(_Param3)
							, fg_Forward<t_CParam4>(_Param4)
						);
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5>
			typename TCEvalReturnType<t_iMember>::CType f_Set(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4, t_CParam5 &&_Param5)
			{
				fp_DestroyCurrent();
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);

				try
				{
					return fp_Set<t_iMember>
						(
							fg_Forward<t_CParam0>(_Param0)
							, fg_Forward<t_CParam1>(_Param1)
							, fg_Forward<t_CParam2>(_Param2)
							, fg_Forward<t_CParam3>(_Param3)
							, fg_Forward<t_CParam4>(_Param4)
							, fg_Forward<t_CParam5>(_Param5)
						);
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}

			template <t_CIndexType t_iMember, typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5, typename t_CParam6>
			typename TCEvalReturnType<t_iMember>::CType 
			f_Set
			(
				t_CParam0 &&_Param0
				, t_CParam1 &&_Param1
				, t_CParam2 &&_Param2
				, t_CParam3 &&_Param3
				, t_CParam4 &&_Param4
				, t_CParam5 &&_Param5
				, t_CParam6 &&_Param6
			)
			{
				fp_DestroyCurrent();
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);

				try
				{
					return fp_Set<t_iMember>
						(
							fg_Forward<t_CParam0>(_Param0)
							, fg_Forward<t_CParam1>(_Param1)
							, fg_Forward<t_CParam2>(_Param2)
							, fg_Forward<t_CParam3>(_Param3)
							, fg_Forward<t_CParam4>(_Param4)
							, fg_Forward<t_CParam5>(_Param5)
							, fg_Forward<t_CParam6>(_Param6)
						);
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}

			template 
			<
				t_CIndexType t_iMember
				, typename t_CParam0
				, typename t_CParam1
				, typename t_CParam2
				, typename t_CParam3
				, typename t_CParam4
				, typename t_CParam5
				, typename t_CParam6
				, typename t_CParam7
			>
			typename TCEvalReturnType<t_iMember>::CType 
			f_Set
			(
				t_CParam0 &&_Param0
				, t_CParam1 &&_Param1
				, t_CParam2 &&_Param2
				, t_CParam3 &&_Param3
				, t_CParam4 &&_Param4
				, t_CParam5 &&_Param5
				, t_CParam6 &&_Param6
				, t_CParam6 &&_Param7
			)
			{
				fp_DestroyCurrent();
				static_assert
				(
					mcp_FirstNothrowDefaultConstructible != -1
					, "No suitable nothrow default constructible type exists in variant. Without such a type exception safety cannot be guaranteed."
				);

				try
				{
					return fp_Set<t_iMember>
						(
							fg_Forward<t_CParam0>(_Param0)
							, fg_Forward<t_CParam1>(_Param1)
							, fg_Forward<t_CParam2>(_Param2)
							, fg_Forward<t_CParam3>(_Param3)
							, fg_Forward<t_CParam4>(_Param4)
							, fg_Forward<t_CParam5>(_Param5)
							, fg_Forward<t_CParam6>(_Param6)
							, fg_Forward<t_CParam7>(_Param7)
						);
				}
				catch (...)
				{
					fp_SetNoRet<(t_CIndexType)mcp_FirstNothrowDefaultConstructible>();
					throw;
				}
			}

		};

#ifdef DMibDebuggerHelpers
		template 
		<
			typename t_CIndexType
			, typename t_CType0, t_CIndexType t_iMember0
			, typename t_CType1, t_CIndexType t_iMember1
			, typename t_CType2, t_CIndexType t_iMember2
			, typename t_CType3, t_CIndexType t_iMember3
			, typename t_CType4, t_CIndexType t_iMember4
			, typename t_CType5, t_CIndexType t_iMember5
			, typename t_CType6, t_CIndexType t_iMember6
			, typename t_CType7, t_CIndexType t_iMember7
#if DMibContainerVariantMany > 0
			, typename t_CType8, t_CIndexType t_iMember8
			, typename t_CType9, t_CIndexType t_iMember9
			, typename t_CType10, t_CIndexType t_iMember10
			, typename t_CType11, t_CIndexType t_iMember11
			, typename t_CType12, t_CIndexType t_iMember12
			, typename t_CType13, t_CIndexType t_iMember13
			, typename t_CType14, t_CIndexType t_iMember14
			, typename t_CType15, t_CIndexType t_iMember15
#if DMibContainerVariantMany > 1
			, typename t_CType16, t_CIndexType t_iMember16
			, typename t_CType17, t_CIndexType t_iMember17
			, typename t_CType18, t_CIndexType t_iMember18
			, typename t_CType19, t_CIndexType t_iMember19
			, typename t_CType20, t_CIndexType t_iMember20
			, typename t_CType21, t_CIndexType t_iMember21
			, typename t_CType22, t_CIndexType t_iMember22
			, typename t_CType23, t_CIndexType t_iMember23
#endif
#endif
			, bint t_bStreamable
		>
		assure_used typename TCStreamableVariant
			<
				t_CIndexType
				, t_CType0, t_iMember0
				, t_CType1, t_iMember1
				, t_CType2, t_iMember2
				, t_CType3, t_iMember3
				, t_CType4, t_iMember4
				, t_CType5, t_iMember5
				, t_CType6, t_iMember6
				, t_CType7, t_iMember7
	#if DMibContainerVariantMany > 0
				, t_CType8, t_iMember8
				, t_CType9, t_iMember9
				, t_CType10, t_iMember10
				, t_CType11, t_iMember11
				, t_CType12, t_iMember12
				, t_CType13, t_iMember13
				, t_CType14, t_iMember14
				, t_CType15, t_iMember15
	#if DMibContainerVariantMany > 1
				, t_CType16, t_iMember16
				, t_CType17, t_iMember17
				, t_CType18, t_iMember18
				, t_CType19, t_iMember19
				, t_CType20, t_iMember20
				, t_CType21, t_iMember21
				, t_CType22, t_iMember22
				, t_CType23, t_iMember23
	#endif
	#endif
				, t_bStreamable
			>::CMemberValues TCStreamableVariant
			<
				t_CIndexType
				, t_CType0, t_iMember0
				, t_CType1, t_iMember1
				, t_CType2, t_iMember2
				, t_CType3, t_iMember3
				, t_CType4, t_iMember4
				, t_CType5, t_iMember5
				, t_CType6, t_iMember6
				, t_CType7, t_iMember7
	#if DMibContainerVariantMany > 0
				, t_CType8, t_iMember8
				, t_CType9, t_iMember9
				, t_CType10, t_iMember10
				, t_CType11, t_iMember11
				, t_CType12, t_iMember12
				, t_CType13, t_iMember13
				, t_CType14, t_iMember14
				, t_CType15, t_iMember15
	#if DMibContainerVariantMany > 1
				, t_CType16, t_iMember16
				, t_CType17, t_iMember17
				, t_CType18, t_iMember18
				, t_CType19, t_iMember19
				, t_CType20, t_iMember20
				, t_CType21, t_iMember21
				, t_CType22, t_iMember22
				, t_CType23, t_iMember23
	#endif
	#endif
				, t_bStreamable
			>::ms_MemberValues
			=
			{
				{
					t_iMember0
					, t_iMember1
					, t_iMember2
					, t_iMember3
					, t_iMember4
					, t_iMember5
					, t_iMember6
					, t_iMember7
		#if DMibContainerVariantMany > 0
					, t_iMember8
					, t_iMember9
					, t_iMember10
					, t_iMember11
					, t_iMember12
					, t_iMember13
					, t_iMember14
					, t_iMember15
		#if DMibContainerVariantMany > 1
					, t_iMember16
					, t_iMember17
					, t_iMember18
					, t_iMember19
					, t_iMember20
					, t_iMember21
					, t_iMember22
					, t_iMember23
		#endif
		#endif
				}
			}
		;
#endif

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Variant																							|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/



		template 
		<
			typename t_CType0
			, typename t_CType1
			, typename t_CType2
			, typename t_CType3
			, typename t_CType4
			, typename t_CType5
			, typename t_CType6
			, typename t_CType7
#if DMibContainerVariantMany > 0
			, typename t_CType8
			, typename t_CType9
			, typename t_CType10
			, typename t_CType11
			, typename t_CType12
			, typename t_CType13
			, typename t_CType14
			, typename t_CType15
#if DMibContainerVariantMany > 1
			, typename t_CType16
			, typename t_CType17
			, typename t_CType18
			, typename t_CType19
			, typename t_CType20
			, typename t_CType21
			, typename t_CType22
			, typename t_CType23
#endif
#endif
		>
		class TCVariant 
			: public TCStreamableVariant
			<
				int32, 
				t_CType0, 0, 
				t_CType1, NMib::NTraits::TCIsVoid<t_CType1>::mc_Value ? -2 : 1,
				t_CType2, NMib::NTraits::TCIsVoid<t_CType2>::mc_Value ? -3 : 2,
				t_CType3, NMib::NTraits::TCIsVoid<t_CType3>::mc_Value ? -4 : 3,
				t_CType4, NMib::NTraits::TCIsVoid<t_CType4>::mc_Value ? -5 : 4,
				t_CType5, NMib::NTraits::TCIsVoid<t_CType5>::mc_Value ? -6 : 5,
				t_CType6, NMib::NTraits::TCIsVoid<t_CType6>::mc_Value ? -7 : 6,
				t_CType7, NMib::NTraits::TCIsVoid<t_CType7>::mc_Value ? -8 : 7,
#if DMibContainerVariantMany > 0
				t_CType8, NMib::NTraits::TCIsVoid<t_CType8>::mc_Value ? -9 : 8,
				t_CType9, NMib::NTraits::TCIsVoid<t_CType9>::mc_Value ? -10 : 9,
				t_CType10, NMib::NTraits::TCIsVoid<t_CType10>::mc_Value ? -11 : 10,
				t_CType11, NMib::NTraits::TCIsVoid<t_CType11>::mc_Value ? -12 : 11,
				t_CType12, NMib::NTraits::TCIsVoid<t_CType12>::mc_Value ? -13 : 12,
				t_CType13, NMib::NTraits::TCIsVoid<t_CType13>::mc_Value ? -14 : 13,
				t_CType14, NMib::NTraits::TCIsVoid<t_CType14>::mc_Value ? -15 : 14,
				t_CType15, NMib::NTraits::TCIsVoid<t_CType15>::mc_Value ? -16 : 15,
#if DMibContainerVariantMany > 1
				t_CType16, NMib::NTraits::TCIsVoid<t_CType16>::mc_Value ? -17 : 16,
				t_CType17, NMib::NTraits::TCIsVoid<t_CType17>::mc_Value ? -18 : 17,
				t_CType18, NMib::NTraits::TCIsVoid<t_CType18>::mc_Value ? -19 : 18,
				t_CType19, NMib::NTraits::TCIsVoid<t_CType19>::mc_Value ? -20 : 19,
				t_CType20, NMib::NTraits::TCIsVoid<t_CType20>::mc_Value ? -21 : 20,
				t_CType21, NMib::NTraits::TCIsVoid<t_CType21>::mc_Value ? -22 : 21,
				t_CType22, NMib::NTraits::TCIsVoid<t_CType22>::mc_Value ? -23 : 22,
				t_CType23, NMib::NTraits::TCIsVoid<t_CType23>::mc_Value ? -24 : 23,
#endif
#endif
				false
			>
		{
			typedef TCStreamableVariant
			<
				int32, 
				t_CType0, 0, 
				t_CType1, NMib::NTraits::TCIsVoid<t_CType1>::mc_Value ? -2 : 1,
				t_CType2, NMib::NTraits::TCIsVoid<t_CType2>::mc_Value ? -3 : 2,
				t_CType3, NMib::NTraits::TCIsVoid<t_CType3>::mc_Value ? -4 : 3,
				t_CType4, NMib::NTraits::TCIsVoid<t_CType4>::mc_Value ? -5 : 4,
				t_CType5, NMib::NTraits::TCIsVoid<t_CType5>::mc_Value ? -6 : 5,
				t_CType6, NMib::NTraits::TCIsVoid<t_CType6>::mc_Value ? -7 : 6,
				t_CType7, NMib::NTraits::TCIsVoid<t_CType7>::mc_Value ? -8 : 7,
#if DMibContainerVariantMany > 0
				t_CType8, NMib::NTraits::TCIsVoid<t_CType8>::mc_Value ? -9 : 8,
				t_CType9, NMib::NTraits::TCIsVoid<t_CType9>::mc_Value ? -10 : 9,
				t_CType10, NMib::NTraits::TCIsVoid<t_CType10>::mc_Value ? -11 : 10,
				t_CType11, NMib::NTraits::TCIsVoid<t_CType11>::mc_Value ? -12 : 11,
				t_CType12, NMib::NTraits::TCIsVoid<t_CType12>::mc_Value ? -13 : 12,
				t_CType13, NMib::NTraits::TCIsVoid<t_CType13>::mc_Value ? -14 : 13,
				t_CType14, NMib::NTraits::TCIsVoid<t_CType14>::mc_Value ? -15 : 14,
				t_CType15, NMib::NTraits::TCIsVoid<t_CType15>::mc_Value ? -16 : 15,
#if DMibContainerVariantMany > 1
				t_CType16, NMib::NTraits::TCIsVoid<t_CType16>::mc_Value ? -17 : 16,
				t_CType17, NMib::NTraits::TCIsVoid<t_CType17>::mc_Value ? -18 : 17,
				t_CType18, NMib::NTraits::TCIsVoid<t_CType18>::mc_Value ? -19 : 18,
				t_CType19, NMib::NTraits::TCIsVoid<t_CType19>::mc_Value ? -20 : 19,
				t_CType20, NMib::NTraits::TCIsVoid<t_CType20>::mc_Value ? -21 : 20,
				t_CType21, NMib::NTraits::TCIsVoid<t_CType21>::mc_Value ? -22 : 21,
				t_CType22, NMib::NTraits::TCIsVoid<t_CType22>::mc_Value ? -23 : 22,
				t_CType23, NMib::NTraits::TCIsVoid<t_CType23>::mc_Value ? -24 : 23,
#endif
#endif
				false
			> CParent;

		public: 
			TCVariant()
			{
			}
			~TCVariant()
			{
			}

			TCVariant(TCVariant &&_Other)
				: CParent(fg_Move(_Other.fp_GetStreamable()))
			{

			}

			TCVariant(TCVariant &_Other)
				: CParent(_Other.fp_GetStreamable())
			{

			}

			TCVariant(TCVariant const &_Other)
				: CParent(_Other.fp_GetStreamable())
			{

			}

			TCVariant & operator = (TCVariant &&_Other)
			{
				this->fp_GetStreamable() = fg_Move(_Other.fp_GetStreamable());
				return *this;
			}

			TCVariant & operator = (TCVariant const &_Other)
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
				return *this;
			}

			TCVariant & operator = (TCVariant &_Other)
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
				return *this;
			}


			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Any Construct																						|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/


			template <typename t_CParam0>
			TCVariant(t_CParam0 &&_Param0)
				: CParent(fg_Forward<t_CParam0>(_Param0))
			{

			}

			template <typename t_CParam0, typename t_CParam1>
			TCVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1))
			{

			}

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2>
			TCVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2))
			{

			}

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3>
			TCVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3))
			{

			}

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4>
			TCVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3), fg_Forward<t_CParam4>(_Param4))
			{

			}

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5>
			TCVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4, t_CParam5 &&_Param5)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3), fg_Forward<t_CParam4>(_Param4), fg_Forward<t_CParam5>(_Param5))
			{

			}

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5, typename t_CParam6>
			TCVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4, t_CParam5 &&_Param5, t_CParam6 &&_Param6)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3), fg_Forward<t_CParam4>(_Param4), fg_Forward<t_CParam5>(_Param5), fg_Forward<t_CParam6>(_Param6))
			{

			}

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5, typename t_CParam6, typename t_CParam7>
			TCVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4, t_CParam5 &&_Param5, t_CParam6 &&_Param6, t_CParam7 &&_Param7)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3), fg_Forward<t_CParam4>(_Param4), fg_Forward<t_CParam5>(_Param5), fg_Forward<t_CParam6>(_Param6), fg_Forward<t_CParam7>(_Param7))
			{

			}

			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Copy Construct																					|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/

			template 
			<
				typename t_CType0Other
				, typename t_CType1Other
				, typename t_CType2Other
				, typename t_CType3Other
				, typename t_CType4Other
				, typename t_CType5Other
				, typename t_CType6Other
				, typename t_CType7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other
				, typename t_CType9Other
				, typename t_CType10Other
				, typename t_CType11Other
				, typename t_CType12Other
				, typename t_CType13Other
				, typename t_CType14Other
				, typename t_CType15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other
				, typename t_CType17Other
				, typename t_CType18Other
				, typename t_CType19Other
				, typename t_CType20Other
				, typename t_CType21Other
				, typename t_CType22Other
				, typename t_CType23Other
#endif
#endif
			>
			TCVariant
			(
				TCVariant
				<
					t_CType0Other
					, t_CType1Other
					, t_CType2Other
					, t_CType3Other
					, t_CType4Other
					, t_CType5Other
					, t_CType6Other
					, t_CType7Other
#if DMibContainerVariantMany > 0
					, t_CType8Other
					, t_CType9Other
					, t_CType10Other
					, t_CType11Other
					, t_CType12Other
					, t_CType13Other
					, t_CType14Other
					, t_CType15Other
#if DMibContainerVariantMany > 1
					, t_CType16Other
					, t_CType17Other
					, t_CType18Other
					, t_CType19Other
					, t_CType20Other
					, t_CType21Other
					, t_CType22Other
					, t_CType23Other
#endif
#endif
				> const &_Other
			)
				: CParent(_Other.fp_GetStreamable())
			{

			}

			template 
			<
				typename t_CType0Other
				, typename t_CType1Other
				, typename t_CType2Other
				, typename t_CType3Other
				, typename t_CType4Other
				, typename t_CType5Other
				, typename t_CType6Other
				, typename t_CType7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other
				, typename t_CType9Other
				, typename t_CType10Other
				, typename t_CType11Other
				, typename t_CType12Other
				, typename t_CType13Other
				, typename t_CType14Other
				, typename t_CType15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other
				, typename t_CType17Other
				, typename t_CType18Other
				, typename t_CType19Other
				, typename t_CType20Other
				, typename t_CType21Other
				, typename t_CType22Other
				, typename t_CType23Other
#endif
#endif
			>
			TCVariant
			(
				TCVariant
				<
					t_CType0Other
					, t_CType1Other
					, t_CType2Other
					, t_CType3Other
					, t_CType4Other
					, t_CType5Other
					, t_CType6Other
					, t_CType7Other
#if DMibContainerVariantMany > 0
					, t_CType8Other
					, t_CType9Other
					, t_CType10Other
					, t_CType11Other
					, t_CType12Other
					, t_CType13Other
					, t_CType14Other
					, t_CType15Other
#if DMibContainerVariantMany > 1
					, t_CType16Other
					, t_CType17Other
					, t_CType18Other
					, t_CType19Other
					, t_CType20Other
					, t_CType21Other
					, t_CType22Other
					, t_CType23Other
#endif
#endif
				> &_Other
			)
				: CParent(_Other.fp_GetStreamable())
			{

			}


			template 
			<
				typename t_CType0Other
				, typename t_CType1Other
				, typename t_CType2Other
				, typename t_CType3Other
				, typename t_CType4Other
				, typename t_CType5Other
				, typename t_CType6Other
				, typename t_CType7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other
				, typename t_CType9Other
				, typename t_CType10Other
				, typename t_CType11Other
				, typename t_CType12Other
				, typename t_CType13Other
				, typename t_CType14Other
				, typename t_CType15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other
				, typename t_CType17Other
				, typename t_CType18Other
				, typename t_CType19Other
				, typename t_CType20Other
				, typename t_CType21Other
				, typename t_CType22Other
				, typename t_CType23Other
#endif
#endif
			>
			TCVariant
			(
				TCVariant
				<
					t_CType0Other
					, t_CType1Other
					, t_CType2Other
					, t_CType3Other
					, t_CType4Other
					, t_CType5Other
					, t_CType6Other
					, t_CType7Other
#if DMibContainerVariantMany > 0
					, t_CType8Other
					, t_CType9Other
					, t_CType10Other
					, t_CType11Other
					, t_CType12Other
					, t_CType13Other
					, t_CType14Other
					, t_CType15Other
#if DMibContainerVariantMany > 1
					, t_CType16Other
					, t_CType17Other
					, t_CType18Other
					, t_CType19Other
					, t_CType20Other
					, t_CType21Other
					, t_CType22Other
					, t_CType23Other
#endif
#endif
				> &&_Other
			)
				: CParent(fg_Move(_Other.fp_GetStreamable()))
			{

			}

			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Assignment																						|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/

			template 
			<
				typename t_CType0Other
				, typename t_CType1Other
				, typename t_CType2Other
				, typename t_CType3Other
				, typename t_CType4Other
				, typename t_CType5Other
				, typename t_CType6Other
				, typename t_CType7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other
				, typename t_CType9Other
				, typename t_CType10Other
				, typename t_CType11Other
				, typename t_CType12Other
				, typename t_CType13Other
				, typename t_CType14Other
				, typename t_CType15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other
				, typename t_CType17Other
				, typename t_CType18Other
				, typename t_CType19Other
				, typename t_CType20Other
				, typename t_CType21Other
				, typename t_CType22Other
				, typename t_CType23Other
#endif
#endif
			>
			TCVariant & operator =
			(
				TCVariant
				<
					t_CType0Other
					, t_CType1Other
					, t_CType2Other
					, t_CType3Other
					, t_CType4Other
					, t_CType5Other
					, t_CType6Other
					, t_CType7Other
#if DMibContainerVariantMany > 0
					, t_CType8Other
					, t_CType9Other
					, t_CType10Other
					, t_CType11Other
					, t_CType12Other
					, t_CType13Other
					, t_CType14Other
					, t_CType15Other
#if DMibContainerVariantMany > 1
					, t_CType16Other
					, t_CType17Other
					, t_CType18Other
					, t_CType19Other
					, t_CType20Other
					, t_CType21Other
					, t_CType22Other
					, t_CType23Other
#endif
#endif
				> const &_Other
			)
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
				return *this;
			}

			template 
			<
				typename t_CType0Other
				, typename t_CType1Other
				, typename t_CType2Other
				, typename t_CType3Other
				, typename t_CType4Other
				, typename t_CType5Other
				, typename t_CType6Other
				, typename t_CType7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other
				, typename t_CType9Other
				, typename t_CType10Other
				, typename t_CType11Other
				, typename t_CType12Other
				, typename t_CType13Other
				, typename t_CType14Other
				, typename t_CType15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other
				, typename t_CType17Other
				, typename t_CType18Other
				, typename t_CType19Other
				, typename t_CType20Other
				, typename t_CType21Other
				, typename t_CType22Other
				, typename t_CType23Other
#endif
#endif
			>
			TCVariant & operator =
			(
				TCVariant
				<
					t_CType0Other
					, t_CType1Other
					, t_CType2Other
					, t_CType3Other
					, t_CType4Other
					, t_CType5Other
					, t_CType6Other
					, t_CType7Other
#if DMibContainerVariantMany > 0
					, t_CType8Other
					, t_CType9Other
					, t_CType10Other
					, t_CType11Other
					, t_CType12Other
					, t_CType13Other
					, t_CType14Other
					, t_CType15Other
#if DMibContainerVariantMany > 1
					, t_CType16Other
					, t_CType17Other
					, t_CType18Other
					, t_CType19Other
					, t_CType20Other
					, t_CType21Other
					, t_CType22Other
					, t_CType23Other
#endif
#endif
				> &_Other
			)
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
				return *this;
			}


			template 
			<
				typename t_CType0Other
				, typename t_CType1Other
				, typename t_CType2Other
				, typename t_CType3Other
				, typename t_CType4Other
				, typename t_CType5Other
				, typename t_CType6Other
				, typename t_CType7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other
				, typename t_CType9Other
				, typename t_CType10Other
				, typename t_CType11Other
				, typename t_CType12Other
				, typename t_CType13Other
				, typename t_CType14Other
				, typename t_CType15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other
				, typename t_CType17Other
				, typename t_CType18Other
				, typename t_CType19Other
				, typename t_CType20Other
				, typename t_CType21Other
				, typename t_CType22Other
				, typename t_CType23Other
#endif
#endif
			>
			TCVariant & operator =
			(
				TCVariant
				<
					t_CType0Other
					, t_CType1Other
					, t_CType2Other
					, t_CType3Other
					, t_CType4Other
					, t_CType5Other
					, t_CType6Other
					, t_CType7Other
#if DMibContainerVariantMany > 0
					, t_CType8Other
					, t_CType9Other
					, t_CType10Other
					, t_CType11Other
					, t_CType12Other
					, t_CType13Other
					, t_CType14Other
					, t_CType15Other
#if DMibContainerVariantMany > 1
					, t_CType16Other
					, t_CType17Other
					, t_CType18Other
					, t_CType19Other
					, t_CType20Other
					, t_CType21Other
					, t_CType22Other
					, t_CType23Other
#endif
#endif
				> &&_Other
			)
			{
				this->fp_GetStreamable() = fg_Move(_Other.fp_GetStreamable());
				return *this;
			}


			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Any assignment																					|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/


			template <typename t_CParam>
			inline_small TCVariant &operator = (t_CParam &&_Param)
			{
				CParent::operator =(fg_Forward<t_CParam>(_Param));
				return *this;
			}

		};

		template 
		<
			typename t_CEnum
			, typename t_CType0
			, typename t_CType1
			, typename t_CType2
			, typename t_CType3
			, typename t_CType4
			, typename t_CType5
			, typename t_CType6
			, typename t_CType7
#if DMibContainerVariantMany > 0
			, typename t_CType8
			, typename t_CType9
			, typename t_CType10
			, typename t_CType11
			, typename t_CType12
			, typename t_CType13
			, typename t_CType14
			, typename t_CType15
#if DMibContainerVariantMany > 1
			, typename t_CType16
			, typename t_CType17
			, typename t_CType18
			, typename t_CType19
			, typename t_CType20
			, typename t_CType21
			, typename t_CType22
			, typename t_CType23
#endif
#endif
		>
		class TCStreamableFixedVariant
			: public TCStreamableVariant
			<
				t_CEnum, 
				t_CType0, t_CEnum(0), 
				t_CType1, NMib::NTraits::TCIsVoid<t_CType1>::mc_Value ? t_CEnum(-2) : t_CEnum(1),
				t_CType2, NMib::NTraits::TCIsVoid<t_CType2>::mc_Value ? t_CEnum(-3) : t_CEnum(2),
				t_CType3, NMib::NTraits::TCIsVoid<t_CType3>::mc_Value ? t_CEnum(-4) : t_CEnum(3),
				t_CType4, NMib::NTraits::TCIsVoid<t_CType4>::mc_Value ? t_CEnum(-5) : t_CEnum(4),
				t_CType5, NMib::NTraits::TCIsVoid<t_CType5>::mc_Value ? t_CEnum(-6) : t_CEnum(5),
				t_CType6, NMib::NTraits::TCIsVoid<t_CType6>::mc_Value ? t_CEnum(-7) : t_CEnum(6),
				t_CType7, NMib::NTraits::TCIsVoid<t_CType7>::mc_Value ? t_CEnum(-8) : t_CEnum(7),
#if DMibContainerVariantMany > 0
				t_CType8, NMib::NTraits::TCIsVoid<t_CType8>::mc_Value ? t_CEnum(-9) : t_CEnum(8),
				t_CType9, NMib::NTraits::TCIsVoid<t_CType9>::mc_Value ? t_CEnum(-10) : t_CEnum(9),
				t_CType10, NMib::NTraits::TCIsVoid<t_CType10>::mc_Value ? t_CEnum(-11) : t_CEnum(10),
				t_CType11, NMib::NTraits::TCIsVoid<t_CType11>::mc_Value ? t_CEnum(-12) : t_CEnum(11),
				t_CType12, NMib::NTraits::TCIsVoid<t_CType12>::mc_Value ? t_CEnum(-13) : t_CEnum(12),
				t_CType13, NMib::NTraits::TCIsVoid<t_CType13>::mc_Value ? t_CEnum(-14) : t_CEnum(13),
				t_CType14, NMib::NTraits::TCIsVoid<t_CType14>::mc_Value ? t_CEnum(-15) : t_CEnum(14),
				t_CType15, NMib::NTraits::TCIsVoid<t_CType15>::mc_Value ? t_CEnum(-16) : t_CEnum(15),
#if DMibContainerVariantMany > 1
				t_CType16, NMib::NTraits::TCIsVoid<t_CType16>::mc_Value ? t_CEnum(-17) : t_CEnum(16),
				t_CType17, NMib::NTraits::TCIsVoid<t_CType17>::mc_Value ? t_CEnum(-18) : t_CEnum(17),
				t_CType18, NMib::NTraits::TCIsVoid<t_CType18>::mc_Value ? t_CEnum(-19) : t_CEnum(18),
				t_CType19, NMib::NTraits::TCIsVoid<t_CType19>::mc_Value ? t_CEnum(-20) : t_CEnum(19),
				t_CType20, NMib::NTraits::TCIsVoid<t_CType20>::mc_Value ? t_CEnum(-21) : t_CEnum(20),
				t_CType21, NMib::NTraits::TCIsVoid<t_CType21>::mc_Value ? t_CEnum(-22) : t_CEnum(21),
				t_CType22, NMib::NTraits::TCIsVoid<t_CType22>::mc_Value ? t_CEnum(-23) : t_CEnum(22),
				t_CType23, NMib::NTraits::TCIsVoid<t_CType23>::mc_Value ? t_CEnum(-24) : t_CEnum(23),
#endif
#endif
				true
			>
		{
			typedef TCStreamableVariant
			<
				t_CEnum, 
				t_CType0, t_CEnum(0), 
				t_CType1, NMib::NTraits::TCIsVoid<t_CType1>::mc_Value ? t_CEnum(-2) : t_CEnum(1),
				t_CType2, NMib::NTraits::TCIsVoid<t_CType2>::mc_Value ? t_CEnum(-3) : t_CEnum(2),
				t_CType3, NMib::NTraits::TCIsVoid<t_CType3>::mc_Value ? t_CEnum(-4) : t_CEnum(3),
				t_CType4, NMib::NTraits::TCIsVoid<t_CType4>::mc_Value ? t_CEnum(-5) : t_CEnum(4),
				t_CType5, NMib::NTraits::TCIsVoid<t_CType5>::mc_Value ? t_CEnum(-6) : t_CEnum(5),
				t_CType6, NMib::NTraits::TCIsVoid<t_CType6>::mc_Value ? t_CEnum(-7) : t_CEnum(6),
				t_CType7, NMib::NTraits::TCIsVoid<t_CType7>::mc_Value ? t_CEnum(-8) : t_CEnum(7),
#if DMibContainerVariantMany > 0
				t_CType8, NMib::NTraits::TCIsVoid<t_CType8>::mc_Value ? t_CEnum(-9) : t_CEnum(8),
				t_CType9, NMib::NTraits::TCIsVoid<t_CType9>::mc_Value ? t_CEnum(-10) : t_CEnum(9),
				t_CType10, NMib::NTraits::TCIsVoid<t_CType10>::mc_Value ? t_CEnum(-11) : t_CEnum(10),
				t_CType11, NMib::NTraits::TCIsVoid<t_CType11>::mc_Value ? t_CEnum(-12) : t_CEnum(11),
				t_CType12, NMib::NTraits::TCIsVoid<t_CType12>::mc_Value ? t_CEnum(-13) : t_CEnum(12),
				t_CType13, NMib::NTraits::TCIsVoid<t_CType13>::mc_Value ? t_CEnum(-14) : t_CEnum(13),
				t_CType14, NMib::NTraits::TCIsVoid<t_CType14>::mc_Value ? t_CEnum(-15) : t_CEnum(14),
				t_CType15, NMib::NTraits::TCIsVoid<t_CType15>::mc_Value ? t_CEnum(-16) : t_CEnum(15),
#if DMibContainerVariantMany > 1
				t_CType16, NMib::NTraits::TCIsVoid<t_CType16>::mc_Value ? t_CEnum(-17) : t_CEnum(16),
				t_CType17, NMib::NTraits::TCIsVoid<t_CType17>::mc_Value ? t_CEnum(-18) : t_CEnum(17),
				t_CType18, NMib::NTraits::TCIsVoid<t_CType18>::mc_Value ? t_CEnum(-19) : t_CEnum(18),
				t_CType19, NMib::NTraits::TCIsVoid<t_CType19>::mc_Value ? t_CEnum(-20) : t_CEnum(19),
				t_CType20, NMib::NTraits::TCIsVoid<t_CType20>::mc_Value ? t_CEnum(-21) : t_CEnum(20),
				t_CType21, NMib::NTraits::TCIsVoid<t_CType21>::mc_Value ? t_CEnum(-22) : t_CEnum(21),
				t_CType22, NMib::NTraits::TCIsVoid<t_CType22>::mc_Value ? t_CEnum(-23) : t_CEnum(22),
				t_CType23, NMib::NTraits::TCIsVoid<t_CType23>::mc_Value ? t_CEnum(-24) : t_CEnum(23),
#endif
#endif
				true
			> CParent;

		public: 
			TCStreamableFixedVariant()
			{
			}
			~TCStreamableFixedVariant()
			{
			}

			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Copy construct																					|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/

			template 
			<
				typename t_CEnumOther
				, typename t_CType0Other
				, typename t_CType1Other
				, typename t_CType2Other
				, typename t_CType3Other
				, typename t_CType4Other
				, typename t_CType5Other
				, typename t_CType6Other
				, typename t_CType7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other
				, typename t_CType9Other
				, typename t_CType10Other
				, typename t_CType11Other
				, typename t_CType12Other
				, typename t_CType13Other
				, typename t_CType14Other
				, typename t_CType15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other
				, typename t_CType17Other
				, typename t_CType18Other
				, typename t_CType19Other
				, typename t_CType20Other
				, typename t_CType21Other
				, typename t_CType22Other
				, typename t_CType23Other
#endif
#endif
			>
			TCStreamableFixedVariant
			(
				TCStreamableFixedVariant
				<
					t_CEnumOther
					, t_CType0Other
					, t_CType1Other
					, t_CType2Other
					, t_CType3Other
					, t_CType4Other
					, t_CType5Other
					, t_CType6Other
					, t_CType7Other
#if DMibContainerVariantMany > 0
					, t_CType8Other
					, t_CType9Other
					, t_CType10Other
					, t_CType11Other
					, t_CType12Other
					, t_CType13Other
					, t_CType14Other
					, t_CType15Other
#if DMibContainerVariantMany > 1
					, t_CType16Other
					, t_CType17Other
					, t_CType18Other
					, t_CType19Other
					, t_CType20Other
					, t_CType21Other
					, t_CType22Other
					, t_CType23Other
#endif
#endif
				> const &_Other
			)
				: CParent(_Other.fp_GetStreamable())
			{

			}

			template 
			<
				typename t_CEnumOther
				, typename t_CType0Other
				, typename t_CType1Other
				, typename t_CType2Other
				, typename t_CType3Other
				, typename t_CType4Other
				, typename t_CType5Other
				, typename t_CType6Other
				, typename t_CType7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other
				, typename t_CType9Other
				, typename t_CType10Other
				, typename t_CType11Other
				, typename t_CType12Other
				, typename t_CType13Other
				, typename t_CType14Other
				, typename t_CType15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other
				, typename t_CType17Other
				, typename t_CType18Other
				, typename t_CType19Other
				, typename t_CType20Other
				, typename t_CType21Other
				, typename t_CType22Other
				, typename t_CType23Other
#endif
#endif
			>
			TCStreamableFixedVariant
			(
				TCStreamableFixedVariant
				<
					t_CEnumOther
					, t_CType0Other
					, t_CType1Other
					, t_CType2Other
					, t_CType3Other
					, t_CType4Other
					, t_CType5Other
					, t_CType6Other
					, t_CType7Other
#if DMibContainerVariantMany > 0
					, t_CType8Other
					, t_CType9Other
					, t_CType10Other
					, t_CType11Other
					, t_CType12Other
					, t_CType13Other
					, t_CType14Other
					, t_CType15Other
#if DMibContainerVariantMany > 1
					, t_CType16Other
					, t_CType17Other
					, t_CType18Other
					, t_CType19Other
					, t_CType20Other
					, t_CType21Other
					, t_CType22Other
					, t_CType23Other
#endif
#endif
				> &_Other
			)
				: CParent(_Other.fp_GetStreamable())
			{

			}

			template 
			<
				typename t_CEnumOther
				, typename t_CType0Other
				, typename t_CType1Other
				, typename t_CType2Other
				, typename t_CType3Other
				, typename t_CType4Other
				, typename t_CType5Other
				, typename t_CType6Other
				, typename t_CType7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other
				, typename t_CType9Other
				, typename t_CType10Other
				, typename t_CType11Other
				, typename t_CType12Other
				, typename t_CType13Other
				, typename t_CType14Other
				, typename t_CType15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other
				, typename t_CType17Other
				, typename t_CType18Other
				, typename t_CType19Other
				, typename t_CType20Other
				, typename t_CType21Other
				, typename t_CType22Other
				, typename t_CType23Other
#endif
#endif
			>
			TCStreamableFixedVariant
			(
				TCStreamableFixedVariant
				<
					t_CEnumOther
					, t_CType0Other
					, t_CType1Other
					, t_CType2Other
					, t_CType3Other
					, t_CType4Other
					, t_CType5Other
					, t_CType6Other
					, t_CType7Other
#if DMibContainerVariantMany > 0
					, t_CType8Other
					, t_CType9Other
					, t_CType10Other
					, t_CType11Other
					, t_CType12Other
					, t_CType13Other
					, t_CType14Other
					, t_CType15Other
#if DMibContainerVariantMany > 1
					, t_CType16Other
					, t_CType17Other
					, t_CType18Other
					, t_CType19Other
					, t_CType20Other
					, t_CType21Other
					, t_CType22Other
					, t_CType23Other
#endif
#endif
				> &&_Other
			)
				: CParent(fg_Move(_Other.fp_GetStreamable()))
			{

			}

			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Assignment																						|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/

			template 
			<
				typename t_CEnumOther
				, typename t_CType0Other
				, typename t_CType1Other
				, typename t_CType2Other
				, typename t_CType3Other
				, typename t_CType4Other
				, typename t_CType5Other
				, typename t_CType6Other
				, typename t_CType7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other
				, typename t_CType9Other
				, typename t_CType10Other
				, typename t_CType11Other
				, typename t_CType12Other
				, typename t_CType13Other
				, typename t_CType14Other
				, typename t_CType15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other
				, typename t_CType17Other
				, typename t_CType18Other
				, typename t_CType19Other
				, typename t_CType20Other
				, typename t_CType21Other
				, typename t_CType22Other
				, typename t_CType23Other
#endif
#endif
			>
			TCStreamableFixedVariant & operator =
			(
				TCStreamableFixedVariant
				<
					t_CEnumOther
					, t_CType0Other
					, t_CType1Other
					, t_CType2Other
					, t_CType3Other
					, t_CType4Other
					, t_CType5Other
					, t_CType6Other
					, t_CType7Other
#if DMibContainerVariantMany > 0
					, t_CType8Other
					, t_CType9Other
					, t_CType10Other
					, t_CType11Other
					, t_CType12Other
					, t_CType13Other
					, t_CType14Other
					, t_CType15Other
#if DMibContainerVariantMany > 1
					, t_CType16Other
					, t_CType17Other
					, t_CType18Other
					, t_CType19Other
					, t_CType20Other
					, t_CType21Other
					, t_CType22Other
					, t_CType23Other
#endif
#endif
				> const &_Other
			)
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
				return *this;
			}

			template 
			<
				typename t_CEnumOther
				, typename t_CType0Other
				, typename t_CType1Other
				, typename t_CType2Other
				, typename t_CType3Other
				, typename t_CType4Other
				, typename t_CType5Other
				, typename t_CType6Other
				, typename t_CType7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other
				, typename t_CType9Other
				, typename t_CType10Other
				, typename t_CType11Other
				, typename t_CType12Other
				, typename t_CType13Other
				, typename t_CType14Other
				, typename t_CType15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other
				, typename t_CType17Other
				, typename t_CType18Other
				, typename t_CType19Other
				, typename t_CType20Other
				, typename t_CType21Other
				, typename t_CType22Other
				, typename t_CType23Other
#endif
#endif
			>
			TCStreamableFixedVariant & operator =
			(
				TCStreamableFixedVariant
				<
					t_CEnumOther
					, t_CType0Other
					, t_CType1Other
					, t_CType2Other
					, t_CType3Other
					, t_CType4Other
					, t_CType5Other
					, t_CType6Other
					, t_CType7Other
#if DMibContainerVariantMany > 0
					, t_CType8Other
					, t_CType9Other
					, t_CType10Other
					, t_CType11Other
					, t_CType12Other
					, t_CType13Other
					, t_CType14Other
					, t_CType15Other
#if DMibContainerVariantMany > 1
					, t_CType16Other
					, t_CType17Other
					, t_CType18Other
					, t_CType19Other
					, t_CType20Other
					, t_CType21Other
					, t_CType22Other
					, t_CType23Other
#endif
#endif
				> &_Other
			)
			{
				this->fp_GetStreamable() = _Other.fp_GetStreamable();
				return *this;
			}

			template 
			<
				typename t_CEnumOther
				, typename t_CType0Other
				, typename t_CType1Other
				, typename t_CType2Other
				, typename t_CType3Other
				, typename t_CType4Other
				, typename t_CType5Other
				, typename t_CType6Other
				, typename t_CType7Other
#if DMibContainerVariantMany > 0
				, typename t_CType8Other
				, typename t_CType9Other
				, typename t_CType10Other
				, typename t_CType11Other
				, typename t_CType12Other
				, typename t_CType13Other
				, typename t_CType14Other
				, typename t_CType15Other
#if DMibContainerVariantMany > 1
				, typename t_CType16Other
				, typename t_CType17Other
				, typename t_CType18Other
				, typename t_CType19Other
				, typename t_CType20Other
				, typename t_CType21Other
				, typename t_CType22Other
				, typename t_CType23Other
#endif
#endif
			>
			TCStreamableFixedVariant & operator =
			(
				TCStreamableFixedVariant
				<
					t_CEnumOther
					, t_CType0Other
					, t_CType1Other
					, t_CType2Other
					, t_CType3Other
					, t_CType4Other
					, t_CType5Other
					, t_CType6Other
					, t_CType7Other
#if DMibContainerVariantMany > 0
					, t_CType8Other
					, t_CType9Other
					, t_CType10Other
					, t_CType11Other
					, t_CType12Other
					, t_CType13Other
					, t_CType14Other
					, t_CType15Other
#if DMibContainerVariantMany > 1
					, t_CType16Other
					, t_CType17Other
					, t_CType18Other
					, t_CType19Other
					, t_CType20Other
					, t_CType21Other
					, t_CType22Other
					, t_CType23Other
#endif
#endif
				> &&_Other
			)
			{
				this->fp_GetStreamable() = fg_Move(_Other.fp_GetStreamable());
				return *this;
			}

			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Any Construct																						|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/



			template <typename t_CParam0>
			TCStreamableFixedVariant(t_CParam0 &&_Param0)
				: CParent(fg_Forward<t_CParam0>(_Param0))
			{

			}

			template <typename t_CParam0, typename t_CParam1>
			TCStreamableFixedVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1))
			{

			}

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2>
			TCStreamableFixedVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2))
			{

			}

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3>
			TCStreamableFixedVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3))
			{

			}

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4>
			TCStreamableFixedVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3), fg_Forward<t_CParam4>(_Param4))
			{

			}

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5>
			TCStreamableFixedVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4, t_CParam5 &&_Param5)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3), fg_Forward<t_CParam4>(_Param4), fg_Forward<t_CParam5>(_Param5))
			{

			}

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5, typename t_CParam6>
			TCStreamableFixedVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4, t_CParam5 &&_Param5, t_CParam6 &&_Param6)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3), fg_Forward<t_CParam4>(_Param4), fg_Forward<t_CParam5>(_Param5), fg_Forward<t_CParam6>(_Param6))
			{

			}

			template <typename t_CParam0, typename t_CParam1, typename t_CParam2, typename t_CParam3, typename t_CParam4, typename t_CParam5, typename t_CParam6, typename t_CParam7>
			TCStreamableFixedVariant(t_CParam0 &&_Param0, t_CParam1 &&_Param1, t_CParam2 &&_Param2, t_CParam3 &&_Param3, t_CParam4 &&_Param4, t_CParam5 &&_Param5, t_CParam6 &&_Param6, t_CParam7 &&_Param7)
				: CParent(fg_Forward<t_CParam0>(_Param0), fg_Forward<t_CParam1>(_Param1), fg_Forward<t_CParam2>(_Param2), fg_Forward<t_CParam3>(_Param3), fg_Forward<t_CParam4>(_Param4), fg_Forward<t_CParam5>(_Param5), fg_Forward<t_CParam6>(_Param6), fg_Forward<t_CParam7>(_Param7))
			{

			}

			/***************************************************************************************************\
			|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
			| Any Assignment																					|
			|___________________________________________________________________________________________________|
			\***************************************************************************************************/


			template <typename t_CParam>
			inline_small TCStreamableFixedVariant &operator = (t_CParam &&_Param)
			{
				CParent::operator =(fg_Forward<t_CParam>(_Param));
				return *this;
			}
		};

		template <typename t_CType, typename t_CIndexType, t_CIndexType t_Name>
		struct TCVariantMember
		{
			using CType = t_CType; 
			static constexpr t_CIndexType mc_Name = t_Name;
		};
		
#define DMibVariantMember(d_Type, d_Name) d_Type, d_Type##_##d_Name 
		
		namespace NPrivate
		{
			template <typename t_CMember> 
			struct TCGetMember_Type
			{
				using CType = void;
			};

			template <typename t_CType, typename t_CIndexType, t_CIndexType t_Name>
			struct TCGetMember_Type<TCVariantMember<t_CType, t_CIndexType, t_Name>>
			{
				using CType = typename TCVariantMember<t_CType, t_CIndexType, t_Name>::CType;
			};
			
			template <aint t_iMember, typename t_CMember> 
			struct TCGetMember_Name
			{
				static constexpr aint mc_Name = -t_iMember;
			};
			
			template <aint t_iMember, typename t_CType, typename t_CIndexType, t_CIndexType t_Name>
			struct TCGetMember_Name<t_iMember, TCVariantMember<t_CType, t_CIndexType, t_Name>>
			{
				static constexpr auto mc_Name = TCVariantMember<t_CType, t_CIndexType, t_Name>::mc_Name;
			};
			
			template <aint t_iMember, typename ...tp_CMembers> 
			struct TCGetMember
			{
				using CVariantMember = typename NMeta::TCTypeList_GetOrVoid<t_iMember, NMeta::TCTypeList<tp_CMembers...>>::CType;
				
				using CType = typename TCGetMember_Type<CVariantMember>::CType;
				static auto constexpr mc_Name = TCGetMember_Name<t_iMember, CVariantMember>::mc_Name; 
			};
		}
		
		template <typename t_CIndexType, typename ...tp_CMembers>
		using TCVariantMembers = TCStreamableVariant
			<
				t_CIndexType
				, typename NPrivate::TCGetMember<0, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<0, tp_CMembers...>::mc_Name
				, typename NPrivate::TCGetMember<1, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<1, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<2, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<2, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<3, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<3, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<4, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<4, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<5, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<5, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<6, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<6, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<7, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<7, tp_CMembers...>::mc_Name 
#if DMibContainerVariantMany > 0
				, typename NPrivate::TCGetMember<8, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<8, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<9, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<9, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<10, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<10, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<11, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<11, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<12, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<12, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<13, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<13, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<14, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<14, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<15, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<15, tp_CMembers...>::mc_Name 
#if DMibContainerVariantMany > 1
				, typename NPrivate::TCGetMember<16, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<16, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<17, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<17, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<18, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<18, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<19, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<19, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<20, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<20, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<21, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<21, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<22, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<22, tp_CMembers...>::mc_Name 
				, typename NPrivate::TCGetMember<23, tp_CMembers...>::CType, (t_CIndexType)NPrivate::TCGetMember<23, tp_CMembers...>::mc_Name
#endif
#endif
			>
		;
	}

	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| Streaming																							|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/


	namespace NStream
	{
		namespace NPrivate
		{
			template <typename t_CStream>
			struct TCVariantVisitor_Feed
			{
				t_CStream &m_Stream;
				TCVariantVisitor_Feed(t_CStream &_Stream)
					: m_Stream(_Stream)
				{
				}
				void operator () (CVoidTag)
				{
				}

				template <typename t_CType>
				void operator () (t_CType &&_Data)
				{
					m_Stream << fg_Forward<t_CType>(_Data);
				}
			};

			template <typename t_CStream>
			struct TCVariantVisitor_FeedMove
			{
				t_CStream &m_Stream;
				TCVariantVisitor_FeedMove(t_CStream &_Stream)
					: m_Stream(_Stream)
				{
				}
				void operator () (CVoidTag)
				{
				}

				template <typename t_CType>
				void operator () (t_CType &&_Data)
				{
					m_Stream << fg_Move(_Data);
				}
			};

			template <typename t_CStream>
			struct TCVariantVisitor_Consume
			{
				t_CStream &m_Stream;
				TCVariantVisitor_Consume(t_CStream &_Stream)
					: m_Stream(_Stream)
				{
				}
				void operator () (CVoidTag)
				{
				}

				template <typename t_CType>
				void operator () (t_CType &&_Data)
				{
					m_Stream >> fg_Forward<t_CType>(_Data);
				}
			};
		}
		template 
		<
			typename t_CStream
			, typename t_CIndexTypeOther
			, typename t_CType0Other, t_CIndexTypeOther t_iMember0Other
			, typename t_CType1Other, t_CIndexTypeOther t_iMember1Other
			, typename t_CType2Other, t_CIndexTypeOther t_iMember2Other
			, typename t_CType3Other, t_CIndexTypeOther t_iMember3Other
			, typename t_CType4Other, t_CIndexTypeOther t_iMember4Other
			, typename t_CType5Other, t_CIndexTypeOther t_iMember5Other
			, typename t_CType6Other, t_CIndexTypeOther t_iMember6Other
			, typename t_CType7Other, t_CIndexTypeOther t_iMember7Other
#if DMibContainerVariantMany > 0
			, typename t_CType8Other, t_CIndexTypeOther t_iMember8Other
			, typename t_CType9Other, t_CIndexTypeOther t_iMember9Other
			, typename t_CType10Other, t_CIndexTypeOther t_iMember10Other
			, typename t_CType11Other, t_CIndexTypeOther t_iMember11Other
			, typename t_CType12Other, t_CIndexTypeOther t_iMember12Other
			, typename t_CType13Other, t_CIndexTypeOther t_iMember13Other
			, typename t_CType14Other, t_CIndexTypeOther t_iMember14Other
			, typename t_CType15Other, t_CIndexTypeOther t_iMember15Other
#if DMibContainerVariantMany > 1
			, typename t_CType16Other, t_CIndexTypeOther t_iMember16Other
			, typename t_CType17Other, t_CIndexTypeOther t_iMember17Other
			, typename t_CType18Other, t_CIndexTypeOther t_iMember18Other
			, typename t_CType19Other, t_CIndexTypeOther t_iMember19Other
			, typename t_CType20Other, t_CIndexTypeOther t_iMember20Other
			, typename t_CType21Other, t_CIndexTypeOther t_iMember21Other
			, typename t_CType22Other, t_CIndexTypeOther t_iMember22Other
			, typename t_CType23Other, t_CIndexTypeOther t_iMember23Other
#endif
#endif
			, bint t_bStreamableOther
		>		
		class TCBinaryStreamTypeReference
		<
			t_CStream
			, NContainer::TCStreamableVariant
			<
				t_CIndexTypeOther, 
				t_CType0Other, t_iMember0Other, 
				t_CType1Other, t_iMember1Other, 
				t_CType2Other, t_iMember2Other, 
				t_CType3Other, t_iMember3Other, 
				t_CType4Other, t_iMember4Other, 
				t_CType5Other, t_iMember5Other,
				t_CType6Other, t_iMember6Other,
				t_CType7Other, t_iMember7Other,
#if DMibContainerVariantMany > 0
				t_CType8Other, t_iMember8Other,
				t_CType9Other, t_iMember9Other,
				t_CType10Other, t_iMember10Other,
				t_CType11Other, t_iMember11Other,
				t_CType12Other, t_iMember12Other,
				t_CType13Other, t_iMember13Other,
				t_CType14Other, t_iMember14Other,
				t_CType15Other, t_iMember15Other,
#if DMibContainerVariantMany > 1
				t_CType16Other, t_iMember16Other,
				t_CType17Other, t_iMember17Other,
				t_CType18Other, t_iMember18Other,
				t_CType19Other, t_iMember19Other,
				t_CType20Other, t_iMember20Other,
				t_CType21Other, t_iMember21Other,
				t_CType22Other, t_iMember22Other,
				t_CType23Other, t_iMember23Other,
#endif
#endif
				t_bStreamableOther
			>
		>
		{
			static_assert(t_bStreamableOther, "This variant is not streamable, use TCStreamableVariant or TCStreamableVariantFixed to make variant streamable");
			typedef NContainer::TCStreamableVariant
			<
				t_CIndexTypeOther, 
				t_CType0Other, t_iMember0Other, 
				t_CType1Other, t_iMember1Other, 
				t_CType2Other, t_iMember2Other, 
				t_CType3Other, t_iMember3Other, 
				t_CType4Other, t_iMember4Other, 
				t_CType5Other, t_iMember5Other,
				t_CType6Other, t_iMember6Other,
				t_CType7Other, t_iMember7Other,
#if DMibContainerVariantMany > 0
				t_CType8Other, t_iMember8Other,
				t_CType9Other, t_iMember9Other,
				t_CType10Other, t_iMember10Other,
				t_CType11Other, t_iMember11Other,
				t_CType12Other, t_iMember12Other,
				t_CType13Other, t_iMember13Other,
				t_CType14Other, t_iMember14Other,
				t_CType15Other, t_iMember15Other,
#if DMibContainerVariantMany > 1
				t_CType16Other, t_iMember16Other,
				t_CType17Other, t_iMember17Other,
				t_CType18Other, t_iMember18Other,
				t_CType19Other, t_iMember19Other,
				t_CType20Other, t_iMember20Other,
				t_CType21Other, t_iMember21Other,
				t_CType22Other, t_iMember22Other,
				t_CType23Other, t_iMember23Other,
#endif
#endif
				t_bStreamableOther
			> CStreamableVariant;

		public:
			static void fs_Feed(t_CStream &_Stream, CStreamableVariant const &_Data)
			{
				_Stream << _Data.f_GetTypeID();
				_Data.f_Visit(NPrivate::TCVariantVisitor_Feed<t_CStream>(_Stream));
			}
	
			static void fs_Feed(t_CStream &_Stream, CStreamableVariant &&_Data)
			{
				_Stream << _Data.f_GetTypeID();
				_Data.f_Visit(NPrivate::TCVariantVisitor_FeedMove<t_CStream>(_Stream));
			}
	
			static void fs_Consume(t_CStream &_Stream, CStreamableVariant &_Data)
			{
				typename CStreamableVariant::CIndexType TypeID;
				_Stream >> TypeID;
				_Data.f_VisitCreate(TypeID, NPrivate::TCVariantVisitor_Consume<t_CStream>(_Stream));
			}
		};

		template 
		<
			typename t_CStream
			, typename t_CEnumOther
			, typename t_CType0Other
			, typename t_CType1Other
			, typename t_CType2Other
			, typename t_CType3Other
			, typename t_CType4Other
			, typename t_CType5Other
			, typename t_CType6Other
			, typename t_CType7Other
#if DMibContainerVariantMany > 0
			, typename t_CType8Other
			, typename t_CType9Other
			, typename t_CType10Other
			, typename t_CType11Other
			, typename t_CType12Other
			, typename t_CType13Other
			, typename t_CType14Other
			, typename t_CType15Other
#if DMibContainerVariantMany > 1
			, typename t_CType16Other
			, typename t_CType17Other
			, typename t_CType18Other
			, typename t_CType19Other
			, typename t_CType20Other
			, typename t_CType21Other
			, typename t_CType22Other
			, typename t_CType23Other
#endif
#endif
		>		
		class TCBinaryStreamTypeReference
		<
			t_CStream
			, NContainer::TCStreamableFixedVariant
			<
				t_CEnumOther
				, t_CType0Other
				, t_CType1Other
				, t_CType2Other
				, t_CType3Other
				, t_CType4Other
				, t_CType5Other
				, t_CType6Other
				, t_CType7Other
#if DMibContainerVariantMany > 0
				, t_CType8Other
				, t_CType9Other
				, t_CType10Other
				, t_CType11Other
				, t_CType12Other
				, t_CType13Other
				, t_CType14Other
				, t_CType15Other
#if DMibContainerVariantMany > 1
				, t_CType16Other
				, t_CType17Other
				, t_CType18Other
				, t_CType19Other
				, t_CType20Other
				, t_CType21Other
				, t_CType22Other
				, t_CType23Other
#endif
#endif
			>
		>
		{
			typedef NContainer::TCStreamableFixedVariant
			<
				t_CEnumOther
				, t_CType0Other
				, t_CType1Other
				, t_CType2Other
				, t_CType3Other
				, t_CType4Other
				, t_CType5Other
				, t_CType6Other
				, t_CType7Other
#if DMibContainerVariantMany > 0
				, t_CType8Other
				, t_CType9Other
				, t_CType10Other
				, t_CType11Other
				, t_CType12Other
				, t_CType13Other
				, t_CType14Other
				, t_CType15Other
#if DMibContainerVariantMany > 1
				, t_CType16Other
				, t_CType17Other
				, t_CType18Other
				, t_CType19Other
				, t_CType20Other
				, t_CType21Other
				, t_CType22Other
				, t_CType23Other
#endif
#endif
			> CStreamableVariant;

		public:
			
			static void fs_Feed(t_CStream &_Stream, CStreamableVariant const &_Data)
			{
				_Stream << _Data.f_GetTypeID();
				_Data.f_Visit(NPrivate::TCVariantVisitor_Feed<t_CStream>(_Stream));
			}
	
			static void fs_Feed(t_CStream &_Stream, CStreamableVariant &&_Data)
			{
				_Stream << _Data.f_GetTypeID();
				_Data.f_Visit(NPrivate::TCVariantVisitor_FeedMove<t_CStream>(_Stream));
			}
	
			static void fs_Consume(t_CStream &_Stream, CStreamableVariant &_Data)
			{
				typename CStreamableVariant::CIndexType TypeID;
				_Stream >> TypeID;
				_Data.f_VisitCreate(TypeID, NPrivate::TCVariantVisitor_Consume<t_CStream>(_Stream));
			}
		};

	}

	template <typename t_CVisitor, typename t_CToVisit0>
	void fg_Visit(t_CVisitor &&_Visitor, t_CToVisit0 &&_ToVisit0)
	{
		fg_Forward<t_CToVisit0>(_ToVisit0).f_Visit(fg_Forward<t_CVisitor>(_Visitor));
	}

	template <typename t_CReturn, typename t_CVisitor, typename t_CToVisit0>
	t_CReturn fg_VisitRet(t_CVisitor &&_Visitor, t_CToVisit0 &&_ToVisit0)
	{
		return fg_Forward<t_CToVisit0>(_ToVisit0).template f_VisitRet<t_CReturn>(fg_Forward<t_CVisitor>(_Visitor));
	}

	template <typename t_CRet, typename t_CVisitor, typename t_CToVisit>
	struct TCInnerVisitor
	{
		t_CVisitor m_Visitor;
		t_CToVisit m_ToVisit;

		TCInnerVisitor(t_CVisitor _Visitor, t_CToVisit _ToVisit)
			: m_Visitor(_Visitor)
			, m_ToVisit(_ToVisit)
		{
		}
		
		template <typename t_CInnerVisitor, typename t_CValue>
		struct TCValueVisitor
		{
			t_CInnerVisitor m_Visitor;
			t_CValue m_Value;
			TCValueVisitor(t_CInnerVisitor _Visitor, t_CValue _Value)
				: m_Visitor(_Visitor)
				, m_Value(_Value)
			{
			}
			template <typename t_CType>
			t_CRet operator () (t_CType &&_Type)
			{
				return m_Visitor(fg_Forward<t_CValue>(m_Value), fg_Forward<t_CType>(_Type));
			}
		};

		template <typename t_CType>
		t_CRet operator () (t_CType &&_Value)
		{
			TCValueVisitor<t_CVisitor, t_CType> Visitor(m_Visitor, _Value);

			return fg_VisitRet<t_CRet>(Visitor, fg_Forward<t_CToVisit>(m_ToVisit));
		}
	};

	template <typename t_CVisitor, typename t_CToVisit0, typename t_CToVisit1>
	void fg_Visit(t_CVisitor &&_Visitor, t_CToVisit0 &&_ToVisit0, t_CToVisit1 &&_ToVisit1)
	{
		TCInnerVisitor<void, t_CVisitor, t_CToVisit1> Visitor(_Visitor, _ToVisit1);
		fg_Visit(Visitor, _ToVisit0);
	}

	template <typename t_CRet, typename t_CVisitor, typename t_CToVisit0, typename t_CToVisit1>
	t_CRet fg_VisitRet(t_CVisitor &&_Visitor, t_CToVisit0 &&_ToVisit0, t_CToVisit1 &&_ToVisit1)
	{
		TCInnerVisitor<t_CRet, t_CVisitor, t_CToVisit1> Visitor(_Visitor, _ToVisit1);
		return fg_VisitRet<t_CRet>(Visitor, _ToVisit0);
	}
	

}
