#ifndef FOLDERWORKER_H
#define FOLDERWORKER_H

#include <QRunnable>
#include <QFileInfoList>
#include <QDir>
#include <QDebug>
#include <QObject>


class FolderWorker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    FolderWorker(QFileInfo dirFileInfo) :
        m_dirFileInfo(dirFileInfo)
    {

    }

    void run()
    {
        if(m_dirFileInfo.isReadable()) {
            auto dir = QDir(m_dirFileInfo.absoluteFilePath());
            //qInfo()<<"Parsing: "<<dir.absolutePath()<< " Dir is readable: "<<dir.isReadable();

            emit newFolderResults(dir.entryInfoList( {"*"},QDir::Dirs | QDir::NoDotAndDotDot));

            dir.setNameFilters({"*.jpg"});
            emit newImageResults(dir.entryInfoList(QDir::Files));
        } else {
            qCritical()<<m_dirFileInfo.absolutePath()<< " unreadable";
        }
    }

signals:
    void newFolderResults(QFileInfoList results);
    void newImageResults(QFileInfoList results);
public:

    QFileInfo m_dirFileInfo;
};

#endif // FOLDERWORKER_H
