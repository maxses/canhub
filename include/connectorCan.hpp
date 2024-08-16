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
      QString m_interface;
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
      const char* getName() override { return("Socket-CAN Adapter"); };
      virtual const char* getInterface() { return( qPrintable(m_interface) ); };

   public slots:
      //void readyReadSlot(QSocketDescriptor socket, QSocketNotifier::Type type);
      void readyReadSlot( int socket );
      void disconnect();
      void reconnect();
      void checkConnection();
      virtual void dataOut( const SMessage&, CConnector* source ) override;
};


} // namespace CANHub


#endif // CONNECTOR_CAN_HPP
