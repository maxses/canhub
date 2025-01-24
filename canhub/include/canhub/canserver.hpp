#ifndef CANHUB_CANSERVER_HPP
#define CANHUB_CANSERVER_HPP
/**---------------------------------------------------------------------------
 *
 * @file       canserver.hpp
 * @brief      Class for canserver command
 *
 *             See class documentation.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Header ----------------------------------------------------------------*/


#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include "canhub/connector.hpp"
#include "canhub/config.hpp"


/*--- Implementation --------------------------------------------------------*/


namespace CANHub
{


class CConnectorTcpServer;

/**
 * @brief   The CCanServer class
 *
 *          Implementation of the can server.
 *          The server holds an list of connectors. Each incomming message
 *          will be send to all connectors in the list.
 */
class CCanServer
         :public QTcpServer
{
   Q_OBJECT

public:
   explicit CCanServer(QObject *parent = 0, int port = CANHub::CANSERVER_DEFAULT_PORT );

signals:
   void dataOut( const SMessage& msg, CANHub::CConnector* source );

public slots:
   void newConnection();
   void heartbeat();
   void removeConnection( CANHub::CConnector* );
   void dataIn( const SMessage& msg, CANHub::CConnector* source );

private:
   QTimer m_heartbeatTimer;
   QList< CANHub::CConnector* > m_listConnections;

protected:
   void incomingConnection(qintptr socketDescriptor) override;
   void addConnector( CANHub::CConnector* connector );

public:
   bool addSocketCan(const QString interface = "can0" );
};


} // namespace CANHub


/*--- fin -------------------------------------------------------------------*/
#endif // CANHUB_CANSERVER_HPP
