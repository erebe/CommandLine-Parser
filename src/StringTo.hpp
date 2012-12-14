// =====================================================================================
// 
//       Filename:  StringTo.hpp
// 
//    Description:  Templates pour convertir les chaines de caractères
//        Created:  09/11/2011 01:00:03
//       Compiler:  g++
// 
//         Author:  Romain GERARD, romain.gerard@insa-lyon.fr
// 
// =====================================================================================

#ifndef CmdLineStringTo_HPP
#define CmdLineStringTo_HPP

#include	<string>
#include	<vector>
#include	<sstream>
#include	"Exceptions.hpp"


namespace CmdLine {

using namespace CmdLine;

    template<typename T>
        T stringTo( const std::string&  /* arg */ )
    {/*{{{*/
         throw UnknownConvertion();

         return T();
    }/*}}}*/

/*-----------------------------------------------------------------------------
 *  Types simples
 *-----------------------------------------------------------------------------*/
    template<>
        inline int stringTo<int>( const std::string& arg )
    {/*{{{*/
         std::stringstream s( arg );
         int value = 0;

         s >> value;

         if ( s.fail() )
              { throw BadConvertion(); }

         return value;
    }/*}}}*/

    template<>
        inline float stringTo<float>( const std::string& arg )
    {/*{{{*/
         std::stringstream s( arg );
         float value = 0;

         s >> value;

         if ( s.fail() )
              { throw BadConvertion(); }

         return value;
    }/*}}}*/

    template<>
        inline double stringTo<double>( const std::string& arg )
    {/*{{{*/
         std::stringstream s( arg );
         double value = 0;

         s >> value;

         if ( s.fail() )
              { throw BadConvertion(); }

         return value;
    }/*}}}*/

    template<>
        inline bool stringTo<bool>( const std::string& arg )
    {/*{{{*/
         std::stringstream s( arg );
         int value = 0;

         s >> value;

         if ( s.fail() )
              { throw BadConvertion(); }

         return ( value );
    }/*}}}*/

    template<>
        inline std::string stringTo<std::string>( const std::string& arg )
    {/*{{{*/
         return arg;
    }/*}}}*/


/*-----------------------------------------------------------------------------
 *  Types composés
 *-----------------------------------------------------------------------------*/
    template<>
        inline std::vector<std::string> stringTo<std::vector< std::string> >( const std::string& cpArg )
    {/*{{{*/

         std::string arg = cpArg;
         std::vector<std::string> conteneur;
         const char separator = ',';

         int found = arg.find_first_of( separator );

         while( found != ( ( int ) std::string::npos ) ) {
              if( found > 0 ) {
                   conteneur.push_back( arg.substr( 0, found ) );
              }

              arg = arg.substr( found + 1 );
              found = arg.find_first_of( separator );
         }

         if ( arg.length() > 0 ) {
              conteneur.push_back( arg );
         }

         return conteneur;
    }/*}}}*/
    
    template<>
        inline std::vector<int> stringTo<std::vector<int> >( const std::string& arg )
    {/*{{{*/

         std::vector<int> conteneur;
         const char separator = ',';
         std::stringstream buffer;
         std::string cpArg = arg;

         int found = cpArg.find_first_of( separator );
         int val = 0;

         while( found != ( ( int ) std::string::npos ) ) {

              if( found > 0 ) {
                   buffer << cpArg.substr( 0, found );
                   buffer >> val;
                   
                   if ( buffer.fail() )
                   { throw BadConvertion(); }

                   conteneur.push_back( val );
              }

              cpArg = cpArg.substr( found + 1 );
              found = cpArg.find_first_of( separator );
              buffer.clear();
         }

         if ( arg.length() > 0 ) {
           buffer << cpArg.substr( 0, found );
           buffer >> val;
           if ( buffer.fail() )
           { throw BadConvertion(); }
           conteneur.push_back( val );
         }

         return conteneur;
    }/*}}}*/

    template<>
        inline std::vector<double> stringTo<std::vector<double> >( const std::string& arg )
    {/*{{{*/

         std::vector<double> conteneur;
         const char separator = ',';
         std::stringstream buffer;
         std::string cpArg = arg;

         int found = cpArg.find_first_of( separator );
         double val = 0;

         while( found != ( ( int ) std::string::npos ) ) {

              if( found > 0 ) {
                   buffer << cpArg.substr( 0, found );
                   buffer >> val;
                   
                   if ( buffer.fail() )
                   { throw BadConvertion(); }

                   conteneur.push_back( val );
              }

              cpArg = cpArg.substr( found + 1 );
              found = cpArg.find_first_of( separator );
              buffer.clear();
         }

         if ( arg.length() > 0 ) {
           buffer << cpArg.substr( 0, found );
           buffer >> val;

           if ( buffer.fail() )
           { throw BadConvertion(); }
           
           conteneur.push_back( val );
         }

         return conteneur;
    }/*}}}*/
    
    template<>
        inline std::vector<float> stringTo<std::vector<float> >( const std::string& arg )
    {/*{{{*/

         std::vector<float> conteneur;
         const char separator = ',';
         std::stringstream buffer;
         std::string cpArg = arg;

         int found = cpArg.find_first_of( separator );
         double val = 0;

         while( found != ( ( int ) std::string::npos ) ) {

              if( found > 0 ) {
                   buffer << cpArg.substr( 0, found );
                   buffer >> val;
                   
                   if ( buffer.fail() )
                   { throw BadConvertion(); }

                   conteneur.push_back( val );
              }

              cpArg = cpArg.substr( found + 1 );
              found = cpArg.find_first_of( separator );
              buffer.clear();
         }

         if ( arg.length() > 0 ) {
           buffer << cpArg.substr( 0, found );
           buffer >> val;

           if ( buffer.fail() )
           { throw BadConvertion(); }
           
           conteneur.push_back( val );
         }

         return conteneur;
    }/*}}}*/
}

#endif
