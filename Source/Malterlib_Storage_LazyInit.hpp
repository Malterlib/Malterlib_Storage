namespace NMib::NStorage
{
	template <typename t_CData, typename t_CLock>
	template <typename... tfp_CData>
	void TCLazyInit<t_CData, t_CLock>::fp_Construct(tfp_CData && ... p_Params)
	{
		DMibLockTyped(t_CLock, m_Lock);
		uint32 OldFlags = m_LifetimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire);

		DMibSafeCheck(!(OldFlags & uint32(ELifetimeFlag_Destructed)), "Already destructed, cannot construct again");

		if (!(OldFlags & uint32(ELifetimeFlag_Constructed)))
		{
			new(m_ObjectSpace) t_CData(fg_Forward<tfp_CData>(p_Params)...);
			OldFlags = m_LifetimeFlags.f_FetchOr(uint32(ELifetimeFlag_Constructed), NAtomic::gc_MemoryOrder_Release);
			DMibSafeCheck(!(OldFlags & uint32(ELifetimeFlag_Destructed)), "Already destructed, cannot construct again");
		}
	}

	template <typename t_CData, typename t_CLock>
	constexpr TCLazyInit<t_CData, t_CLock>::TCLazyInit()
	{
	}

	template <typename t_CData, typename t_CLock>
	TCLazyInit<t_CData, t_CLock>::~TCLazyInit()
	{
		uint32 LifetimeFlags = m_LifetimeFlags.f_FetchOr(uint32(ELifetimeFlag_Destructed));
		if ((LifetimeFlags & uint32(ELifetimeFlag_Constructed)) && !(LifetimeFlags & uint32(ELifetimeFlag_Destructed)))
		{
			((t_CData *)m_ObjectSpace)->~t_CData();

			m_LifetimeFlags.f_FetchAnd(~uint32(ELifetimeFlag_Constructed), NAtomic::gc_MemoryOrder_Release);
		}
	}

	template <typename t_CData, typename t_CLock>
	template <typename ...tfp_CParam>
	inline_small t_CData &TCLazyInit<t_CData, t_CLock>::operator() (tfp_CParam && ...p_Param)
	{
		if (!(m_LifetimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & uint32(ELifetimeFlag_Constructed)))
			fp_Construct(fg_Forward<tfp_CParam>(p_Param)...);

		return *((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData, typename t_CLock>
	inline_small t_CData *TCLazyInit<t_CData, t_CLock>::operator ->()
	{
		if (!(m_LifetimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & uint32(ELifetimeFlag_Constructed)))
			fp_Construct();

		return ((t_CData *)m_ObjectSpace);
	}

	template <typename t_CData, typename t_CLock>
	inline_small t_CData &TCLazyInit<t_CData, t_CLock>::operator *()
	{
		if (!(m_LifetimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & uint32(ELifetimeFlag_Constructed)))
			fp_Construct();

		return *((t_CData *)m_ObjectSpace);
	}
}
