#ifndef EP_CUSTOMLABEL_H
#define EP_CUSTOMLABEL_H

#include <QLabel>
#include <QFrame>
#include "ep_baseclass_gui_reportmain.h"

class EP_CustomLabel : public QLabel, EP_BaseClass_GUI_ReportMain
{
    Q_OBJECT

    Q_PROPERTY(int m_Id MEMBER IdInTable)
public:
    EP_CustomLabel();

    /*ID of table row in DB for the current expense/income.*/
    int IdInTable = 0;

    /*Exposing base class functions.*/
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer;
    using EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer;


public slots:
    void createMenu(const QPoint &pos);



protected:
    /*Create highlight effect.*/
    void enterEvent(QEvent *ev) override
    {
       this->setFrameStyle(QFrame::Panel | QFrame::Raised);

    }

    void leaveEvent(QEvent *ev) override
    {
       this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    }

};

#endif // EP_CUSTOMLABEL_H
