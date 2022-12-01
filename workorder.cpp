#include <workorder.h>


WorkOrder::WorkOrder()
{
    ID = -1;
    command = Message();
    data = Message();
    security = Message();
}
