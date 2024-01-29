#include <QApplication>
#include <QQmlApplicationEngine>
#include "controller.hpp"

const QUrl QML_MAIN_URL = QStringLiteral("qrc:/main.qml");
const QString CPP_CONSTRUCTION_ONLY = QStringLiteral("cpp construction only");
const QString WORD_COUNTER_MODULE = QStringLiteral("my.wc");

int main(int argc, char *argv[])
{
    // @uri my.wc
    qmlRegisterModule(WORD_COUNTER_MODULE.toLatin1(), 1, 0);
    qmlRegisterUncreatableType<wc::Controller>(WORD_COUNTER_MODULE.toLatin1(), 1, 0,
                                            "WCController", CPP_CONSTRUCTION_ONLY);

    QApplication app(argc, argv);

    wc::Controller controller(&app);

    QQmlApplicationEngine engine;
    engine.setInitialProperties({
        {"controller", QVariant::fromValue(&controller)}
    });
    engine.load(QML_MAIN_URL);

    return app.exec();
}
