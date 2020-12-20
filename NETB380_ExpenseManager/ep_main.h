#ifndef EP_MAIN_H
#define EP_MAIN_H

#include <QMainWindow>
#include "ep_register.h" //needed in order to open reg window from main window
#include "ep_db_settings.h"
#include <QMutex>
#include "ep_eventdispatcher.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EP_Main; }
QT_END_NAMESPACE

class EP_Main : public QMainWindow
{
    Q_OBJECT

public:
    EP_Main(QWidget *parent = nullptr);
    ~EP_Main();
    /*Setters*/
    void EP_Main_SetUserDataPointer(EP_UserData *UserDataPointer);
    void EP_Main_SetEventDispatcherPointer(EP_EventDispatcher *EDPointer);
    /*Getters*/
    EP_UserData* EP_Main_GetUserDataPointer();
    EP_EventDispatcher* EP_Main_GetEDPointer();
    /*Connection to EventDispatcher signals if necessary. Left here only for template*/
    void EP_Main_ConnectSlots_EventDispatcher();

private slots:
    void on_pushButtonLogIn_clicked();
    void on_pushButtonConnectDB_clicked();
    void on_pushButtonCreateNewAccount_clicked();
    void EP_Main_RegistrationStatusWindow(int RegStatus);

private:
    Ui::EP_Main *ui;
    ep_register *ep_reg; //needed in order to open reg window from main window
    ep_db_settings *ep_db_set;
    /*User data pointer.*/
    EP_UserData *PointerToUserData = nullptr;
    /*Event dispatcher pointer.*/
    EP_EventDispatcher *PointerToEventDispacther = nullptr;
};
#endif // EP_MAIN_H
