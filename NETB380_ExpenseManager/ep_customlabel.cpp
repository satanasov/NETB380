#include <QMenu>
#include <QPoint>
#include <QWidget>
#include <QLayout>
#include <QDebug>
#include "ep_customlabel.h"
#include "ep_custom_menu.h"

EP_CustomLabel::EP_CustomLabel()
{
    /*Connect righ-click event to createMenu slot to create the context menu.*/
    connect(
        this, &EP_CustomLabel::customContextMenuRequested,
        this, &EP_CustomLabel::createMenu
    );
}

void EP_CustomLabel::createMenu(const QPoint &pos)
{
//        QList <QLabel*> pointToLabel = this->findChildren<QLabel*>();
//        for(QLabel *LabelsInside: pointToLabel)
//        {
//            qDebug() << LabelsInside->text();
//        }
//    qDebug() << "createMenu"; TO DO use this information to pass to edit menu.
    /*Create menu object.*/
    EP_custom_menu *menu = new EP_custom_menu();
    menu->pointToLabelOwner = this;
    /*TO DO : Delete inline stylsheet. Provide program stylesheet for different windows.*/
    menu->setStyleSheet("QMenu::item:selected{background-color: rgb(132, 162, 174)} "
                        "QMenu{background-color: rgb(255, 255, 255)}"
                        "QMenu{border: 1px solid #000000;}");
    /*Connect to menu action.*/
    connect(menu,&EP_custom_menu::triggered,menu,&EP_custom_menu::editButtonClicked);
    /*Add actions.*/
    menu->addAction(new QAction("Edit", menu));
    menu->addAction(new QAction("Close", menu));
    /*Get current cursor position.*/
    QPoint globalCursorPos = QCursor::pos();
    /*Map to widget location.*/
    globalCursorPos = QWidget::mapFromGlobal(globalCursorPos);
    /*Set to visible and set to cursor location but in the proper widget.*/
    menu->setVisible(true);
    menu->exec(mapToGlobal(globalCursorPos));

}



