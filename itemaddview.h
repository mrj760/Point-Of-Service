#ifndef ITEMADDVIEW_H
#define ITEMADDVIEW_H

#include <QtWidgets>
#include <QtSql>

class ItemAddView : public QWidget
{
    Q_OBJECT
public:
    explicit ItemAddView(QWidget* parent = nullptr);
private:
    QVBoxLayout* mLayout;

    //inputs
    QLineEdit* itemQtyInput ;
    QLineEdit* itemNameInput;
    QLineEdit* itemPriceInput;

    //item table view
    QTableView* viewExistingItems;
    QSqlTableModel* itemModel;

    void handleViewItems();
    void handleSubmit();
signals:

};

#endif // ITEMADDVIEW_H
