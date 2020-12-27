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
    void EP_ED_RegistrationRequest();
    void EP_ED_LogInRequest();

    /*Signals to GUI.*/
    void EP_ED_RegistrationStatus(int RegStatus);
    void EP_ED_LoginStatus(int LogStatus);
};

#endif // EP_EVENTDISPATCHER_H
