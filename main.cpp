#include <QCoreApplication>
#include <QTimer>
#include "downloader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDateTime data;
    data = QDateTime::currentDateTime();
    QString name = "./"+data.toString("yyyy-MM-dd-HH:mm:ss")+".mp4";
    Downloader d(0,name);
    d.doDownload();




    return a.exec();
}
