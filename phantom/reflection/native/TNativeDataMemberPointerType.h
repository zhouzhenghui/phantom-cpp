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

#ifndef o_phantom_reflection_native_TNativeDataMemberPointerType_h__
#define o_phantom_reflection_native_TNativeDataMemberPointerType_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Any>
class TNativeDataMemberPointerType;

template<typename t_Ty, typename t_ValueTy>
class TNativeDataMemberPointerType<t_ValueTy (t_Ty::*)> : public DataMemberPointerType
{
public:
    typedef TNativeDataMemberPointerType<t_Ty, t_ValueTy> self_type;
    typedef t_ValueTy (t_Ty::*data_member_pointer_t);
    typedef o_NESTED_TYPE boost::remove_const<t_ValueTy>::type t_ValueTyNoConst;
    typedef o_NESTED_TYPE canonical_meta_class_type_of<t_ValueTyNoConst>::type meta_value_type;

public:
    TNativeDataMemberPointerType()
        : DataMemberPointerType(typeOf<t_Ty>(), typeOf<t_ValueTy>(), sizeof(data_member_pointer_t), boost::alignment_of<data_member_pointer_t>::value, o_native)
    {}

    virtual void*        getAddress( void* a_pPointer, void const* a_pObject ) const
    {
        return
            const_cast<t_ValueTyNoConst*>
            (
                &(static_cast<t_Ty const*>(a_pObject)->*(*static_cast<data_member_pointer_t*>(a_pPointer)))
            );
    }

    virtual size_t      getOffset(void* a_pPointer) const 
    {
        return (size_t)const_cast<t_ValueTyNoConst*>(&(((t_Ty const*)nullptr)->*(*static_cast<data_member_pointer_t*>(a_pPointer)));
    }

    virtual void        getValue( void* a_pPointer, void const* a_pObject, void* dest ) const
    {
        value_getter<t_ValueTy>::apply(dest, const_cast<t_Ty*>(reinterpret_cast<t_Ty const*>(a_pObject))->*(*static_cast<data_member_pointer_t*>(a_pPointer))) ;
    }
    virtual void        setValue( void* a_pPointer, void* a_pObject, void const* src ) const
    {
        value_setter<t_ValueTy>::apply(src, reinterpret_cast<t_Ty*>(a_pObject)->*(*static_cast<data_member_pointer_t*>(a_pPointer)));
    }
};

o_namespace_end(phantom, reflection, native)

#endif // TNativeDataMemberPointerType_h__
