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

void ep_edit::on_pushButtonExpenseAddEdit_clicked()
{
    //save edited expense
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Edit", "Are you sure you want to save current expense?",
                                  QMessageBox::Yes|QMessageBox::No);
}

void ep_edit::on_pushButtonDeleteEdit_clicked()
{
    //delete the whole entry
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete current expense?",
                                  QMessageBox::Yes|QMessageBox::No);
}

