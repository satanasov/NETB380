#include <QDateTime>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QFrame>
#include "ep_show_report.h"
#include "ui_ep_show_report.h"

ep_show_report::ep_show_report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_show_report)
{
    ui->setupUi(this);
    /*/*Add VBoxLayout to the scrollArea.*/
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(1, 1, 1, 1);
    mainLayout->setSpacing(0);
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
    ui->labelDefaultUser->setText("Username: " + this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_LogUserName());
    /*Get current time and date for report generation.*/
    QDateTime dateANDtime = QDateTime::currentDateTime();
    QString dateTime = dateANDtime.currentDateTime().toString();
    QString final_date = "Current date is: " + dateTime;
    ui->label_3->setText(final_date);
    /*Indexes in reportData.*/
    int arrayIndexesInDataReport[5] = {4,6,3,255,7}; // 255 should be subsitute with the currency type of the expense.
    /*Start of report first column of */
    QString firstRow[5] = {"Name","Type","Amount","Currency Type","Date"};
    /*Process all expenses/incomes only if they are available. */
    if(false == reportData.isEmpty())
    {
        for(int i = -1; i < reportData.size(); i++)
        {
            /*Create widget container.*/
            QWidget *newWidgetContainer = new QWidget;
            /*Create horizontal box layout.*/
            QHBoxLayout *labelLayout = new QHBoxLayout;
            labelLayout->setContentsMargins(0, 0, 0, 0);
            labelLayout->setSpacing(0);
            for(int j = 0; j < 5; j++)
            {
                /*Name of expense.*/
                QLabel *label = new QLabel();
                label->setMinimumSize(100,25);
                label->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
                /*Add first row name of columns*/
                if(-1 == i)
                {
                    /*Take name columns from arrayIndexesInDataReport of names.*/
                    label->setText(firstRow[j]);
                    label->setStyleSheet("QLabel { background-color : orange; color : black; }");
                }
                else if(arrayIndexesInDataReport[j] == 255)
                {
                    /*TO DO: Here should be the currency type.*/
                    label->setText("BGN");
                }
                else if(arrayIndexesInDataReport[j] == 7)
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
                    label->setText(reportData.at(i).at(arrayIndexesInDataReport[j]));
                }
                /*Make center alignment*/
                label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
                /*Add label to layout*/
                labelLayout->addWidget(label);

                /*Set to the container widget all gathered Qlabels.*/
                newWidgetContainer->setLayout(labelLayout);
                /*Add to the scrollAreaReport.*/
                ui->scrollAreaReport->widget()->layout()->addWidget(newWidgetContainer);
            }
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
        label->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
        label->setText("No data to present. Please firstly add the requested data for report.");
        label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        labelLayout->addWidget(label);
        /*Set to the container widget all gathered Qlabels.*/
        newWidgetContainer->setLayout(labelLayout);
        /*Add to the scrollAreaReport.*/
        ui->scrollAreaReport->widget()->layout()->addWidget(newWidgetContainer);
    }
}
