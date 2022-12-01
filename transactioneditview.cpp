#include "transactioneditview.h"

TransactionEditView::TransactionEditView(QWidget *parent) : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("main_widget");


    setupTitle();
    setupTable();
    setupInput();


    this->setStyleSheet(
                "QTableView{font: 16px;}"
                "QPushButton{alignment: left; font: bold 14px; min-width:100px; max-width: 500px; min-height:40px; color: white; background-color: rgb(50,83,135);}"
                "QLineEdit{font: bold 20px; alignment: left; min-height: 40px; min-width: 250px; max-width: 600px;}"
                "QLabel{font: 16px; min-width:250px; max-width: 600px; min-height: 40px;}"
                "#title{font: bold 18px;}"
                "#close_button{alignment: center; min-width:250px;}"
                "#qtyLE {max-width: 60px;}"
                "#increment{alignment: left; max-width: 50px; min-height:60px; font: bold 20px;}"
                "#decrement{alignment: right; max-width: 50px; min-height:60px; font: bold 20px;}"
                );
}

void TransactionEditView::AddItem(int sku)
{
    Item* item = dbmanager::getItem(sku);
    if (item == nullptr)
    {

    }
}

void TransactionEditView::RemoveItem(int sku)
{

}

void TransactionEditView::setupTitle()
{
    QLabel* title = new QLabel("Edit Transaction");
    title->setObjectName("title");
    mainLayout->addWidget(title);
}

void TransactionEditView::setupTable()
{
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
}

void TransactionEditView::setupInput()
{
    QWidget *inputHolder = new QWidget;
    inputHolder->setLayout(new QVBoxLayout);

    QWidget* skuInputHolder = new QWidget;
    skuInputHolder->setLayout(new QHBoxLayout);
    skuLineEdit = new QLineEdit;
    skuLineEdit->setPlaceholderText("SKU");
    skuLineEdit->setValidator(new QIntValidator());

    addItemButton = new QPushButton("Add Item");
    removeItemButton = new QPushButton("Remove Item");

    skuInputHolder->layout()->addWidget(skuLineEdit);
    inputHolder->layout()->addWidget(skuInputHolder);

    QWidget* qtyInputHolder = new QWidget;
    qtyInputHolder->setLayout(new QHBoxLayout);

    qtyLineEdit = new QLineEdit;
    qtyLineEdit->setPlaceholderText("Quantity");
    qtyLineEdit->setObjectName("qtyLE");
    qtyLineEdit->setValidator(new QIntValidator());
    connect(qtyLineEdit, &QLineEdit::textEdited, this, &TransactionEditView::checkQty);

    decQtyButton = new QPushButton("-");
    incQtyButton = new QPushButton("+");
    decQtyButton->setObjectName("decrement");
    incQtyButton->setObjectName("increment");

    connect(decQtyButton, &QPushButton::clicked, this, &TransactionEditView::decQty);
    connect(incQtyButton, &QPushButton::clicked, this, &TransactionEditView::incQty);

    qtyInputHolder->layout()->addWidget(decQtyButton);
    qtyInputHolder->layout()->addWidget(qtyLineEdit);
    qtyInputHolder->layout()->addWidget(incQtyButton);
    qtyInputHolder->layout()->setAlignment(decQtyButton, Qt::AlignRight);
    qtyInputHolder->layout()->setAlignment(incQtyButton, Qt::AlignLeft);
    inputHolder->layout()->addWidget(qtyInputHolder);

    mainLayout->addWidget(inputHolder);
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
    nameval->setFlags(nameval->flags() & ~Qt::ItemIsEditable);

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

void TransactionEditView::incQty()
{
    if (skuLineEdit->text() == "")
        return;

    auto qtytext = qtyLineEdit->text();
    if (qtytext == "")
    {
        qtyLineEdit->setText("1");
    }
    else
    {
        int qty = qtytext.toInt();
        qtyLineEdit->setText(QString::number(qty+1));
    }
    checkQty();
}

void TransactionEditView::decQty()
{
    if (skuLineEdit->text() == "")
        return;

    auto qtytext = qtyLineEdit->text();
    if (qtytext == "")
    {
        qtyLineEdit->setText("");
    }
    else if (qtytext == "0")
    {
        qtytext = "0";
    }
    else
    {
        int qty = qtyLineEdit->text().toInt();
        qtyLineEdit->setText(QString::number(qty+1));
    }
    checkQty();
}

// Check that the quantity doesn't go over the max available for an item
void TransactionEditView::checkQty()
{
    if (skuLineEdit->text() == "")
    {
        qtyLineEdit->setText("");
    }

    int sku = skuLineEdit->text().toInt();
    Item* item = dbmanager::getItem(sku);
    if (item == nullptr)
    {
        skuLineEdit->setText("");
        qtyLineEdit->setText("");
        return;
    }

    int qty = qtyLineEdit->text().toInt();
    if (qty > item->qty)
    {
        qtyLineEdit->setText(QString::number(item->qty));
    }
    else if (qty < 0)
    {
        qtyLineEdit->setText("0");
    }
}

