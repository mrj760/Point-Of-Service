#include "itemmanagerview.h"

ItemManagerView::ItemManagerView(QWidget* parent)
{
    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    this->setObjectName("main_widget");

    // Title over table
    QLabel* tableTitle = new QLabel("Items");
    mainLayout->addWidget(tableTitle);

    /* TableView */

    // Create and add to main layout
    tableView = new QTableView(this);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(tableView);

    // Hide indexes
    tableView->verticalHeader()->hide();

    // Can't directly edit and can only select whole rows at a time
    tableView->setEditTriggers(QTableView::NoEditTriggers);
    tableView->setSelectionMode(QTableView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Set to a table model
    tableModel = new QSqlTableModel;
    tableModel->setTable("pos_schema.item");
    tableModel->setSort(0, Qt::SortOrder::AscendingOrder);
    tableModel->select();

    connect(tableView, &QTableView::clicked, this, &ItemManagerView::highlightItem);

    /* END TableView */

    // below the tableview is the rest
    QWidget* bottom = new QWidget(this);
    bottom->setLayout(new QHBoxLayout(this));
    mainLayout->addWidget(bottom);

    /* ================================================== */

    /* Item Search/Edit Section (Below TableView and on the left) */

    // contains Labels, LineEdits, and Buttons for table management
    QWidget* searchedit = new QWidget(this);
    searchedit->setLayout(new QHBoxLayout());

    // Container for Labels tell which LineEdits are which
    QWidget* searcheditlabels = new QWidget(this);
    searcheditlabels->setLayout(new QVBoxLayout(this));
    searchedit->layout()->addWidget(searcheditlabels);

    // Container for LineEdits used for input
    QWidget* searcheditlineedits = new QWidget(this);
    searcheditlineedits->setLayout(new QVBoxLayout(this));
    searchedit->layout()->addWidget(searcheditlineedits);

    // Add Lables and LineEdits and FilterModels
    for (int i = 0; i < 4; ++i)
    {
        // Add Labels
        searcheditlabels->layout()->addWidget(new QLabel(this->itemFieldNames[i], this));

        // Add LineEdits
        searcheditlineedits->layout()->addWidget(lineEdits[i] = new QLineEdit(this));
        connect(lineEdits[i], &QLineEdit::textEdited, this, &ItemManagerView::filterResults);

        // Add/Layer Filters for searching
        filterModels[i] = new QSortFilterProxyModel();
        filterModels[i]->setFilterCaseSensitivity(Qt::CaseInsensitive);
        filterModels[i]->setFilterKeyColumn(i);
        if (i == 0)
            filterModels[i]->setSourceModel(tableModel);
        else
            filterModels[i]->setSourceModel(filterModels[i-1]);
    }

    // Set the TableView model to the last filterModel
    tableView->setModel(filterModels[3]);

    // Quantity and Cents LineEdits can only have digits
    lineEdits[0]->setValidator(new QIntValidator());
    lineEdits[1]->setValidator(new QIntValidator());
    lineEdits[2]->setValidator(new QIntValidator());

    // Container for buttons for search/edit
    QWidget* searcheditbuttons = new QWidget(this);
    searcheditbuttons->setLayout(new QVBoxLayout(this));
    searchedit->layout()->addWidget(searcheditbuttons);

    // Button to add new item to db
    QPushButton *submitNewButton = new QPushButton("Submit New", this);
    submitNewButton->setObjectName("submit_button");
    connect(submitNewButton, &QPushButton::clicked, this, &ItemManagerView::submitNew);
    searcheditbuttons->layout()->addWidget(submitNewButton);

    // Button to edit item which already exits in db
    QPushButton *editExistingButton = new QPushButton("Edit Existing", this);
    editExistingButton->setObjectName("edit_button");
    connect(editExistingButton, &QPushButton::clicked, this, &ItemManagerView::editExisting);
    searcheditbuttons->layout()->addWidget(editExistingButton);

    // Button to clear LineEdits
    QPushButton* clearButton = new QPushButton("Clear", this);
    clearButton->setObjectName("cancel_button");
    connect(clearButton, &QPushButton::clicked, this, &ItemManagerView::clearScreen);
    searcheditbuttons->layout()->addWidget(clearButton);

    // Add labels, LineEdits, and buttons to container underneath table view
    bottom->layout()->addWidget(searchedit);

    /* END Item Lookup/Edit Section */

    /* ============================================== */

    /* Item Selection Section (Below TableView and on the right) */

    // Container for holding Labels
    QWidget *itemselect = new QWidget(this);
    itemselect->setLayout(new QHBoxLayout(this));

    // Container holding read-only text fields
    QWidget *iteminfo = new QWidget(this);
    iteminfo->setLayout(new QVBoxLayout(this));
    itemselect->layout()->addWidget(iteminfo);

    // Add Labels which display selected item information
    for (int i=0; i<4; ++i)
    {
        itemInfoLabels[i] = new QLabel("", this);
        iteminfo->layout()->addWidget(itemInfoLabels[i]);
    }

    // Container holding buttons
    QWidget *itemselectbuttons = new QWidget(this);
    itemselectbuttons->setLayout(new QVBoxLayout(this));
    itemselect->layout()->addWidget(itemselectbuttons);

    // Button to attribute the current item to the transaction
    QPushButton *dropButton = new QPushButton("Delete", this);
    connect(dropButton, &QPushButton::clicked, this, &ItemManagerView::dropItem);
    itemselectbuttons->layout()->addWidget(dropButton);

    // Add item select widget to bottom
    bottom->layout()->addWidget(itemselect);

    /* END Item Selection Section */


    // button to close item screen
    QPushButton *closeButton = new QPushButton("Close", this);
    connect(closeButton, &QPushButton::clicked, this, &ItemManagerView::cancel);
    mainLayout->addWidget(closeButton);

    this->setStyleSheet(
                "QLineEdit{min-width: 120px;}"
                "QLabel{min-width:120px;}"
                );
}

void ItemManagerView::submitNew()
{
    QString
            qty=lineEdits[1]->text(),
            cents=lineEdits[2]->text(),
            name=lineEdits[3]->text();

    // No negative quantities
    if (qty.toInt() < 0)
    {
        QMessageBox error;
        error.setText("Item Submission Failure");
        error.setInformativeText("Quantity must be greater than or equal to zero");
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        return;
    }

    // time to add the item
    Item i = Item(0, qty.toInt(), cents.toInt(), name);
    if (!dbmanager::addItem(i))
    {
        // dbmanager takes care of displaying errors
        return;
    }
    tableModel->select();
}

void ItemManagerView::editExisting()
{
    // get the input text from the line edits
    QString sku=lineEdits[0]->text(),
            qty=lineEdits[1]->text(),
            cents=lineEdits[2]->text(),
            name=lineEdits[3]->text();

    // sku number should be 10 digits
    if (sku.length() != 8)
    {
        QMessageBox error;
        error.setText("Item Update Failure");
        error.setInformativeText("SKU number must include 8 digits");
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        return;
    }

    // see if item with given sku number exists in database
    QSqlQuery sel;
    sel.prepare("SELECT FROM pos_schema.item WHERE sku = :sku");
    sel.bindValue(":sku", sku.toLongLong());

    if (!sel.exec())
    {
        QMessageBox error;
        error.setText("Item Update Error");
        error.setInformativeText(sel.lastError().text());
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        qDebug() << "Item Selection Error in func \"editExisting\"" << sel.lastError().text();
        return;
    }

    // if item doesn't exist we have nothing to update
    if (sel.size() == 0)
    {
        QMessageBox error;
        error.setText("Item Update Failure");
        error.setInformativeText("Item SKU number does not exist.");
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        return;
    }

    // actually make the update
    qDebug() << "sku: " << sku << ", qty: " << qty << ", cents: " << cents << ", name: " << name;
    QSqlQuery upd;
    upd.prepare("UPDATE pos_schema.item "
                "SET qty = :qty, cents = :cents, name = :name "
                "WHERE sku = :sku;");
    upd.bindValue(":sku", sku.toLongLong());
    upd.bindValue(":qty", qty.toInt());
    upd.bindValue(":cents", cents.toInt());
    upd.bindValue(":name", name=="" ? NULL : name);

    if (!upd.exec())
    {
        QMessageBox error;
        error.setText("Item Update Error");
        error.setInformativeText(upd.lastError().text());
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        qDebug() << "Item update Error in func \"editExisitng\"" << upd.lastError().text();
        return;
    }

    QMessageBox scs;
    scs.setText("Item Update Success");
    scs.setInformativeText("Item " + name + " updated successfully");
    scs.setIcon(QMessageBox::Information);
    scs.setStandardButtons(QMessageBox::Ok);
    scs.setBaseSize(600,120);
    scs.exec();
    tableModel->select();
}

void ItemManagerView::clearScreen()
{
    for (int i = 0; i < 4; ++i)
    {
        lineEdits[i]->setText("");
        itemInfoLabels[i]->setText("");
    }
    lineEdits[0]->setReadOnly(false);
    tableModel->select();
    filterResults();
}

void ItemManagerView::dropItem()
{

    QString sku = itemInfoLabels[0]->text();
    if (sku == "")
        return;

    QString qty = itemInfoLabels[1]->text();
    if (qty.toInt() > 0)
    {
        QMessageBox error;
        error.setText("Item Drop Error");
        error.setInformativeText("Cannot drop items which are still in inventory");
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        return;
    }

    QSqlQuery drop;
    drop.prepare("delete from pos_schema.item where sku = :sku;");
    drop.bindValue(":sku", sku);
    if (!drop.exec())
    {
        QMessageBox error;
        error.setText("Item Drop Error");
        error.setInformativeText(drop.lastError().text());
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        qDebug() << "Item Drop Error: " << drop.lastError().text();
        return;
    }
    QMessageBox scs;
    scs.setText("Item Drop Success");
    scs.setInformativeText("Item " + itemInfoLabels[3]->text() + " dropped successfully");
    scs.setIcon(QMessageBox::Information);
    scs.setStandardButtons(QMessageBox::Ok);
    scs.setBaseSize(600,120);
    scs.exec();
    tableModel->select();
}

void ItemManagerView::cancel()
{
    this->hide();
}

void ItemManagerView::highlightItem()
{
    auto row = tableView->selectionModel()->selectedRows().begin()->row();
    for (int i = 0; i < 4; ++i)
    {
        auto idx = tableView->model()->index(row, i);
        auto data = tableView->model()->data(idx);
        auto value = data.value<QString>();
        itemInfoLabels[i]->setText(value);
        lineEdits[i]->setText(value);
    }
    lineEdits[0]->setReadOnly(true);
}

void ItemManagerView::filterResults()
{
    for (int i=0; i < 4; ++i)
    {
        filterModels[i]->setFilterFixedString(lineEdits[i]->text());
    }
}
