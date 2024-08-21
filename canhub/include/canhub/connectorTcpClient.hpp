#ifndef CANHUB_CONNECTOR_TCP_CLIENT_HPP
#define CANHUB_CONNECTOR_TCP_CLIENT_HPP
/**---------------------------------------------------------------------------
 *
 * @file       connectorTcpClient.hpp
 * @brief      Class for a connector connecting to an TCP-Server
 *
 *             See class documentation.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Header ----------------------------------------------------------------*/


#include <QTcpSocket>
#include <QTimer>
#include "canhub/connector.hpp"
#include "canhub/config.hpp"


/*--- Implementation --------------------------------------------------------*/


namespace CANHub {

/**
 * @brief   The CConnectorTcpClient class
 *
 *          The TCP-Client connector connecting to an TCP-Server
 */
class CConnectorTcpClient : public CConnector
{
   Q_OBJECT

private:
   QTcpSocket m_socket;
   QString m_host;
   int m_port;

public:
   explicit CConnectorTcpClient( QObject *parent = 0, const QString = "localhost", int port = CANHub::CANSERVER_DEFAULT_PORT );

public slots:
   void heartbeat();
   void readyRead();
   virtual void dataOut( const SMessage&, CConnector* source ) override;

    
private:
   QTimer m_heartbeatTimer;
};

} // namespace CANHub


/*--- fin -------------------------------------------------------------------*/
#endif // CANHUB_CONNECTOR_TCP_CLIENT_HPP
