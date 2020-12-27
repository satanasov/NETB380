QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ep_baseclass_gui_reportmain.cpp \
    ep_db_settings.cpp \
    ep_db_wrapper.cpp \
    ep_eventdispatcher.cpp \
    ep_register.cpp \
    ep_reportmain_wrapper.cpp \
    ep_userdata.cpp \
    ep_welcome.cpp \
    main.cpp \
    ep_main.cpp

HEADERS += \
    ep_baseclass_gui_reportmain.h \
    ep_db_settings.h \
    ep_db_wrapper.h \
    ep_eventdispatcher.h \
    ep_main.h \
    ep_register.h \
    ep_reportmain_wrapper.h \
    ep_userdata.h \
    ep_welcome.h

FORMS += \
    ep_db_settings.ui \
    ep_main.ui \
    ep_register.ui \
    ep_welcome.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
