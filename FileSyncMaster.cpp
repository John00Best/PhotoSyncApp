#include "FileSyncMaster.h"
#include <QtDebug>
#include <QVariant>

FileSyncMaster::FileSyncMaster(QObject *parent) : QObject(parent)
{

}


void FileSyncMaster::startFilePasring(QVariant src,QVariant dest) {
    qInfo()<<"startFileParsing() Source: "<<src.toString()<<" Destination "<<dest.toString();
}
