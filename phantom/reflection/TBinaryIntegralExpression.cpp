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
#include <phantom/reflection/TBinaryIntegralExpression.h>
#include <phantom/reflection/TBinaryIntegralExpression.hxx>
/* *********************************************** */
o_registerNT((phantom, reflection), (typename), (t_Ty), TBinaryIntegralExpression);

o_registerNTI((phantom, reflection), TBinaryIntegralExpression, (bool));
o_registerNTI((phantom, reflection), TBinaryIntegralExpression, (char));
o_registerNTI((phantom, reflection), TBinaryIntegralExpression, (signed char));
o_registerNTI((phantom, reflection), TBinaryIntegralExpression, (unsigned char));
o_registerNTI((phantom, reflection), TBinaryIntegralExpression, (short));
o_registerNTI((phantom, reflection), TBinaryIntegralExpression, (unsigned short));
o_registerNTI((phantom, reflection), TBinaryIntegralExpression, (int));
o_registerNTI((phantom, reflection), TBinaryIntegralExpression, (unsigned int));
o_registerNTI((phantom, reflection), TBinaryIntegralExpression, (long));
o_registerNTI((phantom, reflection), TBinaryIntegralExpression, (unsigned long));
o_registerNTI((phantom, reflection), TBinaryIntegralExpression, (long long));
o_registerNTI((phantom, reflection), TBinaryIntegralExpression, (unsigned long long));

o_namespace_begin(phantom, reflection) 



o_namespace_end(phantom, reflection)
