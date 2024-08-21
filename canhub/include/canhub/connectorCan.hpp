#ifndef CANHUB_CONNECTOR_CAN_HPP
#define CANHUB_CONNECTOR_CAN_HPP
/**---------------------------------------------------------------------------
 *
 * @file       connectorCan.hpp
 * @brief      Class for a CAN-Adapter-connector
 *
 *             Se class documentation.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Header ----------------------------------------------------------------*/


#include <QSocketNotifier>
#include <QTimer>
#include "canhub/connector.hpp"
#include "canhub/message.hpp"


/*--- Implementation --------------------------------------------------------*/


namespace CANHub {

/**
 * @brief The CConnectorCan class
 *
 *          The connector uses an USB-CAN-Adapter
 */
class CConnectorCan
      :public CConnector
{
   Q_OBJECT

   private:
      QSocketNotifier *m_socketNotifier;
      QTimer m_checkTimer;
      int skt;
      bool m_connected;
      
   public:
      CConnectorCan( QObject *parent, const QString interface );
      void connectCan();
      bool getConnectionStatus()
      {
         return(m_connected);
      }

   public slots:
      void readyReadSlot( int socket );
      void disconnect();
      void reconnect();
      void checkConnection();
      virtual void dataOut( const SMessage&, CConnector* source ) override;
};


} // namespace CANHub


/*--- fin -------------------------------------------------------------------*/
#endif // CANHUB_CONNECTOR_CAN_HPP
