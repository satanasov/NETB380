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
    QSqlDatabase db = QSqlDatabase::database("appdb");
    db.close();
}



/** Check if database is opened.
 * @brief EP_DB_Wrapper::isDBOpen
 * @return DBConnectionStatus -> Check if DB connection is opened.
 */
bool EP_DB_Wrapper::isDBOpen()
{
    bool DBConnectionStatus = false;
    QSqlDatabase db = QSqlDatabase::database("appdb");
    if(true == db.isOpen())
    {
        DBConnectionStatus = true;
    }
    else
    {
        DBConnectionStatus = false;
    }

    return DBConnectionStatus;
}

int EP_DB_Wrapper::isValid(int userid)
{
    QSqlDatabase db = QSqlDatabase::database("appdb");
    if(!this->isDBOpen())
    {
        return -1;
    }
    else
    {
        QSqlQuery query = db.exec("SELECT id, user_active FROM ep_users WHERE id = '" + QString("%1").arg(userid) + "';");
        if (query.size() < 1)
        {
            return -3;
        }
        else
        {
            query.next();
            qDebug() << query.value(0).toString();
            int is_active = query.value(1).toInt();
            if (is_active == 1)
            {
                return 0;
            }
        }
    }
    return -2;
}


/**
 * We will use this method to deply our tables :D (DUH!!!)
 * @brief EP_DB_Wrapper::deployTables
 */
void EP_DB_Wrapper::deployTables()
{
    qDebug() << "DeployTables executed.";
    QSqlDatabase db = QSqlDatabase::database("appdb");
    if (db.isOpen())
    {
        qDebug() << "DB is open tables are deployed";
        // Create users_table (ep_users)
        db.exec("CREATE TABLE ep_account_types(id serial PRIMARY KEY, type VARCHAR (64), description text);");
        db.exec("CREATE TABLE ep_currencies (id serial PRIMARY KEY, iso VARCHAR (8) UNIQUE NOT NULL, long_name VARCHAR (256), short_name VARCHAR (8), rate NUMERIC);");
        db.exec("CREATE TABLE ep_expenses_groups (id serial PRIMARY KEY, uid NUMERIC, name VARCHAR (256), description TEXT);");
        db.exec("CREATE TABLE ep_users (id serial PRIMARY KEY, username VARCHAR (64) NOT NULL, username_clean VARCHAR (80) UNIQUE NOT NULL, password VARCHAR (60) NOT NULL, email VARCHAR (256) UNIQUE NOT NULL, name VARCHAR (512), reg_date NUMERIC, last_active NUMERIC, user_active smallint );");
        db.exec("CREATE TABLE ep_expenses_table (id serial PRIMARY KEY, uid NUMERIC, aid NUMERIC, type NUMERIC, amount DECIMAL, name VARCHAR (256), description TEXT, group_name NUMERIC, added_at NUMERIC, is_active smallint);");
        db.exec("CREATE TABLE ep_user_accounts (id serial PRIMARY KEY, uid NUMERIC, type NUMERIC, name VARCHAR (256), description TEXT, amount DECIMAL, currency NUMERIC, added_at NUMERIC, last_change NUMERIC, is_active smallint);");
        // Let's create some default values
        db.exec("INSERT INTO ep_currencies (iso, long_name, short_name, rate) VALUES ('BGN', 'Bulgarian Lev', ' лв.', 1);");
        qDebug() << db.lastError().text();
    }
}

/**
 * We will use this method to drop all tables :D
 * @brief EP_DB_Wrapper::dropTables
 */
void EP_DB_Wrapper::dropTables()
{
    QSqlDatabase db = QSqlDatabase::database("appdb");
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
 * 4 -> there was error creating the account
 * 3 -> there was error retreaving the user id
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
                QSqlQuery query2 = db.exec("INSERT INTO ep_users (username, username_clean, password, email, user_active) VALUES ('" + QString("%1").arg(username) +"', '" + QString("%1").arg(username_clean) +"', '" + QString("%1").arg(password) +"','" + QString("%1").arg(email) +"', 1)");
                if (db.lastError().isValid())
                {
                    qDebug() << db.lastError().text();
                }
                else
                {
                    // Let's create default account
                    // let's get last user ID
                    QSqlQuery query3 = db.exec("SELECT * FROM ep_users WHERE username_clean LIKE '" + QString("%1").arg(username_clean) + "';");
                    query3.next();
                    int userId = query3.value(0).toInt();
                    qDebug() << userId;
                    if (userId < 0)
                    {
                        return 3;
                    }
                    int accountResponse = this->addUserAccount(userId, 1, "default", "This is some base description", 0, 1);
                    qDebug() << accountResponse;
                    if (accountResponse != 0)
                    {
                        return 4;
                    }
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
 * >0 -> OK
 * -1 -> no connection to DB
 * -2 -> unknown error
 * -3 -> User does not exist
 * -4 -> Wrong pass!
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
    qDebug() << username_clean;
    if (db.isOpen())
    {
        qDebug() << "here be dragon ... puf";
        // Check for duplicate username
        // TODO: Use clean username and use username_clean
        QSqlQuery query = db.exec("SELECT * FROM ep_users WHERE username_clean LIKE '" + QString("%1").arg(username_clean) + "';");
        if (query.size() < 1)
        {
            return -3;
        }
        else
        {
            query.next();
            db_pass = query.value(3).toString();
            if (db_pass == input_pass)
            {
                qDebug() << query.value(0).toInt();
                return query.value(0).toInt();
            }
            else
            {
                return -4;
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
 * @brief EP_DB_Wrapper::addAcountType
 * @param type
 * @param description
 * @return
 *
 * Return values:
 * 0 -> OK
 * -1 -> no connection to DB
 * -2 -> unknown error
 */

int EP_DB_Wrapper::addAcountType(QString type, QString description)
{
    QSqlDatabase db = QSqlDatabase::database("appdb");
    if (db.isOpen())
    {
        QSqlQuery query = db.exec("INSERT INTO ep_account_types (type, description) VALUES ('" + QString("%1").arg(type) + "', '" + QString("%1").arg(description) + "')");
        if (db.lastError().isValid())
        {
            qDebug() << db.lastError().text();
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return -1;
    }
    return -2;
}

/**
 * @brief EP_DB_Wrapper::getAccountTypes
 * @return QList<QList<QString>> of all account types
 * Form:
 * [] => array(
 *      QString ID,
 *      QString type,
 *      Qstring description
 * )
 */
QList<QList<QString>> EP_DB_Wrapper::getAccountTypes()
{
    QSqlDatabase db = QSqlDatabase::database("appdb");
    QList<QList<QString>> answers;
    if (db.isOpen())
    {
        QSqlQuery query = db.exec("SELECT * FROM ep_account_types");
        while (query.next()) {
            QList<QString> a;
            a.append(QString("%1").arg(query.value(0).toInt()));
            a.append(QString("%1").arg(query.value(1).toString()));
            a.append(QString("%1").arg(query.value(2).toString()));
            answers.append(a);
        }
    }
    else
    {
        QList<QString> a;
        QString message = "DB SUX ... Please check connection.";
        a.append(message);
        answers.append(a);
    }
    return answers;
}

/**
 * @brief EP_DB_Wrapper::addCurency
 * @param ISO
 * @param longaneme
 * @return
 *
 * Return values:
 * 0 -> OK
 * -1 -> no connection to DB
 * -2 -> unknown error
 */

int EP_DB_Wrapper::addCurency(QString ISO, QString longname)
{
    QSqlDatabase db = QSqlDatabase::database("appdb");
    if (db.isOpen())
    {
        QSqlQuery query = db.exec("INSERT INTO ep_currencies (iso, long_name) VALUES ('" + QString("%1").arg(ISO) + "', '" + QString("%1").arg(longname) + "')");
        if (db.lastError().isValid())
        {
            qDebug() << db.lastError().text();
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return -1;
    }
    return -2;
}

/**
 * @brief EP_DB_Wrapper::getCurrencies
 * @return QList<QList<QString>> of all currencies
 * Form:
 * [] => array(
 *      QString ID,
 *      QString type,
 *      Qstring description
 * )
 */
QList<QList<QString>> EP_DB_Wrapper::getCurrencies()
{
    QSqlDatabase db = QSqlDatabase::database("appdb");
    QList<QList<QString>> answers;
    if (db.isOpen())
    {
        QSqlQuery query = db.exec("SELECT * FROM ep_currencies");
        while (query.next()) {
            QList<QString> a;
            a.append(QString("%1").arg(query.value(0).toInt()));
            a.append(QString("%1").arg(query.value(1).toString()));
            a.append(QString("%1").arg(query.value(2).toString()));
            answers.append(a);
        }
    }
    else
    {
        QList<QString> a;
        QString message = "DB SUX ... Please check connection.";
        a.append(message);
        answers.append(a);
    }
    return answers;
}

/**
 * @brief EP_DB_Wrapper::addExpenseGroup
 * @param userId
 * @param name
 * @param description
 * @return
 *
 * Return values:
 * 0 -> OK
 * -1 -> no connection to DB
 * -2 -> unknown error
 * -3 -> user does not exist
 * -4 -> user is not active
 */

int EP_DB_Wrapper::addExpenseGroup(int userId, QString name, QString description)
{
    QSqlDatabase db = QSqlDatabase::database("appdb");
    if (db.isOpen())
    {
        // Check if user exists and is active
        QSqlQuery query = db.exec("SELECT id, user_active FROM ep_users WHERE id = '" + QString("%1").arg(userId) + "';");
        if (query.size() < 1)
        {
            return -3;
        }
        else
        {
            query.next();
            qDebug() << query.value(0).toString();
            int is_active = query.value(1).toInt();
            if (is_active == 1)
            {
                QSqlQuery query1 = db.exec("INSERT INTO ep_expenses_groups (uid, name, description) VALUES ('" + QString("%1").arg(userId) + "', '" + QString("%1").arg(name) + "', '" + QString("%1").arg(description) + "')");
                if (db.lastError().isValid())
                {
                    qDebug() << db.lastError().text();
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return -4;
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
 * Get expense groups for user ...
 * @brief getExpenseGroups
 * @param userId
 * @return
 */
QList<QList<QString>> EP_DB_Wrapper::getExpenseGroups(int userId)
{
    QSqlDatabase db = QSqlDatabase::database("appdb");
    QList<QList<QString>> answers;
    if (db.isOpen())
    {
        QSqlQuery query = db.exec("SELECT id, user_active FROM ep_users WHERE id =' " + QString("%1").arg(userId) + "';");
        if (query.size() < 1)
        {
            QList<QString> a;
            QString message = "Invalid user ... mhm ...";
            a.append(message);
            answers.append(a);
        }
        else
        {
            query.next();
            int is_active = query.value(1).toInt();
            if (is_active == 1)
            {
                //query.next();
                QSqlQuery query2 = db.exec("SELECT EXISTS (SELECT 1 FROM ep_expenses_groups);");
                if (db.lastError().isValid())
                {
                    qDebug() << db.lastError().text();
                }
                else
                {
                    query2.next();
                    if(query2.value(0) == "FALSE")
                    {
                        /*User hasnt still added a expense group.*/
                        QList<QString> a;
                        QString message = "emptyTable";
                        a.append(message);
                        answers.append(a);
                    }
                    else
                    {
                        query.next();
                        QSqlQuery query1 = db.exec("SELECT * FROM ep_expenses_groups WHERE uid = '" + QString("%1").arg(userId) + "';");
                        if (db.lastError().isValid())
                        {
                            qDebug() << db.lastError().text();
                        }
                        else
                        {
                            while (query1.next()) {
                                QList<QString> a;
                                a.append(QString("%1").arg(query1.value(0).toString()));
                                a.append(QString("%1").arg(query1.value(1).toString()));
                                a.append(QString("%1").arg(query1.value(2).toString()));
                                a.append(QString("%1").arg(query1.value(3).toString()));
                                answers.append(a);
                            }
                        }
                    }
                }
            }
            else
            {
                QList<QString> a;
                QString message = "User not active ... what are you trying to pull?";
                a.append(message);
                answers.append(a);
            }
        }
    }
    else
    {
        QList<QString> a;
        QString message = "DB SUX ... Please check connection.";
        a.append(message);
        answers.append(a);
    }
    return answers;
}

/**
 * @brief EP_DB_Wrapper::addUserAccount
 * @param userId
 * @param type
 * @param name
 * @param description
 * @param ammount
 * @param currency
 * @return
 */
int EP_DB_Wrapper::addUserAccount(int userId, int type, QString name, QString description, double ammount, int currency)
{
    QSqlDatabase db = QSqlDatabase::database("appdb");
    if (db.isOpen())
    {
        QSqlQuery usrQuery = db.exec("SELECT id, user_active FROM ep_users WHERE id = '" + QString("%1").arg(userId) + "';");
        if (usrQuery.size() < 1)
        {
            return -3;
        }
        else
        {
            usrQuery.next();
            int is_active = usrQuery.value(1).toInt();
            if (is_active == 1)
            {
                QDateTime * timestamp = new QDateTime;
                int added_at = timestamp->currentSecsSinceEpoch();
                QSqlQuery accountQuery = db.exec("INSERT INTO ep_user_accounts (uid, type, name, description, amount, currency, added_at, last_change, is_active) VALUES ('" + QString("%1").arg(userId) + "', '" + QString("%1").arg(type) + "', '" + QString("%1").arg(name) + "', '" + QString("%1").arg(description) + "', '" + QString("%1").arg(ammount) + "', '" + QString("%1").arg(currency) + "', '" + QString("%1").arg(added_at) + "', '" + QString("%1").arg(added_at) + "', 1)");
                if (db.lastError().isValid())
                {
                    qDebug() << db.lastError().text();
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return -4;
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
* @brief EP_DB_Wrapper::getUserAccounts
* @param userId
* @return
*/

QList<QList<QString>> EP_DB_Wrapper::getUserAccounts(int userId)
{
    QSqlDatabase db = QSqlDatabase::database("appdb");
    QList<QList<QString>> answers;
    if (db.isOpen())
    {
        QSqlQuery query = db.exec("SELECT id, user_active FROM ep_users WHERE id = '" + QString("%1").arg(userId) + "';");
        if (query.size() < 1)
        {
            QList<QString> a;
            QString message = "Invalid user ... mhm ...";
            a.append(message);
            answers.append(a);
        }
        else
        {
            query.next();
            int is_active = query.value(1).toInt();
            if (is_active == 1)
            {
                QSqlQuery query1 = db.exec("SELECT * FROM ep_user_accounts WHERE uid = '" + QString("%1").arg(userId) + "'");
                if (db.lastError().isValid())
                {
                    qDebug() << db.lastError().text();
                }
                else
                {
                    while (query1.next()) {
                        QList<QString> a;
                        a.append(query1.value(0).toString());
                        a.append(query1.value(2).toString());
                        a.append(query1.value(3).toString());
                        a.append(query1.value(4).toString());
                        a.append(query1.value(5).toString());
                        a.append(query1.value(6).toString());
                        a.append(query1.value(7).toString());
                        a.append(query1.value(8).toString());
                        a.append(query1.value(9).toString());
                        answers.append(a);
                    }
                }
            }
            else
            {
                QList<QString> a;
                QString message = "User not active ... what are you trying to pull?";
                a.append(message);
                answers.append(a);
            }
        }
    }
    else
    {
        QList<QString> a;
        QString message = "DB SUX ... Please check connection.";
        a.append(message);
        answers.append(a);
    }
    return answers;
}

/**
 * @brief EP_DB_Wrapper::addExpense
 * @param userId
 * @param accountId
 * @param ammount
 * @param name
 * @param description
 * @param expGroup
 * @param added_at
 * @return
 */
int EP_DB_Wrapper::addExpense(int userId, int accountId, double ammount, QString name, QString description, int expGroup, int added_at)
{
    QSqlDatabase db = QSqlDatabase::database("appdb");
    if (db.isOpen())
    {
        QSqlQuery usrQuery = db.exec("SELECT id, user_active FROM ep_users WHERE id = '" + QString("%1").arg(userId) + "';");
        if (usrQuery.size() < 1)
        {
            return -3;
        }
        else
        {
            usrQuery.next();
            int is_active = usrQuery.value(1).toInt();
            if (is_active == 1)
            {
                QSqlQuery expQuery = db.exec("INSERT INTO ep_expenses_table (uid, aid, type, amount, name, description, group_name, added_at, is_active) VALUES ('" + QString("%1").arg(userId) + "', '" + QString("%1").arg(accountId) + "', 1, '" + QString("%1").arg(ammount) + "', '" + QString("%1").arg(name) + "', '" + QString("%1").arg(description) + "', '" + QString("%1").arg(expGroup) + "', '" + QString("%1").arg(added_at) + "', 1)");
                if (db.lastError().isValid())
                {
                    qDebug() << db.lastError().text();
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return -4;
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
 * @brief EP_DB_Wrapper::getExpenses
 * @param userId
 * @param accountId
 * @param type
 * @param ammount
 * @param ammount_delta
 * @param name
 * @param description
 * @param expGroup
 * @param fromTime
 * @param toTime
 * @param limit
 * @return
 */
QList<QList<QString>> EP_DB_Wrapper::getExpenses(int userId, int accountId, int type, double ammount, QString ammount_delta, QString name, QString description, int expGroup, int fromTime, int toTime, int limit)
{
    QSqlDatabase db = QSqlDatabase::database("appdb");
    QList<QList<QString>> answers;
    if (db.isOpen())
    {
        QSqlQuery query = db.exec("SELECT id, user_active FROM ep_users WHERE id = '" + QString("%1").arg(userId) + "';");
        if (query.size() < 1)
        {
            QList<QString> a;
            QString message = "Invalid user ... mhm ...";
            a.append(message);
            answers.append(a);
        }
        else
        {
            query.next();
            int is_active = query.value(1).toInt();
            if (is_active == 1)
            {
                // Code goes here MF
                QString request = "SELECT * FROM ep_expenses_table WHERE uid = " + QString("%1").arg(userId);
                if (accountId != 0)
                {
                    request.append(" AND aid = " + QString("%1").arg(userId));
                }
                if (ammount != 0.0)
                {
                    request.append(" AND amount " + QString("%1").arg(ammount_delta) + " " + QString("%1").arg(ammount));
                }
                if (name != "")
                {
                     request.append(" AND name LIKE '%" + QString("%1").arg(name) + "%'");
                }
                if (description != "")
                {
                     request.append(" AND description LIKE '%" + QString("%1").arg(description) + "%'");
                }
                if (expGroup != 0)
                {
                    request.append(" AND id = " + QString("%1").arg(expGroup));
                }
                request.append(" AND is_active = 1;"); //+ QString("%1").arg(limit));
                QSqlQuery expQuery = db.exec(request);
                if (db.lastError().isValid())
                {
                    qDebug() << db.lastError().text();
                }
                else
                {
                    while (expQuery.next()) {
                        QList<QString> a;
                        a.append(expQuery.value(0).toString());
                        a.append(expQuery.value(2).toString());
                        a.append(expQuery.value(3).toString());
                        a.append(expQuery.value(4).toString());
                        a.append(expQuery.value(5).toString());
                        a.append(expQuery.value(6).toString());
                        a.append(expQuery.value(7).toString());
                        a.append(expQuery.value(8).toString());
                        a.append(expQuery.value(9).toString());
                        answers.append(a);
                    }
                }

            }
            else
            {
                QList<QString> a;
                QString message = "User not active ... what are you trying to pull?";
                a.append(message);
                answers.append(a);
            }
        }
    }
    else
    {
        QList<QString> a;
        QString message = "DB SUX ... Please check connection.";
        a.append(message);
        answers.append(a);
    }
    return answers;
}

/**
 * Edit expenses
 * @brief EP_DB_Wrapper::updateExpense
 * @param expense_id
 * @param new_aid
 * @param type
 * @param ammount
 * @param new_group_name
 * @param new_desc
 * @return
 */
int EP_DB_Wrapper::updateExpense(int expense_id, int new_aid = 0, int type = 0, double ammount = 0, int new_group_name = 0, QString new_desc = "")
{
    QSqlDatabase db = QSqlDatabase::database("appdb");
    if (db.isOpen())
    {
        // Let's build query
        QString request = "UPDATE INTO ep_expenses_table SET";
        QStringList req;
        if (new_aid > 0)
        {
            req << " aid = " + QString("%1").arg(expense_id);
        }
        if (type > 0)
        {
             req << " type = " + QString("%1").arg(expense_id);
        }
        if (ammount > 0)
        {
            req << " ammount = " + QString("%1").arg(ammount);
        }
        if (new_group_name > 0)
        {
            req << " group_name = " + QString("%1").arg(new_group_name);
        }
        if (new_desc != "")
        {
            req << " description = '" + QString("%1").arg(new_group_name) + "'";
        }
        QString rq = req.join(",");
        request.append(rq);
        request.append(" WHERE id = " + QString("%1").arg(expense_id));
        db.exec(request);
        if (db.lastError().isValid())
        {
            qDebug() << db.lastError().text();
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return -3;
    }
    return -4;
}
