QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backbone.cpp \
    customer.cpp \
    customermanagerview.cpp \
    dbmanager.cpp \
    item.cpp \
    itemaddview.cpp \
    main.cpp \
    mainwindow.cpp \
    message.cpp \
    pos.cpp \
    register.cpp \
    simplecrypt.cpp \
    transaction.cpp
#    workorder.cpp

HEADERS += \
    customer.h \
    customermanagerview.h \
    dbmanager.h \
    item.h \
    itemaddview.h \
    mainwindow.h \
    backbone.h \
    message.h \
    passkey.h \
    pos.h \
    register.h \
    simplecrypt.h \
    transaction.h \
    workorder.h \
    module.h

FORMS += \
    mainwindow.ui

OTHER_FILES += recreate_tables.txt

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter

RESOURCES += \
    resources.qrc

DISTFILES += \
    modules.config
