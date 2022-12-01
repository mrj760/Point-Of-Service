#include "qlineeditfocus.h"

QLineEditFocus::QLineEditFocus(QWidget *parent): QLineEdit{parent}
{
}

void QLineEditFocus::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    emit editFocused();
}

void QLineEditFocus::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    emit editUnFocused();
}
