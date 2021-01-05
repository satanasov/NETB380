#include "ep_add_expense.h"
#include "ui_ep_add_expense.h"

ep_add_expense::ep_add_expense(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_add_expense)
{
    ui->setupUi(this);
}

ep_add_expense::~ep_add_expense()
{
    delete ui;
}

void ep_add_expense::on_pushButtonExpenseAdd_clicked()
{
    //successfully add expense
}
