#include "ep_userdata.h"
/*Constructor and Destructor*/
EP_UserData::EP_UserData()
{
    /*Initialize user data information.*/
    this->UserEmail = "";
    this->UserName = "";
    this->UserPassword = "";
}

EP_UserData::~EP_UserData()
{
    delete this;
}

/*Setters*/
void EP_UserData::EP_UserData_Set_UserName(QString ProvidedUserName)
{
    this->UserName = ProvidedUserName;
}

void EP_UserData::EP_UserData_Set_UserPassword(QString ProvidedUserPassword)
{
    this->UserPassword = ProvidedUserPassword;
}

void EP_UserData::EP_UserData_Set_UserEmail(QString ProvidedUserEmail)
{
    this->UserEmail = ProvidedUserEmail;
}

/* Getters*/
QString EP_UserData::EP_UserData_Get_UserName()
{
    return this->UserName;
}

QString EP_UserData::EP_UserData_Get_UserPassword()
{
    return this->UserPassword;
}
QString EP_UserData::EP_UserData_Get_UserEmail()
{
     return this->UserEmail;
}

/*Slots*/
void EP_UserData::EP_UserData_GUI_RegisterData()
{
    qDebug() << "User data slot connected properly.";
}
