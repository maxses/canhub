// main.cpp

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "canclient.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("CAN Client");
    parser.addHelpOption();
    parser.addVersionOption();

    // A boolean option with a single name (-p)
    QCommandLineOption oDaemon("d", "Start server daemon");
    parser.addOption(oDaemon);

    // Process the actual command line arguments given by the user
    parser.process(app);

    CCanClient client;
    client.connectToHost("ryzen", 3344);

    qWarning("State: %d", client.state());

    return app.exec();
}
