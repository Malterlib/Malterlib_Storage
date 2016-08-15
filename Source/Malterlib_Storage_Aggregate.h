// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

namespace NMib
{

	class CSystem;
	class CSystemModule;
	namespace NAggregate
	{

		template <typename t_CData = aint>
		class TCAggregateSimple
		{
			typedef t_CData CData;
			typedef uint8 CObjectType[sizeof(CData)];
			typedef typename NTraits::TCAlign<CObjectType, NTraits::TCAlignmentOf<CData>::mc_Value>::CType CTypeAligned;
			public:
			CTypeAligned m_ObjectSpace;

#ifndef DMibNoAggregateConstexpr
			TCAggregateSimple() = delete;
			constexpr TCAggregateSimple(EAggregateInitialization _Init)
				: m_ObjectSpace{}
			{
			}
#endif
			
			void f_Destruct()
			{
				((t_CData *)m_ObjectSpace.m_Aligned)->t_CData::~t_CData();
			}

			template <typename ...tfp_CParam>
			void f_Construct(tfp_CParam && ...p_Params)
			{
				new(m_ObjectSpace.m_Aligned) t_CData(fg_Forward<tfp_CParam>(p_Params)...);
			}

			inline_small operator t_CData *()
			{
				return ((t_CData *)m_ObjectSpace.m_Aligned);
			}

			inline_small operator t_CData const *() const
			{
				return ((t_CData *)m_ObjectSpace.m_Aligned);
			}

			inline_small t_CData * operator ->()
			{
				return ((t_CData *)m_ObjectSpace.m_Aligned);
			}

			inline_small t_CData const * operator ->() const
			{
				return ((t_CData const *)m_ObjectSpace.m_Aligned);
			}

/*			inline_small t_CData & operator &()
			{
				return *((t_CData *)m_ObjectSpace.m_Aligned);
			}*/
		};

		template <typename t_CData, aint t_Priority = 128, typename t_CLock = NThread::CMutualAggregate>
		class TCAggregate;

		typedef TCAggregate<aint, 128, NThread::CNoLock> CAggregate;

		template <typename t_CData, aint t_Priority, typename t_CLock>
		class TCAggregate
		{
			typedef t_CData CData;
			typedef uint8 CObjectType[sizeof(CData)];
			typedef typename NTraits::TCAlign<CObjectType, NTraits::TCAlignmentOf<CData>::mc_Value>::CType CTypeAligned;
		public:

#ifndef DMibNoAggregateConstexpr
			TCAggregate() = delete;
			constexpr TCAggregate(EAggregateInitialization _Init)
				: m_bConstructed{0}
				, m_bDestructed{0}
				, m_Link{_Init}
				, m_Priority{0}
				, m_fDestruct{nullptr}
				, m_ObjectSpace{}
				, m_Lock{_Init}
			{
			}
#endif
			typedef void (PFAggregateDestruct)(CAggregate *_pThis);
			uint32 m_bConstructed:1;
			uint32 m_bDestructed:1;
			DMibListLinkDA_Link(TCAggregate, m_Link);
			aint m_Priority;

			PFAggregateDestruct *m_fDestruct;

			CTypeAligned m_ObjectSpace;

			t_CLock m_Lock;


			static void fs_Destruct(CAggregate *_pThis)
			{
				((TCAggregate<t_CData, t_Priority, t_CLock> *)_pThis)->f_Destruct();				
			}

			void f_Destruct();
			void f_Clear();

			void f_Lock()
			{
				return m_Lock.f_Lock();
			}

			void f_Unlock()
			{
				return m_Lock.f_Unlock();
			}

			bint f_IsConstructed()
			{
				return m_bConstructed;
			}

			bint f_WasDestructed()
			{
				return m_bDestructed;
			}

			template <typename tf_CFunctor>
			void f_ConstructFunctor(tf_CFunctor const &_fFunctor);

			template <typename... tfp_CData>
			void f_Construct(tfp_CData && ... p_Params);

			template <typename tf_CFunctor>
			inline_small t_CData * f_CreateFunctor(tf_CFunctor const &_fFunctor)
			{
				if (!m_bConstructed)
				{
					f_ConstructFunctor(_fFunctor);
				}

				return ((t_CData *)m_ObjectSpace.m_Aligned);
			}
			
			inline_small operator t_CData *()
			{
				if (!m_bConstructed)
					f_Construct();

				return ((t_CData *)m_ObjectSpace.m_Aligned);
			}

			inline_small t_CData &f_GetUnsafe()
			{
				return *((t_CData *)m_ObjectSpace.m_Aligned);
			}

			template <typename tf_CData0>
			inline_small t_CData * operator() (tf_CData0 &_Data0)
			{
				if (!m_bConstructed)
					f_Construct(_Data0);

				return ((t_CData *)m_ObjectSpace.m_Aligned);
			}

			template <typename tf_CData0, typename tf_CData1>
			inline_small t_CData * operator() (tf_CData0 &_Data0, tf_CData1 &_Data1)
			{
				if (!m_bConstructed)
					f_Construct(_Data0, _Data1);

				return ((t_CData *)m_ObjectSpace.m_Aligned);
			}

			template <typename tf_CData0, typename tf_CData1, typename tf_CData2>
			inline_small t_CData * operator() (tf_CData0 &_Data0, tf_CData1 &_Data1, tf_CData2 &_Data2)
			{
				if (!m_bConstructed)
					f_Construct(_Data0, _Data1, _Data2);

				return ((t_CData *)m_ObjectSpace.m_Aligned);
			}

			template <typename tf_CData0, typename tf_CData1, typename tf_CData2, typename tf_CData3>
			inline_small t_CData * operator() (tf_CData0 &_Data0, tf_CData1 &_Data1, tf_CData2 &_Data2, tf_CData3 &_Data3)
			{
				if (!m_bConstructed)
					f_Construct(_Data0, _Data1, _Data2, _Data3);

				return ((t_CData *)m_ObjectSpace.m_Aligned);
			}

			inline_small t_CData * operator ->()
			{
				if (!m_bConstructed)
					f_Construct();

				return ((t_CData *)m_ObjectSpace.m_Aligned);
			}

			inline_small t_CData & operator *()
			{
				if (!m_bConstructed)
					f_Construct();

				return *((t_CData *)m_ObjectSpace.m_Aligned);
			}

/*			inline_small t_CData & operator &()
			{
				if (!m_bConstructed)
					f_Construct();

				return *((t_CData *)m_ObjectSpace.m_Aligned);
			}*/
		};

	}

}

#ifndef DMibPNoShortCuts
	using namespace NMib::NAggregate;
#endif

