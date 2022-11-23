#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>

class Customer
{
    friend class Main_POS; /* Allow Main_POS to access all customer details */

public:

    /* Constructors */
    Customer(QString phone="", QString name="", QString address="", QString zip="") :
        phone(phone), name(name), address(address), zip(zip) {};

    Customer(const Customer& c) :
        phone(c.phone), name(c.name), address(c.address), zip(c.zip) {};

    /* Member Vars */
    QString phone; /* Numeric customer ID (Phone Number) */
    QString name; /* Customer name */
    QString address; /* Customer street address */
    QString zip; /* Customer zip code */

    bool operator==(const Customer&); /* Return whether one Customer is equal to another based on ID */
    Customer operator=(const Customer&); /* Copy assigns the given customer */
};

#endif // CUSTOMER_H
