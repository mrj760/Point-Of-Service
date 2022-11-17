#ifndef MESSAGE_H
#define MESSAGE_H
#include <vector>
#include <string>

class Message
{
public:

    enum MessageType
    {

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
