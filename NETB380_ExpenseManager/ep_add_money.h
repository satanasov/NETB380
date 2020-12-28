#ifndef EP_ADD_MONEY_H
#define EP_ADD_MONEY_H

#include <QDialog>

namespace Ui {
class ep_add_money;
}

class ep_add_money : public QDialog
{
    Q_OBJECT

public:
    explicit ep_add_money(QWidget *parent = nullptr);
    ~ep_add_money();

private slots:
    void on_pushButtonMoneyAdd_clicked();

private:
    Ui::ep_add_money *ui;
};

#endif // EP_ADD_MONEY_H
