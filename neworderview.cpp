#include "neworderview.h"


int luhnValidateCredit (QString credNumStr)
{
    QVector<QString> credNumF;
    for(int i=0; i<credNumStr.size(); ++i){
        credNumF.append(credNumStr[i]);
    }
    QVector<int> credNum;
    for(int i=0; i<credNumF.size(); ++i){
        credNum.append(credNumF[i].toInt());
    }
    int numLen = credNum.size();
    int doubleEvenSum = 0;

    for (int i = numLen - 2; i >= 0; i -= 2) {
        int dbl = (credNum[i]) * 2;
        if (dbl > 9) {
            dbl = (dbl / 10) + (dbl % 10);
        }
        doubleEvenSum += dbl;
    }

    for (int i = numLen - 1; i >= 0; i -= 2) {
        doubleEvenSum += credNum[i];
    }
    return doubleEvenSum % 10 == 0;
}

void setAspect(QPixmap pix, QLabel *label){
    //    int w = label->width();
    //    int h = label->height();
    if(pix.isNull()){
        label->setPixmap(pix);
    }
    else
        //        label->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        label->setPixmap(pix);
}

NewOrderView::NewOrderView(QWidget *parent)
    : QWidget{parent}
{
    this->setStyleSheet(""
                        //                        "#THIS{background-color: rgb(45, 42, 43)}"
                        "#ItemView {min-width: 550px; min-height:550px; }"

                        //                        "#ItemCategoryGrid{background-color: rgb(47, 47, 47)}"

                        "QPushButton {padding: 0px; font-size: 16px; min-height: 40px; max-height: 400px}"

                        //                        "#CategoryButton{min-height: 40px; min-width: 100px; max-width: 100px; font-size: 14px; color: rgb(160, 160, 160); background-color: rgb(41, 41, 41); border-bottom: 1px solid rgb(21, 11, 21)}"
                        //                        "#CategoryButton:hover {background-color: rgb(61, 61, 61)}"

                        //CART////////////////////////////////////////////////////////////
                        //                        "#CartDisplayWidget {background-color: rgb(21, 21, 21)}"
                        "#ItemViewLabel {min-width: 50px}"
                        //                        "#RowWidget{ background-color: rgb(31, 31, 31); padding 0px;}"
                        "#MainItemGridView {background-color: rgb(31, 31, 31); }"
                        "#MainItemGridView QPushButton:hover{background-color: rgb(0, 1, 5);}"

                        "#itemNameBtn{font-weight: bold}"
                        "#itemNameBtnRed {background-color: rgba(239, 83, 80, 0.8); font-weight: bold}"
                        "#itemNameBtnGreen{background-color: rgba(7, 251, 84, .6); font-weight: bold}"


                        ""
                        //                        "#TransactionHolder {background-color: rgb(21, 21, 21); min-width: 450px; max-width: 800px; }"

                        ""
                        ""
                        //Order Info
                        //Total Display at Bottom
                        "#TotalWidget{background-color: rgb(35, 35, 35);}"
                        "#TotalWidget QLabel{background-color: rgb(35, 35, 35); color: white; min-height: 30px; font-size: 18px; font-weight: bold}"

                        "#CartItemRow {min-height: 60px; max-height: 100px;}"
                        "#CartItemRow QLineEdit{font-size: 14px; max-width: 65px; min-height: 35px; font-weight: bold}"
                        "#CartItemRow QLabel{font-size: 14px; font-style: Lato}"

                        //                        "#CartItemRow2 { min-height: 20px; border-bottom: 1px solid rgba(100, 100, 100, .5)}"
                        //                        "#CartItemRow2 QLabel { min-height: 20px; border-bottom: 1px solid rgba(100, 100, 100, .5); font-family: Helvetica; font-size: 10px}"

                        ""
                        ""
                        //                        "#CartHeaderBtn {padding-left: 10px; border-bottom: 2px solid rgb(35, 35, 35); color: rgb(170, 170, 170); background-color: rgb(45, 43, 45); font-size: 14px; font-weight: bold;}"
                        //                        "#CartHeaderBtn:hover {background-color: rgb(71, 71, 71)}"
                        //                        "#CartHeaderBtn:checked {background-color: rgb(31, 31, 31)}"
                        ""

                        //Card Details
                        "#CardDetWidgetInner {min-height: 100px; max-height: 100px;}"
                        "#CardDetWidget {background-color: rgb(45, 45, 45); border: 1px solid rgb(21, 21, 21);}"
                        "#CardDetWidget QLabel{ max-width: 20px; font-weight: bold; font-size: 10px; color: rgb(150, 150, 150); }"
                        "#CardDetWidget QLineEdit { font-size: 14px }"
                        ""
                        "#CardSubmitBtn {background-color: rgba(76, 153, 0, .3); }"
                        "#CardSubmitBtn:hover{background-color: rgba(76, 153, 0, .6);}"
                        ""
                        "#CardLogoLabel {min-height: 80px; max-height: 80px; min-width: 130px}"
                        ""

                        //Masking Card Edit
                        "#EditMaskBtn {background-color: rgb(31, 31, 31); color: transparent}"
                        "#EditMaskBtn:hover {background-color: rgb(61, 61, 61)}"

                        "#CardExpEditStack { max-width: 680px; max-height: 30px}"
                        ""

                        //NUMPAD////
                        "#NumPad {max-height: 500px}"


                        "#HideNumPadBtn {background-color: rgb(11, 11, 11)}"
                        "#HideNumPadBtn:hover {background-color: rgb(100, 100, 100); }"

                        ///CUSTOMERR///////////////////
                        "#CustomerInputWidget {background-color: rgb(45, 45, 45)}"
                        "#CustomerInputWidget QLineEdit { max-height: 300px; font-size: 16px}"
                        "#CustomerInfoWidget {max-height: 400px;}"
                        ""
                        ""
                        //FULL ORDER DETAILSSS///////////
                        "#FullOrderDetailsW {}"
                        "#FullOrderDetailsW QLabel {font-weight: bold}"
                        //                        "QTableView::item {background-color: black; color: rgb(160, 160, 160);}"
                        //                        "#CardEditStack {max-height: 30px}"
                        "#OrderDetLabel {color: rgb(170, 170, 170); }"
                        "#OrderDetValue{color: rgb(211, 211, 211); }"
                        "#OrderDetLabelTOTAL {color: rgb(170, 170, 170); font-size: 16px; font-weight: bold}"
                        "#OrderDetValueTOTAL {color: rgb(240, 230, 240); font-size: 24px; font-weight: normal;}"
                        "");

    numPadMinimalCardDets = new NumpadWidget;
    numPadMinimalCardDets->setObjectName("NumPad");

    mLayout = new QVBoxLayout;
    this->setLayout(mLayout);
    this->setObjectName("newOrderView");
    QLabel *title = new QLabel("Transaction");
    title->setObjectName("HeaderTitle");
    mLayout->addWidget(title);


    innerViewWidget = new QWidget;
    innerViewWidget->setObjectName("THIS");
    innerViewWLayout = new QHBoxLayout;
    innerViewWLayout->setSpacing(0);
    innerViewWLayout->setContentsMargins(0, 0, 0, 0);
    innerViewWLayout->setAlignment(Qt::AlignLeft);

    innerViewWidget->setLayout(innerViewWLayout);
    mLayout->addWidget(innerViewWidget);
    mLayout->setStretchFactor(title, 0);
    mLayout->setStretchFactor(innerViewWidget, 1);


    QWidget *transactionView = new QWidget;
    transactionView->setObjectName("TransactionView");
    innerViewWLayout->addWidget(transactionView);

    QHBoxLayout* transactionViewLayout = new QHBoxLayout();
    transactionView->setLayout(transactionViewLayout);
    transactionViewLayout->setContentsMargins(0, 0, 0, 0);
    transactionViewLayout->setSpacing(0);
    transactionViewLayout->setAlignment(Qt::AlignLeft);


    itemCategoryButtonGrid = new QWidget;
    transactionViewLayout->addWidget(itemCategoryButtonGrid);
    itemCategoryButtonGrid->setObjectName("ItemCategoryGrid");
    itemCategoryLayout = new QVBoxLayout;
    itemCategoryLayout->setContentsMargins(0, 0, 0, 0);
    itemCategoryLayout->setSpacing(0);
    itemCategoryLayout->setAlignment(Qt::AlignTop);
    itemCategoryButtonGrid->setLayout(itemCategoryLayout);

    itemView = new QWidget;
    itemView->setObjectName("ItemView");
    transactionViewLayout->addWidget(itemView);
    QVBoxLayout *itemViewLayout = new QVBoxLayout();
    itemView->setLayout(itemViewLayout);
    itemViewLayout->setSpacing(0);
    itemViewLayout->setContentsMargins(0, 0, 0, 0);
    transactionViewLayout->setStretch(0, 0);
    transactionViewLayout->setStretch(1, 1);

    QWidget *transactionHolderWidget = new QWidget;
    transactionHolderWidget->setObjectName("TransactionHolder");
    transHolderWLayout = new QVBoxLayout;
    transHolderWLayout->setSpacing(0);
    transHolderWLayout->setContentsMargins(0, 0, 0, 0);


    transactionHolderWidget->setLayout(transHolderWLayout);
    innerViewWLayout->addWidget(transactionHolderWidget);

    innerViewWLayout->setStretchFactor(transactionView, 6);
    innerViewWLayout->setStretchFactor(transactionHolderWidget, 3);

    //    transHolderWLayout->addWidget(new QLabel("Order Info"));
    //    QWidget *cartHeaderW = new QWidget;
    //    cartHeaderW->setLayout(new QHBoxLayout());

    //    QButtonGroup *headerBtnGroup = new QButtonGroup(cartHeaderW);
    //    QPushButton *cartHeaderBtn = new QPushButton("🛒 Items");
    //    cartHeaderBtn->setCheckable(true);
    //    cartHeaderBtn->setChecked(true);
    //    cartHeaderBtn->setObjectName("CartHeaderBtn");
    //    cartHeaderW->layout()->addWidget(cartHeaderBtn);
    ////    cartHeaderBtn->setStyleSheet("padding-left: 10px; border-bottom: 2px solid rgb(35, 35, 35); color: rgb(170, 170, 170); background-color: rgb(45, 43, 45); font-size: 14px; font-weight: bold ");
    //    QPushButton *pmntHeaderBtn = new QPushButton("🧾 Payment");
    //    pmntHeaderBtn->setObjectName("CartHeaderBtn");
    //    pmntHeaderBtn->setCheckable(true);
    //    headerBtnGroup->addButton(pmntHeaderBtn);
    //    headerBtnGroup->addButton(cartHeaderBtn);
    //    connect(cartHeaderBtn, &QPushButton::clicked, this, &NewOrderView::handleCartHeaderClick);
    //    connect(pmntHeaderBtn, &QPushButton::clicked, this, &NewOrderView::handleCartHeaderClick);
    //    cartHeaderW->layout()->addWidget(pmntHeaderBtn);
    ////    pmntHeaderBtn->setStyleSheet("padding-left: 10px; border-bottom: 2px solid rgb(35, 35, 35); color: rgb(170, 170, 170); background-color: rgb(45, 43, 45); font-size: 14px; font-weight: bold;");
    //    transHolderWLayout->addWidget(cartHeaderW);


    scrollCart = new QScrollArea;
    scrollCart->setWidgetResizable(true);
    scrollCart->setObjectName("ScrollWidget");
    transHolderWLayout->addWidget(scrollCart);
    transHolderWLayout->setStretchFactor(scrollCart, 6);


    //Total Widget
    QWidget *totalW = new QWidget;
    totalW->setObjectName("TotalWidget");
    totalW->setLayout(new QHBoxLayout());
    totalW->layout()->addWidget(new QLabel("Sub Total: "));
    totalW->layout()->setAlignment(Qt::AlignCenter);
    totalLabel = new QLabel();
    //    totalLabel->setObjectName("TotalLabel");
    totalW->layout()->addWidget(totalLabel);
    transHolderWLayout->addWidget(totalW);


    //Payment Tab//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    paymentWidget = new QWidget;
    //    paymentWidget->hide();
    paymentWLayout = new QVBoxLayout;
    paymentWidget->setLayout(paymentWLayout);
    transHolderWLayout->addWidget(paymentWidget);
    transHolderWLayout->setStretchFactor(paymentWidget, 0);
    paymentWidget->setObjectName("PaymentWidget");

    //💸 💵 🤑 ☏ 👤

    QWidget *paymentHeaderW = new QWidget;
    paymentWLayout->addWidget(paymentHeaderW);
    paymentHeaderW->setLayout(new QHBoxLayout());

    orderBtnGroup = new QButtonGroup(paymentHeaderW);

    orderHideBtn = new QPushButton("");
    connect(orderHideBtn, &QPushButton::clicked, this, &NewOrderView::showFullOrderDetails);
    orderHideBtn->setCheckable(true);
    orderBtnGroup->addButton(orderHideBtn);

    QPushButton *cashBtn = new QPushButton("💸 Cash");
    cashBtn->setCheckable(true);
    orderBtnGroup->addButton(cashBtn);
    connect(cashBtn, &QPushButton::clicked, this, &NewOrderView::cashPaymentClicked);

    QPushButton *cardBtn = new QPushButton("💳 Card");
    cardBtn->setCheckable(true);
    orderBtnGroup->addButton(cardBtn);
    connect(cardBtn, &QPushButton::clicked, this, &NewOrderView::cardPaymentClicked);

    QPushButton *couponBtn = new QPushButton("🤑 Coupon");
    couponBtn->setCheckable(true);
    orderBtnGroup->addButton(couponBtn);

    QPushButton *customerButton = new QPushButton;
    customerButton->setCheckable(true);
    orderBtnGroup->addButton(customerButton);
    connect(customerButton, &QPushButton::clicked, this, &NewOrderView::customerClicked);
    customerButton->setText("👤 Customer");

    paymentHeaderW->layout()->addWidget(cashBtn);
    paymentHeaderW->layout()->addWidget(cardBtn);
    paymentHeaderW->layout()->addWidget(couponBtn);
    paymentHeaderW->layout()->addWidget(customerButton);


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Card Payment Display
    cardPmtWidget = new QWidget;
    cardPmtWidget->hide();
    cardPmtWidget->setObjectName("CardDetWidget");
    cardPmtWidget->setLayout(new QVBoxLayout());

    cardVecDisplayW = new QWidget;
    cardVecDisplayW->setLayout(new QVBoxLayout());
    cardVecDisplayW->layout()->addWidget(new QLabel("Card"));
    cardVecDisplayW->layout()->setAlignment(Qt::AlignTop);
    cardPmtWidget->layout()->addWidget(cardVecDisplayW);


    cardNumEdit = new QLineEditFocus;
    lineEditNumpadVec.append(cardNumEdit);
    QRegularExpression R_Card("^[0-9]+");
    QRegularExpressionValidator *validCard = new QRegularExpressionValidator(R_Card);
    cardNumEdit->setValidator(validCard);
    connect(cardNumEdit, &QLineEdit::textChanged, this, &NewOrderView::handleCardEdit);
    cardPmtWidget->layout()->addWidget(cardNumEdit);


    QWidget *cardDetWidget = new QWidget;
    cardDetWidget->setObjectName("CardDetWidgetInner");
    cardDetWidget->setLayout(new QHBoxLayout());
    cardDetWidget->layout()->setAlignment(Qt::AlignCenter);
    cardDetWidget->layout()->setSpacing(40);
    cardDetWidget->layout()->setContentsMargins(40, 0, 40, 0);
    cardPmtWidget->layout()->addWidget(cardDetWidget);


    // Set date validator for date lineedit
    QRegularExpression R_date("^((0[1-9])|(1[0-2]))/([0-9]{4})$");
    QRegularExpressionValidator *valida = new QRegularExpressionValidator(R_date);
    cardDetWidget->layout()->addWidget(new QLabel("Exp "));
    cardExpEdit = new QLineEditFocus;
    lineEditNumpadVec.append(cardExpEdit);
    connect(cardExpEdit, &QLineEdit::textChanged, this, &NewOrderView::catchExpCard);
    cardDetWidget->layout()->addWidget(cardExpEdit);
    cardExpEdit->setStyleSheet("max-width: 100px");

    cardExpEdit->setValidator(valida);
    //    cardExpEdit->setInputMask("00/0000");
    //    cardExpEdit->setPlaceholderText("05/" + QString::number(QDate::currentDate().year() + 5));
    cardExpEdit->setCursorPosition(0);



    cardExpEditBtn =  new QPushButton;
    connect(cardExpEditBtn, &QPushButton::clicked, this, &NewOrderView::handleCardExpMask);
    cardExpEditBtn->setObjectName("EditMaskBtn");
    cardExpEditBtn->setText("Card Expiration");

    cardExpEditStack = new QStackedWidget;
    cardExpEditStack->setObjectName("CardExpEditStack");
    cardExpEditStack->addWidget(cardExpEditBtn);
    cardExpEditStack->setCurrentWidget(cardExpEditBtn);

    cardDetWidget->layout()->addWidget(new QLabel("CVV "));
    cardCvvEdit = new QLineEditFocus;
    lineEditNumpadVec.append(cardCvvEdit);


    cardCvvEdit->setStyleSheet("max-width: 55px; min-height: 30px; max-height: 30px");
    cardCvvEdit->setValidator( new QIntValidator(0, 1000) );
    cardDetWidget->layout()->addWidget(cardCvvEdit);


    QPushButton *cardSubmitBtn = new QPushButton;
    connect(cardSubmitBtn, &QPushButton::clicked, this, &NewOrderView::handleSubmitCard);
    cardSubmitBtn->setObjectName("CardSubmitBtn");
    cardSubmitBtn->setText("Submit");



    /////////////////////////MAKE THIS A STACK INSTEAD/////////////////

    infoEditStack = new QStackedWidget;
    //    paymentWLayout->addWidget(infoEditStack);


    QWidget *cardPmtFooterW = new QWidget;
    cardPmtFooterW->setLayout(new QHBoxLayout());
    cardLogoLabel = new QLabel;
    cardLogoLabel->setObjectName("CardLogoLabel");
    cardPmtFooterW->layout()->addWidget(cardLogoLabel);
    cardPmtFooterW->layout()->addWidget(cardSubmitBtn);
    cardPmtWidget->layout()->addWidget(cardPmtFooterW);
    paymentWLayout->addWidget(cardPmtWidget);
    //    infoEditStack->addWidget(cardPmtWidget);



    //NUMPADYY
    QPushButton *hideNumPadBtn = new QPushButton;
    hideNumPadBtn->setObjectName("HideNumPadBtn");
    hideNumPadBtn->setText("⌨");
    connect(hideNumPadBtn, &QPushButton::clicked, this, &NewOrderView::hideNumpad);

    transHolderWLayout->addWidget(hideNumPadBtn);
    transHolderWLayout->addWidget(numPadMinimalCardDets);
    transHolderWLayout->setStretchFactor(numPadMinimalCardDets, 4);



    //CUSTOMER INFO/////////////////////////////////////////////////////////////////////////////////
    customerInfoWidget = new QWidget;
    customerInfoWidget->setObjectName("CustomerInfoWidget");
    customerInfoWidget->hide();
    customerInfoWidget->setLayout(new QHBoxLayout());
    paymentWLayout->addWidget(customerInfoWidget);


    QWidget *custEditW = new QWidget;
    custEditW->setObjectName("CustomerInputWidget");
    QVBoxLayout *custEditWLayout = new QVBoxLayout;
    custEditW->setLayout(custEditWLayout);
    customerInfoWidget->layout()->addWidget(custEditW);

    for(int i=0; i<custLabVec.size(); ++i)
    {
        bool nameSplit = false;
        bool addressSplit = false;
        bool phoneSplit = false;
        QLineEditFocus *custEdit = new QLineEditFocus;
        customerEditVec.append(custEdit);
        QString label = custLabVec[i];
        if(label == "Zip") {
            QRegularExpression R("^[0-9\-]{12}");
            QRegularExpressionValidator *validator = new QRegularExpressionValidator(R);
            custEdit->setValidator(validator);
            lineEditNumpadVec.append(custEdit);
        }
        else if(label == "Phone"){
            phoneSplit = true;
            QWidget *phoneW = new QWidget;
            custEditWLayout->addWidget(phoneW);
            phoneW->setLayout(new QHBoxLayout());
            phoneW->layout()->setContentsMargins(0, 5, 10, 5);
            bannedIndLabel = new QLabel("🗸");
            phoneW->layout()->addWidget(custEdit);
            phoneW->layout()->addWidget(bannedIndLabel);
            bannedIndLabel->setStyleSheet("font-size: 14px; color black; ");

            QRegularExpression R("^[0-9]{10}");
            custEdit->setValidator(new QRegularExpressionValidator(R));
            lineEditNumpadVec.append(custEdit);
            ///
            ///
            QCompleter *phoneCompleter = new QCompleter();
            connect(phoneCompleter, QOverload<const QString &>::of(&QCompleter::activated), this, &NewOrderView::handleExistingPhoneFill);

            phoneModel = new QSqlTableModel;

            phoneModel->setTable("pos_customer");
            phoneModel->select();
            phoneCompleter->setModel(phoneModel);
            phoneCompleter ->setFilterMode(Qt::MatchContains);
            phoneCompleter->setCompletionColumn(0);
            phoneCompleter->setCompletionMode(QCompleter::PopupCompletion);
            phoneCompleter->setCaseSensitivity(Qt::CaseInsensitive);
            QAbstractItemView *popup = phoneCompleter->popup();
            QStyledItemDelegate *mCompleterItemDelegate = new QStyledItemDelegate;
            popup->setItemDelegate(mCompleterItemDelegate);
            popup->setObjectName("PopupCompleter");
            //            popup->setStyleSheet("::item:hover {background-color: black; color: rgb(160, 160, 160);} ::item {background-color: rgb(35, 35, 35); }");
            custEdit->setCompleter(phoneCompleter);
        }
        else if(label == "Name"){
            nameSplit = true;
        }
        else if(label == "Address"){
            addressSplit = true;
            custEdit->setObjectName(custEditObjectNamePre + label);
            custEdit->setPlaceholderText(custLabVec[i]);
            custEditWLayout->addWidget(custEdit);
            custEditWLayout->setStretchFactor(custEdit, 6);

            QWidget *addressW = new QWidget;
            addressW->setStyleSheet("border: 1px solid rgb(31,31, 31);");
            addressW->setLayout(new QHBoxLayout());
            addressW->layout()->setSpacing(5);
            addressW->layout()->setContentsMargins(0, 0, 0, 0);

            custEditWLayout->addWidget(addressW);
            custEditWLayout->setStretchFactor(addressW, 4);


            QRegularExpression R("^[a-zA-Z]{20}");
            QRegularExpressionValidator *validator = new QRegularExpressionValidator(R);

            QLineEdit *custEditCity= new QLineEdit;
            customerEditVec.append(custEditCity);
            addressW->layout()->addWidget(custEditCity);
            custEditCity->setValidator(validator);
            custEditCity->setObjectName(custEditObjectNamePre + "City");
            custEditCity->setPlaceholderText("City");
            custEditCity->setValidator(validator);


            QLineEdit *custEditState= new QLineEdit;
            customerEditVec.append(custEditState);
            addressW->layout()->addWidget(custEditState);
            custEditState->setValidator(validator);
            custEditState->setObjectName(custEditObjectNamePre + "State");
            custEditState->setPlaceholderText("State");
        }
        if(nameSplit || addressSplit){
            if(nameSplit){
                QWidget *nameW = new QWidget;
                nameW->setStyleSheet("border: 1px solid rgb(31,31, 31);");
                nameW->setLayout(new QHBoxLayout());
                nameW->layout()->setSpacing(5);
                nameW->layout()->setContentsMargins(0, 0, 0, 0);

                custEditWLayout->addWidget(nameW);
                custEditWLayout->setStretchFactor(nameW, 4);


                nameW->layout()->addWidget(custEdit);

                custEdit->setObjectName(custEditObjectNamePre + "First");
                custEdit->setPlaceholderText("First");

                QRegularExpression R("^[a-zA-Z]{20}");
                QRegularExpressionValidator *validator = new QRegularExpressionValidator(R);
                custEdit->setValidator(validator);


                QLineEdit *custEditN= new QLineEdit;
                customerEditVec.append(custEditN);
                nameW->layout()->addWidget(custEditN);
                custEditN->setValidator(validator);
                custEditN->setObjectName(custEditObjectNamePre + "Last");
                custEditN->setPlaceholderText("Last");
            }
        }
        else {
            custEdit->setObjectName(custEditObjectNamePre + label);
            custEdit->setPlaceholderText(custLabVec[i]);
            if(!phoneSplit){
                custEditWLayout->addWidget(custEdit);
                custEditWLayout->setStretchFactor(custEdit, 6);
            }
        }
    }

    QWidget *custFootW = new QWidget;
    QHBoxLayout *custFootWLayout = new QHBoxLayout();
    custEditWLayout->addWidget(custFootW);
    custFootW->setLayout(custFootWLayout);
    custFootWLayout->setContentsMargins(0,0,0, 0);


    QPushButton *custSubmitBtn = new QPushButton;
    connect(custSubmitBtn, &QPushButton::clicked, this, &NewOrderView::handleSubmitCustomer);
    custSubmitBtn->setObjectName("CardSubmitBtn");
    custSubmitBtn->setText("Submit");
    custFootWLayout->addWidget(custSubmitBtn);

    QPushButton *custClearBtn = new QPushButton;
    connect(custClearBtn, &QPushButton::clicked, this, &NewOrderView::handleSubmitCustomer);
    custClearBtn->setText("Clear");
    custFootWLayout->addWidget(custClearBtn);
    custFootWLayout->setStretchFactor(custSubmitBtn, 3);
    custFootWLayout->setStretchFactor(custClearBtn, 1);

    custNotesEdit = new QTextEdit;
    customerInfoWidget->layout()->addWidget(custNotesEdit);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //FULL ORDER WIDGET//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    fullOrderDetailsW = new QWidget;
    fullOrderDetailsW->hide();
    //    fullOrderDetailsW->setObjectName("FullOrderDetailsW");
    paymentWLayout->addWidget(fullOrderDetailsW);
    fullOrderDetailsW->setLayout(new QVBoxLayout());

    QWidget *leftOrderDetW = new QWidget;
    fullOrderDetailsW->layout()->addWidget(leftOrderDetW);
    leftOrderDetW->setLayout(new QVBoxLayout());
    leftOrderDetW->setObjectName("FullOrderDetailsW");
    //    QWidget *rightOrderDetW = new QWidget;
    //    fullOrderDetailsW->layout()->addWidget(rightOrderDetW);
    //    rightOrderDetW->setLayout(new QVBoxLayout());
    QVector<QString> orderDetLabelVec ={"LINES", "DISCOUNTS", "TAX", "TOTAL DUE"};
    for(int i=0; i<4; ++i){
        QWidget *rowW = new QWidget;
        leftOrderDetW->layout()->addWidget(rowW);
        rowW->setLayout(new QHBoxLayout());
        QLabel *label = new QLabel(orderDetLabelVec[i]);
        label->setObjectName("OrderDetLabel");
        //        label->setStyleSheet("");
        rowW->layout()->addWidget(label);
        QLabel *labelVal = new QLabel;
        labelVal->setObjectName("OrderDetValue");
        orderDetValueVec.append(labelVal);
        rowW->layout()->addWidget(labelVal);
        if(orderDetLabelVec[i] == "TOTAL DUE"){
            label->setObjectName("OrderDetLabelTOTAL");
            labelVal->setObjectName("OrderDetValueTOTAL");
        }
    }

    QWidget *footerW = new QWidget;
    footerW->setLayout(new QHBoxLayout);
    footerW->layout()->setContentsMargins(0, 0, 0, 0);
    footerW->layout()->setSpacing(0);
    QLabel *fill = new QLabel();
    //    fill->setStyleSheet("min-width: 400px");
    mLayout->addWidget(footerW);

    footerW->layout()->addWidget(fill);
    //    footerW->layout()->addWidget(numPadMinimalCardDets);


    loadCategories();
    connect(this, &NewOrderView::signalUpdateCartView, this, &NewOrderView::handleUpdateCartView);
    connect(this, &NewOrderView::signalUpdateCartTotal, this, &NewOrderView::handleCartTotalChange);
    //    connect(this, &NewOrderView::signalEditSubmitted, this, &NewOrderView::hideNumpad);

    for(int i=0; i < lineEditNumpadVec.size(); ++i){
        connect(lineEditNumpadVec[i], &QLineEditFocus::editFocused, this, &NewOrderView::showNumpad);
        //        connect(lineEditNumpadVec[i], &QLineEditFocus::editUnFocused, this, &NewOrderView::hideNumpad);
    }
}


//Item Functions///////////////////////////////////////////////////
void NewOrderView::loadItems()
{
    QPushButton *ptPush = qobject_cast<QPushButton*>(sender());
    QString category = ptPush->text();
    QSqlQuery q;
    q.prepare("SELECT name, cents, qty FROM pos_schema.item WHERE category = :category");
    q.bindValue(":category", category);
    if(!q.exec()){
        qDebug()<<"Item retrieval error";
        return;
    }
    else {
        itemCentsVec.clear();
        itemQtyVec.clear();
        itemNameVec.clear();
        if(q.isSelect()){
            while(q.next()){
                itemCentsVec.append(q.value(1).toInt());
                itemQtyVec.append(q.value(2).toInt());
                itemNameVec.append(q.value(0).toString());
            }
        }
    }
    for(int i=0; i<itemWidgetVec.size(); ++i){
        itemWidgetVec[i]->deleteLater();
    }

    itemWidgetVec.clear();

    QWidget *mItemW = new QWidget;
    mItemW->setObjectName("MainItemGridView");
    QVBoxLayout *mItemWLayout = new QVBoxLayout;
    mItemW->setLayout(mItemWLayout);
    mItemW->layout()->setSpacing(0);
    mItemW->layout()->setAlignment(Qt::AlignTop);
    mItemW->layout()->setContentsMargins(0, 0, 0, 0);
    itemView->layout()->addWidget(mItemW);
    itemWidgetVec.append(mItemW);

    for(int i=0; i<itemNameVec.size(); ++i){

        if(i % 4 == 0 || i== 0){
            rowW = new QWidget;
            rowW->setObjectName("RowWidget");
            mItemW->layout()->addWidget(rowW);
            mItemWLayout->setStretchFactor(rowW, 1);
            rowW->setLayout(new QHBoxLayout());
            rowW->layout()->setSpacing(2);
            rowW->setContentsMargins(0, 0, 0, 0);
        }

        QWidget* nItem = new QWidget;
        nItem->setObjectName("ItemWidget");
        //        nItem->setStyleSheet("min-width: 100px; min-height: 100px");
        nItem->setLayout(new QVBoxLayout());

        nItem->layout()->setSpacing(0);
        nItem->layout()->setAlignment(Qt::AlignTop);
        nItem->layout()->setContentsMargins(0, 0, 0, 0);
        //        nItem->layout()->setSpacing(0);
        QPushButton *itemNameBtn = new QPushButton;
        //        itemNameBtn->setStyleSheet(":hover{background-color: rgb(61, 61, 61);}");
        itemNameBtn->setText(itemNameVec[i]);
        nItem->layout()->addWidget(itemNameBtn);

        itemNameBtn->setObjectName("itemNameBtn");
        if(itemQtyVec[i]<1){
            itemNameBtn->setObjectName("itemNameBtnRed");
        }
        else{
            itemNameBtn->setObjectName("itemNameBtnGreen");
        }
        itemNameBtn->style()->unpolish(itemNameBtn);
        itemNameBtn->style()->polish(itemNameBtn);

        nItem->setObjectName("itemButton");
        rowW->layout()->addWidget(itemNameBtn);
        connect(itemNameBtn, &QPushButton::clicked, this, &NewOrderView::handleItemClicked);

    }
}

void NewOrderView::loadCategories()
{
    QSqlQuery q;
    q.prepare("SELECT DISTINCT category FROM pos_schema.item");
    if(!q.exec()){
        qDebug()<<"Category retrieval error";
        return;
    }
    else {
        itemCategoryVec.clear();
        if(q.isSelect()){
            while(q.next()){
                itemCategoryVec.append(q.value(0).toString());
            }
        }
    }

    for(int i=0; i<categoryWidgetVec.size(); ++i){
        categoryWidgetVec[i]->deleteLater();
    }
    categoryWidgetVec.clear();

    for(int i=0; i<itemCategoryVec.size(); ++i){
        QPushButton *catBtn = new QPushButton;
        connect(catBtn, &QPushButton::clicked, this, &NewOrderView::loadItems);
        catBtn->setObjectName("CategoryButton");
        catBtn->setText(itemCategoryVec[i]);
        itemCategoryLayout->addWidget(catBtn);
        categoryWidgetVec.append(catBtn);
    }

}

//Cart Functions///////////////////////////////////////////////////
void NewOrderView::dropCartItem()
{
    QString dropName = "";
    QPushButton *nPush = qobject_cast<QPushButton*>(sender());
    QWidget *par = nPush->parentWidget();
    dropName = par->findChild<QLabel*>("CartItemName")->text();

    int idx = -1;
    for(int i=0; i<activeCartItemNameVec.size(); ++i){
        if(activeCartItemNameVec[i] == dropName){
            idx = i;
            break;
        }
    }

    if(idx !=-1){
        activeCartItemNameVec.remove(idx);
        activeCartItemQtyVec.remove(idx);
        activeCartItemTotalVec.remove(idx);
        activeCartItemCentsVec.remove(idx);
        runningTotal = 0;
        for(int i=0; i<activeCartItemNameVec.size(); ++i){
            runningTotal+= activeCartItemQtyVec[i] * activeCartItemCentsVec[i];
        }
        emit signalUpdateCartView();
    }

}

void NewOrderView::handleItemClicked(){

    QPushButton *item = qobject_cast<QPushButton*>(sender());

    QString name = item->text();

    bool newItem = true;
    for(int i=0; i<activeCartItemNameVec.size(); ++i){
        if(activeCartItemNameVec[i] == name){
            activeCartItemQtyVec[i]++;
            newItem = false;
            break;
        }
    }
    if(newItem){
        activeCartItemNameVec.append(name);
        activeCartItemQtyVec.append(1);
        activeCartItemTotalVec.append(0);
    }

    runningTotal = 0;
    for(int i=0; i<activeCartItemNameVec.size(); ++i){
        double cents = 0;
        double tempTotal = 0;

        QSqlQuery q;
        q.prepare("SELECT cents FROM pos_schema.item WHERE name = :name");
        q.bindValue(":name", name);
        if(!q.exec()){
            qDebug()<<q.lastError();
        }
        if(q.isSelect()){
            while(q.next()){
                cents = q.value(0).toDouble() / 100;
                tempTotal = activeCartItemQtyVec[i] * cents;
                activeCartItemCentsVec.append(cents);
                activeCartItemTotalVec[i] = tempTotal;
                runningTotal +=tempTotal;
            }
        }
    }
    emit signalUpdateCartView();
}

void NewOrderView::handleUpdateCartView()
{
    for(int i=0; i<cartItemWidgetVec.size(); ++i){
        cartItemWidgetVec[i]->deleteLater();
    }
    cartItemWidgetVec.clear();

    for(int i=0; i<oldcartWVec.size(); ++i){
        oldcartWVec[i]->deleteLater();
    }
    oldcartWVec.clear();


    QWidget *cartDisplayWidget = new QWidget;
    cartDisplayWidget->setObjectName("CartDisplayWidget");
    QVBoxLayout *cartDisplayWLayout = new QVBoxLayout;
    cartDisplayWidget->setLayout(cartDisplayWLayout);
    oldcartWVec.append(cartDisplayWidget);
    //    cartItemViewWLayout->addWidget(cartDisplayWidget);

    for(int i=0; i<activeCartItemNameVec.size(); ++i){
        QWidget *cartItemRow = new QWidget;
        cartItemRow->setObjectName("CartItemRow");
        QHBoxLayout *rowLayout = new QHBoxLayout;
        cartItemRow->setLayout(rowLayout);
        cartItemRow->layout()->setSpacing(60);

        QLineEditSelect *cartQtyEdit = new QLineEditSelect;
        QRegularExpression R_Qty("[1-9][0-9]{6}");
        QRegularExpressionValidator *qtyValidator = new QRegularExpressionValidator(R_Qty);
        cartQtyEdit->setValidator(qtyValidator);
        connect(cartQtyEdit, &QLineEdit::textEdited, this, &NewOrderView::handleQtyChanged);
        rowLayout->addWidget(cartQtyEdit);
        cartQtyEdit->setText(QString::number(activeCartItemQtyVec[i]));


        QWidget *cartItemW = new QWidget;
        cartItemW->setObjectName("CartItemDetails");
        cartItemW->setLayout(new QVBoxLayout());
        cartItemW->layout()->setSpacing(1);
        cartItemW->layout()->setContentsMargins(0, 0, 0, 0);
        rowLayout->addWidget(cartItemW);


        QLabel *cartItemNameLabel = new QLabel(activeCartItemNameVec[i]);
        cartItemNameLabel->setObjectName("CartItemName");
        cartItemNameLabel->setStyleSheet("font-weight: bold; font-size: 14px");
        cartItemW->layout()->addWidget(cartItemNameLabel);


        QLabel *centsL = new QLabel("$ " + QString::number(activeCartItemCentsVec[i]));
        //        centsL->setStyleSheet("font-size: 12px; color: rgb(170, 170, 170); font-weight: bold");
        cartItemW->layout()->addWidget(centsL);


        QPushButton *dropBtn = new QPushButton;
        connect(dropBtn, &QPushButton::clicked, this, &NewOrderView::dropCartItem);
        dropBtn->setText("🗑");
        rowLayout->addWidget(dropBtn);


        cartDisplayWLayout->addWidget(cartItemRow);
        cartDisplayWLayout->setStretchFactor(cartItemRow, 1);
    }
    scrollCart->setWidget(cartDisplayWidget);

    emit signalUpdateCartTotal();
}

void NewOrderView::handleCartTotalChange(){
    totalLabel->setText(QString("$%L1").arg(runningTotal, 0, 'f', 2));
    orderDetValueVec[0]->setText(QString("$%L1").arg(runningTotal, 0, 'f', 2));
    orderDetValueVec[1]->setText("$00.00");
    orderDetValueVec[2]->setText( QString::number(tax * 100) + "%");
    orderDetValueVec[3]->setText(QString("$%L1").arg( runningTotal + (runningTotal * tax), 0, 'f', 2));
}

void NewOrderView::handleCartHeaderClick()
{
    QPushButton *nPush = qobject_cast<QPushButton*>(sender());

    QString name = nPush->text();
    if(name=="🛒 Items"){
        //        if(scrollCart->isHidden()){
        //            scrollCart->show();
        //            paymentWidget->hide();
        //        }
    }
    else if(name== "🧾 Payment"){
        //        scrollCart->hide();
        //        paymentWidget->show();
    }


}

void NewOrderView::handleQtyChanged()
{
    //    return;
    QLineEdit *qtyEdit = qobject_cast<QLineEdit*>(sender());
    QString qtyText = qtyEdit->text();
    QWidget *parent = qtyEdit->parentWidget();
    QWidget *child1 = parent->findChild<QWidget*>("CartItemDetails");
    QLabel *child2 = child1->findChild<QLabel*>("CartItemName");
    QString itemName = child2->text();

    for(int i=0; i<activeCartItemNameVec.size(); ++i){
        if(activeCartItemNameVec[i] == itemName){
            activeCartItemQtyVec[i] = qtyText.toInt();
        }
    }
    runningTotal = 0;
    for(int i=0; i<activeCartItemNameVec.size(); ++i){
        activeCartItemTotalVec[i] = activeCartItemQtyVec[i] * activeCartItemCentsVec[i];
        runningTotal += activeCartItemTotalVec[i];
    }
    emit signalUpdateCartTotal();

}


//Payment Functions///////////////////////////////////////////////////
//Card Functions////

void NewOrderView::showCardPayment(QVector<QString> cardDetVec)
{
    if(cardDetVec.size() == 0){

        cardNumEdit->setText("371449635398431");
        cardExpEdit->setText("05/2024");
        cardCvvEdit->setText("6969");
    }
    else {
        cardNumEdit->setText(cardDetVec[0]);
        cardExpEdit->setText(cardDetVec[1]);
        cardCvvEdit->setText(cardDetVec[2]);
    }
    cardPmtWidget->show();
    cardNumEdit->setFocus();
}


void  NewOrderView::handleCardEdit()
{
    QString cardInfo = cardNumEdit->text();
    //DISPLAY COMPANY LOGOS & ADD CARD TYPE
    if(cardInfo.contains(QRegularExpression("^(?:2131|1800|35)[0-9]{0,}$"))){
        QPixmap pix(":/creditcardlogos/jcblogo.png");
        setAspect(pix, cardLogoLabel);
        cardType = "JCB";
    }
    else if(cardInfo.contains(QRegularExpression("^3[47][0-9]{0,}$"))){
        QPixmap pix(":/creditcardlogos/amexlogo.png");
        setAspect(pix, cardLogoLabel);
        cardType = "AMEX";
    }
    else if(cardInfo.contains(QRegularExpression("^3(?:0[0-59]{1}|[689])[0-9]{0,}$"))){
        QPixmap pix(":/creditcardlogos/dinersclublogo.png");
        setAspect(pix, cardLogoLabel);
        cardType = "Diner's Club";
    }

    else if(cardInfo.contains(QRegularExpression("^4[0-9]{0,}$"))){
        QPixmap pix(":/creditcardlogos/visalogo.png");
        setAspect(pix, cardLogoLabel);
        cardType = "VISA";
    }

    else if(cardInfo.contains(QRegularExpression("^(5[1-5]|222[1-9]|22[3-9]|2[3-6]|27[01]|2720)[0-9]{0,}$"))){
        QPixmap pix(":/creditcardlogos/mastercardlogo.png");
        setAspect(pix, cardLogoLabel);
        cardType = "MasterCard";
    }

    else if(cardInfo.contains(QRegularExpression("^(5[06789]|6)[0-9]{0,}$"))){

        if (cardInfo[0] == '5') {
            QPixmap pix(":/creditcardlogos/mastercardlogo.png");
            setAspect(pix, cardLogoLabel);
            cardType = "MasterCard";
        } else {
            QPixmap pix(":/creditcardlogos/maestrologo.png");
            setAspect(pix, cardLogoLabel);
            cardType = "Maestro";
        }
    }

    else if(cardInfo.contains(QRegularExpression("^(6011|65|64[4-9]|62212[6-9]|6221[3-9]|622[2-8]|6229[01]|62292[0-5])[0-9]{0,}$"))){
        QPixmap pix(":/creditcardlogos/discoverlogo.png");
        setAspect(pix, cardLogoLabel);
    }
    else {
        setAspect(QPixmap(), cardLogoLabel);
    }
    //LUHN  FORMULA VAILDATION

}

void NewOrderView::showNumpad()
{
    if(!numPadMinimalCardDets->isVisible()){
        numPadMinimalCardDets->show();
    }


}

void NewOrderView::hideNumpad()
{
    if(numPadMinimalCardDets->isVisible()) numPadMinimalCardDets->hide();
    else numPadMinimalCardDets->show();
}


void NewOrderView::handleSubmitCard()
{
    //CARD TEST NUMBERS//////////////////////////////////
    //    American Express

    //        378282246310005

    //        American Express

    //        371449635398431

    //        American Express Corporate

    //        378734493671000


    //        Diners Club

    //        30569309025904

    //        Diners Club

    //        38520000023237

    //        Discover

    //        6011111111111117

    //        Discover

    //        6011000990139424

    //        JCB

    //        3530111333300000

    //        JCB

    //        3566002020360505

    //        MasterCard

    //        5555555555554444

    //        MasterCard

    //        5105105105105100

    //        Visa

    //        4111111111111111

    //        Visa

    //        4012888888881881

    //        Visa

    //        4222222222222

    const QString cardNum = cardNumEdit->text();

    bool changingCardInfo = false;
    int changingCardInfoIdx;
    for(int i=0; i<activeCardVec.size(); ++i){
        if(activeCardVec[i][1] == cardNum){
            changingCardInfo = true;
            changingCardInfoIdx = i;
            break;
        }
    }

    if (cardNum.size() < 7)
    {
        QMessageBox ::warning(0, "Card Number Error", "Card must have at least 7 digits");
        return;
    }
    if(!luhnValidateCredit (cardNum)){
        QMessageBox ::warning(0, "Card Number Error", "Invalid Card Number");
        return;
    }


    const QString cardExp = cardExpEdit->text();
    if (cardExp.mid(3, 4).toInt() < QDate::currentDate().year())
    {
        QMessageBox ::warning(0, "Expiration Error", "Card Expired");
        return;
    }
    const QString cardCvv = cardCvvEdit->text();
    int cvvSize = cardCvv.size();
    if(cvvSize == 3){
        if(cardType == "AMEX"){
            QMessageBox ::warning(0, "CVV Error", "Invalid CVV");
            return;
        }
    }
    if(cvvSize != 3){
        if(cardType != "AMEX"){
            QMessageBox ::warning(0, "CVV Error", "Invalid CVV");
            return;
        }
    }
    const QVector<QString> cardVec = {cardType, cardNum, cardExp, cardCvv};

    if(changingCardInfo){
        activeCardVec[changingCardInfoIdx][0] = cardType;
        activeCardVec[changingCardInfoIdx][1] = cardNum;
        activeCardVec[changingCardInfoIdx][2] = cardExp;
        activeCardVec[changingCardInfoIdx][3] = cardCvv;
    }
    else activeCardVec.append({cardType, cardNum, cardExp, cardCvv});

    addCardToOrder();
}

void NewOrderView::handleCardExpMask()
{
    cardExpEditStack->setCurrentWidget(cardExpEdit);
}

void NewOrderView::catchExpCard()
{
    QString text = cardExpEdit->text();
    if(text.size()== 7){
        QDate cardDate = QDate::fromString(text,"MM/yyyy");
        if(cardDate <= QDate::currentDate()){
            expCardStyleBool = true;
            cardExpEdit->setStyleSheet("background-color: rgba(239, 83, 80, 0.8)");
        }
    }
    else{
        if(expCardStyleBool){
            cardExpEdit->setStyleSheet("");
        }
    }
}

void NewOrderView::addCardToOrder()
{
    //    cardPmtWidget->hide();
    cardNumEdit->setText("");
    cardExpEdit->setText("");
    cardCvvEdit->setText("");

    for(int i=0; i<cardDisplayWVec.size(); ++i){
        cardDisplayWVec[i]->deleteLater();
    }
    cardDisplayWVec.clear();

    for(int i=0; i<activeCardVec.size(); ++i){
        QWidget *rowW = new QWidget;
        rowW->setStyleSheet("max-height: 45px");
        QHBoxLayout *rowWLayout = new QHBoxLayout();
        rowWLayout->setSpacing(30);
        rowW->setLayout(rowWLayout);

        QPushButton *dropCardBtn = new QPushButton;
        connect(dropCardBtn, &QPushButton::clicked, this, &NewOrderView::dropCard);
        dropCardBtn->setStyleSheet("padding: 0px; max-width: 50px; min-height:  30px; font-size: 12px;");
        dropCardBtn->setText("🗑");
        rowWLayout->addWidget(dropCardBtn);

        QLabel *typeL = new QLabel(activeCardVec[i][0]);
        typeL->setStyleSheet("min-width: 40px");
        rowWLayout->addWidget(typeL);

        QPushButton *numL = new QPushButton();
        connect(numL, &QPushButton::clicked, this, &NewOrderView::editCard);
        numL->setText("**** " + activeCardVec[i][1].right(4));
        numL->setObjectName("CardNumberInVec");
        numL->setStyleSheet("color: black; font-size: 10px; font-weight: bold; max-width: 70px; min-width: 70px; min-height:  30px");
        rowWLayout->addWidget(numL);

        QLabel *expL = new QLabel(activeCardVec[i][2]);
        expL->setStyleSheet("min-width: 40px");
        rowWLayout->addWidget(expL);

        cardDisplayWVec.append(rowW);
        cardVecDisplayW->layout()->addWidget(rowW);
    }
    cardVecDisplayW->show();

}

void NewOrderView::dropCard()
{
    QPushButton *nPush = qobject_cast<QPushButton*>(sender());
    QWidget *par = nPush->parentWidget();
    QString cardNum = par->findChild<QPushButton*>("CardNumberInVec")->text().right(4);
    int indexDrop;
    bool dropBool = false;
    for(int i=0; i<activeCardVec.size(); ++i){
        if(activeCardVec[i][1].right(4) == cardNum){
            indexDrop = i;
            dropBool = true;
            break;
        }
    }
    if(dropBool){
        activeCardVec.removeAt(indexDrop);
        addCardToOrder();
    }
}

void NewOrderView::editCard()
{
    QPushButton *nPush = qobject_cast<QPushButton*>(sender());
    QWidget *par = nPush->parentWidget();
    QString cardNum = par->findChild<QPushButton*>("CardNumberInVec")->text().right(4);
    int indexEdit;
    bool editBool = false;

    for(int i=0; i<activeCardVec.size(); ++i){
        if(activeCardVec[i][1].right(4) == cardNum){
            indexEdit = i;
            editBool = true;
            break;
        }
    }
    if(editBool){
        //        activeCardVec.removeAt(indexDrop);
        //        addCardToOrder();
        showCardPayment({activeCardVec[indexEdit][1], activeCardVec[indexEdit][2], activeCardVec[indexEdit][3]});
    }
}

void NewOrderView::cardPaymentClicked()
{
    //show card adder widget
    if(cardPmtWidget->isVisible()){
        cardPmtWidget->hide();
        QPushButton *nPush = qobject_cast<QPushButton*>(sender());
        orderHideBtn->click();
        orderHideBtn->setChecked(true);
        //        numPadMinimalCardDets->hide();
    }
    else{
        cardPmtWidget->show();
        showCardPayment({});
    }
    if(customerInfoWidget->isVisible()){
        customerInfoWidget->hide();
    }
}

void NewOrderView::cashPaymentClicked()
{
    //show card adder widget
    if(cardPmtWidget->isVisible()){
        cardPmtWidget->hide();
        orderHideBtn->click();
        orderHideBtn->setChecked(true);
    }
    //    if(customerInfoWidget->isVisible()) customerInfoWidget->hide();

    //    cashPmtWidget->show();

}

void NewOrderView::customerClicked()
{
    if(customerInfoWidget->isVisible()){
        customerInfoWidget->hide();
        orderHideBtn->setChecked(true);
        orderHideBtn->click();
    }
    else {
        customerInfoWidget->show();
        for(int i=0; i<customerEditVec.size(); ++i){
            if(customerEditVec[i]->objectName() == custEditObjectNamePre + "Phone") customerEditVec[i]->setFocus();
        }
    }
    //show card adder widget
    if(cardPmtWidget->isVisible()) cardPmtWidget->hide();
    //    if(customerInfoWidget->isVisible()) customerInfoWidget->hide();

}

//Cash Functions////


//Customer Functions
void NewOrderView::handleSubmitCustomer(){
    bool banned = false;
    QPushButton *nPush = qobject_cast<QPushButton*>(sender());
    if(nPush->text() == "Clear"){
        for(int i=0; i<customerEditVec.size(); ++i){
            customerEditVec[i]->setText("");
        }
        phoneModel->select();
        return;
    }
    //    if(nPush->text() == "Submit"){}

    //or use sorting algo/////////////////////
    QString phone = "";
    QString first = "";
    QString last = "";
    QString address = "";
    QString city = "";
    QString state = "";
    QString zip = "";
    QString notes = custNotesEdit->toPlainText();

    for(int i=0; i<customerEditVec.size(); ++i){
        if(customerEditVec[i]->objectName() == custEditObjectNamePre + "Phone") phone = customerEditVec[i]->text();
        else if(customerEditVec[i]->objectName() == custEditObjectNamePre + "First") first = customerEditVec[i]->text();
        else if(customerEditVec[i]->objectName() == custEditObjectNamePre + "Last") last = customerEditVec[i]->text();
        else if(customerEditVec[i]->objectName() == custEditObjectNamePre + "Address") address = customerEditVec[i]->text();
        else if(customerEditVec[i]->objectName() == custEditObjectNamePre + "City") city = customerEditVec[i]->text();
        else if(customerEditVec[i]->objectName() == custEditObjectNamePre + "State") state = customerEditVec[i]->text();
        else if(customerEditVec[i]->objectName() == custEditObjectNamePre + "Zip") zip = customerEditVec[i]->text();
    }

    QVector<QString> editStrings;
    editStrings.append(phone);
    editStrings.append(first);
    editStrings.append(last);
    editStrings.append(address);
    editStrings.append(city);
    editStrings.append(state);
    editStrings.append(zip);
    editStrings.append(notes);
    bool newCustomer = true;


    QVector<QString> existingCustInfo;
    if(phone.size() < 10){
        QMessageBox::warning(0, "Phone Error", "Phone number must be at least 10 digits");
        return;
    }

    QSqlQuery qSearch;
    qSearch.prepare("SELECT phone, name_first, name_last, address, city, state, zip, notes, banned FROM pos_customer WHERE phone = :phone");
    qSearch.bindValue(":phone", phone);
    if(!qSearch.exec()){
        QMessageBox::warning(0, "SQL Error", "Phone search failed: " + qSearch.lastError().text());
    }
    else{
        if(qSearch.isSelect()){
            int count = 0;
            while(qSearch.next()){
                if(qSearch.value(0).toString() != ""){
                    newCustomer = false;
                }
                for(int i=0; i<qSearch.record().count(); ++i){
                    existingCustInfo.append(qSearch.value(i).toString());
                    //                    QString fieldName = qSearch.record().fieldName(i);
                    //                  if(fieldName == "banned") banned = ;

                }
                ++count;
            }
        }
    }
    if(newCustomer){
        QSqlQuery qIns;
        // Not using ON CONFLICT here because we dont want to replace existing info with null values from line edit////////////////////////////////
        qIns.prepare("INSERT INTO pos_customer VALUES(:phone, :name_first, :name_last, :address, :city, :state, :zip, :notes)");
        qIns.bindValue(":phone", phone);
        qIns.bindValue(":name_first", first);
        qIns.bindValue(":name_last", last);
        qIns.bindValue(":address", address);
        qIns.bindValue(":city", city);
        qIns.bindValue(":state", state);
        qIns.bindValue(":zip", zip);
        qIns.bindValue(":notes", notes);
        if(!qIns.exec()){
            QMessageBox::warning(0, "SQL Error", "Adding new customer to order failed: " + qIns.lastError().text() + "    " + qIns.lastQuery() );
        }
    }
    else{
        QVector<QString> pushCustInfo;
        for(int i=0; i<editStrings.size(); ++i){
            if(existingCustInfo[i] == "" && editStrings[i] != ""){
                pushCustInfo.append(editStrings[i]);
            }
            else if(existingCustInfo[i] != "" && editStrings[i] != ""){
                pushCustInfo.append(editStrings[i]);
            }
            else{
                pushCustInfo.append(existingCustInfo[i]);
            }
        }

        QSqlQuery qUpdt;
        qUpdt.prepare("UPDATE pos_customer SET name_first = :name_first, name_last = :name_last, address =  :address, city =  :city, state =  :state, zip =  :zip, notes = :notes WHERE phone = :phone");
        qUpdt.bindValue(":phone", phone);
        qUpdt.bindValue(":name_first", pushCustInfo[1]);
        qUpdt.bindValue(":name_last", pushCustInfo[2]);
        qUpdt.bindValue(":address", pushCustInfo[3]);
        qUpdt.bindValue(":city", pushCustInfo[4]);
        qUpdt.bindValue(":state", pushCustInfo[5]);
        qUpdt.bindValue(":zip", pushCustInfo[6]);
        qUpdt.bindValue(":notes", pushCustInfo[7]);
        if(!qUpdt.exec()){
            QMessageBox::warning(0, "SQL Error", "Updating existing customer on order failed: " + qUpdt.lastError().text() );
        }
    }
    if (!newCustomer)
    {
        if(existingCustInfo[existingCustInfo.size() - 1].toInt() == 0){
            bannedIndLabel->setStyleSheet("color: rgba(7, 251, 84, .6)");
            bannedIndLabel->setText("🗸");
        }
        else {
            bannedIndLabel->setStyleSheet("color: rgba(239, 83, 80, 0.6)");
            bannedIndLabel->setText("🗙");
        }
    }

    phoneModel->select();
    emit signalCustomerChanged();
}

void NewOrderView::handleExistingPhoneFill(const QString phone)
{
    QVector<QString> custInfoVec;
    QSqlQuery qSearch;
    qSearch.prepare("SELECT name_first, name_last, address, city, state, zip, notes FROM pos_customer WHERE phone = :phone");
    qSearch.bindValue(":phone", phone);
    if(!qSearch.exec()){
        QMessageBox::warning(0, "SQL Error", "Auto fill customer failed: " + qSearch.lastError().text());
    }
    else {
        if(qSearch.isSelect()){
            while(qSearch.next()){
                for(int i=0; i< qSearch.record().count(); ++i){
                    custInfoVec.append(qSearch.value(i).toString());
                }
            }
        }
    }
    for(int i=0; i<customerEditVec.size(); ++i){
        if(customerEditVec[i]->objectName() == custEditObjectNamePre + "First")         customerEditVec[i]           ->setText(custInfoVec[0]);
        if(customerEditVec[i]->objectName() == custEditObjectNamePre + "Last")          customerEditVec[i]           ->setText(custInfoVec[1]);
        if(customerEditVec[i]->objectName() == custEditObjectNamePre + "Address")    customerEditVec[i]           ->setText(custInfoVec[2]);
        if(customerEditVec[i]->objectName() == custEditObjectNamePre + "City")          customerEditVec[i]           ->setText(custInfoVec[3]);
        if(customerEditVec[i]->objectName() == custEditObjectNamePre + "State")        customerEditVec[i]           ->setText(custInfoVec[4]);
        if(customerEditVec[i]->objectName() == custEditObjectNamePre + "Zip")           customerEditVec[i]           ->setText(custInfoVec[5]);
    }
    custNotesEdit->setText(custInfoVec[6]);

}




void NewOrderView::showFullOrderDetails()
{
    hideNumpad();
    fullOrderDetailsW->show();
}



