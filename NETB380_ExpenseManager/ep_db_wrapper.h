#ifndef EP_DB_WRAPPER_H
#define EP_DB_WRAPPER_H

#include <QString>
#include <QList>
#include <QSql>
#include <QObject>

class EP_DB_Wrapper : public QObject
{
    Q_OBJECT
public:
    void openDB(QString hostname, QString username, QString password, QString dbname);
    void closeDB();
    void deployTables();
    void dropTables();
    int registerUser(QString username, QString password, QString email);
    int loginUser(QString username, QString password);

public slots:
    //void registerUserSlot(QString username, QString password, QString email);
   // void registerUserSlot();
};

#endif // EP_DB_WRAPPER_H
