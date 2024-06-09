// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

namespace NMib::NStorage
{
	template <typename t_CData, aint t_Priority, typename t_CLock>
	void TCAggregate<t_CData, t_Priority, t_CLock>::f_Destruct()
	{
		[[maybe_unused]] auto OldFlags = m_LifeTimeFlags.f_Load();
		DMibSafeCheck(!(OldFlags & EAggregateLifeTimeFlag_Destructed), "Should not arrive here unless we are constructed");
		((t_CData *)m_ObjectSpace)->~t_CData();
		fg_GetModule()->f_RemoveAggregate((CAggregate*)this);
		m_Link.f_Destruct();
		OldFlags = m_LifeTimeFlags.f_Exchange(EAggregateLifeTimeFlag_Destructed);
		DMibSafeCheck
			(
				(OldFlags & EAggregateLifeTimeFlag_Constructed)
				&& !(OldFlags & EAggregateLifeTimeFlag_Destructed)
				, "Should not arrive here unless we are constructed"
			)
		;
		m_Lock.f_Destruct();
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	template <typename tf_CFunctor>
	void TCAggregate<t_CData, t_Priority, t_CLock>::f_ConstructFunctor(tf_CFunctor const &_fFunctor)
	{
		DMibLockTyped(t_CLock, m_Lock);
		uint32 LifeTimeFlags = m_LifeTimeFlags.f_Load();
		DMibSafeCheck(!(LifeTimeFlags & EAggregateLifeTimeFlag_Destructed), "Already destructed, cannot construct again");
		if (!(LifeTimeFlags & EAggregateLifeTimeFlag_Constructed))
		{
			m_fDestruct = (PFAggregateDestruct *)(TCAggregate<t_CData, t_Priority, t_CLock>::fs_Destruct);
			m_Link.f_Construct();
			m_Priority = t_Priority;
			_fFunctor((void *)m_ObjectSpace);
			fg_GetModule()->f_AddAggregate((CAggregate*)this);
			m_LifeTimeFlags.f_FetchOr(EAggregateLifeTimeFlag_Constructed);
		}
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	template <typename... tfp_CData>
	void TCAggregate<t_CData, t_Priority, t_CLock>::f_Construct(tfp_CData && ... p_Params)
	{
		DMibLockTyped(t_CLock, m_Lock);
		uint32 LifeTimeFlags = m_LifeTimeFlags.f_Load();
		DMibSafeCheck(!(LifeTimeFlags & EAggregateLifeTimeFlag_Destructed), "Already destructed, cannot construct again");
		if (!(LifeTimeFlags & EAggregateLifeTimeFlag_Constructed))
		{
			m_fDestruct = (PFAggregateDestruct *)(TCAggregate<t_CData, t_Priority, t_CLock>::fs_Destruct);
			m_Link.f_Construct();
			m_Priority = t_Priority;
			new(m_ObjectSpace) t_CData(fg_Forward<tfp_CData>(p_Params)...);
			fg_GetModule()->f_AddAggregate((CAggregate*)this);
			m_LifeTimeFlags.f_FetchOr(EAggregateLifeTimeFlag_Constructed);
		}
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	void TCAggregate<t_CData, t_Priority, t_CLock>::f_Clear()
	{
		DMibLockTyped(t_CLock, m_Lock);
		uint32 LifeTimeFlags = m_LifeTimeFlags.f_Load();
		DMibSafeCheck(!(LifeTimeFlags & EAggregateLifeTimeFlag_Destructed), "Already destructed");
		if (LifeTimeFlags & EAggregateLifeTimeFlag_Constructed)
		{
			((t_CData *)m_ObjectSpace)->~t_CData();
			fg_GetModule()->f_RemoveAggregate((CAggregate*)this);
			m_Link.f_Destruct();
			[[maybe_unused]] auto OldFlags = m_LifeTimeFlags.f_Exchange(0);
			DMibSafeCheck(!(OldFlags & EAggregateLifeTimeFlag_Destructed), "Already destructed, race condition");
		}
	}
}
