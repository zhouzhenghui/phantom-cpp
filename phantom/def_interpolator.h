/* TODO LICENCE HERE */

#ifndef o_def_interpolator_h__
#define o_def_interpolator_h__

o_namespace_begin(phantom)


// Interpolator

template<typename t_Ty>
struct default_interpolator;

enum default_interpolator_id
{
    default_interpolator_arithmetic,
    default_interpolator_compound,
    default_interpolator_not_available,
};

namespace detail
{
    template<typename t_Ty, int t_id>
    struct default_interpolator_helper;

    template<typename t_Ty>
    struct default_interpolator_helper <t_Ty, default_interpolator_arithmetic>
    {
        static void interpolate(t_Ty* a_src_start, t_Ty* a_src_end, real a_fPercent, t_Ty* a_dest, uint mode)
        {
            *a_dest = *a_src_start +
                static_cast<t_Ty>(
                static_cast<real>(
                *a_src_end - static_cast<real>(*a_src_start)
                )*a_fPercent
                );
        }
    };

    template<typename t_Ty>
    struct default_interpolator_helper <t_Ty, default_interpolator_not_available>
    {
        static void interpolate(t_Ty* a_src_start, t_Ty* a_src_end, real a_fPercent, t_Ty* a_dest, uint mode)
        {
            o_exception(exception::unsupported_member_function_exception, __FUNCTION__);
        }
    };

    template<typename t_Ty>
    struct default_interpolator_helper <t_Ty, default_interpolator_compound>
    {
        static void interpolate(t_Ty* a_src_start, t_Ty* a_src_end, real a_fPercent, t_Ty* a_dest, uint mode)
        {
            o_unused(a_src_start);
            o_unused(a_src_end);
            o_unused(a_fPercent);
            o_unused(a_dest);
            o_unused(mode);
            o_error(false, "not implemented");
        }
    };
}

template<typename t_Ty>
struct default_interpolator : public detail::default_interpolator_helper<t_Ty,
    boost::is_arithmetic<t_Ty>::value AND NOT(boost::is_same<bool,t_Ty>::value)
    ? default_interpolator_arithmetic
    : (boost::is_class<t_Ty>::value AND has_reflection_cascade<t_Ty>::value)
    ? default_interpolator_compound
    : default_interpolator_not_available
>
{
    o_rebind(default_interpolator)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct interpolator
///
/// \brief  interpolator.
/// 		Provides interpolation from a start value to and end value
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct interpolator : public default_interpolator<t_Ty>
{
};

o_namespace_end(phantom)

#endif // o_def_interpolator_h__