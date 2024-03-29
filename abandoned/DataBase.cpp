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
#include <phantom/serialization/Node.h>
#include <phantom/serialization/DataTypeManager.h>
#include <phantom/serialization/Trashbin.h>
#include <phantom/serialization/DataBase.h>
/* *********************************************** */
o_cpp_begin

ReflectionCPP__________________________________________________________________________________
    
    o_signal(dataAdded, (const phantom::data&, Node*))
    o_signal(dataAboutToBeRemoved, (const phantom::data&, Node*))
    o_signal(dataAboutToBeAborted, (const phantom::data&, Node*))
    o_signal(dataMoved, (const phantom::data&, Node*, Node*))
    o_signal(dataAttributeValueChanged, (const phantom::data&, size_t, const string&));
    o_signal(dataReplaced, (const phantom::data&, const phantom::data&));

    o_signal(subDataOwnershipLost, (const phantom::data&));

    o_signal(nodeAdded, (Node*, Node*))
    o_signal(nodeAboutToBeRemoved, (Node*, Node*))
    o_signal(nodeMoved, (Node*, Node*, Node*))
    o_signal(nodeAttributeValueChanged, (Node*, size_t, const string&)); 

    o_signal(dataMarkedAsModified, (const phantom::data&));
    o_signal(dataMarkedAsAdded, (const phantom::data&));
    o_signal(dataMarkedAsRemoved, (const phantom::data&));
    o_signal(dataUnmarkedAsModified, (const phantom::data&));
    o_signal(dataUnmarkedAsAdded, (const phantom::data&));
    o_signal(dataUnmarkedAsRemoved, (const phantom::data&));
    o_signal(nodeMarkedAsModified, (Node*));
    o_signal(nodeUnmarkedAsModified, (Node*));

__________________________________________________________________________________ReflectionCPP
    
DataBase::DataBase( const string& url, uint a_uiSerializationFlag ) 
: m_strUrl(url)
, m_pRootNode(nullptr)
, m_dependency_tester_delegate(&DataBase::defaultDependencyChecker)
, m_dependency_getter_delegate(&DataBase::defaultDependencyGetter)
, m_uiLoadedDataSize(0)
, m_uiLoadedDataResetSize(0)
, m_uiLoadedDataSerializedSize(0)
, m_uiSerializationFlag(a_uiSerializationFlag)
, m_pDataTypeManager(nullptr)
, m_pDataStateBase(nullptr)
, m_pTrashbin(nullptr)
, m_eActionOnMissingType(e_ActionOnMissingType_IgnoreAndDestroyData)
{

}

Trashbin* DataBase::getTrashbin() const
{
	return m_pTrashbin;
}

void DataBase::setTrashbin(Trashbin* a_pTrashbin)
{
	m_pTrashbin = a_pTrashbin;
}

void            DataBase::moveNode(Node* a_pNode, Node* a_pNewParent)
{
    if(NOT(canMoveNode(a_pNode,a_pNewParent))) 
    {
        o_exception(exception::base_exception, "forbidden action");
    }
    Node* pOldParent = a_pNode->getParentNode();
    if(pOldParent == a_pNewParent) return;
    pOldParent->eraseNode(a_pNode);
    moveNodeEntry(a_pNode, a_pNewParent);
    a_pNewParent->storeNode(a_pNode);
    o_emit nodeMoved(a_pNode, pOldParent, a_pNewParent);
}

void            DataBase::moveData(const phantom::data& a_Data, Node* a_pNewOwnerNode)
{
    if(NOT(canMoveData(a_Data,a_pNewOwnerNode)))
    {
        o_exception(exception::base_exception, "forbidden action");
    }
    void* pAddress = a_Data.address();
    uint guid = getGuid(pAddress);
    o_assert(guid != 0xFFFFFFFF);
    Node* pOldOwnerNode = getNode(pAddress);
    if(pOldOwnerNode == a_pNewOwnerNode) return;
    pOldOwnerNode->eraseData(a_Data);
    o_assert(isDataCompatibleWithNode(a_Data, a_pNewOwnerNode));
    moveDataEntry(a_Data, guid, pOldOwnerNode, a_pNewOwnerNode);
    m_DataNodeMap[pAddress] = a_pNewOwnerNode;
    a_pNewOwnerNode->storeData(a_Data);
    o_emit dataMoved(a_Data, pOldOwnerNode, a_pNewOwnerNode);
}

boolean DataBase::defaultDependencyCheckerInContainer( reflection::ContainerClass* a_pContainerClass, void* a_pContainer, const phantom::data& a_Dep )
{
    util::Iterator* pIterator = a_pContainerClass->begin(a_pContainer);

    bool result = false;

    reflection::Type* pType = a_pContainerClass->getValueType();
    if(pType->isDataPointerType())
    {
        void* ptr = nullptr; 
        while(pIterator->hasNext())
        {
            pIterator->next(&ptr);
            phantom::data d(ptr);
            if(NOT(d.isNull()) && d.address() == a_Dep.address())
            {
                result = true;
                break;
            }
        }
    }
    else 
    {
        reflection::ContainerClass* pSubContainerClass = pType->asContainerClass();
        o_assert(pSubContainerClass);
        void* pSubContainer = pSubContainerClass->newInstance();
        while(pIterator->hasNext())
        {
            pIterator->next(pSubContainer);
            if(defaultDependencyCheckerInContainer(pSubContainerClass, pSubContainer, a_Dep))
            {
                result = true;
                break;
            }
        }
        pSubContainerClass->deleteInstance(pSubContainer);
    }

    o_dynamic_delete pIterator;

    return result;
}

boolean DataBase::defaultDependencyCheckerClassType( void* a_SrcAddress, phantom::reflection::ClassType* a_pClassType, const phantom::data& a_Dep )
{
    reflection::Class::member_const_iterator it = a_pClassType->valueMembersBegin();
    reflection::Class::member_const_iterator end = a_pClassType->valueMembersEnd();
    for(; it != end; ++it)
    {
        reflection::ValueMember* pValueMember = static_cast<reflection::ValueMember*>(it->second);
        reflection::Type* pType = pValueMember->getValueType();
        if(pType->isDataPointerType())
        {
            void* ptr = nullptr;
            pValueMember->getValue(a_pClassType->cast(pValueMember->getOwnerClassType(), a_SrcAddress), &ptr);
            phantom::data d(ptr);
            if(NOT(d.isNull()) && d.address() == a_Dep.address())
            {
                return true;
            }
        }
        else 
        {
            reflection::ContainerClass* pContainerClass = pType->asContainerClass();
            if(pContainerClass)
            {
                void* pContainer = pContainerClass->newInstance();
                pValueMember->getValue(a_pClassType->cast(pValueMember->getOwnerClassType(), a_SrcAddress), pContainer);
                boolean result = defaultDependencyCheckerInContainer(pContainerClass, pContainer, a_Dep);
                pContainerClass->deleteInstance(pContainer);
                if(result) return true;
            }
        }
    }
    if(a_pClassType->isClass())
    {
        reflection::Class* pClass = static_cast<reflection::Class*>(a_pClassType);
        size_t i = 0;
        size_t count = pClass->getSuperClassCount();
        for(;i<count;++i)
        {
            byte* pAddress = (byte*)a_SrcAddress + pClass->getSuperClassOffset(i);
            if(defaultDependencyCheckerClassType(pAddress, pClass->getSuperClass(i), a_Dep))
                return true;
        }
    }
    return false;
}

void DataBase::defaultDependencyGetterClassType( void* a_SrcAddress, phantom::reflection::ClassType* a_pClassType, vector<phantom::data>& a_Dependencies )
{
    reflection::Class::member_const_iterator it = a_pClassType->valueMembersBegin();
    reflection::Class::member_const_iterator end = a_pClassType->valueMembersEnd();
    for(; it != end; ++it)
    {
        reflection::ValueMember* pValueMember = static_cast<reflection::ValueMember*>(it->second);
        if(NOT(pValueMember->isTransient()) AND pValueMember->getValueType()->isDataPointerType())
        {
            void* value = NULL;
            pValueMember->getValue(a_SrcAddress, &value);
            if(value != NULL) 
            {
                reflection::Type* pPointedType = static_cast<reflection::DataPointerType*>(pValueMember->getValueType())->getPointedType();
                const phantom::rtti_data& rtti = phantom::rttiDataOf(value);
                a_Dependencies.push_back(rtti.isNull()
                    ? phantom::data(value, pPointedType)
                    : rtti.data());
            }
        }
    }
    if(a_pClassType->isClass())
    {
        reflection::Class* pClass = static_cast<reflection::Class*>(a_pClassType);
        size_t i = 0;
        size_t count = pClass->getSuperClassCount();
        for(;i<count;++i)
        {
            defaultDependencyGetterClassType(
                (byte*)a_SrcAddress + pClass->getSuperClassOffset(i)
                , pClass->getSuperClass(i)
                , a_Dependencies
            );
        }
    }
}

void DataBase::addDataToTrashbin(const phantom::data& a_Data)
{
	o_assert(m_pTrashbin);

	Node* pNode = getNode(a_Data);
	uint uiGuid = getGuid(a_Data);
	m_pTrashbin->addData(a_Data, pNode, uiGuid);
	pNode->removeData(a_Data);
}

void DataBase::removeDataFromTrashbin(uint a_uiGuid)
{
	o_assert(m_pTrashbin);

	phantom::data d = m_pTrashbin->getDataByGuid(a_uiGuid);
	Node* pNode = m_pTrashbin->getNodeOf(d);
	m_pTrashbin->removeDataByGuid(a_uiGuid);
	pNode->addData(d, a_uiGuid);
}

void DataBase::addNodeToTrashbin(Node* a_pNode)
{
	o_assert(m_pTrashbin);

	Node* pParentNode = a_pNode->getParentNode();
	uint uiGuid = a_pNode->getGuid();
	m_pTrashbin->addNode(a_pNode, pParentNode, uiGuid);
	a_pNode->unload();
	pParentNode->removeChildNode(a_pNode);
}

void DataBase::removeNodeFromTrashbin(uint a_uiGuid)
{
	o_assert(m_pTrashbin);

	Node* pNode = m_pTrashbin->getNodeByGuid(a_uiGuid);	
	Node* pParentNode = m_pTrashbin->getNodeOf(pNode);	
	pParentNode->addChildNode(pNode, a_uiGuid);
	pParentNode->getOwnerDataBase()->setNodeAttributeValue(pNode, pParentNode->getOwnerDataBase()->getAttributeIndex("name"), "Node");
	pNode->saveAttributes();
	pNode->load();

	m_pTrashbin->removeNodeByGuid(a_uiGuid);	
}

void DataBase::registerData( const phantom::data& a_Data, uint a_Guid, Node* a_pOwnerNode )
{
    o_assert(hasDataEntry(a_Data, a_Guid, a_pOwnerNode), "Data must have an entry created to be registered");
    o_assert(NOT(isDataRegistered(a_Data.address())), "Data already registered");
    o_assert(a_Guid != e_Constant_InvalidGuidValue);
    o_assert(isDataCompatibleWithNode(a_Data, a_pOwnerNode));
    m_uiLoadedDataSize += a_Data.type()->getSize();
    m_uiLoadedDataResetSize += a_Data.type()->getResetSize();
    m_uiLoadedDataSerializedSize += a_Data.type()->getSerializedSize();
    m_GuidBase.add(a_Guid, a_Data);
    size_t fieldCount = getAttributeCount();
    if(fieldCount)
    {
        string* values = o_allocate_n(fieldCount, string);
        size_t i = 0;
        for(;i<fieldCount;++i)
        {
            new (&values[i]) string();
        }
        o_assert(m_AttributeValues.find(a_Data.address()) == m_AttributeValues.end());
        m_AttributeValues[a_Data.address()] = values;
    }
    m_DataNodeMap[a_Data.address()] = a_pOwnerNode;
}

void DataBase::unregisterData( const phantom::data& a_Data )
{
    o_assert(isDataRegistered(a_Data.address()), "Data not registered");
    unregisterSubDataOwner(a_Data);
    m_uiLoadedDataSize -= a_Data.type()->getSize();
    m_uiLoadedDataResetSize -= a_Data.type()->getResetSize();
    m_uiLoadedDataSerializedSize -= a_Data.type()->getSerializedSize();
    m_GuidBase.remove(a_Data.address());
    size_t fieldCount = getAttributeCount();
    if(fieldCount)
    {
        attribute_map::iterator found = m_AttributeValues.find(a_Data.address());
        string* values = found->second;
        size_t i = 0;
        for(;i<fieldCount;++i)
        {
            values[i].~string();
        }
        o_deallocate_n(values, fieldCount, string);
        m_AttributeValues.erase(found);
    }
    data_node_map::iterator found = m_DataNodeMap.find(a_Data.address());
    o_assert(found != m_DataNodeMap.end());
    m_DataNodeMap.erase(found);
}

void DataBase::registerNode( Node* a_pNode )
{
    o_assert(hasNodeEntry(a_pNode), "Node must have an entry created to be registered");
    o_assert(NOT(isNodeRegistered(a_pNode)), "Node already registered");
    o_assert(a_pNode->getGuid() != e_Constant_InvalidGuidValue);
    m_GuidBase.add(a_pNode->getGuid(), phantom::data(a_pNode, classOf(a_pNode)));
    size_t fieldCount = getAttributeCount();
    if(fieldCount)
    {
        string* values = o_allocate_n(fieldCount, string);
        size_t i = 0;
        for(;i<fieldCount;++i)
        {
            new (&values[i]) string();
        }
        o_assert(m_AttributeValues.find(a_pNode) == m_AttributeValues.end());
        m_AttributeValues[a_pNode] = values;
    }
}

void DataBase::unregisterNode( Node* a_pNode )
{
    o_assert(a_pNode != rootNode(), "Root node cannot be unregistered");
    o_assert(isNodeRegistered(a_pNode), "Node not registered in database");
    m_GuidBase.remove(a_pNode);
    size_t fieldCount = getAttributeCount();
    if(fieldCount)
    {
        attribute_map::iterator found = m_AttributeValues.find(a_pNode);
        string* values = found->second;
        size_t i = 0;
        for(;i<fieldCount;++i)
        {
            values[i].~string();
        }
        o_deallocate_n(values, fieldCount, string);
        m_AttributeValues.erase(found);
    }
    o_assert(a_pNode->getParentNode(), "Node should have a parent");
    Node* pOldParent = a_pNode->getParentNode();
    pOldParent->eraseNode(a_pNode);
}

Node* DataBase::createNewNode( Node* a_pParentNode )
{
    uint guid = generateGuid();
    Node* pNewNode = createNode(guid, a_pParentNode);
    createNodeEntry(pNewNode);
    registerNode(pNewNode);
    pNewNode->save();
    o_emit nodeAdded(pNewNode, a_pParentNode);
    return pNewNode;
}

void DataBase::addNode( Node* a_pNode, Node* a_pParentNode, uint a_uiGuid )
{
	a_pParentNode->storeNode(a_pNode);
	createNodeEntry(a_pNode);	
	registerNode(a_pNode);
	a_pNode->save();
	o_emit nodeAdded(a_pNode, a_pParentNode);
}

void DataBase::deleteNode( Node* a_pNode )
{
    o_emit nodeAboutToBeRemoved(a_pNode, a_pNode->getParentNode());
    uint guid = getGuid(a_pNode);
    o_assert(guid != 0xFFFFFFFF);
    unregisterNode(a_pNode);
    destroyNodeEntry(a_pNode);
    destroyNode(a_pNode);
    releaseGuid(guid);
}

void DataBase::removeNode( Node* a_pNode )
{
	o_emit nodeAboutToBeRemoved(a_pNode, a_pNode->getParentNode());
	uint guid = getGuid(a_pNode);
	o_assert(guid != 0xFFFFFFFF);
	destroyNodeEntry(a_pNode);
	unregisterNode(a_pNode);
	releaseGuid(guid);
}

void DataBase::replaceDataInfo( const phantom::data& a_Old, const phantom::data& a_New )
{
    // Guid base
    uint guid = m_GuidBase.getGuid(a_Old);
    m_GuidBase.remove(a_Old.address());
    m_GuidBase.add(guid, a_New);

    // Parent node
    {
        auto found = m_DataNodeMap.find(a_Old.address());
        o_assert(found != m_DataNodeMap.end());
        Node* pOldNode = found->second;
        m_DataNodeMap.erase(found);
        m_DataNodeMap[a_New.address()] = pOldNode;
    }

    // Owner data
    {
        // Replace sub data entry
        auto found = m_SubDataOwnerMap.find(a_Old.address());
        if(found != m_SubDataOwnerMap.end())
        {
            data oldOwner = found->second;
            m_SubDataOwnerMap.erase(found);
            m_SubDataOwnerMap[a_New.address()] = oldOwner;
        }

        // Replace owner data entry
        auto it = m_SubDataOwnerMap.begin();
        auto end = m_SubDataOwnerMap.end();
        for(;it!=end;++it)
        {
            if(it->second.address() == a_Old.address())
            {
                it->second = a_New;
            }
        }
    }

    // Attributes
    {
        auto found = m_AttributeValues.find(a_Old.address());
        o_assert(found != m_AttributeValues.end());
        string* oldValues = found->second;
        m_AttributeValues.erase(found);
        m_AttributeValues[a_New.address()] = oldValues;
    }

    m_uiLoadedDataSize -= a_Old.type()->getSize();
    m_uiLoadedDataSize += a_New.type()->getSize();
}

void DataBase::setDataTypeManager( DataTypeManager* a_pDataTypeManager )
{
    m_pDataTypeManager = a_pDataTypeManager;
}

reflection::Type* DataBase::solveTypeByName( const string& a_strName ) const
{
    return m_pDataTypeManager 
            ? m_pDataTypeManager->solveTypeByName(a_strName) 
            : phantom::typeByName(a_strName);
}

reflection::Type* DataBase::solveTypeById(uint id) const
{
    o_warning(false, "implementation not complete");
    return m_pDataTypeManager 
        ? m_pDataTypeManager->solveTypeById(id) 
        : nullptr;
}

void DataBase::clearDataReference( const phantom::data& a_data )
{
    vector<void*> layout;
    phantom::rttiLayoutOf(a_data.address(), layout);
    if(layout.empty()) layout.push_back(a_data.address());
    rootNode()->clearDataReferenceCascade(layout);
}

void DataBase::replaceDataReference( const phantom::data& a_old, const phantom::data& a_New ) 
{
    vector<void*> layout;
    phantom::rttiLayoutOf(a_old.address(), layout);
    if(layout.empty()) layout.push_back(a_old.address());
    rootNode()->replaceDataReferenceCascade(layout, a_New);
}
/*
void DataBase::rebuildAllData( reflection::Type* a_pOld, reflection::Type* a_pNew, uint a_uiCurrentState )
{
    vector<data_pair> rebuilt_pairs;
    rootNode()->rebuildAllDataCascade(a_pOld, a_pNew, rebuilt_pairs);

    // First pass : replace data info in database
    {
        auto it = rebuilt_pairs.begin();
        auto end = rebuilt_pairs.end();
        for(;it!=end;++it)
        {
            replaceDataInfo(it->first, it->second);
        }
    }

    vector<phantom::data> subDataWhichHaveLostOwnership;

    // Second pass : reconfigure and reload data
    {
        
        auto it = rebuilt_pairs.begin();
        auto end = rebuilt_pairs.end();
        for(;it!=end;++it)
        {
            phantom::data oldData = it->first;
            phantom::data newData = it->second;

            unconfigure(oldData);

            Node* pNode = getNode(newData);
            // Reload the data
            pNode->loadData(newData);
            restore_state state = restore_incomplete;
            uint pass = 0;
            while(state == restore_incomplete)
            {
                o_assert(pass < 10);
                // extract the data from the queue
                state = newData.type()->restore(newData.address(), m_uiSerializationFlag, pass);
                if(state == restore_failed) // if failed we store the data in the destruction queue which will be handled at the node loading end
                {
                    pNode->abortData(newData);
                    return;
                }
                ++pass;
            }
            configure(newData);

            if(a_uiCurrentState != 0xffffffff)
            {
                // Load the requested state (if defined)
                pNode->loadDataState(newData, a_uiCurrentState);
            }

        }

    }

    // Third pass : check lost ownership 
    {
        auto it = rebuilt_pairs.begin();
        auto end = rebuilt_pairs.end();
        for(;it!=end;++it)
        {
            phantom::data newData = it->second;
            // Check if the sub data interface is still present
            if(NOT(getSubDataOwner(newData).isNull()))
            {
                if(m_pSubDataManager->getCollectionContainingData(newData) == nullptr)
                {
                    subDataWhichHaveLostOwnership.push_back(newData);
                }
            }
        }
    }

    // Fourth pass : notify about replacement
    {
        auto it = rebuilt_pairs.begin();
        auto end = rebuilt_pairs.end();
        for(;it!=end;++it)
        {
            o_emit dataReplaced(it->first, it->second);
        }
    }    


    // Fifth : destroy old data
    {
        auto it = rebuilt_pairs.begin();
        auto end = rebuilt_pairs.end();
        for(;it!=end;++it)
        {
            it->first.destroy();
        }
    }

    // Ensure we have sub data first and their owners after
    sortSubDataFirst(subDataWhichHaveLostOwnership.begin(), subDataWhichHaveLostOwnership.end());

    // Sixth and last pass : erase sub data owner info for data having lost ownership
    {
        auto it = subDataWhichHaveLostOwnership.begin();
        auto end = subDataWhichHaveLostOwnership.end();
        for(;it!=end;++it)
        {
            o_emit subDataOwnershipLost(*it);
            m_SubDataOwnerMap.erase(it->address());
        }
    }

}
*/
void DataBase::replaceDataTypes( const map<reflection::Type*, reflection::Type*>& replacedTypes, uint a_uiCurrentState /*= 0xffffffff*/ )
{
    if(replacedTypes.empty()) return;
    // rebuild and list all replaced data
    vector<data> oldData;
    vector<data> newData;
    {
        auto it = replacedTypes.begin();
        auto end = replacedTypes.end();
        for(;it!=end;++it)
        {
            vector<data_pair> rebuilt_pairs;
            rootNode()->rebuildAllDataCascade(it->first, it->second, oldData, newData);
        }
    }

    o_assert(oldData.size() == newData.size());

    // replace data info in data base
    size_t i = 0;
    size_t count = oldData.size();

    if(count == 0) return;

    for(;i<count;++i)
    {
        replaceDataInfo(oldData[i], newData[i]);
    }

    // list all dependant to these replaced data
    vector<phantom::data> dependantData;
    {
        auto it = oldData.begin();
        auto end = oldData.end();
        for(;it!=end;++it)
        {
            rootNode()->fetchDataWhichDependsOnData(*it, dependantData);
        }
    }
    // remove duplicates from dependant data (sort + unique)
    std::sort(dependantData.begin(), dependantData.end());
    std::unique(dependantData.begin(), dependantData.end());

    // remove from dependant data the old data replaced
    vector<phantom::data> notReplacedDependantData(dependantData.size());
    if(notReplacedDependantData.size())
    {
        vector<data> sortedOldData = oldData;
        std::sort(sortedOldData.begin(), sortedOldData.end());
        auto difference_end = std::set_difference(dependantData.begin(), dependantData.end(), sortedOldData.begin(), sortedOldData.end(), notReplacedDependantData.begin());
        notReplacedDependantData.resize(difference_end - notReplacedDependantData.begin());
    }

    // reloaded data = not replaced dependant + newly build data
    vector<phantom::data> reloadedData = newData;
    reloadedData.insert(reloadedData.end(), notReplacedDependantData.begin(), notReplacedDependantData.end());

    if(reloadedData.empty()) return;
    {
        auto it = reloadedData.begin();
        auto end = reloadedData.end();
        for(;it!=end;++it)
        {
            phantom::data d = *it;
            Node* pNode = getNode(d);
            // Reload the data
            pNode->loadData(d);
        }
    }
    list<data> dataRestoreQueue;
    list<data> dataAbortQueue;
    {
        dataRestoreQueue.insert(dataRestoreQueue.end(), reloadedData.begin(), reloadedData.end());
        uint pass = 0;
        int counter = 0;
        int cycle_count = dataRestoreQueue.size();
        while(cycle_count)
        {
            // extract the data from the queue
            phantom::data d = dataRestoreQueue.front();
            dataRestoreQueue.pop_front();

            restore_state state = d.type()->restore(d.address(), m_uiSerializationFlag, pass);
            switch(state)
            {
            case restore_complete: // if success, we do nothing
                break;
            case restore_incomplete: // if incomplete, we reinject the data at the end of the queue to apply to it another pass later
                dataRestoreQueue.push_back(d);
                break;
            case restore_failed: // if failed we store the data in the destruction queue which will be handled at the node loading end
                dataAbortQueue.push_back(d);
                break;
            default:
                o_assert(false, "state unknown, anormal, probably a segfault somewhere which overrided the restore_state enum value");
                break;
            }
            if((++counter) == cycle_count) // reached the cycle end => increment pass, reset counters
            {
                ++pass;
                cycle_count = dataRestoreQueue.size();
                counter = 0;
            }
        }
    }

    i = 0;
    for(;i<count;++i)
    {
        // update added/removed/modified data 
        {
            auto found = m_ModifiedData.find(oldData[i]);
            if(found != m_ModifiedData.end())
            {
                m_ModifiedData.erase(found);
                m_ModifiedData.insert(newData[i]);
            }
        }
        {
            auto found = m_RemovedData.find(oldData[i]);
            if(found != m_RemovedData.end())
            {
                m_RemovedData.erase(found);
                m_RemovedData.insert(newData[i]);
            }
        }
        {
            auto found = m_AddedData.find(oldData[i]);
            if(found != m_AddedData.end())
            {
                m_AddedData.erase(found);
                m_AddedData.insert(newData[i]);
            }
        }

        o_emit dataReplaced(oldData[i], newData[i]);
    }

    {
        auto it = reloadedData.begin();
        auto end = reloadedData.end();
        for(;it!=end;++it)
        {
            phantom::data d = *it;
            Node* pNode = getNode(d);
            if(pNode) // Data could not exist anymore due to component removal
            {
                pNode->addDataComponents(d);
            }
        }
    }
    if(a_uiCurrentState != 0xffffffff)
    {
        auto it = reloadedData.begin();
        auto end = reloadedData.end();
        for(;it!=end;++it)
        {
            Node* pNode = getNode(*it);
            // Load the requested state (if defined)
            if(pNode) // Data could not exist anymore due to component removal
            pNode->loadDataState(*it, a_uiCurrentState);
        }
    } 

    // Remove and destroy aborted data
    o_foreach(data d, dataAbortQueue)
    {
        Node* pNode = getNode(d);
        pNode->abortData(d);
    }

    // To finish save all
    save();
    if(a_uiCurrentState)
    {
        saveState(a_uiCurrentState);
    }
}

boolean DataBase::canMoveNode( Node* a_pNode, Node* a_pNewParent ) const
{
    Node* pOldParent = a_pNode->getParentNode();
    o_assert(pOldParent);
    vector<Node*> dependentNodes;
    pOldParent->getAllDescendantWhichDependsOn(a_pNode, dependentNodes);
    vector<Node*>::const_iterator it = dependentNodes.begin();
    vector<Node*>::const_iterator end = dependentNodes.end();
    for(;it!=end;++it)
    {
        Node* pNode = *it;
        if(NOT( pNode == a_pNewParent OR pNode->hasParentNodeCascade(a_pNewParent) ))
        {
            return false;
        }
    }
    return true;
}

boolean DataBase::canMoveData( const phantom::data& a_Data, Node* a_pNewParent ) const
{
    Node* pOldParent = getNode(a_Data);
    o_assert(pOldParent);
    vector<Node*> dependentNodes;
    pOldParent->getAllDescendantWhichDependsOn(a_Data, dependentNodes);
    if(pOldParent->containsDataWhichDependsOnData(a_Data))
        dependentNodes.push_back(pOldParent);
    vector<Node*>::const_iterator it = dependentNodes.begin();
    vector<Node*>::const_iterator end = dependentNodes.end();
    for(;it!=end;++it)
    {
        Node* pNode = *it;
        if(NOT( pNode == a_pNewParent OR pNode->hasParentNodeCascade(a_pNewParent) ))
        {
            return false;
        }
    }
    return a_pNewParent->acceptsData(a_Data);
}

void DataBase::terminate()
{
    if(m_pRootNode)
    {
        destroyNode(m_pRootNode);
    }
}

reflection::Collection* DataBase::getCollectionContainingSubData( const phantom::data& d ) const
{
    phantom::data ownerData = getSubDataOwner(d);
    if(ownerData.isNull())
        return nullptr;

    vector<reflection::Collection*> collections;
    if(ownerData.type()->asClass() == nullptr) return nullptr;
    ownerData.type()->asClass()->getAllCollectionCascade(collections);
    auto it = collections.begin();
    auto end = collections.end();
    for(;it!=end;++it)
    {
        reflection::Collection* pCollection = *it;
        if(NOT(pCollection->isComponent())) continue; 
        reflection::DataPointerType* pDataPointerType = pCollection->getElementType()->asDataPointerType();
        if(pDataPointerType == nullptr) continue;
        if(!d.type()->isKindOf(pDataPointerType->getPointedType())) continue;
        void * castedAddress = ownerData.cast(pCollection->getOwner()->asClassType()).address();
        size_t i = 0;
        size_t count = pCollection->getSize(castedAddress);
        for(;i<count;++i)
        {
            void* subData = NULL;
            pCollection->getElement(castedAddress, i, &subData);
            if(subData == d.address())
            {
                return *it;
            }
        }
    }
    return nullptr;
}


void DataBase::markDataAsModified( const phantom::data& a_Data )
{
    m_ModifiedData.insert(a_Data);
    o_emit dataMarkedAsModified(a_Data);
    const phantom::data& ownerData = getSubDataOwner(a_Data);
    if(ownerData.isNull())
    {
        Node* pNode = getNode(a_Data);
        o_assert(pNode);
        markNodeAsModified(pNode);
    }
    else
    {
        markDataAsModified(ownerData);
    }
}

void DataBase::markDataAsAdded(const phantom::data& a_Data)
{
	m_AddedData.insert(a_Data);
	o_emit dataMarkedAsAdded(a_Data);
	const phantom::data& ownerData = getSubDataOwner(a_Data);
	if(ownerData.isNull())
	{
		Node* pNode = getNode(a_Data);
		o_assert(pNode);
		markNodeAsModified(pNode);
	}
	else
	{
		markDataAsModified(ownerData);
	}
}

void DataBase::markDataAsRemoved(const phantom::data& a_Data)
{
	m_RemovedData.insert(a_Data);
	o_emit dataMarkedAsRemoved(a_Data);
	const phantom::data& ownerData = getSubDataOwner(a_Data);
	if(ownerData.isNull())
	{
		Node* pNode = getNode(a_Data);
		o_assert(pNode);
		markNodeAsModified(pNode);
	}
	else
	{
		markDataAsModified(ownerData);
	}

	if (std::find(m_AddedData.begin(), m_AddedData.end(), a_Data) != m_AddedData.end())
	{
		m_AddedData.erase(a_Data);
	}
}

void DataBase::unmarkDataAsModified( const phantom::data& a_Data )
{
    if (std::find(m_ModifiedData.begin(), m_ModifiedData.end(), a_Data) != m_ModifiedData.end())
	{
		m_ModifiedData.erase(a_Data);
		o_emit dataUnmarkedAsModified(a_Data);
	}
}

void DataBase::unmarkDataAsAdded(const phantom::data& a_Data)
{
	if (std::find(m_AddedData.begin(), m_AddedData.end(), a_Data) != m_AddedData.end())
    {
        m_AddedData.erase(a_Data);
        o_emit dataUnmarkedAsAdded(a_Data);
	}
}

void DataBase::unmarkDataAsRemoved(const phantom::data& a_Data)
{
	if (std::find(m_RemovedData.begin(), m_RemovedData.end(), a_Data) != m_RemovedData.end())
	{
		m_RemovedData.erase(a_Data);
		o_emit dataUnmarkedAsRemoved(a_Data);
	}
}

void DataBase::saveModifiedData()
{
    o_foreach(phantom::data d, m_ModifiedData)
    {
        Node* pNode = getNode(d.address());
        pNode->saveData(d);
        pNode->saveDataAttributes(d);
        o_emit dataUnmarkedAsModified(d);
    }
    m_ModifiedData.clear();
}

void DataBase::saveModifiedData( const phantom::data& a_Data )
{
    o_assert(isDataMarkedAsModified(a_Data));
    Node* pNode = getNode(a_Data);
    pNode->saveData(a_Data);
    pNode->saveDataAttributes(a_Data);
    m_ModifiedData.erase(a_Data);
    o_emit dataUnmarkedAsModified(a_Data);
}

void DataBase::saveAddedData()
{
	o_foreach(phantom::data d, m_AddedData)
	{
		Node* pNode = getNode(d.address());
		pNode->saveData(d);
		pNode->saveDataAttributes(d);
		o_emit dataUnmarkedAsAdded(d);
	}
	m_AddedData.clear();
}

void DataBase::saveRemovedData()
{
	o_foreach(phantom::data d, m_RemovedData)
	{
		Node* pNode = getNode(d.address());
		pNode->removeData(d);
		o_emit dataUnmarkedAsRemoved(d);
	}
	m_RemovedData.clear();
}

void DataBase::saveModifiedNode( Node* a_pNode )
{
    o_assert(isNodeMarkedAsModified(a_pNode));
	a_pNode->saveIndex();
    a_pNode->saveAttributes();
    
	// TODO : to remove ?
	/*emit nodeUnmarkedAsModified(a_pNode);
    phantom::vector<phantom::data> allData;
    a_pNode->getAllData(allData);
    o_foreach(phantom::data d, allData)
    {
        if(isDataMarkedAsModified(d))
        {
            saveModifiedData(d);
        }
    }*/

    unmarkNodeAsModified(a_pNode);
    //a_pNode->saveState(e_InitialDataStateId);
}

void DataBase::saveModifiedNodes()
{
    while(NOT(m_ModifiedNodes.empty()))
    {
        saveModifiedNode(*m_ModifiedNodes.begin());
    }
}

bool DataBase::isDataMarkedAsModified( const phantom::data& a_Data ) const
{
    return m_ModifiedData.find(a_Data) != m_ModifiedData.end();
}

bool DataBase::isDataMarkedAsAdded( const phantom::data& a_Data ) const
{
	return m_AddedData.find(a_Data) != m_AddedData.end();
}

bool DataBase::isDataMarkedAsRemoved( const phantom::data& a_Data ) const
{
	return m_RemovedData.find(a_Data) != m_RemovedData.end();
}

void DataBase::markNodeAsModified( Node* a_pNode )
{
    m_ModifiedNodes.insert(a_pNode);
    /*emit nodeMarkedAsModified(a_pNode);
    a_pNode->saveAttributes();*/
}

void DataBase::unmarkNodeAsModified( Node* a_pNode )
{
    m_ModifiedNodes.erase(a_pNode);
    //emit nodeUnmarkedAsModified(a_pNode);
}

bool DataBase::isNodeMarkedAsModified( Node* a_pNode ) const
{
    return m_ModifiedNodes.find(a_pNode) != m_ModifiedNodes.end();
}

void DataBase::cancelAddedAndRemovedData(Node* a_pNode)
{
    // Unmark datas
    std::set<phantom::data> datas;
    datas.insert(m_ModifiedData.begin(), m_ModifiedData.end());
    std::set<phantom::data>::iterator it = datas.begin();
    std::set<phantom::data>::iterator end = datas.end();
    for (; it != end; it++)
    {
        Node* pNodeOfData = getNode(it->address());
        if (a_pNode == pNodeOfData)
        {
            unmarkDataAsModified(*it);
        }
    }
    datas.clear();

    datas.insert(m_AddedData.begin(), m_AddedData.end());
    it = datas.begin();
    end = datas.end();
    for (; it != end; it++)
    {
        phantom::data d = *it;
        Node* pNodeOfData = getNode(d);
        if (a_pNode == pNodeOfData)
        {
            pNodeOfData->removeData(d);
            unmarkDataAsAdded(d);
        }
    }
    datas.clear();

    datas.insert(m_RemovedData.begin(), m_RemovedData.end());
    it = datas.begin();
    end = datas.end();
    for (; it != end; it++)
    {
        Node* pNodeOfData = getNode(it->address());
        if (a_pNode == pNodeOfData)
        {
            removeDataFromTrashbin(*it);
            unmarkDataAsRemoved(*it);
        }
    }
    datas.clear();

    unmarkNodeAsModified(a_pNode);
}

void DataBase::rebuildData( phantom::data& a_inOutData, reflection::Type* a_pOld, reflection::Type* a_pNewType, vector<data>& a_Old, vector<data>& a_New, uint a_uiStateId /*= 0xffffffff*/ )
{
    o_assert(a_inOutData.type() == a_pOld);
    o_assert(a_pOld->isClass() == a_pNewType->isClass(), "to be replaced, types must be of the same 'type', both classes or both not classes");

    phantom::data newData(a_pNewType->allocate(), a_pNewType);
    a_pNewType->build(newData.address());
    phantom::data oldData = a_inOutData;

    // Replace by the new data
    a_inOutData = newData;

    a_Old.push_back(oldData);
    a_New.push_back(newData);
}

void DataBase::saveState( uint a_uiState )
{
    o_assert(m_pDataStateBase, "You must associate a DataStateBase with this DataBase to be able to load/save states");
    if(rootNode()->isLoaded())
    {
        rootNode()->saveStateCascade(m_pDataStateBase, a_uiState);
    }
}

void DataBase::loadState( uint a_uiState )
{
    o_assert(m_pDataStateBase, "You must associate a DataStateBase with this DataBase to be able to load/save states");
    if(rootNode()->isLoaded())
    {
        rootNode()->loadStateCascade(m_pDataStateBase, a_uiState);
    }
}

void DataBase::save()
{
    if(rootNode()->isLoaded())
    {
        rootNode()->saveCascade();
    }
}

Node* DataBase::rootNode()
{
    if (m_pRootNode == NULL)
    {
        m_pRootNode = createNode(0, NULL);
        if(NOT(hasNodeEntry(m_pRootNode)))
        {
            createNodeEntry(m_pRootNode);
            m_pRootNode->save();
        }
        registerNode(m_pRootNode);
    }
    return m_pRootNode;
}

boolean DataBase::isDataCompatibleWithNode( const phantom::data& a_Data, Node* a_pOwnerNode ) const
{
    return NOT(a_pOwnerNode->childNodesContainDependencyOfDeep(a_Data))
        AND a_pOwnerNode->acceptsData(a_Data);
}

void DataBase::dataDestroyed( void* a_pAddress )
{
    Node* pDataNode = getNode(a_pAddress);
    if(pDataNode) return; // Means that this instance is not in the database
    pDataNode->removeData(a_pAddress);
}

const string& DataBase::getDataAttributeValue( const phantom::data& a_Data, size_t attributeIndex ) const
{
    o_assert(attributeIndex < getAttributeCount());
    static string null_string;
    attribute_map::const_iterator found = m_AttributeValues.find(a_Data.address());
    if(found != m_AttributeValues.end())
    {
        return (found->second)[attributeIndex];
    }
    return null_string;
}

const string& DataBase::getDataAttributeValue( const phantom::data& a_Data, const string& attributeName ) const
{
    return getDataAttributeValue(a_Data, getAttributeIndex(attributeName));
}

const string& DataBase::getNodeAttributeValue( Node* a_pNode, size_t attributeIndex ) const
{
    o_assert(attributeIndex < getAttributeCount());
    static string null_string;
    attribute_map::const_iterator found = m_AttributeValues.find(a_pNode);
    if(found != m_AttributeValues.end())
    {
        return (found->second)[attributeIndex];
    }
    return null_string;
}

const string& DataBase::getNodeAttributeValue( Node* a_pNode, const string& attributeName ) const
{
    return getNodeAttributeValue(a_pNode, getAttributeIndex(attributeName));
}

const string* DataBase::getDataAttributeValues( const phantom::data& a_data )
{
    attribute_map::const_iterator found = m_AttributeValues.find(a_data.address());
    return found != m_AttributeValues.end() ? found->second : NULL;
}

const string* DataBase::getNodeAttributeValues( Node* a_pNode ) const
{
    attribute_map::const_iterator found = m_AttributeValues.find(a_pNode);
    return found != m_AttributeValues.end() ? found->second : NULL;
}

void DataBase::setDataAttributeValue( const phantom::data& a_Data, size_t attributeIndex, const string& value )
{
    o_assert(attributeIndex < getAttributeCount());
    m_AttributeValues[a_Data.address()][attributeIndex] = value;
    o_emit dataAttributeValueChanged(a_Data, attributeIndex, value);
}

void DataBase::setDataAttributeValue( const phantom::data& a_Data, const string& fieldName, const string& value )
{
    setDataAttributeValue(a_Data, getAttributeIndex(fieldName), value);
}

void DataBase::setNodeAttributeValue( Node* a_pNode, size_t attributeIndex, const string& value )
{
    o_assert(attributeIndex < getAttributeCount());
    m_AttributeValues[a_pNode][attributeIndex] = value;
    o_emit nodeAttributeValueChanged(a_pNode, attributeIndex, value);
}

void DataBase::setNodeAttributeValue( Node* a_pNode, const string& fieldName, const string& value )
{
    setNodeAttributeValue(a_pNode, getAttributeIndex(fieldName), value);
}

size_t DataBase::addAttribute( const string& a_name )
{
    o_assert(m_GuidBase.isEmpty(), "Cannot add dataMember after data");
    m_AttributeNames.push_back(a_name);
    return m_AttributeNames.size()-1;
}

size_t DataBase::getAttributeIndex( const string& a_name ) const
{
    size_t i = 0;
    size_t count = m_AttributeNames.size();
    for(;i<count;++i)
    {
        if(m_AttributeNames[i] == a_name) return i;
    }
    return e_Constant_InvalidAttributeIndex;
}

const string& DataBase::getAttributeName( size_t attributeIndex ) const
{
    o_assert(attributeIndex < getAttributeCount());
    return m_AttributeNames[attributeIndex];
}



o_cpp_end
