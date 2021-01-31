/*
- Purpose of this class is to connect events between the GUI and DBMS Wrapper module.
*/

#ifndef EP_EVENTDISPATCHER_H
#define EP_EVENTDISPATCHER_H

#include <QObject>
#include <QDateTime>
#include "EP_CustomTypes.h"

class EP_EventDispatcher: public QObject
{
    Q_OBJECT
public:
    EP_EventDispatcher();

signals:
    /*Signals to Report Main.*/
        /*reg screen.*/
        void EP_ED_RegWinRegistrationRequest();
        /*log screen.*/
        void EP_ED_LogWinLogInRequest();
        /*DB_Settings*/
        void EP_ED_DBWinRequestDBConnection(int RequestId);
        void EP_ED_DBWinRequestDeployTable();
        void EP_ED_DBWinRequestDropTable();
        /*WelcomeScreen.*/
        void EP_ED_WlcScreenUpdateCurrentUserData();
        void EP_ED_RMWlcScreen_getReport(EP_Report_Types ReportType, QList<QString> DataToProvide);
        void EP_ED_RMWlcScreen_updateCurrentUserExpGroups(int ReqType);
        /*Add expense window.*/
        void EP_ED_AEWinRequestAddingExpense(QString nameOfExpense, QString typeOfExpense, QString amountOfExpense, QString description, QDateTime date, int expType);
        /*Editing expense window.*/
        void EP_ED_EWinRequestTableRowUpdate(QList<QString> data);

    /*Signals to GUI.*/
        /*Registration window.*/
        void EP_ED_RMRegistrationStatus(int RegStatus);
        /*Log-in window.*/
        void EP_ED_RMLoginStatus(int LogStatus);
        /*DB_Settings window.*/
        void EP_ED_RMDBConectionSuccessfull();
        /*Welcom screen window.*/
        void EP_ED_RMWlcScreen_GenerateReport(QList<QList<QString>> queryResult, QString reportName);
        void EP_ED_RMWlcScreen_UpdateCurrentUserAmount();
        void EP_ED_RMWlcScreen_OpenAddExpenseWindow();
        void EP_ED_RMWlcScreen_OpenCustomExpTypeFilter();
        /*Add expense window.*/
        void EP_ED_RM_AddExpenseStatus(int Status);
        /*Add money window.*/
        void EP_ED_RM_AddMoneyStatus(int Status);
        /*Edit window.*/
        void EP_ED_RM_Editexpenseincoem(int Status);
};

#endif // EP_EVENTDISPATCHER_H
