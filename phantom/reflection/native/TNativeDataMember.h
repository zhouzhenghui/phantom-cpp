/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TNativeDataMember_h__
#define o_phantom_reflection_native_TNativeDataMember_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename t_ContentType>
class TNativeDataMember : public DataMember
{
public:
    typedef TNativeDataMember<t_Ty, t_ContentType> self_type;
    typedef t_ContentType (t_Ty::*data_member_pointer_t);
    typedef o_NESTED_TYPE boost::remove_const<t_ContentType>::type t_ContentTypeNoConst;
    typedef o_NESTED_TYPE canonical_meta_class_type_of<t_ContentTypeNoConst>::type meta_value_type;

public:
    TNativeDataMember(Type* a_pContentType, const string& a_strName, data_member_pointer_t a_member_field_pointer, Range* a_pRange, uint a_uiSerializationMask, modifiers_t a_uiModifiers = 0 )
        : DataMember(a_pContentType
                            , a_strName
                            , (size_t)const_cast<t_ContentTypeNoConst*>(&(((t_Ty const*)nullptr)->*a_member_field_pointer))
                            , a_pRange
                            , a_uiSerializationMask
                            , a_uiModifiers|o_native)
     , m_member_field_pointer(a_member_field_pointer)
    {}

    virtual void*        getAddress( void const* a_pObject ) const
    {
        return
            const_cast<t_ContentTypeNoConst*>
            (
                &(static_cast<t_Ty const*>(a_pObject)->*m_member_field_pointer)
            );
    }
    virtual void        getValue( void const* a_pObject, void* dest ) const
    {
        value_getter<t_ContentType>::apply(dest, const_cast<t_Ty*>(reinterpret_cast<t_Ty const*>(a_pObject))->*m_member_field_pointer) ;
    }
    virtual void        setValue( void* a_pObject, void const* src ) const
    {
        value_setter<t_ContentType>::apply(src, reinterpret_cast<t_Ty*>(a_pObject)->*m_member_field_pointer);
    }

    void serializeValue( void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        phantom::serializer<t_ContentType>::serialize(static_cast<meta_value_type*>(getValueType()),
            &(static_cast<t_Ty const*>(a_pInstance)->*m_member_field_pointer)
            , a_pOutBuffer
            , a_uiSerializationMask, a_pDataBase);
    }

    void serializeValue( void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pInstance);
        while(a_uiCount--)
        {
            phantom::serializer<t_ContentType>::serialize(static_cast<meta_value_type*>(getValueType()),
                &(reinterpret_cast<t_Ty const*>(pChunk)->*m_member_field_pointer)
                , a_pOutBuffer
                , a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    
    void deserializeValue( void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        phantom::serializer<t_ContentType>::deserialize(static_cast<meta_value_type*>(getValueType()),
            &(static_cast<t_Ty*>(a_pInstance)->*m_member_field_pointer)
            , a_pInBuffer
            , a_uiSerializationMask, a_pDataBase);
    }

    void deserializeValue( void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pInstance);
        while(a_uiCount--)
        {
            phantom::serializer<t_ContentType>::deserialize(static_cast<meta_value_type*>(getValueType()),
                &(reinterpret_cast<t_Ty*>(pChunk)->*m_member_field_pointer)
                , a_pInBuffer
                , a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    void serializeValue( void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        property_tree value_tree;
        
        m_pValueType->serialize(
            &(static_cast<t_Ty const*>(a_pInstance)->*m_member_field_pointer)
            , value_tree
            , a_uiSerializationMask, a_pDataBase);
        a_OutBranch.add_child(m_strName, value_tree);
    }

    void serializeValue( void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        while(a_uiCount--)
        {
            // TODO : correct this
            property_tree value_tree;
            m_pValueType->serialize(
                &(reinterpret_cast<t_Ty const*>(pChunk)->*m_member_field_pointer)
                , value_tree
                , a_uiSerializationMask, a_pDataBase);
            a_OutBranch.add_child(m_strName, value_tree);
            pChunk += a_uiChunkSectionSize;
        }
    }

    void deserializeValue( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        boost::optional<const property_tree&> value_tree_opt = a_InBranch.get_child_optional(m_strName);
        if(value_tree_opt.is_initialized())
        {
            m_pValueType->deserialize(
                &(static_cast<t_Ty*>(a_pInstance)->*m_member_field_pointer)
                , *value_tree_opt
                , a_uiSerializationMask, a_pDataBase);
        }
    }

    void deserializeValue( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            // TODO : correct this ... all values will taken from the same tag... bad me, baaad
            boost::optional<const property_tree&> value_tree_opt = a_InBranch.get_child_optional(m_strName);
            if(value_tree_opt.is_initialized())
            {
                m_pValueType->deserialize(
                    &(reinterpret_cast<t_Ty*>(pChunk)->*m_member_field_pointer)
                    , *value_tree_opt
                    , a_uiSerializationMask, a_pDataBase);
            }
            pChunk += a_uiChunkSectionSize;
        }
    }

    void rememberValue( void const* a_pInstance, byte*& a_pOutBuffer ) const
    {
        phantom::resetter<t_ContentType>::remember(static_cast<meta_value_type*>(getValueType()),
            &(static_cast<t_Ty const*>(a_pInstance)->*m_member_field_pointer)
            , a_pOutBuffer);
    }

    void rememberValue( void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer ) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pInstance);
        while(a_uiCount--)
        {
            phantom::resetter<t_ContentType>::remember(static_cast<meta_value_type*>(getValueType()),
                &(reinterpret_cast<t_Ty const*>(pChunk)->*m_member_field_pointer)
                , a_pOutBuffer);
            pChunk += a_uiChunkSectionSize;
        }
    }

    void resetValue( void* a_pInstance, byte const*& a_pInBuffer ) const
    {
        phantom::resetter<t_ContentType>::reset(static_cast<meta_value_type*>(getValueType()),
            &(static_cast<t_Ty*>(a_pInstance)->*m_member_field_pointer)
            , a_pInBuffer);
    }

    void resetValue( void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer ) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pInstance);
        while(a_uiCount--)
        {
            phantom::resetter<t_ContentType>::reset(static_cast<meta_value_type*>(getValueType()),
                &(reinterpret_cast<t_Ty*>(pChunk)->*m_member_field_pointer)
                , a_pInBuffer);
            pChunk += a_uiChunkSectionSize;
        }
    }

    data_member_pointer_t    m_member_field_pointer;
};

template<typename t_Ty, typename t_ContentType>
class TNativeDataMember<t_Ty, t_ContentType const>
    : public TNativeDataMember<t_Ty,t_ContentType>
{
public:
    typedef TNativeDataMember<t_Ty, t_ContentType const> self_type;
    typedef t_ContentType const (t_Ty::*data_member_pointer_t);

public:
    TNativeDataMember(Type* a_pContentType, const string& a_strName, data_member_pointer_t a_member_field_pointer, Range* a_pRange, uint a_uiSerializationMask, modifiers_t a_uiModifiers = 0)
        : TNativeDataMember<t_Ty,t_ContentType>(a_pContentType, a_strName

        // We manage const-type attributes like no-const-type attributes : we break the const qualifier to be able to force write with "setValue"
        , const_cast<typename TNativeDataMember<t_Ty,t_ContentType>::data_member_pointer_t>(a_member_field_pointer)
        , a_pRange
        , a_uiSerializationMask
        , a_uiModifiers)
    {}

};

o_namespace_end(phantom, reflection, native)

#endif // TNativeDataMember_h__
