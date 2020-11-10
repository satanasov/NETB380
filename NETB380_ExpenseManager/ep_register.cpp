#include "ep_register.h"
#include "ui_ep_register.h"
#include <QMessageBox>

ep_register::ep_register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_register)
{
    ui->setupUi(this);

    ui->RegisterUsername->setPlaceholderText("Enter a username");
    ui->RegisterPassword->setPlaceholderText("Enter a password");
    ui->RegisterRepeat->setPlaceholderText("Repeat the password");
    ui->RegisterEmail->setPlaceholderText("Enter an email");
    //placeholders for register fields
}

ep_register::~ep_register()
{
    delete ui;
}

void ep_register::on_pushButtonRegister_clicked()
{
    //todo
    /*
        when databese is connected
        -check if username already exists
        -check if both passwords match
        -check if email is a valid one

        -make a new account
    */
    QMessageBox::information(this, "See todo", "register"); //testing purpose

}
