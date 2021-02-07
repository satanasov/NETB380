#include "ep_other.h"
#include "ui_ep_other.h"
#include <QDateTime>

ep_other::ep_other(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_other)
{
    ui->setupUi(this);
    QDate date = QDate::currentDate();
    ui->dateTimeEditFrom->setDate(date);
    ui->dateTimeEditTo->setDate(date);
}

ep_other::~ep_other()
{
    delete ui;
}

void ep_other::on_pushButtonSearch_clicked()
{
    QList<QString> info;
    /*From time.*/
    QDateTime from;
    from = ui->dateTimeEditFrom->dateTime();
    from.setTimeSpec(Qt::UTC);
    int UTC_TimeFrom = from.toTime_t();
    /*To time.*/
    QDateTime to;
    to = ui->dateTimeEditTo->dateTime();
    to.setTimeSpec(Qt::UTC);
    int UTC_TimeTo = to.toTime_t();
    /*Append information to qlist and emit signal to generate report*/
    info.append(QString::number(UTC_TimeFrom));
    info.append(QString::number(UTC_TimeTo));

    /*Emit signal*/
    if(this->typeOfOther == 0)
    {
        emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_EXPENSE_CUSTOM_TIME,info);
    }
    else
    {
        emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_INCOME_CUSTOM,info);
    }
    /*Close window.*/
    this->~ep_other();
}
