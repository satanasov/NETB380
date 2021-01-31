#include <QTimer>
#include <QDateTime>
#include <QMutex>
#include "ep_welcome.h"
#include "ui_ep_welcome.h"
#include "ep_other.h"
#include "ep_expenestype_customfilter.h"
#include "ep_edit.h"

ep_welcome::ep_welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_welcome)
{
    /**/
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start();

}

ep_welcome::~ep_welcome()
{
    delete ui;
}

/*SLOT:Update time of welcome screen.*/
void ep_welcome::updateTime()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    QString time_text = "Time : " + time.toString("hh : mm : ss");
    QString date_text = "Date : " + date.toString();
    ui->labelTime->setText(time_text);
    ui->labelDate->setText(date_text);
}

/*FUCNTION:*/
void ep_welcome::EP_WelcomeScreen_ConnectToED()
{
    /*All connections to ED to be made here.*/
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMWlcScreen_GenerateReport(QList<QList<QString>>,QString)),this,SLOT(generateReport(QList<QList<QString>>,QString)));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMWlcScreen_UpdateCurrentUserAmount()),this,SLOT(updateCurrentUserAmount()));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMWlcScreen_OpenAddExpenseWindow()),this,SLOT(openAddExpenseWindow()));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMWlcScreen_OpenCustomExpTypeFilter()),this,SLOT(openCustomExpFilterWindow()));
}

/*Get current user information: Name and ammoint available.*/
void ep_welcome::EP_WelcomeScreen_InitValues()
{
   /**/
   QString amount = this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserData().at(0).at(4);
   QString nameToDiplay = this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_LogUserName();
   /**/
   ui->labelWelcome->setText("Welcome back: " + nameToDiplay);
   ui->labelBalance->setText("Your current amount is: " + amount + " BGN");
}

/*Update ammount in welcome screen.*/
void ep_welcome::updateCurrentUserAmount()
{
    /*Get available user ammount.*/
    QString amount = this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserData().at(0).at(4);
    /*Set text to Welcome screen.*/
    ui->labelBalance->setText("Your current amount is: " + amount + " BGN");
}

void ep_welcome::on_pushButtonAddMoney_clicked()
{
    ep_ad_m = new ep_add_money(this);
    ep_ad_m -> EP_BaseClass_SetUserDataPointer(this->EP_BaseClass_GetUserDataPointer());
    ep_ad_m -> EP_BaseClass_SetEventDispatcherPointer(this->EP_BaseClass_GetEDPointer());
    ep_ad_m ->EP_AddMoney_ConnectToED();
    ep_ad_m->show();
}

void ep_welcome::on_pushButtonNewExpense_clicked()
{
    /*Get current user exp groups for combobox.update.*/
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_updateCurrentUserExpGroups(0);
}
void ep_welcome::generateReport(QList<QList<QString>> queryResult, QString typeOfReport)
{
    //today
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->EP_BaseClass_SetEventDispatcherPointer(this->EP_BaseClass_GetEDPointer());
    ep_sh_r->EP_BaseClass_SetUserDataPointer(this->EP_BaseClass_GetUserDataPointer());
    /*Process query result.*/
    ep_sh_r->EP_ShowReport_ProcessReport(queryResult);
    ep_sh_r->setWindowTitle("Type of report : " + typeOfReport);
    /*Request report.*/
    ep_sh_r->show();
}

void ep_welcome::openAddExpenseWindow()
{
    ep_ad_e = new ep_add_expense(this);
    ep_ad_e -> EP_BaseClass_SetUserDataPointer(this->EP_BaseClass_GetUserDataPointer());
    ep_ad_e -> EP_BaseClass_SetEventDispatcherPointer(this->EP_BaseClass_GetEDPointer());
    ep_ad_e -> EP_AddExpense_ConnectToED();
    ep_ad_e ->EP_AE_InitializeComboBoxValues();
    ep_ad_e->show();
}

void ep_welcome::openCustomExpFilterWindow()
{
    /*Send to report main request for all available exp groups.*/
    EP_ExpenesType_CustomFilter *CustomFilter = new EP_ExpenesType_CustomFilter();
    CustomFilter->EP_BaseClass_SetEventDispatcherPointer(this->EP_BaseClass_GetEDPointer());
    CustomFilter->EP_BaseClass_SetUserDataPointer(this->EP_BaseClass_GetUserDataPointer());
    CustomFilter->UpdateComboList();
    CustomFilter->exec();
}

/*Today all expense..*/
void ep_welcome::on_pushButtonToday_clicked()
{
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_EXPENSE_TODAY_EXPENSE_TIME,Empty);
}
/**/
void ep_welcome::on_pushButtonWeek_clicked()
{
    //this week
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_EXPENSE_THIS_WEEK_TIME,Empty);
}

void ep_welcome::on_pushButtonMonth_clicked()
{
    //this month
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_EXPENSE_THIS_MONTH_TIME,Empty);
}

void ep_welcome::on_pushButtonYear_clicked()
{
    //this year
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_EXPENSE_THIS_YEAR_TIME,Empty);
}

void ep_welcome::on_pushButtonAllTime_clicked()
{
    //all time
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_EXPENSE_ALL_TIME_TIME,Empty);
}

void ep_welcome::on_pushButtonCustom_clicked()
{
    //custom ???????
    ep_other *customTime = new ep_other();
    customTime->EP_BaseClass_SetEventDispatcherPointer(this->EP_BaseClass_GetEDPointer());
    customTime->exec();
}

void ep_welcome::on_pushButtonTransport_clicked()
{
    //transport
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_EXPENSE_TRANSPORT_TYPE,Empty);
}

void ep_welcome::on_pushButtonFood_clicked()
{
    //food
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_EXPENSE_FOOD_TYPE,Empty);
}

void ep_welcome::on_pushButtonClothes_clicked()
{
    //clothes
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_EXPENSE_CLOTHES_TYPE,Empty);
}

void ep_welcome::on_pushButtonUtility_clicked()
{
    //utility
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_EXPENSE_UTILITY_TYPE,Empty);
}

void ep_welcome::on_pushButtonBank_clicked()
{
    //bank
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_EXPENSE_BANK_TYPE,Empty);
}

void ep_welcome::on_pushButtonOther_clicked()
{
    /*Request update.*/
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_updateCurrentUserExpGroups(1);
}

void ep_welcome::on_pushButtonTodayIncomes_clicked()
{
    //bank
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_INCOME_TODAY,Empty);
}

void ep_welcome::on_pushButtonWeekIncomes_clicked()
{
    //bank
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_INCOME_THIS_WEEK,Empty);
}

void ep_welcome::on_pushButtonMonthIncomes_clicked()
{
    //bank
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_INCOME_THIS_MONTH,Empty);
}

void ep_welcome::on_pushButtonYear_2_clicked()
{
    //bank
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_INCOME_THIS_YEAR,Empty);
}

void ep_welcome::on_pushButtonAllTimeIncomes_clicked()
{
    //bank
    QList<QString> Empty;
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_INCOME_ALL_TIME,Empty);
}

void ep_welcome::on_pushButtonCustomIncomes_clicked()
{
    ep_other *customTime = new ep_other();
    customTime->EP_BaseClass_SetEventDispatcherPointer(this->EP_BaseClass_GetEDPointer());
    customTime->exec();
}
