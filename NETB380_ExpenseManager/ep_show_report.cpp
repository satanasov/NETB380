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
