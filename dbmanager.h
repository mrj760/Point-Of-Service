#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QWidget>
#include <QSqlDatabase>
typedef QSqlDatabase Database;
#include <QSqlQuery>
typedef QSqlQuery Query;
#include <QSqlError>
#include <QMessageBox>
#include <vector>
#include <simplecrypt.h>

typedef QString QString;


class dbmanager
{

    SimpleCrypt crypt;
    Database _db;

public:

    dbmanager(const QString& driver, const QString& path);
    const Database& db = _db; /* db getter */

    bool addItem(const int& qty, const int& cents, QWidget* from);
    bool addTransaction(const int& cust_phone, const int& total_cents, const QString& items,
                        const QString& payment_type, const int& tender, const int& change,
                        const int& card_number, const int& card_exp, const int& card_cvv, QWidget* from);
    bool addCustomer(const int& phone, const QString& name, const QString& address, const int& zip, QWidget* from);
    bool addRegister(const int& id, const int& cash, QWidget* from);
     void displayError(const QString& errorType, QWidget* from, const Query& q);
};

#endif // DBMANAGER_H
