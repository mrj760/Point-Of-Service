#ifndef WORKORDER_H
#define WORKORDER_H
#include <message.h>

class WorkOrder
{
    WorkOrder();
    ~WorkOrder();
public:
    int ID;
    Message command;
    Message data;
    Message security;
    bool operator ==(WorkOrder* wo){
        return (command == &(wo->command) && data == &(wo->data) && ID == wo->ID);
    }
};

#endif // WORKORDER_H
