#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "FileSyncMaster.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("somename");
    app.setOrganizationDomain("somename");
    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);
    QObject *item = engine.rootObjects().first();
    QVariant len = engine.rootObjects().length();

    FileSyncMaster master;
    QObject::connect(item, SIGNAL(startPressed(QVariant,QVariant)),
                      &master, SLOT(startFilePasring(QVariant,QVariant)));


    return app.exec();
}
