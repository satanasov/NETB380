#include <QDateTime>
#include <QMessageBox>
#include "ep_add_expense.h"
#include "ui_ep_add_expense.h"

ep_add_expense::ep_add_expense(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_add_expense)
{
    ui->setupUi(this);
    /*Add current system date.*/
    QDate date = QDate::currentDate();
    ui->dateEditDateExpense->setDate(date);

}

ep_add_expense::~ep_add_expense()
{
    delete ui;
}

void ep_add_expense::on_pushButtonExpenseAdd_clicked()
{
    /*Make input validation.*/
    QString nameOfExpense = ui->lineEditNameExpense->text();
    QString typeOfExpense = ui->lineEditTypeExpense->text();
    QString amountOfExpense = ui->doubleSpinBoxPriceExpense->text();

    /* Request expense adding.*/
    this->EP_BaseClass_GetEDPointer()->EP_ED_AEWinRequestAddingExpense(nameOfExpense,typeOfExpense,amountOfExpense,ui->dateEditDateExpense->dateTime());
}

/* Local function.*/
void ep_add_expense::EP_AddExpense_ConnectToED()
{
   /*Connect to Event dispatcher.*/
   connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RM_AddExpenseStatus(int)),this,SLOT(EP_AE_AddedExpenseStatus(int)));
}



/*Slots*/
void ep_add_expense::EP_AE_AddedExpenseStatus(int Status)
{
    /*Extend if you need further error handling.*/
    QMessageBox msg;
    switch (Status) {
        case -2:
           msg.setText("Unknown ERROR ... you should never see this.");
        break;
        case -1:
           msg.setText("Database is not connected ... Do you know what you are doing?");
        break;
        case 0:
           msg.setText("Expense succesfully added!");
        break;
        case 1:
           msg.setText("User alredy exists ...");
        break;
        case 2:
           msg.setText("Email alredy in system ...");
        break;
    }
    msg.setWindowTitle("Add expense status");
    msg.exec();
}
