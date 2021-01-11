#ifndef EP_ADD_EXPENSE_H
#define EP_ADD_EXPENSE_H

#include <QDialog>

namespace Ui {
class ep_add_expense;
}

class ep_add_expense : public QDialog
{
    Q_OBJECT

public:
    explicit ep_add_expense(QWidget *parent = nullptr);
    ~ep_add_expense();



private slots:
    void on_pushButtonExpenseAdd_clicked();

private:
    Ui::ep_add_expense *ui;
};

#endif // EP_ADD_EXPENSE_H
