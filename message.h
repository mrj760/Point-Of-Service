#ifndef MESSAGE_H
#define MESSAGE_H
#include <vector>

class Message
{
public:

    enum MessageType
    {

    };

    Message();
    MessageType type(){return msgtype;}

    bool operator ==(Message* msg){
        if(this->type() == msg->type())
            if(this->getText()==msg->getText())
            return true;
        return false;
    }
    void operator = (std::string st){this->fill(st);}
    void operator += (std::string st){this->add(st);}
    void fill(std::string st){this->text.assign({st});}
    void add(std::string st){this->text.push_back(st);}
    std::vector<std::string> getText(){return text;}
private:
    std::vector<std::string> text;
    MessageType msgtype;
};

#endif // MESSAGE_H
