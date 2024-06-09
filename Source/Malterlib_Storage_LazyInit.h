
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
#include <Mib/Atomic/Atomic>

namespace NMib::NThread
{
	struct CLowLevelLockAggregate;
}

namespace NMib::NStorage
{
	template <typename t_CData, typename t_CLock = NThread::CLowLevelLockAggregate>
	struct TCLazyInit
	{
		constexpr TCLazyInit();
		~TCLazyInit();

		template <typename ...tfp_CParam>
		inline_small t_CData &operator() (tfp_CParam && ...p_Param);
		inline_small t_CData *operator ->();
		inline_small t_CData &operator *();

	private:
		enum ELifetimeFlag
		{
			ELifetimeFlag_None = 0
			, ELifetimeFlag_Constructed = DMibBit(0)
			, ELifetimeFlag_Destructed = DMibBit(1)
		};

		template <typename... tfp_CData>
		void fp_Construct(tfp_CData && ... p_Params);

		typedef t_CData CData;

		alignas(CData) uint8 m_ObjectSpace[sizeof(CData)] = {};
		t_CLock m_Lock;
		NAtomic::TCAtomic<uint32> m_LifetimeFlags = ELifetimeFlag_None;
	};
}

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif
