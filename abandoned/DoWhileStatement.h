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

#ifndef o_phantom_reflection_DoWhileStatement_h__
#define o_phantom_reflection_DoWhileStatement_h__



/* ****************** Includes ******************* */
#include "phantom/reflection/Statement.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), DoWhileStatement);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export DoWhileStatement : public Block
{
public:
    DoWhileStatement();

    virtual variant         compile(Compiler* a_pCompiler);

    virtual void            eval() const { o_assert(false); }

    virtual void            flush() const {}

    void                    setCondition(Expression* a_pExpression);

    Expression*             getCondition() const { return m_pCondition; }

    void                    setStatement(Statement* a_pStatement);

    Statement*              getStatement() const { return m_pStatement; }

protected:
    Expression*             m_pCondition;
    Statement*              m_pStatement;
};

o_namespace_end(phantom, reflection)



#endif
