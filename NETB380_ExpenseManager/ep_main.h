#ifndef EP_MAIN_H
#define EP_MAIN_H

#include <QMainWindow>
#include "ep_register.h" //needed in order to open reg window from main window

QT_BEGIN_NAMESPACE
namespace Ui { class EP_Main; }
QT_END_NAMESPACE

class EP_Main : public QMainWindow
{
    Q_OBJECT

public:
    EP_Main(QWidget *parent = nullptr);
    ~EP_Main();

private slots:

    void on_pushButtonLogIn_clicked();

    void on_pushButtonConnectDB_clicked();

    void on_pushButtonCreateNewAccount_clicked();

private:
    Ui::EP_Main *ui;
    ep_register *ep_reg; //needed in order to open reg window from main window
};
#endif // EP_MAIN_H
