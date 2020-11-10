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
    void EP_UserData_Set_UserName(QString ProvidedUserName);
    void EP_UserData_Set_UserPassword(QString ProvidedUserPassword);
    void EP_UserData_Set_UserEmail(QString ProvidedUserEmail);
    /*Getters.*/
    QString EP_UserData_Get_UserName();
    QString EP_UserData_Get_UserPassword();
    QString EP_UserData_Get_UserEmail();
private:
    /*To DO:
     * Add here the containers necessary to update GUI report and all User data that will be provided to and from the GUI.
    */
    QString UserName;
    QString UserPassword;
    QString UserEmail;

signals:


private slots:
    void EP_UserData_GUI_RegisterData();
};

#endif // EP_USERDATA_H
