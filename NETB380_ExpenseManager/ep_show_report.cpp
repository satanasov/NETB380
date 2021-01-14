#include <QDateTime>
#include <QSpacerItem>
#include "ep_show_report.h"
#include "ui_ep_show_report.h"

ep_show_report::ep_show_report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_show_report)
{
    ui->setupUi(this);
}

ep_show_report::~ep_show_report()
{
    delete ui;
}

/*Function to process reportData.*/
void ep_show_report::EP_ShowReport_ProcessReport(QList<QList<QString>> reportData)
{
    /*TO DO get real money aval.*/
    ui->labelAmountOfMoney->setText("Your current amount is: " + this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserData().at(0).at(4) + " BGN");
    /*Set current user*/
    ui->labelDefaultUser->setText("Name: " + this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_LogUserName());
    /*Get current time and date for report generation.*/
    QDateTime dateANDtime = QDateTime::currentDateTime();
    QString dateTime = dateANDtime.currentDateTime().toString();
    ui->label_3->setText(dateTime);
    /*Add expenses to */
    for(int i = 0; i< reportData.size(); i++)
    {
        /*Name of expense.*/
        QLabel *label = new QLabel(this);
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setText(reportData.at(0).at(4));
        label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        /*Type of expense.*/
        QLabel *label1 = new QLabel(this);
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setText(reportData.at(0).at(6));
        label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        /*Price of expense*/
        QLabel *label2 = new QLabel(this);
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setText(reportData.at(0).at(3));
        label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        /*Currency of expense.*/
        QLabel *label3 = new QLabel(this);
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setText("BGN");
        label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        /*Date of expense.*/
        QDateTime timestamp;
        timestamp.setTime_t(reportData.at(0).at(7).toUInt());
        QString expense_date = timestamp.toString();
        QLabel *label4 = new QLabel(this);
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setText(expense_date);
        label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);

        /*Configure gridLayout*/
//        ui->gridLayout->setColumnMinimumWidth(4,4);
//        QSpacerItem *spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
//        ui->gridLayout->addItem(spacerItem, 1, 1, 1, 1);
//        QSpacerItem *spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
//        ui->gridLayout->addItem(spacerItem1, 1, 0, 1, 1);
        ui->gridLayout->setSpacing(10);
        /*Add all widgets to grid layout TO DO FIX THIS SHIT :D.*/
        ui->gridLayout->addWidget(label,i,0,1,1);
        ui->gridLayout->addWidget(label1,i,1,1,1);
        ui->gridLayout->addWidget(label2,i,2,1,1);
        ui->gridLayout->addWidget(label3,i,3,1,1);
        ui->gridLayout->addWidget(label4,i,4,1,1);
    }
}
