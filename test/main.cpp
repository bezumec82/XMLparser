#include <iostream>

#include <boost/program_options.hpp>

#include "XMLParser.h"

namespace ProgOpt = ::boost::program_options;
using OptDesc = ::boost::program_options::options_description;
using VarMap = ::boost::program_options::variables_map;

int main( int argc, char** argv)
{
    std::string file_name;
    try 
    {
        OptDesc desc( "Allowed options" );
        desc.add_options()
            ( "file", ProgOpt::value< std::string >( &file_name ),
                "Set file to parse.\n"
                "EXAMPLE : --file some_file.xml\n" );
        VarMap var_map;
        ProgOpt::store(
            ProgOpt::parse_command_line( argc, argv, desc ), var_map );
        ProgOpt::notify(var_map);
        if( var_map.count( "help" ) )
        {
            std::cout << desc;
            return EXIT_SUCCESS;
        }
        if( file_name.empty() )
        {
            ::std::cerr << "Name of the file is not provided !!!" << ::std::endl;
            return EXIT_FAILURE;
        }
        if( var_map.empty() )
        {
            std::cerr << "!!! Use options !!!" << ::std::endl;
            std::cout << desc;
            return EXIT_SUCCESS;
        }
    } catch( const ::std::exception& e ) {
        ::std::cerr << e.what() << '\n';
        ::std::cerr << "Try to use --help option." << ::std::endl;
        return EXIT_FAILURE;
    }

    ::XML::AirCrafts_parser ac;
    ac.load( file_name );
    ::std::string ret_file = file_name.substr( 0, file_name.find(".xml") ) + "_ret.xml";
    ac.save( ret_file );
    return EXIT_SUCCESS;
}
