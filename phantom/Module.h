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

#ifndef o_phantom_reflection_Module_h__
#define o_phantom_reflection_Module_h__

/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom), Module)
/* *********************************************** */
o_namespace_begin(phantom)

class o_export Module
{

public:
    Module(const string& a_strName, const string& a_strFilePath, size_t a_PlatformHandle);
    ~Module();

    o_terminate();

    const string& getName() const { return m_strName; }
    string        getFileName() const;
    const string& getFilePath() const { return m_strFilePath; }

    void addLanguageElement(reflection::LanguageElement* a_pLanguageElement) ;
    void removeLanguageElement(reflection::LanguageElement* a_pLanguageElement) ;
    
    void beginReplaceLanguageElements( const vector<reflection::LanguageElement*>& a_OldLanguageElements);
    void endReplaceLanguageElements( const vector<reflection::LanguageElement*>& a_NewLanguageElements );
    
    void beginReplaceLanguageElement( reflection::LanguageElement* a_pOldLanguageElement );
    void endReplaceLanguageElement( reflection::LanguageElement* a_pOldLanguageElement );
    
    bool hasLanguageElement(reflection::LanguageElement* a_pLanguageElement) const;

    vector<reflection::LanguageElement*>::const_iterator beginLanguageElements() { return m_LanguageElements.begin(); }
    vector<reflection::LanguageElement*>::const_iterator endLanguageElements() { return m_LanguageElements.end(); }

    void setParentModule(Module* a_pModule);
    Module* getParentModule() const { return m_pParentModule; }

    size_t getPlatformHandle() const { return m_PlatformHandle; }

    void checkCompleteness();

    bool canBeUnloaded() const;

protected:
    inline phantom::signal_t elementAdded(reflection::LanguageElement*);
    inline phantom::signal_t elementAboutToBeRemoved(reflection::LanguageElement*);
    inline phantom::signal_t elementsAboutToBeReplaced(const vector<reflection::LanguageElement*>&);
    inline phantom::signal_t elementsReplaced(const vector<reflection::LanguageElement*>&, const vector<reflection::LanguageElement*>&);

protected:
    phantom::connection::slot::list         PHANTOM_CODEGEN_m_slot_list_of_elementAdded;
    phantom::connection::slot::list         PHANTOM_CODEGEN_m_slot_list_of_elementAboutToBeRemoved;
    phantom::connection::slot::list         PHANTOM_CODEGEN_m_slot_list_of_elementsAboutToBeReplaced;
    phantom::connection::slot::list         PHANTOM_CODEGEN_m_slot_list_of_elementsReplaced;
    Module*                                 m_pParentModule;
    string                                  m_strName;
    string                                  m_strFilePath;
    vector<reflection::LanguageElement*>    m_LanguageElements;
    size_t                                  m_PlatformHandle;
    vector<reflection::LanguageElement*>    m_ReplacementOldElements;

};

o_namespace_end(phantom)

#endif
