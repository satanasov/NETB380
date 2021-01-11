#include <QTimer>
#include <QDateTime>
#include <QMutex>
#include "ep_welcome.h"
#include "ui_ep_welcome.h"

ep_welcome::ep_welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_welcome)
{
    ui->setupUi(this);
    /*Set Timer to update the clock of the program.*/
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start();
    /*Connect comboBox signals.*/
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(EP_WlcWin_GetComboBoxIndex(int)));
}

ep_welcome::~ep_welcome()
{
    delete ui;
}

/**/
void ep_welcome::updateTime()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    QString time_text = "Time : " + time.toString("hh : mm : ss");
    QString date_text = "Date : " + date.toString();
    ui->labelTime->setText(time_text);
    ui->labelDate->setText(date_text);
}

/**/
void ep_welcome::EP_WelcomeScreen_Initialize()
{
    /*Initialize welcome screen.*/
    ui->labelWelcome->setText("Welcome : " + this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_LogUserName());
    QString currentBalance = ui->comboBox->currentText();
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_WelcWinRequestCurrentBalance(EP_CustomFunctions::translateStringToCurrency(currentBalance));
    /*Add balance from DB.*/
}

void ep_welcome::on_pushButtonAddMoney_clicked()
{
    ep_ad_m = new ep_add_money(this);
    ep_ad_m->EP_BaseClass_SetEventDispatcherPointer(this->EP_BaseClass_GetEDPointer());
    ep_ad_m->EP_Add_Money_connectToED();
    ep_ad_m->show();
}

void ep_welcome::on_pushButtonNewExpense_clicked()
{
    ep_ad_e = new ep_add_expense(this);
    ep_ad_e->show();
}

void ep_welcome::on_pushButtonToday_clicked()
{
    //today
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->show();
}

void ep_welcome::on_pushButtonWeek_clicked()
{
    //this week
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->show();
}

void ep_welcome::on_pushButtonMonth_clicked()
{
    //this month
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->show();
}

void ep_welcome::on_pushButtonYear_clicked()
{
    //this year
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->show();
}

void ep_welcome::on_pushButtonAllTime_clicked()
{
    //all time
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->show();
}

void ep_welcome::on_pushButtonCustom_clicked()
{
    //custom ???????
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->show();
}

void ep_welcome::on_pushButtonTransport_clicked()
{
    //transport
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->show();
}

void ep_welcome::on_pushButtonFood_clicked()
{
    //food
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->show();
}

void ep_welcome::on_pushButtonClothes_clicked()
{
    //clothes
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->show();
}

void ep_welcome::on_pushButtonUtility_clicked()
{
    //utility
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->show();
}

void ep_welcome::on_pushButtonBank_clicked()
{
    //bank
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->show();
}

void ep_welcome::on_pushButtonOther_clicked()
{
    //other
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->show();
}

/*SLOT: Update currentbalance on welcome screen.*/
void ep_welcome::EP_WlcWin_UpdateCurrency(EP_Currencies currentCurrency, QString valueToDisplay)
{
    ui->labelBalance->setText(EP_CustomFunctions::defaultWelcomeScreenCurrency + valueToDisplay);
    /*Change to appropriate currency.*/
    ui->comboBox->setCurrentText(EP_CustomFunctions::translateCurrencyToString(currentCurrency));
}

/*Local function for ED connection.*/
void ep_welcome::EP_WelcomeScreen_ConnectoToED()
{
    /*Connect Welcome screen to Event Dispatcher.*/
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMWSUpdateCurrentCurrency(EP_Currencies,QString)),this, SLOT(EP_WlcWin_UpdateCurrency(EP_Currencies, QString )));
}

/*Slot connected to combobox changes.*/
void ep_welcome::EP_WlcWin_GetComboBoxIndex(int indexOfComboBox)
{
    QString GetCurrentCurrency = EP_CustomFunctions::possibleCurrency.at(indexOfComboBox);
    EP_Currencies CurrentWorkingCurrency = EP_CustomFunctions::translateStringToCurrency(GetCurrentCurrency);
    /*Value to be taken from current Active User.*/
    QString ValueToDisplay = EP_CustomFunctions::adapatCurrency(this->EP_BaseClass_GetUserDataPointer()->activeUserMoneyInBgn,EP_BGN, CurrentWorkingCurrency);

    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWSUpdateCurrentCurrency(CurrentWorkingCurrency,ValueToDisplay);
}
