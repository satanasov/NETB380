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
   bool eventFilter(QObject *obj, QEvent *event) override;

public:
    explicit ep_edit(QWidget *parent = nullptr);
    ~ep_edit();

    /**/
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
    QWidget *pointToLabelOwner = nullptr;

private slots:
    void on_pushButtonExpenseAddEdit_clicked();

    void on_pushButtonDeleteEdit_clicked();

public slots:
    void EP_E_MakeLastLineEditable(int CurrentIndex);
    void EP_E_UpdateCurrentRowInReport(int StatusOfUpdate);

private:
    Ui::ep_edit *ui;
};

#endif // EP_EDIT_H
