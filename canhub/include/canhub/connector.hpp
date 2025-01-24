#ifndef CANHUB_CONNECTOR_HPP
#define CANHUB_CONNECTOR_HPP
/**---------------------------------------------------------------------------
 *
 * @file       connector.hpp
 * @brief      Class for a connector
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
#include <canhub/message.hpp>


/*--- Implementation --------------------------------------------------------*/


namespace CANHub
{

/**
 * @brief   The abstract CConnector class
 *
 *          An 'connector' defines an connection to, an connection from or an
 *          connection to an USB-CAN-Adapter.
 *          There is an signal "dataIn" which the inherited class has to emit
 *          whenever it received an message.
 *          There is an slot "dataOut" which the class inherited has to
 *          implement in order to send an message.
 */
class CConnector : public QObject
{
   Q_OBJECT
   
protected:
   QString m_name;
   QString m_interface;
   
public:
   explicit CConnector( QObject *parent = 0, const QString name = "noname" );
   ~CConnector();
   const QString& getName() const { return(m_name); };
   const QString& getInterface() const { return( m_interface ); };

signals:
   void deactivate( CANHub::CConnector* );
   void dataIn( const SMessage& msg, CANHub::CConnector* source );
   void connectionChanged( bool connected );

public slots:
   virtual void dataOut( const SMessage&, CANHub::CConnector* source ) = 0;
};

} // namespace CANHub


/*--- fin -------------------------------------------------------------------*/
#endif // CANHUB_CONNECTOR_HPP
