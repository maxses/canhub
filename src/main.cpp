#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QLoggingCategory>
#include "canserver.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();

    // A boolean option with a single name (-p)
    QCommandLineOption oDaemon("d", "Start server daemon");
    QCommandLineOption oDebug("D", "Enable debug output");
    parser.addOptions( { oDaemon, oDebug } );
    parser.process(app);
    
    qSetMessagePattern("[%{time process}] %{function}: %{message}");
    if( ! parser.isSet(oDebug) )
    {
      QLoggingCategory::setFilterRules("*.debug=false");
    }
    
    if( parser.isSet( oDaemon ) )
    {
      CCanServer mServer;
      mServer.addSocketCan();
      return app.exec();
    }
    
    return app.exec();
}
