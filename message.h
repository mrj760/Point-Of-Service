#ifndef MESSAGE_H
#define MESSAGE_H
#include <vector>
#include <string>

class Message
{
public:

    enum MessageType
    {
        //This is temporary to just test message passing capabilities
        //Nathan (or whoever else) plz fix later
        unknown=0,
        contains_cmd=1,
        contains_db_entry=2,
        contains_item=3
    };

    Message();
    MessageType type();

    bool operator ==(Message* msg);
    void operator = (std::string st);
    void operator += (std::string st);
    void fill(std::string st);
    void add(std::string st);
    std::vector<std::string> getText();
private:
    std::vector<std::string> text;
    MessageType msgtype;
};

#endif // MESSAGE_H
