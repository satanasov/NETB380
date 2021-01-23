#ifndef EP_EDIT_H
#define EP_EDIT_H

#include <QDialog>

namespace Ui {
class ep_edit;
}

class ep_edit : public QDialog
{
    Q_OBJECT

public:
    explicit ep_edit(QWidget *parent = nullptr);
    ~ep_edit();

private slots:
    void on_pushButtonExpenseAdd_clicked();

    void on_pushButtonDeleteEdit_clicked();

    void on_pushButtonExpenseAddEdit_clicked();

private:
    Ui::ep_edit *ui;
};

#endif // EP_EDIT_H
