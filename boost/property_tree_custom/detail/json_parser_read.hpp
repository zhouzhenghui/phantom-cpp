// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_CUSTOM_DETAIL_JSON_PARSER_READ_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_CUSTOM_DETAIL_JSON_PARSER_READ_HPP_INCLUDED

//#define BOOST_SPIRIT_DEBUG

#include <boost/property_tree_custom/ptree.hpp>
#include <boost/property_tree_custom/detail/ptree_utils.hpp>
#include <boost/property_tree_custom/detail/json_parser_error.hpp>
#include <boost/spirit/include/classic.hpp>
#include <boost/limits.hpp>
#include <string>
#include <locale>
#include <istream>
#include <vector>
#include <algorithm>

namespace boost { namespace property_tree_custom { namespace json_parser
{

    ///////////////////////////////////////////////////////////////////////
    // Json parser context
        
    template<class Ptree>
    struct context
    {

        typedef typename Ptree::key_type::value_type Ch;
        typedef typename Ptree::BOOST_NESTED_TEMPLATE for_char<Ch>::basic_string Str;
        typedef typename Ptree::BOOST_NESTED_TEMPLATE for_anytype<Ch>::vector::iterator It;
        
        Str string;
        Str name;
        Ptree root;
        typename Ptree::BOOST_NESTED_TEMPLATE for_anytype<Ptree*>::vector  stack;

        struct a_object_s
        {
            context &c;
            a_object_s(context &c): c(c) { }
            void operator()(Ch) const
            {
                if (c.stack.empty())
                    c.stack.push_back(&c.root);
                else
                {
                    Ptree *parent = c.stack.back();
                    Ptree *child = &parent->push_back(std::make_pair(c.name, Ptree()))->second;
                    c.stack.push_back(child);
                    c.name.clear();
                }
            }
        };
        
        struct a_object_e
        {
            context &c;
            a_object_e(context &c): c(c) { }
            void operator()(Ch) const
            {
                BOOST_ASSERT(c.stack.size() >= 1);
                c.stack.pop_back();
            }
        };

        struct a_name
        {
            context &c;
            a_name(context &c): c(c) { }
            void operator()(It, It) const
            {
                c.name.swap(c.string);
                c.string.clear();
            }
        };

        struct a_string_val
        {
            context &c;
            a_string_val(context &c): c(c) { }
            void operator()(It, It) const
            {
                BOOST_ASSERT(c.stack.size() >= 1);
                c.stack.back()->push_back(std::make_pair(c.name, Ptree(c.string)));
                c.name.clear();
                c.string.clear();
            }
        };

        struct a_literal_val
        {
            context &c;
            a_literal_val(context &c): c(c) { }
            void operator()(It b, It e) const
            {
                BOOST_ASSERT(c.stack.size() >= 1);
                c.stack.back()->push_back(std::make_pair(c.name, Str(b, e)));
                c.name.clear();
                c.string.clear();
            }
        };

        struct a_char
        {
            context &c;
            a_char(context &c): c(c) { }
            void operator()(It b, It e) const
            {
                c.string += *b;
            }
        };

        struct a_escape
        {
            context &c;
            a_escape(context &c): c(c) { }
            void operator()(Ch ch) const
            {
                switch (ch)
                {
                    case Ch('\"'): c.string += Ch('\"'); break;
                    case Ch('\\'): c.string += Ch('\\'); break;
                    case Ch('/'): c.string += Ch('/'); break;
                    case Ch('b'): c.string += Ch('\b'); break;
                    case Ch('f'): c.string += Ch('\f'); break;
                    case Ch('n'): c.string += Ch('\n'); break;
                    case Ch('r'): c.string += Ch('\r'); break;
                    case Ch('t'): c.string += Ch('\t'); break;
                    default: BOOST_ASSERT(0);
                }
            }
        };

        struct a_unicode
        {
            context &c;
            a_unicode(context &c): c(c) { }
            void operator()(unsigned long u) const
            {
                u = (std::min)(u, static_cast<unsigned long>((std::numeric_limits<Ch>::max)()));
                c.string += Ch(u);
            }
        };

    };

    ///////////////////////////////////////////////////////////////////////
    // Json grammar

    template<class Ptree>
    struct json_grammar :
        public boost::spirit::classic::grammar<json_grammar<Ptree> >
    {
        
        typedef context<Ptree> Context;
        typedef typename Ptree::key_type::value_type Ch;

        mutable Context c;
        
        template<class Scanner>
        struct definition
        {
            
            boost::spirit::classic::rule<Scanner>
                root, object, member, array, item, value, string, number;
            boost::spirit::classic::rule<
                typename boost::spirit::classic::lexeme_scanner<Scanner>::type>
                character, escape;

            definition(const json_grammar &self)
            {

                using namespace boost::spirit::classic;
                // There's a boost::assertion too, so another explicit using
                // here:
                using boost::spirit::classic::assertion;

                // Assertions
                assertion<typename Ptree::string_type> expect_object("expected object");
                assertion<typename Ptree::string_type> expect_eoi("expected end of input");
                assertion<typename Ptree::string_type> expect_objclose("expected ',' or '}'");
                assertion<typename Ptree::string_type> expect_arrclose("expected ',' or ']'");
                assertion<typename Ptree::string_type> expect_name("expected object name");
                assertion<typename Ptree::string_type> expect_colon("expected ':'");
                assertion<typename Ptree::string_type> expect_value("expected value");
                assertion<typename Ptree::string_type> expect_escape("invalid escape sequence");

                // JSON grammar rules
                root 
                    =   expect_object(object) 
                        >> expect_eoi(end_p)
                        ;
                
                object 
                    =   ch_p('{')[typename Context::a_object_s(self.c)]
                        >> (ch_p('}')[typename Context::a_object_e(self.c)] 
                           | (list_p(member, ch_p(','))
                              >> expect_objclose(ch_p('}')[typename Context::a_object_e(self.c)])
                             )
                           )
                        ;
                
                member 
                    =   expect_name(string[typename Context::a_name(self.c)]) 
                        >> expect_colon(ch_p(':')) 
                        >> expect_value(value)
                        ;
                
                array 
                    =   ch_p('[')[typename Context::a_object_s(self.c)]
                        >> (ch_p(']')[typename Context::a_object_e(self.c)] 
                            | (list_p(item, ch_p(','))
                               >> expect_arrclose(ch_p(']')[typename Context::a_object_e(self.c)])
                              )
                           )
                    ;

                item 
                    =   expect_value(value)
                        ;

                value 
                    =   string[typename Context::a_string_val(self.c)] 
                        | (number | str_p("true") | "false" | "null")[typename Context::a_literal_val(self.c)]
                        | object 
                        | array
                        ;
                
                number 
                    =   !ch_p("-") >>
                        (ch_p("0") | (range_p(Ch('1'), Ch('9')) >> *digit_p)) >>
                        !(ch_p(".") >> +digit_p) >>
                        !(chset_p(detail::widen<typename Ptree::string_type>("eE").c_str()) >>
                          !chset_p(detail::widen<typename Ptree::string_type>("-+").c_str()) >>
                          +digit_p)
                        ;

                string
                    =   +(lexeme_d[confix_p('\"', *character, '\"')])
                        ;

                character
                    =   (anychar_p - "\\" - "\"")
                            [typename Context::a_char(self.c)]
                    |   ch_p("\\") >> expect_escape(escape)
                    ;

                escape
                    =   chset_p(detail::widen<typename Ptree::string_type>("\"\\/bfnrt").c_str())
                            [typename Context::a_escape(self.c)]
                    |   'u' >> uint_parser<unsigned long, 16, 4, 4>()
                            [typename Context::a_unicode(self.c)]
                    ;

                // Debug
                BOOST_SPIRIT_DEBUG_RULE(root);
                BOOST_SPIRIT_DEBUG_RULE(object);
                BOOST_SPIRIT_DEBUG_RULE(member);
                BOOST_SPIRIT_DEBUG_RULE(array);
                BOOST_SPIRIT_DEBUG_RULE(item);
                BOOST_SPIRIT_DEBUG_RULE(value);
                BOOST_SPIRIT_DEBUG_RULE(string);
                BOOST_SPIRIT_DEBUG_RULE(number);
                BOOST_SPIRIT_DEBUG_RULE(escape);
                BOOST_SPIRIT_DEBUG_RULE(character);

            }

            const boost::spirit::classic::rule<Scanner> &start() const
            {
                return root;
            }

        };

    };

    template<class It, class Ch>
    unsigned long count_lines(It begin, It end)
    {
        return static_cast<unsigned long>(std::count(begin, end, Ch('\n')) + 1);
    }

    template<class Ptree>
    void read_json_internal(typename Ptree::key_basic_istream &stream,
                            Ptree &pt,
                            const typename Ptree::string_type &filename)
    {

        using namespace boost::spirit::classic;
        typedef typename Ptree::key_type::value_type Ch;
        typedef typename Ptree::BOOST_NESTED_TEMPLATE for_anytype<Ch>::vector::iterator It;

        // Load data into vector
       typename Ptree::BOOST_NESTED_TEMPLATE for_anytype<Ch>::vector v(std::istreambuf_iterator<Ch>(stream.rdbuf()),
                          std::istreambuf_iterator<Ch>());
        if (!stream.good())
            BOOST_PROPERTY_TREE_CUSTOM_THROW(json_parser_error<typename Ptree::string_type>("read error", filename, 0));
        
        // Prepare grammar
        json_grammar<Ptree> g;

        // Parse
        try
        {
            parse_info<It> pi = parse(v.begin(), v.end(), g, 
                                      space_p | comment_p("//") | comment_p("/*", "*/"));
            if (!pi.hit || !pi.full)
                BOOST_PROPERTY_TREE_CUSTOM_THROW((parser_error<typename Ptree::string_type, It>(v.begin(), "syntax error")));
        }
        catch (parser_error<typename Ptree::string_type, It> &e)
        {
            BOOST_PROPERTY_TREE_CUSTOM_THROW(json_parser_error<typename Ptree::string_type>(e.descriptor, filename, count_lines<It, Ch>(v.begin(), e.where)));
        }

        // Swap grammar context root and pt
        pt.swap(g.c.root);

    }

} } }

#endif
