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

#ifndef o_phantom_reflection_jit_JitStaticDataMember_h__
#define o_phantom_reflection_jit_JitStaticDataMember_h__



/* ****************** Includes ******************* */
#include <phantom/jit.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection, jit), JitStaticDataMember);
/* *********************************************** */


o_namespace_begin(phantom, reflection, jit)


class o_jit_export JitStaticDataMember : public StaticDataMember
{

public:
    JitStaticDataMember(const string& a_strName, Type* a_pContentType, Range* a_pRange, bitfield a_bfModifiers = bitfield())
        : StaticDataMember(a_strName, a_pContentType, o_dynamic_pool_allocate(a_pContentType->getSize()), a_pRange, a_bfModifiers)
    {

    }
    o_destructor ~JitStaticDataMember(void)     
    {
        o_dynamic_pool_deallocate(m_pAddress, m_pContentType->getSize());
    }

};

o_namespace_end(phantom, reflection, jit)
    
#endif
