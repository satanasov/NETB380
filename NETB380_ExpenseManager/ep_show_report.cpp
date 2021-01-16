#include <QDateTime>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QHBoxLayout>
#include "ep_show_report.h"
#include "ui_ep_show_report.h"

ep_show_report::ep_show_report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_show_report)
{
    ui->setupUi(this);
    /*/*Add VBoxLayout to the scrollArea.*/
    QVBoxLayout *mainLayout = new QVBoxLayout;
    ui->scrollAreaReport->widget()->setLayout(mainLayout);
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
    /*Indexes in reportData.*/
    int array[5] = {4,6,3,255,7}; // 255 should be subsitute with the currency type of the expense.
    /*Process all expenses/incomes only if they are available. */
    if(false == reportData.isEmpty())
    {
        for(int i = 0; i < reportData.size(); i++)
        {
            /*Create widget container.*/
            QWidget *newWidgetContainer = new QWidget;
            /*Create horizontal box layout.*/
            QHBoxLayout *labelLayout = new QHBoxLayout;
            /*Create Table widget item and add to table widget.*/
            for(int j = 0; j < 5; j++)
            {
                /*Name of expense.*/
                QLabel *label = new QLabel();
                label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                if(array[j] == 255)
                {
                    /*TO DO: Here should be the currency type.*/
                    label->setText("BGN");
                }
                else if(array[j] == 7)
                {
                    /*Date of expense-income.*/
                    QDateTime timestamp;
                    /*Get date of expense.*/
                    timestamp.setTime_t(reportData.at(i).at(7).toUInt());
                    QString expense_date = timestamp.date().toString();
                    label->setText(expense_date);
                }
                else
                {
                    /*Take all other data.*/
                    label->setText(reportData.at(i).at(array[j]));
                }
                /*Make center alignment*/
                label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
                /*Add label to layout*/
                labelLayout->addWidget(label);
            }
            /*Set to the container widget all gathered Qlabels.*/
            newWidgetContainer->setLayout(labelLayout);
            /*Add to the scrollAreaReport.*/
            ui->scrollAreaReport->widget()->layout()->addWidget(newWidgetContainer);

        }
    }
    else
    {
        /*Create widget container.*/
        QWidget *newWidgetContainer = new QWidget;
        /*Create horizontal box layout.*/
        QHBoxLayout *labelLayout = new QHBoxLayout;
        /**/
        QLabel *label = new QLabel();
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setText("No data to present. Please add the requested report data firstly.");
        label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        labelLayout->addWidget(label);
        /*Set to the container widget all gathered Qlabels.*/
        newWidgetContainer->setLayout(labelLayout);
        /*Add to the scrollAreaReport.*/
        ui->scrollAreaReport->widget()->layout()->addWidget(newWidgetContainer);
    }
}
