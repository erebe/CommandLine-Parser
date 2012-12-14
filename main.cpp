// =====================================================================================
//
//       Filename:  main.cpp
//
//    Description:  test
//        Created:  06/11/2011 01:09:13
//       Compiler:  g++
//
//         Author:  Romain GERARD, romain.gerard@insa-lyon.fr
//
// =====================================================================================


#include    "src/cmdLine.hpp"
using namespace std;


int main( int argc, char** argv )
{/*{{{*/

    CmdLine::Parser parser( "Permet de tester les classes parsants les arguments de la ligne de commande" );
    parser.addOption( "help,h", "Affiche ce message" );
    parser.addOption( "keyword,k", "Spécifie au programme un fichier de mot clef à utiliser", true );
    parser.addOption( "exclude,e", "Inverse le fonctionnement du programme, les mots clefs sont exclus de la recherche" );
    parser.addOption( "test", "Inverse le fonctionnement du programme, les mots clefs sont exclus de la recherche", true );


    CmdLine::Argument args;
    try {
        parser.parse( argc, argv, args );
    }catch( exception& e ) {
        cout << e.what() << endl; 
        cout << parser << endl;
    }

    return 0;
}/*}}}*/
