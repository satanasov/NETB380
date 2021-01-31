#ifndef EP_REPORTMAIN_WRAPPER_H
#define EP_REPORTMAIN_WRAPPER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QSettings>
#include "ep_db_wrapper.h"
#include "ep_baseclass_gui_reportmain.h"

class EP_ReportMain : public QObject, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

public:
    /*Constructor.*/
    explicit EP_ReportMain(QObject *parent = nullptr);
    /*Create connection between DBMS wrapper and the thread created in main.*/
    void EP_ReportMain_SetupThread(QThread &cThread);
    /*Create connection between Event Dispatcher and Report Main.*/
    void EP_ReportMain_ConnectToEventDispacther();

    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;

    /*Setters*/
    void EP_ReportMain_SetDBPointer(EP_DB_Wrapper *pointToDB);

    /*Getters*/
    EP_DB_Wrapper* EP_ReportMain_GetDBPointer();

    /*Local help funcs.*/
    QString translateTypeOfCurrencyToString(int ExpGroup);
    int translateTypeOfCurrencyToExpGroupNumb(QString typeOfExpense);

private:
    /*Pointer to DB wrapper.*/
    EP_DB_Wrapper *sql = nullptr;
    /*DB Settings*/

signals:
    /*Internal signals.*/
    void EP_ReportMain_OpenDB(int idOfRequest);

public slots:
    /*Main_UI_Slot*/
    void EP_ReportMain_GetUserLogInStatus();

    /*Register_UI_Slots*/
    void EP_ReportMain_GetUserDataRegisterStatus();

    /*DB_Settings Slots*/
    void EP_ReportMain_DeployTableInCurrentDB();
    void EP_ReportMain_DropTableInCurrentDB();

    /*Welcome screen slots.*/
  //  void EP_ReportMain_ActiveUserNameAndAmount();
    void EP_ReportMain_ProcessReport(EP_Report_Types TypeOfReport, QList<QString> dataToProcess);
    void EP_ReportMain_Update_activeUserData();
    void EP_ReportMain_Update_activeUserExpGroups(int TypeOfReq);

    /*Edit window*/
    void EP_ReportMain_UpdateExpense(QList<QString> rowData);
    /*Add expense window*/
    void EP_ReportMain_AddExpense(QString nameOfExpense, QString typeOfExpense, QString amountOfExpense, QString descriptionOfExpense, QDateTime date, int ExpType);

    /*Internal slots*/
    void EP_ReportMain_OpenDBConnection(int idOfRequest);
};

#endif // EP_REPORTMAIN_H
