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
#include <QDateTime>
#include <QList>
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
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_DBWinRequestDBConnection(int)), this, SIGNAL(EP_ReportMain_OpenDB(int)));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_DBWinRequestDeployTable()), this, SLOT(EP_ReportMain_DeployTableInCurrentDB()));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_DBWinRequestDropTable()), this, SLOT(EP_ReportMain_DropTableInCurrentDB()));
    /*Welcome screen requests.*/
    //connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_WlcWinRequestCurrentActiveUserBalanceAndName),this,SLOT(EP_ReportMain_GetCurrentUserAvalCurrency));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMWlcScreen_getReport()),this,SLOT(EP_ReportMain_ProcessReport()));
    /*Add exepense requests.*/
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_AEWinRequestAddingExpense(QString,QString,QString,QString,QDateTime)), this, SLOT(EP_ReportMain_AddExpense(QString,QString,QString,QString,QDateTime)));
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
    /*Post-process result. Negative results are error messages.*/
    if(LoginStatus >= 0)
    {
        /*Save active user ID.*/
        this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Set_ActiveUserId(LoginStatus);
        /*Request DB data for current active and save it in UserData object.*/
        this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Set_activeUserData(this->EP_ReportMain_GetDBPointer()->getUserAccounts(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_ActiveUserId()));
        LoginStatus = 0;
    }

    /*Send the login-status to Event-Dispatcher*/
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMLoginStatus(LoginStatus);
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

/*Add expense program.*/
void EP_ReportMain::EP_ReportMain_AddExpense(QString nameOfExpense, QString typeOfExpense, QString amountOfExpense, QString descriptionOfExpense, QDateTime date)
{
    /*Initialize local variables.*/
    int getCurrentExpenseGroupIdInTable = -1; // Default value.
    int addExpenseGroupStatus = -2;
    int addExpenseStatus = -2;
    QString emptyTable = "emptyTable";
    /*Get expense available expense groups.*/
    QList<QList<QString>> currentUserExpenseGroups = this->EP_ReportMain_GetDBPointer()->getExpenseGroups(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_ActiveUserId());
    /*Check if expense group is available, if not add the expense group.*/
    bool isExpenseGroupAval = false;
    bool isExpenseGroupsDBAval = false;
    /*Check if current DB query is empty.*/
    if(currentUserExpenseGroups.empty())
    {
        /*Empty query means that current user still has not added to the ep_expense_groups.*/
        isExpenseGroupAval = false;
    }
    else
    {
        /*Check if table is empty*/
        if (currentUserExpenseGroups.at(0).at(0) == emptyTable)
        {
            /*No availalbe entries in database, database empty..*/
            isExpenseGroupAval = false;
            /*It will be first ID in table.*/
            getCurrentExpenseGroupIdInTable = 1;
        }
        else
        {
            /*Expense groups is available.*/
            isExpenseGroupsDBAval = true;
            /*Locate id of this particular expense type.*/
            for(int i = 0; i < currentUserExpenseGroups.size();i++)
            {
                /*Type is available only if already added by current user.*/
                if((currentUserExpenseGroups.at(i).at(2) == typeOfExpense)
                        &&
                        /*Check if current user added the group.*/
                       (this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_ActiveUserId() == currentUserExpenseGroups.at(i).at(1).toInt()))
                {
                    /*ID tables are starting from .1.*/
                    getCurrentExpenseGroupIdInTable = currentUserExpenseGroups.at(i).at(0).toInt();
                    isExpenseGroupAval = true;
                    break;
                }
            }
        }
    }
    /*Add expense group if not available.*/
    if(isExpenseGroupAval == false)
    {
        /*Add expense group.*/
        addExpenseGroupStatus = this->EP_ReportMain_GetDBPointer()->addExpenseGroup(
                    this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_ActiveUserId(),
                    typeOfExpense,
                    "default"
                    );
          /*Clear container of QLists*/
          currentUserExpenseGroups.clear();
          /*Get data from DB for expense groups.*/
          currentUserExpenseGroups = this->EP_ReportMain_GetDBPointer()->getExpenseGroups(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_ActiveUserId());
          /*Get current expense id in table.*/
          getCurrentExpenseGroupIdInTable = currentUserExpenseGroups.last().at(0).toInt();
    }
    else
    {
        /*Expense group already part of DB.*/
        addExpenseGroupStatus = 0;
    }
    /*If group is present or successfully added.*/
    if(addExpenseGroupStatus == 0)
    {
        amountOfExpense.replace(",", ".");
        /*Set time format to UNIX*/
        date.setTimeSpec(Qt::UTC);
        /*Assign the value to int.*/
        int UTC_Time = date.toTime_t();
        /*Request adding expense to DB.*/
        addExpenseStatus = this->EP_ReportMain_GetDBPointer()->addExpense(
                    this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_ActiveUserId(), // User uid
                    this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserData().at(0).at(0).toInt(), // user id in ep_accounts table.
                    amountOfExpense.toDouble(),
                    nameOfExpense,
                    descriptionOfExpense,
                    getCurrentExpenseGroupIdInTable,
                    UTC_Time
                    );
    }
    else
    {
        /*For all other problems request reconnection to DB and closing the program.*/
        addExpenseStatus = -2;
    }
    /*Get added expense status and send to Add expense window.*/
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RM_AddExpenseStatus(addExpenseStatus);
}

/*Process expenses and provide to report.*/
void EP_ReportMain::EP_ReportMain_ProcessReport()
{
    /*Get All expenses.*/
   QList<QList<QString>> currentUserExpenses= this->EP_ReportMain_GetDBPointer()->getExpenses(
                this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_ActiveUserId(),
                this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserData().at(0).at(0).toInt(),
                0, // All groups.
                0, // Without filter for amounts
               "", // Empty ammount delta, this is necessary whem amount is presented.
               "", // Empty filter for sorting by expense name
               "", // Empty filter for sorting by description
                0, // Empty filter for sorting by expensegroups.
                0, // Empty filter for sorting by time -> Starting point.
                0, // Empty filter for sorting by time -> Ending point.
                0 // Emppty filter for adding limit to the requested expenses.
                );
   /*Emit signal to GUI to generate the window.*/
   emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_GenerateTodayReport(currentUserExpenses);
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
