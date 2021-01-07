#ifndef EP_DB_SETTINGS_H
#define EP_DB_SETTINGS_H

#include <QDialog>
#include <QMutex>
#include "ep_userdata.h"
#include "ep_db_wrapper.h"
#include "ep_baseclass_gui_reportmain.h"

namespace Ui {
class ep_db_settings;
}

class ep_db_settings : public QDialog, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

public:
    explicit ep_db_settings(QWidget *parent = nullptr);
    ~ep_db_settings();
    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;

private slots:
    void on_pushButtonConnect_clicked();
    void on_pushButtonDeploy_clicked();
    void on_pushButtonDrop_clicked();

private:
    Ui::ep_db_settings *ui;

};

#endif // EP_DB_SETTINGS_H
