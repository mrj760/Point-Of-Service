QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customermanagerview.cpp \
    dbmanager.cpp \
    itemmanagerview.cpp \
    main.cpp \
    mainwindow.cpp \
    transactioneditview.cpp \
    transactionsviewer.cpp

HEADERS += \
    customermanagerview.h \
    dbmanager.h \
    displaymessage.h \
    itemmanagerview.h \
    mainwindow.h \
    template_customer.h \
    template_item.h \
    template_register.h \
    template_transaction.h \
    transactioneditview.h \
    transactionsviewer.h

FORMS += \
    mainwindow.ui

OTHER_FILES += recreate_tables.txt

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter

RESOURCES += \
    resources.qrc


DISTFILES += \
    ideas.txt \
    modules.config
