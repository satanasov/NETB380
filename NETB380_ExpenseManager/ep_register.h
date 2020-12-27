#ifndef EP_REGISTER_H
#define EP_REGISTER_H

#include <QDialog>
#include <QMutex>
#include "ep_db_wrapper.h"
#include "ep_baseclass_gui_reportmain.h"

namespace Ui {
class ep_register;
}

class ep_register : public QDialog, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

public:
    explicit ep_register(QWidget *parent = nullptr);
    ~ep_register();
    /*Connections.*/
    void EP_Register_ConnectSlots_UserData();
    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;

private slots:
    void on_pushButtonRegister_clicked();
    void EP_Register_Save_Data_In_UserData();

signals:
    void EP_Register_registerDialogFilledCorrectly();

private:
    Ui::ep_register *ui;
    bool IsLineEditEmptyOrDefault(int FieldType);
    void CreateWarningDialog(int FieldType);
};

#endif // EP_REGISTER_H
