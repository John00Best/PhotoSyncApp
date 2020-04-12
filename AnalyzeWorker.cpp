#include "AnalyzeWorker.h"
#include <QDir>
#include <QtDebug>
#include <QFileInfo>
#include <QFileInfoList>

AnalyzeWorker::AnalyzeWorker(const QString& folderPath)
    : m_folderPath(folderPath)
{

}

void AnalyzeWorker::run()
{
    QFileInfoList folderList;
    folderList.append(QFileInfo(m_folderPath));
    QFileInfoList foundImageResults;
    while (!folderList.isEmpty()) {
        QFileInfo currentFolder = folderList.takeFirst();

        auto dir = QDir(currentFolder.absoluteFilePath());
        qInfo()<<"Parsing: "<<dir.absolutePath()<< " Dir is readable: "<<dir.isReadable();

        folderList.append(dir.entryInfoList( {"*"},QDir::Dirs | QDir::NoDotAndDotDot));

        dir.setNameFilters({"*.jpg"});
        foundImageResults.append(dir.entryInfoList(QDir::Files));
    }

    emit finished(foundImageResults);
}
