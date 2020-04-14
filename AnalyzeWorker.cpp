#include <QDir>
#include <QtDebug>
#include <QFileInfo>
#include <QFileInfoList>
#include <QThreadPool>

#include "AnalyzeWorker.h"
#include "FolderWorker.h"


void AnalyzeWorker::startFilePasring(QFileInfo startDir)
{
    m_folderList.clear();
    m_foundImageResults.clear();
    m_folderList.append(startDir);
    restartDirAnalzyer();
}


void AnalyzeWorker::folderResults(QFileInfoList results)
{
    m_dirMutex.lock();
    m_folderList.append(results);
    //qDebug()<<"folderResults() adding : "<<results.length()<<" new folders. Total: "<<m_folderList.length();
    m_dirMutex.unlock();
    restartDirAnalzyer();
}


void AnalyzeWorker::imageResults(QFileInfoList results)
{
    m_imgMutex.lock();
    m_foundImageResults.append(results);
    //qDebug()<<"imageResults() adding : "<<results.length()<<" new images. Total: "<<m_foundImageResults.length();
    m_imgMutex.unlock();
    checkIfDone();
}

void AnalyzeWorker::restartDirAnalzyer()
{
    while (!m_folderList.isEmpty()) {
        FolderWorker* worker = new FolderWorker(m_folderList.takeFirst());
        //qDebug()<<"restartDirAnalzyer() Working on : "<<worker->m_dirFileInfo.absoluteFilePath();
        connect(worker,&FolderWorker::newFolderResults,this,&AnalyzeWorker::folderResults);
        connect(worker,&FolderWorker::newImageResults,this,&AnalyzeWorker::imageResults);
        m_threadPool.start(worker);
    }
    checkIfDone();
}


void AnalyzeWorker::checkIfDone()
{
    if(m_threadPool.activeThreadCount() == 0) {
        qDebug()<<"Analzyer Done";
        emit parsingFinished();
    }
}

