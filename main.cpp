#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QQmlContext>

#include <QtQml>

#include "fishmanager.h"
#include "fish.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    FishManager* fishManager = new FishManager(&app);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/FishRandomizer/main.qml"));
    viewer.showExpanded();
    viewer.rootContext()->setContextProperty("fishManager",fishManager);
    qmlRegisterType<Fish>("Fishes",1,0,"FishObj");

    return app.exec();
}
