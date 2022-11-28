#include <itemaddview.h>

ItemAddView::ItemAddView(QWidget *parent)
    : QWidget{parent}
{
    mLayout = new QVBoxLayout;
    this->setLayout(mLayout);
    this->setObjectName("ItemView");

    QLabel *title = new QLabel("Inventory");
    title->setObjectName("HeaderTitle");
    mLayout->addWidget(title);

    viewExistingItems= new QTableView;
    viewExistingItems ->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    viewExistingItems ->verticalHeader()->setVisible(false);
    mLayout->addWidget(viewExistingItems);

    itemModel = new QSqlTableModel;
    itemModel->setTable("pos_schema.item");
    itemModel->select();
    viewExistingItems->setModel(itemModel);


    QWidget *footerW = new QWidget;
    footerW->setLayout(new QHBoxLayout());
    mLayout->addWidget(footerW);

    QWidget *leftFooterW = new QWidget;
    leftFooterW->setLayout(new QVBoxLayout());


    footerW->layout()->addWidget(leftFooterW);

    QWidget* itemNameW = new QWidget;
    leftFooterW->layout()->addWidget(itemNameW);

    itemNameW->setLayout(new QHBoxLayout());
    itemNameW->layout()->setAlignment(Qt::AlignLeft);
    itemNameW->layout()->addWidget(new QLabel("Item Name"));

    itemNameInput = new QLineEdit;
    itemNameInput->setObjectName("FUCK");
    itemNameW->layout()->addWidget(itemNameInput);


    QWidget* itemQtyW = new QWidget;
    leftFooterW->layout()->addWidget(itemQtyW);

    itemQtyW->setLayout(new QHBoxLayout());
    itemQtyW->layout()->setAlignment(Qt::AlignLeft);
    itemQtyW->layout()->addWidget(new QLabel("Item Quantity"));

    itemQtyInput = new QLineEdit;
    itemQtyInput->setValidator( new QIntValidator(0, 1000000) );
    itemQtyW->layout()->addWidget(itemQtyInput);


    QWidget* itemPriceW = new QWidget;
    leftFooterW->layout()->addWidget(itemPriceW);

    itemPriceW->setLayout(new QHBoxLayout());
    itemPriceW->layout()->setAlignment(Qt::AlignLeft);
    itemPriceW->layout()->addWidget(new QLabel("Price $"));

    itemPriceInput = new QLineEdit;
    itemPriceInput->setValidator( new QDoubleValidator(0, 1000000, 2) );
    itemPriceW->layout()->addWidget(itemPriceInput);


    QPushButton *itemSubmitBtn = new QPushButton;
    itemSubmitBtn->setText("Submit");
    itemSubmitBtn->setObjectName("SubmitBtn");
    footerW->layout()->addWidget(itemSubmitBtn);
    connect(itemSubmitBtn, &QPushButton::clicked, this, &ItemAddView::handleSubmit);

    this->setStyleSheet(
                "#ItemView {min-width: 600px; min-height: 800px}"

                "#HeaderTitle{font-size: 16px; font-weight: bold}"

                "QLineEdit{max-width:150px; background-color: rgb(41, 41, 41); border: 1px solid rgba(150, 200, 180, .2) }"

                "#SubmitBtn{min-width: 200px; min-height: 100px}"

                "QLabel { max-width: 75px }"

                "");

}


void ItemAddView::handleSubmit()
{

    QString name = itemNameInput->text();
    int qty = itemQtyInput->text().toInt();
    int price = itemPriceInput->text().toDouble() * 100;

    if(name ==""){
        QMessageBox ::warning(0, "Item Table Error", "No Empty Values");
        return;
    }

    // assuming user-given name does not exist
    int existingSku = NULL;
    bool newSku = true;

    QSqlQuery qpre;
    qpre.prepare("SELECT sku FROM pos_schema.item WHERE name = :name");
    qpre.bindValue(":name", name);
    if (!qpre.exec()){
        QMessageBox ::warning(0, "Item Selection Error", qpre.lastError().text());
    }
    else {
        int recCount = 0;
        if(qpre.isSelect()){
            while (qpre.next()){
                if(recCount > 1){
                    QMessageBox ::warning(0, "Item Table Error", "Duplicate Name Sku Pairs");
//                    return;
                }
                existingSku = qpre.value(0).toInt();
                ++recCount;
            }
        }

        if(existingSku != NULL){
            QSqlQuery qedit;
            qedit.prepare("UPDATE pos_schema.item SET qty = :qty, price = :price WHERE sku = :sku");
            qedit.bindValue(":qty", qty);
            qedit.bindValue(":price", price);
            qedit.bindValue(":sku", existingSku);
            if(!qedit.exec()){
                QMessageBox ::warning(0, "Item Update Error", qedit.lastError().text());
                qDebug()<<qedit.lastQuery();
                return;
            }
            else
                newSku = false;
        }
    }

    if(newSku){
        QSqlQuery q;
        q.prepare("insert into pos_schema.item VALUES ((select coalesce(MAX(sku::int)+1, 10000000) from pos_schema.item), "
                  ":qty, :price, :name)");
        q.bindValue(":qty", qty);
        q.bindValue(":price", price);
        q.bindValue(":name", name);

        if (!q.exec()){
            QMessageBox ::warning(0, "Item Insertion Error", q.lastError().text());
            qDebug()<<q.lastQuery();
        }
    }
    itemModel->select();
}
