QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23

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
    transactionsviewer.cpp \
    POS/UI/ErrorNotification.cpp \
    POS/UI/ProductContainer.cpp \
    POS/UI/VirtualKeyPad.cpp \
    POS/UI/Window.cpp \
    POS/UI/Box/ATextBox.cpp \
    POS/UI/Button/AImageButton.cpp \
    POS/UI/Button/ATextButton.cpp \
    POS/UI/Button/CustomImage.cpp \
    POS/UI/Button/CustomText.cpp \
    POS/UI/Screen/Home.cpp \

HEADERS += \
    POS/UI/Button/ATextButton.hpp \
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
    transactionsviewer.h \
    POS/UI/ErrorNotification.hpp \
    POS/UI/ProductContainer.hpp \
    POS/UI/VirtualKeyPad.hpp \
    POS/UI/Window.hpp \
    POS/UI/Box/ATextBox.hpp \
    POS/UI/Button/AImageButton.hpp \
    POS/UI/Button/CustomImage.hpp \
    POS/UI/Button/CustomText.hpp \
    POS/UI/Screen/Home.hpp \

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
