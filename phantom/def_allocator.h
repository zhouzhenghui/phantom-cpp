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

#ifndef o_def_allocator_h__
#define o_def_allocator_h__

o_namespace_begin(phantom)


template<typename t_Ty>
struct default_allocator : public o__t1_class__default_class_allocator(t_Ty)
{
    o_rebind(default_allocator)
};

/**
 * \struct allocator_inheritance_base_index
 *
 * \brief Allocator inheritance base index. You can specialize it to specify from which base class a class must inherit its allocator.
 * 		  By default it's the first base class (index 0)
 */
namespace detail 
{

    template<typename t_Ty>
    struct allocator_inheritance_base_index
    {
        BOOST_STATIC_CONSTANT(size_t, value = 0);
    };

    template<typename t_Ty, bool t_inherits_allocator>
    struct allocator_inheritance_helper
        : public
        phantom::allocator<
         o_traits_t_Ty_base_class(allocator_inheritance_base_index<t_Ty>::value)
        >
        ::o_NESTED_TEMPLATE rebind<t_Ty>::other
    {
    ///< We inherits allocator thanks to type template rebinding.
    };

    template<typename t_Ty>
    struct allocator_inheritance_helper <t_Ty, false>
        : public default_allocator<t_Ty>
    {
    ///< If we don't inherit from a base allocator, we use default one.
    };
}

template<typename t_Ty>
struct inherited_allocator : public detail::allocator_inheritance_helper<
    t_Ty
    , base_class_count_of<t_Ty>::value != 0 AND ((meta_specifiers<t_Ty>::value & o_inherits_allocator) == o_inherits_allocator)
>
{
    typedef detail::allocator_inheritance_helper<
        t_Ty
        , base_class_count_of<t_Ty>::value != 0 AND ((meta_specifiers<t_Ty>::value & o_inherits_allocator) == o_inherits_allocator)
    >  base_type;
    o_forceinline static t_Ty* allocate() { return base_type::allocate(); }
    o_forceinline static void deallocate(t_Ty* a_pInstance) { base_type::deallocate(a_pInstance); }
    o_forceinline static t_Ty* allocate(size_t a_uiCount) { return base_type::allocate(a_uiCount); }
    o_forceinline static void deallocate(t_Ty* a_pInstance, size_t a_uiCount) { base_type::deallocate(a_pInstance,a_uiCount);  }
};

template<>
struct default_allocator<void>
{
//#pragma message(o_PP_QUOTE(o_exception(unsupported_member_function_exception)))
    o_forceinline static void* allocate() { o_exception(unsupported_member_function_exception); return NULL;  }
    o_forceinline static void deallocate(void* a_pInstance) { o_exception(unsupported_member_function_exception); }
    o_forceinline static void* allocate(size_t a_uiCount) { o_exception(unsupported_member_function_exception); return NULL; }
    o_forceinline static void deallocate(void* a_pInstance, size_t a_uiCount) { o_exception(unsupported_member_function_exception); }
};
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct allocator
///
/// \brief  Allocator. (see instance creation process)
/// 		Allocation / Deallocation : by default phantom uses boost::fast_pool_allocator to allocate instance memory.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct allocator : public o_memory_stat_allocator(t_Ty, inherited_allocator<t_Ty>)
{
};

template<>
struct allocator<void> 
{
    o_forceinline static void* allocate(o_memory_stat_insert_parameters) { o_error(false, "cannot allocate void"); return nullptr; }
    o_forceinline static void deallocate(void* a_pInstance o_memory_stat_append_parameters) { o_error(false, "cannot deallocate void");  }
    o_forceinline static void* allocate(size_t a_uiCount o_memory_stat_append_parameters) { o_error(false, "cannot allocate void"); return nullptr;}
    o_forceinline static void deallocate(void* a_pInstance, size_t a_uiCount o_memory_stat_append_parameters) { o_error(false, "cannot deallocate void"); }
};

o_namespace_end(phantom)

#endif // o_def_allocator_h__