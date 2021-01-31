#include <QMessageBox>
#include <QDebug>
#include <QLabel>
#include <QTextCodec>
#include "ep_custom_menu.h"
#include "ep_edit.h"
#include "ep_customlabel.h"

EP_custom_menu::EP_custom_menu()
{
    /*Set init if needed.*/

}

EP_custom_menu::~EP_custom_menu()
{

}

void EP_custom_menu::editButtonClicked(QAction *action)
{
    /*Create new edit window.*/
    ep_edit *newEdit = new ep_edit();
    newEdit-> EP_BaseClass_SetUserDataPointer(this->EP_BaseClass_GetUserDataPointer());
    newEdit-> EP_BaseClass_SetEventDispatcherPointer(this->EP_BaseClass_GetEDPointer());
    newEdit-> ConnectToED();
    newEdit->pointToLabelOwner = this->pointToLabelOwner;
    /*If edit button pressed.*/
    if(action->text() == "Edit")
   {
        emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_updateCurrentUserExpGroups(3);
        QList<QString> textInLables;
        /*Iterate trought all members in current row of expense/income.*/
        QList <QLabel*> pointToLabel = this->pointToLabelOwner->findChildren<QLabel*>();
              for(QLabel *LabelsInside: pointToLabel)
              {
                  QString helpVar = LabelsInside->text();
                  newEdit->currentLableText.append(helpVar);
              }
        /*Get current ID in DB.*/
        newEdit->currentLableText.append(QString::number(this->pointToLabelOwner->property("m_Id").toInt()));
        /*Creat edit window.*/
        newEdit->DisplayCurrentSavedDate();
        newEdit->exec();
   }
   else
   {
        this->~EP_custom_menu();
        newEdit->~ep_edit();
   }/*Close window.*/
}
