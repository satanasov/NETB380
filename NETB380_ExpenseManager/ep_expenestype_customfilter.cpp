#include "ep_expenestype_customfilter.h"
#include "ui_ep_expenestype_customfilter.h"

EP_ExpenesType_CustomFilter::EP_ExpenesType_CustomFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EP_ExpenesType_CustomFilter)
{
    ui->setupUi(this);
    this->setWindowTitle("Expense type filter.");
}

EP_ExpenesType_CustomFilter::~EP_ExpenesType_CustomFilter()
{
    delete ui;
}

void EP_ExpenesType_CustomFilter::UpdateComboList()
{
    ui->comboBox->clear();
    /*Add items to combobox.*/
    for(int i =0 ; i < (this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().count());i++)
    {
        if(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().at(i).at(2) != "Income")
        {
            qDebug() << this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().at(i).at(2);
            ui->comboBox->addItem(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().at(i).at(2),Qt::DisplayRole);
            ui->comboBox->setEditable(false);
        }
    }
}

void EP_ExpenesType_CustomFilter::on_pushButton_clicked()
{
    QList<QString> expResult;
    QString TypeOfExp = ui->comboBox->currentText();
    if(TypeOfExp != "")
    {
        expResult.append(TypeOfExp);
    }
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_EXPENSE_OTHER_TYPE,expResult);

    this->~EP_ExpenesType_CustomFilter();
}
