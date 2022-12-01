QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#    backbone.cpp \
#    customer.cpp \
    customermanagerview.cpp \
#    customvalidator.cpp \
    dbmanager.cpp \
#    item.cpp \
    itemmanagerview.cpp \
    main.cpp \
    mainwindow.cpp \
#    message.cpp \
#    pos.cpp \
#    register.cpp \
#    simplecrypt.cpp \
#    testmodule.cpp \
#    transaction.cpp \
    transactioneditview.cpp
#    workorder.cpp \

HEADERS += \
    customermanagerview.h \
#    customvalidator.h \
    dbmanager.h \
    displaymessage.h \
    itemmanagerview.h \
    mainwindow.h \
#    backbone.h \
#    message.h \
#    passkey.h \
#    pos.h \
#    simplecrypt.h \
#    testmodule.h \
    template_customer.h \
    template_item.h \
    template_register.h \
    template_transaction.h \
    transactioneditview.h
#    workorder.h \
#    module.h \

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
