#ifndef NEWORDERVIEW_H
#define NEWORDERVIEW_H

#include <QtWidgets>
#include <QtSql>
#include <numpadwidget.h>
#include <qlineeditselect.h>
#include <qlineeditfocus.h>

class NewOrderView : public QWidget
{
    Q_OBJECT
public:
    explicit NewOrderView(QWidget *parent = nullptr);

public slots:
    void loadItems();

    void loadCategories();

private:
//    NumberPad *numPad;
    QVBoxLayout* mLayout;
    QWidget* itemCategoryButtonGrid;
    QWidget *itemView;
    QVBoxLayout* itemCategoryLayout;

    QWidget *paymentWidget;
    QVBoxLayout *paymentWLayout;

    QWidget *innerViewWidget;
    QHBoxLayout *innerViewWLayout;

    QWidget *transactionHolderWidget;
    QVBoxLayout *transHolderWLayout;

    QVector<QWidget*> itemWidgetVec;
    QVector<QWidget*> categoryWidgetVec;

    QVector<QString> itemNameVec;
    QVector<int> itemCentsVec;
    QVector<int> itemQtyVec;
    QVector<QString> itemCategoryVec;

    void handleQtyChanged();
    void handleCartTotalChange();
    QWidget *rowW;

    //Order info
    QScrollArea* scrollCart ;
    QVector<QWidget*> oldcartWVec;

    QStackedWidget *infoEditStack;


    //data
    QLabel *totalLabel;
    QVector<QString> activeCartItemNameVec;
    QVector<int>activeCartItemQtyVec;
    QVector<double>activeCartItemTotalVec;
    QVector<double>activeCartItemCentsVec;

    QVector<QWidget*> cartItemWidgetVec;


    void dropCartItem();
    void handleItemClicked();
    void handleUpdateCartView();

    void handleCartHeaderClick();

    double runningTotal = 0;

    //Payment Buttons
    QButtonGroup *orderBtnGroup;
    QPushButton *orderHideBtn;
    void showFullOrderDetails();
    //Payment
    void cardPaymentClicked();

    //Card Payment//////////////
    QWidget *cardPmtWidget;
    void handleCardEdit();

    //Card Edit//
    QVector<QLineEditFocus*> lineEditNumpadVec;
    void showNumpad();
    void hideNumpad();

    void handleSubmitCard();
    QLineEditFocus *cardNumEdit;

    QStackedWidget *cardExpEditStack;
    QPushButton *cardExpEditBtn;
    QLineEditFocus *cardExpEdit;
    bool expCardStyleBool = false;
    void catchExpCard();
    void handleCardExpMask();

    QLineEditFocus *cardCvvEdit;

    QVector<QVector<QString>> activeCardVec = {};
    QString cardType = "";
    void addCardToOrder();
    void dropCard();
    void editCard();
    void showCardPayment(QVector<QString> cardDetVec);
    //card Fuckery
    NumpadWidget *numPadMinimalCardDets;
    NumpadWidget *numPadMinimalQty;

    QWidget *cardVecDisplayW;
    QVector<QWidget*> cardDisplayWVec;

    QLabel *cardLogoLabel;

    //Cash Payment///////////////////////////////
    void cashPaymentClicked();




    //Customer Info////////////////////////////////
    QVector<QString> custLabVec = {"Phone", "Name", "Address", "Zip"};
    QString custEditObjectNamePre = "CustomerEdit";
    QVector<QLineEdit*> customerEditVec;
    QSqlTableModel *phoneModel;
    QTextEdit *custNotesEdit;
    QLabel *bannedIndLabel;
    void customerClicked();
    QWidget *customerInfoWidget;
    QVector<QString> activeOrderCustomerInfo;

    void handleSubmitCustomer();

    void handleExistingPhoneFill(const QString);

    //FULL ORDER DETS
    QVector<QLabel*> orderDetValueVec;
    QWidget *fullOrderDetailsW;
    double tax = .085;
signals:
    //Cart//////
    void signalUpdateCartView();
    void signalUpdateCartTotal();


    //Customer////
    void signalCustomerChanged();
};

#endif // NEWORDERVIEW_H
