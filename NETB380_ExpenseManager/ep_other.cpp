#include "ep_other.h"
#include "ui_ep_other.h"
#include <QDateTime>

ep_other::ep_other(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_other)
{
    ui->setupUi(this);
    QDate date = QDate::currentDate();
    ui->dateEditFrom->setDate(date);
    ui->dateEditTo->setDate(date);
}

ep_other::~ep_other()
{
    delete ui;
}

void ep_other::on_pushButtonSearch_clicked()
{
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->show();
    hide();
}
