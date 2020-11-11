#include "ep_db_settings.h"
#include "ui_ep_db_settings.h"
#include <QMessageBox>
#include <QSettings>


ep_db_settings::ep_db_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_db_settings)
{
    ui->setupUi(this);

    ui->DBHost->setPlaceholderText("DB Host");
    ui->DBUsername->setPlaceholderText("DB Username");
    ui->DBPass->setPlaceholderText("DB Password");
    ui->DBName->setPlaceholderText("DB Name");
    //placeholders for register fields
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

    this->close();

    qDebug() << settings.fileName();
}
