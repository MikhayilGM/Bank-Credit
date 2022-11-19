#ifndef ADDCLIENT_H
#define ADDCLIENT_H

#include <QMainWindow>
#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <vector>

namespace Ui {
class AddClient;
}

class AddClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddClient(QWidget *parent = nullptr);
    ~AddClient();

private slots:


    void on_pushButton_clicked();

    void on_lineName_editingFinished();

    void on_lineStory_editingFinished();

    void on_lineSurname_editingFinished();

    void on_linePassCode_editingFinished();

    void on_linePhone_editingFinished();

    void on_lineIncome_editingFinished();

    void on_lineSavings_editingFinished();

    void on_dateEdit_userDateChanged(const QDate &date);

private:
    Ui::AddClient *ui;
};

#endif // ADDCLIENT_H
