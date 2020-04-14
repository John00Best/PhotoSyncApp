#ifndef ANALYZEWORKER_H
#define ANALYZEWORKER_H

#include <QRunnable>
#include <QFileInfoList>
#include <QDir>
#include <QDebug>
#include <QObject>
#include <QMutex>


class AnalyzeWorker : public QObject
{
    Q_OBJECT
public:
    QFileInfoList m_foundImageResults;

public slots:
    void startFilePasring(QFileInfo startDir);
    void folderResults(QFileInfoList results);
    void imageResults(QFileInfoList results);

private:
    QMutex m_dirMutex,m_imgMutex;;
    QFileInfoList m_folderList;

    void restartDirAnalzyer();
};

#endif // ANALYZEWORKER_H
