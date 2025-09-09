#ifndef CANHUB_CONNECTOR_TCP_SERVER_HPP
#define CANHUB_CONNECTOR_TCP_SERVER_HPP
/**---------------------------------------------------------------------------
 *
 * @file       connectorTcpServer.hpp
 * @brief      Class for connector from an client within the server.
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
#include "canhub/connector.hpp"


/*--- Implementation --------------------------------------------------------*/


namespace CANHub{

/**
 * @brief The CAN-Server
 *
 */
class CConnectorTcpServer : public CConnector
{
   Q_OBJECT
   
public:
   explicit CConnectorTcpServer(int iID, QObject *parent = 0);
   ~CConnectorTcpServer();
   void connectSocket();
    
public slots:
    void readyRead();
    void disconnected();
    virtual void dataOut( const SMessage&, CConnector* source ) override;

public slots:

private:
    QTcpSocket *m_pSocket;
    int m_socketDescriptor;
};

} // namespace CANHub


/*--- fin -------------------------------------------------------------------*/
#endif // CANHUB_CONNECTOR_TCP_SERVER_HPP
