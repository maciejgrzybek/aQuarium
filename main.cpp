#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "fishmanager.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    FishManager* fishManager = new FishManager(&app);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/FishRandomizer/main.qml"));
    viewer.showExpanded();
    viewer.rootContext()->setContextProperty("fishManager",fishManager);

    return app.exec();
}
