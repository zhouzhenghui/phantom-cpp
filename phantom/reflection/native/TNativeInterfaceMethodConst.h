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

#ifndef o_phantom_reflection_native_TNativeInterfaceMemberFunctionConst_h__
#define o_phantom_reflection_native_TNativeInterfaceMemberFunctionConst_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

    template<typename t_Ty, typename _ReturnType>
class TNativeInterfaceMemberFunctionConst0 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst0<t_Ty, _ReturnType> self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(void) const;

    TNativeInterfaceMemberFunctionConst0(){}
    TNativeInterfaceMemberFunctionConst0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }


    virtual void            deleteNow() { o_delete(self_type) this; }

    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate<_ReturnType()>(phantom::polymorphic_cast<t_Ty>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) 
            = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) 
            = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)();
    }

protected:
    member_function_pointer m_member_function_pointer;

};


template<typename t_Ty>
class TNativeInterfaceMemberFunctionConst0<t_Ty, void> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst0<t_Ty, void>    self_type;
    typedef void (t_Ty::*member_function_pointer)(void) const;

    TNativeInterfaceMemberFunctionConst0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<fastdelegate::detail::DefaultVoid>(phantom::polymorphic_cast<t_Ty>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;

};


template<typename t_Ty, typename _ReturnType, typename t_Param0>
class TNativeInterfaceMemberFunctionConst1 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst1<t_Ty, _ReturnType, t_Param0>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0) const;
    
    TNativeInterfaceMemberFunctionConst1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }

    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<_ReturnType, t_Param0>(phantom::polymorphic_cast<t_Ty>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    { 
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) 
            = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};


template<typename t_Ty, typename t_Param0>
class TNativeInterfaceMemberFunctionConst1<t_Ty, void, t_Param0> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst1<t_Ty, void, t_Param0>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0) const;

    TNativeInterfaceMemberFunctionConst1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }

    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<fastdelegate::detail::DefaultVoid, t_Param0>(phantom::polymorphic_cast<t_Ty>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};


template<typename t_Ty, typename _ReturnType, typename t_Param0, typename t_Param1>
class TNativeInterfaceMemberFunctionConst2 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst2<t_Ty, _ReturnType, t_Param0, t_Param1>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1) const;

    TNativeInterfaceMemberFunctionConst2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<_ReturnType, t_Param0, t_Param1>(phantom::polymorphic_cast<t_Ty>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1]) );
    }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty, typename t_Param0, typename t_Param1>
class TNativeInterfaceMemberFunctionConst2<t_Ty, void, t_Param0, t_Param1> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst2<t_Ty, void, t_Param0, t_Param1>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1) const;

    TNativeInterfaceMemberFunctionConst2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<fastdelegate::detail::DefaultVoid, t_Param0, t_Param1>(phantom::polymorphic_cast<t_Ty>(a_pObject), m_member_function_pointer).GetMemento();
    }
    
    
    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        3 PARAMETERS
///  ==================================================================================================

template<typename t_Ty, typename _ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeInterfaceMemberFunctionConst3 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst3<t_Ty, _ReturnType, t_Param0, t_Param1,t_Param2>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;

    TNativeInterfaceMemberFunctionConst3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<_ReturnType, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2]) );
    }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeInterfaceMemberFunctionConst3<t_Ty, void, t_Param0, t_Param1, t_Param2> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst3<t_Ty, void, t_Param0, t_Param1, t_Param2>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;

    TNativeInterfaceMemberFunctionConst3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};



///  ==================================================================================================
///        4 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeInterfaceMemberFunctionConst4 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst4<t_Ty, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;

    TNativeInterfaceMemberFunctionConst4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) );
    }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeInterfaceMemberFunctionConst4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;

    TNativeInterfaceMemberFunctionConst4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        5 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeInterfaceMemberFunctionConst5 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst5<t_Ty, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;

    TNativeInterfaceMemberFunctionConst5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) 
            , *static_cast<t_Param4*>(a_pParams[4]) );
    }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeInterfaceMemberFunctionConst5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;

    TNativeInterfaceMemberFunctionConst5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};





///  ==================================================================================================
///        6 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeInterfaceMemberFunctionConst6 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst6<t_Ty, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;

    TNativeInterfaceMemberFunctionConst6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) 
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5]) );
    }

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
class TNativeInterfaceMemberFunctionConst6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;

    TNativeInterfaceMemberFunctionConst6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5]));
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};





///  ==================================================================================================
///        7 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeInterfaceMemberFunctionConst7 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst7<t_Ty, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)const;

    TNativeInterfaceMemberFunctionConst7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p0
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p1
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p2
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p3
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p4
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p5
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p6 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p0
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p1
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p2
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p3
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p4
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p5
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p6 );
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5])
            , *static_cast<t_Param6*>(a_pParams[6]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) 
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5])
            , *static_cast<t_Param6*>(a_pParams[6]) );
    }

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
class TNativeInterfaceMemberFunctionConst7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)const;

    TNativeInterfaceMemberFunctionConst7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p0
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p1
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p2
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p3
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p4
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p5
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p6 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5])
            , *static_cast<t_Param6*>(a_pParams[6]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};



///  ==================================================================================================
///        8 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeInterfaceMemberFunctionConst8 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst8<t_Ty, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;

    TNativeInterfaceMemberFunctionConst8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p0
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p1
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p2
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p3
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p4
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p5
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p6
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p7 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p0
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p1
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p2
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p3
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p4
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p5
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p6
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p7 );
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5])
            , *static_cast<t_Param6*>(a_pParams[6])
            , *static_cast<t_Param7*>(a_pParams[7]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) 
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5])
            , *static_cast<t_Param6*>(a_pParams[6])
            , *static_cast<t_Param7*>(a_pParams[7]) );
    }

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
class TNativeInterfaceMemberFunctionConst8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;

    TNativeInterfaceMemberFunctionConst8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p0
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p1
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p2
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p3
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p4
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p5
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p6
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p7 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5])
            , *static_cast<t_Param6*>(a_pParams[6])
            , *static_cast<t_Param7*>(a_pParams[7]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};

#ifndef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE

template<typename t_Ty, typename Signature>
class TNativeInterfaceMemberFunctionConst;

template<typename t_Ty, typename _ReturnType>
class TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType()> 
    : public TNativeInterfaceMemberFunctionConst0<_ReturnType, t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType()>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(void) const;
    
    TNativeInterfaceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunctionConst0<_ReturnType, t_Ty>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
};

template<typename t_Ty, typename _ReturnType, typename t_Param0>
class TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0)> 
    : public TNativeInterfaceMemberFunctionConst1<_ReturnType, t_Param0, t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0) const;
    
    TNativeInterfaceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunctionConst1<_ReturnType, t_Param0, t_Ty>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
};

template<typename t_Ty, typename _ReturnType, typename t_Param0, typename t_Param1>
class TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0,t_Param1)> 
    : public TNativeInterfaceMemberFunctionConst2<t_Ty, _ReturnType, t_Param0, t_Param1>
{
public:
    typedef TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0, t_Param1)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1) const;

    TNativeInterfaceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunctionConst2<t_Ty, _ReturnType, t_Param0, t_Param1>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};


template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0,t_Param1,t_Param2)> : public TNativeInterfaceMemberFunctionConst3<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    typedef TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0, t_Param1, t_Param2)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;
    TNativeInterfaceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunctionConst3<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};


template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3)> : public TNativeInterfaceMemberFunctionConst4<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    typedef TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;
    TNativeInterfaceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunctionConst4<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> 
    : public TNativeInterfaceMemberFunctionConst5<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>
{
public:
    typedef TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
    TNativeInterfaceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunctionConst5<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> : public TNativeInterfaceMemberFunctionConst6<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>
{
public:
    typedef TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
    TNativeInterfaceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunctionConst6<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> : public TNativeInterfaceMemberFunctionConst7<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>
{
public:
    typedef TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6) const;
    TNativeInterfaceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunctionConst7<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};


template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> 
    : public TNativeInterfaceMemberFunctionConst8<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>
{
public:
    typedef TNativeInterfaceMemberFunctionConst<t_Ty, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
    TNativeInterfaceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunctionConst8<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

#endif // o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE

o_namespace_end(phantom, reflection, native)

    //#include "TNativeInterfaceMemberFunctionConst.inl"

#endif // TNativeInterfaceMemberFunctionConst_h__