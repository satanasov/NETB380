/*
- Purpose of this class is to connect events between the GUI and DBMS Wrapper module.
*/

#ifndef EP_EVENTDISPATCHER_H
#define EP_EVENTDISPATCHER_H

#include <QObject>
#include "ep_customtypes.h"

class EP_EventDispatcher: public QObject
{
    Q_OBJECT
public:
    EP_EventDispatcher();

signals:
    /*Signals to Report Main.*/
    void EP_ED_RegWinRegistrationRequest();
    void EP_ED_LogWinLogInRequest();
    void EP_ED_DBWinRequestDBConnection(int RequestId);
    void EP_ED_DBWinRequestDeployTable();
    void EP_ED_DBWinRequestDropTable();
    void EP_ED_WelcWinRequestCurrentBalance(EP_Currencies TypeOfCurrency);
    void EP_ED_AddMoneyWinAddCurrencyValue(QString valueToAdd, EP_Currencies typeOfCurrencySelected);

    /*Signals to GUI.*/
    /*Registration window.*/
    void EP_ED_RMRegistrationStatus(int RegStatus);
    /*Log-in window.*/
    void EP_ED_RMLoginStatus(int LogStatus);
    /*DB_Settings window.*/
    void EP_ED_RMDBConectionSuccessfull();
    /*Welcome Screen.*/
    void EP_ED_RMWSUpdateCurrentCurrency(EP_Currencies currentCurrency, QString valueToDisplay);
    /*Add money screen.*/
    void EP_ED_RMAddedMoneyStatus(int Status, QString ValueToDisplay, EP_Currencies TypeOfCurrency);
};

#endif // EP_EVENTDISPATCHER_H
