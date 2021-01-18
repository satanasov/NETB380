#ifndef EP_ADD_EXPENSE_H
#define EP_ADD_EXPENSE_H

#include <QDialog>
#include <QFocusEvent>
#include "ep_baseclass_gui_reportmain.h"

namespace Ui {
class ep_add_expense;
}

class ep_add_expense : public QDialog, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
public:
    explicit ep_add_expense(QWidget *parent = nullptr);
    ~ep_add_expense();
    /**/
    void EP_AddExpense_ConnectToED();
    void EP_AE_InitializeComboBoxValues();

    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;

private slots:
    void on_pushButtonExpenseAdd_clicked();

public slots:
    void EP_AE_AddedExpenseStatus(int Status);
    void EP_AE_MakeLastLineEditable(int CurrentIndex);

    //void EP_AE_AddItemToComboBox(QFocusEvent *eventThatMovedFocuse);

private:
    Ui::ep_add_expense *ui;
};

#endif // EP_ADD_EXPENSE_H
