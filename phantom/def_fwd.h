#ifndef o_phantom_fwd_h__
#define o_phantom_fwd_h__



o_fwd(class, phantom, Phantom)
o_fwd(class, phantom, Message)
o_fwd(class, phantom, variant)
o_fwd(class, phantom, data)
o_fwd(struct, phantom, signal_t)

o_fwd(class, phantom, reflection, Language);
o_fwd(class, phantom, reflection, CPlusPlus);
o_fwd(class, phantom, reflection, Compiler);
o_fwd(class, phantom, reflection, Interpreter);
o_fwd(class, phantom, Module)
o_fwd(class, phantom, ModuleLoader)
o_fwd(struct, phantom, reflection, CodePosition)
o_fwd(class, phantom, reflection, CodeLocation)
o_fwd(class, phantom, reflection, SourceFile)
o_fwd(class, phantom, reflection, Signature)
o_fwd(class, phantom, reflection, Subroutine)
o_fwd(class, phantom, reflection, Block)
o_fwd(class, phantom, reflection, LocalVariable)
o_fwd(class, phantom, reflection, Function)
o_fwd(class, phantom, reflection, Addressable)
o_fwd(class, phantom, reflection, Constant)
o_fwd(class, phantom, reflection, NumericConstant)
o_fwd(class, phantom, reflection, Variable)
o_fwd(class, phantom, reflection, StaticVariable)
o_fwd(class, phantom, reflection, Member)
o_fwd(class, phantom, reflection, MemberFunction)
o_fwd(class, phantom, reflection, StaticMemberFunction)
o_fwd(class, phantom, reflection, Constructor)
o_fwd(class, phantom, reflection, InstanceMemberFunction)
o_fwd(class, phantom, reflection, Signal)
o_fwd(class, phantom, reflection, DataMember)
o_fwd(class, phantom, reflection, InstanceDataMember)
o_fwd(class, phantom, reflection, AnonymousSection)
o_fwd(class, phantom, reflection, AnonymousStruct)
o_fwd(class, phantom, reflection, AnonymousUnion)
o_fwd(class, phantom, reflection, StaticDataMember)
o_fwd(class, phantom, reflection, Property)
o_fwd(class, phantom, reflection, ValueMember)
o_fwd(class, phantom, reflection, ClassExtension)
o_fwd(class, phantom, reflection, Type)
o_fwd(class, phantom, reflection, PrimitiveType)
o_fwd(class, phantom, reflection, PointerType)
o_fwd(class, phantom, reflection, DataPointerType)
o_fwd(class, phantom, reflection, ConstType)
o_fwd(class, phantom, reflection, ReferenceType)
o_fwd(class, phantom, reflection, ArrayType)
o_fwd(class, phantom, reflection, Enum)
o_fwd(class, phantom, reflection, Class)
o_fwd(class, phantom, reflection, ClassType)
o_fwd(class, phantom, reflection, ContainerClass)
o_fwd(class, phantom, reflection, SequentialContainerClass)
o_fwd(class, phantom, reflection, MapContainerClass)
o_fwd(class, phantom, reflection, SetContainerClass)
o_fwd(class, phantom, reflection, ComponentClass)
o_fwd(class, phantom, reflection, CompositionClass)
o_fwd(class, phantom, reflection, AggregationClass)
o_fwd(class, phantom, reflection, ConstIterator)
o_fwd(class, phantom, reflection, Iterator)
o_fwd(class, phantom, reflection, PODUnion)
o_fwd(class, phantom, reflection, Structure)
o_fwd(class, phantom, reflection, Union)
o_fwd(class, phantom, reflection, LanguageElement)
o_fwd(class, phantom, reflection, TemplateElement)
o_fwd(class, phantom, reflection, Evaluable)
o_fwd(class, phantom, reflection, Statement)
o_fwd(class, phantom, reflection, LabelStatement)
o_fwd(class, phantom, reflection, BreakStatement)
o_fwd(class, phantom, reflection, ContinueStatement)
o_fwd(class, phantom, reflection, BranchIfStatement)
o_fwd(class, phantom, reflection, BranchIfNotStatement)
o_fwd(class, phantom, reflection, BranchStatement)
o_fwd(class, phantom, reflection, ReturnStatement)
o_fwd(class, phantom, reflection, ExpressionStatement)
o_fwd(class, phantom, reflection, Expression)
o_fwd(class, phantom, reflection, CallExpression)
o_fwd(class, phantom, reflection, CastExpression)
o_fwd(class, phantom, reflection, ReferenceExpression)
o_fwd(class, phantom, reflection, AddressExpression)
o_fwd(class, phantom, reflection, BinaryLogicalExpression)
o_fwd(class, phantom, reflection, VirtualMemberFunctionTable)
o_fwd(class, phantom, reflection, Namespace)
o_fwd(class, phantom, reflection, TemplateSpecialization)
o_fwd(class, phantom, reflection, Template)
o_fwd(class, phantom, reflection, Range)

o_fwd(class, phantom, state, StateMachine)
o_fwd(class, phantom, state, StateMachineElement)
o_fwd(class, phantom, state, State)
o_fwd(class, phantom, state, Track)
o_fwd(class, phantom, state, Event)
o_fwd(class, phantom, state, Reaction)
o_fwd(class, phantom, state, base_state_machine_data)

o_fwdT(class, phantom, state, native, (typename), state_machine_data)
o_fwdT(class, phantom, state, native, (typename), TNativeState)
o_fwdT(class, phantom, state, native, (typename, typename, typename, typename), TNativeTransition)
o_fwdT(class, phantom, state, native, (typename), TNativeTrack)
o_fwdT(class, phantom, state, native, (typename), TNativeStateMachine)
o_fwdT(class, phantom, state, native, (typename,bool), TNativeStateMachineHelper)

o_fwd(class, phantom, serialization, data_guid_base)
o_fwd(class, phantom, serialization, Node)
o_fwd(class, phantom, serialization, DataBase)
o_fwd(class, phantom, serialization, DataStateBase)

o_fwdT(class, phantom, reflection, native, (typename), TMapContainerClass )
o_fwdT(class, phantom, reflection, native, (typename), TSequentialContainerClass )
o_fwdT(class, phantom, reflection, native, (typename), TSetContainerClass )
o_fwdT(class, phantom, reflection, native, (typename,typename), TNativeInstanceMemberFunction0 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename), TNativeInstanceMemberFunction1 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename), TNativeInstanceMemberFunction2 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename,typename), TNativeInstanceMemberFunction3 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunction4 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunction5 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunction6 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunction7 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunction8 )

o_fwdT(class, phantom, reflection, native, (typename,typename), TNativeInstanceMemberFunctionConst0 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename), TNativeInstanceMemberFunctionConst1 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename), TNativeInstanceMemberFunctionConst2 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename,typename), TNativeInstanceMemberFunctionConst3 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunctionConst4 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunctionConst5 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunctionConst6 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunctionConst7 )
o_fwdT(class, phantom, reflection, native, (typename,typename,typename,typename,typename,typename,typename,typename,typename,typename), TNativeInstanceMemberFunctionConst8 )

o_fwdT(class, phantom, reflection, native, (typename), TNumericConstant)

o_namespace_begin(phantom, reflection, native)

template <typename, int t_TemplateNestedModifiers = 0> class TType;
template <typename, int t_TemplateNestedModifiers = 0> class TType_;

o_namespace_end(phantom, reflection, native)

o_fwdT(class, phantom, reflection, native, (typename), TPrimitiveType)
o_fwdT(class, phantom, reflection, native, (typename), TFundamentalType)
o_fwdT(class, phantom, reflection, native, (typename), TArithmeticType)
o_fwdT(class, phantom, reflection, native, (typename), TIntegralType)
o_fwdT(class, phantom, reflection, native, (typename), TFloatingPointType)
o_fwdT(class, phantom, reflection, native, (int, typename), TNativeFunction)
o_fwdT(class, phantom, reflection, native, (typename, typename), TNativeSignal)
o_fwdT(class, phantom, reflection, native, (typename, typename), TNativeInstanceMemberFunction)
o_fwdT(class, phantom, reflection, native, (typename, typename), TNativeInstanceMemberFunctionConst)
o_fwdT(class, phantom, reflection, native, (typename, typename), TNativeStaticMemberFunction)
o_fwdT(class, phantom, reflection, native, (typename, typename), TNativeInstanceDataMember)
o_fwdT(class, phantom, reflection, native, (typename, typename), TNativeStaticDataMember)
o_fwdT(class, phantom, reflection, native, (typename), TNativeVariable)

o_fwdT(class, phantom, reflection, native, (typename, uint, typename), TNativeDataMemberProvider)

#ifdef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE
o_fwdT(class, phantom, reflection, native, (typename, uint, typename, typename, typename), TNativeMemberFunctionProvider)
o_fwdT(class, phantom, reflection, native, (typename, typename, typename), TNativeSignatureProvider)
#else
o_fwdT(class, phantom, reflection, native, (typename, uint, typename), TNativeMemberFunctionProvider)
o_fwdT(class, phantom, reflection, native, (int, typename), TNativeSignatureProvider)
#endif

o_fwdT(class, phantom, state, native, (typename), root_statechart)

o_fwd(struct, phantom, reflection, Types);

o_namespace_begin(phantom, reflection, detail)

template<typename t_Ty> 
struct type_of_builder;

template<typename t_Ty, typename t_STy>
struct base_class_adder;

o_namespace_end(phantom, reflection, detail);


o_namespace_begin(phantom, detail);

template<typename t_Ty, int>
struct default_constructor_helper;

template<typename t_Ty, int>
struct default_installer_helper;

template<typename t_Ty, int>
struct default_initializer_helper;

template<typename t_Ty, int>
struct default_serializer_helper;

template<typename t_Ty, int>
struct default_resetter_helper;

o_namespace_end(phantom, detail);

o_namespace_begin(phantom)

struct empty_struct {};

template< typename >
struct constructor;

template< typename >
struct allocator;

template< typename >
struct serializer;

template< typename >
struct resetter;

template< typename >
struct initializer;

template< typename >
struct installer;

template<typename t_Ty>
struct rtti_data_registrer;

template<typename t_Ty>
struct dynamic_deleter;

template<typename t_Ty>
struct default_allocator;

template <typename t_Ty>
struct default_constructor;

template <typename t_Ty>
struct default_initializer;

template <typename t_Ty>
struct default_installer;

template <typename t_Ty>
struct default_serializer;

template <typename t_Ty>
struct default_resetter;

class dynamic_initializer_handle;

template<typename>
struct proxy_new_helper;

template<typename>
struct proxy_delete_helper;

struct dynamic_new_helper;

template<typename t_Ty>
struct dynamic_delete_helper;

template<typename t_Ty>
struct dynamic_proxy_deleter;

namespace state
{
    template<typename t_Ty>
    struct state_machine_serializer;
    template<typename t_Ty>
    struct state_machine_initializer;
    template<typename t_Ty>
    struct root_class_state_machine_serializer;
    template<typename t_Ty>
    struct state_machine_resetter;
    template<typename t_Ty>
    struct root_class_state_machine_resetter;
}

namespace reflection
{
    template<typename> 
    struct type_reflection_registrer;

    template<typename t_Ty>
    struct type_infos_of;
}

o_namespace_end(phantom)

#endif // o_phantom_fwd_h__
