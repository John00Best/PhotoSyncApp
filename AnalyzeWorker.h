#ifndef ANALYZEWORKER_H
#define ANALYZEWORKER_H

#include <QRunnable>
#include <QFileInfoList>

class AnalyzeWorker : public QRunnable
{
    Q_OBJECT
public:
    AnalyzeWorker(const QString& folderPath);
    void run() override;
signals:
    void finished(QFileInfoList results);

private:
    QString m_folderPath;
};

#endif // ANALYZEWORKER_H
