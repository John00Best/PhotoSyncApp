#ifndef FILESYNCMASTER_H
#define FILESYNCMASTER_H

#include <QObject>
#include <QVariant>
#include <QFileInfoList>
#include <QMutex>


#include "AnalyzeWorker.h"

class FileSyncMaster : public QObject
{
    Q_OBJECT
public:
    explicit FileSyncMaster(QObject *parent = nullptr);

public slots:
    void startFilePasring(QVariant src,QVariant dest);

private:
    AnalyzeWorker m_srcFolderWorker;
    AnalyzeWorker m_destFolderWorker;
};

#endif // FILESYNCMASTER_H
