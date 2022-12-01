#ifndef QLINEEDITFOCUS_H
#define QLINEEDITFOCUS_H

#include <QWidget>
#include <QLineEdit>
#include <QTimer>

class QLineEditFocus : public QLineEdit
{
    Q_OBJECT
public:
    explicit QLineEditFocus(QWidget *parent = nullptr);

    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

signals:
    void editFocused();
    void editUnFocused();
};

#endif // QLINEEDITFOCUS_H
