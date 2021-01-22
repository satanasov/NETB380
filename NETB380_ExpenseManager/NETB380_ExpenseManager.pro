QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ep_add_expense.cpp \
    ep_add_money.cpp \
    ep_baseclass_gui_reportmain.cpp \
    ep_custom_menu.cpp \
    ep_db_settings.cpp \
    ep_db_wrapper.cpp \
    ep_eventdispatcher.cpp \
    ep_register.cpp \
    ep_reportmain_wrapper.cpp \
    ep_show_report.cpp \
    ep_userdata.cpp \
    ep_welcome.cpp \
    main.cpp \
    ep_main.cpp \
    ep_customlabel.cpp \
    ep_other.cpp

HEADERS += \
    EP_CustomTypes.h \
    ep_add_expense.h \
    ep_add_money.h \
    ep_baseclass_gui_reportmain.h \
    ep_custom_menu.h \
    ep_db_settings.h \
    ep_db_wrapper.h \
    ep_eventdispatcher.h \
    ep_main.h \
    ep_register.h \
    ep_reportmain_wrapper.h \
    ep_show_report.h \
    ep_userdata.h \
    ep_welcome.h \
    ep_customlabel.h \
    ep_other.h

FORMS += \
    ep_add_expense.ui \
    ep_add_money.ui \
    ep_db_settings.ui \
    ep_main.ui \
    ep_register.ui \
    ep_show_report.ui \
    ep_welcome.ui \
    ep_other.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    resources.qrc
