// NO_FORMAT ===========================================================================
//
//       Filename:  commandLineParser.hpp
//
//    Description:  Classe permettant d'extraire les informations de la ligne de commande
//        Created:  06/11/2011 00:50:26
//       Compiler:  g++
//
//         Author:  Romain GERARD, romain.gerard@insa-lyon.fr
//
// =====================================================================================


#ifndef CmdLineParser_HPP
#define CmdLineParser_HPP

#include    <iostream>
#include    <string>
#include    <map>
#include    <list>
#include    <utility>

namespace CmdLine {

using namespace CmdLine;
class Argument;


/* =====================================================================================
 *        Class:  Parser
 *  Description:  Permet d'extraire et de découper les arguments de la ligne de commande
 * =====================================================================================*/
class Parser {

     public:

/*-----------------------------------------------------------------------------
 *  Constructeur
 *-----------------------------------------------------------------------------*/
          Parser( std::string = "" );

/*-----------------------------------------------------------------------------
 *  Méthodes Publiques
 *-----------------------------------------------------------------------------*/

          /* ===  FUNCTION  ======================================================================
           *         Name:  addDescription
           *  Description:  Ajoute une description au programme
           * =====================================================================================*/
          void addDescription( std::string );

          /* ===  FUNCTION  ======================================================================
           *         Name:  addOption
           *  Description:  Ajoute une option que doit gérer le programme
           * =====================================================================================*/
          void addOption( std::string optionName, std::string description, bool hasArgument = false );
          
          /* ===  FUNCTION  ======================================================================
           *         Name:  parse
           *  Description:  Extrait et stocke les informations de la ligne de commande
           * =====================================================================================*/
          void parse( int argc, char** argv, Argument& args );

          /* ===  FUNCTION  ======================================================================
           *         Name:  display
           *  Description:  Affiche la description ainsi que les arguments accepté par le programme
           *                dans le flux spécifié
           * =====================================================================================*/
          void display( std::ostream& flux ) const;


     private:

/*-----------------------------------------------------------------------------
 *  Les états que peut prendre l'objet
 *-----------------------------------------------------------------------------*/
          enum State { Free, ShortCondition, LongCondition, FreeArgument };
          State _state;

          
/*-----------------------------------------------------------------------------
 *  Les structures de données pour stocker les arguments
 *-----------------------------------------------------------------------------*/
          struct optValue;
          typedef std::pair<const std::string, optValue*> lItem;
          typedef std::pair<const char, optValue*> sItem;

          struct optValue {
               std::string description;
               bool hasArgument;
               lItem* lOption;
               sItem* sOption;
          };

          std::map< const std::string, optValue* > _lOptions;
          std::map< const char, optValue* > _sOptions;
          std::list<optValue> _options; // pas de vector car la zone mémoire bouge
          std::string _description;
          std::string _freeArgs;

/*-----------------------------------------------------------------------------
 *  Méthodes privées
 *-----------------------------------------------------------------------------*/

          /* ===  FUNCTION  ======================================================================
           *         Name:  processInput
           *  Description:  Traite la ligne de commande
           * =====================================================================================*/
          void processInput( std::string::iterator& it, Argument& args );

          /* ===  FUNCTION  ======================================================================
           *         Name:  ChangeState
           *  Description:  Détermine l'état de l'objet
           * =====================================================================================*/
          void changeState( std::string::iterator& it );




};

//Surcharge de l'operateur de flux
std::ostream& operator<<( std::ostream& flux,  const Parser& parser );

}/*}}}*/
#endif

