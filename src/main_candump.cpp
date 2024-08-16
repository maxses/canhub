// main.cpp

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QLoggingCategory>
#include "connector.hpp"
#include "connectorTcpClient.hpp"
#include "connectorCan.hpp"
#include "candump.h"
#include "config.hpp"

int main(int argc, char *argv[])
{
   QCoreApplication app(argc, argv);
   QCommandLineParser parser;
   CANHub::CConnector *connector;
   
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
