#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QLoggingCategory>
#include "canserver.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    CCanServer mServer;
    
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();

    // A boolean option with a single name (-p)
    QCommandLineOption oInterface("i", "Use CAN interface <interface>", "interface");
    QCommandLineOption oDebug("d", "Enable debug output");
    parser.addOptions( { oInterface, oDebug } );
    parser.process(app);
    
    qSetMessagePattern("[%{time process}] %{function}: %{message}");

    if( ! parser.isSet(oDebug) )
    {
      QLoggingCategory::setFilterRules("*.debug=false");
    }
    
    if( parser.isSet( oInterface ) )
    {
      mServer.addSocketCan( parser.value( oInterface ) );
    }
    
    return app.exec();
}
