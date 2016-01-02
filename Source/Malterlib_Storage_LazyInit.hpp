namespace NMib
{
	namespace NStorage
	{
		template <typename t_CData, typename t_CLock>
		template <typename... tfp_CData>
		void TCLazyInit<t_CData, t_CLock>::fp_Construct(tfp_CData && ... p_Params)
		{
			DMibLockTyped(t_CLock, m_Lock);
			DMibSafeCheck(!m_bDestructed, "Already destructed, cannot construct again");
			if (!m_bConstructed)
			{
				new(m_ObjectSpace.m_Aligned) t_CData(fg_Forward<tfp_CData>(p_Params)...);
				NMib::NAtomic::fg_MemoryFence(NAtomic::EMemoryOrder_Release);
				m_bConstructed = true;
			}
		}

		template <typename t_CData, typename t_CLock>
		TCLazyInit<t_CData, t_CLock>::TCLazyInit()
			: m_bConstructed(false)
			, m_bDestructed(false)
		{
		}

		template <typename t_CData, typename t_CLock>
		TCLazyInit<t_CData, t_CLock>::~TCLazyInit()
		{
			if (m_bConstructed && !m_bDestructed)
			{
				DMibSafeCheck(m_bConstructed && !m_bDestructed, "Should not arrive here unless we are constructed");
				m_bDestructed = true;
				((t_CData *)m_ObjectSpace.m_Aligned)->~t_CData();
				NMib::NAtomic::fg_MemoryFence(NAtomic::EMemoryOrder_Release);
				m_bConstructed = false;
			}
		}

		template <typename t_CData, typename t_CLock>
		template <typename ...tfp_CParam>
		inline_small t_CData *TCLazyInit<t_CData, t_CLock>::operator() (tfp_CParam && ...p_Param)
		{
			NAtomic::fg_MemoryFence(NAtomic::EMemoryOrder_Acquire);
			if (!m_bConstructed)
				fp_Construct(fg_Forward<tfp_CParam>(p_Param)...);

			return ((t_CData *)m_ObjectSpace.m_Aligned);
		}

		template <typename t_CData, typename t_CLock>
		inline_small t_CData *TCLazyInit<t_CData, t_CLock>::operator ->()
		{
			NAtomic::fg_MemoryFence(NAtomic::EMemoryOrder_Acquire);
			if (!m_bConstructed)
				fp_Construct();

			return ((t_CData *)m_ObjectSpace.m_Aligned);
		}

		template <typename t_CData, typename t_CLock>
		inline_small t_CData &TCLazyInit<t_CData, t_CLock>::operator *()
		{
			NAtomic::fg_MemoryFence(NAtomic::EMemoryOrder_Acquire);
			if (!m_bConstructed)
				fp_Construct();

			return *((t_CData *)m_ObjectSpace.m_Aligned);
		}
	}
}
