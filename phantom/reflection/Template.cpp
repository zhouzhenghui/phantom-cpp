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
#include <phantom/reflection/Template.h>
#include <phantom/reflection/Template.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), Template);

o_namespace_begin(phantom, reflection) 

Template::Template(const string& a_strName, TemplateSignature* a_pSignature, modifiers_t a_Modifiers /*= 0*/)
    : LanguageElement(a_strName, a_Modifiers)
    , m_pTemplateSignature(a_pSignature)
{
    if(m_pTemplateSignature)
        addElement(m_pTemplateSignature);
    else setInvalid();
    createEmptySpecialization();
}

Template::Template(const string& a_strName, const string& a_strTemplateTypes, const string& a_strTemplateParam, modifiers_t a_Modifiers /*= 0*/)
    : LanguageElement(a_strName, a_Modifiers)
    , m_pTemplateSignature(o_new(TemplateSignature)(a_strTemplateTypes, a_strTemplateParam))
{
    addElement(m_pTemplateSignature);
    createEmptySpecialization();
}

Template::~Template()
{

}

size_t Template::getTemplateParameterIndex( const string& a_strName ) const
{
    return m_pTemplateSignature->getParameterIndex(a_strName);
}

size_t Template::getTemplateParameterIndex( TemplateParameter* a_pTemplateParameter ) const
{
    return m_pTemplateSignature->getParameterIndex(a_pTemplateParameter);
}

LanguageElement* Template::getDefaultArgument(const string& a_strParameterName) const 
{
    return m_pTemplateSignature->getDefaultArgument(a_strParameterName);
}

LanguageElement* Template::getDefaultArgument(size_t i) const 
{
    return m_pTemplateSignature->getDefaultArgument(i);
}

void Template::setDefaultArgument( const string& a_strParameterName, LanguageElement* a_pElement )
{
    m_pTemplateSignature->setDefaultArgument(a_strParameterName, a_pElement);
}

size_t Template::getDefaultArgumentCount() const
{
    return m_pTemplateSignature->getDefaultArgumentCount();
}

void Template::addTemplateParameter( TemplateParameter* a_pTemplateParameter )
{
    m_pTemplateSignature->addParameter(a_pTemplateParameter);
}

void Template::addTemplateParameterAliasName( size_t a_uiIndex, const string& a_strAlias )
{
    m_pTemplateSignature->addParameterAliasName(a_uiIndex, a_strAlias);
}

size_t Template::getTemplateParameterCount() const
{
    return m_pTemplateSignature->getParameterCount();
}

vector<TemplateParameter*>::const_iterator Template::beginTemplateParameters() const
{
    return m_pTemplateSignature->beginParameters();
}

vector<TemplateParameter*>::const_iterator Template::endTemplateParameters() const
{
    return m_pTemplateSignature->endParameters();
}

void Template::createEmptySpecialization()
{
    registerSpecialization(o_new(TemplateSpecialization)(this, m_pTemplateSignature->getPlaceholders(), m_pTemplateSignature));
}

void Template::registerSpecialization( TemplateSpecialization* a_pTemplateSpecialization )
{
#ifndef NDEBUG
    for(auto it = m_Specializations.begin(); it != m_Specializations.end(); ++it)
    {
        o_assert(!(*it)->equals(a_pTemplateSpecialization));
    }
#endif
    m_Specializations.push_back(a_pTemplateSpecialization);
}

TemplateSpecialization*  Template::createSpecialization( const vector<LanguageElement*>& arguments, TemplateSignature* a_pTemplateSignature )
{
    TemplateSpecialization* pSpec = o_new(TemplateSpecialization)(this, arguments, a_pTemplateSignature);
    registerSpecialization(pSpec);
    return pSpec;
}

ClassType* Template::instanciate( const vector<LanguageElement*>& arguments )
{
    o_assert_no_implementation();
    return nullptr;
}

o_namespace_end(phantom, reflection)