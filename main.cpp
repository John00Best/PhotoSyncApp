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

    qRegisterMetaType<QFileInfoList>("QFileInfoList");
    qmlRegisterType<FileSyncMaster>("com.FileSyncMaster", 1, 0, "FileSyncMaster");

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

    QObject::connect(&master, SIGNAL(syncChanged(QVariant,QVariant)),
                     item, SIGNAL(syncChanged(QVariant,QVariant)));

    QObject::connect(item, SIGNAL(startSync()),
                     &master, SLOT(startSync()));

    QObject::connect(&app, SIGNAL(aboutToQuit()),
                     &master, SLOT(closing()));

    return app.exec();
}
