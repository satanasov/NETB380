#include <QMessageBox>
#include "ep_add_money.h"
#include "ui_ep_add_money.h"


ep_add_money::ep_add_money(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_add_money)
{
    ui->setupUi(this);
}

ep_add_money::~ep_add_money()
{
    delete ui;
}

void ep_add_money::on_pushButtonMoneyAdd_clicked()
{
    QString money = "";
    /*Get selected curency.*/
    QString selectedCurrency = ui->comboBox->currentText();
    /*Translate string to currency.*/
    EP_Currencies currentSelcetedCurrency = EP_CustomFunctions::translateStringToCurrency(selectedCurrency);
    /*Adapt money before saving in DB.*/
    money = QString::number(ui->doubleSpinBoxAmmount->value());
    /*Request value adding to */
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_AddMoneyWinAddCurrencyValue(money,currentSelcetedCurrency);
}

void ep_add_money::EP_Add_Money_statusOfAddMoneyRequest(int status, QString valueToDisplay, EP_Currencies adaptCurrency)
{
    QString valueToDisplayAddMoney= "";
    switch (status) {
        case -1:
            QMessageBox::information(this,"ERROR", "No connection with DB, please reconnect to DB!");
        break;
        case 0:
            QMessageBox::information(this,"Success !!" ,"Succesfully added:" + valueToDisplay + " to balance!");
        break;
        default:
            QMessageBox::information(this,"ERROR", "DEBUG PURPOSES: Default case hitted!");
        break;
    }
}
/*Handle all connections to Event Dispatcher.*/
void ep_add_money::EP_Add_Money_connectToED()
{
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RMAddedMoneyStatus(int,QString,EP_Currencies)), this, SLOT(EP_Add_Money_statusOfAddMoneyRequest(int,QString,EP_Currencies)));
}
