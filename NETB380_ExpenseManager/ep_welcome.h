#ifndef EP_WELCOME_H
#define EP_WELCOME_H

#include <QDialog>

namespace Ui {
class ep_welcome;
}

class ep_welcome : public QDialog
{
    Q_OBJECT

public:
    explicit ep_welcome(QWidget *parent = nullptr);
    ~ep_welcome();

private slots:
    void on_pushButtonAddMoney_clicked();

private:
    Ui::ep_welcome *ui;
};

#endif // EP_WELCOME_H
