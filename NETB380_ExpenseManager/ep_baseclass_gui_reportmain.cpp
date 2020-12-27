#include "ep_baseclass_gui_reportmain.h"

EP_BaseClass_GUI_ReportMain::EP_BaseClass_GUI_ReportMain()
{
    /*Initialize private members.*/
    this->PointerToEventDispacther = nullptr;
    this->PointerToUserData = nullptr;
}

/*Set pointer to user data class.*/
void EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetUserDataPointer(EP_UserData * UserDataPointer)
{
    this->PointerToUserData = UserDataPointer;
}

/*Get user data object location*/
EP_UserData* EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetUserDataPointer()
{
    return this->PointerToUserData;
}

/*Set pointer to event dispatcher class.*/
void EP_BaseClass_GUI_ReportMain::EP_BaseClass_SetEventDispatcherPointer(EP_EventDispatcher *EDPointer)
{
    this->PointerToEventDispacther = EDPointer;
}

/*Get event dispatcher object location*/
EP_EventDispatcher* EP_BaseClass_GUI_ReportMain::EP_BaseClass_GetEDPointer()
{
    return this->PointerToEventDispacther;
}
