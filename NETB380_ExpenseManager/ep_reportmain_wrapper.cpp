/*
Purpose of this class is to be intermediate layer between the DBMS and GUI.
Here we will:
-> Gather data from DBMS.
-> Process it and provide it into suitable shape/format for the GUI.
-> This class will be handled as a separate thread into the main.
*/
#include <QSettings>
#include <QThread>
#include <QMessageBox>
#include "ep_db_wrapper.h"
#include "ep_reportmain_wrapper.h"

EP_ReportMain::EP_ReportMain(QObject *parent) : QObject(parent)
{
    /*Default constructor.*/
    connect(this,SIGNAL(EP_ReportMain_OpenDB(int)),this,SLOT(EP_ReportMain_OpenDBConnection(int)));
}

void EP_ReportMain::EP_ReportMain_ConnectToEventDispacther()
{
    /*Connection between Event Dispatcher and report main.*/
    /*LogIn Window requests.*/
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_LogWinLogInRequest()), this, SLOT(EP_ReportMain_GetUserLogInStatus()));
    /*Registration Window requests.*/
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RegWinRegistrationRequest()), this, SLOT(EP_ReportMain_GetUserDataRegisterStatus()));
    /*DB_Settings requests.*/
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_DBWinRequestDBConnection()), this, SLOT(EP_ReportMain_DBWin_RequestDbConnection()));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_DBWinRequestDeployTable()), this, SLOT(EP_ReportMain_DeployTableInCurrentDB()));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_DBWinRequestDropTable()), this, SLOT(EP_ReportMain_DropTableInCurrentDB()));
}

/* Function to DB.*/
void EP_ReportMain::EP_ReportMain_GetUserDataRegisterStatus()
{
    /*Check if DB is already opened if not request DB connection.*/
    if(false == this->sql->isDBOpen())
    {
        emit this->EP_ReportMain_OpenDB(0);
    }
    /*Purpose of this function is to get the registration status from DB*/
    int RegistrationStatus = 0;
    /*All data is written to UserData, request from DB status of the registration.*/
    RegistrationStatus = this->sql->registerUser(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_RegUserName(),
                            this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_RegUserPassword(),
                            this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_RegUserEmail());
    /*After registration request status is recieved send it to the EP_EventDispatcher */
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMRegistrationStatus(RegistrationStatus);
}

void EP_ReportMain::EP_ReportMain_GetUserLogInStatus()
{
    /*Check if DB is already opened if not request DB connection.*/
    if(false == this->EP_ReportMain_GetDBPointer()->isDBOpen())
    {
        emit this->EP_ReportMain_OpenDB(0);
    }
    /*Login status*/
    int LoginStatus = 0;
    LoginStatus = this->sql->loginUser(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_LogUserName(),
                                       this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_LogUserPassword());
    /*Send the login-status to Event-Dispatcher*/
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMLoginStatus(LoginStatus);
}

void EP_ReportMain::EP_ReportMain_DBWin_RequestDbConnection()
{
    /*Request to Open DB.*/
    emit this->EP_ReportMain_OpenDB(1);
}

void EP_ReportMain::EP_ReportMain_DeployTableInCurrentDB()
{
    /*Request tables to be added to current DB.*/
    this->EP_ReportMain_GetDBPointer()->deployTables();
}

void EP_ReportMain::EP_ReportMain_DropTableInCurrentDB()
{
    /*Request tables to be deleted into current DB.*/
    this->EP_ReportMain_GetDBPointer()->dropTables();
}

/*Connection to the database to be established here.*/
void EP_ReportMain::EP_ReportMain_OpenDBConnection(int idOfRequest)
{
    // Request settings for opening DB connection.
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Netb380", "EPManager");
    QString DB_HOST = settings.value("DB_HOST", "").toString();
    QString DB_USER = settings.value("DB_USER", "").toString();
    QString DB_PASS = settings.value("DB_PASS", "").toString();
    QString DB_NAME = settings.value("DB_NAME", "").toString();

    // TODO: Check if DB settings have connected to the DB and recheck
    if (DB_HOST  == "" || DB_NAME == "" || DB_USER == "" || DB_PASS == "")
    {
        qDebug() << "You are missing DB settings :D";
    }
    else
    {
        EP_DB_Wrapper *sql = new EP_DB_Wrapper();
        this->EP_ReportMain_SetDBPointer(sql);
        this->EP_ReportMain_GetDBPointer()->openDB(DB_HOST, DB_USER, DB_PASS, DB_NAME);
        /*Display connection status to DB only when DB_Settings requested db connection. */
        if((true == this->EP_ReportMain_GetDBPointer()->isDBOpen()) && (idOfRequest == 1))
        {
            emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMDBConectionSuccessfull();
        }
    }
}

/*Setters*/
void EP_ReportMain::EP_ReportMain_SetDBPointer(EP_DB_Wrapper *pointToDB)
{
    this->sql = pointToDB;
}

/*Getters*/
EP_DB_Wrapper* EP_ReportMain::EP_ReportMain_GetDBPointer()
{
    return this->sql;
}
