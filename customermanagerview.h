#ifndef CUSTOMERMANAGERVIEW_H
#define CUSTOMERMANAGERVIEW_H

#include <QtWidgets>
#include <QtSql>
#include <vector>
using std::vector;

class CustomerManagerView : public QWidget
{
    Q_OBJECT
public:
    CustomerManagerView(QWidget* parent = nullptr);

private:
    QVBoxLayout* mainLayout;

    QString custFieldNames[4] = {"Phone", "Name", "Address", "ZIP"};

    QLineEdit* lineEdits [4];
    QLabel* custInfoLabels[4];

    QTableView* tableView;
    QSqlTableModel* tableModel;

    void submitNew();
    void editExisting();
    void clearScreen();

    void selectCustomer();
    void cancel();

    void highlightCustomer();
};

#endif // CUSTOMERMANAGERVIEW_H
