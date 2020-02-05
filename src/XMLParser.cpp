#include "XMLParser.h"

int ::XML::AirCrafts_parser::load( const std::string &file_name )
{
    // Create empty property tree object
    Tree tree;
    // Parse the XML into the property tree.
    try {
        // Use the throwing version of get to find the file.
        // If the path cannot be resolved, an exception is thrown.
        PropTree::read_xml( file_name, tree );
    } catch ( const ::std::exception& e ) {
        ::std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    BOOST_FOREACH( Tree::value_type& aircraft, tree.get_child("body.aircrafts") )
    {
        m_airCrafts.emplace_back( ::XML::AirCraft{
            .ID        =              aircraft.second.get< int >          ( "<xmlattr>.id",        0 ),
            .name      =              aircraft.second.get< ::std::string >( "name",      "????" ),
            .latitude  = ::std::pair{ aircraft.second.get< ::std::string >( "latitude", "0N"    ), 0 },
            .longitude = ::std::pair{ aircraft.second.get< ::std::string >( "longitude", "0E"   ), 0 },
            .speed     = ::std::pair{ aircraft.second.get< ::std::string >( "speed",     "0E"   ), 0 },
            .arl_code   =             aircraft.second.get< ::std::string >( "arl_code",  "????" )
        } );
    }
    return EXIT_SUCCESS;
}

int ::XML::AirCrafts_parser::save( const std::string &file_name )
{
    // Create an empty property tree object.
    int idx=0;
    Tree root;
    Tree& body = root.add( "body", "" );
    Tree& aircrafts = body.add( "aircrafts" , "" );
    for( const auto& value : m_airCrafts )
    {
        Tree& node = aircrafts.add("aircraft", "");
        node.put("<xmlattr>.id",              value.ID );
        node.put( "name",                     value.name );
        node.put( "latitude",  ::std::get<0>( value.latitude ) );
        node.put( "longitude", ::std::get<0>( value.longitude ) );
        node.put( "speed",     ::std::get<0>( value.speed ) );
        node.put( "arl_code",                 value.arl_code );
    }
    try {
        PropTree::xml_writer_settings< std::string > settings( '\t', 1 );
        #if (0)
        PropTree::write_xml( file_name, root, std::locale(), settings );
        #else
        //without XML declaration
        ::std::ofstream file_ostream;
        file_ostream.open( file_name );
        PropTree::xml_parser::write_xml_element( \
            file_ostream, root.front().first, root.front().second, 0, settings );
        #endif
    } catch ( const ::std::exception& e ) {
        ::std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}