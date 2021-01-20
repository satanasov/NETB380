#ifndef EP_WELCOME_H
#define EP_WELCOME_H

#include <QDialog>
#include "ep_baseclass_gui_reportmain.h"
#include "ep_add_money.h"
#include "ep_add_expense.h"
#include "ep_show_report.h"
#include "EP_CustomTypes.h"
#include "ep_other.h"

namespace Ui {
class ep_welcome;
}

class ep_welcome : public QDialog, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

public:
    explicit ep_welcome(QWidget *parent = nullptr);
    ~ep_welcome();
    void EP_WelcomeScreen_ConnectToED();
    void EP_WelcomeScreen_InitValues();

    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;

private slots:
    void on_pushButtonAddMoney_clicked();

    void on_pushButtonNewExpense_clicked();

    void on_pushButtonToday_clicked();

    void on_pushButtonWeek_clicked();

    void on_pushButtonMonth_clicked();

    void on_pushButtonYear_clicked();

    void on_pushButtonAllTime_clicked();

    void on_pushButtonCustom_clicked();

    void on_pushButtonTransport_clicked();

    void on_pushButtonFood_clicked();

    void on_pushButtonClothes_clicked();

    void on_pushButtonUtility_clicked();

    void on_pushButtonBank_clicked();

    void on_pushButtonOther_clicked();

public slots:
    void updateTime();
    void updateCurrentUserAmount();
    void generateReport(QList<QList<QString>> queryResult, EP_Report_Types typeOfReport);
    void openAddExpenseWindow();


private:
    Ui::ep_welcome *ui;
    ep_add_money *ep_ad_m;
    ep_add_expense *ep_ad_e;
    ep_show_report *ep_sh_r;
    ep_other *ep_ot;

};

#endif // EP_WELCOME_H
