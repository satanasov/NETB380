/*
- Purpose of this class is to connect events between the GUI and DBMS Wrapper module.
*/

#ifndef EP_EVENTDISPATCHER_H
#define EP_EVENTDISPATCHER_H

#include <QObject>

class EP_EventDispatcher: public QObject
{
    Q_OBJECT
public:
    EP_EventDispatcher();

signals:
    /*Signals to Report Main.*/
    void EP_ED_RegWinRegistrationRequest();
    void EP_ED_LogWinLogInRequest();
    void EP_ED_DBWinRequestDBConnection();
    void EP_ED_DBWinRequestDeployTable();
    void EP_ED_DBWinRequestDropTable();

    /*Signals to GUI.*/
    /*Registration window.*/
    void EP_ED_RMRegistrationStatus(int RegStatus);
    /*Log-in window.*/
    void EP_ED_RMLoginStatus(int LogStatus);
    /*DB_Settings window.*/
    void EP_ED_RMDBConectionSuccessfull();
};

#endif // EP_EVENTDISPATCHER_H
