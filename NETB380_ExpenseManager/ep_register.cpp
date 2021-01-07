#include <QMessageBox>
#include "ep_register.h"
#include "ui_ep_register.h"
#include "ep_db_wrapper.h"


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
     connect(this, SIGNAL(EP_Register_registerDialogFilledCorrectly()),this,SLOT(EP_Register_Save_Data_In_UserData()));
}

ep_register::~ep_register()
{
    delete ui;
}

/*LOCAL FUNCTIONS*/
void ep_register::on_pushButtonRegister_clicked()
{
    int WhichFieldIsEmpty = 0; // Init value.
    bool ErrorInField = false;
    //todo
    /*
        when databese is connected
        -check if username already exists
        -check if email is a valid one
        -make a new account
    */
    /**/
    for(WhichFieldIsEmpty; WhichFieldIsEmpty <= 4; WhichFieldIsEmpty++)
    {
        if(true == (ErrorInField = this->IsLineEditEmptyOrDefault(WhichFieldIsEmpty)))
        {
            CreateWarningDialog(WhichFieldIsEmpty);
            break;
        }
    }

    if(false == ErrorInField)
    {
      /*Emit signal that data is filled correctly and gather it in UserData object.*/
       emit EP_Register_registerDialogFilledCorrectly();
    }

    //QMessageBox::information(this, "See todo", "register"); //testing purpose
}

bool ep_register::IsLineEditEmptyOrDefault(int FieldType)
{
    /*Check if register field is empty.*/
    QString defaultValue = "";
    QString Field = "";
    bool PasswordConsistency = true;

    switch (FieldType)
    {
        case 0:
        {
            defaultValue = "Enter a username";
            Field = ui->RegisterUsername->text();
            break;
        }
        case 1:
        {
            defaultValue = "Enter a password";
            Field = ui->RegisterPassword->text();
            break;
        }
        case 2:
        {
            defaultValue = "Repeat the password";
            Field = ui->RegisterRepeat->text();
            break;
        }
        case 3:
        {
            defaultValue = "Not Used in this check!";
            Field = "Not Used";
            if((QString)ui->RegisterPassword->text() == (QString)ui->RegisterRepeat->text())
            {
                PasswordConsistency = true;
            }
            else
            {
                PasswordConsistency = false;
            }
            break;
        }
        case 4:
        {
            defaultValue = "Enter an email";
            Field = ui->RegisterEmail->text();
            break;
        }
    default:
        {
            defaultValue = "ERROR";
            break;
        }
    }

    if(((true == Field.isEmpty()) || (Field == defaultValue) || (defaultValue == "ERROR")) || (PasswordConsistency == false))
    {
        return true;
    }
    else
    {
        return false;
    }
}

 void ep_register::CreateWarningDialog(int FieldType)
{
     switch (FieldType)
     {
         case 0:
         {
             QMessageBox::information(this, "Warning!", "Please enter Username!");
             break;
         }
         case 1:
         {
             QMessageBox::information(this, "Warning!", "Please enter password!");
             break;
         }
         case 2:
         {
             QMessageBox::information(this, "Warning!", "Repeated password field is empty!");
             break;
         }
         case 3:
         {
             QMessageBox::information(this, "Warning!", "The two passwords are not matching!");
             break;
         }
         case 4:
         {
             QMessageBox::information(this, "Warning!", "Please enter e-mail!");
             break;
         }
     default:
         {
            // defaultValue = "ERROR";
            QMessageBox::information(this, "Warning", "ERROR, Checkk all fields!");
            break;
         }
     }
}

/*SLOT*/
void ep_register::EP_Register_Save_Data_In_UserData()
{
    /*Take Email from registration window.*/
    this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Set_RegUserEmail(ui->RegisterEmail->text());
    /*Take User name from registration window.*/
    this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Set_RegUserName(ui->RegisterUsername->text());
    /*Take User name from registration window.*/
    this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Set_RegUserPassword(ui->RegisterPassword->text());
    /*Close register window.*/
    this->close();
    /*Emit signal that registration is requested on DB side.*/
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RegWinRegistrationRequest();
}
