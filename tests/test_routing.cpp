//----------------------------------------------------------------------------
///
/// \file   main.cpp
///
/// \brief  main file for canserver
///
/// \date   20240813
/// \author Maximilian Seesslen <mes@seesslen.net>
///
//----------------------------------------------------------------------------


//---Documentation------------------------------------------------------------


//---Includes -----------------------------------------------------------------


//---General--------------------------

#define CATCH_CONFIG_MAIN
#define LEPTO_LOG_DEBUG

#if defined ( CATCH2 )
   #include <catch2/catch_test_macros.hpp>
#elif defined ( CATCH )
   #include <catch/catch.hpp>
#else
   #error "Either 'catch' or 'catch2' has to be installed"
#endif
#include <QCoreApplication>
#include <QElapsedTimer>

//--- Own ----------------------------

#include "canserver.hpp"
#include "connectorTcpClient.hpp"
#include "test_connector.hpp"

#define TEST_ALL
#define STOP_ON_FAIL


//---Implementation------------------------------------------------------------


int argc=1;
char* argv[]{"foo"};

struct SPattern
{
   int index;
   unsigned char pattern;
   int len;
   bool bad;
};


SPattern testPatterns[] {
   { .index=0, .pattern=0x10, .len=10, .bad=false },
   { .index=1, .pattern=0x20, .len=10, .bad=false },
   { .index=0, .pattern=0x30, .len=10, .bad=false },
   { .index=1, .pattern=0x40, .len=10, .bad=false },
   { .index=1, .pattern=0x50, .len=10, .bad=false },
    
   { .index=0, .pattern=0x60, .len=128, .bad=false },
   { .index=1, .pattern=0x70, .len=256, .bad=false },
    
   { .index=0, .pattern=0x80, .len=20, .bad=true },
   { .index=1, .pattern=0x90, .len=20, .bad=true },
   { .index=0, .pattern=0x80, .len=20, .bad=true },
};

TEST_CASE( "Routing", "[default]" )
{
   QCoreApplication app(argc, argv);
   
   SECTION( "Routing" )
   {
      CCanServer canServer( &app, CanHub::CANSERVER_DEFAULT_PORT + 1 );

      CConnectorTcpClient* connectorTcpA = new CConnectorTcpClient( &app, "localhost", CanHub::CANSERVER_DEFAULT_PORT + 1 ) ;
      CConnectorTcpClient* connectorTcpB = new CConnectorTcpClient( &app, "localhost", CanHub::CANSERVER_DEFAULT_PORT + 1 ) ;
      
      CTestConnector connectorA(connectorTcpA, &canServer);
      CTestConnector connectorB(connectorTcpB, &canServer);
      
      CTestConnector* connectors[2]{ &connectorA, &connectorB };
      
      SMessage msg;
      char buf[64];
      QElapsedTimer timer;
      
      for(int i1=0; i1<sizeof(testPatterns)/sizeof(testPatterns[0]); i1++)
      {
         memset( buf, testPatterns[i1].pattern, qMin( (int)sizeof(buf), testPatterns[i1].len ) );
         msg.setId(0x123);
         msg.setData(testPatterns[i1].len, buf);
         
         connectors[( testPatterns[i1].index + 1 ) % 2 ]->setExpected(
             testPatterns[i1].pattern + (testPatterns[i1].bad ? 0x2 : 0x0 ) );
         connectors[testPatterns[i1].index]->dataOut(msg, nullptr);
         timer.start();
         
         // Wait 1ms to process events
         while( timer.elapsed() < 1 )
         {
            app.processEvents();
         }
      }
      REQUIRE ( connectorA.getGood() == 4 );
      REQUIRE ( connectorA.getBad() == 1 );
      REQUIRE ( connectorB.getGood() == 3 );
      REQUIRE ( connectorB.getBad() == 2 );
      
      REQUIRE ( connectorA.getTotal() == 30 + 64 + 20 );
      REQUIRE ( connectorB.getTotal() == 20 + 64 + 40 );
   }
}


//---fin-----------------------------------------------------------------------
