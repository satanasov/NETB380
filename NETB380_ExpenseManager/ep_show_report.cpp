#include <QDateTime>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QFrame>
#include "ep_show_report.h"
#include "ui_ep_show_report.h"
#include "ep_custom_menu.h"

ep_show_report::ep_show_report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_show_report)
{
    ui->setupUi(this);
    /*/*Add VBoxLayout to the scrollArea.*/
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop);
   // mainLayout->set
    ui->scrollAreaReport->widget()->setLayout(mainLayout);
    /*Default background color for all objects in report.*/
    //this->setStyleSheet("QDialog::item{background-color: grey}");
}

ep_show_report::~ep_show_report()
{
    delete ui;
}

/*Function to process reportData.*/
void ep_show_report::EP_ShowReport_ProcessReport(QList<QList<QString>> reportData)
{
    /*TO DO get real money aval.*/
    double AmountInThisRecord = 0;
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
            /*Create horizontal box layout.*/
            QHBoxLayout *labelLayout = new QHBoxLayout;
            labelLayout->setContentsMargins(0, 0, 0, 0);
            labelLayout->setSpacing(0);
            /*Make custom label function.*/
            EP_CustomLabel *LabelToStore = new EP_CustomLabel();
            LabelToStore->setLayout(labelLayout);
            LabelToStore->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
            LabelToStore->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            LabelToStore->setStyleSheet("*:hover{ background-color : rgb(132, 162, 174); style} ");
            LabelToStore->setMinimumSize(500,25);
            LabelToStore->setMaximumHeight(50);
            /*Add custom menu.*/
            LabelToStore->setContextMenuPolicy(Qt::CustomContextMenu);
            /*Index trought the data.*/
            for(int j = 0; j < 5; j++)
            {
                /*Name of expense.*/
                QLabel *label = new QLabel();
               //label->setVisible(false); // To do remove
                label->setMinimumSize(100,25);
                label->setFrameStyle(QFrame::Panel | QFrame::Plain);
                //label->setStyleSheet("QLabel { background-color : white; color : black; }");
                /*Add first row name of columns*/
                if(-1 == i)
                {
                    /*First row is not editable.*/
                    LabelToStore->setContextMenuPolicy(Qt::NoContextMenu);
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
                    timestamp.setTimeSpec(Qt::UTC);
                    timestamp.setTime_t(reportData.at(i).at(7).toUInt());                  
                    QString expense_date = timestamp.date().toString();
                    label->setText(expense_date);
                }
                else
                {
                    if(arrayIndexesInDataReport[j] == 3)
                    {
                        AmountInThisRecord += reportData.at(i).at(arrayIndexesInDataReport[j]).toDouble();
                    }
                    /*Take all other data.*/
                    label->setText(reportData.at(i).at(arrayIndexesInDataReport[j]));
                }
                /*Make center alignment*/
                label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
                /*Add label to layout*/
                labelLayout->addWidget(label);

                /*Set to the container widget all gathered Qlabels.*/
                LabelToStore->setLayout(labelLayout);
                /*Add to the scrollAreaReport.*/
                ui->scrollAreaReport->widget()->layout()->addWidget(LabelToStore);
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
    ui->labelAmountOfMoney->setText("Total amount in current report records is: " + QString::number(AmountInThisRecord) + " BGN");
}
