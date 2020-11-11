#ifndef EP_REPORTMAIN_WRAPPER_H
#define EP_REPORTMAIN_WRAPPER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QSettings>

class EP_ReportMain : public QObject
{
    Q_OBJECT
public:
    /*Constructor.*/
    explicit EP_ReportMain(QObject *parent = nullptr);
    /*Create connection between DBMS wrapper and the thread created in main.*/
    void EP_ReportMain_SetupThread(QThread &cThread);
signals:
    /*Here we need to define signals that can be for example that a job is completed and the GUI to repaint.*/
public slots:
    /*Create thread slot. (The job that will be executed)*/
    void EP_Report_Main();
    /*Main_UI_Slot*/
    void EP_GetUserDataRegister();
};

#endif // EP_REPORTMAIN_H
