#include "message.h"

    Message::Message(){}
    Message::MessageType Message::type(){return msgtype;}

    bool Message::operator ==(Message* msg)
    {
        if(this->type() == msg->type())
            if(this->getText()==msg->getText())
            return true;
        return false;
    }
    void Message::operator = (std::string st)
    {
        this->fill(st);
    }
    void Message::operator += (std::string st)
    {
        this->add(st);
    }
    void Message::fill(std::string st)
    {
        this->text.assign({st});
    }
    void Message::add(std::string st)
    {
        this->text.push_back(st);
    }
    std::vector<std::string> Message::getText()
    {
        return text;
    }