#include "dbmanager.h"
#include "qsqlrecord.h"

/* Constructor */
dbmanager::dbmanager(const qstr& driver, const qstr& path)
{    
    db = database::addDatabase(driver);
    db.setDatabaseName(path);
    db.setUserName("postgres");
    db.setPassword("grant00--");

    if (!db.open())
        qDebug() << "Database: Connection failed.";

    for (auto table : db.tables())
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
    qry q;
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
bool dbmanager::addTransaction(const int& custPhone=0, const int& totalCents=0, const qstr& items="",
                               const qstr& paymentType="", const int& tender=0, const int& change=0,
                               const int& cardNum=0, const int& cardExp=0, const int& cardCVV=0, QWidget* from=nullptr)
{
    qry q;
    q.prepare("insert into pos_schema.transaction values( (select ifnull(max(id), 0) + 1 from pos_schema.transaction), datetime('now'), "
              ":phone, :total_cents, :items, :payment_type, :tender, :change, :card_number, :card_exp, :card_cvv);");
    q.bindValue(":phone",custPhone);
    q.bindValue(":total_cents", totalCents);
    q.bindValue(":items", items);
    q.bindValue(":payment_type", paymentType);
    q.bindValue(":tender", tender);
    q.bindValue(":change", change);


    qstr cryptCardNum = crypt.encryptToString(qstr::number(cardNum));
    qstr cryptCardExp = crypt.encryptToString(qstr::number(cardExp));
    qstr cryptCardCVV = crypt.encryptToString(qstr::number(cardCVV));

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
bool dbmanager::addCustomer(const int &phone, const qstr &name, const qstr &address, const int &zip, QWidget* from=nullptr)
{
    qry q;
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
    qry q;
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
void dbmanager::displayError(const qstr& errortype, QWidget* from, const qry& q)
{
    if (from == nullptr)
        return;
    qmsg::warning(from, errortype+" Error", q.lastError().text());
}
