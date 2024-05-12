#ifndef MESSAGE_H
#define MESSAGE_H


enum class EType
{
   Message,
   Replay,
   Heartbeat
};

enum class EType
{
   Message,
   Replay,
   Heartbeat
};

struct SMessage
{
   EType eType;
   unsigned int id;
   int lendgth;
   int flags;
   char data[64];
};


static_asser( sizeof(SMessage) == 64+16, "Size missmatch");

#endif // MESSAGE_H
