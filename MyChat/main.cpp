#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/style/stylesheet.qss");
    if(file.open(QFile::ReadOnly| QIODevice::Text)){
        qDebug("open success");
        QTextStream stream(&file);
        QString qss = stream.readAll();
        a.setStyleSheet(qss);
        file.close();
    }
    else {
        qDebug("open failed");
    }


    MainWindow w;
    w.show();
    return a.exec();
}
