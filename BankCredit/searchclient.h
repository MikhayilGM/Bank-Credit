#ifndef SEARCHCLIENT_H
#define SEARCHCLIENT_H

#include <QMainWindow>
#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>


namespace Ui {
class SearchClient;
}

class SearchClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchClient(QWidget *parent = nullptr);
    ~SearchClient();

private slots:
    void on_dateEdit_userDateChanged(const QDate &date);

    void on_lineName_editingFinished();

    void on_lineSurname_editingFinished();

    void on_linePassCode_editingFinished();

    void on_linePhone_editingFinished();

    void on_pushButton_clicked();

private:
    Ui::SearchClient *ui;
};

#endif // SEARCHCLIENT_H
