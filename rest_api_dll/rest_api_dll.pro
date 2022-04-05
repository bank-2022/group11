QT -= gui
QT += network

TEMPLATE = lib
DEFINES += REST_API_DLL_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    restapi.cpp \
    restapiengine.cpp

HEADERS += \
    rest_api_dll_global.h \
    restapi.h \
    restapiengine.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
