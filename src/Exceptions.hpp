// NO_FORMAT ===========================================================================
// 
//       Filename:  Exceptions.hpp
// 
//    Description:  Les exceptions pouvant être lancées
//        Created:  09/11/2011 01:07:40
//       Compiler:  g++
// 
//         Author:  Romain GERARD, romain.gerard@insa-lyon.fr
// 
// =====================================================================================

#ifndef CmdLineExceptions_HPP
#define CmdLineExceptions_HPP

#include	<exception>

/*-----------------------------------------------------------------------------
 *  Exceptions
 *-----------------------------------------------------------------------------*/

namespace CmdLine {

using namespace CmdLine;


    /* =====================================================================================
     *        Class:  UnknownCnvertion
     *  Description:  Exception lancé si on ne sait pas convertir la chaine vers le format
     * =====================================================================================*/
    class UnknownConvertion : public std::exception {
         public:
              virtual const char* what() const throw()
              { return "Don't know how to convert the argument to this type !"; }
    };


    /* =====================================================================================
     *        Class:  BadConvertion
     *  Description:  Exception lancé si la convertion a échoué
     * =====================================================================================*/
    class BadConvertion : public std::exception {
         public:
              virtual const char* what() const throw()
              { return "The convertion of the argument to this type failed !"; }
    };


    /* =====================================================================================
     *        Class:  InvalidKey
     *  Description:  Exception lancé si l'option ne correspond à aucune clef
     * =====================================================================================*/
    class InvalidKey : public std::exception {
         public:
              virtual const char* what() const throw()
              { return "The key specified don't exist ! Check first with count()"; }
    };


    /* =====================================================================================
     *        Class:  ArgumentBadFormatted
     *  Description:  Exception lancé lorsque la ligne de commande n'est pas bien formaté
     * =====================================================================================*/
    class ArgumentBadFormatted : public std::exception {
         public:
              const char* what() const throw()
              { return "Arguments are not well formatted !"; }
    };


    /* =====================================================================================
     *        Class:  UnknownOption
     *  Description:  Exception lancé lorsqu'une option n'existe pas
     * =====================================================================================*/
    class UnknownOption : public std::exception {
         public:
              UnknownOption( std::string& option ): _option( option ) {}
              virtual ~UnknownOption() throw() {}

              const char* what() const throw()
              { return std::string( "Option not recognized \"" + _option + "\"" ).c_str(); }

         private:
              std::string _option;
    };

}
#endif
