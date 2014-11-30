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
#include <phantom/reflection/ArrayType.h>
#include <phantom/reflection/ArrayType.hxx>
#include "phantom/reflection/ArrayElementAccess.h"
/* *********************************************** */
o_registerN((phantom, reflection), ArrayType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(ArrayType);

ArrayType::ArrayType( Type* a_pElementType, size_t a_uiCount ) 
    : Type(e_array, a_pElementType->getName()
    , a_uiCount*a_pElementType->getSize(), a_pElementType->getAlignment(), a_pElementType->getModifiers())
    , m_pElementType(a_pElementType)
    , m_uiCount(a_uiCount)
{
    o_assert(a_uiCount);
    addReferencedElement(m_pElementType);
}

ArrayType::~ArrayType( void )
{
    if(m_pElementType)
    {
        m_pElementType->removeExtendedType(this);
    }
}

boolean ArrayType::isConvertibleTo( Type* a_pType ) const
{
    return a_pType->asDataPointerType() OR a_pType->asArrayType() OR isImplicitlyConvertibleTo(a_pType);
}

boolean ArrayType::isImplicitlyConvertibleTo( Type* a_pType ) const
{
    if(a_pType == this OR m_pElementType->pointerType()->isImplicitlyConvertibleTo(a_pType)) return true;
    if(a_pType->asArrayType() == nullptr) return false;
    Type*    pElementType = static_cast<ArrayType*>(a_pType)->getElementType();
    if((pElementType->asClass() == nullptr) OR (m_pElementType->asClass() == nullptr)) return false;
    return static_cast<Class*>(pElementType)->isKindOf(static_cast<Class*>(m_pElementType));
}


void ArrayType::serialize( void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    m_pElementType->serialize(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_OutBranch, a_uiSerializationMask, a_pDataBase);
}

void ArrayType::deserialize( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    m_pElementType->deserialize(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_InBranch, a_uiSerializationMask, a_pDataBase);
}

void ArrayType::copy( void* a_pDest, void const* a_pSrc ) const
{
    size_t i = 0;
    size_t storedTypeSize = m_pElementType->getSize();
    for(;i<m_uiCount;++i)
    {
        m_pElementType->copy((byte*)a_pDest + i*storedTypeSize, (byte*)a_pSrc + i*storedTypeSize);
    }
}

void ArrayType::referencedElementRemoved( LanguageElement* a_pElement )
{
    Type::referencedElementRemoved(a_pElement);
    if(m_pElementType == a_pElement)
    {
        m_pElementType->removeExtendedType(this);
        m_pElementType = nullptr;
    }
}

Expression* ArrayType::solveOperator( const string& a_strOperator, const vector<Expression*>& a_Expressions, modifiers_t a_Modifiers ) const
{
    if(a_strOperator == "[]" AND a_Expressions.size() == 2)
    {
        if(a_Expressions[0]->getValueType()->removeReference()->removeConst() == this)
        {
            if(a_Expressions[1]->getValueType()->isConvertibleTo(typeOf<size_t>()))
            {
                if(a_Modifiers & o_const)
                {
                    return o_new(ArrayElementAccess)( constType(), a_Expressions[0], a_Expressions[1]);
                }
                else 
                {
                    return o_new(ArrayElementAccess)( const_cast<ArrayType*>(this), a_Expressions[0], a_Expressions[1]);
                }
            }
        }
    }
    return Type::solveOperator(a_strOperator, a_Expressions, a_Modifiers);
}

void ArrayType::convertValueTo( Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue ) const
{
    if(a_pDestType->asPointerType())
    {
        m_pElementType->pointerType()->convertValueTo(a_pDestType, a_pDestValue, &a_pSrcValue);
    }
    else 
    {

    }
}

void ArrayType::valueFromString(const string& a_str, void* dest) const
{
    *reinterpret_cast<void**>(dest) = ::phantom::lexical_cast<void*>(a_str);
}

void ArrayType::valueToString(string& a_str, const void* src) const
{
    a_str += ::phantom::lexical_cast<string>(*((void**)src));
}

string ArrayType::getDecoratedName() const
{
    return m_pElementType->getDecoratedName()+'['+phantom::lexical_cast<string>(m_uiCount)+']';
}

string ArrayType::getQualifiedDecoratedName() const
{
    return m_pElementType->getQualifiedDecoratedName()+'['+phantom::lexical_cast<string>(m_uiCount)+']';
}

o_namespace_end(phantom, reflection)