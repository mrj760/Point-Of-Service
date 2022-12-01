#ifndef NUMPADWIDGET_H
#define NUMPADWIDGET_H
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QToolButton>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalMapper>



class NumpadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NumpadWidget(QWidget *parent = nullptr);
private:
//    MyInputPanelForm form;
//    QWidget *lastFocusedWidget;
//    QSignalMapper signalMapper;
private slots:
    void onClicked();

//    void saveFocusWidget(QWidget *oldFocus, QWidget *newFocus);
//    void buttonClicked(QWidget *w);
protected:
//    bool event(QEvent *e);

signals:
//    void characterGenerated(QChar character);
};

#endif // NUMPADWIDGET_H
