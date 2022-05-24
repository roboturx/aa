#include <cppbackend.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<CppBackend>(
        "backend", 1, 0, "BackendObject",
        [](QQmlEngine *, QJSEngine *) { return new CppBackend; });

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath("qrc:/imports/"); // Adding imports paths
    engine.addImportPath("qrc:/cppImports/");

    engine.load(url);

    return app.exec();
}
