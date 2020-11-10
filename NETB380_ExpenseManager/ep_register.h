#ifndef EP_REGISTER_H
#define EP_REGISTER_H

#include <QDialog>

namespace Ui {
class ep_register;
}

class ep_register : public QDialog
{
    Q_OBJECT

public:
    explicit ep_register(QWidget *parent = nullptr);
    ~ep_register();

private slots:
    void on_pushButtonRegister_clicked();

private:
    Ui::ep_register *ui;
};

#endif // EP_REGISTER_H
