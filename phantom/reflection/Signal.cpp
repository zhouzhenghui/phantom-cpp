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
#include <phantom/reflection/Signal.h>
#include <phantom/reflection/Signal.hxx>
#include "phantom/reflection/Compiler.h"
/* *********************************************** */
o_registerN((phantom, reflection), Signal);

o_namespace_begin(phantom, reflection) 

Class* const Signal::metaType = o_type_of(Signal);

Signal::Signal( const string& a_strName, Signature* a_pSignature, bitfield a_uiModifiers /*= 0*/ ) 
: InstanceMemberFunction(a_strName, a_pSignature, a_uiModifiers|o_slot_member_function)
, m_uiNodeDestructionGuardLevel(0)
, m_uiConnectionCount(0)
, m_uiSlotListDataMemberOffset(~size_t(0))
{
    if(testModifiers(o_virtual))
    {
        o_exception(exception::reflection_runtime_exception, "Signal cannot be virtual");
    }
}

variant Signal::compile( Compiler* a_pCompiler )
{
    return a_pCompiler->compile(this);
}

connection::slot::list* Signal::getSlotList( void* a_pCaller ) const
{
    o_assert( m_uiSlotListDataMemberOffset != 0xffffffff);
    return reinterpret_cast<connection::slot::list*>( ((byte*)a_pCaller) + m_uiSlotListDataMemberOffset );
}

o_namespace_end(phantom, reflection)


