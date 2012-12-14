// =====================================================================================
//
//       Filename:  cmdLineParser.cpp
//
//    Description:  Permet d'extraire les informations de la ligne de commande
//        Created:  06/11/2011 01:43:35
//       Compiler:  g++
//
//         Author:  Romain GERARD, romain.gerard@insa-lyon.fr
//
// =====================================================================================

#include    "Parser.hpp"
#include    "Argument.hpp"
#include    <string>
#include    <map>
#include    <utility>

namespace CmdLine {

using namespace CmdLine;
using namespace std;

/*-----------------------------------------------------------------------------
 *  Constructeurs
 *-----------------------------------------------------------------------------*/
Parser::Parser( string description ):
     _state( Free ), _description( description )
{}


/*-----------------------------------------------------------------------------
 *  Méthode Publiques
 *-----------------------------------------------------------------------------*/
void Parser::addDescription( string description )
{/*{{{*/
     _description = description;
}/*}}}*/

void Parser::addOption( string optionName, string description, bool hasArgument )
{/*{{{*/

     string lOption, sOption;

     size_t pos = optionName.find_first_of( ',' );

     lOption = optionName.substr( 0,  pos );
     sOption = optionName.substr( ( pos == string::npos ) ? optionName.size() : ++pos );

     lItem* lIt = &( *( _lOptions.insert( make_pair( lOption, ( optValue* )0 ) ).first ) );
     sItem* sIt = 0;

     if( !sOption.empty() ) {
          sIt = &( *( _sOptions.insert( make_pair( sOption.at( 0 ), ( optValue* )0 ) ).first ) );
     }

     optValue value = { description, hasArgument, lIt, sIt };
     _options.push_back( value );

     lIt->second = &( _options.back() );

     if ( sIt ) {
          sIt->second = lIt->second;
     }
}/*}}}*/

void Parser::display( ostream& flux ) const
{/*{{{*/

     string option;
     flux << _description << endl << endl;

     flux << "Liste des arguments : " << endl;

     for( list<optValue>::const_iterator it = _options.begin(); it != _options.end(); it++ ) {

          flux << "\t";

          if( it->sOption ) {
               option += "-";
               option += it->sOption->first;
               option += ", ";
          }

          option += "--";
          flux.width( 18 );
          flux << left << option + it->lOption->first;

          flux.width( 5 );

          if ( it->hasArgument ) {
               flux << left << "arg";

          } else {
               flux << "";
          }

          flux << it->description << endl;

          option.clear();
     }

}/*}}}*/

void Parser::parse( int argc, char** argv, Argument& args )
{/*{{{*/

     string cmdLine;

     for ( char** it = argv + 1; it < argv + argc; it++ ) {
          cmdLine += *it;
          cmdLine += " ";
     }

     cmdLine += "  ";

     string::iterator it = cmdLine.begin();

     while( it != cmdLine.end() ) {

          changeState( it );
          processInput( it, args );
     }

     args._arguments.insert( make_pair( "__args__", _freeArgs ) );

     //    for( map<string, string>::iterator it = args._arguments.begin();
     //         it != args._arguments.end(); it++ ) {
     //        cout << it->first << " : " << it->second << endl;
     //    }


}/*}}}*/


/*-----------------------------------------------------------------------------
 *  Méthodes Privées
 *-----------------------------------------------------------------------------*/
void Parser::changeState( string::iterator& it )
{/*{{{*/

     if( *it == '-' ) {
          _state = ( _state == ShortCondition ) ? LongCondition : ShortCondition;

     } else if( *it == ' ' ) {
          _state = Free;

     } else if( _state == ShortCondition ) {
          _state = ShortCondition;

     } else {
          _state = FreeArgument;
     }

}/*}}}*/

void Parser::processInput( string::iterator& it, Argument& args )
{/*{{{*/


     if( _state == Free ) {
          it++;

     } else if( _state == FreeArgument ) {

          while( *it != ' ' ) {
               _freeArgs += *it;
               it++;
          }

          _freeArgs += ',';

     } else if ( _state == LongCondition ) {
          string key;
          it++;

          while( *it != '=' && *it != ' ' ) {
               key += *it;
               it++;
          }

          if( !_lOptions.count( key ) ) {
               throw UnknownOption( key );
          }

          lItem& item = *( _lOptions.find( key ) );

          if( ( item.second->hasArgument && *it == ' ' )
              || ( !item.second->hasArgument && *it == '=' ) ) {
               throw ArgumentBadFormatted();
          }

          string value;

          if( !item.second->hasArgument ) {
               value = "42";

          } else {
               it++;

               while( *it != ' ' ) {
                    value += *it;
                    it++;
               }
          }

          if( value.empty() ) {
               throw ArgumentBadFormatted();
          }

          args._arguments.insert( make_pair( key, value ) );

     } else if ( _state == ShortCondition ) {

          if ( *it == '-' ) {
               it++;

          } else {

               string key;
               key += *it;

               if ( !_sOptions.count( *it ) ) {
                    throw UnknownOption( key );
               }

               sItem& item = *( _sOptions.find( *it ) );
               key = item.second->lOption->first;

               it++;

               if ( !item.second->hasArgument ) {
                    args._arguments.insert( make_pair( key, "42" ) );

               } else {

                    if ( *it != ' ' ) {
                         throw ArgumentBadFormatted();
                    }

                    ++it;
                    string value;

                    while( *it != ' ' ) {
                         value += *it;
                         it++;
                    }

                    if( value.empty() ) {
                         throw  ArgumentBadFormatted();
                    }

                    args._arguments.insert( make_pair( key, value ) );
               }

          }
     }



}/*}}}*/


/*-----------------------------------------------------------------------------
 *  Surcharge Opérateur
 *-----------------------------------------------------------------------------*/
ostream& operator<<( ostream& flux, const Parser& parser )
{/*{{{*/

     parser.display( flux );

     return flux;
}/*}}}*/

}/*}}}*/
