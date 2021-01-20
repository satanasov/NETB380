#ifndef EP_OTHER_H
#define EP_OTHER_H

#include <QDialog>
#include <ep_show_report.h>

namespace Ui {
class ep_other;
}

class ep_other : public QDialog
{
    Q_OBJECT

public:
    explicit ep_other(QWidget *parent = nullptr);
    ~ep_other();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ep_other *ui;
    ep_show_report *ep_sh_r;
};

#endif // EP_OTHER_H
