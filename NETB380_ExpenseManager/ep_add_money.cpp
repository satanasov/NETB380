#include "ep_add_money.h"
#include "ui_ep_add_money.h"

ep_add_money::ep_add_money(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_add_money)
{
    ui->setupUi(this);
}

ep_add_money::~ep_add_money()
{
    delete ui;
}

void ep_add_money::on_pushButtonMoneyAdd_clicked()
{
    //todo succesfully add money to account
}
