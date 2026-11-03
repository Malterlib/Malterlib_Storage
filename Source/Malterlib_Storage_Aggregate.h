// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Core/Core>

namespace NMib
{
	struct CSystem;
	struct CSystemModule;
	namespace NThread
	{
		template <typename t_CEvent, bool t_bAllowRecursive>
		struct TCMutualAggregate;

		using CMutualAggregate = TCMutualAggregate<CEventAutoResetAggregate, true>;
	}
}

namespace NMib::NStorage
{
	template <typename t_CData = aint>
	struct TCAggregateSimple
	{
	private:
		// Declared before the public section, which uses it.
		using CData = t_CData;

	public:
		alignas(CData) uint8 m_ObjectSpace[sizeof(CData)];

		inline_always TCAggregateSimple() = default;
		constexpr TCAggregateSimple(EAggregateInitialization _Init);

		inline_always void f_Destruct();

		template <typename ...tfp_CParam>
		inline_always void f_Construct(tfp_CParam && ...p_Params);

		inline_small operator t_CData * ();
		inline_small operator t_CData const * () const;
		inline_small t_CData *operator -> ();
		inline_small t_CData const *operator -> () const;

		/*
			inline_small t_CData & operator &()
		{
			return *((t_CData *)m_ObjectSpace);
		}*/
	};

	template <typename t_CData, aint t_Priority = 128, typename t_CLock = NThread::CLowLevelLockAggregate>
	struct TCAggregate;

	using CAggregate = TCAggregate<aint, 128, NThread::CNoLock>;

	enum EAggregateLifeTimeFlag
	{
		EAggregateLifeTimeFlag_None          = 0
		, EAggregateLifeTimeFlag_Constructed = DMibBit(0)
		, EAggregateLifeTimeFlag_Destructed  = DMibBit(1)
		, EAggregateLifeTimeFlag_Destructing = DMibBit(2)
	};

	template <typename t_CData, aint t_Priority, typename t_CLock>
	struct TCAggregate
	{
	private:
		// Declared before the public section, which uses it.
		using CData = t_CData;

	public:
		TCAggregate() = delete;
		constexpr TCAggregate(EAggregateInitialization _Init);

		using FAggregateDestruct = void (CAggregate *_pThis);

		NAtomic::TCAtomic<uint32> m_LifeTimeFlags;
		DMibListLinkDA_Link(TCAggregate, m_Link);
		aint m_Priority;

		FAggregateDestruct *m_fDestruct;

		alignas(CData) uint8 m_ObjectSpace[sizeof(CData)];

		t_CLock m_Lock;

		static void fs_Destruct(CAggregate *_pThis);

		void f_Destruct();
		void f_Clear();

		void f_Lock();
		void f_Unlock();

		bool f_IsConstructed();
		bool f_WasDestructed();

		template <typename tf_FFunctor>
		void f_ConstructFunctor(tf_FFunctor const &_fFunctor);

		template <typename ...tfp_CData>
		void f_Construct(tfp_CData && ...p_Params);

		template <typename tf_FFunctor>
		mark_nodebug inline_small t_CData *f_CreateFunctor(tf_FFunctor const &_fFunctor);

		mark_nodebug inline_small operator t_CData * ();
		mark_nodebug inline_small t_CData &f_GetUnsafe();

		template <typename tf_CData0>
		mark_nodebug inline_small t_CData *operator () (tf_CData0 &_Data0);
		template <typename tf_CData0, typename tf_CData1>
		mark_nodebug inline_small t_CData *operator () (tf_CData0 &_Data0, tf_CData1 &_Data1);
		template <typename tf_CData0, typename tf_CData1, typename tf_CData2>
		mark_nodebug inline_small t_CData *operator () (tf_CData0 &_Data0, tf_CData1 &_Data1, tf_CData2 &_Data2);
		template <typename tf_CData0, typename tf_CData1, typename tf_CData2, typename tf_CData3>
		mark_nodebug inline_small t_CData *operator () (tf_CData0 &_Data0, tf_CData1 &_Data1, tf_CData2 &_Data2, tf_CData3 &_Data3);

		mark_nodebug inline_small t_CData *operator -> ();
		mark_nodebug inline_small t_CData &operator * ();

		/*
			inline_small t_CData & operator &()
		{
			if (!(m_LifeTimeFlags.f_Load(NAtomic::gc_MemoryOrder_Acquire) & EAggregateLifeTimeFlag_Constructed))
				f_Construct();

			return *((t_CData *)m_ObjectSpace);
		}*/
	};
}

#ifndef DMibPNoShortCuts
using namespace NMib::NStorage;
#endif
