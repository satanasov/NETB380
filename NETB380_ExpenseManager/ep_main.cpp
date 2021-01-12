#include <QMessageBox>
#include <QThread>
#include "ep_main.h"
#include "ui_ep_main.h"
#include "ep_reportmain_wrapper.h"
#include "ep_db_settings.h"
#include "ep_welcome.h"

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

void EP_Main::EP_Main_ConnectSlots_EventDispatcher()
{
    /*Make all connections between Event Dispatcher and Main window slots..*/
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMRegistrationStatus(int)), this, SLOT(EP_Main_RegistrationStatusWindow(int)));
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMLoginStatus(int)),this, SLOT(EP_Main_LoginStatusWindow(int)));
}

void EP_Main::on_pushButtonLogIn_clicked()
{
    /*Check IF:
     * - UserName is empty.
     * - Password is empty.
    */
    if((ui->LogInUsername->text() == "" || ui->LogInUsername->text() == " ")
            ||
        (ui->LogInPassword->text() == "" || ui->LogInPassword->text() == " ")
            )
    {
        /*Display error message.*/
        QMessageBox msg;
        msg.setText("Username or Password Empty!");
        msg.setWindowTitle("Log-In error status");
        msg.exec();
    }
    else
    {
        /*Save log-in data.*/
        this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Set_LogUserName(ui->LogInUsername->text());
        this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Set_LogUserPassword(ui->LogInPassword->text());
        /*Request log-in to DB.*/
        emit this->EP_BaseClass_GetEDPointer()->EP_ED_LogWinLogInRequest();
    }
}

void EP_Main::on_pushButtonConnectDB_clicked()
{
    //QMessageBox::information(this, "See todo", "connect"); //testing purpose
    ep_db_set = new ep_db_settings();
    ep_db_set->EP_BaseClass_SetEventDispatcherPointer(this->EP_BaseClass_GetEDPointer());
    ep_db_set->EP_DB_Settings_connectToEventDispatcher();
    ep_db_set->show();
}

void EP_Main::on_pushButtonCreateNewAccount_clicked()
{
    //todo Create new account in database
    //QMessageBox::information(this, "See todo", "create"); //testing purpose

    //hide(); don't think it's practical
    ep_reg = new ep_register(this); //needed in order to open reg window from main window
    ep_reg->EP_BaseClass_SetUserDataPointer(this->EP_BaseClass_GetUserDataPointer());
    ep_reg->EP_BaseClass_SetEventDispatcherPointer(this->EP_BaseClass_GetEDPointer());
    ep_reg->show(); //show the reg window
}

void EP_Main::EP_Main_RegistrationStatusWindow(int RegStatus)
{
    QMessageBox msg;
    switch (RegStatus) {
        case -2:
           msg.setText("Unknown ERROR ... you should never see this.");
        break;
        case -1:
           msg.setText("Database is not connected ... Do you know what you are doing?");
        break;
        case 0:
           msg.setText("Registration was successfull!");
        break;
        case 1:
           msg.setText("User alredy exists ...");
        break;
        case 2:
           msg.setText("Email alredy in system ...");
        break;
    }
    msg.setWindowTitle("Registration status");
    msg.exec();
}

void EP_Main::EP_Main_LoginStatusWindow(int LogStatus)
{
    /*Create WelcomeScreen Object.*/
    ep_welcome WelcomeScreen;
    QMessageBox msg;
    switch (LogStatus) {
        case -4:
            msg.setText("Wrong password!");
        break;
        case -3:
            msg.setText("User does not exist. Please register in DataBase!");
        break;
        case -2:
           msg.setText("Unknown ERROR ... you should never see this.");
        break;
        case -1:
           msg.setText("Database is not connected ... Do you know what you are doing?");
        break;
        case 0:
            /*Log-In is successfull*/
            this->~EP_Main();
            /* Execute welocme screen.*/
            WelcomeScreen.EP_BaseClass_SetEventDispatcherPointer(this->EP_BaseClass_GetEDPointer());
            WelcomeScreen.EP_BaseClass_SetUserDataPointer(this->EP_BaseClass_GetUserDataPointer());
            WelcomeScreen.EP_WelcomeScreen_ConnectToED();
            WelcomeScreen.EP_WelcomeScreen_InitValues();
            /*Initialize Function to update welcomescreen.*/
            WelcomeScreen.exec();
            /* Create all necessary connections here and cofiguration for WelcomeScreen.*/
            // TO DO.
            /**/
        break;
        default:
            msg.setText("Unknown ERROR ... you should never see this.");
        break;
    }
    /*Check-if Log-in Status message object is still available.*/
    if(LogStatus != 0)
    {
        /*Set dialog name and execute it.*/
        msg.setWindowTitle("Log-In status");
        msg.exec();
    }
}
