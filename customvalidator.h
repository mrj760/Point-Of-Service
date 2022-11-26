#ifndef CUSTOMVALIDATOR_H
#define CUSTOMVALIDATOR_H

#include <QObject>
#include <QRegularExpressionValidator>

class CustomValidator: public QRegularExpressionValidator {
    Q_OBJECT

public:
    explicit CustomValidator(QString, QObject* parent=nullptr);

protected:
    virtual QRegularExpressionValidator::State validate(QString& input, int&) const override;
};

#endif // CUSTOMVALIDATOR_H
