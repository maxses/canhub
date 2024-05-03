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
   CConnector *connector;
   
   parser.setApplicationDescription("CAN Client");
   parser.addHelpOption();
   parser.addVersionOption();
   
   QCommandLineOption oDirect("s", "Use CAN-Adapter directly without TCP server");
   QCommandLineOption oDebug("D", "Enable debug output");
   parser.addOptions( { oDirect, oDebug } );
   parser.process(app);
   
   qSetMessagePattern("[%{time process}] %{function}: %{message}");
   if( ! parser.isSet(oDebug) )
   {
      QLoggingCategory::setFilterRules("*.debug=false");
   }
   
   if( parser.isSet( oDirect ) )
   {
      qInfo("CANDump, direct connection" );
      connector = new CConnectorCan( &app );
   }
   else
   {
      qInfo("CANDump, TCP connection" );
      connector = new CConnectorTcpClient( &app ) ;
   }
   
   CCanDump* dump=new CCanDump( connector, &app );
   
   return app.exec();
}
