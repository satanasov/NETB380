#include "ep_db_wrapper.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include <QCryptographicHash>

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
    QSqlDatabase db = QSqlDatabase::database("appdb");
    qDebug() << db.isOpen();
    if (!db.isOpen())
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "appdb");
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

}

/**
 * Close DB connection
 * @brief EP_DB_Wrapper::closeDB
 */
void EP_DB_Wrapper::closeDB()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
}


/**
 * We will use this method to deply our tables :D (DUH!!!)
 * @brief EP_DB_Wrapper::deployTables
 */
void EP_DB_Wrapper::deployTables()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen())
    {
        // Create users_table (ep_users)
        db.exec("CREATE TABLE ep_users (id serial PRIMARY KEY, username VARCHAR (64) NOT NULL, username_crean VARCHAR (80) UNIQUE NOT NULL, password VARCHAR (60) NOT NULL, email VARCHAR (256) UNIQUE NOT NULL, name VARCHAR (512), reg_date NUMERIC, last_active NUMERIC, user_active smallint );");
        db.exec("CREATE TABLE ep_account_types(id serial PRIMARY KEY, type VARCHAR (64), description text);");
        db.exec("CREATE TABLE ep_currencies (id serial PRIMARY KEY, iso VARCHAR (8) UNIQUE NOT NULL, long_name VARCHAR (256));");
        db.exec("CREATE TABLE ep_expenses_groups (id serial PRIMARY KEY, uid NUMERIC, name VARCHAR (256), description TEXT");
        db.exec("CREATE TABLE ep_user_accounts (id serial PRIMARY KEY, uid NUMERIC, type NUMERIC, name VARCHAR (256), description TEXT, amount DECIMAL, currency NUMERICAL, added_at NUMERICAL, last_change NUMERICAL, is_active smallint");
        db.exec("CREATE TABLE ep_expenses_table (id serial PRIMARY KEY, uid NUMERIC, aid NUMERIC, type NUMERIC, amount DECIMAL, name VARCHAR (256), description TEXT, group_name NUMERIC, added_at NUMERIC, is_active smallint);");
        qDebug() << db.lastError().text();
    }
}

/**
 * We will use this method to drop all tables :D
 * @brief EP_DB_Wrapper::dropTables
 */
void EP_DB_Wrapper::dropTables()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen())
    {
        // Create users_table (ep_users)
        db.exec("DROP TABLE ep_users;");
        db.exec("DROP TABLE ep_account_types;");
        db.exec("DROP TABLE ep_currencies;");
        db.exec("DROP TABLE ep_expenses_groups;");
        db.exec("DROP TABLE ep_user_accounts;");
        db.exec("DROP TABLE ep_expenses_table;");
        qDebug() << db.lastError().text();
    }
}

/**
 * This is owr magical registration method :D
 * @brief EP_DB_Wrapper::registerUser
 * @param username
 * @param password
 * @param email
 * @return
 *
 * Return values:
 * 2 -> email exists
 * 1 -> user exists
 * 0 -> OK
 * -1 -> no connection to DB
 * -2 -> unknown error
 */
int EP_DB_Wrapper::registerUser(QString username, QString password, QString email)
{
    //Username should be normilized
    QString username_clean = username.toLower();
    QByteArray pswNsalt (password.toStdString().c_str()) ;
    pswNsalt.append("HAAGASFASDfasdfASDFWAERQ@#RASDFASDFQWFASDFASEFAS") ;
    QByteArray hashedSaltedPsw = QCryptographicHash::hash(pswNsalt, QCryptographicHash::Sha256).toHex() ;
    QSqlDatabase db = QSqlDatabase::database("appdb");
    if (db.isOpen())
    {
        qDebug() << "here be dragon ... puf";
        // Check for duplicate username
        // TODO: Use clean username and use username_clean
        //QSqlQuery query("SELECT * FROM ep_users WHERE username LIKE '" + QString("%1").arg(username) + "';");
        QSqlQuery query =  db.exec("SELECT * FROM ep_users WHERE username LIKE '" + QString("%1").arg(username) + "';");
        if (query.size() > 0)
        {
            return 1;
        }
        else
        {
            QSqlQuery query1 =  db.exec("SELECT * FROM ep_users WHERE email LIKE '" + QString("%1").arg(email) + "';");
            if (query1.size() > 0)
            {
                return 2;
            }
            else
            {
                QSqlQuery query2 = db.exec("INSERT INTO ep_users (username, username_crean, password, email) VALUES ('" + QString("%1").arg(username) +"', '" + QString("%1").arg(username_clean) +"', '" + QString("%1").arg(password) +"','" + QString("%1").arg(email) +"')");
                if (db.lastError().isValid())
                {
                    qDebug() << db.lastError().text();
                }
                else
                {
                    return 0;
                }
            }
        }


    }
    else
    {
        return -1;
    }
    return -2;
}


/**
 * This is login function.
 * @brief EP_DB_Wrapper::loginUser
 * @param username
 * @param password
 * @return
 *
 * Return values:
 * 2 -> email exists
 * 1 -> user exists
 * 0 -> OK
 * -1 -> no connection to DB
 * -2 -> unknown error
 */
int EP_DB_Wrapper::loginUser(QString username, QString password)
{
    //Username should be normilized
    QString username_clean = username.toLower();
    QByteArray pswNsalt (password.toStdString().c_str()) ;
    pswNsalt.append("HAAGASFASDfasdfASDFWAERQ@#RASDFASDFQWFASDFASEFAS") ;
    QByteArray hashedSaltedPsw = QCryptographicHash::hash(pswNsalt, QCryptographicHash::Sha256).toHex() ;
    QSqlDatabase db = QSqlDatabase::database("appdb");
    QString input_pass = QString("%1").arg(password);
    QString db_pass;
    if (db.isOpen())
    {
        qDebug() << "here be dragon ... puf";
        // Check for duplicate username
        // TODO: Use clean username and use username_clean
        //QSqlQuery query("SELECT * FROM ep_users WHERE username LIKE '" + QString("%1").arg(username) + "';");
        QSqlQuery query =  db.exec("SELECT * FROM ep_users WHERE username_clean LIKE '" + QString("%1").arg(username_clean) + "';");
        if (query.size() > 0)
        {
            return 1;
        }
        else
        {
            qDebug() << query.value(0).toString();
            db_pass = query.value(3).toString();
            if (db_pass == input_pass)
            {
                return 0;
            }
            else
            {
                return 2;
            }
        }
    }
    else
    {
        return -1;
    }
    return -2;
}
