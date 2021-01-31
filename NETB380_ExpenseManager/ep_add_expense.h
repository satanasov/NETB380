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
    /*Override function eventFiltr to detected Tab key press.*/
    bool eventFilter(QObject *obj, QEvent *event) override;
public:
    explicit ep_add_expense(QWidget *parent = nullptr);
    ~ep_add_expense();
    /*Connect to Event Dispatcher.*/
    void EP_AddExpense_ConnectToED();
    /*Initialize the combobox with all available expense groups..*/
    void EP_AE_InitializeComboBoxValues();
    /*List of strings containing all availalb expense groups.*/
    QStringList AllAvalExpTypes;
    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;

private slots:
    /*Slot for button ADD*/
    void on_pushButtonExpenseAdd_clicked();

public slots:
    /*Slots for feedback of expense adding.*/
    void EP_AE_AddedExpenseStatus(int Status);
    /*Slot for making last line in combobox editable.*/
    void EP_AE_MakeLastLineEditable(int CurrentIndex);

private:
    Ui::ep_add_expense *ui;
};

#endif // EP_ADD_EXPENSE_H
