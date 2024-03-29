/* TODO LICENCE HERE */

#ifndef state_native_TNativeStateMachine_h__
#define state_native_TNativeStateMachine_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, native)

#define TNativeStateMachine_smdataptr(_object_) ((phantom::state_machine_data<object_class>*&)(static_cast<root_object_class*>(_object_)->PHANTOM_CODEGEN_m_smdataptr))
#define TNativeStateMachine_smdataptr_const(_object_) ((phantom::state_machine_data<object_class>*)(static_cast<root_object_class const*>(_object_)->PHANTOM_CODEGEN_m_smdataptr))

template <typename t_Ty>
class TNativeStateMachine : public StateMachine
{
public:
    o_static_assert_msg(has_statechart<t_Ty>::value, "To build a state machine, the class must have a statechart declared, even empty.");

    typedef TNativeState<t_Ty>        state_class;
    typedef TNativeTrack<t_Ty>        track_class;
    typedef TNativeStateMachine<t_Ty>        self_type;
    typedef t_Ty                    object_class;
    typedef o_NESTED_TYPE first_base_statechart_class_of<t_Ty>::type        root_object_class;

    typedef state_machine_data<object_class>    instance_data;

    typedef State* t_Ty::*history_state_attribute_pointer;

    TNativeStateMachine(void) 
    {
    }
    o_destructor ~TNativeStateMachine(void)     {}

    static self_type*    Instance()
    {
        static self_type* s_Instance = NULL;
        if(s_Instance == NULL)
        {
            phantom::reflection::Class* pClass = phantom::typeOf<object_class>();
            o_assert(pClass);
            if(pClass->getStateMachine())
            {
                s_Instance = (self_type*)pClass->getStateMachine();
            }
            else
            {
                s_Instance = o_dynamic_proxy_new(self_type);
            }
        }
        return s_Instance;
    }    

    static int        NextTrackIndex() 
    {
        static int s_nextTrackIndex = 1;
        return s_nextTrackIndex++;
    }
    
    // StateMachine interface definition
    
    virtual void install(void* a_pObject) const
    {
        TNativeStateMachine_smdataptr(static_cast<object_class*>(a_pObject)) = new (o_allocate(instance_data)) instance_data(a_pObject);
    }
    
    virtual void uninstall(void* a_pObject) const
    {
        o_deallocate(
         (instance_data*)(TNativeStateMachine_smdataptr(static_cast<object_class*>(a_pObject))), instance_data
                                         );
        TNativeStateMachine_smdataptr(static_cast<object_class*>(a_pObject)) = nullptr;
    }
    
    virtual void initialize(void* a_pObject) 
    {
        instance_data* smdataptr = TNativeStateMachine_smdataptr(static_cast<object_class*>(a_pObject));
        smdataptr->flags &= ~instance_data::e_Flag_Inactive;
        smdataptr->history_state = NULL;
        static_cast<track_class*>(m_Tracks[0])->enter(smdataptr); 
    }

    virtual void update(void* a_pObject)
    {
        object_class* pObject = static_cast<object_class*>(a_pObject);
        instance_data* smdataptr = TNativeStateMachine_smdataptr(pObject);
        if(!smdataptr->isLocked())
        {
            solveQueuedTransitions(smdataptr);
        }
		smdataptr->lock();
        static_cast<track_class*>(m_Tracks[0])->update(smdataptr);
		smdataptr->unlock();
		if(!smdataptr->isLocked())
		{
			solveQueuedTransitions(smdataptr);
		}
    }

    virtual void terminate(void* a_pObject)
    {
        instance_data* smdataptr = TNativeStateMachine_smdataptr(static_cast<object_class*>(a_pObject));
        // leave root track
        static_cast<track_class*>(m_Tracks[0])->leave(smdataptr);
        smdataptr->history_state = NULL;
        smdataptr->flags |= instance_data::e_Flag_Inactive;
    }
    
    virtual void postEvent( void* a_pObject, uint a_uiEventId )
    {
        o_StateMachine_TracePostEvent(a_uiEventId);
        object_class* pObject = static_cast<object_class*>(a_pObject);
        instance_data*    smdataptr = TNativeStateMachine_smdataptr(pObject);
        queue(smdataptr, a_uiEventId);
        if(!smdataptr->isLocked())
        {
            solveQueuedTransitions(smdataptr);
        }
    }

    virtual void    queueEvent(void* a_pObject, uint a_uiEventId) 
    {
        object_class* pObject = static_cast<object_class*>(a_pObject);
        instance_data*    smdataptr = TNativeStateMachine_smdataptr(pObject);
        queue(smdataptr, a_uiEventId);
    }

    virtual State*const *   getTransitStates(void const* a_pInstance) const { return (State*const*)TNativeStateMachine_smdataptr_const(static_cast<object_class const*>(a_pInstance))->transit_states;}
    virtual State*const *   getCurrentStates(void const* a_pInstance) const { return (State*const*)TNativeStateMachine_smdataptr_const(static_cast<object_class const*>(a_pInstance))->current_states;}
    virtual State**         getTransitStates(void * a_pInstance) const { return (State**)TNativeStateMachine_smdataptr(static_cast<object_class*>(a_pInstance))->transit_states;}
    virtual State**         getCurrentStates(void * a_pInstance) const { return (State**)TNativeStateMachine_smdataptr(static_cast<object_class*>(a_pInstance))->current_states;}

    virtual State*      getCurrentState(void* a_pObject, const Track* a_pTrack) const 
    {
        return TNativeStateMachine_smdataptr_const(static_cast<object_class const*>(a_pObject))->transit_states[a_pTrack->getIndex()];
    }
    virtual State*      getTransitState(void* a_pObject, const Track* a_pTrack) const 
    {
        return TNativeStateMachine_smdataptr_const(static_cast<object_class const*>(a_pObject))->transit_states[a_pTrack->getIndex()];
    }
    
    virtual size_t  getDataPtrOffset() const 
    { 
        return ((size_t)&(static_cast<root_object_class*>(static_cast<object_class*>((void*)1))->PHANTOM_CODEGEN_m_smdataptr))-1;
    }
    
    // Internal member_functions

    void    solveQueuedTransitions(instance_data* smdataptr)
    {
        o_assert(!smdataptr->isLocked());
        for(int i = o__uint__state_machine_event_queue_size-smdataptr->event_queue_size
            ; i<o__uint__state_machine_event_queue_size; )
        {
            if(smdataptr->event_queue[i] != UCHAR_MAX)
            {
                uint8 event = smdataptr->event_queue[i];
                smdataptr->event_queue[i] = UCHAR_MAX; // clear event
                smdataptr->event_queue_size--;
                solveTransitions(smdataptr, event);
                o_assert(!smdataptr->isLocked());
                i = o__uint__state_machine_event_queue_size-smdataptr->event_queue_size; // restart from the beginning
            }
            else 
            {
                ++i; // continue
            }
        }
    }

    void    solveTransitions( instance_data* smdataptr, uint a_uiEventId )
    {
        size_t count = m_Tracks.size();
        for(size_t i = 0; i < count; ++i)
        {
            State* pCurrentState = smdataptr->current_states[i];
            if(pCurrentState != nullptr) 
            {
                State* pTransitionState = smdataptr->state_machine->getTransitionState(smdataptr->current_states[i], a_uiEventId);
                if(pTransitionState != nullptr) 
                {
                    o_StateMachine_TraceDispatchEvent(a_uiEventId);
                    static_cast<track_class*>(pTransitionState->getParentTrack())->transit(smdataptr, static_cast<state_class*>(pTransitionState));
                }
            }
        }
    }

    o_forceinline void queue(instance_data* smdataptr, uint a_uiEventId)
    {
        uint currentEventId = a_uiEventId;
        int i = o__uint__state_machine_event_queue_size;
        while(i--)
        {
            if(smdataptr->event_queue[i] == UCHAR_MAX) // free 
            {
                smdataptr->event_queue[i] = (uint8)currentEventId;
                smdataptr->event_queue_size++;
                o_StateMachine_TraceQueued(a_uiEventId);
                return;
            }
            else // occupied by another event for this track
            {
                uint event = smdataptr->event_queue[i];
                smdataptr->event_queue[i] = currentEventId; // clear event
                currentEventId = event;
            }
        }
        o_StateMachine_TraceQueued(a_uiEventId);
        o_StateMachine_TraceEventQueueFull(currentEventId);
    }
    
    template<typename t_EventTy>
    o_forceinline
        void            postEvent(t_Ty* a_pObject) 
    {
        postEvent(a_pObject, t_EventTy::Id());
    }

    base_state_machine_data* getInstanceData(void* a_pInstance) const
    {
        return getInstanceData(static_cast<object_class*>(a_pInstance));
    }

    instance_data* getInstanceData(object_class const* a_pInstance)
    {
        return static_cast<instance_data*>(a_pInstance->PHANTOM_CODEGEN_m_smdataptr); 
    }

protected:
    
    void addTrack(Track* a_pTrack)
    {
        o_assert(m_Tracks[0] == NULL); 
        setRootTrack(a_pTrack);
    }

protected:
    
};


#undef TNativeStateMachine_smdataptr
#undef TNativeStateMachine_smdataptr_const

o_namespace_end(phantom, reflection, native)

#endif
