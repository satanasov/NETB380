#include <QDateTime>
#include <QMessageBox>
#include "ep_add_expense.h"
#include "ui_ep_add_expense.h"

ep_add_expense::ep_add_expense(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ep_add_expense)
{
    ui->setupUi(this);
    /*Add current system date.*/
    QDate date = QDate::currentDate();
    ui->dateTimeEditDateExpense->setDate(date);
    ui->comboBox->setFocusPolicy(Qt::StrongFocus);
    ui->comboBox->setFocus();
    ui->comboBox->installEventFilter(this);
    /*Connect local */
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(EP_AE_MakeLastLineEditable(int)));
}

ep_add_expense::~ep_add_expense()
{
    delete ui;
}

void ep_add_expense::on_pushButtonExpenseAdd_clicked()
{
    /*Make input validation.*/
    QString nameOfExpense = ui->lineEditNameExpense->text();
    QString typeOfExpense = ui->comboBox->currentText();
    QString amountOfExpense = ui->doubleSpinBoxPriceExpense->text();
    QString descriptionOfExpense = ui->lineEditDescription->text();
    /* Request expense adding.*/
    this->EP_BaseClass_GetEDPointer()->EP_ED_AEWinRequestAddingExpense(nameOfExpense,typeOfExpense,amountOfExpense,descriptionOfExpense,ui->dateTimeEditDateExpense->dateTime(),1);
}

/* Local function.*/
void ep_add_expense::EP_AddExpense_ConnectToED()
{
   /*Connect to Event dispatcher.*/
   connect(this->EP_BaseClass_GetEDPointer(),SIGNAL(EP_ED_RM_AddExpenseStatus(int)),this,SLOT(EP_AE_AddedExpenseStatus(int)));
}

void ep_add_expense::EP_AE_InitializeComboBoxValues()
{
    /*TO DO CHECK FOR EMPTY container.*/
    int CounterOfExpGroups = 0;
    ui->comboBox->clear();
    /*Add items to combobox.*/
    for(int i =0 ; i < (this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().count()+1);i++)
    {
        /*Get all available items.*/
        if(i < this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().count())
        {
            if(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().at(i).at(2) != "Income")
            {
                ui->comboBox->addItem(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().at(i).at(2),Qt::DisplayRole);
                ui->comboBox->setEditable(false);
                ui->comboBox->setCurrentIndex(CounterOfExpGroups);
                this->AllAvalExpTypes.append(this->EP_BaseClass_GetUserDataPointer()->EP_UserData_Get_activeUserExpGroups().at(i).at(2));
            }
        }
        else
        {
            /*Add last item as New.*/
            ui->comboBox->addItem("New",Qt::DisplayRole);
            ui->comboBox->setEditable(false);
            ui->comboBox->setCurrentIndex(CounterOfExpGroups);
        }
    }
}

/*Slots*/
void ep_add_expense::EP_AE_AddedExpenseStatus(int Status)
{
    /*Extend if you need further error handling.*/
    QMessageBox msg;
    switch (Status) {
        case -3:
           msg.setText("User not available.");
        break;
        case -2:
           msg.setText("Expense group not added correctly, please restart program and check DB connection.");
        break;
        case -1:
           msg.setText("Database is not connected ... Do you know what you are doing?");
        break;
        case 0:
           msg.setText("Expense succesfully added!");
           /*Request welcome screen update of money.*/
           emit this->EP_BaseClass_GetEDPointer()->EP_ED_WlcScreenUpdateCurrentUserData();
        break;
        case 1:
           msg.setText("Expense group already exists ...");
        break;
        case 2:
           msg.setText("Email alredy in system ...");
        break;
    }
    msg.setWindowTitle("Add expense status");
    msg.exec();
}

void ep_add_expense::EP_AE_MakeLastLineEditable(int CurrentIndex)
{
    /*Make comboBox editable only if new/Last index is selected.*/
    if(CurrentIndex == (this->ui->comboBox->count() - 1))
    {
        this->ui->comboBox->setEditable(true);
        QCompleter *newCompleter = (this->AllAvalExpTypes,nullptr);
        this->ui->comboBox->setCompleter(newCompleter);
    }
    else
    {
        this->ui->comboBox->setEditable(false);
    }
}

bool ep_add_expense::eventFilter(QObject *obj, QEvent *event)
{
    if ((event->type() == QEvent::FocusOut))
    {
        if(true == ui->comboBox->isEditable())
        {
            /*Change policy to add before this index.*/
            ui->comboBox->setInsertPolicy(QComboBox::InsertBeforeCurrent);
            /*Get user input.*/
            QString userInput = ui->comboBox->currentText();
            /*Check if current string is empty.*/
            if(userInput != " ")
            {
                /*Search if text is already available.*/
                int FindTextResult = ui->comboBox->findText(userInput, Qt::MatchCaseSensitive);
                if(FindTextResult != -1)
                {
                    ui->comboBox->setEditable(false);
                    ui->comboBox->setCurrentIndex(ui->comboBox->count()-2);

                    return false;
                }
                else
                {
                    ui->comboBox->setItemText(ui->comboBox->count()-1, userInput);
                    ui->comboBox->setEditable(false);
                    ui->comboBox->addItem("New",Qt::DisplayRole);
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
