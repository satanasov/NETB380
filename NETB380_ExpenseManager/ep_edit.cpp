#include "ep_edit.h"
#include "ui_ep_edit.h"
#include <QMessageBox>

ep_edit::ep_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_edit)
{
    ui->setupUi(this);
}

//todo get values from the selected expense

ep_edit::~ep_edit()
{
    delete ui;
}
