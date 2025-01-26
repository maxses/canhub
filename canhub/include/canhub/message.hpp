#ifndef CANHUB_MESSAGE_HPP
#define CANHUB_MESSAGE_HPP

#include <QtGlobal>


namespace CANHub
{


enum class EType
{
   Unknown=1,
   Message,
   Replay,
   ClientHeartbeat,
   ServerHeartbeat,     // 4
};

static constexpr uint32_t MAGIC = 0x11223344;

struct SMessage
{
   EType eType;
   unsigned int id;
   int length;
   int flags;
   char senderName[16];
   unsigned char data[64];
   uint32_t magic;
   
   SMessage()
   {
      eType=EType::Unknown;
      length=0;
      flags=0;
      id=0;
      magic=MAGIC;
      strcpy(senderName, "noSender");
   }
   
   SMessage(int _id, int _length, const unsigned char* _data)
   {
      eType=EType::Message;
      setId(_id);
      setData(_length, _data);
      magic=MAGIC;
      strcpy(senderName, "noSender");
   }

   void setId(int _id)
   {
      id = _id;
   }
   
   int getId() const
   {
      return( id );
   }
   
   void setData(int _length, const unsigned char* _data )
   {
      length = _length;
      if(length>sizeof(data))
      {
         qWarning("Length to big: %d", length );
         length=sizeof(data);
      }
      memcpy( data, _data, qMin(length, (int)sizeof(data)) );
   }
   void setSenderName( const QString _senderName )
   {
      snprintf(senderName, sizeof(senderName), qPrintable(_senderName) );
   }
   
   int getLen() const
   {
      return( length );
   }
   
   const unsigned char* getData() const
   {
      return( data );
   }
   const char* getSenderName() const
   {
      return( senderName );
   }
};


} // namespace CANHub

//static_asser( sizeof(SMessage) == 64+16, "Size missmatch");

#endif // CANHUB_MESSAGE_HPP
