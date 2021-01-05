#ifndef EP_SHOW_REPORT_H
#define EP_SHOW_REPORT_H

#include <QDialog>

namespace Ui {
class ep_show_report;
}

class ep_show_report : public QDialog
{
    Q_OBJECT

public:
    explicit ep_show_report(QWidget *parent = nullptr);
    ~ep_show_report();

private:
    Ui::ep_show_report *ui;
};

#endif // EP_SHOW_REPORT_H
