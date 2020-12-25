#include "ep_welcome.h"
#include "ui_ep_welcome.h"

ep_welcome::ep_welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_welcome)
{
    ui->setupUi(this);
}

ep_welcome::~ep_welcome()
{
    delete ui;
}

void ep_welcome::on_pushButtonAddMoney_clicked()
{
    //add money dialog
}
