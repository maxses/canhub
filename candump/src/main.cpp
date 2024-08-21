/**---------------------------------------------------------------------------
 *
 * @file       main.cpp
 * @brief      Main file for the candump commandline tool
 *
 *             It prints the CAN messages in the way "candump" from "can-utils"
 *             does.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Header ----------------------------------------------------------------*/


#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QLoggingCategory>
#include "canhub/connector.hpp"
#include "canhub/connectorTcpClient.hpp"
#include "canhub/connectorCan.hpp"
#include "canhub/config.hpp"
#include "candump.hpp"
#include "git_version_canhub.h"


/*--- Implementation --------------------------------------------------------*/


/**
 * @brief Runs the instance of CCanDump after parsing command line arguments
 * @param argc
 * @param argv
 * @return status
 */
int main(int argc, char *argv[])
{
   QCoreApplication app(argc, argv);
   QCommandLineParser parser;
   CANHub::CConnector *connector;
   app.setApplicationVersion( GIT_SEMI );
   
   parser.setApplicationDescription("CAN Client");
   parser.addHelpOption();
   parser.addVersionOption();
   
   QCommandLineOption oInterface("i", "Use CAN-Adapter <interface> directly without TCP server", "interface");
   QCommandLineOption oHost("host", "Use host <host> instead of localhost", "host");
   QCommandLineOption oDebug("d", "Enable debug output");
   parser.addOptions( { oInterface, oHost, oDebug } );
   parser.process(app);
   
   qSetMessagePattern("[%{time process}] %{function}: %{message}");

   if( ! parser.isSet(oDebug) )
   {
      QLoggingCategory::setFilterRules("*.debug=false");
   }
   
   if( parser.isSet( oInterface ) )
   {
      qInfo("CANDump, direct connection" );
      connector = new CANHub::CConnectorCan( &app, parser.value( oInterface ) );
   }
   else
   {
      qInfo("CANDump, TCP connection" );
      if( parser.isSet( oHost ) )
      {
         qDebug("Connecting to %s", qPrintable( parser.value( oHost ) ) );
         connector = new CANHub::CConnectorTcpClient( &app, parser.value( oHost ) ) ;
      }
      else
      {
         connector = new CANHub::CConnectorTcpClient( &app ) ;
      }
   }
   
   CCanDump* dump=new CCanDump( &app, connector );
   
   return app.exec();
}


/*--- fin -------------------------------------------------------------------*/
