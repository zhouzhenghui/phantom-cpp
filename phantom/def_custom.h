/* TODO LICENCE HERE */

#ifndef o_phantom_custom_h__
#define o_phantom_custom_h__

// FEATURES activation / deactivation
#define o__bool__disable_runtime_compilation              0     /// Disable runtime compilation
#define o__int__reflection_template_use_level             1     /// All symbol resolution will be made via parsing instead of meta programming where possible (quicker compilation / slower runtime). Switch from Dynamic to Static is straightforward, opposite requires more reflection declaration such as template instances and typedefs in .cpp. 
#define o__int__bitset_bit_count                          64    /// Number of bit in a phantom::modifiers_t
#define o__bool__nedalloc                                 0     /// Uses nedmalloc
#define o__bool__use_custom_stl_contiguous_allocator      0     /// For vector and string and other contigous memory container
#define o__bool__use_custom_stl_partioned_allocator       0     /// For maps and other node based containers
#define o__bool__use_custom_default_allocator             0     /// Change the default allocator for all phantom allocated classes
#define o__bool__enable_reflection_feature                1     /// Enable type reflection generation
#define o__bool__enable_signal_connection_feature         1     /// Enable connection between objects via signals
#define o__bool__enable_nested_state_machine_feature      1     /// Enable statemachine system
#define o__bool__enable_allocation_statistics             1     /// Enable statitistics (file, line, count ...) on phantom class allocations (for stl class it wont generate any file/line information, but it's not a probleme since stl is safe)
#define o__bool__enable_serialization                     1     /// Enable serialization feature
#define o__bool__generate_member_reflection               1     /// Enable member reflection generation
#define o__bool__use_double_precision_real                0     /// The type 'real', used in maths operations will be a typedef of 'double' instead of 'float'
#define o__bool__use_double_as_default_real_type          0     /// activate : 'typedef double real;' instead of 'typedef float real;'
#define o__bool__use_kind_creation_signal                 1     /// if enabled, on each object creation, a signal will be emitted from its meta-class to notify that an instance of it's type has been created
#define o__bool__use_kind_destruction_signal              1     /// if enabled, on each object destruction, a signal will be emitted from its meta-class to notify that an instance of it's type has been destroyed
#define o__bool__use_destroyed_signal                     1     /// enable destroyed() signal emitted by each object about to be destroyed
#define o__bool__use_exceptions                           0     /// use C++ exception system to report errors    
#define o__bool__enable_state_machine_trace               1
#define o__uint__state_machine_event_queue_size           16     /// maximum event count that can be queued on a busy statemachine 
#define o__uint__max_class_size                           0xfffffff  /// set the maximum size of all phantom managed class
#define o__list__registered_associated_templates(type)    phantom::vector<type*> /// each time a class is registered, the template in the list are too


// ALLOCATION / CONSTRUCTION / INSTALLATION customization
#if o__bool__nedalloc

#   define o__func__malloc(_memsize_)                          ::nedalloc::nedmalloc(_memsize_)
#   define o__func__realloc(_ptr_,_memsize_)                   ::nedalloc::nedrealloc(_ptr_,_memsize_)
#   define o__func__free(_ptr_)                                ::nedalloc::nedfree(_ptr_)

#else 

#   define o__func__malloc(_memsize_)                          ::malloc(_memsize_)//::nedalloc::nedmalloc(_memsize_)
#   define o__func__realloc(_ptr_,_memsize_)                   ::realloc(_ptr_,_memsize_)//::nedalloc::nedrealloc(_ptr_,_memsize_)
#   define o__func__free(_ptr_)                                ::free(_ptr_)//::nedalloc::nedfree(_ptr_)

#endif

#if o__bool__use_custom_stl_contiguous_allocator 
#    define o__t1_class__contiguous_memory_allocator(...)       // to define
#else
#    define o__t1_class__contiguous_memory_allocator(...)       ::std::allocator<__VA_ARGS__>//::boost::pool_allocator<_type_, phantom::memory::malloc_free_allocator_for_boost>
#endif

#if o__bool__use_custom_stl_partioned_allocator 
#    define o__t1_class__partioned_memory_allocator(...)        // define
#else
#    define o__t1_class__partioned_memory_allocator(...)        ::std::allocator<__VA_ARGS__>//::boost::pool_allocator<_type_, phantom::memory::malloc_free_allocator_for_boost>
#endif

#if o__bool__use_custom_default_allocator
#   define o__t1_class__default_allocator(...)                 // define
#else
#   define o__t1_class__default_allocator(...)                 ::phantom::memory::malloc_free_allocator<__VA_ARGS__>//::boost::fast_pool_allocator<_type_, phantom::memory::malloc_free_allocator_for_boost>
#endif

#define o__t1_class__raii_allocator(...)                     ::boost::object_pool<__VA_ARGS__, ::phantom::memory::malloc_free_allocator_for_boost>
#define o__t1_class__slot_allocator(...)                     o__t1_class__raii_allocator(__VA_ARGS__)//o__t1_class__raii_allocator(_type_)

#define o__t1_class__default_class_allocator(...)           o__t1_class__default_allocator(__VA_ARGS__)

#define o__t1_class__default_constructor(...)               phantom::constructor<__VA_ARGS__>
#define o__t1_class__default_serializer(...)                phantom::serializer<__VA_ARGS__>
#define o__t1_class__default_installer(...)                 phantom::installer<__VA_ARGS__>
#define o__t1_class__default_initializer(...)               phantom::initializer<__VA_ARGS__>

// EXPERTS ONLY
#define o__t1_class__native_class_tag(_modifiers_)            phantom::reflection::native::native_class_default_tag_filter<_modifiers_>::tag /// Allow full native class content redefinition by partial specialization of TNativeType<t_Class, o__t1_class__native_class_tag(_modifiers_)>

#if o__int__reflection_template_use_level == 3
#pragma message("REFLECTION TEMPLATE LEVEL : 3")
#elif o__int__reflection_template_use_level == 2
#pragma message("REFLECTION TEMPLATE LEVEL : 2")
#elif o__int__reflection_template_use_level == 1
#pragma message("REFLECTION TEMPLATE LEVEL : 1")
#else
#undef o__int__reflection_template_use_level
#define o__int__reflection_template_use_level 0
#pragma message("REFLECTION TEMPLATE LEVEL : 0")
#endif

#endif // o_phantom_custom_h__