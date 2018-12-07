
/*¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯*\
|	File:			Short_desscription															|
|																								|
|	Author:			Erik Olofsson																|
|																								|
|	Copyright:		Erik Olofsson, 2002															|
|																								|
|	Contents:		A_list_of_classes_functions_etc_defined_in_file								|
|																								|
|	Comments:		Longer_description_not_mandatory											|
|																								|
|	History:																					|
|		020316:		Created File																|
\*_____________________________________________________________________________________________*/

#include <Mib/Core/Core>

namespace NMib::NStorage
{
	template <typename t_CData, typename t_CLock = NThread::CMutual>
	class TCLazyInit
	{
	public:

		TCLazyInit();
		~TCLazyInit();

		template <typename ...tfp_CParam>
		inline_small t_CData *operator() (tfp_CParam && ...p_Param);
		inline_small t_CData *operator ->();
		inline_small t_CData &operator *();

	private:
		template <typename... tfp_CData>
		void fp_Construct(tfp_CData && ... p_Params);

		typedef t_CData CData;
		typedef uint8 CObjectType[sizeof(CData)];
		typedef typename NTraits::TCAlign<CObjectType, NTraits::TCAlignmentOf<CData>::mc_Value>::CType CTypeAligned;

		CTypeAligned m_ObjectSpace;
		t_CLock m_Lock;
		bool m_bConstructed:1;
		bool m_bDestructed:1;
	};
}

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif

#include "Malterlib_Storage_LazyInit.hpp"
