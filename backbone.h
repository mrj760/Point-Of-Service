#ifndef BACKBONE_H
#define BACKBONE_H
#include "message.h"


class Backbone
{
public:
    Backbone();

    void receiveMsg(Message msg);

    void sendMsg(Message msg);
};

#endif // BACKBONE_H
