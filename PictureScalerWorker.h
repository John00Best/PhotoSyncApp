#ifndef PICTURESCALLERWORKER_H
#define PICTURESCALLERWORKER_H
#include <QRunnable>
#include <QFileInfo>
#include <QDebug>
#include <QImage>


class PictureScalerWorker : public QRunnable
{

public:
    PictureScalerWorker(QFileInfo src,QFileInfo dest) :
        m_src(src),
        m_dest(dest)
    {

    }

    void run()
    {
        QImage srcImage(m_src.absoluteFilePath());
        QImage destImage = srcImage.scaledToHeight(800,Qt::SmoothTransformation);
        bool ret = destImage.save(m_dest.absoluteFilePath());
        if(!ret)
        {
            qInfo()<<"Save File: "<<m_dest.absoluteFilePath()<<" result: "<<(ret ? "true" : "false")<<": "<<destImage.size();
        }
    }
public:

    QFileInfo m_src;
    QFileInfo m_dest;
};

#endif // PICTURESCALLERWORKER_H
