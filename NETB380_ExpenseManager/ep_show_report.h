#ifndef EP_SHOW_REPORT_H
#define EP_SHOW_REPORT_H

#include <QDialog>
#include "ep_baseclass_gui_reportmain.h"
#include "ep_customlabel.h"

namespace Ui {
class ep_show_report;
}

class ep_show_report : public QDialog , EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

public:
    explicit ep_show_report(QWidget *parent = nullptr);
    ~ep_show_report();

    /*Local functions.*/
    void EP_ShowReport_ProcessReport(QList<QList<QString>> reportData);
    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;

private:
    Ui::ep_show_report *ui;
};

#endif // EP_SHOW_REPORT_H
