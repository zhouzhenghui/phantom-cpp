
o_namespace_begin(phantom)
    
template<typename t_Ty>
void state_machine_serializer<t_Ty>::serialize(t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const * a_pDataBase)
{
    reflection::StateMachine* pStateMachine = a_pInstance->PHANTOM_CODEGEN_m_smdataptr->getStateMachine();
    reflection::State*const*    current_states  = pStateMachine->getCurrentStates(a_pInstance->PHANTOM_CODEGEN_m_smdataptr->getOwner());
    uint i = 0;
    uint count = pStateMachine->getTrackCount();
    for(;i<count;++i)
    {
        reflection::Track*  pTrack = pStateMachine->getTrack(i);
        if(pTrack->isSaved(a_uiSerializationMask))
        {
            *reinterpret_cast<uint*>(a_pOutBuffer) = (*current_states++)->getIndexInTrack();
            a_pOutBuffer += sizeof(uint);
        }
    }
}

template<typename t_Ty>
void state_machine_serializer<t_Ty>::deserialize(t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const * a_pDataBase)
{
    reflection::StateMachine* pStateMachine = a_pInstance->PHANTOM_CODEGEN_m_smdataptr->getStateMachine();
    reflection::State**    transit_states = pStateMachine->getTransitStates(a_pInstance->PHANTOM_CODEGEN_m_smdataptr->getOwner());
    uint i = 0;
    uint count = pStateMachine->getTrackCount();
    for(;i<count;++i)
    {
        reflection::Track*  pTrack = pStateMachine->getTrack(i);
        if(pTrack->isSaved(a_uiSerializationMask))
        {
            *transit_states++ = pTrack->getState(*reinterpret_cast<uint const*>(a_pInBuffer));
            a_pInBuffer += sizeof(uint);
        }
    }
}

template<typename t_Ty>
void state_machine_serializer<t_Ty>::serialize(t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) 
{ 
    reflection::StateMachine* pStateMachine = a_pInstance->PHANTOM_CODEGEN_m_smdataptr->getStateMachine();
    reflection::State*const*    current_states = pStateMachine->getCurrentStates(a_pInstance->PHANTOM_CODEGEN_m_smdataptr->getOwner());
    uint i = 0;
    uint count = pStateMachine->getTrackCount();
    for(;i<count;++i)
    {
        reflection::Track*  pTrack = pStateMachine->getTrack(i);
        if(pTrack->isSaved(a_uiSerializationMask))
        {
            reflection::State* pState = *current_states++;
            a_OutBranch.put<string>(pTrack->getName(), pState?pState->getName():"");
        }
    }
}

template<typename t_Ty>
void state_machine_serializer<t_Ty>::deserialize(t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) 
{ 
    reflection::StateMachine* pStateMachine = a_pInstance->PHANTOM_CODEGEN_m_smdataptr->getStateMachine();
    reflection::State**    transit_states = pStateMachine->getTransitStates(a_pInstance->PHANTOM_CODEGEN_m_smdataptr->getOwner());
    uint i = 0;
    uint count = pStateMachine->getTrackCount();
    for(;i<count;++i)
    {
        reflection::Track*  pTrack = pStateMachine->getTrack(i);
        if(pTrack->isSaved(a_uiSerializationMask))
        {
            const boost::optional<string>& a_opt_strStateName = a_InBranch.get_optional<string>(pTrack->getName());
            const string& a_strStateName = a_opt_strStateName.get_value_or("");
            *transit_states++ = a_strStateName.empty() ? NULL : pTrack->getState(a_strStateName);
        }
    }
}


template<typename t_Ty>
void state_machine_resetter<t_Ty>::remember(t_Ty const* a_pInstance, byte*& a_pOutBuffer)
{
    reflection::StateMachine* pStateMachine = a_pInstance->PHANTOM_CODEGEN_m_smdataptr->getStateMachine();
    reflection::State*const*    current_states  = pStateMachine->getCurrentStates(a_pInstance->PHANTOM_CODEGEN_m_smdataptr->getOwner());
    uint i = 0;
    uint count = pStateMachine->getTrackCount();
    for(;i<count;++i)
    {
        reflection::Track*  pTrack = pStateMachine->getTrack(i);
        if(pTrack->isReset())
        {
            *reinterpret_cast<uint*>(a_pOutBuffer) = (*current_states++)->getIndexInTrack();
            a_pOutBuffer += sizeof(uint);
        }
    }
}

template<typename t_Ty>
void state_machine_resetter<t_Ty>::reset(t_Ty* a_pInstance, byte const*& a_pInBuffer)
{
    reflection::StateMachine* pStateMachine = a_pInstance->PHANTOM_CODEGEN_m_smdataptr->getStateMachine();
    reflection::State**    transit_states = pStateMachine->getTransitStates(a_pInstance->PHANTOM_CODEGEN_m_smdataptr->getOwner());
    uint i = 0;
    uint count = pStateMachine->getTrackCount();
    for(;i<count;++i)
    {
        reflection::Track*  pTrack = pStateMachine->getTrack(i);
        if(pTrack->isReset())
        {
            *transit_states++ = pTrack->getState(*reinterpret_cast<uint const*>(a_pInBuffer));
            a_pInBuffer += sizeof(uint);
        }
        else
        {
            // if not savec, we reset to the initial state (the first declared in the track)
            *transit_states++ = pTrack->getInitialState();
        }
    }
}

o_forceinline void          base_state_machine_data::initialize() const 
{
    /*o_assert(thread_id == 0);
    thread_id = currentThreadId(); */
    state_machine->initialize(owner); 
}

o_forceinline void          base_state_machine_data::terminate() const 
{ 
    /*size_t threadId = currentThreadId(); 
    o_assert(threadId == thread_id);
    thread_id = 0;*/
    state_machine->terminate(owner); 
}

o_forceinline void          base_state_machine_data::update() const 
{
    /*size_t threadId = currentThreadId(); 
    o_assert(threadId == thread_id); */
    state_machine->update(owner); 
}

o_forceinline void          base_state_machine_data::reset() const 
{
    /*size_t threadId = currentThreadId(); 
    o_assert(threadId == thread_id); */
    state_machine->reset(owner); 
}

o_forceinline void          base_state_machine_data::postEvent(uint a_uiEventId) const 
{ 
    /*size_t threadId = currentThreadId(); 
    if(threadId == thread_id)
    {*/
        state_machine->postEvent(owner, a_uiEventId); 
    /*}
    else 
    {
        while(isLocked()) 
        {
            phantom::yieldCurrentThread(); 
        }
        state_machine->queueEvent(owner, a_uiEventId);
    }*/
}

o_forceinline void          base_state_machine_data::postEvent(const string& a_strEventName) const 
{ 
    /*size_t threadId = currentThreadId(); 
    if(threadId == thread_id)
    {*/
        state_machine->postEvent(owner, a_strEventName); 
    /*}
    else 
    {
        while(isLocked()) 
        {
            phantom::yieldCurrentThread(); 
        }
        state_machine->queueEvent(owner, a_uiEventId);
    }*/
}

o_namespace_end(phantom)