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
#include <QTimeZone>
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
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMWlcScreen_getReport(EP_Report_Types,QList<QString>)),this,SLOT(EP_ReportMain_ProcessReport(EP_Report_Types,QList<QString>)));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_WlcScreenUpdateCurrentUserData()),this,SLOT(EP_ReportMain_Update_activeUserData()));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_AEWinRequestAddingExpense(QString,QString,QString,QString,QDateTime,int)),this,SLOT(EP_ReportMain_AddExpense(QString,QString,QString,QString,QDateTime,int)));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMWlcScreen_updateCurrentUserExpGroups(int)), this, SLOT(EP_ReportMain_Update_activeUserExpGroups(int)));
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

void EP_ReportMain::EP_ReportMain_Update_activeUserData()
{
    /*Update current user from data.*/
    this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Set_activeUserData(this->EP_ReportMain_GetDBPointer()->getUserAccounts(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_ActiveUserId()));
    /*Request welcome screen update.*/
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_UpdateCurrentUserAmount();
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
void EP_ReportMain::EP_ReportMain_AddExpense(QString nameOfExpense, QString typeOfExpense, QString amountOfExpense, QString descriptionOfExpense, QDateTime date, int ExpType)
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
                    UTC_Time,
                    ExpType
                    );
        // This is example of how edit works.
        //addExpenseStatus = this->EP_ReportMain_GetDBPointer()->updateExpense(1, 0, 0, 25.9, 0, "edit test");
    }
    else
    {
        /*For all other problems request reconnection to DB and closing the program.*/
        addExpenseStatus = -2;
    }
    /*If expense type is 1, then expense is added.*/
    if(1 == ExpType)
    {
        /*Get added expense status and send to Add expense window.*/
        emit this->EP_BaseClass_GetEDPointer()->EP_ED_RM_AddExpenseStatus(addExpenseStatus);
    }
    else if(0 == ExpType)
    {
        /*To do: emit signal to add_money.*/
        emit this->EP_BaseClass_GetEDPointer()->EP_ED_RM_AddMoneyStatus(addExpenseStatus);
    }
    else
    {
        // Can be deleted. For whatever reason.
    }

}

void EP_ReportMain::EP_ReportMain_Update_activeUserExpGroups(int TypeOfReq)
{
    QString defaulTypes[5] = {"Bank","Transport","Utility","Food","Clothes"};
    QString defaulTypesDesc[5] = {"Bank expenses.","Transport expenses.","Utility expenses.","Food expenses.","Clothes expenses."};
     /*Get current exp groups.*/
     QList<QList<QString>> currentUserExpenseGroups = this->EP_ReportMain_GetDBPointer()->getExpenseGroups(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_ActiveUserId());
     if(!(currentUserExpenseGroups.empty()))
     {
         /*Check if table is empty*/
         if (currentUserExpenseGroups.at(0).at(0) == "emptyTable")
         {
             currentUserExpenseGroups.clear();
             // Brand new user no records.
             for(int i =0 ; i < 5; i++)
             {
                 QList<QString> firstRow;
                 firstRow.append("-1"); // Fake id as it is defaults.
                 firstRow.append(QString::number(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_ActiveUserId()));
                 firstRow.append(defaulTypes[i]);
                 firstRow.append(defaulTypesDesc[i]);
                 currentUserExpenseGroups.append(firstRow);
             }

         }
         else
         {
            for(int j = 0; j < 5;j++)
            {
                int isDefaultTypeAval = false;
                for(int i = 0; i < currentUserExpenseGroups.size();i++)
                {
                    /*Type is available only if already added by current user.*/
                    if(currentUserExpenseGroups.at(i).at(2) == defaulTypes[j])
                    {
                        /*ID tables are starting from .1.*/
                        isDefaultTypeAval = true;
                        break;

                    }
                }
                if(false == isDefaultTypeAval)
                {
                    QList<QString> firstRow;
                    firstRow.append("-1"); // Fake id as it is defaults.
                    firstRow.append(QString::number(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_ActiveUserId())); // Fake id as it is defaults.
                    firstRow.append(defaulTypes[j]);
                    firstRow.append(defaulTypesDesc[j]);
                    currentUserExpenseGroups.append(firstRow);
                }
            }
         }
     }
     else
     {
         /*Defensive programming if table is empty. No rows from current user.*/
        for(int i =0 ; i < 5; i++)
        {
            QList<QString> firstRow;
            firstRow.append("-1"); // Fake id as it is defaults.
            firstRow.append("-1"); // Fake id as it is defaults.
            firstRow.append(defaulTypes[i]);
            firstRow.append(defaulTypesDesc[i]);
            currentUserExpenseGroups.append(firstRow);
        }
     }
     this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Set_activeUserExpGroups(currentUserExpenseGroups);

     if(TypeOfReq == 0)
     {
        /*Request add expense window.*/
        emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_OpenAddExpenseWindow();
     }
     else
     {
         /*Request custom window for searching by type.*/
        emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_OpenCustomExpTypeFilter();
     }
}

/*Process expenses and provide to report.*/
void EP_ReportMain::EP_ReportMain_ProcessReport(EP_Report_Types TypeOfReport, QList<QString> dataToProcess)
{
    /*Local vars.*/
    QString typeOfReport = "";
    bool isUserRequestAval = false;
    /*Get All expense groups.*/
    QList<QList<QString>> currentUserExpenseGroups = this->EP_ReportMain_GetDBPointer()->getExpenseGroups(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_ActiveUserId());
    /*Initialize input arguments for getExpenseGroups.*/
    int TypeOfExpense = 0;
    double Ammount = 0;
    QString Ammount_delta = "";
    QString expense_name = "";
    QString Expense_description = "";
    int ExpGroups = 0;
    int FromTime = 0;
    int toTime = 0;
    /*Pre-process necessary arguments for calling function getExpense.*/
    switch (TypeOfReport)
    {
        case EP_EXPENSE_TODAY_EXPENSE_TIME:
        {
            QDateTime date = QDateTime::currentDateTime();
            /*Set time format to UNIX*/
            date.setTimeSpec(Qt::UTC);
            /*Change query for today date the value to int.*/
            FromTime = date.toTime_t();
            typeOfReport = "Today expenses.";
            isUserRequestAval = true;
            TypeOfExpense = 1; // Expense.
            break;
        }
        case EP_EXPENSE_THIS_WEEK_TIME:
        {
            /*Create ending point.*/
            QDate date = QDate::currentDate();
            QTime time;
            /*Set time to last possible hour/minute/second/milisceond of the current day.*/
            time.setHMS(23,59,59,999);
            QDateTime endingPoint = QDateTime::currentDateTime();
            endingPoint.setTime(time);
            /* - Set time format to UNIX*/
            /* Get time from ECpoch*/
            endingPoint.setTimeSpec(Qt::UTC);
            /*Create strating point.*/
            int numbOfWeekDay = date.dayOfWeek();
            /*Always compare current day of week with first-monday.*/
            qint64 getOffsetForStartingPoint = 1 - numbOfWeekDay;
            /*Calculate how many days in terms of seconds to substract the current date.*/
            getOffsetForStartingPoint = (86400 * (numbOfWeekDay * (-1)));
            qint64 startingPointOfweekInEpochSecs = (endingPoint.toSecsSinceEpoch() - getOffsetForStartingPoint);
            QDateTime StartingPoint = QDateTime();
            /*Set time defined by Epoc and timespec to UTC..*/
            StartingPoint.setTimeSpec(Qt::UTC);
            StartingPoint.setSecsSinceEpoch(startingPointOfweekInEpochSecs);
            /*Change starting point and ending point.*/
            toTime = endingPoint.toTime_t();
            FromTime = StartingPoint.toTime_t();
            typeOfReport = "This week expenses.";
            isUserRequestAval = true;
            TypeOfExpense = 1; // Expense.
            break;
        }
        case EP_EXPENSE_THIS_MONTH_TIME:
        {
            /*Create ending point.*/
            QDate date = QDate::currentDate();
            QTime time;
            /*Set time to last possible hour/minute/second/milisceond of the current day.*/
            time.setHMS(23,59,59,999);
            QDateTime endingPoint = QDateTime::currentDateTime();
            endingPoint.setTime(time);
            /* - Set time format to UNIX*/
            /* Get time from ECpoch*/
            endingPoint.setTimeSpec(Qt::UTC);
            /*Create strating point.*/
            qint64 getOffsetForStartingPoint = (date.day() - date.daysInMonth());
            /*Calculate how many days in terms of seconds to substract the current date.*/
            getOffsetForStartingPoint = (86400 * (getOffsetForStartingPoint * (-1)));
            qint64 startingPointOfweekInEpochSecs = (endingPoint.toSecsSinceEpoch() - getOffsetForStartingPoint);
            QDateTime StartingPoint = QDateTime();
            /*Set time defined by Epoc and timespec to UTC..*/
            StartingPoint.setTimeSpec(Qt::UTC);
            StartingPoint.setSecsSinceEpoch(startingPointOfweekInEpochSecs);
            /*Change starting point and ending point.*/
            toTime = endingPoint.toTime_t();
            FromTime = StartingPoint.toTime_t();
            typeOfReport = "This month expenses.";
            isUserRequestAval = true;
            TypeOfExpense = 1; // Expense.
            break;
        }
        case EP_EXPENSE_THIS_YEAR_TIME:
        {
            /*Create ending point.*/
            QDate dateEndOfyear = QDate::currentDate();
            QTime timeEndOfYear;
            timeEndOfYear.setHMS(23,59,59,999); /*Set time to last possible hour/minute/second/milisceond of the current day.*/
            QDateTime endingPoint = QDateTime(dateEndOfyear,timeEndOfYear);
            /*Create starting point*/
            QDate dateStartOfyear = QDate(dateEndOfyear.year(),1,1);
            QTime timeStartOfYear;
            timeStartOfYear.setHMS(23,59,59,999); /*Set time to last possible hour/minute/second/milisceond of the current day.*/
            QDateTime StartingPoint = QDateTime(dateStartOfyear,timeStartOfYear);
            /*Change starting point and ending point.*/
            toTime = endingPoint.toTime_t();
            FromTime = StartingPoint.toTime_t();
            typeOfReport = "This year expenses.";
            isUserRequestAval = true;
            TypeOfExpense = 1; // Expense.
            break;
        }
        case EP_EXPENSE_ALL_TIME_TIME:
        {
            typeOfReport = "All time expenses.";
            isUserRequestAval = true;
            TypeOfExpense = 1; // Expense.
            break;
        }
        case EP_EXPENSE_CUSTOM_TIME:
        {
            typeOfReport = "Custom time fileters expenses.";
            FromTime = dataToProcess.at(0).toInt();
            qDebug("From time : %d", FromTime);
            toTime = dataToProcess.at(1).toInt();
            qDebug("To time : %d", toTime);
            TypeOfExpense = 1; // Expense.
            isUserRequestAval = true;
            break;
        }
        case EP_EXPENSE_TRANSPORT_TYPE:
        {
            QString expenseGroupConst = "Transport";
            for(int i = 0; i < currentUserExpenseGroups.size();i++)
            {
                if(currentUserExpenseGroups.at(i).at(2) == expenseGroupConst)
                {
                    isUserRequestAval = true;
                    ExpGroups = currentUserExpenseGroups.at(i).at(0).toInt();
                }
            }
            typeOfReport = "Transport expenses.";
            TypeOfExpense = 1; // Expense.
            break;
        }
        case EP_EXPENSE_FOOD_TYPE:
        {
            QString expenseGroupConst = "Food";
            for(int i = 0; i < currentUserExpenseGroups.size();i++)
            {
                if(currentUserExpenseGroups.at(i).at(2) == expenseGroupConst)
                {
                    isUserRequestAval = true;
                    ExpGroups = currentUserExpenseGroups.at(i).at(0).toInt();
                }
            }
            typeOfReport = "Food expenses.";
            TypeOfExpense = 1; // Expense.
            break;
        }
        case EP_EXPENSE_CLOTHES_TYPE:
        {
            QString expenseGroupConst = "Clothes";
            for(int i = 0; i < currentUserExpenseGroups.size();i++)
            {
                if(currentUserExpenseGroups.at(i).at(2) == expenseGroupConst)
                {
                    isUserRequestAval = true;
                    ExpGroups = currentUserExpenseGroups.at(i).at(0).toInt();
                }
            }
            typeOfReport = "Clothes expenses.";
            TypeOfExpense = 1; // Expense.
            break;
        }
        case EP_EXPENSE_UTILITY_TYPE:
        {
            QString expenseGroupConst = "Utility";
            for(int i = 0; i < currentUserExpenseGroups.size();i++)
            {
                if(currentUserExpenseGroups.at(i).at(2) == expenseGroupConst)
                {
                    isUserRequestAval = true;
                    ExpGroups = currentUserExpenseGroups.at(i).at(0).toInt();
                }
            }
            typeOfReport = "Utility expenses.";
            TypeOfExpense = 1; // Expense.
            break;
        }
        case EP_EXPENSE_BANK_TYPE:
        {
            QString expenseGroupConst = "Bank";
            for(int i = 0; i < currentUserExpenseGroups.size();i++)
            {
                if(currentUserExpenseGroups.at(i).at(2) == expenseGroupConst)
                {
                    isUserRequestAval = true;
                    ExpGroups = currentUserExpenseGroups.at(i).at(0).toInt();
                }
            }
            typeOfReport = "Bank expenses.";
            TypeOfExpense = 1; // Expense.
            break;
        }
        case EP_EXPENSE_OTHER_TYPE:
        {
            typeOfReport = "Custom type filters expenses.";
            TypeOfExpense = 1; // Expense.
            QString expenseGroupConst = dataToProcess.at(0);
            for(int i = 0; i < currentUserExpenseGroups.size();i++)
            {
                if(currentUserExpenseGroups.at(i).at(2) == expenseGroupConst)
                {
                    isUserRequestAval = true;
                    ExpGroups = currentUserExpenseGroups.at(i).at(0).toInt();
                }
            }
            break;
        }
        case EP_INCOME_TODAY:
        {
            QDateTime date = QDateTime::currentDateTime();
            /*Set time format to UNIX*/
            date.setTimeSpec(Qt::UTC);
            /*Change query for today date the value to int.*/
            FromTime = date.toTime_t();
            typeOfReport = "Today incomes.";
            isUserRequestAval = true;
            TypeOfExpense = 0; // Expense.
            break;
        }
        case EP_INCOME_THIS_WEEK:
        {
            /*Create ending point.*/
            QDate date = QDate::currentDate();
            QTime time;
            /*Set time to last possible hour/minute/second/milisceond of the current day.*/
            time.setHMS(23,59,59,999);
            QDateTime endingPoint = QDateTime::currentDateTime();
            endingPoint.setTime(time);
            /* - Set time format to UNIX*/
            /* Get time from ECpoch*/
            endingPoint.setTimeSpec(Qt::UTC);
            /*Create strating point.*/
            int numbOfWeekDay = date.dayOfWeek();
            /*Always compare current day of week with first-monday.*/
            qint64 getOffsetForStartingPoint = 1 - numbOfWeekDay;
            /*Calculate how many days in terms of seconds to substract the current date.*/
            getOffsetForStartingPoint = (86400 * (numbOfWeekDay * (-1)));
            qint64 startingPointOfweekInEpochSecs = (endingPoint.toSecsSinceEpoch() - getOffsetForStartingPoint);
            QDateTime StartingPoint = QDateTime();
            /*Set time defined by Epoc and timespec to UTC..*/
            StartingPoint.setTimeSpec(Qt::UTC);
            StartingPoint.setSecsSinceEpoch(startingPointOfweekInEpochSecs);
            /*Change starting point and ending point.*/
            toTime = endingPoint.toTime_t();
            FromTime = StartingPoint.toTime_t();
            typeOfReport = "This week incomes.";
            isUserRequestAval = true;
            TypeOfExpense = 0; // Expense.
            break;
        }
        case EP_INCOME_THIS_MONTH:
        {
            /*Create ending point.*/
            QDate date = QDate::currentDate();
            QTime time;
            /*Set time to last possible hour/minute/second/milisceond of the current day.*/
            time.setHMS(23,59,59,999);
            QDateTime endingPoint = QDateTime::currentDateTime();
            endingPoint.setTime(time);
            /* - Set time format to UNIX*/
            /* Get time from ECpoch*/
            endingPoint.setTimeSpec(Qt::UTC);
            /*Create strating point.*/
            qint64 getOffsetForStartingPoint = (date.day() - date.daysInMonth());
            /*Calculate how many days in terms of seconds to substract the current date.*/
            getOffsetForStartingPoint = (86400 * (getOffsetForStartingPoint * (-1)));
            qint64 startingPointOfweekInEpochSecs = (endingPoint.toSecsSinceEpoch() - getOffsetForStartingPoint);
            QDateTime StartingPoint = QDateTime();
            /*Set time defined by Epoc and timespec to UTC..*/
            StartingPoint.setTimeSpec(Qt::UTC);
            StartingPoint.setSecsSinceEpoch(startingPointOfweekInEpochSecs);
            /*Change starting point and ending point.*/
            toTime = endingPoint.toTime_t();
            FromTime = StartingPoint.toTime_t();
            typeOfReport = "This month incomes.";
            isUserRequestAval = true;
            TypeOfExpense = 0; // Expense.
            break;
        }
        case EP_INCOME_THIS_YEAR:
        {
            /*Create ending point.*/
            QDate dateEndOfyear = QDate::currentDate();
            QTime timeEndOfYear;
            timeEndOfYear.setHMS(23,59,59,999); /*Set time to last possible hour/minute/second/milisceond of the current day.*/
            QDateTime endingPoint = QDateTime(dateEndOfyear,timeEndOfYear);
            /*Create starting point*/
            QDate dateStartOfyear = QDate(dateEndOfyear.year(),1,1);
            QTime timeStartOfYear;
            timeStartOfYear.setHMS(23,59,59,999); /*Set time to last possible hour/minute/second/milisceond of the current day.*/
            QDateTime StartingPoint = QDateTime(dateStartOfyear,timeStartOfYear);
            /*Change starting point and ending point.*/
            toTime = endingPoint.toTime_t();
            FromTime = StartingPoint.toTime_t();
            typeOfReport = "This year incomes.";
            isUserRequestAval = true;
            TypeOfExpense = 0; // Income.
            break;
        }
        case EP_INCOME_ALL_TIME:
        {
            typeOfReport = "All time incomes.";
            isUserRequestAval = true;
            TypeOfExpense = 0; // Income.
            break;
        }
        case EP_INCOME_CUSTOM:
        {
            typeOfReport = "Custom time fileters incomes.";
            FromTime = dataToProcess.at(0).toInt();
            qDebug("From time : %d", FromTime);
            toTime = dataToProcess.at(1).toInt();
            qDebug("To time : %d", toTime);
            TypeOfExpense = 0; // Expense.
            isUserRequestAval = true;
            break;
        }
        default:
        {
            break;
        }
    }
    QList<QList<QString>> currentUserExpenses;
    if(isUserRequestAval == true)
    {
        /*Get All expenses.*/
       currentUserExpenses= this->EP_ReportMain_GetDBPointer()->getExpenses(
                    this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_ActiveUserId(),
                    this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserData().at(0).at(0).toInt(),
                    TypeOfExpense, // All groups.
                    Ammount, // Without filter for amounts
                   Ammount_delta, // Empty ammount delta, this is necessary whem amount is presented.
                   expense_name, // Empty filter for sorting by expense name
                   Expense_description, // Empty filter for sorting by description
                    ExpGroups, // Empty filter for sorting by expensegroups.
                    FromTime, // Empty filter for sorting by time -> Starting point.
                    toTime, // Empty filter for sorting by time -> Ending point.
                    0 // Empty filter for adding limit to the requested expenses.
                    );
    }
    else
    {
        // Do nothing QList of QList is already empty.
    }

   /*Substitue the exp_groups id to name of expense type.*/
   for(int i = 0; i< currentUserExpenses.count();i++)
   {
       for(int j = 0; j< currentUserExpenseGroups.count();j++)
       {
           if(currentUserExpenses.at(i).at(6).toInt() == currentUserExpenseGroups.at(j).at(0).toInt())
           {
               currentUserExpenses[i][6] = currentUserExpenseGroups[j][2];
               break;
           }
       }
   }
   /*Emit signal to GUI to generate the window.*/
   emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_GenerateReport(currentUserExpenses, typeOfReport);
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
