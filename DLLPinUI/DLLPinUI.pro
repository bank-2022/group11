#QT -= gui
QT += widgets

TEMPLATE = lib
DEFINES += DLLPINUI_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dllpinui.cpp \
    pincode.cpp \
    creditdebit.cpp

HEADERS += \
    DLLPinUI_global.h \
    dllpinui.h \
    pincode.h \
    creditdebit.h

FORMS += \
    pincode.ui \
    creditdebit.ui

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
