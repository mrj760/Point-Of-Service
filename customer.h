#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>

typedef QString qstring;

class Customer
{
public:
    Customer();
    int getID() const;
    void setID(int newID);
    const qstring &getName() const;
    void setName(const qstring &newName);
    const qstring &getAddress() const;
    void setAddress(const qstring &newAddress);

signals:
    void IDChanged();
    void nameChanged();
    void addressChanged();

private:
    int ID;
    qstring name;
    qstring address;
    Q_PROPERTY(int ID READ getID WRITE setID NOTIFY IDChanged)
    Q_PROPERTY(qstring name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(qstring address READ getAddress WRITE setAddress NOTIFY addressChanged)
};

#endif // CUSTOMER_H
