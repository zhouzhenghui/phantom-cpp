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
#include <phantom/reflection/Type.h>
#include <phantom/reflection/Type.hxx>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/DataPointerType.hxx>
#include <phantom/reflection/ArrayType.hxx>
#include <phantom/reflection/ReferenceType.hxx>
#include <phantom/reflection/ConstType.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), Type);
o_enumNC((phantom,reflection), (Type), ERelation) (
          e_Relation_None
        , e_Relation_Equal
        , e_Relation_Child
        , e_Relation_Parent
        , e_Relation_GenericContentChild
        , e_Relation_GenericContentParent
    )

o_registerNC((phantom,reflection),(Type),ERelation)

o_namespace_begin(phantom, reflection) 

o_define_meta_type(Type);

Type::Type( ETypeId a_eTypeId ) 
    : LanguageElement()
    , m_eTypeId(a_eTypeId)
    , m_uiSize(0)
    , m_uiSerializedSize(0)
    , m_uiResetSize(0)
    , m_uiAlignment(0)
    , m_pNestedTypes(nullptr)
    , m_pNestedTypedefs(nullptr)
    , m_pExtendedTypes(nullptr)
    , m_pTypedefs(nullptr)
{
    m_uiBuildOrder = NextBuildOrderValue();
}

Type::Type( ETypeId a_eTypeId, const string& a_strName, modifiers_t a_Modifiers /*= 0*/ ) 
    : LanguageElement(a_strName, a_Modifiers)
    , m_eTypeId(a_eTypeId)
, m_uiSize(0)
, m_uiSerializedSize(0)
, m_uiResetSize(0)
, m_uiAlignment(0)
, m_pNestedTypes(nullptr)
, m_pNestedTypedefs(nullptr)
, m_pExtendedTypes(nullptr)
, m_pTypedefs(nullptr)
{
    m_uiBuildOrder = NextBuildOrderValue();
}

Type::Type( ETypeId a_eTypeId, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers /*= 0*/ ) 
    : LanguageElement(a_strName, a_Modifiers)
    , m_eTypeId(a_eTypeId)
    , m_uiSize(a_uiSize)
    , m_uiAlignment(a_uiAlignment)
    , m_uiSerializedSize(a_uiSize)
    , m_uiResetSize(a_uiSize)
    , m_pNestedTypes(nullptr)
    , m_pNestedTypedefs(nullptr)
    , m_pExtendedTypes(nullptr)
    , m_pTypedefs(nullptr)
{
    m_uiBuildOrder = NextBuildOrderValue();
}

Type::~Type()
{

}

o_terminate_cpp(Type)
{
    while(m_pExtendedTypes)
    {
        o_dynamic_delete m_pExtendedTypes->back();
    }
}

Type::ERelation Type::getRelationWith( Type* a_pType ) const
{
    if(a_pType == this) return e_Relation_Equal;
    return e_Relation_None;
}

boolean Type::areValueEqual( void const* a_pSrc0, void const* a_pSrc1 ) const
{
    return memcmp(a_pSrc0, a_pSrc1, m_uiSize) == 0;
}

void Type::removeFromNamespace()
{
    o_assert(m_pOwner);
    getNamespace()->removeType(this);
}

DataPointerType* Type::createDataPointerType() const
{
    return o_new(DataPointerType)(const_cast<Type*>(this));
}

ArrayType* Type::createArrayType(size_t a_uiCount) const
{
    return o_new(ArrayType)(const_cast<Type*>(this), a_uiCount);
}

ReferenceType* Type::createReferenceType() const 
{
    return o_new(ReferenceType)(const_cast<Type*>(this));
}

void* Type::allocate() const
{
    // allocate m_uiSize bytes
    void* memory = o_malloc(m_uiSize);

    // initialize memory to 0xdadadadada.... to recognize it
    memset(memory, 0xda, m_uiSize);
    return memory;
}

void Type::deallocate(void* a_pInstance) const
{
    o_free(a_pInstance);
}

void* Type::allocate(size_t a_uiCount) const
{
    void* pAllocation = o_malloc(a_uiCount*m_uiSize); 

    // initialize memory to 0xdadadadada.... to recognize it
    memset(pAllocation, 0xda, m_uiSize*a_uiCount);
    return pAllocation;
}

void Type::deallocate(void* a_pChunk, size_t a_uiCount) const
{
    o_free(a_pChunk);
}

void* Type::newInstance() const
{
    void* pInstance = allocate(m_uiSize); 
    return pInstance;
}

void Type::deleteInstance(void* a_pInstance) const
{
    deallocate(a_pInstance); 
}

Namespace* Type::getNamespace() const
{
    return m_pOwner ? m_pOwner->asNamespace() : nullptr;
}

Type* Type::getOwnerType() const
{
    return m_pOwner ? m_pOwner->asType() : nullptr;
}

void Type::addNestedTypedef( const string& a_strTypedef, Type* a_pType )
{
    if(m_pNestedTypedefs == nullptr)
    {
        m_pNestedTypedefs = new nested_typedef_map;
    }
    o_assert(m_pNestedTypedefs->find(a_strTypedef) == m_pNestedTypedefs->end(), "Typedef already registered");
    (*m_pNestedTypedefs)[a_strTypedef] = a_pType;
}

void Type::removeNestedTypedef( const string& a_strTypedef, Type* a_pType )
{
    o_assert(m_pNestedTypedefs);
    auto found = m_pNestedTypedefs->find(a_strTypedef);
    o_assert( found != m_pNestedTypedefs->end(), "Typedef not found");
    m_pNestedTypedefs->erase(found);
    if(m_pNestedTypedefs->empty()) 
    {
        delete m_pNestedTypedefs;
        m_pNestedTypedefs = nullptr;
    }
}

inline Type* Type::getNestedTypedef( const string& a_strTypedef ) const
{
    if(m_pNestedTypedefs == nullptr) return nullptr;
    auto found = m_pNestedTypedefs->find(a_strTypedef);
    if( found != m_pNestedTypedefs->end() ) return found->second;
    return nullptr;
}

void Type::addNestedType( Type* a_pType )
{
    addElement(a_pType);
}

void Type::removeNestedType( Type* a_pType )
{
    removeElement(a_pType);
}

void Type::elementAdded(LanguageElement* a_pElement)
{
    LanguageElement::elementAdded(a_pElement);
    Type* pType = a_pElement->asType();
    if(pType)
    {
        if(m_pNestedTypes == NULL)
        {
            m_pNestedTypes = new vector<Type*>;
        }
        o_assert(std::find(m_pNestedTypes->begin(), m_pNestedTypes->end(), pType) == m_pNestedTypes->end(), "Type already added");
        m_pNestedTypes->push_back(pType);
    }
}

void Type::elementRemoved(LanguageElement* a_pElement)
{
    LanguageElement::elementRemoved(a_pElement);
    Type* pType = a_pElement->asType();
    if(pType)
    {
        o_assert(m_pNestedTypes);
        o_assert(pType->m_pOwner == this, "Type doesn't belong to this type");
        if(std::find(m_pNestedTypes->begin(), m_pNestedTypes->end(), pType) != m_pNestedTypes->end())
        {
            m_pNestedTypes->erase(std::find(m_pNestedTypes->begin(), m_pNestedTypes->end(), pType));
            if(m_pNestedTypes->size() == 0)
            {
                delete m_pNestedTypes;
                m_pNestedTypes = nullptr;
            }
        }
    }
}

#if o__bool__use_kind_creation_signal
void                Type::fireKindCreated(void* a_pObject) 
{
    o_emit kindCreated(a_pObject);
}
#endif

#if o__bool__use_kind_destruction_signal
void                Type::fireKindDestroyed(void* a_pObject) 
{
    o_emit kindDestroyed(a_pObject);
}

#endif



#if o__bool__use_kind_creation_signal

phantom::signal_t Type::kindCreated(void* a_pInstance)
{
    phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_kindCreated.head();
    while(pSlot)
    {
        phantom::connection::pair::push(this, pSlot);
        void* args[] = { (void*)(&a_pInstance) };
        pSlot->subroutine()->call( pSlot->receiver(), args );
        pSlot = pSlot->next();
        phantom::connection::pair::pop();
    }
    return phantom::signal_t();
}

#endif

#if o__bool__use_kind_destruction_signal
phantom::signal_t Type::kindDestroyed(void* a_pInstance)
{
    phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_kindDestroyed.head();
    while(pSlot)
    {
        phantom::connection::pair::push(this, pSlot);
        void* args[] = { (void*)(&a_pInstance) };
        pSlot->subroutine()->call( pSlot->receiver(), args );
        pSlot = pSlot->next();
        phantom::connection::pair::pop();
    }
    return phantom::signal_t();
}
#endif

void Type::convertValueTo( Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue ) const
{
    if(a_pDestType->removeConst() == this)
    {
        copy(a_pDestValue, a_pSrcValue);
    }
    // By default just copy
    else 
    {
        ClassType* pClassType = a_pDestType->asClassType();
        o_assert(pClassType);
        Constructor* pConstructor = pClassType->getConstructor(const_cast<Type*>(this), nullptr, 0);
        o_assert(pConstructor);
        void* pBuffer = a_pDestType->allocate();
        void* args[1] = {(void*)a_pSrcValue};
        pConstructor->call(pBuffer, args); // construct the temp buffer
        a_pDestType->copy(a_pDestValue, pBuffer);
        a_pDestType->destroy(pBuffer); // destroy the temp buffer
        a_pDestType->deallocate(pBuffer);
    }
}

boolean Type::isConvertibleTo( Type* a_pType ) const
{
    if(a_pType->removeConst() == removeConst()) return true;
    return isImplicitlyConvertibleTo(a_pType);
}

boolean Type::isImplicitlyConvertibleTo( Type* a_pType ) const
{
    if (a_pType == this) return true;
    
    // if a_pType is a const reference, it is possible to convert to it via a temporary constructed buffer
    a_pType = (a_pType->asReferenceType() AND a_pType->asReferenceType()->getReferencedType()->asConstType()) ? a_pType->removeConstReference() : a_pType;
    if (a_pType == this) return true;
    
    return (a_pType->asClassType() != nullptr) 
                AND (a_pType->asClassType()->getConstructor(const_cast<Type*>(this), nullptr, 0) != nullptr);
}

void Type::aligner::construct( Type* a_pType )
{
    a_pType->construct(m_pStartAddress+m_WrittenBytes);
    size_t alignment = a_pType->m_uiAlignment;
    if(alignment > m_MaxAlignment)
    {
        m_MaxAlignment = alignment;
    }
    
    size_t modulo = m_WrittenBytes % alignment;
    if(modulo)
        m_WrittenBytes += (alignment - modulo);
    
    m_WrittenBytes += a_pType->m_uiSize;
}

void Type::aligner::safeConstruct( Type* a_pType )
{
    a_pType->safeConstruct(m_pStartAddress+m_WrittenBytes);
    size_t alignment = a_pType->m_uiAlignment;
    if(alignment > m_MaxAlignment)
    {
        m_MaxAlignment = alignment;
    }

    size_t modulo = m_WrittenBytes % alignment;
    if(modulo)
        m_WrittenBytes += (alignment - modulo);

    m_WrittenBytes += a_pType->m_uiSize;
}

void Type::aligner::destroy( Type* a_pType )
{
    a_pType->destroy(m_pStartAddress+m_WrittenBytes);
    size_t alignment = a_pType->m_uiAlignment;
    if(alignment > m_MaxAlignment)
    {
        m_MaxAlignment = alignment;
    }
    
    size_t modulo = m_WrittenBytes % alignment;
    if(modulo)
        m_WrittenBytes += (alignment - modulo);
    
    m_WrittenBytes += a_pType->m_uiSize;
}

void Type::aligner::push( Type* a_pType, byte* a_pValueBytes )
{
    memcpy(m_pStartAddress+m_WrittenBytes, a_pValueBytes, a_pType->m_uiSize);
    size_t alignment = a_pType->m_uiAlignment;
    if(alignment > m_MaxAlignment)
    {
        m_MaxAlignment = alignment;
    }
    
    size_t modulo = m_WrittenBytes % alignment;
    if(modulo)
        m_WrittenBytes += (alignment - modulo);
    
    m_WrittenBytes += a_pType->m_uiSize;
}

void Type::aligner::skip( Type* a_pType )
{
    size_t alignment = a_pType->m_uiAlignment;
    if(alignment > m_MaxAlignment)
    {
        m_MaxAlignment = alignment;
    }


    size_t modulo = m_WrittenBytes % alignment;
    if(modulo)
        m_WrittenBytes += (alignment - modulo);

    m_WrittenBytes += a_pType->m_uiSize;
}

byte* Type::aligner::terminate()
{
    size_t modulo = m_WrittenBytes % m_MaxAlignment;
    if(modulo)
        return m_pStartAddress + (m_MaxAlignment - modulo);

    return m_pStartAddress+m_WrittenBytes;
}


size_t Type::alignment::computer::push( Type* a_pType )
{
    size_t alignment = a_pType->m_uiAlignment;
    if(alignment > m_MaxAlignment)
    {
        m_MaxAlignment = alignment;
    }
        
    size_t modulo = m_Result % alignment;
    if(modulo)
        m_Result += (alignment - modulo);
        
    size_t offset = m_Result;
    m_Result += a_pType->m_uiSize;
    return offset;
}


size_t Type::alignment::computer::compute()
{
    if(m_Result == 0 OR m_MaxAlignment == 0) return 0;
    size_t modulo = m_Result % m_MaxAlignment;
    if(modulo)
        m_Result += (m_MaxAlignment - modulo);
        
    return m_Result;
}

void Type::getElements( vector<LanguageElement*>& out, Class* a_pClass ) const
{
    LanguageElement::getElements(out, a_pClass);
    if(m_pNestedTypes AND (a_pClass == nullptr OR typeOf<Type>()->isKindOf(a_pClass)))
    {
        for(auto it = m_pNestedTypes->begin(); it != m_pNestedTypes->end(); ++it)
        {
            out.push_back(*it);
        }
    }
}

void Type::smartCopy( reflection::Type* a_pDestType, void* a_pDest, void const* a_pSource ) const
{
    if(a_pDestType == this)
        copy(a_pDest, a_pSource);
}

Type* Type::getCommonAncestor( Type* a_pType ) const
{
    o_assert(a_pType);
    Type* pCommonType = const_cast<Type*>(this);
    Class::ERelation relationType = this->getRelationWith(a_pType);
    switch(relationType)
    {
    case Class::e_Relation_Equal:
    case Class::e_Relation_Parent:
        {
            // Keep same type
        }
        break;
    case Class::e_Relation_Compatible:
    case Class::e_Relation_GenericContentChild:
    case Class::e_Relation_GenericContentParent:
        {
            // Not used
        }
        break;
    case Class::e_Relation_Child:
        {
            pCommonType = a_pType;
        }
        break;
    default:
        {
            pCommonType = NULL;

            Class* class1 = this->asClass();
            Class* class2 = a_pType->asClass();
            if (class1 AND class2)
            {
                uint uiBaseClassCount = class1->getBaseClassCount();
                if (uiBaseClassCount > 0)
                {
                    for (uint i = 0; i < uiBaseClassCount AND pCommonType == NULL; i++)
                    {
                        pCommonType = class1->getBaseClass(i)->getCommonAncestor(a_pType);						
                    }
                }

                uiBaseClassCount = class2->getBaseClassCount();
                if (uiBaseClassCount > 0)
                {
                    for (uint i = 0; i < uiBaseClassCount AND pCommonType == NULL; i++)
                    {
                        pCommonType = this->getCommonAncestor(class2->getBaseClass(i));						
                    }
                }
            }
        }
        break;
    }

    return pCommonType;
}

void Type::moduleChanged( Module* a_pModule )
{
    if(m_pExtendedTypes && a_pModule) 
    {
        for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
        {
            a_pModule->addLanguageElement(*it);
        }
    }
    LanguageElement::moduleChanged(a_pModule);
}

DataPointerType* Type::getDataPointerType() const
{
    if(m_pExtendedTypes == nullptr) return nullptr;
    for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
    {
        DataPointerType* pDataPointerType = (*it)->asDataPointerType();
        if(pDataPointerType) return pDataPointerType;
    }
    return nullptr;
}

ReferenceType* Type::getReferenceType() const
{
    if(m_pExtendedTypes == nullptr) return nullptr;
    for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
    {
        ReferenceType* pDataPointerType = (*it)->asReferenceType();
        if(pDataPointerType) return pDataPointerType;
    }
    return nullptr;
}

ArrayType* Type::getArrayType( size_t a_uiCount ) const
{
    if(m_pExtendedTypes == nullptr) return nullptr;
    for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
    {
        ArrayType* pArrayType = (*it)->asArrayType();
        if(pArrayType && pArrayType->getElementCount() == a_uiCount) return pArrayType;
    }
    return nullptr;
}

ConstType* Type::getConstType() const
{
    if(m_pExtendedTypes == nullptr) return nullptr;
    for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
    {
        ConstType* pConstType = (*it)->asConstType();
        if(pConstType) return pConstType;
    }
    return nullptr;
}

DataPointerType* Type::pointerType() const
{
    if(this == nullptr) return nullptr;
    if(m_pExtendedTypes == nullptr)
    {
        m_pExtendedTypes = new type_container;
    }
    DataPointerType* pType = getDataPointerType();
    if(pType == nullptr)
    {
        pType = createDataPointerType();
        if(pType == nullptr) return nullptr;
        m_pExtendedTypes->push_back(pType);
        if(m_pModule)
        {
            m_pModule->addLanguageElement(pType);
        }
        if(getNamespace())
        {
            getNamespace()->addType(pType);
        }
        else if(m_pOwner && m_pOwner->asType())
        {
            m_pOwner->asType()->addNestedType(pType);
        }
    }
    return pType;
}

ReferenceType* Type::referenceType() const
{
    if(this == nullptr) return nullptr;
    if(m_pExtendedTypes == nullptr)
    {
        m_pExtendedTypes = new type_container;
    }
    ReferenceType* pType = getReferenceType();
    if(pType == nullptr)
    {
        pType = createReferenceType();
        if(pType == nullptr) return nullptr;
        m_pExtendedTypes->push_back(pType);
        if(m_pModule)
        {
            m_pModule->addLanguageElement(pType);
        }
        if(getNamespace())
        {
            getNamespace()->addType(pType);
        }
        else if(m_pOwner && m_pOwner->asType())
        {
            m_pOwner->asType()->addNestedType(pType);
        }
    }
    return pType;
}

ArrayType* Type::arrayType( size_t a_uiCount ) const
{
    if(this == nullptr) return nullptr;
    if(m_pExtendedTypes == nullptr)
    {
        m_pExtendedTypes = new type_container;
    }
    ArrayType* pType = getArrayType(a_uiCount);
    if(pType == nullptr)
    {
        pType = createArrayType(a_uiCount);
        if(pType == nullptr) return nullptr;
        m_pExtendedTypes->push_back(pType);
        if(m_pModule)
        {
            m_pModule->addLanguageElement(pType);
        }
        if(getNamespace())
        {
            getNamespace()->addType(pType);
        }
        else if(m_pOwner && m_pOwner->asType())
        {
            m_pOwner->asType()->addNestedType(pType);
        }
    }
    return pType;
}

ConstType* Type::constType() const
{
    if(this == nullptr) return nullptr;
    if(m_pExtendedTypes == nullptr)
    {
        m_pExtendedTypes = new type_container;
    }
    ConstType* pType = getConstType();
    if(pType == nullptr)
    {
        pType = createConstType();
        if(pType == nullptr) return nullptr;
        m_pExtendedTypes->push_back(pType);
        if(m_pModule)
        {
            m_pModule->addLanguageElement(pType);
        }
        if(getNamespace())
        {
            getNamespace()->addType(pType);
        }
        else if(m_pOwner && m_pOwner->asType())
        {
            m_pOwner->asType()->addNestedType(pType);
        }
    }
    return pType;
}

Type* Type::pointerType( size_t a_uiPointerLevel ) const
{
    if(a_uiPointerLevel == 0) return (Type*)this;
    return pointerType()->pointerType(a_uiPointerLevel-1);
}

void Type::registerTypedef( Namespace* a_pNamespace, const string& a_strTypedefName )
{
    if(m_pTypedefs == nullptr)
    {
        m_pTypedefs = new typedef_namespace_map;
    }
    (*m_pTypedefs)[a_pNamespace].push_back(a_strTypedefName);
}

void Type::unregisterTypedef( Namespace* a_pNamespace, const string& a_strTypedefName )
{
    auto& vec = (*m_pTypedefs)[a_pNamespace];
    vec.erase(std::find(vec.begin(), vec.end(), a_strTypedefName));
    if(vec.empty())
        m_pTypedefs->erase(a_pNamespace);
    if(m_pTypedefs->empty())
    {
        delete m_pTypedefs;
        m_pTypedefs = nullptr;
    }
}

void Type::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pExtendedTypes)
    {
        auto found = std::find(m_pExtendedTypes->begin(), m_pExtendedTypes->end(), a_pElement);
        if(found != m_pExtendedTypes->end())
        {
            m_pExtendedTypes->erase(found);
            if(m_pExtendedTypes->empty())
            {
                delete m_pExtendedTypes;
                m_pExtendedTypes = nullptr;
            }
        }
    }
    LanguageElement::referencedElementRemoved(a_pElement);
}

void Type::construct( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    byte* pChunk = (byte*)a_pChunk;
    while(a_uiCount--)
    {
        construct(pChunk);
        pChunk += a_uiChunkSectionSize;
    }
}

void Type::destroy( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    byte*    chunk_address = reinterpret_cast<byte*>(a_pChunk);
    while(a_uiCount--)
    {
        destroy(a_pChunk);
        chunk_address += a_uiChunkSectionSize;
    }
}

ConstType* Type::createConstType() const
{
    return o_new(ConstType)(const_cast<Type*>(this));
}

void Type::install( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const rtti_data* a_pOwner /*= 0 */ ) const
{
    byte* pChunk = (byte*)a_pChunk;
    while(a_uiCount--)
    {
        install(pChunk);
        pChunk += a_uiChunkSectionSize;
    }
}
     
void Type::uninstall( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel /*= 0 */ ) const
{
    byte* pChunk = (byte*)a_pChunk;
    while(a_uiCount--)
    {
        uninstall(pChunk);
        pChunk += a_uiChunkSectionSize;
    }
}

void Type::initialize( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    byte* pChunk = (byte*)a_pChunk;
    while(a_uiCount--)
    {
        initialize(pChunk);
        pChunk += a_uiChunkSectionSize;
    }
}

void Type::terminate( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    byte* pChunk = (byte*)a_pChunk;
    while(a_uiCount--)
    {
        terminate(pChunk);
        pChunk += a_uiChunkSectionSize;
    }
}

void Type::valueToLiteral( string& s, const void* src ) const
{
    valueToString(s, src);
}

void Type::setOwnerByQualifiedDecoratedName( string a_Owner )
{
    if(a_Owner.empty()) 
        return;
    LanguageElement* pElement = phantom::elementByName(a_Owner);
    if(pElement)
    {
        if(pElement->asType())
        {
           pElement->asType()->addNestedType(this);
        }
        else if(pElement->asNamespace())
        {
            pElement->asNamespace()->addType(this);
        }
    }
    else 
    {
        if(a_Owner.find("::") == 0)
        {
            globalNamespace()->findOrCreateNamespaceCascade(a_Owner.substr(2))->addType(this);
        }
    }
}

void Type::removeExtendedType( Type* a_pType )
{
    o_assert(m_pExtendedTypes);
    m_pExtendedTypes->erase(std::find(m_pExtendedTypes->begin(), m_pExtendedTypes->end(), a_pType));
    if(m_pExtendedTypes->empty())
    {
        delete m_pExtendedTypes;
        m_pExtendedTypes = nullptr;
    }
}

bool Type::referencesData(const void* a_pInstance, const phantom::data& a_Data) const 
{
    o_unused(a_pInstance); o_unused(a_Data); 
    return false; 
}

bool Type::matches( const string& a_strName, const vector<LanguageElement*>* a_pTemplateSignature, modifiers_t modifiers = 0 ) const
{
    if((a_pTemplateSignature AND m_pTemplateSpecialization == nullptr)
        OR (a_pTemplateSignature == nullptr AND m_pTemplateSpecialization)
        OR (m_strName != a_strName)
        OR (m_Modifiers&modifiers) != modifiers) return false;
    return a_pTemplateSignature ? m_pTemplateSpecialization->matches(a_pTemplateSignature) : true;
}

o_namespace_end(phantom, reflection)


