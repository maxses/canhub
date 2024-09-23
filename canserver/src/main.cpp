/**---------------------------------------------------------------------------
 *
 * @file       main.cpp
 * @brief      Main file for canserver
 *
 *             See class dosumentation for further details.
 *
 * @date      20240821
 * @author    Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Header ----------------------------------------------------------------*/


#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QLoggingCategory>
#include "canhub/canserver.hpp"
#include "git_version.h"


/*--- Implementation --------------------------------------------------------*/


/**
 * @brief Runs the instance of CCanServer after parsing command line arguments
 * @param argc
 * @param argv
 * @return status
 */
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    CCanServer mServer;
    app.setApplicationVersion( GIT_SEMI );
    
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();

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

/*---fin---------------------------------------------------------------------*/
