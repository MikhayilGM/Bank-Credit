#include "searchclient.h"
#include "ui_searchclient.h"

SearchClient::SearchClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchClient)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Search Client");
}

SearchClient::~SearchClient()
{
    delete ui;
}

void SearchClient::on_pushButton_clicked()
{
    if(ui -> lineName -> text() == "" || ui -> lineSurname -> text() == "" || ui -> linePassCode -> text() == "" || ui -> linePhone -> text() == "")
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Some of your lines is empty, please enter the information", QMessageBox::Ok);
        return;
    }

    QFile file("C:/Users/segbu/OneDrive/Документы/GitHub/BankCredit/Clients.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString str;
    std::vector<QString> strs;

    while(!in.atEnd())
    {
        in >> str;
        strs.push_back(str);
    }
    for (int i = 0; i < strs.size(); i += 16)
    {
        if(strs[i+1] == ui -> lineName -> text() && strs[i+3] == ui -> lineSurname -> text() && strs[i+5] == ui -> dateEdit -> date().toString("dd.MM.yyyy") && strs[i+7] == ui -> linePassCode -> text() && strs[i+9] == ui -> linePhone -> text())
        {
              QString tmp = "Your Income is " + strs[i+11] + ", Savings is " + strs[i+13] + " and Story is " + strs[i+15];
              QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Already Exist", tmp, QMessageBox::Ok);
              return;

        }
    }


    QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Not Client", "Your not our Client, please Sign Up", QMessageBox::Ok);
    return;
}


void SearchClient::on_dateEdit_userDateChanged(const QDate &date)
{
        if(QDate::currentDate().year() - date.year() < 16)
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "You must be older than 16 years old", QMessageBox::Ok);
            ui -> dateEdit -> setDate(QDate(2000, 1, 1));
            return;
        }
        else if (QDate::currentDate().year() - 16 == date.year() && QDate::currentDate().month() < date.month())
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "You must be older than 16 years old", QMessageBox::Ok);
            ui -> dateEdit -> setDate(QDate(2000, 1, 1));
            return;
        }
}


void SearchClient::on_lineName_editingFinished()
{
    QString str = ui -> lineName -> text();

    if(!(str[0].toLatin1()>='A' && str[0].toLatin1()<='Z'))
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Name must start with Upper letter, please try it again", QMessageBox::Ok);
        ui -> lineName -> setText("");
        return;
    }

    for(int i = 1; i < str.length(); ++i)
    {
        if(!(str[i].toLatin1()>='a' && str[i].toLatin1()<='z'))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Name entered incorrectly, please try it again", QMessageBox::Ok);
            ui -> lineName -> setText("");
            return;
        }
    }
}

void SearchClient::on_lineSurname_editingFinished()
{
    QString str = ui -> lineSurname -> text();

    if(!(str[0].toLatin1()>='A' && str[0].toLatin1()<='Z'))
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Surname must start with Upper letter, please try it again", QMessageBox::Ok);
        ui -> lineSurname -> setText("");
        return;
    }

    for(int i = 1; i < str.length(); ++i)
    {
        if(!(str[i].toLatin1()>='a' && str[i].toLatin1()<='z'))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Surname entered incorrectly, please try it again", QMessageBox::Ok);
            ui -> lineSurname -> setText("");
            return;
        }
    }

}



void SearchClient::on_linePassCode_editingFinished()
{
    QString str = ui -> linePassCode -> text();
    if(str.length() != 9)
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Passport Code entered incorrectly, please try it again", QMessageBox::Ok);
        ui -> linePassCode -> setText("");
        return;
    }
    int i = 0;
    for(; i < 2; ++i)
    {
        if(!(str[i].toLatin1()>='A' && str[i].toLatin1()<='Z'))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Passport Code entered incorrectly, please try it again", QMessageBox::Ok);
            ui -> linePassCode -> setText("");
            return;
        }
    }
    for(; i < 9; ++i)
    {
        if(!(str[i].toLatin1()>='0' && str[i].toLatin1()<='9'))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Passport Code entered incorrectly, please try it again", QMessageBox::Ok);
            ui -> linePassCode -> setText("");
            return;
        }
    }
}


void SearchClient::on_linePhone_editingFinished()
{
    QString str = ui -> linePhone -> text();

    if(str.length() != 9)
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Phone entered incorrectly, please try it again", QMessageBox::Ok);
        ui -> linePhone -> setText("");
        return;
    }

    for(int i = 0; i < str.length(); ++i)
    {
        if(!(str[i].toLatin1()>='0' && str[i].toLatin1()<='9'))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Phone entered incorrectly, please try it again", QMessageBox::Ok);
            ui -> linePhone -> setText("");
            return;
        }
    }

}
