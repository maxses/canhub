// main.cpp

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "connectorTcpClient.hpp"
#include "config.hpp"

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

    CConnectorTcpClient client;
    client.connectToHost( "ryzen", CanHub::CANSERVER_DEFAULT_PORT );

    qWarning("State: %d", client.state());

    return app.exec();
}
