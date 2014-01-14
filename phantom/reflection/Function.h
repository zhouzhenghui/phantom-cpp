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

#ifndef o_phantom_reflection_Function_h__
#define o_phantom_reflection_Function_h__

/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Function.classdef.h"
/* **************** Declarations ***************** */
/* *********************************************** */

o_h_begin

class o_export Function : public Subroutine
{

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

protected:
    Function(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0)
        : Subroutine(a_strName, a_pSignature, a_Modifiers)
    {

    }
    virtual Function* asFunction() const { return (Function*)this; }

    virtual void call(void** args) const = 0;
    virtual void call(void** args, void* a_pReturnAddress) const = 0;

    virtual void    call( void* a_pCallerAddress, void** a_pArgs ) const { call(a_pArgs); }
    virtual void    call( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const { call(a_pArgs, a_pReturnAddress); }

protected:
};

o_h_end

#else
#include "Function.classdef.h"
#endif