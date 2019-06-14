#ifndef UPLOADER_H
#define UPLOADER_H

#include <QTcpSocket>
#include <QFile>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonParseError>

#include "Server.h"
#include "items/downloaditem.h"

class Uploader : public QObject
{
    Q_OBJECT
public:
    explicit Uploader(QObject *parent = nullptr);
    virtual ~Uploader();

    void setIp(const QString &ip);
    QString getIp() const;
    void uploadFile(DownloadItem *item) const;
    void connectToServer();
    void setFiles(QList<DownloadItem *> files);
    void sendFileInfo(const QString &path, const QString &size);

private:
    QString ip;
    QTcpSocket *socket;
    QFile *file;
    const qint64 BUFFER_SIZE = 327680;
    quint16 port = 4448;
    QString head = "\"type\":\"p2p_connected\", \"status\":\"OK\"";
    QJsonDocument doc;
    QJsonParseError docError;
    QList<DownloadItem *> files;

signals:
    void blockUploaded(DownloadItem *item, const int progress) const;
    void fileUploaded() const;
    void connected();
    void startUploading(const QString &path);

public slots:
    void socketReady();
    void socketDisconnect();
};

#endif // UPLOADER_H
