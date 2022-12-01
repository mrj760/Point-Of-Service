#include "dbmanager.h"

/* Constructor */

dbmanager::dbmanager(const QString &driver, const QString &path, const QString &username, const QString &password)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase(driver);
    db.setDatabaseName(path);
    db.setUserName(username);
    db.setPassword(password);

    if (!db.open())
    {
        qDebug() << "Database: Connection failed.";
        displayError("DATABASE ERROR", "Failed to connect to database. Exiting.\n" + db.lastError().text());
        exit(1);
    }

    for (auto& table: db.tables())
    {
        qDebug() << table;
    }

    qDebug() << "Database: Connection success.";
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

    QSqlQuery q;
    q.prepare("insert into pos_schema.item values((select coalesce(MAX(sku::int)+1, 10000000) from pos_schema.item), :qty, :cents, :name);");
    q.bindValue(":qty", item.qty);
    qDebug() << item.qty;
    q.bindValue(":cents", item.cents);
    q.bindValue(":name", item.name);

    if (!q.exec())
    {
        qDebug() << "Item Insertion Error: " << q.lastError().text();
        displayQueryError("Item Insertion", q);
        return false;
    }

    QMessageBox scs;
    scs.setText("Item Submission Success");
    scs.setInformativeText("Item " + item.name + " submitted successfully");
    scs.setIcon(QMessageBox::Information);
    scs.setStandardButtons(QMessageBox::Ok);
    scs.setBaseSize(600,120);
    scs.exec();
    return true;
}

/* Insert Transaction */
bool dbmanager::addTransaction(Transaction transaction)
{
    QSqlQuery q;
    q.prepare("insert into pos_schema.transaction values((SELECT coalesce(MAX(id::int)+1, 1) from pos_schema.transaction WHERE pos_schema.transaction.date = CURRENT_DATE), "
              "NOW()::date, NOW()::time, :phone, :total_cents, :items, :payment_type, :tender, :change, :card_number, :card_exp, :card_cvv);");
    q.bindValue(":phone", transaction.customerPhone);
    q.bindValue(":total_cents", transaction.totalCents);
    q.bindValue(":items", transaction.itemsAsString());
    q.bindValue(":payment_type", transaction.paymentType);
    q.bindValue(":tender", transaction.tender);
    q.bindValue(":change", transaction.change);

    q.bindValue(":card_number", transaction.cardNumber);
    q.bindValue(":card_exp", transaction.cardExpiration);
    q.bindValue(":card_cvv", transaction.cardCVV);

    if (q.exec())
    {
        qDebug() << "Transaction Insertion Error:" << q.lastError().text();
        displayQueryError("Transaction Insertion", q);
        return false;
    }

    QString id = q.lastInsertId().toString();

    QMessageBox scs;
    scs.setText("Item Submission Success");
    scs.setInformativeText("Item " + id + " submitted successfully");
    scs.setIcon(QMessageBox::Information);
    scs.setStandardButtons(QMessageBox::Ok);
    scs.setBaseSize(600,120);
    scs.exec();
    return true;
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

    QSqlQuery q;
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
    QSqlQuery q;
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


Item* dbmanager::getItem(int sku)
{
    // see if item with given sku number exists in database
    QSqlQuery sel;
    sel.prepare("SELECT qty, cents, name FROM pos_schema.item WHERE sku = :sku");
    long long longsku = sku;
    sel.bindValue(":sku", longsku);

    if (!sel.exec())
    {
        displayQueryError("Item Update Error", sel);
        qDebug() << "Item Selection Error in func \"editExisting\"" << sel.lastError().text();
        return nullptr;
    }

    // if item doesn't exist we have nothing to update
    if (sel.size() == 0)
    {
        displayError("Item Update Failure", "Item SKU number does not exist.");
        return nullptr;
    }

    sel.next();
    auto qty = sel.value(0).toInt();
    auto cents = sel.value(1).toInt();
    auto name =  sel.value(2).toString();

    return new Item(sku, qty, cents, name);
}


/*  */
/*  */
/*------------------------------------- Error Functions -------------------------------------*/
/*  */
/*  */

void dbmanager::displayError(const QString& errorType, const QString& errorText)
{
    QMessageBox error;
    error.setText(errorType);
    error.setInformativeText(errorText);
    error.setIcon(QMessageBox::Warning);
    error.setStandardButtons(QMessageBox::Ok);
    error.setBaseSize(600,120);
    error.exec();
}


/* Display Error */
void dbmanager::displayQueryError(const QString& errorType, const QSqlQuery& q)
{
    QMessageBox::warning(0, errorType+" Error", q.lastError().text());
}
