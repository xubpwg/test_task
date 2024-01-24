#include <QApplication>
#include <QQmlApplicationEngine>
#include "wordcounter.hpp"

const QUrl QML_MAIN_URL = QStringLiteral("qrc:/main.qml");
const QString CPP_CONSTRUCTION_ONLY = QStringLiteral("cpp construction only");
const QString WORD_COUNTER_MODULE = QStringLiteral("my.WordCounter");

int main(int argc, char *argv[])
{
    // @uri my.WordCounter
    qmlRegisterModule(WORD_COUNTER_MODULE.toLatin1(), 1, 0);
    qmlRegisterUncreatableType<WordCounter>(WORD_COUNTER_MODULE.toLatin1(), 1, 0,
                                            "WordCounter", CPP_CONSTRUCTION_ONLY);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [](QObject *obj, const QUrl &objUrl) {
        if (!obj && objUrl == QML_MAIN_URL) QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    WordCounter wordCounter(&app);
    engine.setInitialProperties({
        {"wordCounter", QVariant::fromValue(&wordCounter)}
    });
    engine.load(QML_MAIN_URL);

    return app.exec();
}
