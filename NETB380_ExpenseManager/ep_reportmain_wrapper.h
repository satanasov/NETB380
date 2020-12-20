#ifndef EP_REPORTMAIN_WRAPPER_H
#define EP_REPORTMAIN_WRAPPER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QSettings>
#include "ep_db_wrapper.h"
#include "ep_userdata.h"
#include "ep_eventdispatcher.h"

class EP_ReportMain : public QObject
{
    Q_OBJECT

public:
    /*Constructor.*/
    explicit EP_ReportMain(QObject *parent = nullptr);
    /*Create connection between DBMS wrapper and the thread created in main.*/
    void EP_ReportMain_SetupThread(QThread &cThread);
    /*Create connection between Event Dispatcher and Report Main.*/
    void EP_ReportMain_ConnectToEventDispacther();
    /*Setters*/
    void EP_ReportMain_SetUserDataPointer(EP_UserData *UserDataPointer);
    void EP_ReportMain_SetEventDispatcherPointer(EP_EventDispatcher *EDPointer);
    /*Getters*/
    EP_UserData* EP_ReportMain_GetUserDataPointer();
    EP_EventDispatcher* EP_ReportMain_GetEDPointer();

private:
    EP_DB_Wrapper *sql = new EP_DB_Wrapper();
    /*User data pointer.*/
    EP_UserData *PointerToUserData = nullptr;
    /*Event dispatcher pointer.*/
    EP_EventDispatcher *PointerToEventDispacther = nullptr;

public slots:
    /*Create thread slot. (The job that will be executed)*/
    void EP_Report_Main();
    /*Main_UI_Slot*/
    void EP_ReportMain_GetUserLogInStatus();
    /*Register_UI_Slots*/
    void EP_ReportMain_GetUserDataRegisterStatus();

};

#endif // EP_REPORTMAIN_H
