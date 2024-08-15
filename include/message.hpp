#ifndef CANSERVER_MESSAGE_HPP
#define CANSERVER_MESSAGE_HPP

#include <QtGlobal>

enum class EType
{
   Unknown=1,
   Message,
   Replay,
   ClientHeartbeat,
   ServerHeartbeat,     // 4
};


struct SMessage
{
   EType eType;
   unsigned int id;
   int length;
   int flags;
   char data[64];
   
   SMessage()
   {
      eType=EType::Unknown;
      length=0;
   }
   
   void setId(int _id)
   {
      id = _id;
   }
   
   int getId() const
   {
      return( id );
   }
   
   void setData(int _length, char* _data )
   {
      length = _length;
      if(length>sizeof(data))
      {
         qWarning("Length to big: %d", length );
         length=sizeof(data);
      }
      memcpy( data, _data, qMin(length, (int)sizeof(data)) );
   }
   
   int getLen() const
   {
      return( length );
   }
   
   const char* getData() const
   {
      return( data );
   }
};


//static_asser( sizeof(SMessage) == 64+16, "Size missmatch");

#endif // CANSERVER_MESSAGE_HPP
