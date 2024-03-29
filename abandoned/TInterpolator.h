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

#ifndef util_TInterpolator_h__
#define util_TInterpolator_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <phantom/util/Interpolator.h>
/* **************** Declarations ***************** */

/* *********************************************** */


o_h_begin

template<typename _basic_type>
class TInterpolator : public Interpolator
{
public:
    
    TInterpolator(const _basic_type& a_start, const _basic_type& a_end)                 
        : m_Start(a_start), m_End(a_end) 
    {
    }
    o_destructor ~TInterpolator(void)     
    {
    }

    virtual PrimitiveType*        getInterpolatedType() const { return Phantom::basicTypeOf<_basic_type>(); }

    virtual void setStartValue(void* a_pSrc) { m_Start = *((_basic_type*)a_pSrc); }
    virtual void setEndValue(void* a_pSrc) { m_End = *((_basic_type*)a_pSrc); }
    virtual void getValue(real a_fPercent, void* a_pDest, uint mode = 0) const 
    {
        getInterpolatedType()->interpolate(&m_Start, &m_End, a_fPercent, a_pDest, mode);
    }

protected:
    _basic_type        m_Start;
    _basic_type        m_End;
};

o_h_end

#endif