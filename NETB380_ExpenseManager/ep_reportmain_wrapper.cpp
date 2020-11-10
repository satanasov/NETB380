/*
Purpose of this class is to be intermediate layer between the DBMS and GUI.
Here we will:
-> Gather data from DBMS.
-> Process it and provide it into suitable shape/format for the GUI.
-> This class will be handled as a separate thread into the main.
*/
#include "ep_reportmain_wrapper.h"

EP_ReportMain::EP_ReportMain(QObject *parent) : QObject(parent)
{
    /*Default constructor.*/
}

void EP_ReportMain::EP_ReportMain_SetupThread(QThread &cThread)
{
    /*Make connection between main thread and the thread in Report main. We will be executing "EP_Report_Main"
    1) When this thread is emiting started signal then we will connect it to the slot/job EP_Dbms_Main.
    2) This will permit us to make the connection with the ReportMain->DBMS to be ran on separate thread.  */
    connect(&cThread,SIGNAL(started()),this,SLOT(EP_Report_Main()));
}

void EP_ReportMain::EP_GetUserDataRegister()
{
    qDebug() << "UserData slot created.";
}

/*Connection to the database to be established here.*/
void EP_ReportMain::EP_Report_Main()
{


}
