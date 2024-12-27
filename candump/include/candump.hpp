#ifndef CANHUB_CANDUMP_HPP
#define CANHUB_CANDUMP_HPP
/**---------------------------------------------------------------------------
 *
 * @file       candump.hpp
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


/*--- Includes---------------------------------------------------------------*/


#include <QObject>
#include "canhub/connector.hpp"


/*--- Implementation --------------------------------------------------------*/


namespace CANHub
{


class CCanDump: QObject
{
   Q_OBJECT

   public:
      /**
       * @brief Le constructeur
       * @param parent[in]
       * @param connector[in] Which connector to use. Can be a CAN-Connector or
       *                      TCP-COnnector
       */
      explicit CCanDump( QObject *parent = 0, CANHub::CConnector* connector = 0 );
      
   public slots:
      void slotDataIn( const SMessage& msg, CANHub::CConnector* source );

   private:
      CANHub::CConnector* m_connector;
       
   signals:
      //void signalDataIn( const SMessage& msg, CANHub::CConnector* source );
      //void signalConnectionChanged( bool connected );
};


} // namespace CANHub


/*--- fin -------------------------------------------------------------------*/
#endif // CANHUB_CANDUMP_HPP
