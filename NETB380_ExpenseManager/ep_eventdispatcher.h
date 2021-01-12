/*
- Purpose of this class is to connect events between the GUI and DBMS Wrapper module.
*/

#ifndef EP_EVENTDISPATCHER_H
#define EP_EVENTDISPATCHER_H

#include <QObject>
#include <QDateTime>

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
   // void EP_ED_WlcScreenRequestInit();
    /*Add expense window*/
    void EP_ED_AEWinRequestAddingExpense(QString nameOfExpense, QString typeOfExpense, QString amountOfExpense, QDateTime date);

    /*Signals to GUI.*/
    /*Registration window.*/
    void EP_ED_RMRegistrationStatus(int RegStatus);
    /*Log-in window.*/
    void EP_ED_RMLoginStatus(int LogStatus);
    /*DB_Settings window.*/
    void EP_ED_RMDBConectionSuccessfull();
    /*Welcom screen window.*/
    //void EP_ED_RMWlcScreen_UpdateUserNameAndAmount(QString amount, QString Name);
    /*Add expense window.*/
    void EP_ED_RM_AddExpenseStatus(int Status);

};

#endif // EP_EVENTDISPATCHER_H
