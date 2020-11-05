#include "ep_main.h"
#include "ui_ep_main.h"
#include "ep_reportmain_wrapper.h"


EP_Main::EP_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EP_Main)
{
    ui->setupUi(this);
}

EP_Main::~EP_Main()
{
    delete ui;
}

