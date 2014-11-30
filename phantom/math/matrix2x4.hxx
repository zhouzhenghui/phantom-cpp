#pragma once

o_structureNT((phantom, math), (typename), (t_Ty), matrix2x4)
(
    o_nested_typedef(self_type);
    o_nested_typedef(vector4_type);
    o_anonymous_union
    (
        o_data_member(t_Ty[8], m);
        o_data_member(t_Ty[4][2], mm);
        o_anonymous_struct
        (
            o_data_member(vector4_type, ex);
            o_data_member(vector4_type, ey);
        );
    );
    o_member_function(bool, operator==, (const self_type&), o_const);
    o_member_function(bool, operator!=, (const self_type&), o_const);
);