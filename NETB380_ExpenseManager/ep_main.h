#ifndef EP_MAIN_H
#define EP_MAIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class EP_Main; }
QT_END_NAMESPACE

class EP_Main : public QMainWindow
{
    Q_OBJECT

public:
    EP_Main(QWidget *parent = nullptr);
    ~EP_Main();

private:
    Ui::EP_Main *ui;
};
#endif // EP_MAIN_H
