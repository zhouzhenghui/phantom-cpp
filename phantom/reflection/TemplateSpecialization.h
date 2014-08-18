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

#ifndef o_phantom_reflection_TemplateSpecialization_h__
#define o_phantom_reflection_TemplateSpecialization_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export TemplateSpecialization : public LanguageElement
{
    friend class TemplateElement;
    friend class LanguageElement;
public:

public:

    TemplateSpecialization(Template* a_pTemplate);
    o_destructor ~TemplateSpecialization();

    virtual void terminate();

    virtual TemplateSpecialization* asTemplateSpecialization() const { return (TemplateSpecialization*)this; }

    uint                getArgumentCount() const { return m_Arguments.size(); }
    Type*               getType(const string& a_strTypenameVariableName) const;
    ClassType*          getClassType() const { return m_pOwner ? m_pOwner->asClassType() : nullptr; }
    TemplateElement*    getArgumentElement(const string& a_strTypenameVariableName) const;
    size_t              getArgumentIndex(const string& a_strTemplateTypeName) const;

    void                setArgument(const string& a_strTemplateTypeName, TemplateElement* a_pElement);
    void                removeArgument(TemplateElement* a_pElement);

    void                setDefaultArgument(const string& a_strParameterName, TemplateElement* a_pElement);
    TemplateElement*    getDefaultArgument(const string& a_strParameterName) const;

    string              getQualifiedName() const;
    string              getQualifiedDecoratedName() const;

    boolean             matches(const vector<TemplateElement*>* a_TemplateSpecialization) const;
  
    Template*           getTemplate() const { return m_pTemplate; }

    virtual void        checkCompleteness() const;
    virtual bool        canBeDestroyed() const;
 
protected:
    void                _updateName();
    void                referencedElementAdded(LanguageElement* a_pElement);
    void                referencedElementRemoved(LanguageElement* a_pElement);

protected:
    typedef phantom::map<string, TemplateElement*>  template_element_map;
    typedef phantom::map<string, size_t>            template_element_index_map;
    struct Argument
    {
        Argument() : element(nullptr), defaultElement(nullptr) {}
        Argument(const string& n, TemplateElement* e, TemplateElement* d = nullptr) : name(n), element(e), defaultElement(d) {}
        string name;
        TemplateElement* element;
        TemplateElement* defaultElement;
    };
    vector<Argument>            m_Arguments;
    size_t                      m_DefaultArgumentsCount;
    Template*                   m_pTemplate;

};

o_namespace_end(phantom, reflection)



#endif
