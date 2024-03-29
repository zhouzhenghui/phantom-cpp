/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/RValueReferenceType.h>
#include <phantom/reflection/RValueReferenceType.hxx>
#include <phantom/reflection/Expression.h>
/* *********************************************** */
o_registerN((phantom, reflection), RValueReferenceType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(RValueReferenceType);

RValueReferenceType::RValueReferenceType( Type* a_pReferencedType ) 
    : ReferenceType(a_pReferencedType, "&&")
{

}

bool RValueReferenceType::partialAccepts( Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_DeducedConstants ) const
{
    if(a_pType->asRValueReferenceType())
    {
        a_Score += 10;
        return m_pReferencedType ? m_pReferencedType->partialAccepts(a_pType->removeRValueReference(), a_Score, a_DeducedConstants) : false;
    }
    return false;
}

o_namespace_end(phantom, reflection)