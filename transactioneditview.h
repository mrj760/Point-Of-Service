#ifndef TRANSACTIONEDITVIEW_H
#define TRANSACTIONEDITVIEW_H

#include <QObject>
#include <QtWidgets>
#include <QtSql>
#include <QAbstractTableModel>
#include <template_item.h>
#include <dbmanager.h>
#include <displaymessage.h>

class TransactionEditView : public QWidget
{
    Q_OBJECT
public:
    explicit TransactionEditView(QWidget *parent = nullptr);

    QVBoxLayout *mainLayout;

    /* Table for displaying items in transaction, the # of them, and the price of that many */
    QTableView *itemsView;
    QStandardItemModel *itemsModel;
    QStringList colNames;

    QLineEdit
    *skuLineEdit /* enter sku here for item lookup/entry */,
    *qtyLineEdit /* enter quantity here for # of items to add */;

    QPushButton
    *incQtyButton,
    *decQtyButton;

    QPushButton
    *addItemButton /* adds the given # of the given item to the transaction */,
    *searchByNameButton /* pop-up to search for item by name. places result sku in skuLineEdt */;

    QLabel* tax, subtotal, total;

    void AddItem(int sku);
    void RemoveItem(int sku);

    void searchByName();
    void calculatePrices();

    void appendRow(Item *item);
    void appendRow(int sku, QString name, int qty, int cents);

    void incQty();
    void decQty();

    void checkQty();

private:

    void setupTitle();
    void setupTable();
    void setupInput();

};

#endif // TRANSACTIONEDITVIEW_H
