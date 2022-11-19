#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QFile styles("C:/Users/segbu/OneDrive/Документы/BankCredit/style.css");
    styles.open(QFile::ReadOnly);
    QApplication a(argc, argv);
    a.setStyleSheet(styles.readAll());
    MainWindow w;
    w.show();
    return a.exec();
}
