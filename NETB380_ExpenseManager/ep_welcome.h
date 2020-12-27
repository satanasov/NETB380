#ifndef EP_WELCOME_H
#define EP_WELCOME_H

#include <QDialog>
#include "ep_baseclass_gui_reportmain.h"

namespace Ui {
class ep_welcome;
}

class ep_welcome : public QDialog, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

public:
    explicit ep_welcome(QWidget *parent = nullptr);
    ~ep_welcome();
    void EP_WelcomeScreen_Initialize();

    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;

private slots:
    void on_pushButtonAddMoney_clicked();

public slots:
    void updateTime();

private:
    Ui::ep_welcome *ui;
};

#endif // EP_WELCOME_H
