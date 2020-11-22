#ifndef EP_REGISTER_H
#define EP_REGISTER_H

#include <QDialog>
#include "ep_userdata.h"
#include <QMutex>
#include "ep_db_wrapper.h"

namespace Ui {
class ep_register;
}

class ep_register : public QDialog
{
    Q_OBJECT

public:
    explicit ep_register(QWidget *parent = nullptr);
    ~ep_register();
    void EP_Register_SetUserDataPointer(EP_UserData *UserDataPointer);
    EP_UserData* EP_Register_GetUserDataPointer();
    void EP_Register_ConnectSlots_UserData();

private slots:
    void on_pushButtonRegister_clicked();
    void save_Data_In_UserData();

signals:
    void registerDialogFilledCorrectly();

private:
    Ui::ep_register *ui;
    EP_UserData *PointerToUserData = nullptr;
    bool IsLineEditEmptyOrDefault(int FieldType);
    void CreateWarningDialog(int FieldType);
    EP_DB_Wrapper *sql = new EP_DB_Wrapper();
};

#endif // EP_REGISTER_H
