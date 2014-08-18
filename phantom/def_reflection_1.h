
#define o_attribute(_name_, _variant_)\
    class o_PP_CAT(attribute,__LINE__) \
    {\
        friend class enclosed_reflection;\
        o_PP_CAT(attribute,__LINE__)()\
        {\
            phantom::reflection::Types::currentInstalledClass->addAttribute(_name_, _variant_);\
        }\
    } o_PP_CAT(o_PP_CAT(attribute,__LINE__), _instance);

#define o_property_8(_type_, _name_, _set_member_function_, _get_member_function_, _signal_, _range_, _modifiers_, _serialization_mask_)\
    o_static_assert_msg( (((_modifiers_&o_transient) == 0) OR (_serialization_mask_ == 0)), "if transient, property must have a null serialization mask" );\
class o_PP_CAT(_name_,__LINE__) \
    {\
    friend class enclosed_reflection;\
    enum {_name_};\
    o_PP_CAT(_name_,__LINE__)()\
        {\
        auto pGetMemberFunction = phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,((_modifiers_&o_public)==o_public)?o_public:o_protected,_type_ ()>::CreateMemberFunction( \
        o_PP_QUOTE(_get_member_function_) \
        , phantom::reflection::Signature::Create(o_PP_QUOTE(_type_)"()", phantom::reflection::Types::currentInstalledTemplateSpecialization, phantom::reflection::Types::currentInstalledClass) \
        , &phantom_proxy_generator_reflection_proxy_type::_get_member_function_ \
        ,((_modifiers_&o_public)==o_public)?o_public:o_protected);\
        pGetMemberFunction->asLanguageElement()->addCodeLocation(phantom::sourceFile(__FILE__));\
        phantom::reflection::Types::currentInstalledClass->addMemberFunction(pGetMemberFunction);\
        auto pSetMemberFunction = phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,phantom::detail::int_embedder<__VA_ARGS__>::value|o_slot_member_function,void (_type_)>::CreateMemberFunction( \
        o_PP_QUOTE(_set_member_function_) \
        , phantom::reflection::Signature::Create("void" o_PP_QUOTE((_type_)), phantom::reflection::Types::currentInstalledTemplateSpecialization, phantom::reflection::Types::currentInstalledClass) \
        , &phantom_proxy_generator_reflection_proxy_type::_set_member_function_ \
        ,(((_modifiers_&o_public)==o_public)?o_public:o_protected)|o_slot_member_function);\
        pSetMemberFunction->asLanguageElement()->addCodeLocation(phantom::sourceFile(__FILE__));\
        phantom::reflection::Types::currentInstalledClass->addMemberFunction(pSetMemberFunction);\
        phantom::reflection::Type* pType = phantom::typeByName(o_PP_QUOTE(_type_), phantom::reflection::Types::currentInstalledClass);\
        o_assert(pType, o_PP_QUOTE(_type_)" type not registered");\
        phantom::reflection::Signal* pSignal = phantom::reflection::native::DynamicNativePropertySignalProvider<phantom_proxy_generator_reflection_self_type, _type_>::CreateSignal(\
        o_PP_QUOTE(_signal_)\
        , o_PP_QUOTE(_type_)\
        , phantom::reflection::Types::currentInstalledTemplateSpecialization\
        , phantom::reflection::Types::currentInstalledClass\
        , &phantom_proxy_generator_reflection_proxy_type::_signal_\
        , &phantom_proxy_generator_reflection_proxy_type::PHANTOM_CODEGEN_m_slot_list_of_##_signal_\
        );\
        phantom::reflection::ValueMember* pValueMember = o_dynamic_proxy_new(phantom::reflection::Property, phantom::reflection::Property::metaType,\
        phantom::reflection::native::TNativeProperty<\
        phantom_proxy_generator_reflection_self_type, _type_>) \
        ( o_PP_QUOTE(_name_)\
        , pType\
        , pSetMemberFunction->asInstanceMemberFunction()\
        , pGetMemberFunction->asInstanceMemberFunction()\
        , pSignal\
        , o_range _range_\
        , &phantom_proxy_generator_reflection_proxy_type::_set_member_function_\
        , &phantom_proxy_generator_reflection_proxy_type::_get_member_function_\
        , _serialization_mask_\
        , _modifiers_\
        );\
        pValueMember->addCodeLocation(phantom::sourceFile(__FILE__));\
        phantom::reflection::Types::currentInstalledClass->addValueMember(pValueMember);\
        }\
    } o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);


/// COLLECTIONS

#define o_collection_9(_type_, _name_, _add_member_function_, _remove_member_function_, _move_member_function_, _set_member_function_, _get_member_function_, _size_member_function_, _modifiers_)\
class o_PP_CAT(_name_,__LINE__) \
    {\
    friend class enclosed_reflection;\
    enum {_name_};\
    o_PP_CAT(_name_,__LINE__)()\
    {\
    phantom::reflection::Type* pType = phantom::typeByName(o_PP_QUOTE(_type_),phantom::reflection::Types::currentInstalledClass);\
    o_assert(pType, o_PP_QUOTE(_type_)" type not registered");\
    phantom::reflection::Collection* pCollection = o_proxy_new(phantom::reflection::Collection,\
    phantom::reflection::native::TNativeCollection<\
    phantom_proxy_generator_reflection_self_type, _type_>) \
    ( o_PP_QUOTE(_name_)\
    , pType\
    , &phantom_proxy_generator_reflection_proxy_type::_add_member_function_\
    , &phantom_proxy_generator_reflection_proxy_type::_remove_member_function_\
    , &phantom_proxy_generator_reflection_proxy_type::_move_member_function_\
    , &phantom_proxy_generator_reflection_proxy_type::_set_member_function_\
    , &phantom_proxy_generator_reflection_proxy_type::_get_member_function_\
    , &phantom_proxy_generator_reflection_proxy_type::_size_member_function_\
    , _modifiers_\
    );\
    pCollection->addCodeLocation(phantom::sourceFile(__FILE__));\
    phantom::reflection::Types::currentInstalledClass->addCollection(pCollection);\
    }\
} o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);


#define o_extension(_extension_class_, ...) \
class o_PP_CAT(_name_,__LINE__) \
    {\
    friend class enclosed_reflection;\
    o_PP_CAT(_name_,__LINE__)()\
        {\
        phantom::reflection::Types::currentInstalledClass->addExtension(o_new(_extension_class_)(phantom::detail::int_embedder<__VA_ARGS__>::value));\
        }\
    } o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);


#    define o_signal(_name_, _parameterslist_, ...) \
class o_PP_CAT(_name_,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(_name_,__LINE__)() \
            {\
            phantom::reflection::Signal* pSignal = o_dynamic_proxy_new(phantom::reflection::Signal,phantom::reflection::Signal::metaType,\
            phantom::reflection::native::TNativeSignal<\
            phantom_proxy_generator_reflection_self_type\
            , phantom::signal_t _parameterslist_>) \
            ( o_PP_QUOTE(_name_)\
            , phantom::reflection::Signature::Create(\
            "phantom::signal_t" o_PP_QUOTE(_parameterslist_)\
            , phantom::reflection::Types::currentInstalledTemplateSpecialization\
            , phantom::reflection::Types::currentInstalledClass\
            )\
            , &phantom_proxy_generator_reflection_proxy_type::_name_\
            , &phantom_proxy_generator_reflection_proxy_type::PHANTOM_CODEGEN_m_slot_list_of_##_name_\
            , phantom::detail::int_embedder< __VA_ARGS__ >::value\
            );\
            pSignal->addCodeLocation(phantom::sourceFile(__FILE__));\
            o_assert(phantom::reflection::Types::currentInstalledClass->asClass(), "Cannot add signal to pod class");\
            phantom::reflection::Types::currentInstalledClass->asClass()->addSignal(pSignal);\
            }\
        } o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);


#    define o_data_member_5(_type_, _name_, _range_, _modifiers_, _serialization_mask_) \
    o_static_assert_msg( ((((_modifiers_)&o_transient) == 0) OR (_serialization_mask_ == 0)), "if transient, data member must have a null serialization mask" );\
    class o_PP_CAT(_name_,__LINE__)\
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(_name_,__LINE__)()\
            {\
            phantom::reflection::Type* pType = phantom::typeByName(o_PP_QUOTE(_type_),phantom::reflection::Types::currentInstalledClass);\
            o_assert(pType, o_PP_QUOTE(_type_)" type not registered");\
            if(pType == nullptr) { \
            o_exception(phantom::exception::t_unknown_reflection_type_exception<_type_> \
            , "dataMember type "#_type_" (or its pointed type if it's a pointer type) must be declared previously with the macro o_declare provided by phantom so that it can be considered as a phantom type"); \
            }\
            pType->addReferenceCodeLocation(phantom::sourceFile(__FILE__));\
            auto pDataMember = phantom::reflection::native::TNativeDataMemberProvider< phantom_proxy_generator_reflection_self_type, _modifiers_, _type_ >::CreateDataMember(o_PP_QUOTE(_name_), pType, &phantom_proxy_generator_reflection_proxy_type::_name_, o_range _range_, _serialization_mask_, _modifiers_);\
            pDataMember->asLanguageElement()->addCodeLocation(phantom::sourceFile(__FILE__));\
            phantom::reflection::Types::currentInstalledClass->addDataMember(pDataMember);\
            }\
        } o_PP_CAT(o_PP_CAT(_name_,__LINE__),_instance);


#    define o_member_function(_returntype_, _name_, _parameterslist_, ...) \
class o_PP_CAT(member_function,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(member_function,__LINE__)() \
            {\
            auto pMemberFunction = phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,phantom::detail::int_embedder<__VA_ARGS__>::value,_returntype_ _parameterslist_>::CreateMemberFunction( \
            o_PP_QUOTE(_name_) \
            , phantom::reflection::Signature::Create(o_PP_QUOTE(_returntype_) "" o_PP_QUOTE(_parameterslist_), phantom::reflection::Types::currentInstalledTemplateSpecialization, phantom::reflection::Types::currentInstalledClass) \
            , &phantom_proxy_generator_reflection_proxy_type::_name_ \
            ,phantom::detail::int_embedder<__VA_ARGS__>::value);\
            pMemberFunction->asLanguageElement()->addCodeLocation(phantom::sourceFile(__FILE__));\
            phantom::reflection::Types::currentInstalledClass->addMemberFunction(pMemberFunction);\
            }\
        } o_PP_CAT(member_function,__LINE__);

#    define o_slot(_returntype_, _name_, _parameterslist_, ...) \
class o_PP_CAT(slot,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(slot,__LINE__)() \
            {\
            auto pMemberFunction = phantom::reflection::native::TNativeMemberFunctionProvider<phantom_proxy_generator_reflection_self_type,phantom::detail::int_embedder<__VA_ARGS__>::value|o_slot_member_function,_returntype_ _parameterslist_>::CreateMemberFunction( \
            o_PP_QUOTE(_name_) \
            , phantom::reflection::Signature::Create(o_PP_QUOTE(_returntype_) "" o_PP_QUOTE(_parameterslist_), phantom::reflection::Types::currentInstalledTemplateSpecialization, phantom::reflection::Types::currentInstalledClass) \
            , &phantom_proxy_generator_reflection_proxy_type::_name_ \
            ,phantom::detail::int_embedder<__VA_ARGS__>::value|o_slot_member_function);\
            pMemberFunction->asLanguageElement()->addCodeLocation(phantom::sourceFile(__FILE__));\
            phantom::reflection::Types::currentInstalledClass->addMemberFunction(pMemberFunction);\
            }\
        } o_PP_CAT(slot,__LINE__);

#    define o_constructor(_parameterslist_, ...) \
class o_PP_CAT(o_global_value_Type,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(o_global_value_Type,__LINE__)() \
            {\
            auto pConstructor = o_proxy_new(phantom::reflection::Constructor, phantom::reflection::native::TNativeConstructor<phantom_proxy_generator_reflection_self_type _parameterslist_>)(phantom::reflection::Types::currentInstalledClass->getName(), phantom::reflection::Signature::Create("void" o_PP_QUOTE(_parameterslist_), phantom::reflection::Types::currentInstalledTemplateSpecialization),phantom::detail::int_embedder<__VA_ARGS__>::value);\
            pConstructor->addCodeLocation(phantom::sourceFile(__FILE__));\
            phantom::reflection::Types::currentInstalledClass->addConstructor(pConstructor);\
            }\
        } o_PP_CAT(o_PP_CAT(constructor,__LINE__),_instance);


#define o_nested_typedef_1(name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::reflection::detail::type_of_counter<name, PHANTOM_CODEGEN_reflection_counter_value>::object());\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_nested_typedef_2(part0, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_nested_typedef_3(part0, part1, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0 #part1, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_nested_typedef_4(part0, part1, part2, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0 #part1 #part2, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_nested_typedef_5(part0, part1, part2, part3, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0 #part1 #part2 #part3, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_nested_typedef_6(part0, part1, part2, part3, part4, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0 #part1 #part2 #part3 #part4, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_default_template_argument_type(parameter, ...)\
class o_PP_CAT(parameter,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(parameter,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledTemplateSpecialization->setDefaultArgument(#parameter, phantom::reflection::detail::type_of_counter<__VA_ARGS__, PHANTOM_CODEGEN_reflection_counter_value>::object());\
            }\
        } o_PP_CAT(parameter,__LINE__);
/*

#define o_nested_typedef_2(part0, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_nested_typedef_3(part0, part1, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0","#part1, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_nested_typedef_4(part0, part1, part2, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0","#part1","#part2, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_nested_typedef_5(part0, part1, part2, part3, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0","#part1","#part2","#part3, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_nested_typedef_6(part0, part1, part2, part3, part4, name)\
class o_PP_CAT(name,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(name,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledClass->addNestedTypedef(#name, phantom::typeByName(#part0","#part1","#part2","#part3","#part4, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(name,__LINE__);

#define o_default_template_argument_type(parameter, ...)\
class o_PP_CAT(parameter,__LINE__) \
        {\
        friend class enclosed_reflection;\
        o_PP_CAT(parameter,__LINE__)() \
            {\
            phantom::reflection::Types::currentInstalledTemplateSpecialization->setDefaultArgument(#parameter, phantom::typeByName(#__VA_ARGS__, phantom::reflection::Types::currentInstalledClass));\
            }\
        } o_PP_CAT(parameter,__LINE__);
        */

#define o_function(_returntype_, _name_, _parameters_, ...) \
    static phantom::reflection::function_registrer<_returntype_ _parameters_>  o_PP_CAT(g_reflection_function_registration_##_name_, __COUNTER__)(#_name_, o_PP_QUOTE(_returntype_)o_PP_QUOTE(_parameters_),_name_,##__VA_ARGS__);

#define o_functionN(_namespace_, _returntype_, _name_, _parameters_, ...) \
    static phantom::reflection::function_registrer<_returntype_ _parameters_>  o_PP_CAT o_PP_LEFT_PAREN o_PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_namespace_, _name_), __COUNTER__ o_PP_RIGHT_PAREN (o_PP_QUOTE o_PP_LEFT_PAREN o_PP_CREATE_SCOPE _namespace_ o_PP_RIGHT_PAREN , #_name_, o_PP_QUOTE(_returntype_)o_PP_QUOTE(_parameters_), o_PP_CREATE_QUALIFIED_NAME(_namespace_, _name_),##__VA_ARGS__);
