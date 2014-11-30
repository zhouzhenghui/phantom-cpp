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

#ifndef o_phantom_reflection_ReferenceExpression_h__
#define o_phantom_reflection_ReferenceExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), ReferenceExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ReferenceExpression : public Expression
{
public:
    ReferenceExpression(Expression* a_pReferenceableExpression);

    virtual void                    getValue(void* a_pDest) const 
    {
        *((void**)a_pDest) = m_pReferencedExpression->loadEffectiveAddress();
    }

    virtual ReferenceExpression*    asReferenceExpression() const  { return const_cast<ReferenceExpression*>(this); }

    virtual void flush() const { m_pReferencedExpression->flush(); }

    virtual Expression*     reference() const
    {
        return const_cast<ReferenceExpression*>(this);
    }
    
    virtual Expression*     dereference() const
    {
        Expression* pExp = m_pReferencedExpression;
        const_cast<ReferenceExpression*>(this)->removeElement(pExp);
        o_dynamic_delete const_cast<ReferenceExpression*>(this);
        return pExp;
    }

    Expression* getReferencedExpression() const { return m_pReferencedExpression; }

    virtual ReferenceExpression*     clone() const;
protected:
    Expression* m_pReferencedExpression;
};

o_namespace_end(phantom, reflection)



#endif
