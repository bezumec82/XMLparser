#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <string>
#include <set>
#include <exception>
#include <iostream>
#include <list>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

namespace XML
{   
    namespace PropTree = ::boost::property_tree;
    using Tree = ::boost::property_tree::ptree;

    struct AirCraft
    {
        int                                    ID;  
        ::std::string                          name;
        ::std::pair< ::std::string, uint32_t > latitude;
        ::std::pair< ::std::string, uint32_t > longitude;
        ::std::pair< ::std::string, uint32_t > speed;
        ::std::string                          arl_code;
    };

    class AirCrafts_parser
    {
        using AirCrafts = ::std::list<AirCraft>;
        AirCrafts m_airCrafts;
    public :
        int load( const std::string &file_name );
        int save( const std::string &file_name );
        
        AirCrafts& getAirCrafts( void )
        {
            return m_airCrafts;
        }
    };
}
#endif /* XML_PARSER_H */