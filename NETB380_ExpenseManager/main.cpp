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
    w.EP_BaseClass_SetUserDataPointer(&UserData);
    w.EP_BaseClass_SetEventDispatcherPointer(&ED);
    w.EP_Main_ConnectSlots_EventDispatcher();

    /*Create ReportMain object. -> Connection between GUI and DB.*/
    EP_ReportMain Report_Main;
    /*Assign user data object and event dispatcher.*/
    Report_Main.EP_BaseClass_SetUserDataPointer(&UserData);
    Report_Main.EP_BaseClass_SetEventDispatcherPointer(&ED);
    Report_Main.EP_ReportMain_ConnectToEventDispacther();

    /*Show GUI.*/
    w.show();

    return a.exec();
}
