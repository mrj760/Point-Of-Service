#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Set the database which the window will work with */
void MainWindow::setDB(QSqlDatabase *db)
{
    this->db = db;
    if (!db->isOpen())
        qmsg::critical(this, "Error!", db->lastError().text());
    tmodel = new tablemodel(this, *db);
}

/* Change the name of the table which the model refers to */
void MainWindow::setTableModel(const qstr& tablename)
{
    /* Setup to work with table in db and populate the model */
    tmodel->setTable(tablename);
    tmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if (!tmodel->select())
        qDebug() << "Database Table: Unable to find table" << tablename;
    else
    {
        /* Change the widget now that the model is ready */
        QTableView* transactions = ui->transactions_list;
        transactions->setModel(tmodel);
        transactions->show();
    }
}

void MainWindow::on_items_clicked()
{
    setTableModel("pos_schema.item");
}

void MainWindow::on_customers_clicked()
{
    setTableModel("pos_schema.customer");
}


void MainWindow::on_transactions_clicked()
{
    setTableModel("pos_schema.Transaction");
}


void MainWindow::on_registers_clicked()
{
    setTableModel("pos_schema.Registers");
}


void MainWindow::on_save_clicked()
{
    if(!tmodel->submitAll())
    {
        qmsg::warning(this, "Unable to Save Changes", tmodel->lastError().text());
    }
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{

}
