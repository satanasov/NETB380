#ifndef EP_EXPENESTYPE_CUSTOMFILTER_H
#define EP_EXPENESTYPE_CUSTOMFILTER_H

#include <QDialog>
#include "ep_baseclass_gui_reportmain.h"

namespace Ui {
class EP_ExpenesType_CustomFilter;
}

class EP_ExpenesType_CustomFilter : public QDialog, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

public:
    explicit EP_ExpenesType_CustomFilter(QWidget *parent = nullptr);
    ~EP_ExpenesType_CustomFilter();

    /**/
    void UpdateComboList();
    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;

private slots:
    void on_pushButton_clicked();

private:
    Ui::EP_ExpenesType_CustomFilter *ui;
};

#endif // EP_EXPENESTYPE_CUSTOMFILTER_H
