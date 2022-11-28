#include "customvalidator.h"


CustomValidator::CustomValidator(QString s, QObject *parent): QRegularExpressionValidator{parent} {
    this->setRegularExpression(QRegularExpression(s));
}

QRegularExpressionValidator::State CustomValidator::validate(QString &input, int &) const
{
    input = input.toUpper();
    return QValidator::Acceptable;
};
