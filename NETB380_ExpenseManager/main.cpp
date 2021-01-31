#include "ep_main.h"
#include "ep_reportmain_wrapper.h"
#include "ep_userdata.h"
#include "ep_eventdispatcher.h"
#include <QThread>
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    /*Standar QApplication QT object creation.*/
    QApplication a(argc, argv);

    /*Create container object for GUI objects and ReportMain object. -> EP_UserData.*/
    EP_UserData UserData;

    /*Create communcation between GUI and EP_ReportMain.*/
    EP_EventDispatcher ED;

    /*Create first window object -> GUI.*/
    EP_Main MainWindow;
    MainWindow.EP_BaseClass_SetUserDataPointer(&UserData);
    MainWindow.EP_BaseClass_SetEventDispatcherPointer(&ED);
    MainWindow.EP_Main_ConnectSlots_EventDispatcher();

    /*Create ReportMain object. -> Connection between GUI and DB.*/
    EP_ReportMain GUIandDBAbstraction;
    /*Assign user data object and event dispatcher.*/
    GUIandDBAbstraction.EP_BaseClass_SetUserDataPointer(&UserData);
    GUIandDBAbstraction.EP_BaseClass_SetEventDispatcherPointer(&ED);
    GUIandDBAbstraction.EP_ReportMain_ConnectToEventDispacther();

    /*Show first window of GUI.*/
    MainWindow.show();

    return a.exec();
}
