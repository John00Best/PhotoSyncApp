#include <QtDebug>
#include <QVariant>

#include <QImage>
#include <QDir>

#include <QThreadPool>
#include <QFuture>
#include <QtConcurrent>

#include "FileSyncMaster.h"

FileSyncMaster::FileSyncMaster(QObject *parent) :
    QObject(parent),
    m_fileIsAlreadySynced(0)
{
    m_threadPool.setMaxThreadCount(16);
    connect(&m_srcFolderWorker,&AnalyzeWorker::parsingFinished,this,&FileSyncMaster::finalizeParsing);
}

void FileSyncMaster::closing(){
    m_threadPool.clear();
    qInfo()<<"Threadpool cleared()";
}

void FileSyncMaster::startFilePasring(QVariant src,QVariant dest) {
    qInfo()<<"startFileParsing() Source: "<<src.toString()<<" Destination "<<dest.toString();
    m_srcDirectory = src.toString().replace("file://","");
    m_destDirectory = dest.toString().replace("file://","");
    m_srcFolderWorker.startFilePasring(m_srcDirectory);
}

void scaleImage(const QFileInfo&  src,const QFileInfo&  dest)
{
    QImage srcImage(src.absoluteFilePath());
    QImage destImage = srcImage.scaledToHeight(800,Qt::SmoothTransformation);
    bool ret = destImage.save(dest.absoluteFilePath());
    if(!ret)
    {
        qInfo()<<"Save File: "<<dest.absoluteFilePath()<<" result: "<<(ret ? "true" : "false")<<": "<<destImage.size();
    }
}

void FileSyncMaster::finalizeParsing()
{
    m_fileIsAlreadySynced = 0;

    foreach (const QFileInfo& srcFile, m_srcFolderWorker.m_foundImageResults)
    {
        QString relativeFilePathName = srcFile.absoluteFilePath().remove(m_srcDirectory,Qt::CaseInsensitive);
        QString destinationFilePath = m_destDirectory+relativeFilePathName;
        QFileInfo destFile(destinationFilePath);
        if(destFile.isReadable())
        {
            m_fileIsAlreadySynced++;
        } else
        {
            m_imageSyncPair.append(QPair<QFileInfo,QFileInfo>(srcFile,destFile));
        }
    }
    qInfo()<<"Files synced: "<<QString::number(m_fileIsAlreadySynced)<<"/"<<m_srcFolderWorker.m_foundImageResults.length();
    emit syncChangedTotal(m_fileIsAlreadySynced,m_srcFolderWorker.m_foundImageResults.length());
}

void FileSyncMaster::startSync()
{
    for (const QPair<QFileInfo,QFileInfo>& filePair : m_imageSyncPair)
    {
        checkDestDir(filePair.second); // create destDir if not already
        m_threadStatusList.append(QtConcurrent::run(&m_threadPool,this,&FileSyncMaster::scaleImage,filePair.first,filePair.second));
    }
    QtConcurrent::run(this,&FileSyncMaster::printPoolStatus);
}


void FileSyncMaster::checkDestDir(const QFileInfo&  dest)
{
    if(!dest.dir().isReadable())
    {
        bool ret = dest.dir().mkpath(dest.absolutePath());
        if(!ret)
        {
            qInfo()<<"Created Dir: "<<dest.absolutePath()<<" result: "<<(ret ? "true" : "false");
        }
    }
}

void FileSyncMaster::scaleImage(const QFileInfo&  src,const QFileInfo&  dest)
{
    QImage srcImage(src.absoluteFilePath());
    QImage destImage = srcImage.scaledToHeight(800,Qt::SmoothTransformation);
    bool ret = destImage.save(dest.absoluteFilePath());
    if(!ret)
    {
        qInfo()<<"Save File: "<<dest.absoluteFilePath()<<" result: "<<(ret ? "true" : "false")<<": "<<destImage.size();
    }
}

void FileSyncMaster::printPoolStatus()
{
    do
    {
        uint done = 0;
        foreach(QFuture<void> future,m_threadStatusList)
        {
            if(future.isFinished())
            {
                done++;
            }
        }
        emit syncChanged(QVariant(done),QVariant(m_threadStatusList.length()));
        emit syncChangedTotal(QVariant(m_fileIsAlreadySynced+done),QVariant(m_srcFolderWorker.m_foundImageResults.length()));
        //qInfo()<<"Status: "<<QString::number(done)<<"/"<<m_threadStatusList.length();
    } while(!m_threadPool.waitForDone(1000));
}
