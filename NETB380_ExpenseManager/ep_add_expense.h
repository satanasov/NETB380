#ifndef EP_ADD_EXPENSE_H
#define EP_ADD_EXPENSE_H

#include <QDialog>
#include "ep_baseclass_gui_reportmain.h"

namespace Ui {
class ep_add_expense;
}

class ep_add_expense : public QDialog, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

public:
    explicit ep_add_expense(QWidget *parent = nullptr);
    ~ep_add_expense();
    /**/
    void EP_AddExpense_ConnectToED();

    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;

private slots:
    void on_pushButtonExpenseAdd_clicked();

public slots:
    void EP_AE_AddedExpenseStatus(int Status);

private:
    Ui::ep_add_expense *ui;
};

#endif // EP_ADD_EXPENSE_H
