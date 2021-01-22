#ifndef EP_OTHER_H
#define EP_OTHER_H

#include <QDialog>
#include <ep_show_report.h>
#include "ep_baseclass_gui_reportmain.h"

namespace Ui {
class ep_other;
}

class ep_other : public QDialog, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

public:
    explicit ep_other(QWidget *parent = nullptr);
    ~ep_other();

    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;

private slots:
    void on_pushButtonSearch_clicked();

private:
    Ui::ep_other *ui;
    ep_show_report *ep_sh_r;
};

#endif // EP_OTHER_H
