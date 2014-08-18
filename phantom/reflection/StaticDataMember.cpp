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

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/StaticDataMember.h>
#include <phantom/reflection/StaticDataMember.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), StaticDataMember);

o_namespace_begin(phantom, reflection) 

Class* const StaticDataMember::metaType = o_type_of(phantom::reflection::StaticDataMember);

StaticDataMember::StaticDataMember( const string& a_strName, Type* a_pContentType, void* a_pStaticDataMemberAddress, Range* a_pRange, bitfield a_Modifiers /*= 0*/ ) 
    : StaticVariable( a_pStaticDataMemberAddress, a_pContentType, a_strName, a_pRange, a_Modifiers)
    , m_bAllocated(false)
{
}

StaticDataMember::StaticDataMember( const string& a_strName, Type* a_pContentType, Range* a_pRange, bitfield a_Modifiers /*= 0*/ ) 
    : StaticVariable( a_pContentType->newInstance(), a_pContentType, a_strName, a_pRange, a_Modifiers)
    , m_bAllocated(true)
{

}

o_destructor StaticDataMember::~StaticDataMember( void )
{
    if(m_bAllocated)
    {
        m_pValueType->deleteInstance(m_pAddress);
    }
}

void StaticDataMember::getValue( void const* a_pObject, void* dest ) const
{
    m_pValueType->copy(dest, m_pAddress);
}

void StaticDataMember::setValue( void* a_pObject, void const* src ) const
{
    m_pValueType->copy(m_pAddress, src);
}

o_namespace_end(phantom, reflection)
