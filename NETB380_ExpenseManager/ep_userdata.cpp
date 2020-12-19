#include "ep_userdata.h"
/*Constructor and Destructor*/
EP_UserData::EP_UserData()
{
    /*Initialize user data information.*/
    this->RegUserEmail = "";
    this->RegUserName = "";
    this->RegUserPassword = "";
    this->LogUserName = "";
    this->LogUserPassword = "";
}

EP_UserData::~EP_UserData()
{
    delete this;
}

/*Setters*/
void EP_UserData::EP_UserData_Set_RegUserName(QString ProvidedUserName)
{
    this->RegUserName = ProvidedUserName;
}

void EP_UserData::EP_UserData_Set_RegUserPassword(QString ProvidedUserPassword)
{
    this->RegUserPassword = ProvidedUserPassword;
}

void EP_UserData::EP_UserData_Set_RegUserEmail(QString ProvidedUserEmail)
{
    this->RegUserEmail = ProvidedUserEmail;
}
/*Setters*/
void EP_UserData::EP_UserData_Set_LogUserName(QString ProvidedUserName)
{
    this->LogUserName = ProvidedUserName;
}

void EP_UserData::EP_UserData_Set_LogUserPassword(QString ProvidedUserPassword)
{
    this->LogUserPassword = ProvidedUserPassword;
}
/* Getters*/
QString EP_UserData::EP_UserData_Get_RegUserName()
{
    return this->RegUserName;
}

QString EP_UserData::EP_UserData_Get_RegUserPassword()
{
    return this->RegUserPassword;
}
QString EP_UserData::EP_UserData_Get_RegUserEmail()
{
     return this->RegUserEmail;
}
QString EP_UserData::EP_UserData_Get_LogUserName()
{
    return this->LogUserName;
}

QString EP_UserData::EP_UserData_Get_LogUserPassword()
{
    return this->LogUserPassword;
}


