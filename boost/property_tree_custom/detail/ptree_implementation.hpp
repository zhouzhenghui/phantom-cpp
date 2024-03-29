// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_CUSTOM_DETAIL_PTREE_IMPLEMENTATION_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_CUSTOM_DETAIL_PTREE_IMPLEMENTATION_HPP_INCLUDED

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <memory>
#include <cassert>

#if defined(BOOST_MSVC) && \
    (_MSC_FULL_VER >= 160000000 && _MSC_FULL_VER < 170000000)
#define BOOST_PROPERTY_TREE_CUSTOM_PAIR_BUG
#endif

namespace boost { namespace property_tree_custom
{
    template <class K, class D, class A, class S, class C>
    struct basic_ptree<K, D, A, S, C>::subs
    {
        struct by_name {};
        // The actual child container.
#if defined(BOOST_PROPERTY_TREE_CUSTOM_PAIR_BUG)
        // MSVC 10 has moved std::pair's members to a base
        // class. Unfortunately this does break the interface.
        BOOST_STATIC_CONSTANT(unsigned,
            first_offset = offsetof(value_type, first));
        typedef multi_index_container<value_type,
            multi_index::indexed_by<
                multi_index::sequenced<>,
                multi_index::ordered_non_unique<multi_index::tag<by_name>,
                    multi_index::member_offset<value_type, const key_type,
                                        first_offset>,
                    key_compare
                >
            >
        > base_container;
#else
        typedef multi_index_container<value_type,
            multi_index::indexed_by<
                multi_index::sequenced<>,
                multi_index::ordered_non_unique<multi_index::tag<by_name>,
                    multi_index::member<value_type, const key_type,
                                        &value_type::first>,
                    key_compare
                >
            >
        > base_container;
#endif
        // The by-name lookup index.
        typedef typename base_container::template index<by_name>::type
            by_name_index;

        // Access functions for getting to the children of a tree.
        static base_container& ch(self_type *s) {
            return *static_cast<base_container*>(s->m_children);
        }
        static const base_container& ch(const self_type *s) {
            return *static_cast<const base_container*>(s->m_children);
        }
        static by_name_index& assoc(self_type *s) {
            return ch(s).BOOST_NESTED_TEMPLATE get<by_name>();
        }
        static const by_name_index& assoc(const self_type *s) {
            return ch(s).BOOST_NESTED_TEMPLATE get<by_name>();
        }
    };
    template <class K, class D, class A, class S, class C>
    class basic_ptree<K, D, A, S, C>::iterator : public boost::iterator_adaptor<
        iterator, typename subs::base_container::iterator, value_type>
    {
        friend class boost::iterator_core_access;
        typedef boost::iterator_adaptor<
            iterator, typename subs::base_container::iterator, value_type>
            baset;
    public:
        typedef typename baset::reference reference;
        iterator() {}
        explicit iterator(typename iterator::base_type b)
            : iterator::iterator_adaptor_(b)
        {}
        reference dereference() const
        {
            // multi_index doesn't allow modification of its values, because
            // indexes could sort by anything, and modification screws that up.
            // However, we only sort by the key, and it's protected against
            // modification in the value_type, so this const_cast is safe.
            return const_cast<reference>(*this->base_reference());
        }
    };
    template <class K, class D, class A, class S, class C>
    class basic_ptree<K, D, A, S, C>::const_iterator : public boost::iterator_adaptor<
        const_iterator, typename subs::base_container::const_iterator>
    {
    public:
        const_iterator() {}
        explicit const_iterator(typename const_iterator::base_type b)
            : const_iterator::iterator_adaptor_(b)
        {}
        const_iterator(iterator b)
            : const_iterator::iterator_adaptor_(b.base())
        {}
    };
    template <class K, class D, class A, class S, class C>
    class basic_ptree<K, D, A, S, C>::reverse_iterator
        : public boost::reverse_iterator<iterator>
    {
    public:
        reverse_iterator() {}
        explicit reverse_iterator(iterator b)
            : boost::reverse_iterator<iterator>(b)
        {}
    };
    template <class K, class D, class A, class S, class C>
    class basic_ptree<K, D, A, S, C>::const_reverse_iterator
        : public boost::reverse_iterator<const_iterator>
    {
    public:
        const_reverse_iterator() {}
        explicit const_reverse_iterator(const_iterator b)
            : boost::reverse_iterator<const_iterator>(b)
        {}
        const_reverse_iterator(
            typename basic_ptree<K, D, A, S, C>::reverse_iterator b)
            : boost::reverse_iterator<const_iterator>(b)
        {}
    };
    template <class K, class D, class A, class S, class C>
    class basic_ptree<K, D, A, S, C>::assoc_iterator
        : public boost::iterator_adaptor<assoc_iterator,
                                         typename subs::by_name_index::iterator,
                                         value_type>
    {
        friend class boost::iterator_core_access;
        typedef boost::iterator_adaptor<assoc_iterator,
                                         typename subs::by_name_index::iterator,
                                         value_type>
            baset;
    public:
        typedef typename baset::reference reference;
        assoc_iterator() {}
        explicit assoc_iterator(typename assoc_iterator::base_type b)
            : assoc_iterator::iterator_adaptor_(b)
        {}
        reference dereference() const
        {
            return const_cast<reference>(*this->base_reference());
        }
    };
    template <class K, class D, class A, class S, class C>
    class basic_ptree<K, D, A, S, C>::const_assoc_iterator
        : public boost::iterator_adaptor<const_assoc_iterator,
                                   typename subs::by_name_index::const_iterator>
    {
    public:
        const_assoc_iterator() {}
        explicit const_assoc_iterator(
            typename const_assoc_iterator::base_type b)
            : const_assoc_iterator::iterator_adaptor_(b)
        {}
        const_assoc_iterator(assoc_iterator b)
            : const_assoc_iterator::iterator_adaptor_(b.base())
        {}
    };


    // Big five

    // Perhaps the children collection could be created on-demand only, to
    // reduce heap traffic. But that's a lot more work to implement.

    template<class K, class D, class A, class S, class C> inline
    basic_ptree<K, D, A, S, C>::basic_ptree()
        : m_children(new (A::BOOST_NESTED_TEMPLATE rebind<typename subs::base_container>::other::allocate()) typename subs::base_container)
    {
    }

    template<class K, class D, class A, class S, class C> inline
    basic_ptree<K, D, A, S, C>::basic_ptree(const data_type &d)
        : m_data(d), m_children(new (A::BOOST_NESTED_TEMPLATE rebind<typename subs::base_container>::other::allocate()) typename subs::base_container)
    {
    }

    template<class K, class D, class A, class S, class C> inline
    basic_ptree<K, D, A, S, C>::basic_ptree(const basic_ptree<K, D, A, S, C> &rhs)
        : m_data(rhs.m_data),
          m_children(new (A::BOOST_NESTED_TEMPLATE rebind<typename subs::base_container>::other::allocate()) typename subs::base_container(subs::ch(&rhs)))
    {
    }

    template<class K, class D, class A, class S, class C>
    basic_ptree<K, D, A, S, C> &
        basic_ptree<K, D, A, S, C>::operator =(const basic_ptree<K, D, A, S, C> &rhs)
    {
        self_type(rhs).swap(*this);
        return *this;
    }

    template<class K, class D, class A, class S, class C>
    basic_ptree<K, D, A, S, C>::~basic_ptree()
    {
		typedef typename subs::base_container base_c;
		base_c* ptr = &subs::ch(this);
		ptr->~base_c();
		A::BOOST_NESTED_TEMPLATE rebind<base_c>::other::deallocate(ptr);
    }

    template<class K, class D, class A, class S, class C> inline
    void basic_ptree<K, D, A, S, C>::swap(basic_ptree<K, D, A, S, C> &rhs)
    {
        m_data.swap(rhs.m_data);
        // Void pointers, no ADL necessary
        std::swap(m_children, rhs.m_children);
    }

    // Container view

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::size_type
        basic_ptree<K, D, A, S, C>::size() const
    {
        return subs::ch(this).size();
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::size_type
        basic_ptree<K, D, A, S, C>::max_size() const
    {
        return subs::ch(this).max_size();
    }

    template<class K, class D, class A, class S, class C> inline
    bool basic_ptree<K, D, A, S, C>::empty() const
    {
        return subs::ch(this).empty();
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::iterator
        basic_ptree<K, D, A, S, C>::begin()
    {
        return iterator(subs::ch(this).begin());
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::const_iterator
        basic_ptree<K, D, A, S, C>::begin() const
    {
        return const_iterator(subs::ch(this).begin());
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::iterator
        basic_ptree<K, D, A, S, C>::end()
    {
        return iterator(subs::ch(this).end());
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::const_iterator
        basic_ptree<K, D, A, S, C>::end() const
    {
        return const_iterator(subs::ch(this).end());
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::reverse_iterator
        basic_ptree<K, D, A, S, C>::rbegin()
    {
        return reverse_iterator(this->end());
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::const_reverse_iterator
        basic_ptree<K, D, A, S, C>::rbegin() const
    {
        return const_reverse_iterator(this->end());
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::reverse_iterator
        basic_ptree<K, D, A, S, C>::rend()
    {
        return reverse_iterator(this->begin());
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::const_reverse_iterator
        basic_ptree<K, D, A, S, C>::rend() const
    {
        return const_reverse_iterator(this->begin());
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::value_type &
        basic_ptree<K, D, A, S, C>::front()
    {
        return const_cast<value_type&>(subs::ch(this).front());
    }

    template<class K, class D, class A, class S, class C> inline
    const typename basic_ptree<K, D, A, S, C>::value_type &
        basic_ptree<K, D, A, S, C>::front() const
    {
        return subs::ch(this).front();
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::value_type &
        basic_ptree<K, D, A, S, C>::back()
    {
        return const_cast<value_type&>(subs::ch(this).back());
    }

    template<class K, class D, class A, class S, class C> inline
    const typename basic_ptree<K, D, A, S, C>::value_type &
        basic_ptree<K, D, A, S, C>::back() const
    {
        return subs::ch(this).back();
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::iterator
    basic_ptree<K, D, A, S, C>::insert(iterator where, const value_type &value)
    {
        return iterator(subs::ch(this).insert(where.base(), value).first);
    }

    template<class K, class D, class A, class S, class C>
    template<class It> inline
    void basic_ptree<K, D, A, S, C>::insert(iterator where, It first, It last)
    {
        subs::ch(this).insert(where.base(), first, last);
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::iterator
        basic_ptree<K, D, A, S, C>::erase(iterator where)
    {
        return iterator(subs::ch(this).erase(where.base()));
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::iterator
        basic_ptree<K, D, A, S, C>::erase(iterator first, iterator last)
    {
        return iterator(subs::ch(this).erase(first.base(), last.base()));
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::iterator
        basic_ptree<K, D, A, S, C>::push_front(const value_type &value)
    {
        return iterator(subs::ch(this).push_front(value).first);
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::iterator
        basic_ptree<K, D, A, S, C>::push_back(const value_type &value)
    {
        return iterator(subs::ch(this).push_back(value).first);
    }

    template<class K, class D, class A, class S, class C> inline
    void basic_ptree<K, D, A, S, C>::pop_front()
    {
        subs::ch(this).pop_front();
    }

    template<class K, class D, class A, class S, class C> inline
    void basic_ptree<K, D, A, S, C>::pop_back()
    {
        subs::ch(this).pop_back();
    }

    template<class K, class D, class A, class S, class C> inline
    void basic_ptree<K, D, A, S, C>::reverse()
    {
        subs::ch(this).reverse();
    }

    template<class K, class D, class A, class S, class C> inline
    void basic_ptree<K, D, A, S, C>::sort()
    {
        subs::ch(this).sort();
    }

    template<class K, class D, class A, class S, class C>
    template<class Compare> inline
    void basic_ptree<K, D, A, S, C>::sort(Compare comp)
    {
        subs::ch(this).sort(comp);
    }

    // Equality

    template<class K, class D, class A, class S, class C> inline
    bool basic_ptree<K, D, A, S, C>::operator ==(
                                  const basic_ptree<K, D, A, S, C> &rhs) const
    {
        // The size test is cheap, so add it as an optimization
        return size() == rhs.size() && data() == rhs.data() &&
            subs::ch(this) == subs::ch(&rhs);
    }

    template<class K, class D, class A, class S, class C> inline
    bool basic_ptree<K, D, A, S, C>::operator !=(
                                  const basic_ptree<K, D, A, S, C> &rhs) const
    {
        return !(*this == rhs);
    }

    // Associative view

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::assoc_iterator
        basic_ptree<K, D, A, S, C>::ordered_begin()
    {
        return assoc_iterator(subs::assoc(this).begin());
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::const_assoc_iterator
        basic_ptree<K, D, A, S, C>::ordered_begin() const
    {
        return const_assoc_iterator(subs::assoc(this).begin());
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::assoc_iterator
        basic_ptree<K, D, A, S, C>::not_found()
    {
        return assoc_iterator(subs::assoc(this).end());
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::const_assoc_iterator
        basic_ptree<K, D, A, S, C>::not_found() const
    {
        return const_assoc_iterator(subs::assoc(this).end());
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::assoc_iterator
        basic_ptree<K, D, A, S, C>::find(const key_type &key)
    {
        return assoc_iterator(subs::assoc(this).find(key));
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::const_assoc_iterator
        basic_ptree<K, D, A, S, C>::find(const key_type &key) const
    {
        return const_assoc_iterator(subs::assoc(this).find(key));
    }

    template<class K, class D, class A, class S, class C> inline
    std::pair<
        typename basic_ptree<K, D, A, S, C>::assoc_iterator,
        typename basic_ptree<K, D, A, S, C>::assoc_iterator
    > basic_ptree<K, D, A, S, C>::equal_range(const key_type &key)
    {
        std::pair<typename subs::by_name_index::iterator,
                  typename subs::by_name_index::iterator> r(
            subs::assoc(this).equal_range(key));
        return std::pair<assoc_iterator, assoc_iterator>(
          assoc_iterator(r.first), assoc_iterator(r.second));
    }

    template<class K, class D, class A, class S, class C> inline
    std::pair<
        typename basic_ptree<K, D, A, S, C>::const_assoc_iterator,
        typename basic_ptree<K, D, A, S, C>::const_assoc_iterator
    > basic_ptree<K, D, A, S, C>::equal_range(const key_type &key) const
    {
        std::pair<typename subs::by_name_index::const_iterator,
                  typename subs::by_name_index::const_iterator> r(
            subs::assoc(this).equal_range(key));
        return std::pair<const_assoc_iterator, const_assoc_iterator>(
            const_assoc_iterator(r.first), const_assoc_iterator(r.second));
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::size_type
        basic_ptree<K, D, A, S, C>::count(const key_type &key) const
    {
        return subs::assoc(this).count(key);
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::size_type
        basic_ptree<K, D, A, S, C>::erase(const key_type &key)
    {
        return subs::assoc(this).erase(key);
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::iterator
        basic_ptree<K, D, A, S, C>::to_iterator(assoc_iterator ai)
    {
        return iterator(subs::ch(this).
            BOOST_NESTED_TEMPLATE project<0>(ai.base()));
    }

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::const_iterator
        basic_ptree<K, D, A, S, C>::to_iterator(const_assoc_iterator ai) const
    {
        return const_iterator(subs::ch(this).
            BOOST_NESTED_TEMPLATE project<0>(ai.base()));
    }

    // Property tree view

    template<class K, class D, class A, class S, class C> inline
    typename basic_ptree<K, D, A, S, C>::data_type &
        basic_ptree<K, D, A, S, C>::data()
    {
        return m_data;
    }

    template<class K, class D, class A, class S, class C> inline
    const typename basic_ptree<K, D, A, S, C>::data_type &
        basic_ptree<K, D, A, S, C>::data() const
    {
        return m_data;
    }

    template<class K, class D, class A, class S, class C> inline
    void basic_ptree<K, D, A, S, C>::clear()
    {
        m_data = data_type();
        subs::ch(this).clear();
    }

    template<class K, class D, class A, class S, class C>
    basic_ptree<K, D, A, S, C> &
        basic_ptree<K, D, A, S, C>::get_child(const path_type &path)
    {
        path_type p(path);
        self_type *n = walk_path(p);
        if (!n) {
            BOOST_PROPERTY_TREE_CUSTOM_THROW(ptree_bad_path<string_type>("No such node", path));
        }
        return *n;
    }

    template<class K, class D, class A, class S, class C> inline
    const basic_ptree<K, D, A, S, C> &
        basic_ptree<K, D, A, S, C>::get_child(const path_type &path) const
    {
        return const_cast<self_type*>(this)->get_child(path);
    }

    template<class K, class D, class A, class S, class C> inline
    basic_ptree<K, D, A, S, C> &
        basic_ptree<K, D, A, S, C>::get_child(const path_type &path,
                                        self_type &default_value)
    {
        path_type p(path);
        self_type *n = walk_path(p);
        return n ? *n : default_value;
    }

    template<class K, class D, class A, class S, class C> inline
    const basic_ptree<K, D, A, S, C> &
        basic_ptree<K, D, A, S, C>::get_child(const path_type &path,
                                        const self_type &default_value) const
    {
        return const_cast<self_type*>(this)->get_child(path,
            const_cast<self_type&>(default_value));
    }


    template<class K, class D, class A, class S, class C>
    optional<basic_ptree<K, D, A, S, C> &>
        basic_ptree<K, D, A, S, C>::get_child_optional(const path_type &path)
    {
        path_type p(path);
        self_type *n = walk_path(p);
        if (!n) {
            return optional<self_type&>();
        }
        return *n;
    }

    template<class K, class D, class A, class S, class C>
    optional<const basic_ptree<K, D, A, S, C> &>
        basic_ptree<K, D, A, S, C>::get_child_optional(const path_type &path) const
    {
        path_type p(path);
        self_type *n = walk_path(p);
        if (!n) {
            return optional<const self_type&>();
        }
        return *n;
    }

    template<class K, class D, class A, class S, class C>
    basic_ptree<K, D, A, S, C> &
        basic_ptree<K, D, A, S, C>::put_child(const path_type &path,
                                        const self_type &value)
    {
        path_type p(path);
        self_type &parent = force_path(p);
        // Got the parent. Now get the correct child.
        key_type fragment = p.reduce();
        assoc_iterator el = parent.find(fragment);
        // If the new child exists, replace it.
        if(el != parent.not_found()) {
            return el->second = value;
        } else {
            return parent.push_back(value_type(fragment, value))->second;
        }
    }

    template<class K, class D, class A, class S, class C>
    basic_ptree<K, D, A, S, C> &
        basic_ptree<K, D, A, S, C>::add_child(const path_type &path,
                                        const self_type &value)
    {
        path_type p(path);
        self_type &parent = force_path(p);
        // Got the parent.
        key_type fragment = p.reduce();
        return parent.push_back(value_type(fragment, value))->second;
    }

    template<class K, class D, class A, class S, class C>
    template<class Type, class Translator>
    typename boost::enable_if<detail::is_translator<Translator>, Type>::type
    basic_ptree<K, D, A, S, C>::get_value(Translator tr) const
    {
        if(boost::optional<Type> o = get_value_optional<Type>(tr)) {
            return *o;
        }
        BOOST_PROPERTY_TREE_CUSTOM_THROW(ptree_bad_data<string_type>(
            string_type("conversion of data to type \"") +
            typeid(Type).name() + "\" failed", data()));
    }

    template<class K, class D, class A, class S, class C>
    template<class Type> inline
    Type basic_ptree<K, D, A, S, C>::get_value() const
    {
        return get_value<Type>(
            typename translator_between<data_type, Type>::type());
    }

    template<class K, class D, class A, class S, class C>
    template<class Type, class Translator> inline
    Type basic_ptree<K, D, A, S, C>::get_value(const Type &default_value,
                                         Translator tr) const
    {
        return get_value_optional<Type>(tr).get_value_or(default_value);
    }

    template<class K, class D, class A, class S, class C>
    template <class Ch, class Translator>
    typename boost::enable_if<
        detail::is_character<Ch>,
        typename basic_ptree<K, D, A, S, C>:: BOOST_NESTED_TEMPLATE for_char<Ch>::basic_string
    >::type
    basic_ptree<K, D, A, S, C>::get_value(const Ch *default_value, Translator tr)const
    {
        return get_value<typename basic_ptree<K, D, A, S, C>::string_type, Translator>(default_value, tr);
    }

    template<class K, class D, class A, class S, class C>
    template<class Type> inline
    typename boost::disable_if<detail::is_translator<Type>, Type>::type
    basic_ptree<K, D, A, S, C>::get_value(const Type &default_value) const
    {
        return get_value(default_value,
                         typename translator_between<data_type, Type>::type());
    }

    template<class K, class D, class A, class S, class C>
    template <class Ch>
    typename boost::enable_if<
        detail::is_character<Ch>,
        typename basic_ptree<K, D, A, S, C>::BOOST_NESTED_TEMPLATE for_char<Ch>::basic_string
    >::type
    basic_ptree<K, D, A, S, C>::get_value(const Ch *default_value) const
    {
        return get_value< typename basic_ptree<K, D, A, S, C>::string_type >(default_value);
    }

    template<class K, class D, class A, class S, class C>
    template<class Type, class Translator> inline
    optional<Type> basic_ptree<K, D, A, S, C>::get_value_optional(
                                                Translator tr) const
    {
        return tr.get_value(data());
    }

    template<class K, class D, class A, class S, class C>
    template<class Type> inline
    optional<Type> basic_ptree<K, D, A, S, C>::get_value_optional() const
    {
        return get_value_optional<Type>(
            typename translator_between<data_type, Type>::type());
    }

    template<class K, class D, class A, class S, class C>
    template<class Type, class Translator> inline
    typename boost::enable_if<detail::is_translator<Translator>, Type>::type
    basic_ptree<K, D, A, S, C>::get(const path_type &path,
                              Translator tr) const
    {
        return get_child(path).BOOST_NESTED_TEMPLATE get_value<Type>(tr);
    }

    template<class K, class D, class A, class S, class C>
    template<class Type> inline
    Type basic_ptree<K, D, A, S, C>::get(const path_type &path) const
    {
        return get_child(path).BOOST_NESTED_TEMPLATE get_value<Type>();
    }

    template<class K, class D, class A, class S, class C>
    template<class Type, class Translator> inline
    Type basic_ptree<K, D, A, S, C>::get(const path_type &path,
                                   const Type &default_value,
                                   Translator tr) const
    {
        return get_optional<Type>(path, tr).get_value_or(default_value);
    }

    template<class K, class D, class A, class S, class C>
    template <class Ch, class Translator>
    typename boost::enable_if<
        detail::is_character<Ch>,
        typename basic_ptree<K, D, A, S, C>::BOOST_NESTED_TEMPLATE for_char<Ch>::basic_string
    >::type
    basic_ptree<K, D, A, S, C>::get(
        const path_type &path, const Ch *default_value, Translator tr) const
    {
        return get<typename basic_ptree<K, D, A, S, C>::BOOST_NESTED_TEMPLATE for_char<Ch>::basic_string, Translator>(path, default_value, tr);
    }

    template<class K, class D, class A, class S, class C>
    template<class Type> inline
    typename boost::disable_if<detail::is_translator<Type>, Type>::type
    basic_ptree<K, D, A, S, C>::get(const path_type &path,
                              const Type &default_value) const
    {
        return get_optional<Type>(path).get_value_or(default_value);
    }

    template<class K, class D, class A, class S, class C>
    template <class Ch>
    typename boost::enable_if<
        detail::is_character<Ch>,
        typename basic_ptree<K, D, A, S, C>::BOOST_NESTED_TEMPLATE for_char<Ch>::basic_string
    >::type
    basic_ptree<K, D, A, S, C>::get(
        const path_type &path, const Ch *default_value) const
    {
        return get< typename basic_ptree<K, D, A, S, C>::BOOST_NESTED_TEMPLATE for_char<Ch>::basic_string >(path, default_value);
    }

    template<class K, class D, class A, class S, class C>
    template<class Type, class Translator>
    optional<Type> basic_ptree<K, D, A, S, C>::get_optional(const path_type &path,
                                                         Translator tr) const
    {
        if (optional<const self_type&> child = get_child_optional(path))
            return child.get().
                BOOST_NESTED_TEMPLATE get_value_optional<Type>(tr);
        else
            return optional<Type>();
    }

    template<class K, class D, class A, class S, class C>
    template<class Type>
    optional<Type> basic_ptree<K, D, A, S, C>::get_optional(
                                                const path_type &path) const
    {
        if (optional<const self_type&> child = get_child_optional(path))
            return child.get().BOOST_NESTED_TEMPLATE get_value_optional<Type>();
        else
            return optional<Type>();
    }

    template<class K, class D, class A, class S, class C>
    template<class Type, class Translator>
    void basic_ptree<K, D, A, S, C>::put_value(const Type &value, Translator tr)
    {
        if(optional<data_type> o = tr.put_value(value)) {
            data() = *o;
        } else {
            BOOST_PROPERTY_TREE_CUSTOM_THROW(ptree_bad_data<string_type>(
                string_type("conversion of type \"") + typeid(Type).name() +
                "\" to data failed", boost::any()));
        }
    }

    template<class K, class D, class A, class S, class C>
    template<class Type> inline
    void basic_ptree<K, D, A, S, C>::put_value(const Type &value)
    {
        put_value(value, typename translator_between<data_type, Type>::type());
    }

    template<class K, class D, class A, class S, class C>
    template<class Type, typename Translator>
    basic_ptree<K, D, A, S, C> & basic_ptree<K, D, A, S, C>::put(
        const path_type &path, const Type &value, Translator tr)
    {
        if(optional<self_type &> child = get_child_optional(path)) {
            child.get().put_value(value, tr);
            return *child;
        } else {
            self_type &child2 = put_child(path, self_type());
            child2.put_value(value, tr);
            return child2;
        }
    }

    template<class K, class D, class A, class S, class C>
    template<class Type> inline
    basic_ptree<K, D, A, S, C> & basic_ptree<K, D, A, S, C>::put(
        const path_type &path, const Type &value)
    {
        return put(path, value,
                   typename translator_between<data_type, Type>::type());
    }

    template<class K, class D, class A, class S, class C>
    template<class Type, typename Translator> inline
    basic_ptree<K, D, A, S, C> & basic_ptree<K, D, A, S, C>::add(
        const path_type &path, const Type &value, Translator tr)
    {
        self_type &child = add_child(path, self_type());
        child.put_value(value, tr);
        return child;
    }

    template<class K, class D, class A, class S, class C>
    template<class Type> inline
    basic_ptree<K, D, A, S, C> & basic_ptree<K, D, A, S, C>::add(
        const path_type &path, const Type &value)
    {
        return add(path, value,
                   typename translator_between<data_type, Type>::type());
    }


    template<class K, class D, class A, class S, class C>
    basic_ptree<K, D, A, S, C> *
    basic_ptree<K, D, A, S, C>::walk_path(path_type &p) const
    {
        if(p.empty()) {
            // I'm the child we're looking for.
            return const_cast<basic_ptree*>(this);
        }
        // Recurse down the tree to find the path.
        key_type fragment = p.reduce();
        const_assoc_iterator el = find(fragment);
        if(el == not_found()) {
            // No such child.
            return 0;
        }
        // Not done yet, recurse.
        return el->second.walk_path(p);
    }

    template<class K, class D, class A, class S, class C>
    basic_ptree<K, D, A, S, C> & basic_ptree<K, D, A, S, C>::force_path(path_type &p)
    {
        assert(!p.empty() && "Empty path not allowed for put_child.");
        if(p.single()) {
            // I'm the parent we're looking for.
            return *this;
        }
        key_type fragment = p.reduce();
        assoc_iterator el = find(fragment);
        // If we've found an existing child, go down that path. Else
        // create a new one.
        self_type& child = el == not_found() ?
            push_back(value_type(fragment, self_type()))->second : el->second;
        return child.force_path(p);
    }

    // Free functions

    template<class K, class D, class A, class S, class C>
    inline void swap(basic_ptree<K, D, A, S, C> &pt1, basic_ptree<K, D, A, S, C> &pt2)
    {
        pt1.swap(pt2);
    }

} }

#if defined(BOOST_PROPERTY_TREE_CUSTOM_PAIR_BUG)
#undef BOOST_PROPERTY_TREE_CUSTOM_PAIR_BUG
#endif

#endif
