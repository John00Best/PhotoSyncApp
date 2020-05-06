#ifndef FILESYNCMASTER_H
#define FILESYNCMASTER_H

#include <QObject>
#include <QVariant>
#include <QFileInfoList>
#include <QThreadPool>
#include <QMutex>
#include <QFuture>
#include <QSettings>


#include "AnalyzeWorker.h"

class FileSyncMaster : public QObject
{
    Q_OBJECT
public:
    explicit FileSyncMaster(QObject *parent = nullptr);
    void init();


public slots:
    void startFilePasring(QVariant src,QVariant dest);
    void finalizeParsing();
    void startSync();
    void closing();

signals:
    void syncChanged(QVariant syncDone,QVariant syncTotal);
    void syncChangedTotal(QVariant syncDone,QVariant syncTotal);
    void initSrcDestDirectory(QVariant srcDir,QVariant destDir);

private:
    uint m_fileIsAlreadySynced;
    AnalyzeWorker m_srcFolderWorker;
    QString m_srcDirectory;
    QString m_destDirectory;
    QSettings m_qSettings;
    QThreadPool m_threadPool;
    QList<QFuture<void>> m_threadStatusList;
    QList<QPair<QFileInfo,QFileInfo>> m_imageSyncPair;
    void startSyncDet();

    void scaleImage(const QFileInfo&  src,const QFileInfo&  dest);
    void checkDestDir(const QFileInfo&  dest);

    void printPoolStatus();
};

#endif // FILESYNCMASTER_H
