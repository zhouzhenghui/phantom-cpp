/*
    This file is part of PHANTOM
         P reprocessed
         H igh-level
         A llocator
         N ested state-machines and
         T emplate
         O riented
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/



#ifndef o_phantom_Phantom_h__
#define o_phantom_Phantom_h__

// ********************************************************************* //
// ******************************************************************* ///
// **************************** PREREQUISITES ************************** //
// ******************************************************************* ///
// ********************************************************************* //
#ifndef DOXYGEN_SRC_PREPROCESSING

#define _CRT_SECURE_NO_WARNINGS 1

/* ************** PHANTOM CONFIGURATION *********** */
#include "phantom/def_config.h"
#include "phantom/def_custom.h"
/* ************* UNIVERSAL PREDEFINITION ********** */
#ifdef _UNICODE
#    ifndef UNICODE
#        define UNICODE
#    endif
#elif defined(UNICODE)
#    define _UNICODE
#endif

#ifdef _DEBUG
#    ifndef DEBUG
#        define DEBUG
#    endif
#elif defined(DEBUG)
#    define _DEBUG
#endif

/* ******************* NEDMALLOC ****************** */
#if o__bool__nedalloc
#    include <phantom/memory/nedmalloc.h>
#endif
/* ********************** STD ********************* */

#if (o_COMPILER == o_COMPILER_GCC)
#include <inttypes.h>
#include <stdlib.h>
#include <stdarg.h>
#endif

#if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS)
#    include <conio.h>
#endif

#include <assert.h>
#include <stdio.h>
#include <cstdio>

#include <iostream>
#include <memory>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>
#include <set>
#if o_HAS_CPP0X
#   include <unordered_set>
#   include <unordered_map>
#else
#   include <tr1/unordered_set>
#   include <tr1/unordered_map>
#endif
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <vector>
#include <limits>
#include <algorithm>
/* ********************* BOOST ******************** */
#if !defined(Q_MOC_RUN)
#include <boost/foreach.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/type_traits.hpp>
#include <boost/lexical_cast.hpp>
#if o__bool__enable_serialization
#   if o__bool__use_custom_stl_partioned_allocator
#      include <boost/property_tree_custom/ptree.hpp>
#   else
#      include <boost/property_tree/ptree.hpp>
#   endif
#endif
#endif // Q_MOC_RUN

/* ***************** FASTDELEGATE ***************** */
#include <fastdelegate/FastDelegate.h>
#include <fastdelegate/FastDelegateBind.h>
/* *************** END DEPENDENCIES *************** */
#else
#include "phantom/def_custom.h"
#endif

/* ******************** PHANTOM ******************* */
#include "phantom/def_macros.h"
#include "phantom/def_alias.h"
#include "phantom/def_export.h"
#include "phantom/def_console.h"
#include "phantom/def_memory.h"
#include "phantom/def_types.h"
#include "phantom/def_fwd.h"
#include "phantom/def_counter.h"
#include "phantom/def_traits.h"
#include "phantom/def_container.h"
#include "phantom/def_exceptions.h"

o_namespace_begin(phantom)

o_export void       assertion BOOST_PREVENT_MACRO_SUBSTITUTION ( const character* e, const character* m , const char* f , uint l);
o_export void       warning BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);
o_export void       error BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);
o_export void       log BOOST_PREVENT_MACRO_SUBSTITUTION (int level, const char* file, uint line, const char* message, ...);

template <typename t_Ty>
o_forceinline string                            typeNameOf();

o_namespace_end(phantom)

#include "phantom/def_helpers.h"

o_namespace_begin(phantom)

struct PIMPL;

namespace util {}

namespace detail
{
    class dynamic_initializer_handle;
    template<typename t_Ty>
    struct module_installer;
    template<typename t_Ty>
    struct module_installer_registrer;
    template<typename t_Ty, boolean t_is_ptr_to_reflected_class>
    struct as_helper;
}

namespace connection
{
    class slot;
    class slot_pool;
}

namespace reflection
{
    template<typename> struct type_of;
    template<typename,int> struct meta_class_type_of;
    template<typename> struct base_meta_class_type_of;
    template<typename> struct canonical_meta_class_type_of;
    template<typename> struct template_specialization_adder;
    template<typename> struct template_specialization_of;
    template<typename> struct typedef_registrer;
    template<typename> struct type_name_of;
}

template <typename t_Ty>
o_forceinline o_NESTED_TYPE phantom::reflection::canonical_meta_class_type_of<t_Ty>::type* typeOf();

#define o_dynamic_type_of(...) phantom::typeByName(phantom::qualifiedDecoratedTypeNameOf<__VA_ARGS__>())
#define o_type_of(...) phantom::reflection::type_of<__VA_ARGS__>::object()

// function forwarding

o_export boolean                                        is(reflection::Class* a_pTestedClass, void*    in);
template<typename t_Ty, typename t_ITy>
inline boolean                                          is(t_ITy*    in);

template<typename t_Ty>
inline boolean                                          is(void*    in);

template<typename t_Ty, typename t_ITy>
inline t_Ty                                             as(t_ITy    in);
template<typename t_Ty>
 phantom::reflection::ReferenceType*                    referenceTypeOf();
template<typename t_Ty>
 phantom::reflection::Type*                             constTypeOf();
template<typename t_Ty>
 phantom::reflection::ArrayType*                        arrayTypeOf(size_t);
template<typename t_Ty>
 phantom::reflection::DataPointerType*                  pointerTypeOf();

o_export phantom::reflection::Namespace*                rootNamespace();
o_export phantom::reflection::Namespace*                namespaceByList( list<string>* a_pNamespaceNameAsStringList );
o_export phantom::reflection::Namespace*                namespaceByName( const string& a_strNamespaceName, reflection::Namespace* a_pScope = rootNamespace() );
o_export inline phantom::reflection::SourceFile*        sourceFile(const string& a_strAbsoluteName);
o_export inline void                                    discardSourceFile(phantom::reflection::SourceFile* a_pSourceFile);
o_export phantom::reflection::Type*                     typeByName(const string& a_strName, phantom::reflection::LanguageElement* a_pScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;
o_export phantom::reflection::Type*					    typeByNameCascade(const string& a_strName, phantom::reflection::LanguageElement* a_pScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;
o_export phantom::reflection::LanguageElement*          elementByName(const string& a_strName, phantom::reflection::LanguageElement* a_pScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;
template<typename t_Ty> o_forceinline t_Ty*             elementByNameAs(const string& a_strName, phantom::reflection::LanguageElement* a_pRootElement = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) { return as<t_Ty*>(elementByName(a_strName, a_pRootElement)); }
o_export phantom::reflection::Function*                 functionByName( const string& a_strName, phantom::reflection::Namespace* a_pScope = rootNamespace() );
o_export phantom::reflection::Class*                    classByName(const string& a_strQualifiedName, phantom::reflection::LanguageElement* a_pRootScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;
o_export phantom::reflection::Expression*               expressionByName(const string& a_strName, phantom::reflection::LanguageElement* a_pScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;
o_export void                                           elementsByClass(reflection::Class* a_pClass, vector<reflection::LanguageElement*>& out, phantom::reflection::LanguageElement* a_pScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace())) ;
o_export phantom::reflection::LanguageElement*		    elementByNameCascade(const string& a_strName, phantom::reflection::Namespace* a_pScope = rootNamespace());

o_export phantom::reflection::Type*                     typeByGuid(uint guid) ;
o_export phantom::reflection::LanguageElement*          elementByGuid(uint guid) ;

o_export phantom::reflection::Language*                 cplusplus();
o_export phantom::reflection::Interpreter*              interpreter();


o_export void*                                          baseOf(void const* a_pThis, size_t a_uiLevel);
o_export phantom::reflection::Class*                    classOf(void const* a_pThis, size_t a_uiLevel);
o_export phantom::reflection::Class*                    classAt(void const* a_pThis, size_t a_uiLevel);
o_export const phantom::rtti_data&                      rttiDataOf(void const* a_pThis, size_t a_uiLevel);
o_export const phantom::rtti_data&                      rttiDataOf(void const* a_pThis, reflection::Class* a_pLayoutClass);
o_export void                                           rttiLayoutOf(void const* a_pThis, vector<void*>& out, size_t a_uiLevel);
o_export void                                           dynamicDelete(void* a_pThis o_memory_stat_append_parameters);
o_export inline const rtti_data*                        addRttiData(void const* a_pThis, const rtti_data& data);
o_export inline void                                    replaceRttiData(void const* a_pThis, const rtti_data& data);
o_export inline void                                    removeRttiData(void const* a_pThis, size_t a_uiLevel);

o_export void                                           assertion BOOST_PREVENT_MACRO_SUBSTITUTION ( const character* e, const character* m , const char* f , uint l);
o_export void                                           warning BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);
o_export void                                           error BOOST_PREVENT_MACRO_SUBSTITUTION (const character* e, const character* m, const char* f, uint l);

o_export string                                         encodeQualifiedDecoratedNameToIdentifierName(const string& a_strTypeName) ;
o_export string                                         decodeQualifiedDecoratedNameFromIdentifierName(const string& a_strTypeName) ;


enum EMessageType
{
    e_MessageType_Undefined,
    e_MessageType_Information,
    e_MessageType_Success,
    e_MessageType_Warning,
    e_MessageType_Error,
};

o_export void                                           message(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, ... );
o_export void                                           message(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, va_list args);
o_export Message*                                       topMessage(const string& a_strCategory);
o_export void                                           clearMessages(const string& a_strCategory);
o_export void                                           pushMessage(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, ...);
o_export void                                           pushMessage(const string& a_strCategory, EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, va_list args);
o_export void                                           popMessage(const string& a_strCategory);

o_export size_t                                         currentThreadId();
o_export void                                           yieldCurrentThread();

o_export void                                           installReflection(const string& a_strName, const string& a_strFileName, size_t a_PlatformHandle);
o_export void                                           uninstallReflection(const string& a_strName);

o_export void                                           pushModule(Module* a_pModule);
o_export Module*                                        popModule();
o_export Module*                                        currentModule();
o_export ModuleLoader*                                  moduleLoader();
o_export Module*                                        moduleByName(const string& a_strName);
o_export Module*                                        moduleByFilePath(const string& a_strFileName);
o_export Module*                                        moduleByFileName(const string& a_strFileName);
o_export map<string, Module*>::const_iterator           beginModules();
o_export map<string, Module*>::const_iterator           endModules();
o_export Module*                                        instanceModuleOf(void const* a_pInstance);
o_export void                                           release();

o_export phantom::reflection::Type*                     backupType(phantom::reflection::Type* a_pType = (phantom::reflection::Type*)0xffffffff);

o_export void                                           setCurrentDataBase(serialization::DataBase* a_pDataBase);
o_export serialization::DataBase*                       getCurrentDataBase();

template <typename t_Ty>
phantom::reflection::Constant*                          constant(t_Ty a_Constant);

o_namespace_end(phantom)

    /* EXTENSION (allocator, constructor, installer, serializer, initializer,  ... to be continued) */

    template<typename t_Ty>
class phantom_proxy_generator__________;

template<typename t_Ty, typename t_Proxy>
class phantom_proxy_generator_base_____
{
protected:
    typedef t_Ty phantom_proxy_generator_reflection_self_type;
    typedef t_Ty phantom_proxy_generator_statechart_self_type;
    typedef t_Proxy phantom_proxy_generator_reflection_proxy_type;
    typedef t_Proxy phantom_proxy_statechart_proxy_type;
};

template<typename t_Ty>
class phantom_proxy_union_generator_base_____
{
protected:
    typedef t_Ty phantom_proxy_generator_reflection_self_type;
    typedef t_Ty phantom_proxy_generator_statechart_self_type;
    typedef t_Ty phantom_proxy_generator_reflection_proxy_type;
    typedef t_Ty phantom_proxy_statechart_proxy_type;

    int                                         m_PHANTOM_RESERVED_no_signal;
    int                                         PHANTOM_CODEGEN_m_slot_list_of_m_PHANTOM_RESERVED_no_signal;
};

#include "phantom/def_connection.h"

#include "phantom/def_memory.inl"
#include "phantom/reflection/native/NativeVTableInspector.h"

#include "phantom/Module.h"
#include "phantom/variant.h"
#include "phantom/reflection/LanguageElement.h"
#include "phantom/reflection/TemplateElement.h"
#include "phantom/reflection/Template.h"
#include "phantom/reflection/Signature.h"
#include "phantom/reflection/VirtualMemberFunctionTable.h"
#include "phantom/reflection/Type.h"
#include "phantom/reflection/ConstType.h"


#include "phantom/reflection/SourceFile.h"
#include "phantom/reflection/PrimitiveType.h"
#include "phantom/reflection/PointerType.h"
#include "phantom/reflection/DataPointerType.h"
#include "phantom/reflection/ReferenceType.h"
#include "phantom/reflection/ArrayType.h"
#include "phantom/reflection/ValueMember.h"
#include "phantom/reflection/Constant.h"
#include "phantom/reflection/NumericConstant.h"
#include "phantom/reflection/Variable.h"
#include "phantom/reflection/Addressable.h"
#include "phantom/reflection/Constant.h"
#include "phantom/reflection/Iterator.h"
#include "phantom/reflection/ConstIterator.h"
#include "phantom/reflection/Subroutine.h"
#include "phantom/reflection/Constructor.h"
#include "phantom/reflection/Function.h"
#include "phantom/reflection/StaticVariable.h"
#include "phantom/reflection/ClassType.h"
#include "phantom/reflection/Class.h"
#include "phantom/reflection/Namespace.h"

#include "phantom/reflection/ContainerClass.h"
#include "phantom/reflection/SequentialContainerClass.h"
#include "phantom/reflection/MapContainerClass.h"
#include "phantom/reflection/SetContainerClass.h"

#include "phantom/reflection/PODUnion.h"
#include "phantom/reflection/Union.h"
#include "phantom/reflection/Structure.h"

#include "phantom/reflection/native/TNumericConstant.h"

#include "phantom/reflection/Enum.h"

#include "phantom/reflection/Member.h"
#include "phantom/reflection/MemberFunction.h"
#include "phantom/reflection/InstanceMemberFunction.h"
#include "phantom/reflection/StaticMemberFunction.h"

o_namespace_begin(phantom, reflection, native)

    template<typename t_Ty>
struct addressable_wrapper
{
    static void*   address(t_Ty call) { return nullptr; }
    enum { value = false };
};

template<typename t_Ty>
struct addressable_wrapper<t_Ty&>
{
    static void*   address(t_Ty& call) { return (void*)&call; }
    enum { value = true };
};

template<typename t_Ty>
struct addressable_wrapper<t_Ty const&>
{
    static void*   address(t_Ty const& call) { return nullptr; }
    enum { value = false };
};

template<typename t_Ty>
struct return_storage_type_helper
{
    typedef t_Ty type;
};

template<typename t_Ty>
struct return_storage_type_helper<t_Ty&>
{
    typedef t_Ty* type;
};

template<typename t_Ty>
struct return_storage_type_helper<const t_Ty>
{
    typedef t_Ty type;
};

template<typename t_Ty>
struct return_storage_wrapper
{
    static t_Ty& apply(const t_Ty& input)
    {
        return (t_Ty&)input;
    }
};

template<typename t_Ty>
struct return_storage_wrapper<t_Ty&>
{
    static t_Ty* apply(t_Ty& input)
    {
        return &input;
    }
};

o_namespace_end(phantom, reflection, native)

#include "phantom/reflection/native/TNativeFunction.h"
#include "phantom/reflection/native/TNativeStaticMemberFunctionBase.h"
#include "phantom/reflection/native/TNativeStaticMemberFunction.h"
#include "phantom/reflection/native/TNativeInstanceMemberFunctionBase.h"
#include "phantom/reflection/native/TNativeInstanceMemberFunction.h"
#include "phantom/reflection/native/TNativeInstanceMemberFunctionConst.h"
#include "phantom/reflection/native/TNativeConstructor.h"

#include "phantom/reflection/native/TNativeMemberFunctionProvider.h"
#include "phantom/reflection/native/TNativeFunctionProvider.h"


#if o__int__reflection_template_use_level >= 2
#include "phantom/reflection/native/TNativeSignatureProvider.h"
#include "phantom/reflection/native/TNativePropertySignalProvider.h"
#else
#include "phantom/reflection/native/DynamicNativeSignalProvider.h"
#endif

#include "phantom/reflection/native/TRange.h"

#include "phantom/reflection/DataMember.h"
#include "phantom/reflection/InstanceDataMember.h"
#include "phantom/reflection/AnonymousSection.h"
#include "phantom/reflection/AnonymousStruct.h"
#include "phantom/reflection/AnonymousUnion.h"
#include "phantom/reflection/StaticDataMember.h"
#include "phantom/reflection/Property.h"
#include "phantom/reflection/native/TNativeInstanceDataMember.h"
#include "phantom/reflection/native/TNativeProperty.h"
#include "phantom/reflection/native/TNativeStaticDataMember.h"
#include "phantom/reflection/native/TNativeVariable.h"
#include "phantom/reflection/native/TNativeDataMemberProvider.h"
#include "phantom/util/Comparator.h"

#include "phantom/reflection/TemplateSpecialization.h"
#include "phantom/reflection/Signal.h"
#include "phantom/reflection/native/TNativeSignalBase.h"
#include "phantom/reflection/native/TNativeSignal.h"
#include "phantom/reflection/ClassExtension.h"
#include "phantom/reflection/PureVirtualMemberFunction.h"
#include "phantom/reflection/Function.h"

o_namespace_begin(phantom)

o_export dynamic_initializer_handle*                dynamic_initializer();

class o_export dynamic_initializer_handle
{
    friend o_export void installReflection(const string& a_strName);
    friend o_export void uninstallReflection(const string& a_strName);
    friend o_export dynamic_initializer_handle* dynamic_initializer();
    typedef void    (*module_installation_func)        (phantom::reflection::Type*,uint);
    friend class phantom::Phantom;

protected:
    dynamic_initializer_handle();
    ~dynamic_initializer_handle();
    phantom::reflection::Namespace* parseNamespace(const string& a_strFileName) const;

protected:
    struct dynamic_initializer_module_installation_func
    {
        dynamic_initializer_module_installation_func() : setupFunc(NULL) {}
        dynamic_initializer_module_installation_func( phantom::reflection::Type*      a_pType, module_installation_func    a_setupFunc )
            : type(a_pType)
            , setupFunc(a_setupFunc)
        {

        }
        o_forceinline void exec(uint step)
        {
            (*setupFunc)(type, step);
        }
        o_forceinline bool operator<(const dynamic_initializer_module_installation_func& other) const;
        module_installation_func        setupFunc;
        phantom::reflection::Type*      type;
    };

    struct deferred_registrer_base
    {
        virtual ~deferred_registrer_base() {}
        virtual void registerElement() = 0;
    };

    template<typename t_SignatureTy, typename t_FunctionPtrTy>
    struct deferred_function_registrer : public deferred_registrer_base
    {
        deferred_function_registrer() {}
        deferred_function_registrer(const string& a_Namespace, const string& a_Name, const string& a_Signature, t_FunctionPtrTy a_FunctionPtr, modifiers_t a_Modifiers = 0)
            : m_Name(a_Name)
            , m_Namespace(a_Namespace)
            , m_Signature(a_Signature)
            , m_FunctionPtr(a_FunctionPtr)
            , m_Modifiers(a_Modifiers)
        {

        }
        virtual void registerElement()
        {
            reflection::Namespace* pNamespace = m_Namespace.empty() ? phantom::rootNamespace() : phantom::namespaceByName(m_Namespace);
            pNamespace->addFunction(
                phantom::reflection::native::TNativeFunctionProvider<t_SignatureTy>::CreateFunction(m_Name, phantom::reflection::Signature::Create(m_Signature.c_str(), nullptr, pNamespace), m_FunctionPtr, m_Modifiers)
                );
        }
        string m_Name;
        string m_Namespace;
        string m_Signature;
        t_FunctionPtrTy  m_FunctionPtr;
        modifiers_t m_Modifiers;
    };
    typedef vector<dynamic_initializer_module_installation_func>        dynamic_initializer_module_installation_func_vector;

    template<typename t_Ty>
    struct deferred_variable_registrer : public deferred_registrer_base
    {
        deferred_variable_registrer() {}
        deferred_variable_registrer(const string& a_Namespace, const string& a_Name, t_Ty* a_pVariablePointer, reflection::Range* a_pRange, modifiers_t a_Modifiers = 0)
            : m_Name(a_Name)
            , m_Namespace(a_Namespace)
            , m_pVariablePointer(a_pVariablePointer)
            , m_pRange(a_pRange)
            , m_Modifiers(a_Modifiers)
        {

        }
        virtual void registerElement()
        {
            reflection::Namespace* pNamespace = m_Namespace.empty() ? phantom::rootNamespace() : phantom::namespaceByName(m_Namespace);
            pNamespace->addVariable(o_dynamic_proxy_new(phantom::reflection::native::TNativeVariable<t_Ty>)(typeOf<t_Ty>(), m_Name, m_pVariablePointer, m_pRange, m_Modifiers));
        }
        string m_Name;
        string m_Namespace;
        t_Ty*  m_pVariablePointer;
        reflection::Range* m_pRange;
        modifiers_t m_Modifiers;
    };

private:
    vector<dynamic_initializer_module_installation_func_vector>     m_DeferredSetupInfos;
    vector<reflection::Template*>                                   m_DeferredTemplates;
    vector<deferred_registrer_base*>                                m_DeferredElements;
    int                                                             m_iCurrentInstallationStep;
    unordered_map<string, reflection::Type*>                        m_RegisteredTypes;
    bool                                                            m_bActive;
    bool                                                            m_bAutoRegistrationLocked;

public:
    inline reflection::Type*    registeredTypeByName(const string& a_strQualifiedDecoratedName)
    {
        auto found = m_RegisteredTypes.find(a_strQualifiedDecoratedName);
        if(found == m_RegisteredTypes.end()) return nullptr;
        return found->second;
    }
    void    registerType( const string& a_strQualifiedDecoratedName, phantom::reflection::Type* a_pType );
    void    registerType( const string& a_strQualifiedDecoratedName, const string& a_strScope, phantom::reflection::Type* a_pType );
    void    registerModule( phantom::reflection::Type* a_pType, module_installation_func setupFunc, uint a_uiSetupStepMask );
    void    registerTemplate( reflection::Template* a_pTemplate );
    void    installReflection(const string& a_strName, const string& a_strFileName, size_t a_PlatformHandle);
    void    uninstallReflection(const string& a_strName);
    bool    isActive() const { return m_bActive; }
    bool    isAutoRegistrationLocked() const { return m_bAutoRegistrationLocked; }
    void    setActive(bool a_bActive) { o_assert(a_bActive == !m_bActive); m_bActive = a_bActive; }
    void    setAutoRegistrationLocked(bool a_bLocked) { o_assert(a_bLocked == !m_bAutoRegistrationLocked); m_bAutoRegistrationLocked = a_bLocked; }
    template<typename t_SignatureTy, typename t_FunctionPtrTy>
    void    registerFunction( const string& a_Namespace, const string& a_Name, const string& a_Signature, t_FunctionPtrTy a_FunctionPtr, modifiers_t a_Modifiers = 0 )
    {
        m_DeferredElements.push_back(new deferred_function_registrer<t_SignatureTy, t_FunctionPtrTy>(a_Namespace, a_Name, a_Signature, a_FunctionPtr, a_Modifiers));
    }
    template<typename t_Ty>
    void    registerVariable( const string& a_Namespace, const string& a_Name, t_Ty* a_pVariablePtr, reflection::Range* a_pRange,  modifiers_t a_Modifiers = 0 )
    {
        m_DeferredElements.push_back(new deferred_variable_registrer<t_Ty>(a_Namespace, a_Name, a_pVariablePtr, a_pRange, a_Modifiers));
    }
};

o_namespace_end(phantom)


#include "data.h"
#include "object.h"
#include "rtti_data.h"
#include "def_reflection.h"
#include "phantom/def_phantom_0_0.inl"
#include "def_serialization.h"
#include "phantom/serialization/DataBase.h"
#include "def_extension.h"
#include "def_allocate.h"
#include "def_statechart.h"
#include "def_declare.h"
#include "def_util.h"
#include "def_math.h"

o_namespace_begin(phantom)

typedef std::pair<data,data> data_pair;

o_namespace_end(phantom)

o_namespace_begin(phantom)

template <typename t_Ty>
o_forceinline state::StateMachine* stateMachineOf(t_Ty* a_pPtr)
{
    return a_pPtr->PHANTOM_CODEGEN_m_smdataptr->stateMachine();
}

o_forceinline state::StateMachine* stateMachineOf(void* a_pPtr, size_t a_uiLevel)
{
    return classOf(a_pPtr, a_uiLevel)->getStateMachineCascade();
}

o_namespace_end(phantom)

o_namespace_begin(phantom)

template<typename t_Ty>
inline const phantom::rtti_data& rttiDataOf(t_Ty const* a_pThis);

namespace detail {

    template<typename t_Ty, boolean t_are_pointers>
    struct as_helper
    {
        template<typename t_ITy>
        static t_Ty apply(t_ITy in)
        {
            reflection::Type* pDestType = reflection::type_of<o_NESTED_TYPE boost::remove_pointer<t_Ty>::type>::object();
            if(pDestType AND pDestType->asClass())
            {
                const rtti_data& oi = rttiDataOf(in);

                return oi.isNull()
                    ? nullptr// If no rtti registered we cannot know how to cast, we return NULL which is safer than trying to cast
                    : static_cast<t_Ty>(oi.cast((reflection::Class*)pDestType));
            }
            return nullptr;
        }
    };

    template<typename t_Ty>
    struct as_helper<t_Ty, false>
    {
        template<typename t_ITy>
        static t_Ty apply(t_ITy in)
        {
            return in;
        }
    };

} // namespace detail

template<typename t_Ty, typename t_ITy>
t_Ty           as(t_ITy    in)
{
    return detail::as_helper<t_Ty,boost::is_pointer<t_Ty>::value AND boost::is_pointer<t_ITy>::value>::apply(in);
}

#include "data.inl"
#include "object.inl"

o_export const phantom::rtti_data&                      rttiDataOf(void const* a_pThis, size_t a_uiLevel);
o_export const phantom::rtti_data&                      rttiDataOf(void const* a_pThis, reflection::Class* a_pLayoutClass);
o_export inline void                                    rttiLayoutOf(void const* a_pThis, vector<void*>& out, size_t a_uiLevel);

o_export void default_assert(const character* expression, const character* message, const char* file, uint line);
o_export void default_warning(const character* expression, const character* message, const char* file, uint line);
o_export void default_error(const character* expression, const character* message, const char* file, uint line);
o_export void default_log(int level, const char* file, uint line, const char* message, va_list args);

template <typename t_Ty>
o_forceinline
    phantom::reflection::TemplateSpecialization* templateSpecializationOf()
{
    return phantom::reflection::template_specialization_of<t_Ty>::object();
}

template <typename t_Ty>
o_forceinline phantom::reflection::Type*        registerType()
{
    return phantom::typeOf<t_Ty>();
}

template <typename t_Ty>
o_forceinline void                              registerTypedef(const char* a_strNamespace, const char* a_strTypedef)
{
    phantom::reflection::typedef_registrer<t_Ty> reg(a_strNamespace, a_strTypedef);
}

template <typename t_Ty>
o_forceinline void                              registerTypedef(const char* a_strTypedef)
{
    phantom::reflection::typedef_registrer<t_Ty> reg(a_strTypedef);
}

o_export boolean                 canConnect(phantom::reflection::Signal* a_pSignal, phantom::reflection::InstanceMemberFunction* a_pMemberFunction );

template<typename t_Sender, typename t_Receiver>
connection::slot const*             connect(t_Sender* a_pSender, const character* a_pSignal, t_Receiver* a_pReceiver, const character* a_pMemberFunction, const char* file = __FILE__, long line = __LINE__)
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return connect(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                 , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction, file, line);
}

template<typename t_Sender, typename t_Receiver>
connection::slot const*             disconnect(t_Sender* a_pSender, const character* a_pSignal, t_Receiver* a_pReceiver, const character* a_pMemberFunction, const char* file = __FILE__, long line = __LINE__)
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return disconnect(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                    , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction, file, line);
}

template<typename t_Sender, typename t_Receiver>
connection::slot const*             connect(t_Sender* a_pSender, phantom::reflection::Signal* a_pSignal, t_Receiver* a_pReceiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction, const char* file = __FILE__, long line = __LINE__)
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return connect(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                 , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction, file, line);
}

template<typename t_Sender, typename t_Receiver>
connection::slot const*             disconnect(t_Sender* a_pSender, phantom::reflection::Signal* a_pSignal, t_Receiver* a_pReceiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction, const char* file = __FILE__, long line = __LINE__)
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return disconnect(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                    , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction, file, line);
}

template<typename t_Sender, typename t_Receiver>
connection::slot const*             tryConnect(t_Sender* a_pSender, const character* a_pSignal, t_Receiver* a_pReceiver, const character* a_pMemberFunction, const char* file = __FILE__, long line = __LINE__)
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return tryConnect(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                    , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction, file, line);
}

template<typename t_Sender, typename t_Receiver>
connection::slot const*             tryDisconnect(t_Sender* a_pSender, const character* a_pSignal, t_Receiver* a_pReceiver, const character* a_pMemberFunction, const char* file = __FILE__, long line = __LINE__)
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return tryDisconnect(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                       , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction, file, line);
}

template<typename t_Sender, typename t_Receiver>
boolean                             areConnected(t_Sender* a_pSender, const character* a_pSignal, t_Receiver* a_pReceiver, const character* a_pMemberFunction )
{
    reflection::Type* pSenderType = phantom::typeOf<typename boost::remove_const<t_Sender>::type>();
    reflection::Type* pReceiverType = phantom::typeOf<typename boost::remove_const<t_Receiver>::type>();
    return areConnected(rttiDataOf(a_pSender, pSenderType ? pSenderType->asClass() : nullptr), a_pSignal
                      , rttiDataOf(a_pReceiver, pReceiverType ? pReceiverType->asClass() : nullptr), a_pMemberFunction);
}

o_namespace_end(phantom)

#include "phantom/def_phantom_0_3.inl"

o_namespace_begin(phantom)

enum
{
    eInvalidMetaDataIndex = 0xffffffff,
};

o_export phantom::reflection::Namespace*            rootNamespace();
o_export reflection::Type*                          stringType();

o_export size_t                                     metaDataIndex(const string& elementName);
o_export void                                       setMetaDataValue(const string& elementName, size_t index, const string& value);
o_export void                                       setMetaDataValue(const string& elementName, const string& metaDataName, const string& value);

o_export const string&                              metaDataValue(const string& elementName, size_t index);
o_export const string&                              metaDataValue(const string& elementName, const string& metaDataName);
o_export size_t                                     metaDataCount();
o_export const string&                              metaDataName(size_t index);

template<typename t_Ty>
inline reflection::template_specialization_registrer<t_Ty>::template_specialization_registrer()
{
    dynamic_initializer()->setActive(true);
    typeOf<t_Ty>();
    dynamic_initializer()->setActive(false);
}

template<unsigned alloc_size>
class static_size_allocator : public boost::singleton_pool<boost::fast_pool_allocator_tag, alloc_size>
{};

template<size_t t_size>
o_forceinline void*                                 staticPoolAllocate() { return phantom::static_size_allocator<t_size>::ordered_malloc(); }
template<size_t t_size>
o_forceinline void                                  staticPoolDeallocate(void* ptr) { phantom::static_size_allocator<t_size>::ordered_free(ptr); }
template<size_t t_size>
o_forceinline void*                                 staticPoolAllocateN(typename phantom::static_size_allocator<t_size>::size_type n) { return phantom::static_size_allocator<t_size>::ordered_malloc(n); }
template<size_t t_size>
o_forceinline void                                  staticPoolDeallocateN(void* ptr, typename phantom::static_size_allocator<t_size>::size_type n) { phantom::static_size_allocator<t_size>::ordered_free(ptr,n); }

o_export phantom::reflection::Signature*            createSignature(const char* a_pText, phantom::reflection::TemplateSpecialization* a_pTemplateSpecialization, phantom::reflection::LanguageElement* a_pScope);
o_export void*                                      baseOf(void const* a_pThis, size_t a_uiLevel = 0);
o_export phantom::reflection::Class*                classOf(void const* a_pThis, size_t a_uiLevel);
o_export phantom::reflection::Class*                classAt(void const* a_pThis, size_t a_uiLevel);
o_export const phantom::rtti_data&                  rttiDataOf(void const* a_pThis, size_t a_uiLevel);
o_export void                                       rttiLayoutOf(void const* a_pThis, vector<void*>& out, size_t a_uiLevel);
o_export const rtti_data*                           addRttiData(void const* a_pThis, const rtti_data& a_RttiData);
o_export void                                       replaceRttiData(void const* a_pThis, const rtti_data& a_RttiData);
o_export void                                       removeRttiData(void const* a_pThis, size_t a_uiLevel);
o_export const phantom::rtti_data&                  rttiDataOf(void const* a_pThis, reflection::Class* a_pLayoutClass);

template<typename t_Ty>
inline const phantom::rtti_data&                    rttiDataOf(t_Ty const* a_pThis)
{
    auto pType = typeOf<t_Ty>();
    return rttiDataOf(a_pThis, pType ? pType->asClass() : nullptr);
}

template<typename t_Ty>
inline reflection::Class*                           classOf(t_Ty const* a_pThis)
{
    auto pType = typeOf<t_Ty>();
    return rttiDataOf(a_pThis, pType ? pType->asClass() : nullptr).object_class;
}

o_export connection::slot const*                    connect(const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction, const char* file = __FILE__, long line = __LINE__);
o_export connection::slot const*                    disconnect(const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction, const char* file = __FILE__, long line = __LINE__);
o_export connection::slot const*                    connect(const rtti_data& a_Sender, phantom::reflection::Signal* a_pSignal, const rtti_data& a_Receiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction, const char* file = __FILE__, long line = __LINE__);
o_export connection::slot const*                    disconnect(const rtti_data& a_Sender, phantom::reflection::Signal* a_pSignal, const rtti_data& a_Receiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction, const char* file = __FILE__, long line = __LINE__);
o_export connection::slot const*                    tryConnect(const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction, const char* file = __FILE__, long line = __LINE__);
o_export connection::slot const*                    tryDisconnect(const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction, const char* file = __FILE__, long line = __LINE__);
o_export bool                                       areConnected( const rtti_data& a_Sender, const character* a_pSignal, const rtti_data& a_Receiver, const character* a_pMemberFunction );
o_export bool                                       areConnected( const rtti_data& a_Sender, reflection::Signal* a_pSignal, const rtti_data& a_Receiver, reflection::InstanceMemberFunction* a_pMemberFunction );

o_export inline void*                               custom_malloc(size_t s o_memory_stat_append_parameters){ return o__func__malloc(s);}
o_export inline void                                custom_free(void* ptr o_memory_stat_append_parameters){ o__func__free(ptr);}
o_export inline void*                               custom_realloc(void* ptr, size_t s o_memory_stat_append_parameters){ return o__func__realloc(ptr, s);}

o_export void*                                      dynamicPoolAllocate(size_t s o_memory_stat_append_parameters);
o_export void                                       dynamicPoolDeallocate(size_t s, void* a_pAddress o_memory_stat_append_parameters);
o_export void*                                      dynamicPoolAllocate(size_t s, size_t count o_memory_stat_append_parameters);
o_export void                                       dynamicPoolDeallocate(size_t s, void* a_pAddress, size_t count o_memory_stat_append_parameters);

template<typename t_Ty>
o_forceinline phantom::reflection::DataPointerType* pointerTypeOf()
{
    return typeOf<t_Ty>()->pointerType();
}
template<typename t_Ty>
o_forceinline phantom::reflection::ReferenceType*   referenceTypeOf()
{
    return typeOf<t_Ty>()->referenceType();
}
template<typename t_Ty>
o_forceinline phantom::reflection::Type*            constTypeOf()
{
    return typeOf<t_Ty>()->constType();
}
template<typename t_Ty>
o_forceinline phantom::reflection::ArrayType*       arrayTypeOf(size_t a_uiCount)
{
    return typeOf<t_Ty>()->arrayType(a_uiCount);
}
template<typename t_Ty>
o_forceinline phantom::reflection::PrimitiveType*   basicTypeOf()
{
    o_assert(false, "basicTypeOf not redefined for that basic type");
    return NULL;
}

o_namespace_end(phantom)


// Inlining as soon as possible the member_function which use Type class
template<typename t_Ty>
t_Ty* phantom::data::as() const
{
    reflection::Type* targetType = typeOf<t_Ty>();
    o_assert(targetType, "t_Ty must have reflection");
    if(m_type == targetType) return static_cast<t_Ty*>(m_address);
    return static_cast<t_Ty*>(m_type->cast(targetType, m_address));
}

inline phantom::data       phantom::data::cast(reflection::Type* a_pTargetType) const
{
    void* castedAddress = m_type->upcast(a_pTargetType, m_address);
    return phantom::data(castedAddress, castedAddress ? a_pTargetType : NULL);
}

inline void        phantom::data::destroy()
{
    m_type->teardown(m_address); m_type->deallocate(m_address); m_address = NULL; m_type = NULL;
}

// Inlining as soon as possible the member_function which use ClassType class
template<typename t_Ty>
t_Ty* phantom::object::as  ()
{
    reflection::ClassType* targetType = typeOf<t_Ty>();
    o_assert(m_class_type->isKindOf(targetType));
    if(m_class_type == targetType) return static_cast<t_Ty*>(m_address);
    return static_cast<t_Ty*>(m_class_type->upcast(targetType, m_address));
}

// Continue including ...

o_forceinline void*   phantom::rtti_data::cast(phantom::reflection::Class* a_pTargetClass) const
{
    return object_class->upcast(a_pTargetClass, base);
}

#include "phantom/reflection/native/TNativeDestructor.h"
#include "phantom/reflection/native/TType.h"

#include "phantom/def_phantom_0_1.inl"

#include "phantom/def_phantom_0_2.inl"

// DEFINE INLINE TEMPLATE FUNCS WHICH USE REFLECTION CLASSES (GCC constraint)

#include "phantom/state/StateMachineElement.h"

#include "phantom/state/Event.h"
#include "phantom/state/Reaction.h"
#include "phantom/state/StateMachine.h"
#include "phantom/state/Track.h"
#include "phantom/state/State.h"

#include "phantom/state/native/TNativeStateMachine.h"
#include "phantom/state/native/TNativeTrack.h"
#include "phantom/state/native/TNativeState.h"

#include "phantom/def_modules_phantom_state_StateMachine_dependency.inl"

o_namespace_begin(phantom)

typedef void (*message_report_func)(const character*, const character*, const char*, uint);
typedef void (*log_func)(int level, const char* file, uint line, const char* message, va_list arglist);

o_export void setAssertFunc(message_report_func a_func);
o_export void setErrorFunc(message_report_func a_func);
o_export void setLogFunc(log_func a_func);
o_export void setWarningFunc(message_report_func a_func);

template <typename t_Ty>
phantom::reflection::Constant* constant(t_Ty a_Constant)
{
    return o_dynamic_proxy_new(phantom::reflection::native::TNumericConstant<t_Ty>)(lexical_cast<string>(a_Constant),a_Constant);
}

o_forceinline bool dynamic_initializer_handle::dynamic_initializer_module_installation_func::operator<( const dynamic_initializer_module_installation_func& other ) const
{
    return other.type->isKindOf(type);
}

struct variable
{
    string name;
    variant value;
};

o_namespace_end(phantom)

#if o__int__reflection_template_use_level == 3
#   include "def_phantom_deferred_reflection.inl"
#endif

o_declareN(struct, (phantom, memory), malloc_free_allocator_for_boost);
o_declareNT(struct, (phantom, memory), (typename, typename), (T, UserAllocator), malloc_free_allocator);

#if o__int__reflection_template_use_level == 3
#   include "phantom/phantom.hxx"
#endif

o_declareNT(class, (phantom), (typename), (Enum), flags);

o_declareN((phantom, connection), slot);
o_declareN((phantom, connection), pair);
o_declareNC((phantom, connection), (slot), list);

#include "phantom/variant.inl"

o_namespace_begin(phantom)

class o_export Phantom
{
public:
    Phantom(int argc = 0, char* argv[] = NULL, int metadatasize = 0, char* metadata[] = NULL);
    ~Phantom();
};

o_namespace_end(phantom)

#endif // __prerequisites_h__
