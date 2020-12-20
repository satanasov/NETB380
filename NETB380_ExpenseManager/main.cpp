#include "ep_main.h"
#include "ep_reportmain_wrapper.h"
#include "ep_userdata.h"
#include "ep_eventdispatcher.h"
#include <QThread>
#include <QApplication>

int main(int argc, char *argv[])
{
    /*Standar QApplication QT object creation.*/
    QApplication a(argc, argv);

    /*Create placeholder object -> EP_UserData.*/
    EP_UserData UserData;

    /*Create communcation between GUI and EP_ReportMain.*/
    EP_EventDispatcher ED;

    /*Create main object -> GUI.*/
    EP_Main w;
    w.EP_Main_SetUserDataPointer(&UserData);
    w.EP_Main_SetEventDispatcherPointer(&ED);
    w.EP_Main_ConnectSlots_EventDispatcher();

    /*Create thread object to pass to DBMS_Wrapper.*/
    QThread ReportMain_Thread;
    /*Create DMBS_Wrapper object to pass the thread from main.*/
    EP_ReportMain Report_Main;
    /*Assign user data object and event dispatcher.*/
    Report_Main.EP_ReportMain_SetUserDataPointer(&UserData);
    Report_Main.EP_ReportMain_SetEventDispatcherPointer(&ED);
    Report_Main.EP_ReportMain_ConnectToEventDispacther();
    /*Connect DBMS Wrapper thread job to the main thread*/
    Report_Main.EP_ReportMain_SetupThread(ReportMain_Thread);
    /*Part of QObject class, take DBMS_Wrapper object and move it to the assigned thread.*/
    Report_Main.moveToThread(&ReportMain_Thread);
    /*Initiate main thread*/
    ReportMain_Thread.start();

    /*Show GUI.*/
    w.show();

    return a.exec();
}
