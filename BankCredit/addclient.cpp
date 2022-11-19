#include "addclient.h"
#include "ui_addclient.h"


AddClient::AddClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddClient)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Add Client");
}

AddClient::~AddClient()
{
    delete ui;
}


void AddClient::on_pushButton_clicked()
{
    if(ui -> lineName -> text() == "" || ui -> lineSurname -> text() == "" || ui -> linePassCode -> text() == "" || ui -> linePhone -> text() == "" || ui -> lineIncome -> text() == "" || ui -> lineSavings -> text() == "" || ui -> lineStory -> text() == "")
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Some of your lines is empty, please enter the information", QMessageBox::Ok);
        return;
    }


    QFile file("C:/Users/segbu/OneDrive/Документы/GitHub/BankCredit/Clients.txt");
    file.open(QFile::ReadWrite);
    QTextStream in(&file);
    QString str;
    std::vector<QString> strs;
    while(!in.atEnd())
    {
        strs.push_back(in.readLine());
    }

    for (int i = 0; i < strs.size(); ++i)
    {
        if(strs[i].contains(ui-> linePassCode -> text()) || strs[i].contains(ui-> linePhone -> text()))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Already Exist", "Client with this Passport code or Phone Number already exists", QMessageBox::Ok);
            return;
        }
    }

    QMessageBox::StandardButton qMessage = QMessageBox::question(this, "Are you sure?", "Sign Up?", QMessageBox::Yes | QMessageBox::Cancel);
    if(qMessage == QMessageBox::Yes)
    {
        QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Added", "You Signed Up", QMessageBox::Ok);
        in << "name: " << ui -> lineName -> text() << " surname: " << ui -> lineSurname -> text() << " birthdate: " << ui -> dateEdit -> date().toString("dd.MM.yyyy")  << " passcode: " << ui -> linePassCode -> text() << " phonenumber: " << ui -> linePhone -> text() << " income: " << ui -> lineIncome -> text() << " savigs: " << ui -> lineSavings -> text() << " story: " << ui -> lineStory -> text() << "\n";
    }
    else
    {
        QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Canceled", "Signing Up is Canceled", QMessageBox::Ok);
    }
}

void AddClient::on_dateEdit_userDateChanged(const QDate &date)
{
    if(QDate::currentDate().year() - date.year() < 16)
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "You must be more than 16 years old", QMessageBox::Ok);
        ui -> dateEdit -> setDate(QDate(2000, 1, 1));
        return;
    }
    else if (QDate::currentDate().year() - 16 == date.year() && QDate::currentDate().month() < date.month())
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "You must be more than 16 years old", QMessageBox::Ok);
        ui -> dateEdit -> setDate(QDate(2000, 1, 1));
        return;
    }

}


void AddClient::on_lineName_editingFinished()
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

void AddClient::on_lineSurname_editingFinished()
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



void AddClient::on_linePassCode_editingFinished()
{
    QString str = ui -> linePassCode -> text();
    if(str.length() != 9)
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your enter Passport Code entered incorrectly, please try it again", QMessageBox::Ok);
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


void AddClient::on_linePhone_editingFinished()
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


void AddClient::on_lineIncome_editingFinished()
{
    QString str = ui -> lineIncome -> text();
    bool comma = 1;
    for(int i = 0; i < str.length(); ++i)
    {
        if(!(str[i].toLatin1()>='0' && str[i].toLatin1()<='9'))
        {
            if(str[i].toLatin1() == ',' && comma)
            {
                str[i] = '.';
                comma = 0;
                ui -> lineIncome -> setText(str);
            }
            else
            {
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Income entered incorrectly, please try it again", QMessageBox::Ok);
                ui -> lineIncome -> setText("");
                return;
            }
        }
    }
}

void AddClient::on_lineSavings_editingFinished()
{
    QString str = ui -> lineSavings -> text();
    bool comma = 1;
    for(int i = 0; i < str.length(); ++i)
    {
        if(!(str[i].toLatin1()>='0' && str[i].toLatin1()<='9'))
        {
            if(str[i].toLatin1() == ',' && comma)
            {
                str[i] = '.';
                comma = 0;
                ui -> lineSavings -> setText(str);
            }
            else
            {
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Savings entered incorrectly, please try it again", QMessageBox::Ok);
                ui -> lineSavings -> setText("");
                return;
            }
        }
    }
}


void AddClient::on_lineStory_editingFinished()
{
    QString str = ui -> lineStory -> text();

    if(str != "Good" && str != "Bad" && str != "None")
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Story entered incorrectly, please try it again(It must be 'Good', 'Bad' or 'None')", QMessageBox::Ok);
        ui -> lineStory -> setText("");
        return;
    }

}
