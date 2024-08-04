// main.cpp

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
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
    parser.addOption(oDaemon);

    // Process the actual command line arguments given by the user
    parser.process(app);

    if( parser.isSet( oDaemon ) )
    {
      CCanServer mServer;
      return app.exec();
    }
    
    return app.exec();
}
