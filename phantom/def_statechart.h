#ifndef o_phantom_statechart_h__
#define o_phantom_statechart_h__



#define o_enter(name) void name##_enter(void)
#define o_update(name) void name##_update(void)
#define o_leave(name) void name##_leave(void)

#define o_statemachine_data PHANTOM_CODEGEN_m_smdataptr
#define o_statemachine_get() o_statemachine_data->getStateMachine()
#define o_statemachine_initialize() o_statemachine_data->initialize()
#define o_statemachine_terminate() o_statemachine_data->terminate()
#define o_statemachine_update() o_statemachine_data->update()
#define o_statemachine_reset() o_statemachine_data->reset()

#if o__int__reflection_template_use_level == 3
#define o_statemachine_post_2(_ptr_, _event_) (_ptr_)->o_statemachine_data->postEvent(phantom::statechart<boost::remove_const<boost::remove_pointer<boost::remove_const<decltype(_ptr_)>::type>::type>::type>::_event_::Id())
#else
#define o_statemachine_post_2(_ptr_, _event_) (_ptr_)->o_statemachine_data->postEvent(#_event_)
#endif

#define o_statemachine_post_1(_event_) o_statemachine_post_2(this, _event_)

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_statemachine_post(...) o_PP_CAT(o_PP_CAT(o_statemachine_post_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#define o_base_enter(...) o_PP_CAT(o_PP_CAT(o_base_enter_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#define o_base_update(...) o_PP_CAT(o_PP_CAT(o_base_update_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#define o_base_leave(...) o_PP_CAT(o_PP_CAT(o_base_leave_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#define o_statemachine_post(...) o_PP_CAT(o_statemachine_post_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#define o_base_enter(...) o_PP_CAT(o_base_enter_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#define o_base_update(...) o_PP_CAT(o_base_update_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#define o_base_leave(...) o_PP_CAT(o_base_leave_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#endif

#define o_base_enter_2(_class_, name)     _class_::name##_enter()
#define o_base_update_2(_class_, name)    _class_::name##_update()
#define o_base_leave_2(_class_, name)     _class_::name##_leave()

#if o__bool__enable_state_machine_trace

#define o_StateMachine_TracePostEvent(_eventid_) \
    std::cout<<console::fg_blue<<"posted "\
    <<console::fg_white<<getEventName(_eventid_)<<std::endl 

#define o_StateMachine_TraceDispatchEvent(_eventid_) \
    std::cout<<console::fg_blue<<"dispatched "\
    <<console::fg_white<<getEventName(_eventid_)<<std::endl 

# define o_StateMachine_TraceLocked() \
    std::cout<<console::fg_magenta<<"locked "\
    <<console::fg_white<<smdataptr->lock_counter<<std::endl 

#define o_StateMachine_TraceEventQueueFull(_eventid_) \
    std::cout<<console::bg_red<<console::fg_white<<"dismissed "\
    <<console::bg_black<<smdataptr->state_machine->getEventName(_eventid_)<<std::endl 

#define o_StateMachine_TraceQueued(_eventid_) \
    std::cout<<console::fg_cyan<<"queued "\
    <<console::fg_white<<smdataptr->state_machine->getEventName(_eventid_)<<std::endl 


# define o_Track_TraceEnter() \
std::cout<<console::createSpaces(getLevel())\
<<console::fg_green<<"enter "\
<<console::fg_yellow<<getName()<<std::endl 

# define o_Track_TraceLeave() \
std::cout<<console::createSpaces(getLevel())\
<<console::fg_red<<"leave "\
<<console::fg_yellow<<getName()<<std::endl 

# define o_State_TraceEnter() \
std::cout<<console::createSpaces(getLevel())\
<<console::fg_green<<"enter "\
<<console::fg_white<<getName()<<std::endl

# define o_State_TraceLeave() \
std::cout<<console::createSpaces(getLevel())\
<<console::fg_red<<"leave "\
<<console::fg_white<<getName()<<std::endl

#else
# define o_StateMachine_TracePostEvent(_event_) 
# define o_StateMachine_TraceTrackLocked(_track_index_) 
# define o_StateMachine_TraceDispatchEvent(_event_)
# define o_Track_TraceEnter()
# define o_Track_TraceLeave()
# define o_StateMachine_TraceEventQueueFull(_event_)
# define o_StateMachine_TraceQueued(_event_)
# define o_StateMachine_TraceLocked()
# define o_State_TraceEnter() 
# define o_State_TraceLeave() 
#endif

#define o_statechart_begin \
    private: \
        typedef o_global_value_Type phantom_proxy_generator_statechart_self_type;\
    o_statechart {


#define o_statechart_end \
    }; 

#define o_event(name, ...)\
    public:\
class name  \
{\
    friend class phantom::reflection::native::native_event_registrer<name>;\
    friend class phantom::reflection::Event;\
    name() {};\
public: \
    static phantom::uint Id()\
    {\
        static phantom::uint    s_id = 0xffffffff;\
        if(s_id == 0xffffffff)\
        {\
            s_id = phantom::reflection::native::TNativeStateMachine<t_PHANTOM_RESERVED_statechart_objectclass>::Instance()->getEventId(#name);\
            if(s_id == 0xffffffff)\
            {\
                s_id = phantom::reflection::native::TNativeStateMachine<t_PHANTOM_RESERVED_statechart_objectclass>::Instance()->addEvent(#name);\
            }\
        }\
        return s_id;\
    }\
};\
phantom::reflection::native::native_event_registrer<name> RESERVED_##name##_registrer;

#define o_statemachine \
    public:\
    typedef int PHANTOM_CODEGEN_smdataptr_marker; \
    const phantom::base_state_machine_data* PHANTOM_CODEGEN_m_smdataptr;\
    private:

#define o_track_counter_bis_2() __COUNTER__

#define o_track_counter_bis() o_track_counter_bis_2 o_PP_LEFT_PAREN o_PP_RIGHT_PAREN

#define o_track_counter() o_PP_CAT o_PP_LEFT_PAREN o_track_counter,_bis o_PP_RIGHT_PAREN o_PP_LEFT_PAREN  o_PP_RIGHT_PAREN

#define o_TRACK o_track
#define o_Track o_track

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   define o_track(...) o_PP_CAT(o_PP_CAT(o_track_,o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#   define o_track(...) o_PP_CAT(o_track_,o_PP_NARG(__VA_ARGS__)) (__VA_ARGS__)
#endif

#define o_track_2(name, parent)\
    o_track_4(name, parent, 0, o_save_state)

#define o_track_3(name, parent, modifiers)\
    o_track_4(name, parent, modifiers, o_save_state)

#define o_track_4(name, parent, modifiers, serialization_mask)\
    public:\
    struct phantom_proxy_generator_track_counter_marker;\
template<typename t_Ty, int t_count>\
struct phantom_proxy_generator_track_counter;\
template<typename t_Ty>\
struct phantom_proxy_generator_track_counter<t_Ty,o_track_counter()-phantom_proxy_generator_track_counter_base_value-1> { typedef t_Ty phantom_proxy_generator_track_counter_defined; };\
class name\
{\
    friend class phantom::reflection::native::native_track_registrer<name>;\
    friend class phantom::reflection::native::TNativeTrack<t_PHANTOM_RESERVED_statechart_objectclass>;\
    name() {}\
public: \
    typedef phantom::reflection::native::TNativeTrack<t_PHANTOM_RESERVED_statechart_objectclass> placeholder_type;\
    static placeholder_type* Instance()\
    {\
        static placeholder_type*    s_Instance = NULL;\
        if(s_Instance == NULL)\
        {\
            s_Instance = (placeholder_type*)phantom::reflection::native::TNativeStateMachine<t_PHANTOM_RESERVED_statechart_objectclass>::Instance()->getTrack(o_CS(#name));\
            if(s_Instance == NULL)\
            {\
                phantom::reflection::State* pParentState = parent::Instance();\
                s_Instance = o_dynamic_proxy_new(placeholder_type)(o_CS(#name), serialization_mask, modifiers);\
                pParentState->addTrack(s_Instance);\
            }\
        }\
        return s_Instance;\
    }\
};\
phantom::reflection::native::native_track_registrer<name> RESERVED_##name##_registrer;

#define o_State o_state
#define o_STATE o_state
#define o_state(name, parent, ...)\
    public:\
class name \
{\
    friend class phantom::reflection::native::native_state_registrer<name, t_PHANTOM_RESERVED_statechart_objectclass>;\
    static const phantom::character* RESERVED_get_name() { return o_CS(#name); } \
    name() {}\
public: \
    typedef phantom::reflection::native::TNativeState<t_PHANTOM_RESERVED_statechart_objectclass> placeholder_type;\
    static placeholder_type* Instance()\
    {\
        static placeholder_type*    s_Instance = NULL;\
        if(s_Instance == NULL)\
        {\
            s_Instance = (placeholder_type*)phantom::reflection::native::TNativeStateMachine<t_PHANTOM_RESERVED_statechart_objectclass>::Instance()->getState(o_CS(#name));\
            if(s_Instance == NULL)\
            {\
                phantom::reflection::Track* pParentTrack = parent::Instance();\
                s_Instance = o_dynamic_proxy_new(placeholder_type)(\
                o_CS(#name)\
                , &t_PHANTOM_RESERVED_statechart_objectclass::name##_enter\
                , &t_PHANTOM_RESERVED_statechart_objectclass::name##_update\
                , &t_PHANTOM_RESERVED_statechart_objectclass::name##_leave\
                , __LINE__\
                , phantom::detail::int_embedder<__VA_ARGS__>::value);\
                pParentTrack->addState(s_Instance);\
            }\
        }\
        return s_Instance;\
    }\
};\
phantom::reflection::native::native_state_registrer<name, t_PHANTOM_RESERVED_statechart_objectclass> RESERVED_##name##_registrer;\


#define o_Transition o_transition
#define o_TRANSITION o_transition
#define o_transition(_state_src, _event, _state_tgt)\
    phantom::reflection::native::native_transition_registrer< t_PHANTOM_RESERVED_statechart_objectclass, _state_src, _event, _state_tgt >    m_TNativeTransition_##_state_src##_event##_state_tgt;



o_namespace_begin(phantom)


template<typename t_Ty>
struct state_machine_serializer
{
    static void serialize(t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)   ;
    static void deserialize(t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)   ;
    static void serialize(t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    ;
    static void deserialize(t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    ;

    o_forceinline static void serialize(t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            serialize(reinterpret_cast<t_Ty const*>(pChunk), a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
    }
    o_forceinline static void deserialize(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            deserialize(reinterpret_cast<t_Ty*>(pChunk), a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
    }
    o_forceinline static void serialize(t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            serialize(reinterpret_cast<t_Ty const*>(pChunk), a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
    }
    o_forceinline static void deserialize(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            deserialize(reinterpret_cast<t_Ty*>(pChunk), a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
    }
};

namespace detail 
{
    template<typename t_Ty, int t_base_class_count>
    struct state_machine_initializer_helper_base
    {
        inline static void      initialize( t_Ty* a_pInstance )
        {
            state_machine_initializer_helper_base<t_Ty, t_base_class_count-1>::initialize(a_pInstance);
            state_machine_initializer<o_NESTED_TYPE base_class_of<t_Ty, t_base_class_count-1>::type>::initialize(a_pInstance);
        }
        inline static void      terminate( t_Ty* a_pInstance )
        {
            state_machine_initializer<o_NESTED_TYPE base_class_of<t_Ty, t_base_class_count-1>::type>::terminate(a_pInstance);
            state_machine_initializer_helper_base<t_Ty, t_base_class_count-1>::terminate(a_pInstance);
        }
    };
    template<typename t_Ty>
    struct state_machine_initializer_helper_base<t_Ty, 0>
    {
        inline static void      initialize( t_Ty* a_pInstance ) { }
        inline static void      terminate( t_Ty* a_pInstance ) { }
    };
    template<typename t_Ty, bool t_has_root_statechart>
    struct state_machine_initializer_helper
    {
        inline static void      initialize( t_Ty* a_pInstance )
        {
            state_machine_initializer_helper_base<t_Ty, base_class_count_of<t_Ty>::value>::initialize(a_pInstance);
            a_pInstance->PHANTOM_CODEGEN_m_smdataptr->initialize();
        }
        inline static void      terminate( t_Ty* a_pInstance )
        {
            a_pInstance->PHANTOM_CODEGEN_m_smdataptr->terminate();
            state_machine_initializer_helper_base<t_Ty, base_class_count_of<t_Ty>::value>::terminate(a_pInstance);
        }
    };
    template<typename t_Ty>
    struct state_machine_initializer_helper<t_Ty, false> 
        : public state_machine_initializer_helper_base<t_Ty, base_class_count_of<t_Ty>::value>
    {
    };
}

template<typename t_Ty, int t_base_class_count>
struct state_machine_initializer_base : public detail::state_machine_initializer_helper<t_Ty, has_root_statechart<t_Ty>::value> 
{
};

template<typename t_Ty>
struct state_machine_initializer : public detail::state_machine_initializer_helper<t_Ty, has_root_statechart<t_Ty>::value> 
{
};

template<typename t_Ty>
struct state_machine_resetter
{
    static void remember(t_Ty const* a_pInstance, byte*& a_pOutBuffer)   ;
    static void reset(t_Ty* a_pInstance, byte const*& a_pInBuffer)   ;

    o_forceinline static void remember(t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            remember(reinterpret_cast<t_Ty const*>(pChunk), a_pOutBuffer);
        }
    }
    o_forceinline static void reset(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            reset(reinterpret_cast<t_Ty*>(pChunk), a_pInBuffer);
        }
    }
    
};


namespace detail 
{
template<typename t_Ty, boolean t_is_root>
struct root_class_state_machine_serializer_helper
{
    o_forceinline static void serialize(t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) {    }
    o_forceinline static void deserialize(t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
    o_forceinline static void serialize(t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
    o_forceinline static void deserialize(t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    {    }
    o_forceinline static void serialize(t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    {    }
    o_forceinline static void deserialize(t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
    o_forceinline static void serialize(t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
    o_forceinline static void deserialize(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    {    }
};

template<typename t_Ty, boolean t_is_root>
struct root_class_state_machine_resetter_helper
{
    o_forceinline static void remember(t_Ty const* a_pInstance, byte*& a_pOutBuffer) {    }
    o_forceinline static void reset(t_Ty* a_pInstance, byte const*& a_pInBuffer)     {    }
    o_forceinline static void remember(t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)     {    }
    o_forceinline static void reset(t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)    {    }
};

template<typename t_Ty>
struct root_class_state_machine_serializer_helper<t_Ty, true> 
    : public state_machine_serializer<t_Ty>
{

};

template<typename t_Ty>
struct root_class_state_machine_resetter_helper<t_Ty, true> 
    : public state_machine_resetter<t_Ty>
{

};

}

template<typename t_Ty>
struct root_class_state_machine_serializer 
    : public detail::root_class_state_machine_serializer_helper<t_Ty
    , has_root_statechart<t_Ty>::value>
{

};

template<typename t_Ty>
struct root_class_state_machine_resetter
    : public detail::root_class_state_machine_resetter_helper<t_Ty
    , has_root_statechart<t_Ty>::value>
{

};

class base_state_machine_data
{
public:
    enum EFlag
    {
        e_Flag_Updating = 1,
        e_Flag_Dispatching = 2,
        e_Flag_Inactive = 4,
    };
    o_forceinline reflection::StateMachine* getStateMachine() const { return state_machine; }
    o_forceinline void*         getOwner() const { return owner; }
    o_forceinline void          initialize() const ;
    o_forceinline void          terminate() const ;
    o_forceinline void          update() const ;
    o_forceinline void          reset() const ;
    o_forceinline void          postEvent(uint a_uiEventId) const ;
    o_forceinline void          postEvent(const string& a_strEventName) const ;

public:
    base_state_machine_data(void* a_pOwner, reflection::StateMachine* a_pStateMachine) 
        : owner(a_pOwner)
        , state_machine(a_pStateMachine) 
        , flags(e_Flag_Inactive) 
        , lock_counter(0L)
        , event_queue_size(0)
        , thread_id(0)
    {
        memset(event_queue, 0xff, sizeof(event_queue));
    }

    o_forceinline void lock() 
    { 
        o_assert(lock_counter < UCHAR_MAX);
        lock_counter++; 
    }
    o_forceinline void unlock() 
    { 
        lock_counter--; 
        o_assert(lock_counter < UCHAR_MAX);
    }
    o_forceinline bool isLocked() const
    {
        return lock_counter != 0;
    }

protected:
    void*                   owner;
    mutable size_t          thread_id;
    reflection::StateMachine*           state_machine;
    phantom::reflection::State*  history_state;
    phantom::uint8          event_queue[o__uint__state_machine_event_queue_size];
    phantom::uint8          lock_counter;
    phantom::uint8          flags;
    phantom::uint8          event_queue_size;
};


template<typename t_ObjectClass>
class state_machine_data : public base_state_machine_data
{
public:
    template <typename, int> friend class phantom::reflection::native::TType;
    template <typename> friend struct phantom::state_machine_serializer;
    template <typename> friend struct phantom::state_machine_resetter;
    template <typename, typename, typename, typename> friend class phantom::reflection::native::TNativeTransition;
    friend class phantom::reflection::native::TNativeStateMachine<t_ObjectClass>;
    friend class phantom::reflection::native::TNativeState<t_ObjectClass>;
    friend class phantom::reflection::native::TNativeTrack<t_ObjectClass>;
    template<typename, uint> friend class default_installer_helper;
    
    typedef phantom::reflection::native::TNativeStateMachine<t_ObjectClass> state_machine_class;
    typedef phantom::reflection::native::TNativeState<t_ObjectClass> state_class;
    typedef phantom::reflection::native::TNativeTrack<t_ObjectClass> track_class;
    
public:
    state_machine_data(void* a_pBase)
    : base_state_machine_data(a_pBase, phantom::reflection::native::TNativeStateMachine<t_ObjectClass>::Instance()) 
    
    {
        memset(current_states, 0, phantom::track_count_cascade_of<t_ObjectClass>::value*sizeof(state_class*));
        memset(transit_states, 0, phantom::track_count_cascade_of<t_ObjectClass>::value*sizeof(state_class*));
    }
    
protected:
    state_class*    current_states[phantom::track_count_cascade_of<t_ObjectClass>::value];    
    state_class*    transit_states[phantom::track_count_cascade_of<t_ObjectClass>::value];
    
};

o_namespace_end(phantom)

o_namespace_begin(phantom, reflection, native)

template <typename _EventClass>
class native_event_registrer
{
public:
    native_event_registrer()
    {
        _EventClass::Id();
    }
};

template <typename t_Ty, typename t_Src, typename t_Event, typename t_Dest>
struct native_transition_registrer
{
    native_transition_registrer()
    {
        TNativeStateMachine<t_Ty>::Instance()->addTransition(t_Src::Instance(), t_Event::Id(), t_Dest::Instance());
    }
};

o_namespace_end(phantom, reflection, native)


#endif // statechart_h__
