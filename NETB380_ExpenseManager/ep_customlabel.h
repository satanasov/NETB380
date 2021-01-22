#ifndef EP_CUSTOMLABEL_H
#define EP_CUSTOMLABEL_H

#include <QLabel>
#include <QFrame>

class EP_CustomLabel : public QLabel
{
    Q_OBJECT
public:
    EP_CustomLabel();

public slots:
    void createMenu(const QPoint &pos);

protected:
    /*Create highlight effect.*/
    void enterEvent(QEvent *ev) override
    {
       this->setFrameStyle(QFrame::Panel | QFrame::Raised);
       //this->

    }

    void leaveEvent(QEvent *ev) override
    {
       this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    }

};

#endif // EP_CUSTOMLABEL_H
