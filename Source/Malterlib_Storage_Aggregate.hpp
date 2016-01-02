// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

namespace NMib
{
	namespace NAggregate
	{
		template <typename t_CData, aint t_Priority, typename t_CLock>
		void TCAggregate<t_CData, t_Priority, t_CLock>::f_Destruct()
		{
			DMibSafeCheck(m_bConstructed && !m_bDestructed, "Should not arrive here unless we are constructed");
			m_bDestructed = true;
			((t_CData *)m_ObjectSpace.m_Aligned)->~t_CData();
			fg_GetModule()->f_RemoveAggregate((CAggregate*)this);
			m_Link.f_Destruct();
			m_bConstructed = false;
			m_Lock.f_Destruct();
		}

		template <typename t_CData, aint t_Priority, typename t_CLock>
		template <typename tf_CFunctor>
		void TCAggregate<t_CData, t_Priority, t_CLock>::f_ConstructFunctor(tf_CFunctor const &_fFunctor)
		{
			DMibLockTyped(t_CLock, m_Lock);
			DMibSafeCheck(!m_bDestructed, "Already destructed, cannot construct again");
			if (!m_bConstructed)
			{
				m_fDestruct = (PFAggregateDestruct *)(TCAggregate<t_CData, t_Priority, t_CLock>::fs_Destruct);
				m_Link.f_Construct();
				m_Priority = t_Priority;
				_fFunctor((void *)m_ObjectSpace.m_Aligned);
				fg_GetModule()->f_AddAggregate((CAggregate*)this);
				NMib::NAtomic::fg_MemoryFence();
				m_bConstructed = true;
			}
		}
		
		template <typename t_CData, aint t_Priority, typename t_CLock>
		template <typename... tfp_CData>
		void TCAggregate<t_CData, t_Priority, t_CLock>::f_Construct(tfp_CData && ... p_Params)
		{
			DMibLockTyped(t_CLock, m_Lock);
			DMibSafeCheck(!m_bDestructed, "Already destructed, cannot construct again");
			if (!m_bConstructed)
			{
				m_fDestruct = (PFAggregateDestruct *)(TCAggregate<t_CData, t_Priority, t_CLock>::fs_Destruct);
				m_Link.f_Construct();
				m_Priority = t_Priority;
				new(m_ObjectSpace.m_Aligned) t_CData(fg_Forward<tfp_CData>(p_Params)...);
				fg_GetModule()->f_AddAggregate((CAggregate*)this);
				NMib::NAtomic::fg_MemoryFence();
				m_bConstructed = true;
			}
		}

		template <typename t_CData, aint t_Priority, typename t_CLock>
		void TCAggregate<t_CData, t_Priority, t_CLock>::f_Clear()
		{
			DMibLockTyped(t_CLock, m_Lock);
			if (m_bConstructed)
			{
				((t_CData *)m_ObjectSpace.m_Aligned)->~t_CData();
				fg_GetModule()->f_RemoveAggregate((CAggregate*)this);
				m_Link.f_Destruct();
				NMib::NAtomic::fg_MemoryFence();
				m_bConstructed = false;
			}
		}
	}
}
