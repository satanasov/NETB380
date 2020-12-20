#ifndef EP_REGISTER_H
#define EP_REGISTER_H

#include <QDialog>
#include <QMutex>
#include "ep_userdata.h"
#include "ep_db_wrapper.h"
#include "ep_eventdispatcher.h"

namespace Ui {
class ep_register;
}

class ep_register : public QDialog
{
    Q_OBJECT

public:
    explicit ep_register(QWidget *parent = nullptr);
    ~ep_register();

    /*Setters.*/
    void EP_Register_SetUserDataPointer(EP_UserData *UserDataPointer);
    void EP_Register_SetEventDispatcherPointer(EP_EventDispatcher *EDPointer);
    /*Getters.*/
    EP_UserData* EP_Register_GetUserDataPointer();
    EP_EventDispatcher* EP_Register_GetEDPointer();
    /*Connections.*/
    void EP_Register_ConnectSlots_UserData();

private slots:
    void on_pushButtonRegister_clicked();
    void EP_Register_Save_Data_In_UserData();

signals:
    void EP_Register_registerDialogFilledCorrectly();

private:
    Ui::ep_register *ui;
    /*Pointer to User Data.*/
    EP_UserData *PointerToUserData = nullptr;
    /*Event dispatcher pointer.*/
    EP_EventDispatcher *PointerToEventDispacther = nullptr;
    bool IsLineEditEmptyOrDefault(int FieldType);
    void CreateWarningDialog(int FieldType);
    //EP_DB_Wrapper *sql = new EP_DB_Wrapper();
};

#endif // EP_REGISTER_H
