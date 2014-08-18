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
#include <phantom/reflection/Statement.h>
#include <phantom/reflection/Statement.hxx>
#include <phantom/reflection/Block.h>
/* *********************************************** */
o_registerN((phantom, reflection), Statement);

o_namespace_begin(phantom, reflection) 

Statement::Statement( const string& a_strName ) 
    : Evaluable(a_strName, 0)
    , m_uiIndexInBlock(~size_t(0))
{
}

Statement::Statement()
    : Evaluable("", 0)
    , m_uiIndexInBlock(~size_t(0))
{

}

Block* Statement::getBlock() const
{
    return m_pOwner ? m_pOwner->asBlock() : nullptr;
}

Block* Statement::getRootBlock() const
{
    Block* pBlock = getBlock();
    return pBlock ? pBlock->getRootBlock() : nullptr;
}

Subroutine* Statement::getSubroutine() const
{
    Block* pBlock = getBlock();
    return  pBlock ? pBlock->getSubroutine() : nullptr;
}

Statement* Statement::getNextStatement() const
{
    Block* pBlock = getBlock();
    if(pBlock == nullptr) return nullptr;
    size_t nextIndex = m_uiIndexInBlock+1;
    if(nextIndex == pBlock->getStatementCount())
        return pBlock->getNextStatement();
    return pBlock->getStatement(nextIndex);
}

o_namespace_end(phantom, reflection)
