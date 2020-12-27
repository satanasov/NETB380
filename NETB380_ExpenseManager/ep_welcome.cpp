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
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start();
}

ep_welcome::~ep_welcome()
{
    delete ui;
}

void ep_welcome::updateTime()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    QString time_text = "Time : " + time.toString("hh : mm : ss");
    QString date_text = "Date : " + date.toString();
    ui->labelTime->setText(time_text);
    ui->labelDate->setText(date_text);
}

void ep_welcome::EP_WelcomeScreen_Initialize()
{
    /*Create QMutex object to lock the memory for writing into UserData object.*/
    QMutex mutex;
    /*Lock UserData object.*/
    mutex.lock();
    /*Take Email from registration window.*/
    ui->labelWelcome->setText("Welcome : " + this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_LogUserName());
    /*Add balance from DB.*/

    /*Unlock UserData object.*/
    mutex.unlock();
    /*Destroy mutex object.*/
    mutex.~QMutex();
}

void ep_welcome::on_pushButtonAddMoney_clicked()
{
    //add money dialog
}
