#include <QMessageBox>
#include <QDebug>
#include "ep_custom_menu.h"

EP_custom_menu::EP_custom_menu()
{
    /*Set init if needed.*/
}

EP_custom_menu::~EP_custom_menu()
{

}

void EP_custom_menu::editButtonClicked(QAction *action)
{
    /*If edit button pressed.*/
    if(action->text() == "Edit")
   {
        QMessageBox msg;
        msg.setText("Here will be the edit window!");
        msg.setWindowTitle("Edit dialog or whatever.");
        msg.exec();
   }
   else
   {
        this->~EP_custom_menu();
   }/*Close window.*/
}
