#include "ep_edit.h"
#include "ui_ep_edit.h"
#include <QMessageBox>

ep_edit::ep_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_edit)
{
    ui->setupUi(this);
    /*Change focus policy of ComboBox*/
    ui->comboBoxTypeEdit->setFocusPolicy(Qt::StrongFocus);
    ui->comboBoxTypeEdit->setFocus();
    /*Connect to override function eventFilter to get Tab key press.*/
    ui->comboBoxTypeEdit->installEventFilter(this);
    /*Connect class signal slot for making line editable.*/
    connect(ui->comboBoxTypeEdit,SIGNAL(currentIndexChanged(int)),this,SLOT(EP_E_MakeLastLineEditable(int)));

}

ep_edit::~ep_edit()
{
    delete ui;
}

void ep_edit::ConnectToED()
{
    connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RM_Editexpenseincoem(int)),this,SLOT(EP_E_UpdateCurrentRowInReport(int)));
}

void ep_edit::on_pushButtonExpenseAddEdit_clicked()
{
    /**/
    bool IsAmountChanged = false;
    int AmmountDif = 0;
    QList<QString> updatedData;
    /*Check name for difference.*/
    if(this->currentLableText.at(0) != ui->lineEditNameExpenseEdit->text())
    {
        updatedData.append(ui->lineEditNameExpenseEdit->text());
    }
    else
    {
         updatedData.append(this->currentLableText.at(0));
    }
    /*Check type for differences.*/
    if(ui->comboBoxTypeEdit->currentText() != this->currentLableText.at(1))
    {
        updatedData.append(ui->comboBoxTypeEdit->currentText());
    }
    else
    {
         updatedData.append(this->currentLableText.at(1));
    }
    /*Check ammount for differences.*/
    if( QString::number(ui->doubleSpinBoxPriceExpenseEdit->value()) != this->currentLableText.at(2))
    {
        updatedData.append(QString::number(ui->doubleSpinBoxPriceExpenseEdit->value()));
        /*Only if we had API to update user ammounts.*/
        AmmountDif = (ui->doubleSpinBoxPriceExpenseEdit->value() - this->currentLableText.at(2).toDouble());
    }
    else
    {
        updatedData.append(this->currentLableText.at(2));
    }
    /*Check type of currency.*/
    updatedData.append("BGN");
    /*Compare dates.*/
    if( ui->dateEditDateExpenseEdit->dateTime() != QDateTime::fromString(this->currentLableText.at(4), "dd.MM.yyyy hh:mm:ss"))
    {
        updatedData.append(ui->dateEditDateExpenseEdit->dateTime().toString("dd.MM.yyyy hh:mm:ss"));
    }
    else
    {
        updatedData.append(this->currentLableText.at(4));
    }
    /*Check ammount for differences.*/
    if( ui->lineEditDescriptionEdit->text() != this->currentLableText.at(5))
    {
        updatedData.append(ui->lineEditDescriptionEdit->text());
    }
    else
    {
         updatedData.append(this->currentLableText.at(5));
    }
    /*Get ID in table.*/
    updatedData.append(this->currentLableText.at(6));
    /*Store modified data.*/
    this->modifiedText = updatedData;
    /*Get only changed data.*/
    emit this->EP_BaseClass_GetEDPointer()->EP_ED_EWinRequestTableRowUpdate(updatedData);
}

void ep_edit::on_pushButtonDeleteEdit_clicked()
{

}

/*TO BE DELETED. Testing only.*/
void ep_edit::DisplayCurrentSavedDate()
{

    ui->doubleSpinBoxPriceExpenseEdit->setValue(this->currentLableText.at(2).toDouble());
    QDateTime DateTimeFromString = QDateTime::fromString(this->currentLableText.at(4), "dd.MM.yyyy hh:mm:ss");
    ui->dateEditDateExpenseEdit->setDateTime(DateTimeFromString);
    ui->lineEditNameExpenseEdit->setText(this->currentLableText.at(0));
    ui->lineEditDescriptionEdit->setText(this->currentLableText.at(5));
    /*TO DO CHECK FOR EMPTY container.*/
    int CounterOfExpGroups = 0;
    int IndexMatch = 0;
    ui->comboBoxTypeEdit->clear();
    /*Add items to combobox.*/
    for(int i =0 ; i < (this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().count()+1);i++)
    {
        /*Get all available items.*/
        if(i < this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().count())
        {
            if(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().at(i).at(2) != "Income")
            {

                ui->comboBoxTypeEdit->addItem(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().at(i).at(2),Qt::DisplayRole);
                CounterOfExpGroups++;
                ui->comboBoxTypeEdit->setEditable(false);
                if(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().at(i).at(2) == this->currentLableText.at(1))
                {
                   IndexMatch = CounterOfExpGroups;
                   //ui->comboBoxTypeEdit->setCurrentIndex(IndexMatch);
                }
            }
        }
        else
        {
            /*Add last item as New.*/
            ui->comboBoxTypeEdit->addItem("New",Qt::DisplayRole);
            ui->comboBoxTypeEdit->setEditable(false);
            //ui->comboBoxTypeEdit->setCurrentIndex(IndexMatch);
        }
    }
    ui->comboBoxTypeEdit->setCurrentIndex(IndexMatch-1);
}

void ep_edit::EP_E_MakeLastLineEditable(int CurrentIndex)
{
    /*Make comboBox editable only if new selected.*/
    if(CurrentIndex == (this->ui->comboBoxTypeEdit->count() - 1))
    {
        this->ui->comboBoxTypeEdit->setEditable(true);
    }
    else
    {
        this->ui->comboBoxTypeEdit->setEditable(false);
    }
}


bool ep_edit::eventFilter(QObject *obj, QEvent *event)
{
    if ((event->type() == QEvent::FocusOut))
    {
        if(true == ui->comboBoxTypeEdit->isEditable())
        {
            /*Change policy to add before this index.*/
            ui->comboBoxTypeEdit->setInsertPolicy(QComboBox::InsertBeforeCurrent);
            /*Get user input.*/
            QString userInput = ui->comboBoxTypeEdit->currentText();
            /*Check if current string is empty.*/
            if(userInput != " ")
            {
                /*Search if text is already available.*/
                int FindTextResult = ui->comboBoxTypeEdit->findText(userInput, Qt::MatchCaseSensitive);
                if(FindTextResult != -1)
                {
                    ui->comboBoxTypeEdit->setEditable(false);
                    ui->comboBoxTypeEdit->setCurrentIndex(ui->comboBoxTypeEdit->count()-2);

                    return false;
                }
                else
                {
                    ui->comboBoxTypeEdit->setItemText(ui->comboBoxTypeEdit->count()-1, userInput);
                    ui->comboBoxTypeEdit->setEditable(false);
                    ui->comboBoxTypeEdit->addItem("New",Qt::DisplayRole);
                    return true;
                }
            }
            else
            {
                return false;
            }
        }
         return true;
    }
    else
    {
       // standard event processing
       return false;
    }
}

void ep_edit::EP_E_UpdateCurrentRowInReport(int StatusOfUpdate)
{
    int ArrIndex = 0;
    QList<QString> textInLables;
    /*Iterate trought all members in current row of expense/income.*/
    QList <QLabel*> pointToLabel = this->pointToLabelOwner->findChildren<QLabel*>();
          for(QLabel *LabelsInside: pointToLabel)
          {
              if(ArrIndex == 0)
              {
                /*Update name in show report window..*/
                LabelsInside->setText(this->modifiedText.at(0));
              }
              else if(ArrIndex == 1)
              {
                /*Update type in show report window..*/
                LabelsInside->setText(this->modifiedText.at(1));
              }

              else if(ArrIndex == 2)
              {
                /*Update price in show report window..*/
                LabelsInside->setText(this->modifiedText.at(2));
              }

              else if(ArrIndex == 3)
              {
                /*Update currency type in show report window..*/
                LabelsInside->setText(this->modifiedText.at(3));
              }
              else if(ArrIndex == 4)
              {
                /*Update date in show report window..*/
                LabelsInside->setText(this->modifiedText.at(4));
              }
              else if(ArrIndex == 5)
              {
                /*Update description in show report window..*/
                LabelsInside->setText(this->modifiedText.at(5));
              }
              ArrIndex++;
          }
    /*Destroy edit window.*/
    this->~ep_edit();
    QMessageBox msg;
    msg.setWindowTitle("Update expense status");
    msg.setText("Expense is updates successfully!");
    msg.exec();
}
