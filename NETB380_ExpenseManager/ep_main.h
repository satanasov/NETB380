#ifndef EP_MAIN_H
#define EP_MAIN_H

#include <QMainWindow>
#include "ep_register.h" //needed in order to open reg window from main window
#include "ep_db_settings.h"
#include <QMutex>

QT_BEGIN_NAMESPACE
namespace Ui { class EP_Main; }
QT_END_NAMESPACE

class EP_Main : public QMainWindow
{
    Q_OBJECT

public:
    EP_Main(QWidget *parent = nullptr);
    ~EP_Main();
    void EP_Main_SetUserDataPointer(EP_UserData *UserDataPointer);
    EP_UserData* EP_Main_GetUserDataPointer();
    void EP_Main_ConnectSlots_UserData();

private slots:

    void on_pushButtonLogIn_clicked();

    void on_pushButtonConnectDB_clicked();

    void on_pushButtonCreateNewAccount_clicked();

private:
    Ui::EP_Main *ui;
    ep_register *ep_reg; //needed in order to open reg window from main window
    ep_db_settings *ep_db_set;
    /*User data pointer.*/
    EP_UserData *PointerToUserData = nullptr;
};
#endif // EP_MAIN_H
