// ----------------------------------------------------------------------------
// Copyright (C) 2007 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_CUSTOM_DETAIL_XML_PARSER_READ_RAPIDXML_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_CUSTOM_DETAIL_XML_PARSER_READ_RAPIDXML_HPP_INCLUDED

#include <boost/property_tree_custom/ptree.hpp>
#include <boost/property_tree_custom/detail/xml_parser_error.hpp>
#include <boost/property_tree_custom/detail/xml_parser_flags.hpp>
#include <boost/property_tree_custom/detail/xml_parser_utils.hpp>
#include <boost/property_tree_custom/detail/rapidxml.hpp>
#include <vector>

namespace boost { namespace property_tree_custom { namespace xml_parser
{

    template<class Ptree, class Ch>
    void read_xml_node(detail::rapidxml::xml_node<Ch> *node,
                       Ptree &pt, int flags)
    {
		typedef typename Ptree::BOOST_NESTED_TEMPLATE for_char<Ch>::basic_string Str;
        using namespace detail::rapidxml;
        switch (node->type())
        {
            // Element nodes
            case node_element:
            {
                // Create node
                Ptree &pt_node = pt.push_back(std::make_pair(node->name(),
                                                             Ptree()))->second;

                // Copy attributes
                if (node->first_attribute())
                {
                    Ptree &pt_attr_root = pt_node.push_back(
                        std::make_pair(xmlattr<Str>(), Ptree()))->second;
                    for (xml_attribute<Ch> *attr = node->first_attribute();
                         attr; attr = attr->next_attribute())
                    {
                        Ptree &pt_attr = pt_attr_root.push_back(
                            std::make_pair(attr->name(), Ptree()))->second;
                        pt_attr.data() = attr->value();
                    }
                }

                // Copy children
                for (xml_node<Ch> *child = node->first_node();
                     child; child = child->next_sibling())
                    read_xml_node(child, pt_node, flags);
            }
            break;

            // Data nodes
            case node_data:
            case node_cdata:
            {
                if (flags & no_concat_text)
                    pt.push_back(std::make_pair(xmltext<Str>(),
                                                Ptree(node->value())));
                else
                    pt.data() += node->value();
            }
            break;

            // Comment nodes
            case node_comment:
            {
                if (!(flags & no_comments))
                    pt.push_back(std::make_pair(xmlcomment<Str>(),
                                                Ptree(node->value())));
            }
            break;

            default:
                // Skip other node types
                break;
        }
    }

    template<class Ptree>
    void read_xml_internal(typename Ptree::key_basic_istream &stream,
                           Ptree &pt,
                           int flags,
                           const typename Ptree::string_type &filename)
    {
        typedef typename Ptree::key_type::value_type Ch;
        using namespace detail::rapidxml;

        // Load data into vector
        stream.unsetf(std::ios::skipws);
        typename Ptree::BOOST_NESTED_TEMPLATE for_anytype<Ch>::vector v(std::istreambuf_iterator<Ch>(stream.rdbuf()),
                          std::istreambuf_iterator<Ch>());
        if (!stream.good())
            BOOST_PROPERTY_TREE_CUSTOM_THROW(
                xml_parser_error<typename Ptree::string_type>("read error", filename, 0));
        v.push_back(0); // zero-terminate

        try {
            // Parse using appropriate flags
            const int f_tws = parse_normalize_whitespace
                            | parse_trim_whitespace;
            const int f_c = parse_comment_nodes;
            // Some compilers don't like the bitwise or in the template arg.
            const int f_tws_c = parse_normalize_whitespace
                              | parse_trim_whitespace
                              | parse_comment_nodes;
            xml_document<Ch> doc;
            if (flags & no_comments) {
                if (flags & trim_whitespace)
                    doc.BOOST_NESTED_TEMPLATE parse<f_tws>(&v.front());
                else
                    doc.BOOST_NESTED_TEMPLATE parse<0>(&v.front());
            } else {
                if (flags & trim_whitespace)
                    doc.BOOST_NESTED_TEMPLATE parse<f_tws_c>(&v.front());
                else
                    doc.BOOST_NESTED_TEMPLATE parse<f_c>(&v.front());
            }

            // Create ptree from nodes
            Ptree local;
            for (xml_node<Ch> *child = doc.first_node();
                 child; child = child->next_sibling())
                read_xml_node(child, local, flags);

            // Swap local and result ptrees
            pt.swap(local);
        } catch (parse_error &e) {
            long line = static_cast<long>(
                std::count(&v.front(), e.where<Ch>(), Ch('\n')) + 1);
            BOOST_PROPERTY_TREE_CUSTOM_THROW(
                xml_parser_error<typename Ptree::string_type>(e.what(), filename, line));
        }
    }

} } }

#endif
