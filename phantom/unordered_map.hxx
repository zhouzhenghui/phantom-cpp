#pragma once

#include <std/unordered_map.hxx>

#if o_HAS_CPP0X
o_classNTB((phantom), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr), unordered_map, (std::unordered_map<t_Kty, t_Ty, t_Hash, t_Pr, o__t1_class__partioned_memory_allocator(o_TT(std::pair, const t_Kty, t_Ty))>))(
        );
#else
o_classNTB((phantom), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr), unordered_map, (std::tr1::unordered_map<t_Kty, t_Ty, t_Hash, t_Pr, o__t1_class__partioned_memory_allocator(o_TT(std::pair, const t_Kty, t_Ty))>))(
        );
#endif
