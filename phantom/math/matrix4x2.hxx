#pragma once

o_structureNT((phantom, math), (typename), (t_Ty), matrix4x2)
(
    o_nested_typedef(self_type);
    o_nested_typedef(vector2_type);
    o_anonymous_union
    (
        o_data_member(t_Ty[8], m);
        o_data_member(t_Ty[2][4], mm);
        o_anonymous_struct
        (
            o_data_member(vector2_type, ex);
            o_data_member(vector2_type, ey);
            o_data_member(vector2_type, ez);
            o_data_member(vector2_type, ew);
        );
    );
    o_member_function(bool, operator==, (const self_type&), o_const);
    o_member_function(bool, operator!=, (const self_type&), o_const);
);