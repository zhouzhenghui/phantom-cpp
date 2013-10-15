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
/* ** The Class Header must be the last #include * */
#include "SubProperty.h"
/* *********************************************** */
o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

SubProperty::SubProperty( const string& a_strName , Type* a_pContentType , Property* a_pParentProperty , uint a_uiSubOffset , bitfield a_bfModifiers /*= bitfield()*/ ) : Property(a_strName, a_bfModifiers)
, m_uiSubOffset(a_uiSubOffset)
, m_pParentProperty(a_pParentProperty)
, m_pContentType(a_pContentType)
{

}

void SubProperty::getValue( void const* a_pObject, void* dest ) const
{
    byte intermediate_buffer[128];
    m_pParentProperty->getValue(a_pObject, intermediate_buffer);
    memcpy(dest, intermediate_buffer + m_uiSubOffset, m_pContentType->getSize());
}

void SubProperty::setValue( void* a_pObject, void const* src ) const
{
    byte intermediate_buffer[128];
    m_pParentProperty->getValue(a_pObject, intermediate_buffer);
    memcpy(intermediate_buffer+m_uiSubOffset, src, m_pContentType->getSize());
    m_pParentProperty->setValue(a_pObject, intermediate_buffer);
}

o_cpp_end