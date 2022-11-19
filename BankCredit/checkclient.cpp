#include "checkclient.h"
#include "ui_checkclient.h"

CheckClient::CheckClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CheckClient)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Check Client");
}

CheckClient::~CheckClient()
{
    delete ui;
}

void CheckClient::on_pushButton_clicked()
{
    if(ui -> lineName -> text() == "" || ui -> lineSurname -> text() == "" || ui -> linePassCode -> text() == "" || ui -> linePhone -> text() == "" || ui -> lineAoC -> text() == "" || ui -> lineMC -> text() == "")
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Some of your lines is empty, please enter the information", QMessageBox::Ok);
        return;
    }

   QString str = ui -> lineMC -> text();

   double percentage = 0;
   switch (str.toInt())
   {
   case 12:
       percentage = 1.1;
       break;
   case 18:
       percentage = 1.15;
       break;
   case 24:
       percentage = 1.2;
       break;
   case 36:
       percentage = 1.25;
       break;
   }

   QFile clients("C:/Users/segbu/OneDrive/Документы/GitHub/BankCredit/Clients.txt");
   clients.open(QFile::ReadOnly);

   QFile credits("C:/Users/segbu/OneDrive/Документы/GitHub/BankCredit/Credits.txt");
   credits.open(QFile::ReadWrite);

   QTextStream clientsin(&clients);
   QTextStream creditsin(&credits);

   std::vector<QString> clientsstr;
   std::vector<QString> creditsstr;

   while(!clientsin.atEnd())
   {
       clientsin >> str;
       clientsstr.push_back(str);
   }

   while(!creditsin.atEnd())
   {
       str = creditsin.readLine();
       creditsstr.push_back(str);
   }

   for (int i = 0; i < clientsstr.size(); i += 16)
   {
       if(clientsstr[i+1] == ui -> lineName -> text() && clientsstr[i+3] == ui -> lineSurname -> text() && clientsstr[i+5] == ui -> dateEdit -> date().toString("dd.MM.yyyy") && clientsstr[i+7] == ui -> linePassCode -> text() && clientsstr[i+9] == ui -> linePhone -> text())
       {
             signed char story = 0;

             if (clientsstr[i+15] == "Good")
             {
                 story = 2;
             }
             else if(clientsstr[i+15] == "Bad")
             {
                 story = (-2);
             }

             int status = ((int((clientsstr[i+11].toDouble()/(ui -> lineAoC -> text().toDouble() * percentage / ui -> lineMC -> text().toDouble())) - 1)) % 5 + (int(clientsstr[i+13].toDouble() / (ui -> lineAoC -> text().toDouble() * percentage)) % 5) + story) / 5;
             if(status)
             {
                 unsigned int creditcount = 0;

                 for(int j = 0; j < creditsstr.size(); ++j)
                 {
                     if(creditsstr[j].contains(ui -> linePassCode -> text()) && creditsstr[j].contains(ui -> linePhone -> text()))
                     {
                        if(creditsstr[j].contains(ui -> lineBankName -> text()))
                        {
                            ++creditcount;
                            if(creditcount > 1)
                            {
                                 QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Credit", "Credit is Disapproved, You must have less then 2 Credits", QMessageBox::Ok);
                                 return;
                            }
                        }
                        else
                        {
                             QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Credit", "Credit is Disapproved, You Can Not have 2 Credits from Different Banks", QMessageBox::Ok);
                             return;
                        }
                     }
                 }

                 QMessageBox::StandardButton qMessage = QMessageBox::question(this, "Credit", "Your Credit Request is Approved, please Accept it", QMessageBox::Yes | QMessageBox::No);
                 if(qMessage == QMessageBox::Yes)
                 {
                     creditsin << "passcode: " << ui -> linePassCode -> text() << " phone: " << ui -> linePhone -> text() << " bankname: " << ui -> lineBankName -> text() << " amountofcredit: " << ui -> lineAoC -> text() << " monthscount: " << ui -> lineMC -> text() << "\n";
                     QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Credit", "Credit Request is Approved", QMessageBox::Ok);
                 }
                 else
                 {
                     QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Credit", "Credit Request is Canceled", QMessageBox::Ok);
                 }
             }
             else
             {
                 QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Credit", "Credit is Disapproved", QMessageBox::Ok);
             }
             return;

       }

   }

   QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Client", "Your are not Signed Up, please Sign Up before requesting a Credit", QMessageBox::Ok);
}

void CheckClient::on_dateEdit_userDateChanged(const QDate &date)
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

void CheckClient::on_lineName_editingFinished()
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

void CheckClient::on_lineSurname_editingFinished()
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



void CheckClient::on_linePassCode_editingFinished()
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


void CheckClient::on_linePhone_editingFinished()
{
    QString str = ui -> linePhone -> text();

    if(str.length() != 9 || str[0].toLatin1() != '0')
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Phone entered incorrectly, please try it again", QMessageBox::Ok);
        ui -> linePhone -> setText("");
        return;
    }

    for(int i = 1; i < str.length(); ++i)
    {
        if(!(str[i].toLatin1()>='0' && str[i].toLatin1()<='9'))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Phone entered incorrectly, please try it again", QMessageBox::Ok);
            ui -> linePhone -> setText("");
            return;
        }
    }

}

void CheckClient::on_lineBankName_editingFinished()
{
    QString str = ui -> lineBankName -> text();

    for(int i = 0; i < str.length(); ++i)
    {
        if(!(str[i].toLatin1()>='a' && str[i].toLatin1()<='z') && !(str[i].toLatin1()>='A' && str[i].toLatin1()<='Z') && str[i].toLatin1()<=' ')
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Name entered incorrectly, please try it again", QMessageBox::Ok);
            ui -> lineBankName -> setText("");
            return;
        }
    }
}


void CheckClient::on_lineAoC_editingFinished()
{
    QString str = ui -> lineAoC -> text();
    bool comma = 1;
    for(int i = 0; i < str.length(); ++i)
    {
        if(!(str[i].toLatin1()>='0' && str[i].toLatin1()<='9'))
        {
            if(str[i].toLatin1() == ',' && comma)
            {
                str[i] = '.';
                comma = 0;
                ui -> lineAoC -> setText(str);
            }
            else
            {
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Amount of Credit entered incorrectly, please try it again", QMessageBox::Ok);
                ui -> lineAoC -> setText("");
                return;
            }
        }
    }
}



void CheckClient::on_lineMC_editingFinished()
{
    QString str = ui -> lineMC -> text();
    if(str.toInt() != 12 && str.toInt() != 18 && str.toInt() != 24 && str.toInt() != 36)
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your Mount Count must be 12, 18, 24 or 36, please try it again", QMessageBox::Ok);
        ui -> lineMC -> setText("");
        return;
    }
}
