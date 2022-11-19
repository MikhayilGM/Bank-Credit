#ifndef CHECKCLIENT_H
#define CHECKCLIENT_H

#include <QMainWindow>
#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <vector>


namespace Ui {
class CheckClient;
}

class CheckClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit CheckClient(QWidget *parent = nullptr);
    ~CheckClient();

private slots:
    void on_lineName_editingFinished();

    void on_lineSurname_editingFinished();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_linePassCode_editingFinished();

    void on_linePhone_editingFinished();

    void on_lineAoC_editingFinished();

    void on_lineMC_editingFinished();

    void on_pushButton_clicked();

    void on_lineBankName_editingFinished();

private:
    Ui::CheckClient *ui;
};

#endif // CHECKCLIENT_H
