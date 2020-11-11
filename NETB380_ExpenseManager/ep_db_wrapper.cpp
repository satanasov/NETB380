#include "ep_db_wrapper.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>

/**
 * Open DB connection
 * @brief SQLWrapper::openDB
 * @param host
 * @param username
 * @param pass
 * @param dbname
 */
void EP_DB_Wrapper::openDB(QString host, QString username, QString pass, QString dbname)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    qDebug()<<"Let me try and connect";
    db.setHostName(host);
    db.setUserName(username);
    db.setPassword(pass);
    //db.setPassword(QString("pacmmm"));
    db.setDatabaseName(dbname);
    if (db.open())
    {
        qDebug()<<"DB Is HERE!!!!";
    }
    else
    {
        // So if we are not connected - display error message.
        if (db.lastError().isValid()) {
            qDebug() << db.lastError().text();
           // QWidget *test = new QWidget();
          //  QPalette pallette;
          //  pallette.setColor(QPalette::Background, Qt::black);
          //  QMessageBox *error = new QMessageBox;
          //  error->setPalette(pallette);
          //  QString text = db.lastError().text();
          //  error->about(test, QObject::tr("DB Error detected"), QObject::tr(qPrintable(text)));
        }
    }


}
