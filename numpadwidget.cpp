#include "numpadwidget.h"


NumpadWidget::NumpadWidget(QWidget *parent)
    : QWidget{parent}
{

        const QVector<QPair<QString, int>> values{{"1", Qt::Key_1}, {"2", Qt::Key_2}, {"3", Qt::Key_3},
                                                      {"4", Qt::Key_4}, {"5", Qt::Key_5}, {"6", Qt::Key_6},
                                                      {"7", Qt::Key_7}, {"8", Qt::Key_8}, {"9", Qt::Key_9},
                                                      {"0", Qt::Key_0}, {"Enter", Qt::Key_Enter}};

        this->setObjectName("Viewer");

//        this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
//        this->setWindowFlag(Qt::FramelessWindowHint);
        this->setStyleSheet(
            "#Viewer {background-color: rgb(41, 41, 41); min-width: 200px; min-height: 300px}"
            ""
            "QPushButton{ border: 1px solid rgb(21, 21, 21); background-color: rgb(31, 31, 31); color: rgb(180, 180, 180); font-weight: bold; font-size: 14px; "
            "max-width: 1000px; max-height: 1000px; min-width: 40px; min-height:40px }"
            "QPushButton:hover {background-color: rgb(51, 51, 51); color: white}"
            //        "#RowW {border: 1px solid red; padding: 0px}"
            ""
            "");
        QVBoxLayout *mLayout = new QVBoxLayout(this);
        mLayout->setSpacing(0);
        mLayout->setAlignment(Qt::AlignTop);
        this->setLayout(mLayout);

        QWidget *viewer = new QWidget;
        mLayout->addWidget(viewer);

        viewer->setLayout(new QHBoxLayout());
        viewer->layout()->setSpacing(0);
        viewer->layout()->setContentsMargins(0, 0, 0, 0);


        QWidget *leftNumsW = new QWidget;
        QVBoxLayout *leftNumsLayout = new QVBoxLayout;
        leftNumsLayout->setSpacing(0);
        leftNumsLayout->setContentsMargins(0, 0, 0, 0);
        leftNumsW->setLayout(leftNumsLayout);
        viewer->layout()->addWidget(leftNumsW);


        int count = 1;
        for(int i=0; i<4; ++i){
            QWidget *row = new QWidget;
//            row->setObjectName("RowW");
            leftNumsLayout->addWidget(row);

            row->setLayout(new QHBoxLayout());
            row->layout()->setSpacing(0);
            row->layout()->setContentsMargins(0,0, 0, 0);
            leftNumsLayout->setStretchFactor(row, 1);

            for(int k=0; k<3; ++k){
                QPushButton *btn = new QPushButton;
                btn->setFocusPolicy(Qt::FocusPolicy::NoFocus);
                btn->setProperty("text", values[i].first);
                btn->setProperty("key", values[i].second);
                connect(btn, &QToolButton::clicked, this, &NumpadWidget::onClicked);
                if(count == 10){
                    btn->setText("0");
                    row->layout()->addWidget(btn);

                    QPushButton *btnSlash = new QPushButton;
                    btnSlash->setFocusPolicy(Qt::FocusPolicy::NoFocus);
                    btnSlash->setProperty("text", "Enter");
                    btnSlash->setProperty("key", Qt::Key_Slash);
                    connect(btnSlash, &QToolButton::clicked, this, &NumpadWidget::onClicked);

                    btnSlash->setText("/");
                    row->layout()->addWidget(btnSlash);

                    QPushButton *btnEnter = new QPushButton;
                    btnEnter->setFocusPolicy(Qt::FocusPolicy::NoFocus);
                    btnEnter->setProperty("text", "Enter");
                    btnEnter->setProperty("key", Qt::Key_Enter);
                    connect(btnEnter, &QToolButton::clicked, this, &NumpadWidget::onClicked);
                    btnEnter->setStyleSheet("background-color: rgba(7, 251, 84, .6); color: white");
                    btnEnter->setText("Enter");
                    row->layout()->addWidget(btnEnter);
                    break;

                }
                btn->setText(QString::number(count));
                row->layout()->addWidget(btn);
                ++count;
            }
        }
//         setFixedSize(sizeHint());

        QWidget *row = new QWidget;
        row->setObjectName("RowW");
        leftNumsLayout->addWidget(row);

        row->setLayout(new QHBoxLayout());
        row->layout()->setSpacing(0);
        row->layout()->setContentsMargins(0,0, 0, 0);
        leftNumsLayout->setStretchFactor(row, 1);

        const QVector<QPair<QString, int>> altValues = {{"⌫", Qt::Key_Backspace}, {"←",Qt::Key_Left}, {"→", Qt::Key_Right }, {"↹", Qt::Key_Tab}};
        for(int i=0; i< 4; ++i){
            QPushButton *btn = new QPushButton;
            row->layout()->addWidget(btn);
            btn->setFocusPolicy(Qt::FocusPolicy::NoFocus);
            btn->setProperty("text", altValues[i].first);
            btn->setProperty("key", altValues[i].second);
            connect(btn, &QToolButton::clicked, this, &NumpadWidget::onClicked);
        }

//        QObjectList objs = this->children();
//        for(int i=0; i<objs.size(); ++i){
//            objs[i]->setObjectName("Child");
//        }
//        const QVector<QWidget*> widgets = this->findChildren<QWidget*>("Child");
//        for(int i=0; i<widgets.size(); ++i){
//            widgets[i]->setFocusPolicy(Qt::FocusPolicy::NoFocus);
//        }
}

void NumpadWidget::onClicked()
{

    if(QWidget *widget = QApplication::focusWidget()){
//        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(widget);
//        lineEdit->setCursorPosition(0);
        QString text = sender()->property("text").toString();
        int key = sender()->property("key").toInt();
        QKeyEvent * event = new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier, text);
        QCoreApplication::postEvent(widget, event);
    }
}
