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
    /*Clear combobox.*/
    ui->comboBox->clear();
    /*Add items to combobox.*/
    for(int i =0 ; i < (this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().count());i++)
    {
        if(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().at(i).at(2) != "Income")
        {
            /*Update combobox with avalaible expense groups.*/
            ui->comboBox->addItem(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().at(i).at(2),Qt::DisplayRole);
            /*Make it uneditable.*/
            ui->comboBox->setEditable(false);
        }
    }
}

void EP_ExpenesType_CustomFilter::on_pushButton_clicked()
{
    /*Create container to emit.*/
    QList<QString> expResult;
    /*Get selected expense group in ComboBox.*/
    QString TypeOfExp = ui->comboBox->currentText();
    /*Check for empty string. Here we need input validation.*/
    if(TypeOfExp != "")
    {
        /*Add group to contaiener.*/
        expResult.append(TypeOfExp);
    }
    /*Request expense report processing from Report main object.*/
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_RMWlcScreen_getReport(EP_EXPENSE_OTHER_TYPE,expResult);
    /*Destroy object.*/
    this->~EP_ExpenesType_CustomFilter();
}
