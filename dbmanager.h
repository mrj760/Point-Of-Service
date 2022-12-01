#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QtSql>
#include <QMessageBox>
#include <vector>
#include <simplecrypt.h>
#include <template_transaction.h>
#include <template_item.h>
#include <template_customer.h>
#include <template_register.h>

typedef QString QString;


class dbmanager
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

    static Item* getItem(int sku);
    static Item* getItem(Item item);

     static void displayError(const QString& errorType, const QString& errorText);
     static void displayQueryError(const QString& errorType, const QSqlQuery& q);
};

#endif // DBMANAGER_H
