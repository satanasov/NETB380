#ifndef EP_CUSTOMLABEL_H
#define EP_CUSTOMLABEL_H

#include <QLabel>
#include <QFrame>

class EP_CustomLabel : public QLabel
{
public:
    EP_CustomLabel();

public slots:
    void createMenu(const QPoint &pos);

protected:
    /*Create highlight effect.*/
    void enterEvent(QEvent *ev) override
    {
//        this->setStyleSheet("background-color: rgb(132, 162, 174)");
       this->setFrameStyle(QFrame::Panel | QFrame::Raised);

    }

    void leaveEvent(QEvent *ev) override
    {
//        this->setStyleSheet("background-color: unset");
       this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    }

};

#endif // EP_CUSTOMLABEL_H
