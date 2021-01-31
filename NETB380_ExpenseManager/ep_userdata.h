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
    void EP_UserData_Set_ActiveUserId(int saveThisID);
    void EP_UserData_Set_activeUserData(QList<QList<QString>> setThisData);
    void EP_UserData_Set_activeUserExpGroups(QList<QList<QString>> setThisData);
    /*Getters.*/
    QString EP_UserData_Get_RegUserName();
    QString EP_UserData_Get_RegUserPassword();
    QString EP_UserData_Get_RegUserEmail();
    QString EP_UserData_Get_LogUserName();
    QString EP_UserData_Get_LogUserPassword();
    int EP_UserData_Get_ActiveUserId();
    QList<QList<QString>> EP_UserData_Get_activeUserData();
    QList<QList<QString>> EP_UserData_Get_activeUserExpGroups();

private:
    QString RegUserName;
    QString RegUserPassword;
    QString RegUserEmail;
    QString LogUserName;
    QString LogUserPassword;
    int ActiveUserId;
    QList<QList<QString>> activeUserData;
    QList<QList<QString>> activeUserExpGroups;

signals:

private slots:

};

#endif // EP_USERDATA_H
