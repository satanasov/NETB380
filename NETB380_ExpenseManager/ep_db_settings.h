#ifndef EP_DB_SETTINGS_H
#define EP_DB_SETTINGS_H

#include <QDialog>
#include "ep_userdata.h"
#include <QMutex>

namespace Ui {
class ep_db_settings;
}

class ep_db_settings : public QDialog
{
    Q_OBJECT

public:
    explicit ep_db_settings(QWidget *parent = nullptr);
    ~ep_db_settings();
    void EP_Register_SetUserDataPointer(EP_UserData *UserDataPointer);
    EP_UserData* EP_Register_GetUserDataPointer();
    void EP_Register_ConnectSlots_UserData();

private slots:
    void on_pushButtonConnect_clicked();

signals:
    void registerDialogFilledCorrectly();

private:
    Ui::ep_db_settings *ui;

};

#endif // EP_DB_SETTINGS_H
