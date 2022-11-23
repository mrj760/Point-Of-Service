#include "dbmanager.h"

/* Constructor */
dbmanager::dbmanager(const QString& driver, const QString& path)
{    
    _db = Database::addDatabase(driver);
    _db.setDatabaseName(path);
    _db.setUserName("postgres");
    _db.setPassword("grant00--");

    if (!_db.open())
    {
        qDebug() << "Database: Connection failed.";
        return;
    }

    for (auto& table: _db.tables())
    {
        qDebug() << table;
    }

    qDebug() << "Database: Connection success.";

    crypt = SimpleCrypt(Q_UINT64_C(0x2fb30a1c9fddf749));
}

/*  */
/*  */
/*------------------------------------- Insertion Functions -------------------------------------*/
/*  */
/*  */

/* Insert Item */
bool dbmanager::addItem(const int& qty, const int& cents, QWidget* from)
{
    if (qty < 0)
    {
        qDebug() << "Item Insertion Error: Invalid Quantity (Must be Greater than or Equal to Zero)";
        displayError("Item Insertion", "Invalid Quantity (Must be Greater than or Equal to Zero)", from);
        return false;
    }

    Query q;
    q.prepare("insert into pos_schema.item values((select coalesce(MAX(sku::int)+1, 10000000) from pos_schema.item), :qty, :cents);");
    q.bindValue(":qty", qty);
    q.bindValue(":cents", cents);

    if (q.exec())
        return true;

    qDebug() << "Item Insertion Error: " << q.lastError().text();
    displayQueryError("Item Insertion", from, q);
    return false;
}

/* Insert Transaction */
bool dbmanager::addTransaction(const int& custPhone, const int& totalCents, const QString& items,
                               const QString& paymentType, const int& tender, const int& change,
                               const int& cardNum, const int& cardExp, const int& cardCVV, QWidget* from)
{
    Query q;
    q.prepare("insert into pos_schema.transaction values((SELECT coalesce(MAX(id::int)+1, 1) from pos_schema.transaction WHERE pos_schema.transaction.date = CURRENT_DATE), "
              "NOW()::date, NOW()::time, :phone, :total_cents, :items, :payment_type, :tender, :change, :card_number, :card_exp, :card_cvv);");
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
    displayQueryError("Transaction Insertion", from, q);
    return false;
}

/* Insert Customer */
bool dbmanager::addCustomer(const QString& phone, const QString &name, const QString &address, const QString&zip, QWidget* from)
{
    if (phone.length() != 10)
    {
        qDebug() << "Customer Insertion Error: Invalid Phone Number (Must be 10 characters)";
        displayError("Customer Insertion", "Invalid Phone Number (Must be 10 characters)", from);
        return false;
    }
    if (zip.length() != 5)
    {
        qDebug() << "Customer Insertion Error: Invalid ZIP (Must be 5 characters)";
        displayError("Customer Insertion", "Invalid ZIP (Must be 5 characters)", from);
        return false;
    }

    Query q;
    q.prepare("insert into pos_schema.customer values(:phone, :name, :address, :zip);");
    q.bindValue(":phone",phone);
    q.bindValue(":name",name);
    q.bindValue(":address",address);
    q.bindValue(":zip",zip);

    if (q.exec())
        return true;

    qDebug() << "Customer Insertion Error:" << q.lastError().text();
    displayQueryError("Insertion", from, q);
    return false;
}

/* Insert Register */
bool dbmanager::addRegister(const int &id, const int &cash, QWidget* from)
{
    Query q;
    q.prepare("insert into pos_schema.register values(:id, :cash);");
    q.bindValue(":id",id);
    q.bindValue(":cash",cash);

    if (q.exec())
        return true;

    qDebug() << "Register Insertion Error:" << q.lastError().text();
    displayQueryError("Register Insertion", from, q);
    return false;
}




/*  */
/*  */
/*------------------------------------- Updating Functions -------------------------------------*/
/*  */
/*  */





/*  */
/*  */
/*------------------------------------- Error Functions -------------------------------------*/
/*  */
/*  */

void dbmanager::displayError(const QString& errorType, const QString& errorText, QWidget* from)
{
    if (from == nullptr)
        return;
    QMessageBox::warning(from, errorType+" Error", errorText);
}


/* Display Error */
void dbmanager::displayQueryError(const QString& errorType, QWidget* from, const Query& q)
{
    if (from == nullptr)
        return;
    QMessageBox::warning(from, errorType+" Error", q.lastError().text());
}
