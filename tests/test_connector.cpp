//----------------------------------------------------------------------------
///
/// \file   test_connector.hpp
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


//--- Own ----------------------------

#include "canserver.hpp"
#include "connectorTcpClient.hpp"
#include "test_connector.hpp"


//---Implementation------------------------------------------------------------


CTestConnector::CTestConnector( QObject *parent )
   :CConnectorTcpClient( parent, "localhost", CANHub::CANSERVER_UNITTEST_PORT )
{
   bool success = connect( m_connector, SIGNAL( dataIn( const SMessage&, CConnector* ) ),
                          this, SLOT( slotDataIn( const SMessage&, CConnector* ) ),Qt::DirectConnection );
   Q_ASSERT(success);
   
   return;
}


void CTestConnector::slotDataIn( const SMessage& msg, CConnector* source )
{
   // Example from candump from cant-utils
   //   can0  464   [8]  0B 04 30 00 D4 1B 00 00
   
   printf("   %s  %d   [%d] ",
          "can0", msg.getId(), msg.getLen());
   for(int i1=0; i1<msg.getLen(); i1++)
   {
      printf(" %02X", (unsigned char)msg.getData()[i1]);
   }
   
   if( (unsigned char)msg.getData()[0] == m_expected )
   {
      m_good++;
   }
   else
   {
      m_bad++;
   }
   m_total+=msg.getLen();
   printf("\n");
}


//---fin-----------------------------------------------------------------------
