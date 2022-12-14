#ifndef TEMPLATE_TRANSACTION_H
#define TEMPLATE_TRANSACTION_H

#include <QString>
#include <template_item.h>
#include <vector>
#include <QStringList>
using std::tuple, std::vector;

class POS;

class Transaction
{

public:
    Transaction(int ID, QString date="", QString time="", QString customerPhone="", vector<Item> items=vector<Item>(),
                int subTotalCents=0, int salesTaxCents=0, int totalCents=0,
                QString paymentType="", int tender=0, int change=0,
                int cardNumber=0, int cardExpiration=0, int cardCVV=0)

        : ID(ID), date(date), time(time), customerPhone(customerPhone), items(items),
          subTotalCents(subTotalCents), salesTaxCents(salesTaxCents), totalCents(totalCents),
          paymentType(paymentType), tender(tender), change(change),
          cardNumber(cardNumber), cardExpiration(cardExpiration), cardCVV(cardCVV) {};

    /* Member Vars */
    int ID; /* ID of transaction */
    QString date; /* Day which the  transaction takes place */
    QString time;
    QString customerPhone; /* Phone number of the associated customer */
    vector<Item> items; /* Vector of (sku-string, quantity) tuples */
    int subTotalCents;
    int salesTaxCents;
    int totalCents; /* Total cost of cart in cents */
    QString paymentType;
    int tender;
    int change;
    int cardNumber;
    int cardExpiration;
    int cardCVV;
    QString itemsAsString()
    {
        QString ret = "";

        for (auto &item : items)
        {
            ret += QString::number(item.sku) + ", " + QString::number(item.qty);
            if (item.sku != items.back().sku)
            {
                ret += ", ";
            }
        }
        return ret;
    }
};

#endif // TEMPLATE_TRANSACTION_H
