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

#ifndef o_phantom_reflection_TNativeStaticMemberFunction_h__
#define o_phantom_reflection_TNativeStaticMemberFunction_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename t_ReturnType>
class TNativeStaticMemberFunction0 : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction0<t_Ty, t_ReturnType> self_type;
    typedef t_ReturnType (*member_function_pointer)(void);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;


    TNativeStaticMemberFunction0(){}
    TNativeStaticMemberFunction0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunctionBase<t_Ty>(a_strName, a_pSignature, a_Modifiers|o_native|o_static), m_member_function_pointer(a_pFunc){}

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<t_ReturnType>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)();
    }

    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_member_function_pointer)());
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_member_function_pointer)());
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer        m_member_function_pointer;
};


template<typename t_Ty>
class TNativeStaticMemberFunction0<t_Ty, void> : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction0<t_Ty, void>    self_type;
  typedef void (*member_function_pointer)(void);


    TNativeStaticMemberFunction0()
    {

    }
    TNativeStaticMemberFunction0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeStaticMemberFunctionBase<t_Ty>(a_strName, a_pSignature, a_Modifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<fastdelegate::detail::DefaultVoid>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)();
    }
protected:
    member_function_pointer m_member_function_pointer;

};


template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeStaticMemberFunction1 : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction1<t_Ty, t_ReturnType, t_Param0>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;


    TNativeStaticMemberFunction1()
    {

    }
    TNativeStaticMemberFunction1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeStaticMemberFunctionBase<t_Ty>(a_strName, a_pSignature, a_Modifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
    {

    }


    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<t_ReturnType, t_Param0>(m_member_function_pointer).GetMemento();
    }
    
    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) ));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;
};


template<typename t_Ty, typename t_Param0>
class TNativeStaticMemberFunction1<t_Ty, void, t_Param0> : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction1<t_Ty, void, t_Param0>    self_type;
    typedef void (*member_function_pointer)(t_Param0);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;


    TNativeStaticMemberFunction1()
    {

    }
    TNativeStaticMemberFunction1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeStaticMemberFunctionBase<t_Ty>(a_strName, a_pSignature, a_Modifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<fastdelegate::detail::DefaultVoid, t_Param0>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};


template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeStaticMemberFunction2 : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;


    TNativeStaticMemberFunction2()
    {

    }
    TNativeStaticMemberFunction2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeStaticMemberFunctionBase<t_Ty>(a_strName, a_pSignature, a_Modifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<t_ReturnType, t_Param0, t_Param1>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }

    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) ));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty, typename t_Param0, typename t_Param1>
class TNativeStaticMemberFunction2<t_Ty, void, t_Param0, t_Param1> : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction2<t_Ty, void, t_Param0, t_Param1>    self_type;
    typedef void (*member_function_pointer)(t_Param0,t_Param1);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;


    TNativeStaticMemberFunction2()
    {

    }
    TNativeStaticMemberFunction2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeStaticMemberFunctionBase<t_Ty>(a_strName, a_pSignature, a_Modifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<fastdelegate::detail::DefaultVoid, t_Param0, t_Param1>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        3 PARAMETERS
///  ==================================================================================================

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeStaticMemberFunction3 : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;


    TNativeStaticMemberFunction3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<t_ReturnType, t_Param0,t_Param1,t_Param2>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }

    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) ));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) 
            , *static_cast<t_Param2_noref*>(a_pParams[2])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeStaticMemberFunction3<t_Ty, void, t_Param0, t_Param1, t_Param2> : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction3<t_Ty, void, t_Param0, t_Param1, t_Param2>    self_type;
    typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeStaticMemberFunction3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2>(m_member_function_pointer).GetMemento();
    }
    
    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};



///  ==================================================================================================
///        4 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeStaticMemberFunction4 : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeStaticMemberFunction4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeStaticMemberFunction4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3> : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3>    self_type;
    typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeStaticMemberFunction4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        5 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeStaticMemberFunction5 : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeStaticMemberFunction5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) ));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeStaticMemberFunction5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>    self_type;
    typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeStaticMemberFunction5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(m_member_function_pointer).GetMemento();
    }
    
    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};





///  ==================================================================================================
///        6 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeStaticMemberFunction6 : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeStaticMemberFunction6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) ));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeStaticMemberFunction6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>    self_type;
    typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeStaticMemberFunction6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};





///  ==================================================================================================
///        7 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeStaticMemberFunction7 : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeStaticMemberFunction7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(m_member_function_pointer).GetMemento();
    }
    
    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) ));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }


protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeStaticMemberFunction7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>    self_type;
    typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeStaticMemberFunction7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]));
    }

protected:
    member_function_pointer m_member_function_pointer;
};



///  ==================================================================================================
///        8 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeStaticMemberFunction8 : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;

    TNativeStaticMemberFunction8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) ));
    }
    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeStaticMemberFunction8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> : public TNativeStaticMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeStaticMemberFunction8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>    self_type;
  typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);
  typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;



    TNativeStaticMemberFunction8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(m_member_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};



template<typename t_Ty, typename Signature>
class TNativeStaticMemberFunction;

template<typename t_Ty, typename t_ReturnType>
class TNativeStaticMemberFunction<t_Ty, t_ReturnType()>
    : public TNativeStaticMemberFunction0< t_Ty, t_ReturnType>
{
public:
    typedef TNativeStaticMemberFunction<t_Ty, t_ReturnType()>    self_type;
    typedef t_ReturnType (*member_function_pointer)(void);

    TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeStaticMemberFunction0<t_Ty,t_ReturnType>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native)
    {

    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0)> : public TNativeStaticMemberFunction1<t_Ty, t_ReturnType, t_Param0>
{
public:
    typedef TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0)>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0);

    TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeStaticMemberFunction1<t_Ty,t_ReturnType,t_Param0>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native)
    {

    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1)> : public TNativeStaticMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>
{
public:
    typedef TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1);

    TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeStaticMemberFunction2<t_Ty,t_ReturnType,t_Param0,t_Param1>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native)
    {

    }

};

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2)> : public TNativeStaticMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    typedef TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2);

    TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeStaticMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native)
    {

    }

};


template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3)> : public TNativeStaticMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    typedef TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);

    TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeStaticMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native)
    {

    }

};

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> : public TNativeStaticMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>
{
public:
    typedef TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);

    TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeStaticMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native)
    {

    }
};

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> : public TNativeStaticMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>
{
public:
    typedef TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);

    TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeStaticMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native)
    {

    }
};

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> : public TNativeStaticMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>
{
public:
    typedef TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);

    TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeStaticMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native)
    {

    }
};


template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> : public TNativeStaticMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>
{
public:
    typedef TNativeStaticMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);

    TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeStaticMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native)
    {

    }
};


o_namespace_end(phantom, reflection, native)

#endif // TNativeStaticMemberFunction_h__
