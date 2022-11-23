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
#include <transaction.h>
#include <item.h>
#include <customer.h>
#include <register.h>

typedef QString QString;


class dbmanager :QWidget
{

    SimpleCrypt crypt;
    Database _db;

public:

    dbmanager(const QString& driver, const QString& path);
    const Database& db = _db; /* db getter */

    bool addItem(Item item);
    bool addTransaction(Transaction transaction);
    bool addCustomer(Customer customer);
    bool addRegister(Register reg);

    bool updateItem(Item item);
    bool updateTransaction(Transaction transaction);
    bool updateCustomer(Customer customer);
    bool updateRegister(Register reg);

     void displayError(const QString& errorType, const QString& errorText);
     void displayQueryError(const QString& errorType, const Query& q);
};

#endif // DBMANAGER_H
