/* TODO LICENCE HERE */

#ifndef serialization_FileTreeDataBase_h__
#define serialization_FileTreeDataBase_h__

/* ****************** Includes ******************* */
#include <phantom/serialization/DataBase.h>
/* *********************************************** */
o_declareN(class, (phantom, serialization), FileTreeDataBase)
namespace boost { namespace filesystem { class path; } }
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export FileTreeDataBase : public DataBase
{
    friend class FileTreeNode;

public:
    FileTreeDataBase(const string& url, uint a_uiSerializationFlag);
    o_destructor ~FileTreeDataBase(void)     {}

    o_initialize();

    virtual void    loadNodeEntries();
    virtual void    unloadNodeEntries();

    virtual boolean hasNodeEntry(Node* a_pNode) const ;
    virtual boolean hasDataEntry(const phantom::data& a_Data, uint guid, Node* a_pOwnerNode) const;

    virtual string  nodePath(Node* a_pNode, uint a_Guid, Node* a_pParent) const;
    virtual string  nodePath(Node* a_pNode) const;
    virtual string  dataPath(const phantom::data& a_Data, uint a_Guid, Node* a_pParent) const;
    virtual string  dataPath(const phantom::data& a_Data) const
    {
        return dataPath(a_Data, getGuid(a_Data), getNode(a_Data));
    }
    phantom::string relativeDataPath( const phantom::data& a_Data, uint a_Guid, Node* a_pParent ) const;
    phantom::string relativeNodePath( Node* a_pNode, uint a_Guid, Node* a_pParent ) const;
    phantom::string relativeNodePath( Node* a_pNode ) const;
    virtual string  relativeDataPath(const phantom::data& a_Data) const;

    virtual string  dataFileExtension(void* a_pData) const { return ""; }
    
    virtual uint    generateGuid();
    virtual void    releaseGuid(uint guid) {}
    
    virtual Node*   createNode(uint a_Guid, Node* a_pParentNode) const = 0;
    virtual void    destroyNode(Node* a_pNode) const = 0;
    
    virtual void    createDataEntry(const phantom::data& a_Data, uint a_Guid, Node* a_pOwnerNode);
    virtual void    destroyDataEntry(const phantom::data& a_Data, uint a_Guid, Node* a_pOwnerNode);
    virtual void    moveDataEntry(const phantom::data& a_Data, uint a_Guid, Node* a_pOldParent, Node* a_pNewParent);

    virtual void    createNodeEntry(Node* a_pNode) ;
    virtual void    destroyNodeEntry(Node* a_pNode) ;
    virtual void    moveNodeEntry(Node* a_pNode, Node* a_pNewParent) ;

    // TODO : create a TextFileTreeDataBase and make these two functions abstract
    virtual void    write(const string& a_Path, const property_tree& a_Tree) const {}
    virtual void    read(const string& a_Path, property_tree& a_Tree) const {}

    virtual uint    createBackup();
    virtual void    destroyBackup(uint a_uiBackupId);

    virtual void    saveDataEntryBackup(uint a_uiBackupId, const phantom::data& a_Data, uint guid, Node* a_pNode);
    virtual void    saveNodeEntryBackup(uint a_uiBackupId, Node* a_pNode);
    virtual void    restoreDataEntryBackup(uint a_uiBackupId, const phantom::data& a_Data, uint guid, Node* a_pNode);
    virtual void    restoreNodeEntryBackup(uint a_uiBackupId, Node* a_pNode);

    virtual void    saveTypeBackup(uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName);
    virtual void    restoreTypeBackup(uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName);
    virtual void    swapTypeBackup(uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName);
    virtual void    eraseTypeBackup(uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName);
    virtual bool    hasTypeBackup(uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName) const;

protected:
    void            createBackup( uint a_uiBackup );
    string          getBackupPath( uint a_uiBackup ) const;

protected:
    void            loadNodeEntriesHelper(Node* a_pNode, const boost::filesystem::path& a_Path);
    void            generateGuidHelper(const boost::filesystem::path& a_Path, std::set<uint>& guids);
    virtual void    saveType(reflection::Type* a_pType);
    virtual bool    hasTypeEntry(const string& a_strQualifiedDecoratedName, const string& a_strModuleFileName) const;

    string          getTypePath(reflection::Type* a_pType) const;
    string          getTypePath(const string& a_strQualifiedDecoratedName, const string& a_strModuleFileName) const;
    string          getRelativeTypePath( const string& a_strQualifiedDecoratedName, const string& a_strModuleFileName ) const;
    string          getRelativeModulePath( const string& a_strModuleFileName ) const;
    void            createTypeEntry(reflection::Type* a_pType);
    void            destroyTypeEntry(reflection::Type* a_pType);
    string          encodeTypeFileName(const string& a_strQualifiedDecoratedName) const;
    string          decodeTypeFileName(const string& a_strQualifiedDecoratedName) const;
    void            loadTypes( reflection::Module* a_pModule, vector<reflection::Type*>* a_pLoadedTypes, const vector<string>* a_pTypeNames = nullptr );

protected:
    std::set<uint> m_GeneratedGuids;
};

o_namespace_end(phantom, serialization)

#endif 