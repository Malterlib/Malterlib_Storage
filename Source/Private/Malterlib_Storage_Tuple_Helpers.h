// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib
{
	namespace NPrivate
	{
		template <typename t_CDestination, typename t_CSource, bool t_bDestinationIsReference = NMib::NTraits::TCIsLValueReference<t_CDestination>::mc_Value>
		struct TCConvertMoveHelper
		{
			typedef typename NMib::NTraits::TCRemoveReference<t_CSource>::CType &&CType;
		};

		template <typename t_CDestination, typename t_CSource>
		struct TCConvertMoveHelper<t_CDestination, t_CSource, true>
		{
			typedef t_CSource CType;
		};
	}
	
	template <typename tf_CDestinationType, typename tf_CType> 
	inline_always_debug typename NPrivate::TCConvertMoveHelper<tf_CDestinationType, tf_CType>::CType fg_ConvertMove(tf_CType &&_ToMove) noexcept
	{
    	return ((typename NPrivate::TCConvertMoveHelper<tf_CDestinationType, tf_CType>::CType)_ToMove);
	}
	
	namespace NContainer
	{
		namespace NPrivate
		{
			template <typename t_CType, typename t_CTypeCleaned = typename NTraits::TCRemoveReferenceAndQualifiers<t_CType>::CType>
			struct TCIsTuple
			{
				static constexpr bool mc_Value = false;
			};
			
			template <typename t_CType, typename... t_PCTypes>
			struct TCIsTuple<t_CType, TCTuple<t_PCTypes...>>
			{
				static constexpr bool mc_Value = true;
				static constexpr mint mc_nTypes = sizeof...(t_PCTypes);
				typedef TCTuple<t_PCTypes...> CType;
			};
		}

		template <mint tf_Index, typename tf_CType>
		typename NTraits::TCCopyQualifiersAndReference<tf_CType &&, typename TCTuple_Get<tf_Index, typename NPrivate::TCIsTuple<tf_CType &&>::CType>::CType>::CType
		fg_Get(tf_CType &&_Tuple) noexcept;

		template <mint tf_Index, typename tf_CType>
		typename NTraits::TCPromoteQualifiersAndReference<tf_CType &&, typename TCTuple_Get<tf_Index, typename NPrivate::TCIsTuple<tf_CType &&>::CType>::CType>::CType
		fg_GetForward(tf_CType &&_Tuple) noexcept;
		
		namespace NPrivate
		{
			// TCTupleLeaf

			template <typename t_CSourceList>
			struct TCTupleConvertToTypeListHelper;

			template <typename... t_PCTypes>
			struct TCTupleConvertToTypeListHelper<TCTuple<t_PCTypes...>>
			{
				typedef NMeta::TCTypeList<t_PCTypes...> CType;
			};

			
			template <typename t_CSourceList>
			struct TCTupleConvertToTypeList
			{
				typedef typename TCTupleConvertToTypeListHelper
					<
						typename NTraits::TCRemoveQualifiers<typename NTraits::TCRemoveReference<t_CSourceList>::CType>::CType
					>::CType CTypeUnreferenced;
				;
				
				typedef typename NTraits::TCCopyQualifiersAndReference<t_CSourceList, CTypeUnreferenced>::CType CType;
			};
			
			template <typename t_CSourceList, mint t_End = TCTuple_Len<typename NTraits::TCRemoveReference<t_CSourceList>::CType>::mc_Value, mint t_Start = 0>
			struct TCTuple_MakePromotedLValueRefList
				: public NMeta::TCTypeList_MakePromotedLValueRef<typename TCTupleConvertToTypeList<t_CSourceList>::CType, t_End, t_Start>
			{
			};
			
			template <typename t_CType>
			struct TCTuple_CompatibleType
				: NTraits::CCompileTimeFalse
			{
			};

			template <typename t_CType>
			struct TCTuple_CompatibleType<t_CType const>
				: TCTuple_CompatibleType<t_CType>
			{
			};

			template <typename t_CType>
			struct TCTuple_CompatibleType<t_CType volatile>
				: TCTuple_CompatibleType<t_CType>
			{
			};

			template <typename t_CType>
			struct TCTuple_CompatibleType<t_CType const volatile>
				: TCTuple_CompatibleType<t_CType>
			{
			};

			template <typename... t_PCTypes>
			struct TCTuple_CompatibleType<TCTuple<t_PCTypes...>>
				: NTraits::CCompileTimeTrue
			{
			};
			
			template 
			<
				typename t_CFrom
				, typename t_CTo
				, bool t_bFromCompatible = TCTuple_CompatibleType<typename NTraits::TCRemoveReference<t_CFrom>::CType>::mc_Value
				, bool t_bToCompatible = TCTuple_CompatibleType<t_CTo>::mc_Value
			>
			struct TCTuple_IsConstructible
				: public NTraits::CCompileTimeFalse
			{
			};

			template <typename t_CForm, typename t_CTo>
			struct TCTuple_IsConstructible<t_CForm, t_CTo, true, true>
				: public NMeta::TCTypeList_IsConstructible
				<
					typename TCTuple_MakePromotedLValueRefList<t_CForm>::CType
					, typename TCTuple_MakePromotedLValueRefList<t_CTo>::CType
				>
			{
			};

			template 
			<
				typename t_CFrom
				, typename t_CTo
				, bool t_bFromCompatible = TCTuple_CompatibleType<typename NTraits::TCRemoveReference<t_CFrom>::CType>::mc_Value
				, bool t_bToCompatible = TCTuple_CompatibleType<t_CTo>::mc_Value
			>
			struct TCTuple_IsAssignable 
				: public NTraits::CCompileTimeFalse
			{
			};

			template <typename t_CForm, typename t_CTo>
			struct TCTuple_IsAssignable<t_CForm, t_CTo, true, true>
				: public NMeta::TCTypeList_IsAssignable
				<
					typename TCTuple_MakePromotedLValueRefList<t_CForm>::CType
					, typename TCTuple_MakePromotedLValueRefList<t_CTo>::CType
				>
			{
			};

			template 
			<
				mint t_Index
				, typename t_CType
				, bool t_bNoStorage = NTraits::TCIsEmpty<t_CType>::mc_Value
//#if __has_feature(is_final)
//				&& !__is_final(t_CType)
//#endif
			>
			class TCTupleLeaf;

			template <typename t_CType, typename t_CTypeCleaned = typename NTraits::TCRemoveReferenceAndQualifiers<t_CType>::CType>
			struct TCTupleLeafTraits
			{
				static constexpr bool mc_IsTupleLeaf = false;
				typedef void CType;
			};
			
			template <typename t_CType, mint t_Index, typename t_CLeafType, bool t_bNoStorage>
			struct TCTupleLeafTraits<t_CType, TCTupleLeaf<t_Index, t_CLeafType, t_bNoStorage>>
			{
				static constexpr bool mc_IsTupleLeaf = true;
				typedef typename NTraits::TCPromoteQualifiersAndReference<t_CType, t_CLeafType>::CType CType;
			};
			
			template <mint t_Index, typename t_CType, bool t_bNoStorage>
			class TCTupleLeaf
			{
				t_CType mp_Value;
				
			public:
				
				inline_always constexpr 
				TCTupleLeaf()
					noexcept(NTraits::TCHasNothrowDefaultConstructor<t_CType>::mc_Value) 
					: mp_Value()
				{
					static_assert(!NTraits::TCIsReference<t_CType>::mc_Value, "Attempted to default construct a reference element in a tuple");
				}

				inline_always constexpr 
				TCTupleLeaf(NMib::NInternal::CDefault &&)
					noexcept(NTraits::TCHasNothrowDefaultConstructor<t_CType>::mc_Value) 
					: mp_Value()
				{
				}
				// Direct param
				template 
				<
					typename tf_CParam
					, typename TCEnableIf
					<
						!TCTupleLeafTraits<tf_CParam>::mc_IsTupleLeaf
						&& NTraits::TCIsConstructorCallableWith<t_CType, void (tf_CParam &&)>::mc_Value
						, bool
					>::CType = false
				>
				inline_always explicit 
				TCTupleLeaf(tf_CParam &&_Param) 
					noexcept(NTraits::TCIsConstructorNothrowCallableWith<t_CType, void (tf_CParam &&)>::mc_Value)
					: mp_Value(fg_Forward<tf_CParam>(_Param))
				{
					static_assert
						(
							!NTraits::TCIsReference<t_CType>::mc_Value 
							|| 
							(
								NTraits::TCIsLValueReference<t_CType>::mc_Value 
								&& 
								(
									NTraits::TCIsLValueReference<tf_CParam>::mc_Value 
									|| NReference::TCIsReference<tf_CParam>::mc_Value
								)
							)
							||
							(
								NTraits::TCIsRValueReference<t_CType>::mc_Value 
								&& !NTraits::TCIsRValueReference<tf_CParam>::mc_Value
							)
							, "Attempted to construct a reference element in a tuple with an rvalue"
						)
					;
				}
 
				// Other leaf
				inline_always explicit 
				TCTupleLeaf(TCTupleLeaf const &_Param)
					noexcept(NTraits::TCIsConstructorNothrowCallableWith<t_CType, void (t_CType const &)>::mc_Value)
					: mp_Value(_Param.f_Get()) 
				{
				}
				
				inline_always explicit 
				TCTupleLeaf(TCTupleLeaf &&_Param)
					noexcept(NTraits::TCIsConstructorNothrowCallableWith<t_CType, void (t_CType &&)>::mc_Value)
					: mp_Value(fg_ConvertMove<t_CType>(_Param.f_Get()))
				{
				}
				
				template 
				<
					typename tf_CParam
					, typename TCEnableIf
					<
						TCTupleLeafTraits<tf_CParam>::mc_IsTupleLeaf
						&& NTraits::TCIsConstructorCallableWith<t_CType, void (typename TCTupleLeafTraits<tf_CParam>::CType)>::mc_Value
						, bool
					>::CType = false
				>
				inline_always  
				TCTupleLeaf(tf_CParam &&_Param)
					noexcept(NTraits::TCIsConstructorNothrowCallableWith<t_CType, void (typename TCTupleLeafTraits<tf_CParam>::CType)>::mc_Value)
					: mp_Value(fg_Forward<typename TCTupleLeafTraits<tf_CParam>::CType>(_Param.f_Get())) 
				{
				}
				
				// Assignment
				template <typename tf_CParam>
				inline_always
				TCTupleLeaf &operator =(tf_CParam &&_Other) 
					noexcept((NTraits::TCIsOperatorNothrowCallableWith_Assign<t_CType, void (tf_CParam &&)>::mc_Value))
				{
					mp_Value = fg_Forward<tf_CParam>(_Other);
					return *this;
				}

				inline_always
				TCTupleLeaf &operator =(TCTupleLeaf const &_Param) 
					noexcept(NTraits::TCIsOperatorNothrowCallableWith_Assign<t_CType, void (t_CType const &)>::mc_Value)
				{
					mp_Value = _Param.f_Get();
					return *this;
				}
				
				inline_always
				TCTupleLeaf &operator =(TCTupleLeaf &&_Param) 
					noexcept(NTraits::TCIsOperatorNothrowCallableWith_Assign<t_CType, void (t_CType &&)>::mc_Value)
				{
					mp_Value = fg_ConvertMove<t_CType>(_Param.f_Get());
					return *this;
				}
				
				inline_always t_CType &f_Get() noexcept
				{
					return mp_Value;
				}

				inline_always t_CType const &f_Get() const noexcept 
				{
					return mp_Value;
				}

				inline_always t_CType volatile &f_Get() volatile noexcept 
				{
					return mp_Value;
				}

				inline_always t_CType const volatile &f_Get() const volatile noexcept 
				{
					return mp_Value;
				}
			};
			
			template <mint t_Index, typename t_CType>
			class TCTupleLeaf<t_Index, t_CType, true>
			{
			public:
				
				inline_always constexpr 
				TCTupleLeaf()
					noexcept(NTraits::TCHasNothrowDefaultConstructor<t_CType>::mc_Value) 
				{
				}

				inline_always constexpr 
				TCTupleLeaf(NMib::NInternal::CDefault &&)
					noexcept(NTraits::TCHasNothrowDefaultConstructor<t_CType>::mc_Value) 
				{
				}

				// Direct param
				template 
				<
					typename tf_CParam
					, typename TCEnableIf
					<
						!TCTupleLeafTraits<tf_CParam &&>::mc_IsTupleLeaf
						&& NTraits::TCIsConstructorCallableWith<t_CType, void (tf_CParam &&)>::mc_Value
						, bool
					>::CType = false
				>
				inline_always explicit 
				TCTupleLeaf(tf_CParam &&_Param)
					noexcept(NTraits::TCIsConstructorNothrowCallableWith<t_CType, void (tf_CParam &&)>::mc_Value)
				{
					new((void *)&f_Get()) t_CType(fg_Forward<tf_CParam>(_Param));
				}

				// Other leaf
				inline_always explicit 
				TCTupleLeaf(TCTupleLeaf const &_Param)
					noexcept(NTraits::TCIsConstructorNothrowCallableWith<t_CType, void (t_CType const &)>::mc_Value)
				{
					new((void *)&f_Get()) t_CType(_Param.f_Get());
				}
				inline_always explicit 
				TCTupleLeaf(TCTupleLeaf &&_Param)
					noexcept(NTraits::TCIsConstructorNothrowCallableWith<t_CType, void (t_CType &&)>::mc_Value)
				{
					new((void *)&f_Get()) t_CType(fg_ConvertMove<t_CType>(_Param.f_Get()));
				}
				
				template 
				<
					typename tf_CParam
					, typename TCEnableIf
					<
						TCTupleLeafTraits<tf_CParam>::mc_IsTupleLeaf
						&& NTraits::TCIsConstructorCallableWith<t_CType, void (typename TCTupleLeafTraits<tf_CParam>::CType)>::mc_Value
						, bool
					>::CType = false
				>
				inline_always explicit 
				TCTupleLeaf(tf_CParam &&_Param)
					noexcept(NTraits::TCIsConstructorNothrowCallableWith<t_CType, void (typename TCTupleLeafTraits<tf_CParam>::CType)>::mc_Value)
				{
					new((void *)&f_Get()) t_CType(fg_Forward<typename TCTupleLeafTraits<tf_CParam>::CType>(_Param.f_Get()));
				}

				// Other tuple leaf assign
				template <typename tf_CParam>
				inline_always
				TCTupleLeaf &operator =(tf_CParam &&_Param) 
					noexcept(NTraits::TCIsOperatorNothrowCallableWith_Assign<t_CType, void (tf_CParam &&)>::mc_Value)
				{
					f_Get().operator=(fg_Forward<tf_CParam>(_Param));
					return *this;
				}

				inline_always
				TCTupleLeaf &operator =(TCTupleLeaf const &_Param) 
					noexcept(NTraits::TCIsOperatorNothrowCallableWith_Assign<t_CType, void (t_CType const &)>::mc_Value)
				{
					f_Get().operator =(_Param.f_Get());
					return *this;
				}
				
				inline_always
				TCTupleLeaf &operator =(TCTupleLeaf &&_Param) 
					noexcept(NTraits::TCIsOperatorNothrowCallableWith_Assign<t_CType, void (t_CType &&)>::mc_Value)
				{
					f_Get().operator =(fg_ConvertMove<t_CType>(_Param.f_Get()));
					return *this;
				}
				
				inline_always t_CType &f_Get() noexcept
				{
					return *((t_CType *)this);
				}
				inline_always t_CType const &f_Get() const noexcept
				{
					return *((t_CType const *)this);
				}
				inline_always t_CType volatile &f_Get() volatile noexcept
				{
					return *((t_CType volatile *)this);
				}
				inline_always t_CType const volatile &f_Get() const volatile noexcept
				{
					return *((t_CType const volatile *)this);
				}
				
			};

			template <typename t_CIndices, typename... t_PCTypes> struct 
			TCTupleImp;

			template <bool t_bEnable, typename... t_PCTypes>
			struct TCDefaultCopy
			{
				TCDefaultCopy() = default;
				TCDefaultCopy(TCDefaultCopy const &) = default;
				TCDefaultCopy(TCDefaultCopy &&) = default;
				TCDefaultCopy &operator = (TCDefaultCopy const &) = default;
				TCDefaultCopy &operator = (TCDefaultCopy &&) = default;
			};

			template <typename... t_PCTypes>
			struct TCDefaultCopy<false, t_PCTypes...>
			{
				TCDefaultCopy() = default;
				TCDefaultCopy(TCDefaultCopy const &) = delete;
				TCDefaultCopy(TCDefaultCopy &&) = default;
				TCDefaultCopy &operator = (TCDefaultCopy const &) = default;
				TCDefaultCopy &operator = (TCDefaultCopy &&) = default;
			};

			template <bool t_bEnable, typename... t_PCTypes>
			struct TCDefaultMove
			{
				TCDefaultMove() = default;
				TCDefaultMove(TCDefaultMove const &) = default;
				TCDefaultMove(TCDefaultMove &&) = default;
				TCDefaultMove &operator = (TCDefaultMove const &) = default;
				TCDefaultMove &operator = (TCDefaultMove &&) = default;
			};

			template <typename... t_PCTypes>
			struct TCDefaultMove<false, t_PCTypes...>
			{
				TCDefaultMove() = default;
				TCDefaultMove(TCDefaultMove const &) = default;
				TCDefaultMove(TCDefaultMove &&) = delete;
				TCDefaultMove &operator = (TCDefaultMove const &) = default;
				TCDefaultMove &operator = (TCDefaultMove &&) = default;
			};

			template <bool t_bEnable, typename... t_PCTypes>
			struct TCDefaultAssign
			{
				TCDefaultAssign() = default;
				TCDefaultAssign(TCDefaultAssign const &) = default;
				TCDefaultAssign(TCDefaultAssign &&) = default;
				TCDefaultAssign &operator = (TCDefaultAssign const &) = default;
				TCDefaultAssign &operator = (TCDefaultAssign &&) = default;
			};

			template <typename... t_PCTypes>
			struct TCDefaultAssign<false, t_PCTypes...>
			{
				TCDefaultAssign() = default;
				TCDefaultAssign(TCDefaultAssign const &) = default;
				TCDefaultAssign(TCDefaultAssign &&) = default;
				TCDefaultAssign &operator = (TCDefaultAssign const &) = delete;
				TCDefaultAssign &operator = (TCDefaultAssign &&) = default;
			};
				
			template <bool t_bEnable, typename... t_PCTypes>
			struct TCDefaultMoveAssign
			{
				TCDefaultMoveAssign() = default;
				TCDefaultMoveAssign(TCDefaultMoveAssign const &) = default;
				TCDefaultMoveAssign(TCDefaultMoveAssign &&) = default;
				TCDefaultMoveAssign &operator = (TCDefaultMoveAssign const &) = delete;
				TCDefaultMoveAssign &operator = (TCDefaultMoveAssign &&) = default;
			};

			template <typename... t_PCTypes>
			struct TCDefaultMoveAssign<false, t_PCTypes...>
			{
				TCDefaultMoveAssign() = default;
				TCDefaultMoveAssign(TCDefaultMoveAssign const &) = default;
				TCDefaultMoveAssign(TCDefaultMoveAssign &&) = default;
				TCDefaultMoveAssign &operator = (TCDefaultMoveAssign const &) = default;
				TCDefaultMoveAssign &operator = (TCDefaultMoveAssign &&) = delete;
			};
				
				
			template <mint... t_PIndices, typename... t_PCTypes>
			struct TCTupleImp<NMeta::TCIndices<t_PIndices...>, t_PCTypes...>
				: public TCTupleLeaf<t_PIndices, t_PCTypes>...
			{
				constexpr TCTupleImp()
					noexcept(NMeta::TCAllIsTrue<NTraits::TCHasNothrowDefaultConstructor<t_PCTypes>::mc_Value...>::mc_Value) 
				{
				}

				// Params
				template 
				<
					mint... tf_PIndices
					, typename... tf_PCTypes
					, mint... tf_PDefaultConstructIndices
					, typename... tf_PCDefaultConstructTypes
					, typename... tf_PCConstructArguments
				>
				inline_always explicit 
				TCTupleImp
					(
						NMeta::TCIndices<tf_PIndices...>
						, NMeta::TCTypeList<tf_PCTypes...>
						, NMeta::TCIndices<tf_PDefaultConstructIndices...>
						, NMeta::TCTypeList<tf_PCDefaultConstructTypes...>
						, tf_PCConstructArguments &&..._Arguments
					)
					noexcept
					(
						NMeta::TCAllIsTrue<NTraits::TCIsConstructorNothrowCallableWith<TCTupleLeaf<tf_PIndices, tf_PCTypes>, void (tf_PCConstructArguments &&)>::mc_Value...>::mc_Value
						&& NMeta::TCAllIsTrue<NTraits::TCHasNothrowDefaultConstructor<tf_PCDefaultConstructTypes>::mc_Value...>::mc_Value
					) 
					: TCTupleLeaf<tf_PIndices, tf_PCTypes>(fg_Forward<tf_PCConstructArguments>(_Arguments))...
					, TCTupleLeaf<tf_PDefaultConstructIndices, tf_PCDefaultConstructTypes>()...
				{
				}
				
				// Other tuple
				template 
				<
					typename tf_CTuple
					, typename TCEnableIf
					<
						TCTuple_IsConstructible<tf_CTuple, TCTuple<t_PCTypes...>>::mc_Value
						, bool
					>::CType = false
				>
				inline_always
				TCTupleImp(tf_CTuple &&_Param)
					noexcept
					(
						NMeta::TCAllIsTrue
						<
							NTraits::TCIsConstructorNothrowCallableWith
							<
								TCTupleLeaf<t_PIndices, t_PCTypes>
								, void (typename TCTuple_Get<t_PIndices, typename TCTuple_MakePromotedLValueRefList<tf_CTuple>::CType>::CType)
							>::mc_Value...
						>::mc_Value
					)
					: TCTupleLeaf<t_PIndices, t_PCTypes>
					(
						fg_Forward<typename TCTuple_Get<t_PIndices, typename TCTuple_MakePromotedLValueRefList<tf_CTuple>::CType>::CType>(fg_Get<t_PIndices>(_Param))
					)...
				{
				}
				
				// Other tuple assign
				template <typename tf_CTuple>
				inline_always
				typename TCEnableIf
				<
					TCTuple_IsAssignable<tf_CTuple, TCTuple<t_PCTypes...>>::mc_Value
					, TCTupleImp &
				>::CType
				operator = (tf_CTuple &&_Param)
					noexcept
					(
						NMeta::TCAllIsTrue
						<
							NTraits::TCIsOperatorNothrowCallableWith_Assign
							<
								TCTupleLeaf<t_PIndices, t_PCTypes>
								, void (typename TCTuple_Get<t_PIndices, typename TCTuple_MakePromotedLValueRefList<tf_CTuple>::CType>::CType)
							>::mc_Value...
						>::mc_Value
					)
				{
					fg_Swallow
						(
							TCTupleLeaf<t_PIndices, t_PCTypes>::operator =
							(
								fg_Forward<typename TCTuple_Get<t_PIndices, typename TCTuple_MakePromotedLValueRefList<tf_CTuple>::CType>::CType>
								(
									fg_Get<t_PIndices>(_Param)
								)
							)...
						)
					;
					return *this;
				}
				
			};
		
			template <mint t_Index, mint t_End>
			struct TCTupleEqualImp
			{
				template <typename tf_CTupleLeft, typename tf_CTupleRight>
				inline_always
				bool operator()(tf_CTupleLeft &&_Left, tf_CTupleRight &&_Right)
				{
					return 
						fg_Get<t_Index>(fg_Forward<tf_CTupleLeft>(_Left)) == fg_Get<t_Index>(fg_Forward<tf_CTupleRight>(_Right))
						&& TCTupleEqualImp<t_Index+1, t_End>()(fg_Forward<tf_CTupleLeft>(_Left), fg_Forward<tf_CTupleRight>(_Right)) 
					;
				}
			};
			
			template <mint t_End>
			struct TCTupleEqualImp<t_End, t_End>
			{
				template <typename tf_CTupleLeft, typename tf_CTupleRight>
				inline_always
				bool operator()(tf_CTupleLeft &&_Left, tf_CTupleRight &&_Right)
				{
					return true;
				}
			};
			
			template <mint t_Index, mint t_End>
			struct TCTupleLessImp
			{
				template <typename tf_CTupleLeft, typename tf_CTupleRight>
				inline_always
				bool operator()(tf_CTupleLeft &&_Left, tf_CTupleRight &&_Right)
				{
					return 
						fg_Get<t_Index>(fg_Forward<tf_CTupleLeft>(_Left)) < fg_Get<t_Index>(fg_Forward<tf_CTupleRight>(_Right))
						||
						(
							!(fg_Get<t_Index>(fg_Forward<tf_CTupleRight>(_Right)) < fg_Get<t_Index>(fg_Forward<tf_CTupleLeft>(_Left)))
							&& TCTupleLessImp<t_Index + 1, t_End>()(fg_Forward<tf_CTupleLeft>(_Left), fg_Forward<tf_CTupleRight>(_Right))
						)
					;
				}
			};
			
			template <mint t_End>
			struct TCTupleLessImp<t_End, t_End>
			{
				template <typename tf_CTupleLeft, typename tf_CTupleRight>
				inline_always
				bool operator()(tf_CTupleLeft &&_Left, tf_CTupleRight &&_Right)
				{
					return false;
				}
			};
		}
	}
}
