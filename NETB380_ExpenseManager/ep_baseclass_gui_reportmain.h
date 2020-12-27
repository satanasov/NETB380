#ifndef EP_BASECLASS_GUI_REPORTMAIN_H
#define EP_BASECLASS_GUI_REPORTMAIN_H

#include "ep_eventdispatcher.h"
#include "ep_userdata.h"

class EP_BaseClass_GUI_ReportMain
{
public:
    EP_BaseClass_GUI_ReportMain();
    /*Setters*/
    void EP_BaseClass_SetUserDataPointer(EP_UserData *UserDataPointer);
    void EP_BaseClass_SetEventDispatcherPointer(EP_EventDispatcher *EDPointer);
    /*Getters*/
    EP_UserData* EP_BaseClass_GetUserDataPointer();
    EP_EventDispatcher* EP_BaseClass_GetEDPointer();

private:
    /*User data pointer.*/
    EP_UserData *PointerToUserData = nullptr;
    /*Event dispatcher pointer.*/
    EP_EventDispatcher *PointerToEventDispacther = nullptr;
};
#endif // EP_BASECLASS_GUI_REPORTMAIN_H
