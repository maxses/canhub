/**---------------------------------------------------------------------------
 *
 * @file       candump.cpp
 * @brief      Class for commandline candump command
 *
 *             It prints the CAN messages in the way "candump" from "can-utils"
 *             does.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Header ----------------------------------------------------------------*/


#include "canhub/config.hpp"
#include "candump.hpp"


/*--- Implementation --------------------------------------------------------*/


namespace CANHub
{


/**
 * @brief Le constructuer
 * @param parent
 * @param connector
 */
CCanDump::CCanDump( QObject *parent, CANHub::CConnector* connector )
    :QObject( parent )
    ,m_connector( connector )
{
   bool success = connect( m_connector, SIGNAL( dataIn( const CANHub::SMessage&, CANHub::CConnector* ) ),
            this, SLOT( slotDataIn( const CANHub::SMessage&, CANHub::CConnector* ) ),Qt::DirectConnection );
   Q_ASSERT(success);
   
   return;
}


/**
 * @brief   slot for receiving data
 *
 *          prints the CAN messages in the way "candump" from "can-utils"
 *          does.
 * @param   msg[in]
 * @param   source[in]
 */
void CCanDump::slotDataIn( const CANHub::SMessage& msg, CANHub::CConnector* source )
{
   // Example from candump from cant-utils
   //   can0  464   [8]  0B 04 30 00 D4 1B 00 00
   
   QString senderName=msg.getSenderName();
   senderName.resize( 16, ' ');
   // Could also be printed: source->getInterface() )
   printf("   %s  Id:0x%X   [%d] ",
          qPrintable( senderName ), msg.getId(), msg.getLen());
   for(int i1=0; i1<msg.getLen(); i1++)
   {
      printf(" %02X", (unsigned char)msg.getData()[i1]);
   }
   printf("\n");
}


} // namespace CANHub


/*--- fin -------------------------------------------------------------------*/
