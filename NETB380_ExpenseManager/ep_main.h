#ifndef EP_MAIN_H
#define EP_MAIN_H

#include <QMainWindow>
#include "ep_register.h" //needed in order to open reg window from main window
#include "ep_db_settings.h"
#include "ep_baseclass_gui_reportmain.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EP_Main; }
QT_END_NAMESPACE

class EP_Main : public QMainWindow, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

public:
    EP_Main(QWidget *parent = nullptr);
    ~EP_Main();
    /*Connection to EventDispatcher signals if necessary. Left here only for template*/
    void EP_Main_ConnectSlots_EventDispatcher();
    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;

private slots:
    void on_pushButtonLogIn_clicked();
    void on_pushButtonConnectDB_clicked();
    void on_pushButtonCreateNewAccount_clicked();
    void EP_Main_RegistrationStatusWindow(int RegStatus);
    void EP_Main_LoginStatusWindow(int LogStatus);

private:
    Ui::EP_Main *ui;
    ep_register *ep_reg; //needed in order to open reg window from main window
    ep_db_settings *ep_db_set;

};
#endif // EP_MAIN_H
