#include "ep_main.h"
#include "ui_ep_main.h"
#include "ep_reportmain_wrapper.h"
#include <QMessageBox>


EP_Main::EP_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EP_Main)
{
    ui->setupUi(this);

    ui->LogInUsername->setPlaceholderText("Enter your username");
    ui->LogInPassword->setPlaceholderText("Enter your password");
    //placeholders for log in fields

    ui->pushButtonConnectDB->setStyleSheet("color: #FF0000"); //red text alert of button
}

EP_Main::~EP_Main()
{
    delete ui;
}


void EP_Main::on_pushButtonLogIn_clicked()
{
    //todo
    //when db is connected log in or show error message
    QMessageBox::information(this, "See todo", "log"); //testing purpose
}

void EP_Main::on_pushButtonConnectDB_clicked()
{
    //todo connect DB
    QMessageBox::information(this, "See todo", "connect"); //testing purpose
}

void EP_Main::on_pushButtonCreateNewAccount_clicked()
{
    //todo Create new account in database
    //QMessageBox::information(this, "See todo", "create"); //testing purpose

    //hide(); don't think it's practical
    ep_reg = new ep_register(this); //needed in order to open reg window from main window
    ep_reg->show(); //show the reg window
}
