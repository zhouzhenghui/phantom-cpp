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
#include <phantom/reflection/InstanceDataMemberAccess.h>
#include <phantom/reflection/InstanceDataMemberAccess.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), InstanceDataMemberAccess);

o_namespace_begin(phantom, reflection) 

InstanceDataMemberAccess::InstanceDataMemberAccess( Expression* a_pLeftExpression, InstanceDataMember* a_pInstanceDataMember ) 
    : Expression(a_pInstanceDataMember->getValueType(), a_pInstanceDataMember->getName() + "." + a_pInstanceDataMember->getName()
                        
                        , a_pInstanceDataMember->getModifiers())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pInstanceDataMember(a_pInstanceDataMember)
{
    o_assert(m_pLeftExpression->isAddressable());
    addElement(a_pLeftExpression);
    addReferencedElement(m_pInstanceDataMember);
}

void InstanceDataMemberAccess::referencedElementRemoved( LanguageElement* a_pElement )
{
    Expression::referencedElementRemoved(a_pElement);
    if(m_pInstanceDataMember == a_pElement)
        m_pInstanceDataMember = nullptr;
}

o_namespace_end(phantom, reflection)