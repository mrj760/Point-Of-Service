#include "dbmanager.h"

/* Constructor */
dbmanager::dbmanager(const QString& driver, const QString& path)
{    
    _db = Database::addDatabase(driver);
    _db.setDatabaseName(path);
    _db.setUserName("postgres");
    _db.setPassword("grant00--");

    if (!_db.open())
        qDebug() << "Database: Connection failed.";
    return;

    for (auto table : _db.tables())
        qDebug() << table;

    crypt = SimpleCrypt(Q_UINT64_C(0x2fb30a1c9fddf749));
}

/*  */
/*  */
/*------------------------------------- Insertion Functions -------------------------------------*/
/*  */
/*  */

/* Insert Item */
bool dbmanager::addItem(const int& qty, const int& cents, QWidget* from=nullptr)
{
    Query q;
    q.prepare("insert into pos_schema.item values( (select ifnull(max(sku), 0) + 1 from pos_schema.item), "
              ":qty, :cents)");
    q.bindValue(":qty", qty);
    q.bindValue(":cents", cents);

    if (q.exec())
        return true;

    qDebug() << "Item Insertion Error: " << q.lastError().text();
    displayError("Insertion", from, q);
    return false;
}

/* Insert Transaction */
bool dbmanager::addTransaction(const int& custPhone=0, const int& totalCents=0, const QString& items="",
                               const QString& paymentType="", const int& tender=0, const int& change=0,
                               const int& cardNum=0, const int& cardExp=0, const int& cardCVV=0, QWidget* from=nullptr)
{
    Query q;
    q.prepare("insert into pos_schema.transaction values( "
              "(SELECT ifnull(max(id), 0) + 1 FROM pos_schema.transaction WHERE pos_schema.transactiondate.date = CURRENT_DATE), "
              "NOW()::date, NOW()::time, "
              ":phone, :total_cents, :items, :payment_type, :tender, :change, :card_number, :card_exp, :card_cvv);");
    q.bindValue(":phone",custPhone);
    q.bindValue(":total_cents", totalCents);
    q.bindValue(":items", items);
    q.bindValue(":payment_type", paymentType);
    q.bindValue(":tender", tender);
    q.bindValue(":change", change);


    QString cryptCardNum = crypt.encryptToString(QString::number(cardNum));
    QString cryptCardExp = crypt.encryptToString(QString::number(cardExp));
    QString cryptCardCVV = crypt.encryptToString(QString::number(cardCVV));

    q.bindValue(":card_number", cryptCardNum);
    q.bindValue(":card_exp", cryptCardExp);
    q.bindValue(":card_cvv", cryptCardCVV);

    if (q.exec())
        return true;

    qDebug() << "Transaction Insertion Error:" << q.lastError().text();
    displayError("Insertion", from, q);
    return false;
}

/* Insert Customer */
bool dbmanager::addCustomer(const int &phone, const QString &name, const QString &address, const int &zip, QWidget* from=nullptr)
{
    Query q;
    q.prepare("insert into pos_schema.customer values(:phone, :name, :address, :zip)");
    q.bindValue(":phone",phone);
    q.bindValue(":name",name);
    q.bindValue(":address",address);
    q.bindValue(":zip",zip);

    if (q.exec())
        return true;

    qDebug() << "Customer Insertion Error:" << q.lastError().text();
    displayError("Insertion", from, q);
    return false;
}

/* Insert Register */
bool dbmanager::addRegister(const int &id, const int &cash, QWidget* from=nullptr)
{
    Query q;
    q.prepare("insert into pos_schema.register values(:id, :cash)");
    q.bindValue(":id",id);
    q.bindValue(":cash",cash);

    if (q.exec())
        return true;

    qDebug() << "Register Insertion Error:" << q.lastError().text();
    displayError("Insertion", from, q);
    return false;
}

/*  */
/*  */
/*------------------------------------- Error Functions -------------------------------------*/
/*  */
/*  */

/* Display Error */
void dbmanager::displayError(const QString& errortype, QWidget* from, const Query& q)
{
    if (from == nullptr)
        return;
    QMessageBox::warning(from, errortype+" Error", q.lastError().text());
}
