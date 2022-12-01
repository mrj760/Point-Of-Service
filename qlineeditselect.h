#ifndef QLINEEDITSELECT_H
#define QLINEEDITSELECT_H

#include <QWidget>
#include <QLineEdit>
#include <QTimer>

class QLineEditSelect : public QLineEdit
{
    Q_OBJECT
public:
    explicit QLineEditSelect(QWidget *parent = nullptr);

void focusInEvent(QFocusEvent *event) override;


signals:

};

#endif // QLINEEDITSELECT_H
