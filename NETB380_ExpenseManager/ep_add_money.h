#ifndef EP_ADD_MONEY_H
#define EP_ADD_MONEY_H

#include <QDialog>
#include "ep_baseclass_gui_reportmain.h"
#include "ep_customtypes.h"
#include "ep_customfunctions.h"


namespace Ui {
class ep_add_money;
}

class ep_add_money : public QDialog, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

public:
    explicit ep_add_money(QWidget *parent = nullptr);
    ~ep_add_money();

    /*Connect to ED.*/
    void EP_Add_Money_connectToED();

    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;

public slots:
    /*Process added money request.*/
    void EP_Add_Money_statusOfAddMoneyRequest(int status, QString valueToDisplay, EP_Currencies adaptCurrency);

private slots:
    void on_pushButtonMoneyAdd_clicked();

private:
    Ui::ep_add_money *ui;
};

#endif // EP_ADD_MONEY_H
