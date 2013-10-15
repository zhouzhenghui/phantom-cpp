// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_CUSTOM_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_CUSTOM_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree_custom/detail/file_parser_error.hpp>
#include <string>

namespace boost { namespace property_tree_custom { namespace xml_parser
{

    //! Xml parser error
	template <typename Str>
    class xml_parser_error: public file_parser_error<Str>
    {
    public:
        xml_parser_error(const Str &msg,
                         const Str &file,
                         unsigned long l):
            file_parser_error<Str>(msg, file, l)
        {
        }
    };

} } }

#endif
