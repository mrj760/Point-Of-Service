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
bool dbmanager::addItem(Item item)
{
    if (item.qty < 0)
    {
        qDebug() << "Item Insertion Error: Invalid Quantity (Must be Greater than or Equal to Zero)";
        displayError("Item Insertion", "Invalid Quantity (Must be Greater than or Equal to Zero)");
        return false;
    }

    Query q;
    q.prepare("insert into pos_schema.item values((select coalesce(MAX(sku::int)+1, 10000000) from pos_schema.item), :qty, :cents);");
    q.bindValue(":qty", item.qty);
    q.bindValue(":cents", item.cents);

    if (q.exec())
        return true;

    qDebug() << "Item Insertion Error: " << q.lastError().text();
    displayQueryError("Item Insertion", q);
    return false;
}

/* Insert Transaction */
bool dbmanager::addTransaction(Transaction transaction)
{
    Query q;
    q.prepare("insert into pos_schema.transaction values((SELECT coalesce(MAX(id::int)+1, 1) from pos_schema.transaction WHERE pos_schema.transaction.date = CURRENT_DATE), "
              "NOW()::date, NOW()::time, :phone, :total_cents, :items, :payment_type, :tender, :change, :card_number, :card_exp, :card_cvv);");
    q.bindValue(":phone", transaction.customerPhone);
    q.bindValue(":total_cents", transaction.totalCents);
    q.bindValue(":items", transaction.itemsAsString());
    q.bindValue(":payment_type", transaction.paymentType);
    q.bindValue(":tender", transaction.tender);
    q.bindValue(":change", transaction.change);


    QString cryptCardNum = crypt.encryptToString(QString::number(transaction.cardNumber));
    QString cryptCardExp = crypt.encryptToString(QString::number(transaction.cardExpiration));
    QString cryptCardCVV = crypt.encryptToString(QString::number(transaction.cardCVV));

    q.bindValue(":card_number", cryptCardNum);
    q.bindValue(":card_exp", cryptCardExp);
    q.bindValue(":card_cvv", cryptCardCVV);

    if (q.exec())
        return true;

    qDebug() << "Transaction Insertion Error:" << q.lastError().text();
    displayQueryError("Transaction Insertion", q);
    return false;
}

/* Insert Customer */
bool dbmanager::addCustomer(Customer customer)
{
    if (customer.phone.length() != 10)
    {
        qDebug() << "Customer Insertion Error: Invalid Phone Number (Must be 10 characters)";
        displayError("Customer Insertion", "Invalid Phone Number (Must be 10 characters)");
        return false;
    }
    if (customer.zip.length() != 5)
    {
        qDebug() << "Customer Insertion Error: Invalid ZIP (Must be 5 characters)";
        displayError("Customer Insertion", "Invalid ZIP (Must be 5 characters)");
        return false;
    }

    Query q;
    q.prepare("insert into pos_schema.customer values(:phone, :name, :address, :zip);");
    q.bindValue(":phone",customer.phone);
    q.bindValue(":name",customer.name);
    q.bindValue(":address",customer.address);
    q.bindValue(":zip",customer.zip);

    if (q.exec())
        return true;

    qDebug() << "Customer Insertion Error:" << q.lastError().text();
    displayQueryError("Insertion", q);
    return false;
}

/* Insert Register */
bool dbmanager::addRegister(Register reg)
{
    Query q;
    q.prepare("insert into pos_schema.register values(:id, :cash);");
    q.bindValue(":id",reg.ID);
    q.bindValue(":cash",reg.centsInDrawer);

    if (q.exec())
        return true;

    qDebug() << "Register Insertion Error:" << q.lastError().text();
    displayQueryError("Register Insertion", q);
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

void dbmanager::displayError(const QString& errorType, const QString& errorText)
{
    QMessageBox::warning(0, errorType+" Error", errorText);
}


/* Display Error */
void dbmanager::displayQueryError(const QString& errorType, const Query& q)
{
    QMessageBox::warning(0, errorType+" Error", q.lastError().text());
}