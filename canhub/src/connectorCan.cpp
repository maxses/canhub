/**---------------------------------------------------------------------------
 *
 * @file       connectorCan.cpp
 * @brief      Class for a CAN-Adapter-connector
 *
 *             Se class documentation.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


//---Includes------------------------------------------------------------------


#include <sys/ioctl.h>
#include <net/if.h>              // ifreq_ifr
#include <linux/can/raw.h>       // CAN_RAW
#include <sys/socket.h>          // PF_CAN
#include <linux/can/netlink.h>   // can_bittiming
#include <signal.h>              // signal()
#include <unistd.h>              // close()

#include <canhub/connectorCan.hpp>


//---Implementation------------------------------------------------------------


namespace CANHub
{


CConnectorCan::CConnectorCan( QObject *parent, const QString interface )
   :CConnector( parent )
   ,m_socketNotifier( nullptr )
   ,m_connected( false )
   ,skt( 0 )
{
   m_interface=interface;
   m_name="Socket-CAN Adapter";
   connectCan();
   
   connect( &m_checkTimer, SIGNAL( timeout() ), this, SLOT( checkConnection() ) );
   m_checkTimer.start(1000);
}


void CConnectorCan::connectCan()
{
   struct can_bittiming dbt;

   skt = socket( PF_CAN, SOCK_RAW, CAN_RAW );
   int sta=0;
   if(skt<0)
   {
      perror("Socket");
      skt=0;
      return;
   }

   /* Locate the interface you wish to use */
   struct ifreq ifr;

   strcpy(ifr.ifr_name, qPrintable( m_interface ));
   sta=ioctl(skt, SIOCGIFINDEX, &ifr); /* ifr.ifr_ifindex gets filled
                                  * with that device's index */
   if(sta<0)
   {
      perror("Ioctl");
      emit( connectionChanged(false) );
      return;
   }
   
   int val=1;
   sta=setsockopt( skt, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val));

   /* Select that CAN interface, and bind the socket to it. */
   struct sockaddr_can addr;
   addr.can_family = AF_CAN;
   addr.can_ifindex = ifr.ifr_ifindex;
   sta=::bind( skt, (struct sockaddr*)&addr, sizeof(addr) );
   if(sta<0)
   {
      perror("Bind");
      emit( connectionChanged(false) );
      return;
   }

   m_socketNotifier=new QSocketNotifier(skt, QSocketNotifier::Read );

   connect ( m_socketNotifier, SIGNAL( activated( int ) ), this, SLOT( readyReadSlot( int ) ) );
   m_connected = true;
   emit( connectionChanged(true) );
}

#if 0
void CConnectorCan::readyReadSlot(QSocketDescriptor socket, QSocketNotifier::Type type)
#endif
void CConnectorCan::readyReadSlot( int socket )
{
   struct can_frame frame;
   SMessage msg;
   
   qDebug("CAN: data in");
   
#if 0
   if( type != QSocketNotifier::Type::Read )
   {
      qWarning("Unknown type: %d", (int)type );
      return;
   }
#endif

   int bytes_read = read( skt, (char *)&frame, sizeof(frame) );
   
   // Only way yet to detect an problem
   if( bytes_read < 0 )
   {
      disconnect();
      return;
   }
   
   msg.eType = EType::Message;
   msg.setId(frame.can_id & CAN_EFF_MASK);
   msg.setData(frame.can_dlc, (unsigned char*)frame.data);

   #if defined ( llll )
   msg.setOriginExtended( frame.can_id & CAN_EFF_FLAG ? true : false );
   #endif
   
   qDebug("Data in. ID: 0x%X; size: %d", frame.can_id, bytes_read);
   
   if( ( frame.can_dlc == 0) && ( ( frame.can_id & CAN_EFF_MASK ) <= 1 ) )
   {
      disconnect();
   }

   if(0)
   {
      printf("[ID %04X, LEN %04X]: [%X] [%X] [%X] [%X] [%X] [%X]\n"
               , frame.can_id
               , frame.can_dlc
               , frame.data[0], frame.data[1]
               , frame.data[2], frame.data[3]
               , frame.data[4], frame.data[5]
            );
   }
   
   emit( dataIn(msg, this) );
}


void CConnectorCan::disconnect()
{
   qDebug("Disconnect");
   if(m_socketNotifier)
   {
      delete(m_socketNotifier);
      m_socketNotifier=nullptr;
   }
   close(skt);
   skt=0;
   m_connected = false;
   emit( connectionChanged(false) );
}


void CConnectorCan::reconnect()
{
   disconnect();
   connectCan();
}


void CConnectorCan::checkConnection()
{
   int error_code;
   int sta;
   qDebug("Check; %d", skt );
   #if 0
   socklen_t error_code_size = sizeof(error_code);
   if(skt>0)
   {
      // Does not give any usefull information yet
      sta=getsockopt(skt, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
      if( error_code || sta )
      {
         qWarning("Error: %d/%d", error_code, sta);
      }
   }
   #endif
   
   if(!getConnectionStatus())
   {
      connectCan();
      emit(connectionChanged(false));
   }
   else
   {
      emit(connectionChanged(true));
   }
   
}


void CConnectorCan::dataOut( const SMessage& msg, CConnector* source )
{
   if( source != this )
   {
      qDebug( "CAN: Data out: Type=%d", (int)msg.eType );
      struct can_frame frame;
      
      // 11-Bit-Identifier, "Base frame format" (CAN 2.0A)
      // 29-Bit-Identifier, "Extended frame format" (CAN 2.0B).
      
      frame.can_id = msg.getId();
      
      if(frame.can_id>= 2^11)
         frame.can_id|= CAN_EFF_FLAG;

      frame.can_dlc = msg.getLen();
      memcpy( (char *)frame.data, msg.getData(), frame.can_dlc);
      int bytes_sent = write( skt, (const char *)&frame, sizeof(frame) );
      
      qDebug("Bytes send: %d\n", bytes_sent);
   }
}


} // namespace CANHub


//---fin----------------------------------------------------------------------
