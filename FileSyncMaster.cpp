#include "FileSyncMaster.h"
#include <QtDebug>
#include <QVariant>
#include <QThreadPool>
#include "AnalyzeWorker.h"

FileSyncMaster::FileSyncMaster(QObject *parent) : QObject(parent)
{

}


void FileSyncMaster::startFilePasring(QVariant src,QVariant dest) {
    qInfo()<<"###startFileParsing() Source: "<<src.toString()<<" Destination "<<dest.toString();

    AnalyzeWorker *worker = new AnalyzeWorker(src.toString().replace("file:///",""));
    // QThreadPool takes ownership and deletes 'hello' automatically
    connect(worker,&AnalyzeWorker::finished,this,&FileSyncMaster::dirAnalzyerFinished);
    QThreadPool::globalInstance()->start(worker);
}


void FileSyncMaster::dirAnalzyerFinished(QFileInfoList results)
{
    m_mutex.lock();
    m_sourceFileList.append(results);
    m_mutex.unlock();
}
