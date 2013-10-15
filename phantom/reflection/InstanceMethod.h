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

#ifndef o_phantom_reflection_InstanceMethod_h__
#define o_phantom_reflection_InstanceMethod_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Method.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "InstanceMethod.classdef.h"
/* *********************************************** */

o_h_begin

class o_export InstanceMethod : public Subroutine, public Method
{
public:
    enum EOverloadRelation
    {
        e_OverloadRelation_None = 0,
        e_OverloadRelation_Equal,
        e_OverloadRelation_Covariant,
        e_OverloadRelation_Contravariant,
        e_OverloadRelation_Forbidden,
    };

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:

    InstanceMethod(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0);

    reflection::ClassType*  getOwnerClassType() const { return static_cast<reflection::ClassType*>(m_pOwner); }
    reflection::Class*      getOwnerClass() const { return static_cast<reflection::ClassType*>(m_pOwner)->asClass(); }

    void    safeInvoke( void* a_pCallerAddress, void** a_pArgs ) const 
    {
        reflection::Class* pOwnerClass = m_pOwner->asClass();
        if(pOwnerClass)
        {
            const rtti_data& rttiData = phantom::rttiDataOf(a_pCallerAddress);
            invoke( rttiData.cast(pOwnerClass), a_pArgs);
        }
        else
        {
            invoke( a_pCallerAddress, a_pArgs);
        }
    }
    void    safeInvoke( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const 
    {
        reflection::Class* pOwnerClass = m_pOwner->asClass();
        if(pOwnerClass)
        {
            const rtti_data& rttiData = phantom::rttiDataOf(a_pCallerAddress);
            invoke( rttiData.cast(pOwnerClass), a_pArgs, a_pReturnAddress);
        }
        else
        {
            invoke( a_pCallerAddress, a_pArgs, a_pReturnAddress);
        }
    }

    virtual void    invoke( void* a_pCallerAddress, void** a_pArgs ) const = 0;
    virtual void    invoke( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const = 0;
    
    virtual void    call( void** a_pArgs ) const 
    { 
        void* caller = *a_pArgs++;
        invoke( caller, a_pArgs); 
    }
    virtual void    call( void** a_pArgs, void* a_pReturnAddress ) const 
    {
        void* caller = *a_pArgs++;
        invoke( caller, a_pArgs); 
    }

    bool                canOverload(InstanceMethod* a_pInstanceMethod) const
    {
        EOverloadRelation r = getOverloadRelationWith(a_pInstanceMethod);
        return (r == e_OverloadRelation_Covariant) OR (r == e_OverloadRelation_Equal);
    }

    bool                canOverload(const string& a_strName, Signature* a_pSignature) const
    {
        EOverloadRelation r = getOverloadRelationWith(a_strName, a_pSignature);
        return (r == e_OverloadRelation_Covariant) OR (r == e_OverloadRelation_Equal);
    }

    EOverloadRelation   getOverloadRelationWith(const string& a_strName, Signature* a_pSignature) const;

    EOverloadRelation   getOverloadRelationWith(InstanceMethod* a_pMethod) const
    {
        if(NOT(a_pMethod->isVirtual())) return e_OverloadRelation_None;
        return getOverloadRelationWith(a_pMethod->getName(), a_pMethod->getSignature());
    }

    boolean             isAbstract() const { return m_bfModifiers.matchesMask(o_abstract); }
    boolean             isVirtual() const { return m_bfModifiers.matchesMask(o_virtual); }

    boolean             isConst() const { return m_bfModifiers.matchesMask(o_const); }

    virtual boolean     isInstanceMethod() const { return true; }
    virtual boolean     isSlot() const { return (m_bfModifiers & o_slot_method) == o_slot_method; }
    virtual InstanceMethod*    asSlot() const { return (m_bfModifiers & o_slot_method) == o_slot_method ? const_cast<InstanceMethod*>(this) : nullptr; }

    int                 getVirtualTableIndex() const { return m_iVirtualTableIndex; }

    virtual LanguageElement*    asLanguageElement() const { return const_cast<InstanceMethod*>(this); }
    virtual Subroutine*         asSubroutine() const { return const_cast<InstanceMethod*>(this); }
    virtual void                findOverloadedMethods(vector<InstanceMethod*>& a_Result) const;
    virtual Class*              getSortingCategoryClass() const;
    virtual InstanceMethod*     asInstanceMethod() const { return const_cast<InstanceMethod*>(this); }
    virtual Method*             asMethod() const { return const_cast<InstanceMethod*>(this); }

    virtual generic_member_func_ptr getGenericMemberFunctionPointer() const = 0;

protected:
    void                setVirtualTableIndex(int index) { o_assert(m_iVirtualTableIndex == -1); m_iVirtualTableIndex = index; }

protected:
    int            m_iVirtualTableIndex;

};

o_h_end


#else // o_phantom_reflection_InstanceMethod_h__
#include "InstanceMethod.classdef.h"
#endif
