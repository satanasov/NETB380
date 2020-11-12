#include "ep_db_settings.h"
#include "ui_ep_db_settings.h"
#include <QMessageBox>
#include <QSettings>
#include "ep_db_wrapper.h"


ep_db_settings::ep_db_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_db_settings)
{
    ui->setupUi(this);

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Netb380", "EPManager");
    QString DB_HOST = settings.value("DB_HOST", "").toString();
    QString DB_USER = settings.value("DB_USER", "").toString();
    QString DB_PASS = settings.value("DB_PASS", "").toString();
    QString DB_NAME = settings.value("DB_NAME", "").toString();

    // TODO: Check if DB settings have connected to the DB and recheck
    if (DB_HOST == "" || DB_USER == "" || DB_PASS == "" || DB_NAME == "")
    {
        ui->DBHost->setPlaceholderText("DB Host");
        ui->DBUsername->setPlaceholderText("DB Username");
        ui->DBPass->setPlaceholderText("DB Password");
        ui->DBName->setPlaceholderText("DB Name");
        //placeholders for register fields
    }
    else
    {
        ui->DBHost->setText(DB_HOST);
        ui->DBUsername->setText(DB_USER);
        ui->DBPass->setText(DB_PASS);
        ui->DBName->setText(DB_NAME);
        this->sql->openDB(DB_HOST, DB_USER, DB_PASS, DB_NAME);
    }

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

    this->sql->openDB(DB_HOST, DB_USER, DB_PASS, DB_NAME);

    qDebug() << settings.fileName();
}

/**
 * Deply DB tables ...
 * @brief ep_db_settings::on_pushButtonDeploy_clicked
 */
void ep_db_settings::on_pushButtonDeploy_clicked()
{
    this->sql->deployTables();
}

void ep_db_settings::on_pushButtonDrop_clicked()
{
    this->sql->dropTables();
}
