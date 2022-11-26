#include "customermanagerview.h"

CustomerManagerView::CustomerManagerView(QWidget* parent)
{
    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    this->setObjectName("main_widget");

    // Title over table
    QLabel* tableTitle = new QLabel("Customers");
    mainLayout->addWidget(tableTitle);

    // TableView set to customers table
    tableView = new QTableView(this);
    tableView->setEditTriggers(QTableView::NoEditTriggers);
    tableView->setSelectionMode(QTableView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->verticalHeader()->hide();
    mainLayout->addWidget(tableView);
    tableModel = new QSqlTableModel;
    tableModel->setTable("pos_schema.customer");
    tableModel->setSort(0, Qt::SortOrder::AscendingOrder);
    tableModel->select();
    tableView->setModel(tableModel);

    connect(tableView, &QTableView::clicked, this, &CustomerManagerView::highlightCustomer);

    // below the tableview is the rest
    QWidget* bottom = new QWidget(this);
    bottom->setLayout(new QHBoxLayout(this));
    mainLayout->addWidget(bottom);

    /* ================================================== */

    /* Customer Search/Edit Section (Below TableView and on the left) */

    // contains LineEdits and buttons for table management
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

    // Add lables and LineEdits to containers
    for (int i = 0; i < 4; ++i)
    {
        searcheditlabels->layout()->addWidget(new QLabel(this->custFieldNames[i], this));
        searcheditlineedits->layout()->addWidget(lineEdits[i] = new QLineEdit(this));
    }

    // Phone and ZIP LineEdit can only have digits
    lineEdits[0]->setValidator(new QIntValidator());
    lineEdits[3]->setValidator(new QIntValidator());

    // Container for buttons for search/edit
    QWidget* searcheditright = new QWidget(this);
    searcheditright->setLayout(new QVBoxLayout(this));
    searchedit->layout()->addWidget(searcheditright);

    // Button to add new customer to db
    QPushButton *submitNewButton = new QPushButton("Submit New", this);
    submitNewButton->setObjectName("submit_button");
    connect(submitNewButton, &QPushButton::clicked, this, &CustomerManagerView::submitNew);
    searcheditright->layout()->addWidget(submitNewButton);

    // Button to edit customer which already exits in db
    QPushButton *editExistingButton = new QPushButton("Edit Existing", this);
    editExistingButton->setObjectName("edit_button");
    connect(editExistingButton, &QPushButton::clicked, this, &CustomerManagerView::editExisting);
    searcheditright->layout()->addWidget(editExistingButton);

    // Button to clear LineEdits
    QPushButton* clearButton = new QPushButton("Clear", this);
    clearButton->setObjectName("cancel_button");
    connect(clearButton, &QPushButton::clicked, this, &CustomerManagerView::clearScreen);
    searcheditright->layout()->addWidget(clearButton);

    // Add labels, LineEdits, and buttons to container underneath table view
    bottom->layout()->addWidget(searchedit);

    /* END Customer Lookup/Edit Section */

    /* ============================================== */

    /* Customer Selection Section (Below TableView and on the right) */

    // Containers for holding labels,
    QWidget *customerselect = new QWidget(),
            *customerselectleft = new QWidget(),
            *customerselectright = new QWidget();

    customerselect->setLayout(new QHBoxLayout(this));

    // holds non-editable text fields which display selected customer info
    customerselectleft->setLayout(new QVBoxLayout(this));

    // holds buttons for customer selection
    customerselectright->setLayout(new QVBoxLayout(this));

    customerselect->layout()->addWidget(customerselectleft);
    customerselect->layout()->addWidget(customerselectright);

    for (int i=0; i<4; ++i)
    {
        custInfoLabels[i] = new QLabel("", this);
        customerselectleft->layout()->addWidget(custInfoLabels[i]);
    }

    // button to attribute the current customer to the transaction
    QPushButton *selectButton = new QPushButton("Select", this);
    connect(selectButton, &QPushButton::clicked, this, &CustomerManagerView::selectCustomer);
    customerselectright->layout()->addWidget(selectButton);

    bottom->layout()->addWidget(customerselect);

    /* END Customer Selection Section */


    // button to close customer screen
    QPushButton *closeButton = new QPushButton("Close", this);
    connect(closeButton, &QPushButton::clicked, this, &CustomerManagerView::cancel);
    mainLayout->addWidget(closeButton);
}

void CustomerManagerView::submitNew()
{
    QString phone=lineEdits[0]->text(),
            name=lineEdits[1]->text(),
            address=lineEdits[2]->text(),
            zip=lineEdits[3]->text();

    // phone number (if input at all) should be 10 digits
    if (phone.length() != 0 && phone.length() != 10)
    {
        QMessageBox::warning(this, "Customer Submission Error", "Phone number must include 10 digits");
        return;
    }
    // zip number (if input at all) should be 5 digits
    if (zip.length() != 0 && zip.length() != 5)
    {
        QMessageBox::warning(this, "Customer Submission Error", "ZIP number must include 5 digits");
        return;
    }

    if (phone.length() == 0)
    {
        if (name.length() == 0)
        {
            QMessageBox::information(this, "Customer Submission Error","Must include a phone number or name");
            return;
        }
        QSqlQuery check;
        check.prepare("select from pos_schema.customer where phone is null and name = :name");
        check.bindValue(":name", name);
        if (check.size() > 0)
        {
            QMessageBox::information(this, "Customer Submission Error","Customer name already exists");
            return;
        }
    }

    QSqlQuery q;
    q.prepare("insert into pos_schema.customer values(:phone, :name, :address, :zip);");
    q.bindValue(":phone", phone=="" ? NULL : phone);
    q.bindValue(":name", name==""? NULL : name);
    q.bindValue(":address", address==""? NULL : address);
    q.bindValue(":zip", zip==""? NULL : zip);

    if (!q.exec())
    {
        QMessageBox::warning(this, "Customer Insert Error", q.lastError().text());
        qDebug() << "Customer Insert Error in func \"submitNew\"" << q.lastError().text();
        return;
    }
    QMessageBox::information(this, "Success", "Customer " + name + " added successfully");
    tableModel->select();
}

void CustomerManagerView::editExisting()
{
    // get the input text from the line edits
    QString phone=lineEdits[0]->text(),
            name=lineEdits[1]->text(),
            address=lineEdits[2]->text(),
            zip=lineEdits[3]->text();

    // phone number should be 10 digits
    if (phone.length() != 10)
    {
        QMessageBox::information(this, "Customer Update Failure", "Phone number must include 10 digits to update customer");
        return;
    }

    // zip number (if input at all) should be 5 digits
    if (zip.length() != 0 && zip.length() != 5)
    {
        QMessageBox::warning(this, "Customer Update Error", "ZIP number must include 5 digits");
        return;
    }

    // see if customer with given phone number exists in database
    QSqlQuery sel;
    sel.prepare("SELECT FROM pos_schema.customer WHERE phone = :phone");
    sel.bindValue(":phone", phone);

    if (!sel.exec())
    {
        QMessageBox::warning(this, "Customer Selection Error", sel.lastError().text());
        qDebug() << "Customer Selection Error in func \"editExisting\"" << sel.lastError().text();
        return;
    }

    // if customer doesn't exist we have nothing to update
    if (sel.size() == 0)
    {
        QMessageBox::information(this, "Update Failure", "Customer does not exist");
        return;
    }

    // actually make the update
    QSqlQuery upd;
        upd.prepare("UPDATE pos_schema.customer "
                    "SET phone = :phone, name = :name, address = :address, zip = :zip "
                    "WHERE phone = :phone;");
        upd.bindValue(":phone", phone=="" ? NULL : phone);
        upd.bindValue(":name", name==""? NULL : name);
        upd.bindValue(":address", address==""? NULL : address);
        upd.bindValue(":zip", zip==""? NULL : zip);

    if (!upd.exec())
    {
        QMessageBox::warning(this,"Customer Update Error", upd.lastError().text());
        qDebug() << "Customer update Error in func \"editExisitng\"" << upd.lastError().text();
        return;
    }

    QMessageBox::information(this, "Success", "Customer " + name + " updated successfully");
    tableModel->select();
}

void CustomerManagerView::clearScreen()
{
    for (int i = 0; i < 4; ++i)
    {
        lineEdits[i]->setText("");
        custInfoLabels[i]->setText("");
    }
}

void CustomerManagerView::selectCustomer()
{
    //TODO : send customer
}

void CustomerManagerView::cancel()
{
    this->close();
}

void CustomerManagerView::highlightCustomer()
{
    auto row = tableView->selectionModel()->selectedRows().begin()->row();
    for (int i = 0; i < 4; ++i)
    {
        auto idx = tableView->model()->index(row, i);
        auto data = tableView->model()->data(idx);
        auto value = data.value<QString>();
        custInfoLabels[i]->setText(value);
        lineEdits[i]->setText(value);
    }
}
