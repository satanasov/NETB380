#include "ep_add_money.h"
#include "ui_ep_add_money.h"
#include <QMessageBox>
#include <QDateTime>

ep_add_money::ep_add_money(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_add_money)
{
    ui->setupUi(this);
    /*Add current system date.*/
    QDate date = QDate::currentDate();
    ui->dateEditDateExpense->setDate(date);
}

ep_add_money::~ep_add_money()
{
    delete ui;
}

void ep_add_money::on_pushButtonMoneyAdd_clicked()
{
    // add code to get the user input from baseclass
    /*Make input validation.*/
    QString nameOfExpense = "Income";
    QString typeOfExpense = "Income";
    QString amountOfExpense = ui->doubleSpinBoxAmmount->text();
    QString descriptionOfExpense = "Default description for income.";
    /* Request expense adding.*/
    this->EP_BaseClass_GetEDPointer()->EP_ED_AEWinRequestAddingExpense(nameOfExpense,typeOfExpense,amountOfExpense,descriptionOfExpense,ui->dateEditDateExpense->dateTime(),0);
}
/*Locals*/

/* Local function.*/
void ep_add_money::EP_AddMoney_ConnectToED()
{
   /*Connect to Event dispatcher.*/
   connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RM_AddMoneyStatus(int)),this,SLOT(EP_AM_AddedMoneyStatus(int)));
}

/*Slots*/
void ep_add_money::EP_AM_AddedMoneyStatus(int Status)
{
    /*Extend if you need further error handling.*/
    QMessageBox msg;
    switch (Status) {
        case -3:
           msg.setText("User not available.");
        break;
        case -2:
           msg.setText("Expense group not added correctly, please restart program and check DB connection.");
        break;
        case -1:
           msg.setText("Database is not connected ... Do you know what you are doing?");
        break;
        case 0:
           msg.setText("Money succesfully added!");
           /*Request welcome screen update of money.*/
           emit this->EP_BaseClass_GetEDPointer()->EP_ED_WlcScreenUpdateCurrentUserData();
        break;
        case 1:
           msg.setText("Expense group already exists ...");
        break;
        case 2:
           msg.setText("Email alredy in system ...");
        break;
    }
    msg.setWindowTitle("Add expense status");
    msg.exec();
}
