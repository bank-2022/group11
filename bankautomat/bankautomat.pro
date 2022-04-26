QT       += core gui
QT       +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    donationwindow.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    transactionswindow.cpp \
    withdrawwindow.cpp

HEADERS += \
    donationwindow.h \
    mainmenu.h \
    mainwindow.h \
    transactionswindow.h \
    withdrawwindow.h

FORMS += \
    donationwindow.ui \
    mainmenu.ui \
    mainwindow.ui \
    transactionswindow.ui \
    withdrawwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -L$$PWD/../rest_api_dll/build/debug/ -lrest_api_dll

INCLUDEPATH += $$PWD/../rest_api_dll
DEPENDPATH += $$PWD/../rest_api_dll

unix:!macx: LIBS += -L$$PWD/../rest_api_dll/build/ -lrest_api_dll

INCLUDEPATH += $$PWD/../rest_api_dll
DEPENDPATH += $$PWD/../rest_api_dll
