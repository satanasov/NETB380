QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ep_register.cpp \
    ep_reportmain_wrapper.cpp \
    main.cpp \
    ep_main.cpp

HEADERS += \
    ep_main.h \
    ep_register.h \
    ep_reportmain_wrapper.h

FORMS += \
    ep_main.ui \
    ep_register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
