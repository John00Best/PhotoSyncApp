#ifndef FILESYNCMASTER_H
#define FILESYNCMASTER_H

#include <QObject>
#include <QVariant>


class FileSyncMaster : public QObject
{
    Q_OBJECT
public:
    explicit FileSyncMaster(QObject *parent = nullptr);

public slots:
    void startFilePasring(QVariant src,QVariant dest);
};

#endif // FILESYNCMASTER_H
