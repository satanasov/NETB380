#ifndef EP_CUSTOM_MENU_H
#define EP_CUSTOM_MENU_H

#include <QMenu>

class EP_custom_menu : public QMenu
{
    Q_OBJECT
public:
    explicit EP_custom_menu();
    ~EP_custom_menu();
    QWidget *pointToLabelOwner = nullptr;

public slots:
void editButtonClicked(QAction *action);

};

#endif // EP_CUSTOM_MENU_H
