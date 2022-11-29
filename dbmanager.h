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

//    static SimpleCrypt crypt;
//    Database _db;

public:

    dbmanager(const QString& driver, const QString& path, const QString& username, const QString& password);
//    const Database& db = _db; /* db getter */

    static bool addItem(Item item);
    static bool addTransaction(Transaction transaction);
    static bool addCustomer(Customer customer);
    static bool addRegister(Register reg);

    static bool updateItem(Item item);
    static bool updateTransaction(Transaction transaction);
    static bool updateCustomer(Customer customer);
    static bool updateRegister(Register reg);

     static void displayError(const QString& errorType, const QString& errorText);
     static void displayQueryError(const QString& errorType, const Query& q);
};

#endif // DBMANAGER_H
