#ifndef EP_ADD_MONEY_H
#define EP_ADD_MONEY_H

#include <QDialog>
#include "ep_baseclass_gui_reportmain.h"

namespace Ui {
class ep_add_money;
}

class ep_add_money : public QDialog , EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

public:
    explicit ep_add_money(QWidget *parent = nullptr);
    ~ep_add_money();

    /*Connect to ED.*/
    void EP_AddMoney_ConnectToED();

    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;

private slots:
    void on_pushButtonMoneyAdd_clicked();

public slots:
    /*Status of added income.*/
    void EP_AM_AddedMoneyStatus(int Status);

private:
    Ui::ep_add_money *ui;
};

#endif // EP_ADD_MONEY_H
