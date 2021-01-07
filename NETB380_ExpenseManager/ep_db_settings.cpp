#include <QMessageBox>
#include <QSettings>
#include "ep_db_settings.h"
#include "ui_ep_db_settings.h"
#include "ep_db_wrapper.h"

ep_db_settings::ep_db_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_db_settings)
{
    ui->setupUi(this);
}

ep_db_settings::~ep_db_settings()
{
    delete ui;
}

/**
 * Open DB Settings window.
 * @brief ep_db_settings::on_pushButtonConnect_clicked
 */
void ep_db_settings::on_pushButtonConnect_clicked()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,"Netb380", "EPManager");
    QString DB_HOST = ui->DBHost->text();
    QString DB_USER = ui->DBUsername->text();
    QString DB_PASS = ui->DBPass->text();
    QString DB_NAME = ui->DBName->text();

    settings.setValue("DB_HOST", DB_HOST);
    settings.setValue("DB_USER", DB_USER);
    settings.setValue("DB_PASS", DB_PASS);
    settings.setValue("DB_NAME", DB_NAME);
    /*Request opening of DB and pass settings.*/
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_DBSettingsRequest();
    /*Report Ini file location.*/
    qDebug() << settings.fileName();
}

/*Request deployment of DB tables.*/
void ep_db_settings::on_pushButtonDeploy_clicked()
{
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_DBRequestDeployTable();
}

/*Request deletion of DB tables.*/
void ep_db_settings::on_pushButtonDrop_clicked()
{
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_DBRequestDropTable();
}
