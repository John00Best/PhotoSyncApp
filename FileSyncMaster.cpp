#include "FileSyncMaster.h"
#include <QtDebug>


FileSyncMaster::FileSyncMaster(QObject *parent) : QObject(parent)
{

}


void FileSyncMaster::startFilePasring() {
    qInfo()<<"startFileParsing()";
}
