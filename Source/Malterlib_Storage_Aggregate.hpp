// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

namespace NMib::NStorage
{
	template <typename t_CData>
	constexpr TCAggregateSimple<t_CData>::TCAggregateSimple(EAggregateInitialization _Init)
		: m_ObjectSpace{}
	{
	}

	template <typename t_CData>
	inline_always void TCAggregateSimple<t_CData>::f_Destruct()
	{
		((t_CData *)m_ObjectSpace)->t_CData::~t_CData();
	}

	template <typename t_CData>
	template <typename ...tfp_CParam>
	inline_always void TCAggregateSimple<t_CData>::f_Construct(tfp_CParam && ...p_Params)
	{
		new(m_ObjectSpace) t_CData(fg_Forward<tfp_CParam>(p_Params)...);
	}

	template <typename t_CData>
	inline_small TCAggregateSimple<t_CData>::operator t_CData * ()
	{
		return ((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData>
	inline_small TCAggregateSimple<t_CData>::operator t_CData const * () const
	{
		return ((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData>
	inline_small t_CData *TCAggregateSimple<t_CData>::operator -> ()
	{
		return ((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData>
	inline_small t_CData const *TCAggregateSimple<t_CData>::operator -> () const
	{
		return ((t_CData const *)m_ObjectSpace);
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	constexpr TCAggregate<t_CData, t_Priority, t_CLock>::TCAggregate(EAggregateInitialization _Init)
		: m_LifeTimeFlags{0}
		, m_Link{_Init}
		, m_Priority{0}
		, m_fDestruct{nullptr}
		, m_ObjectSpace{}
		, m_Lock{}
	{
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	void TCAggregate<t_CData, t_Priority, t_CLock>::fs_Destruct(CAggregate *_pThis)
	{
		((TCAggregate<t_CData, t_Priority, t_CLock> *)_pThis)->f_Destruct();
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	void TCAggregate<t_CData, t_Priority, t_CLock>::f_Destruct()
	{
		[[maybe_unused]] auto OldFlags = m_LifeTimeFlags.f_FetchOr(EAggregateLifeTimeFlag_Destructing);
		DMibSafeCheck(!(OldFlags & (EAggregateLifeTimeFlag_Destructed | EAggregateLifeTimeFlag_Destructing)), "Should not arrive here unless we are constructed");
		((t_CData *)m_ObjectSpace)->~t_CData();
		fg_GetModule()->f_RemoveAggregate((CAggregate *)this);
		m_Link.f_Destruct();
		OldFlags = m_LifeTimeFlags.f_Exchange(EAggregateLifeTimeFlag_Destructed);
		DMibSafeCheck((OldFlags & EAggregateLifeTimeFlag_Constructed) && !(OldFlags & EAggregateLifeTimeFlag_Destructed), "Should not arrive here unless we are constructed");
		m_Lock.f_Destruct();
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	void TCAggregate<t_CData, t_Priority, t_CLock>::f_Lock()
	{
		return m_Lock.f_Lock();
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	void TCAggregate<t_CData, t_Priority, t_CLock>::f_Unlock()
	{
		return m_Lock.f_Unlock();
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	bool TCAggregate<t_CData, t_Priority, t_CLock>::f_IsConstructed()
	{
		return m_LifeTimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed;
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	bool TCAggregate<t_CData, t_Priority, t_CLock>::f_WasDestructed()
	{
		return (m_LifeTimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & (EAggregateLifeTimeFlag_Destructed | EAggregateLifeTimeFlag_Destructing)) != EAggregateLifeTimeFlag_None;
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	template <typename tf_FFunctor>
	void TCAggregate<t_CData, t_Priority, t_CLock>::f_ConstructFunctor(tf_FFunctor const &_fFunctor)
	{
		DMibLockTyped(t_CLock, m_Lock);
		uint32 LifeTimeFlags = m_LifeTimeFlags.f_Load();
		DMibSafeCheck(!(LifeTimeFlags & (EAggregateLifeTimeFlag_Destructed | EAggregateLifeTimeFlag_Destructing)), "Already destructed, cannot construct again");
		if (!(LifeTimeFlags & EAggregateLifeTimeFlag_Constructed))
		{
			m_fDestruct = (FAggregateDestruct *)(TCAggregate<t_CData, t_Priority, t_CLock>::fs_Destruct);
			m_Link.f_Construct();
			m_Priority = t_Priority;
			_fFunctor((void *)m_ObjectSpace);
			fg_GetModule()->f_AddAggregate((CAggregate *)this);
			m_LifeTimeFlags.f_FetchOr(EAggregateLifeTimeFlag_Constructed);
		}
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	template <typename ...tfp_CData>
	void TCAggregate<t_CData, t_Priority, t_CLock>::f_Construct(tfp_CData && ...p_Params)
	{
		DMibLockTyped(t_CLock, m_Lock);
		uint32 LifeTimeFlags = m_LifeTimeFlags.f_Load();
		DMibSafeCheck(!(LifeTimeFlags & (EAggregateLifeTimeFlag_Destructed | EAggregateLifeTimeFlag_Destructing)), "Already destructed, cannot construct again");
		if (!(LifeTimeFlags & EAggregateLifeTimeFlag_Constructed))
		{
			m_fDestruct = (FAggregateDestruct *)(TCAggregate<t_CData, t_Priority, t_CLock>::fs_Destruct);
			m_Link.f_Construct();
			m_Priority = t_Priority;
			new(m_ObjectSpace) t_CData(fg_Forward<tfp_CData>(p_Params)...);
			fg_GetModule()->f_AddAggregate((CAggregate *)this);
			m_LifeTimeFlags.f_FetchOr(EAggregateLifeTimeFlag_Constructed);
		}
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	template <typename tf_FFunctor>
	mark_nodebug inline_small t_CData *TCAggregate<t_CData, t_Priority, t_CLock>::f_CreateFunctor(tf_FFunctor const &_fFunctor)
	{
		if (!(m_LifeTimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed))
			f_ConstructFunctor(_fFunctor);

		return ((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	mark_nodebug inline_small TCAggregate<t_CData, t_Priority, t_CLock>::operator t_CData * ()
	{
		if (!(m_LifeTimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
			f_Construct();

		return ((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	mark_nodebug inline_small t_CData &TCAggregate<t_CData, t_Priority, t_CLock>::f_GetUnsafe()
	{
		return *((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	template <typename tf_CData0>
	mark_nodebug inline_small t_CData *TCAggregate<t_CData, t_Priority, t_CLock>::operator () (tf_CData0 &_Data0)
	{
		if (!(m_LifeTimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
			f_Construct(_Data0);

		return ((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	template <typename tf_CData0, typename tf_CData1>
	mark_nodebug inline_small t_CData *TCAggregate<t_CData, t_Priority, t_CLock>::operator () (tf_CData0 &_Data0, tf_CData1 &_Data1)
	{
		if (!(m_LifeTimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
			f_Construct(_Data0, _Data1);

		return ((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	template <typename tf_CData0, typename tf_CData1, typename tf_CData2>
	mark_nodebug inline_small t_CData *TCAggregate<t_CData, t_Priority, t_CLock>::operator () (tf_CData0 &_Data0, tf_CData1 &_Data1, tf_CData2 &_Data2)
	{
		if (!(m_LifeTimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
			f_Construct(_Data0, _Data1, _Data2);

		return ((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	template <typename tf_CData0, typename tf_CData1, typename tf_CData2, typename tf_CData3>
	mark_nodebug inline_small t_CData *TCAggregate<t_CData, t_Priority, t_CLock>::operator () (tf_CData0 &_Data0, tf_CData1 &_Data1, tf_CData2 &_Data2, tf_CData3 &_Data3)
	{
		if (!(m_LifeTimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
			f_Construct(_Data0, _Data1, _Data2, _Data3);

		return ((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	mark_nodebug inline_small t_CData *TCAggregate<t_CData, t_Priority, t_CLock>::operator -> ()
	{
		if (!(m_LifeTimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
			f_Construct();

		return ((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	mark_nodebug inline_small t_CData &TCAggregate<t_CData, t_Priority, t_CLock>::operator * ()
	{
		if (!(m_LifeTimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
			f_Construct();

		return *((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData, aint t_Priority, typename t_CLock>
	void TCAggregate<t_CData, t_Priority, t_CLock>::f_Clear()
	{
		DMibLockTyped(t_CLock, m_Lock);
		uint32 LifeTimeFlags = m_LifeTimeFlags.f_Load();
		DMibSafeCheck(!(LifeTimeFlags & (EAggregateLifeTimeFlag_Destructed | EAggregateLifeTimeFlag_Destructing)), "Already destructed");
		if (LifeTimeFlags & EAggregateLifeTimeFlag_Constructed)
		{
			((t_CData *)m_ObjectSpace)->~t_CData();
			fg_GetModule()->f_RemoveAggregate((CAggregate *)this);
			m_Link.f_Destruct();
			[[maybe_unused]] auto OldFlags = m_LifeTimeFlags.f_Exchange(0);
			DMibSafeCheck(!(OldFlags & (EAggregateLifeTimeFlag_Destructed | EAggregateLifeTimeFlag_Destructing)), "Already destructed, race condition");
		}
	}
}
