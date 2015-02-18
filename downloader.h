#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>
#include <QDebug>
#include <QTimer>

class Downloader : public QObject
{

    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0, QString file_name = "fabio.mp4");
    ~Downloader();

    void setName(QString new_name);

    void doDownload();

signals:

public slots:
    void replyFinished (QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QString name;
    int status;
    QDateTime data;

};

#endif // DOWNLOADER_H
