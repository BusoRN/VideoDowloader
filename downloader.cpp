#include "downloader.h"
const QString FLAG_ON = " True ";
const QString FLAG_OFF = " False ";

Downloader::Downloader(QObject *parent, QString file_name) : QObject(parent)
{
    name = file_name;
    status = 1;//1
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(doDownload()));
    timer->start(1000000);
}

Downloader::~Downloader()
{

}

void Downloader::setName(QString new_name)
{
    name = new_name;
}

void Downloader::doDownload()
{
    data = QDateTime::currentDateTime();
    name = "./"+data.toString("yyyy-MM-dd-HH:mm:ss")+".mp4";

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    if(status==0)
    {
   //     manager->get(QNetworkRequest(QUrl("http://planar-contact-601.appspot.com/electrovalves/video")));
        manager->get(QNetworkRequest(QUrl("http://planar-contact-601.appspot.com/video/view")));
    }
    else
    {
      manager->get(QNetworkRequest(QUrl("http://planar-contact-601.appspot.com/electrovalves/video")));
    }
}

void Downloader::replyFinished (QNetworkReply *reply)
{

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        if(status==0)
        {
            QFile *file = new QFile(name);


            if(file->open(QFile::Append))
            {
                file->write(reply->readAll());
                file->flush();
                file->close();
            }
            delete file;
            status = 1;
        }
        else
        {
           QString result(reply->readAll());
           status = QString::compare(result, FLAG_ON);
          qDebug() << QString::number(status);
          if(status == 0)
           {
               QUrl flag_url = QUrl("http://planar-contact-601.appspot.com/add/electrovalve");
               QByteArray postData;
               postData.append("name=video&status=off");
              manager->post(QNetworkRequest(flag_url), postData);
           }
           else
               status = 1;
        }

//        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
//        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();;
//        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
//        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
//        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

    }

    reply->deleteLater();
}
