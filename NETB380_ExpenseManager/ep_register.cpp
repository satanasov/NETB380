#include "ep_register.h"
#include "ui_ep_register.h"
#include <QMessageBox>
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
    this->PointerToUserData = nullptr;
    //placeholders for register fields
}

ep_register::~ep_register()
{
    delete ui;
}

void ep_register::on_pushButtonRegister_clicked()
{
    int WhichFieldIsEmpty = 0; // Init value.
    bool ErrorInField = false;
    //todo
    /*
        when databese is connected
        -check if username already exists
        -check if both passwords match
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
       emit registerDialogFilledCorrectly();
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

void ep_register::EP_Register_SetUserDataPointer(EP_UserData *UserDataPointer)
{
    this->PointerToUserData = UserDataPointer;
}

EP_UserData* ep_register::EP_Register_GetUserDataPointer()
{
    return this->PointerToUserData;
}

void ep_register::EP_Register_ConnectSlots_UserData()
{
    /*Make save in user data.*/
    connect(this, SIGNAL(registerDialogFilledCorrectly()),this,SLOT(save_Data_In_UserData()));
    connect(this, SIGNAL(registerDialogFilledCorrectly()), this->sql, SLOT(registerUserSlot()));
}

void ep_register::save_Data_In_UserData()
{
    /*Create QMutex object to lock the memory for writing into UserData object.*/
    QMutex mutex;
    /*Lock UserData object.*/
    mutex.lock();
    /*Take Email from registration window.*/
    this->PointerToUserData->EP_UserData_Set_UserEmail(ui->RegisterEmail->text());
    /*Take User name from registration window.*/
    this->PointerToUserData->EP_UserData_Set_UserName(ui->RegisterUsername->text());
    /*Take User name from registration window.*/
    this->PointerToUserData->EP_UserData_Set_UserPassword(ui->RegisterPassword->text());
    /*Unlock UserData object.*/
    mutex.unlock();
    /*Destroy mutex object.*/
    mutex.~QMutex();
    /*Show into the Application Output that the data is acquired into the UserData object.*/
    qDebug() << this->PointerToUserData->EP_UserData_Get_UserEmail();
    qDebug() << this->PointerToUserData->EP_UserData_Get_UserName();
    qDebug() << this->PointerToUserData->EP_UserData_Get_UserPassword();
    this->close();
}
