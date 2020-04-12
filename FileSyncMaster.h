#ifndef FILESYNCMASTER_H
#define FILESYNCMASTER_H

#include <QObject>
#include <QVariant>
#include <QFileInfoList>
#include <QMutex>


class FileSyncMaster : public QObject
{
    Q_OBJECT
public:
    explicit FileSyncMaster(QObject *parent = nullptr);

public slots:
    void startFilePasring(QVariant src,QVariant dest);
    void dirAnalzyerFinished(QFileInfoList results);

private:
    QFileInfoList m_sourceFileList;
    QMutex m_mutex;
};

#endif // FILESYNCMASTER_H
