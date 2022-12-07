#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{
    showMaximized();
    mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->setObjectName("main_widget");

    setupTitle();
    setupOrderButtons();
    setupMgrButtons();
    setupCloseButton();

    this->setStyleSheet(
                "QTableView{font: 16px; alignment: center;}"
                "QPushButton{alignment: left; font: bold 14px; min-width:100px; max-width: 500px; min-height:90px; max-height: 250px; color: white; background-color: rgb(50,83,135);}"
                "QLineEdit{font: 16px; alignment: left; min-height: 40px; min-width: 250px; max-width: 600px;}"
                "QLabel{font: 16px; min-width:250px; max-width: 600px; min-height: 40px;}"

                "#title{font: bold 20px;}"
                "#close_button{min-width:250px; min-height: 40px; max-height: 80px}"
                );
}

void MainWindow::setupTitle()
{
    QWidget* titleHolder = new QWidget;
    titleHolder->setLayout(new QHBoxLayout);
    QLabel* title = new QLabel("G6 POS");
    titleHolder->layout()->addWidget(title);
    titleHolder->layout()->setAlignment(title, Qt::AlignCenter);
    title->setObjectName("title");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleHolder);
}

void MainWindow::setupOrderButtons()
{
    QWidget* orderbuttons = new QWidget;
    mainLayout->addWidget(orderbuttons);
    orderbuttons->setLayout(new QHBoxLayout);
    neworderbutton = new QPushButton;
    allordersbutton = new QPushButton;
    neworderbutton->setText("New Order");
    allordersbutton->setText("See All Orders");
    connect(neworderbutton, &QPushButton::clicked, this, &MainWindow::openOrderEditor);
    connect(allordersbutton, &QPushButton::clicked, this, &MainWindow::openOrdersViewer);
    static_cast<QHBoxLayout*>(orderbuttons->layout())->addWidget(neworderbutton);
    orderbuttons->layout()->addWidget(allordersbutton);
}

void MainWindow::setupMgrButtons()
{
    QWidget *mgrbuttons = new QWidget;
    mainLayout->addWidget(mgrbuttons);
    mgrbuttons->setLayout(new QHBoxLayout);
    itemmgrbutton = new QPushButton;
    custmgrbutton = new QPushButton;
    itemmgrbutton->setText("Inventory");
    custmgrbutton->setText("Customers");
    connect(itemmgrbutton, &QPushButton::clicked, this, &MainWindow::openItemMgr);
    connect(custmgrbutton, &QPushButton::clicked, this, &MainWindow::openCustMgr);
    mgrbuttons->layout()->addWidget(itemmgrbutton);
    mgrbuttons->layout()->addWidget(custmgrbutton);
}

void MainWindow::setupCloseButton()
{
    QWidget* closeButtonHolder = new QWidget;
    closeButtonHolder->setLayout(new QHBoxLayout);
    QPushButton* closeButton = new QPushButton("Close");
    closeButtonHolder->layout()->addWidget(closeButton);
    closeButton->setObjectName("close_button");
    connect(closeButton, &QPushButton::clicked, this, &exit);
    mainLayout->addWidget(closeButtonHolder);
}

void MainWindow::openOrderEditor()
{
//    if (transactioneditor == nullptr)
//        transactioneditor = new TransactionEditView;
//    transactioneditor->show();
    if (internalWindowHolder) {
        delete transactioneditor;
    }
    internalWindowHolder = new TransactionContainer(720, 480,"New Order");
    transactioneditor = new Home(*internalWindowHolder);
    internalWindowHolder->linkVirtualKeyPad(transactioneditor->getVirtualKeyPad());
    //internalWindowHolder->showFullScreen();
}

void MainWindow::openOrdersViewer()
{
    if (transactionsviewer == nullptr)
        transactionsviewer = new TransactionsViewer;
    transactionsviewer->showFullScreen();
}

void MainWindow::openItemMgr()
{
    if (itemmgr == nullptr)
    {
        itemmgr = new ItemManagerView(this);
    }
    itemmgr->showFullScreen();
}

void MainWindow::openCustMgr()
{
    if (custmgr == nullptr)
    {
        custmgr = new CustomerManagerView(this);
    }
//    custmgr->showFullScreen();
        custmgr->show();
}


void MainWindow::openRegisterMgr()
{

}

