// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

namespace NMib
{
	class CSystem;
	class CSystemModule;
	namespace NThread
	{
		template <typename t_CEvent, bool t_bAllowRecursive>
		class TCMutualAggregate;

		using CMutualAggregate = TCMutualAggregate<CEventAutoResetAggregate, true>;
	}
}

namespace NMib::NStorage
{
	template <typename t_CData = aint>
	class TCAggregateSimple
	{
		using CData = t_CData;

	public:

		alignas(CData) uint8 m_ObjectSpace[sizeof(CData)];

		inline_always TCAggregateSimple() = default;
		constexpr TCAggregateSimple(EAggregateInitialization _Init)
			: m_ObjectSpace{}
		{
		}

		inline_always void f_Destruct()
		{
			((t_CData *)m_ObjectSpace)->t_CData::~t_CData();
		}

		template <typename ...tfp_CParam>
		inline_always void f_Construct(tfp_CParam && ...p_Params)
		{
			new(m_ObjectSpace) t_CData(fg_Forward<tfp_CParam>(p_Params)...);
		}

		inline_small operator t_CData *()
		{
			return ((t_CData *)m_ObjectSpace);
		}

		inline_small operator t_CData const *() const
		{
			return ((t_CData *)m_ObjectSpace);
		}

		inline_small t_CData * operator ->()
		{
			return ((t_CData *)m_ObjectSpace);
		}

		inline_small t_CData const * operator ->() const
		{
			return ((t_CData const *)m_ObjectSpace);
		}

/*			inline_small t_CData & operator &()
		{
			return *((t_CData *)m_ObjectSpace);
		}*/
	};

	template <typename t_CData, aint t_Priority = 128, typename t_CLock = NThread::CLowLevelLockAggregate>
	class TCAggregate;

	using CAggregate = TCAggregate<aint, 128, NThread::CNoLock>;

	enum EAggregateLifeTimeFlag
	{
		EAggregateLifeTimeFlag_None = 0
		, EAggregateLifeTimeFlag_Constructed = DMibBit(0)
		, EAggregateLifeTimeFlag_Destructed = DMibBit(1)
		, EAggregateLifeTimeFlag_Destructing = DMibBit(2)
	};

	template <typename t_CData, aint t_Priority, typename t_CLock>
	class TCAggregate
	{
		using CData = t_CData;

	public:
		TCAggregate() = delete;
		constexpr TCAggregate(EAggregateInitialization _Init)
			: m_LifeTimeFlags{0}
			, m_Link{_Init}
			, m_Priority{0}
			, m_fDestruct{nullptr}
			, m_ObjectSpace{}
			, m_Lock{}
		{
		}

		using FAggregateDestruct = void (CAggregate *_pThis);

		NAtomic::TCAtomic<uint32> m_LifeTimeFlags;
		DMibListLinkDA_Link(TCAggregate, m_Link);
		aint m_Priority;

		FAggregateDestruct *m_fDestruct;

		alignas(CData) uint8 m_ObjectSpace[sizeof(CData)];

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

		bool f_IsConstructed()
		{
			return m_LifeTimeFlags.f_Load(NAtomic::EMemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed;
		}

		bool f_WasDestructed()
		{
			return (m_LifeTimeFlags.f_Load(NAtomic::EMemoryOrder_Acquire) & (EAggregateLifeTimeFlag_Destructed | EAggregateLifeTimeFlag_Destructing)) != EAggregateLifeTimeFlag_None;
		}

		template <typename tf_CFunctor>
		void f_ConstructFunctor(tf_CFunctor const &_fFunctor);

		template <typename... tfp_CData>
		void f_Construct(tfp_CData && ... p_Params);

		template <typename tf_CFunctor>
		mark_nodebug inline_small t_CData * f_CreateFunctor(tf_CFunctor const &_fFunctor)
		{
			if (!(m_LifeTimeFlags.f_Load(NAtomic::EMemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed))
			{
				f_ConstructFunctor(_fFunctor);
			}

			return ((t_CData *)m_ObjectSpace);
		}

		mark_nodebug inline_small operator t_CData *()
		{
			if (!(m_LifeTimeFlags.f_Load(NAtomic::EMemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
				f_Construct();

			return ((t_CData *)m_ObjectSpace);
		}

		mark_nodebug inline_small t_CData &f_GetUnsafe()
		{
			return *((t_CData *)m_ObjectSpace);
		}

		template <typename tf_CData0>
		mark_nodebug inline_small t_CData * operator() (tf_CData0 &_Data0)
		{
			if (!(m_LifeTimeFlags.f_Load(NAtomic::EMemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
				f_Construct(_Data0);

			return ((t_CData *)m_ObjectSpace);
		}

		template <typename tf_CData0, typename tf_CData1>
		mark_nodebug inline_small t_CData * operator() (tf_CData0 &_Data0, tf_CData1 &_Data1)
		{
			if (!(m_LifeTimeFlags.f_Load(NAtomic::EMemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
				f_Construct(_Data0, _Data1);

			return ((t_CData *)m_ObjectSpace);
		}

		template <typename tf_CData0, typename tf_CData1, typename tf_CData2>
		mark_nodebug inline_small t_CData * operator() (tf_CData0 &_Data0, tf_CData1 &_Data1, tf_CData2 &_Data2)
		{
			if (!(m_LifeTimeFlags.f_Load(NAtomic::EMemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
				f_Construct(_Data0, _Data1, _Data2);

			return ((t_CData *)m_ObjectSpace);
		}

		template <typename tf_CData0, typename tf_CData1, typename tf_CData2, typename tf_CData3>
		mark_nodebug inline_small t_CData * operator() (tf_CData0 &_Data0, tf_CData1 &_Data1, tf_CData2 &_Data2, tf_CData3 &_Data3)
		{
			if (!(m_LifeTimeFlags.f_Load(NAtomic::EMemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
				f_Construct(_Data0, _Data1, _Data2, _Data3);

			return ((t_CData *)m_ObjectSpace);
		}

		mark_nodebug inline_small t_CData * operator ->()
		{
			if (!(m_LifeTimeFlags.f_Load(NAtomic::EMemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
				f_Construct();

			return ((t_CData *)m_ObjectSpace);
		}

		mark_nodebug inline_small t_CData & operator *()
		{
			if (!(m_LifeTimeFlags.f_Load(NAtomic::EMemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed)) [[unlikely]]
				f_Construct();

			return *((t_CData *)m_ObjectSpace);
		}

/*			inline_small t_CData & operator &()
		{
			if (!(m_LifeTimeFlags.f_Load(NAtomic::EMemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed))
				f_Construct();

			return *((t_CData *)m_ObjectSpace);
		}*/
	};
}

#ifndef DMibPNoShortCuts
	using namespace NMib::NStorage;
#endif
