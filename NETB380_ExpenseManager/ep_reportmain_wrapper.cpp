/*
Purpose of this class is to be intermediate layer between the DBMS and GUI.
Here we will:
-> Gather data from DBMS.
-> Process it and provide it into suitable shape/format for the GUI.
-> This class will be handled as a separate thread into the main.
*/
#include <QSettings>
#include <QMutex>
#include "ep_db_wrapper.h"
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

void EP_ReportMain::EP_ReportMain_ConnectToEventDispacther()
{
    /*Connection between Event Dispatcher and report main.*/
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_LogInRequest()), this, SLOT(EP_ReportMain_GetUserLogInStatus()));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RegistrationRequest()), this, SLOT(EP_ReportMain_GetUserDataRegisterStatus()));
}

/* Function to DB.*/
void EP_ReportMain::EP_ReportMain_GetUserDataRegisterStatus()
{
    /*Lock user data with current values.*/
    QMutex mutex;
    /*Create input validation here for the Log-in screen. For. e.x.: Some limitations.*/
    mutex.lock();

    /*Purpose of this function is to get the registration status from DB*/
    int RegistrationStatus = 0;
    /*All data is written to UserData, request from DB status of the registration.*/
    RegistrationStatus = this->sql->registerUser(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_RegUserName(),
                            this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_RegUserPassword(),
                            this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_RegUserEmail());
    /*After registration request status is recieved send it to the EP_EventDispatcher */
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RegistrationStatus(RegistrationStatus);
    /*Unlock UserData object.*/
    mutex.unlock();
    /*Destroy mutex object.*/
    mutex.~QMutex();
}

void EP_ReportMain::EP_ReportMain_GetUserLogInStatus()
{
    /*Lock user data with current values.*/
    QMutex mutex;
    /*Create input validation here for the Log-in screen. For. e.x.: Some limitations.*/
    mutex.lock();
    /*Login status*/
    int LoginStatus = 0;
    LoginStatus = this->sql->loginUser(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_LogUserName(),
                                       this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_LogUserPassword());
    /*Send the login-status to Event-Dispatcher*/
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_LoginStatus(LoginStatus);
    mutex.unlock();
    /*Destroy mutex object.*/
    mutex.~QMutex();
}

/*Connection to the database to be established here.*/
void EP_ReportMain::EP_Report_Main()
{
    // Request settings
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Netb380", "EPManager");
    QString DB_HOST = settings.value("DB_HOST", "").toString();
    QString DB_USER = settings.value("DB_USER", "").toString();
    QString DB_PASS = settings.value("DB_PASS", "").toString();
    QString DB_NAME = settings.value("DB_NAME", "").toString();

    // TODO: Check if DB settings have connected to the DB and recheck
    if (DB_HOST == "" || DB_USER == "" || DB_PASS == "" || DB_NAME == "")
    {
        qDebug() << "You are missing DB settings :D";
    }
    else
    {
        EP_DB_Wrapper *sql = new EP_DB_Wrapper();
        sql->openDB(DB_HOST, DB_USER, DB_PASS, DB_NAME);
    }
}
