#include "ep_main.h"
#include "ep_reportmain_wrapper.h"
#include <QThread>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*Create main object -> GUI.*/
    EP_Main w;
    /*Create thread object to pass to DBMS_Wrapper.*/
    QThread ReportMain_Thread;
    /*Create DMBS_Wrapper object to pass the thread from main.*/
    EP_ReportMain Report_Main;
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
