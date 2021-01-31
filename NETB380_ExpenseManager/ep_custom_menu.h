#ifndef EP_CUSTOM_MENU_H
#define EP_CUSTOM_MENU_H

#include <QMenu>
#include "ep_baseclass_gui_reportmain.h"

class EP_custom_menu : public QMenu, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT
public:
    explicit EP_custom_menu();
    ~EP_custom_menu();
    /*Pointer to QLabel that will be parent object to this class object..*/
    QWidget *pointToLabelOwner = nullptr;

    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;
public slots:
    /*Slot for executing expense edit.*/
    void editButtonClicked(QAction *action);

};

#endif // EP_CUSTOM_MENU_H
