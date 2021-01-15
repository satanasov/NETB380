#include <QTimer>
#include <QDateTime>
#include <QMutex>
#include "ep_welcome.h"
#include "ui_ep_welcome.h"

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

void ep_welcome::EP_WelcomeScreen_ConnectToED()
{
    /*All connections to ED to be made here.*/
    //connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMWlcScreen_UpdateUserNameAndAmount(QString, QString)),this,SLOT(EP_WelcomeScreen_InitValues(QString, QString)));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMWlcScreen_GenerateTodayReport(QList<QList<QString>>)),this,SLOT(generateTodayReport(QList<QList<QString>>)));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMWlcScreen_UpdateCurrentUserAmount()),this,SLOT(updateCurrentUserAmount()));
}
/**/
void ep_welcome::EP_WelcomeScreen_InitValues()
{
   /**/
   QString amount = this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserData().at(0).at(4);
   QString nameToDiplay = this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_LogUserName();
   /**/
   ui->labelWelcome->setText("Welcome back: " + nameToDiplay);
   ui->labelBalance->setText("Your current amount is: " + amount + " BGN");
}

void ep_welcome::updateCurrentUserAmount()
{
    /**/
    QString amount = this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserData().at(0).at(4);
    /**/
    ui->labelBalance->setText("Your current amount is: " + amount + " BGN");
}

void ep_welcome::on_pushButtonAddMoney_clicked()
{
    ep_ad_m = new ep_add_money(this);
    ep_ad_m->show();
}

void ep_welcome::on_pushButtonNewExpense_clicked()
{
    ep_ad_e = new ep_add_expense(this);
    ep_ad_e -> EP_BaseClass_SetUserDataPointer(this->EP_BaseClass_GetUserDataPointer());
    ep_ad_e -> EP_BaseClass_SetEventDispatcherPointer(this->EP_BaseClass_GetEDPointer());
    ep_ad_e ->EP_AddExpense_ConnectToED();
    ep_ad_e->show();
}

void ep_welcome::on_pushButtonToday_clicked()
{
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport();
}

void ep_welcome::generateTodayReport(QList<QList<QString>> queryResult)
{
    //today
    ep_sh_r = new ep_show_report(this);
    ep_sh_r->EP_BaseClass_SetEventDispatcherPointer(this->EP_BaseClass_GetEDPointer());
    ep_sh_r->EP_BaseClass_SetUserDataPointer(this->EP_BaseClass_GetUserDataPointer());
    /*Process query result.*/
    ep_sh_r->EP_ShowReport_ProcessReport(queryResult);
    /*Request report.*/
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
