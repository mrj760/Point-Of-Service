#include "transactioneditview.h"

TransactionEditView::TransactionEditView(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("main_widget");

    itemsView = new QTableView;
    mainLayout->addWidget(itemsView);

    itemsModel = new QStandardItemModel;
    colNames.append("SKU");
    colNames.append("Name");
    colNames.append("Quantity");
    colNames.append("Price");

    itemsModel->setHorizontalHeaderLabels(colNames);
    itemsModel->setVerticalHeaderLabels(QStringList());

    itemsView->setModel(itemsModel);
    itemsView->verticalHeader()->setVisible(false);
    itemsView->verticalHeader()->setDefaultSectionSize(100);
    itemsView->setShowGrid(false);

    itemsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    itemsView->setEditTriggers(QTableView::EditTrigger::DoubleClicked);

    this->setStyleSheet(
                "#main_widget{min-width: 500px}"
                );

    appendRow(dbmanager::getItem(10000004));
}

void TransactionEditView::appendRow(Item *item)
{
    if (item == nullptr)
    {
        qDebug() << "Function \"appendRow\" was passed a null item";
        return;
    }
    if (item->qty <= 0)
    {
        qDebug() << "Cannot add Item " << item->sku << " because there is not sufficient quantity";
        displayMessage::info("Cannot add Item " + QString::number(item->sku), "Insufficient quantity");
        return;
    }

    QStandardItem *skuval = new QStandardItem(QString::number(item->sku)),
            *nameval = new QStandardItem(item->name),
            *qtyval = new QStandardItem(QString::number(item->qty)),
            *centsval = new QStandardItem(QString::number(item->cents));

    skuval->setFlags(skuval->flags() & ~Qt::ItemIsEditable);

    itemsModel->appendRow(QList<QStandardItem*>() << skuval << nameval << qtyval << centsval);
}

void TransactionEditView::appendRow(int sku, QString name, int qty, int cents)
{
    QStandardItem *skuval = new QStandardItem(QString::number(sku)),
            *nameval = new QStandardItem(name),
            *qtyval = new QStandardItem(QString::number(qty)),
            *centsval = new QStandardItem(QString::number(cents));

    skuval->setFlags(skuval->flags() & ~Qt::ItemIsEditable);

    itemsModel->appendRow(QList<QStandardItem*>() << skuval << nameval << qtyval << centsval);
}
