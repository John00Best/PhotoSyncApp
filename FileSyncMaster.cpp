#include <QtDebug>
#include <QVariant>
#include <QThreadPool>
#include <QDir>
#include <QFuture>
#include <QtConcurrent>

#include "FileSyncMaster.h"

FileSyncMaster::FileSyncMaster(QObject *parent) : QObject(parent)
{

}


void FileSyncMaster::startFilePasring(QVariant src,QVariant dest) {
    qInfo()<<"startFileParsing() Source: "<<src.toString()<<" Destination "<<dest.toString();
    m_srcFolderWorker.startFilePasring(src.toString().replace("file://",""));
    m_destFolderWorker.startFilePasring(dest.toString().replace("file://",""));
}


