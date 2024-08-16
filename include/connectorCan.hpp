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
      CConnectorCan( QObject *parent );
      void connectCan();
      bool getConnectionStatus()
      {
         return(m_connected);
      }
      const char* getName() override { return("Socket-CAN Adapter"); };

   public slots:
      void readyReadSlot(QSocketDescriptor socket, QSocketNotifier::Type type);
      void disconnect();
      void reconnect();
      void checkConnection();
      virtual void dataOut( const SMessage&, CConnector* source ) override;

signals:
      //void gotMessage(const CCanMessage &message);
      void connectionChanged(bool connection);
      //void dataIn( const SMessage&, CConnector* source );
};


} // namespace CANHub


#endif // CONNECTOR_CAN_HPP
