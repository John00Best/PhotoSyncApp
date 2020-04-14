#ifndef FILESYNCMASTER_H
#define FILESYNCMASTER_H

#include <QObject>
#include <QVariant>
#include <QFileInfoList>
#include <QThreadPool>
#include <QMutex>
#include <QFuture>


#include "AnalyzeWorker.h"

class FileSyncMaster : public QObject
{
    Q_OBJECT
public:
    explicit FileSyncMaster(QObject *parent = nullptr);


public slots:
    void startFilePasring(QVariant src,QVariant dest);
    void startSync();
    void closing();

signals:
       void syncChanged(QVariant syncDone,QVariant syncTotal);
       void syncChangedTotal(QVariant syncDone,QVariant syncTotal);

private:
    AnalyzeWorker m_srcFolderWorker;
    AnalyzeWorker m_destFolderWorker;
    QString m_srcDirectory;
    QString m_destDirectory;
    QThreadPool m_threadPool;
    QList<QFuture<void>> m_threadStatusList;
    int m_syncDone;
    int m_syncTotal;

    //void scaleImage(const QFileInfo&  src,const QFileInfo&  dest);
    void checkDestDir(const QFileInfo&  dest);

    void printPoolStatus();
};

#endif // FILESYNCMASTER_H
