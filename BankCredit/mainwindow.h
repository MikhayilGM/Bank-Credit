#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <addclient.h>
#include <checkclient.h>
#include <searchclient.h>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_AddClient_clicked();

    void on_SearchClient_clicked();

    void on_CheckClient_clicked();

private:
    Ui::MainWindow *ui;
    AddClient* addclient {nullptr};
    SearchClient* searchlient {nullptr};
    CheckClient* checkclient {nullptr};

};
#endif // MAINWINDOW_H
