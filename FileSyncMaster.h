#ifndef FILESYNCMASTER_H
#define FILESYNCMASTER_H

#include <QObject>

class FileSyncMaster : public QObject
{
    Q_OBJECT
public:
    explicit FileSyncMaster(QObject *parent = nullptr);

public slots:
    void startFilePasring();
};

#endif // FILESYNCMASTER_H
