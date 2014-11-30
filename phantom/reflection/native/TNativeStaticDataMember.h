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

#ifndef o_phantom_reflection_native_TNativeStaticDataMember_h__
#define o_phantom_reflection_native_TNativeStaticDataMember_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename t_ContentType>
class TNativeStaticDataMember : public StaticDataMember
{
public:
    typedef TNativeStaticDataMember<t_Ty, t_ContentType> self_type;
    
public:
    TNativeStaticDataMember(Type* a_pContentType, const string& a_strName, t_ContentType* a_member_field_pointer, Range* a_pRange, modifiers_t a_uiModifiers = 0)
        : StaticDataMember(a_pContentType, a_strName, a_member_field_pointer, a_pRange, a_uiModifiers|o_native)
    {}
    
    virtual void        getValue( void const* a_pObject, void* dest ) const
    {
        *static_cast<t_ContentType*>(dest) = *static_cast<t_ContentType*>(m_pAddress);
    }
    virtual void        setValue( void* a_pObject, void const* src ) const
    {
        *static_cast<t_ContentType*>(m_pAddress) = *static_cast<t_ContentType const*>(src);
    }
    virtual void        getValue( void* dest ) const
    {
        *static_cast<t_ContentType*>(dest) = *static_cast<t_ContentType*>(m_pAddress);
    }
    virtual void        setValue( void const* src ) const
    {
        *static_cast<t_ContentType*>(m_pAddress) = *static_cast<t_ContentType const*>(src);
    }

};

o_namespace_end(phantom, reflection, native)

#endif // TNativeStaticDataMember_h__