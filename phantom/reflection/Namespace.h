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

#ifndef o_phantom_reflection_Namespace_h__
#define o_phantom_reflection_Namespace_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */


o_namespace_begin(phantom, reflection)

class o_export Namespace : public LanguageElement
{
    o_language_element;

public:
    typedef map<string, Type*>  typedef_map;
    typedef map<string, Namespace*> namespace_alias_map;
    typedef vector<Namespace*>  namespace_container;
    typedef vector<Function*>   function_container;
    typedef vector<StaticVariable*> variable_container;
    typedef vector<Type*>       type_container;
    typedef vector<Template*>   template_container;

    friend class phantom::Phantom;
    friend class Type;


public:
    Namespace(void);
    Namespace(const string& a_strName);
    o_destructor ~Namespace(void);


    /** @name Signals
     *
     */
    //@{
protected:
    o_signal_data(typeAdded, Type*)
    o_signal_data(typeRemoved, Type*)
    o_signal_data(namespaceAdded, Namespace*)
    o_signal_data(namespaceRemoved, Namespace*)
    o_signal_data(templateAdded, Template*)
    o_signal_data(templateRemoved, Template*)
    o_signal_data(functionAdded, Function*)
    o_signal_data(functionRemoved, Function*)
    o_signal_data(variableAdded, StaticVariable*)
    o_signal_data(variableRemoved, StaticVariable*)
    //@}

public:
    virtual Namespace*  asNamespace() const { return (Namespace*)this; }
    void                addType(Type* a_pType);
    void                replaceType(Type* a_pOldType, Type* a_pNewType);
    void                removeType(Type* a_pType);
    void                addFunction(Function* a_pFunction);
    void                removeFunction(Function* a_pFunction);
    void                addVariable(StaticVariable* a_pVariable);
    void                removeVariable(StaticVariable* a_pVariable);
    void                addTemplate(Template* a_pTemplate);
    void                removeTemplate( Template* a_pTemplate );
    void                addNamespace(Namespace* a_pNamespace);
    void                removeNamespace(Namespace* a_pNamespace);
    void                getHierarchicalName(string* a_OutString);
    void                getHierarchicalNameNoRoot(string* a_OutString);

    Type*               getType( uint index ) const {return m_Types[index]; }
    Type*               getType( const string& a_strName ) const;
    void                getAllTypesCascade( const string& a_strName, vector<Type*>& a_Out ) const;
	Type*               getTypeByGuid( uint a_uiGuid ) const;
	Type*               getTypeByGuidCascade( uint a_uiGuid ) const;
    uint                getTypeCount() const {return m_Types.size(); }

    PrimitiveType*      getPrimitiveType(const string& a_strName) const;
    Class*              getClass(const string& a_strName) const;
    Class*              getClass(size_t index) const;
    size_t              getClassCount() const;

    Template*           getTemplate( const string& a_strName ) const ;
    Template*           findOrCreateTemplate(const string& a_strName);

    Namespace*          findTypeNamespace(Type* a_pType) const;


    Namespace*          getRootNamespace() const;
    Namespace*          getNamespace(const string& a_strName) const;
    Namespace*          getNamespaceCascade(list<string>* a_HierarchyWords) const;
    Namespace*          getNamespaceCascade(const string& qualifiedName) const;
    o_forceinline
    Namespace*          getParentNamespace() const { return static_cast<Namespace*>(m_pOwner); }
    Namespace*          findOrCreateNamespaceCascade(const string& a_strNamespaceName);
    Namespace*          findOrCreateNamespaceCascade(list<string>* a_HierarchyWords);

    Namespace*          getNamespace(uint i) const { return m_Namespaces[i]; }
    uint                getNamespaceCount() const { return m_Namespaces.size(); }

    void                destroyAllCascade();
    void                destroyAllNamespaceCascade();

    boolean             searchAndDestroy(Type* a_pType);
    boolean             searchAndDestroyCascade(Type* a_pType);

    boolean             searchAndDestroy(Namespace* a_pNamespace);
    boolean             searchAndDestroyCascade(Namespace* a_pNamespace);

    boolean             searchAndRemove(Type* a_pType);
    boolean             searchAndRemoveCascade(Type* a_pType);

    void                removeAllTypeCascade();

    void                addTypedef( const string& a_strTypedef, Type* a_pType );

    void                removeTypedef( const string& a_strTypedef, Type* a_pType );

    inline Type*        getTypedef(const string& a_strTypedef) const;

    void                addNamespaceAlias( const string& a_strAlias, Namespace* a_pNamespace );

    void                removeNamespaceAlias( const string& a_strAlias, Namespace* a_pNamespace );

    inline Namespace*   getNamespaceAlias(const string& a_strAlias) const;

    DataPointerType*    getDataPointerType(Type* a_pPointedType) const;
    ReferenceType*      getReferenceType(Type* a_pPointedType) const;
    Type*               getConstType(Type* a_pPointedType) const;
    ArrayType*          getArrayType(Type* a_pPointedType, size_t a_uiCount) const;

    vector<Type*>::const_iterator beginTypes() const { return m_Types.begin(); }
    vector<Type*>::const_iterator endTypes() const { return m_Types.end(); }
    vector<Template*>::const_iterator beginTemplates() const { return m_Templates.begin(); }
    vector<Template*>::const_iterator endTemplates() const { return m_Templates.end(); }
    vector<Namespace*>::const_iterator beginNamespaces() const { return m_Namespaces.begin(); }
    vector<Namespace*>::const_iterator endNamespaces() const { return m_Namespaces.end(); }
    vector<Function*>::const_iterator beginFunctions() const { return m_Functions.begin(); }
    vector<Function*>::const_iterator endFunctions() const { return m_Functions.end(); }
    vector<StaticVariable*>::const_iterator beginVariables() const { return m_Variables.begin(); }
    vector<StaticVariable*>::const_iterator endVariables() const { return m_Variables.end(); }

    virtual void        getElements(vector<LanguageElement*>& out, Class* a_pClass = nullptr) const;

    virtual bool        isTemplateDependant() const { return false; }

protected:
    void                setParentNamespace(Namespace* a_pNamespace) { m_pOwner = a_pNamespace; }
    virtual void        referencedElementRemoved(LanguageElement* a_pElement);
    virtual void        elementRemoved(LanguageElement* a_pElement);

protected:
    namespace_container m_Namespaces;
    mutable
    function_container  m_Functions;
    mutable
    variable_container  m_Variables;
    type_container      m_Types;
    template_container  m_Templates;
    typedef_map         m_Typedefs;
    namespace_alias_map m_NamespaceAliases;

private:
    void release(vector<Type*>& out_types);
};

inline Type* Namespace::getTypedef( const string& a_strTypedef ) const
{
    auto found = m_Typedefs.find(a_strTypedef);
    if( found != m_Typedefs.end() ) return found->second;
    return nullptr;
}

inline Namespace* Namespace::getNamespaceAlias( const string& a_strAlias ) const
{
    auto found = m_NamespaceAliases.find(a_strAlias);
    if( found != m_NamespaceAliases.end() ) return found->second;
    return nullptr;
}

o_namespace_end(phantom, reflection)



#endif
