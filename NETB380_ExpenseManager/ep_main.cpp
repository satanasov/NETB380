#include "ep_main.h"
#include "ui_ep_main.h"
#include "ep_reportmain_wrapper.h"
#include "ep_db_settings.h"
#include <QMessageBox>


EP_Main::EP_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EP_Main)
{
    ui->setupUi(this);
    this->PointerToUserData = nullptr;
    ui->LogInUsername->setPlaceholderText("Enter your username");
    ui->LogInPassword->setPlaceholderText("Enter your password");
    //placeholders for log in fields

    ui->pushButtonConnectDB->setStyleSheet("color: #FF0000"); //red text alert of button
}

EP_Main::~EP_Main()
{
    delete ui;
}

void EP_Main::EP_Main_ConnectSlots_UserData()
{
    //connect(this,SIGNAL());
}

void EP_Main::on_pushButtonLogIn_clicked()
{
    QMutex mutex;
    /*Lock UserData object.*/
    mutex.lock();
    this->EP_Main_GetUserDataPointer()->EP_UserData_Set_LogUserName(ui->LogInUsername->text());
    this->EP_Main_GetUserDataPointer()->EP_UserData_Set_LogUserPassword(ui->LogInPassword->text());
    mutex.unlock();
    mutex.~QMutex();
}

void EP_Main::on_pushButtonConnectDB_clicked()
{
    //todo connect DB
    //QMessageBox::information(this, "See todo", "connect"); //testing purpose
    ep_db_set = new ep_db_settings();
    ep_db_set->show();
}

void EP_Main::on_pushButtonCreateNewAccount_clicked()
{
    //todo Create new account in database
    //QMessageBox::information(this, "See todo", "create"); //testing purpose

    //hide(); don't think it's practical
    ep_reg = new ep_register(this); //needed in order to open reg window from main window
    ep_reg->EP_Register_SetUserDataPointer(this->EP_Main_GetUserDataPointer());
    ep_reg->EP_Register_ConnectSlots_UserData();
    ep_reg->show(); //show the reg window
}

/*Set pointer to user data class.*/
void EP_Main::EP_Main_SetUserDataPointer(EP_UserData * UserDataPointer)
{
    this->PointerToUserData = UserDataPointer;
}

/*Get user data object location*/
EP_UserData* EP_Main::EP_Main_GetUserDataPointer()
{
    return this->PointerToUserData;
}
