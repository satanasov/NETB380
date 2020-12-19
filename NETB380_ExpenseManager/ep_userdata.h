#ifndef EP_USERDATA_H
#define EP_USERDATA_H

#include <QObject>
#include <QString>
#include <QDebug>

class EP_UserData : QObject
{
    Q_OBJECT
public:
    EP_UserData();
    ~EP_UserData();
    /*Setters.*/
    void EP_UserData_Set_RegUserName(QString ProvidedUserName);
    void EP_UserData_Set_RegUserPassword(QString ProvidedUserPassword);
    void EP_UserData_Set_RegUserEmail(QString ProvidedUserEmail);
    void EP_UserData_Set_LogUserName(QString ProvidedUserName);
    void EP_UserData_Set_LogUserPassword(QString ProvidedUserPassword);
    /*Getters.*/
    QString EP_UserData_Get_RegUserName();
    QString EP_UserData_Get_RegUserPassword();
    QString EP_UserData_Get_RegUserEmail();
    QString EP_UserData_Get_LogUserName();
    QString EP_UserData_Get_LogUserPassword();
private:
    /*To DO:
     * Add here the containers necessary to update GUI report and all User data that will be provided to and from the GUI.
    */
    QString RegUserName;
    QString RegUserPassword;
    QString RegUserEmail;
    QString LogUserName;
    QString LogUserPassword;

signals:

private slots:
    //void EP_UserData_GUI_RegisterData();
};

#endif // EP_USERDATA_H
