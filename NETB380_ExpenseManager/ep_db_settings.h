#ifndef EP_DB_SETTINGS_H
#define EP_DB_SETTINGS_H

#include <QDialog>
#include "ep_userdata.h"
#include <QMutex>
#include "ep_db_wrapper.h"

namespace Ui {
class ep_db_settings;
}

class ep_db_settings : public QDialog
{
    Q_OBJECT

public:
    explicit ep_db_settings(QWidget *parent = nullptr);
    ~ep_db_settings();

private slots:
    void on_pushButtonConnect_clicked();
    void on_pushButtonDeploy_clicked();
    void on_pushButtonDrop_clicked();

signals:
    void registerDialogFilledCorrectly();

private:
    Ui::ep_db_settings *ui;
    EP_DB_Wrapper *sql = new EP_DB_Wrapper();

};

#endif // EP_DB_SETTINGS_H
