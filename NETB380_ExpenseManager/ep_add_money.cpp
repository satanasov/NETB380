#include "ep_add_money.h"
#include "ui_ep_add_money.h"
#include <QMessageBox>

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
    double money = ui->doubleSpinBoxAmmount->value();
    QMessageBox::information(this, "Success!", "Succesfully added %d to balance!");
    // add code to get the user input from baseclass
}
