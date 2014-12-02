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

#ifndef o_phantom_reflection_native_TNativeConstructorBase_h__
#define o_phantom_reflection_native_TNativeConstructorBase_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Class>
class TNativeConstructorBase : public Constructor
{
public:
    typedef void (t_Class::*simplest_member_function_ptr)();
    TNativeConstructorBase(const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers)
    {

    }
    virtual bool isNative() const { return true; }
    virtual void call( void* a_pCaller, void** a_pArgs ) const = 0;
    virtual void call( void* a_pCaller, void** a_pArgs, void* a_pReturnAddress ) const { call(a_pCaller, a_pArgs); }
    virtual void call( void** a_pArgs ) const
    {
        void* caller = *(void**)(*a_pArgs++);
        call( caller, a_pArgs);
    }
    virtual void call( void** a_pArgs, void* a_pReturnAddress ) const
    {
        void* caller = *(void**)(*a_pArgs++);
        call( caller, a_pArgs, a_pReturnAddress);
    }
};


o_namespace_end(phantom, reflection, native)


    /*o_traits_specialize_all_base_traitNTB(
    (phantom,reflection,native)
    , (typename)
    , (t_Ty)
    , TNativeConstructorBase
    , (Constructor)
    )*/

#endif // reflection_native_TNativeConstructorBase_h__