#ifndef CONNECTOR_CAN_HPP
#define CONNECTOR_CAN_HPP

#include <QSocketNotifier>
#include <QTimer>
#include <connector.hpp>
#include <message.hpp>


namespace CANHub {

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


#endif // CONNECTOR_CAN_HPP
