/**---------------------------------------------------------------------------
 *
 * @file       test_connector.cpp
 * @brief      Test connector for CANHub
 *
 *             The test counter is needed for unit tests.
 *             The test connector can be configured to expect specific data
 *             from the CAN-server. When the connector receives data, it
 *             checks if the data matches the expected data. According to the
 *             result it increases an good- or bad-counter.
 *
 * @date       20240813
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/



/*--- Header ----------------------------------------------------------------*/


#include "canhub/canserver.hpp"
#include "canhub/connectorTcpClient.hpp"
#include "test_connector.hpp"


/*--- Implementation --------------------------------------------------------*/


namespace CANHub {


CTestConnector::CTestConnector( QObject *parent )
   :CConnectorTcpClient( parent, "testConnector", "localhost", CANHub::CANSERVER_UNITTEST_PORT )
{
   bool success = connect(
         this, SIGNAL( dataIn( const CANHub::SMessage&, CANHub::CConnector* ) ),
         this, SLOT( slotVerifyDataIn( const CANHub::SMessage&, CANHub::CConnector* ) ),Qt::DirectConnection );
   Q_ASSERT(success);
   
   return;
}


void CTestConnector::slotVerifyDataIn( const CANHub::SMessage& msg, CConnector* source )
{
   // Example from candump from cant-utils
   //   can0  464   [8]  0B 04 30 00 D4 1B 00 00
   
   printf("   %s  %d   [%d] ",
          qPrintable(source->getInterface()), msg.getId(), msg.getLen());
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

} // namespace CANHub


/*---fin---------------------------------------------------------------------*/
