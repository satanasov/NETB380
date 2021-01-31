#ifndef EP_EDIT_H
#define EP_EDIT_H

#include <QDialog>
#include "ep_baseclass_gui_reportmain.h"

namespace Ui {
class ep_edit;
}

class ep_edit : public QDialog, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

protected:
    /*Override eventFilter to detected Tab key press.*/
    bool eventFilter(QObject *obj, QEvent *event) override;

public:
    explicit ep_edit(QWidget *parent = nullptr);
    ~ep_edit();

    /*Local function for connecting to Event Dispatcher.*/
    void DisplayCurrentSavedDate();
    void ConnectToED();

    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;

    /*Public members for current row data.*/
    QList<QString> currentLableText;
    QList<QString> modifiedText;
    /*Pointer to parent witdget for updating.*/
    QWidget *pointToLabelOwner = nullptr;

private slots:
    /*When edit button is clicked.*/
    void on_pushButtonExpenseAddEdit_clicked();
    /*When delete button is pressed.*/
    void on_pushButtonDeleteEdit_clicked();

public slots:
    /*Making last line of combobox editable.*/
    void EP_E_MakeLastLineEditable(int CurrentIndex);
    /*Status for DB table row update of expense/income.*/
    void EP_E_UpdateCurrentRowInReport(int StatusOfUpdate);

private:
    Ui::ep_edit *ui;
};

#endif // EP_EDIT_H
