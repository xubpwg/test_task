#include "uniquewordcollector.hpp"
#include <QFile>
#include <QtConcurrent>

namespace wc
{

UniqueWordCollector::UniqueWordCollector(QObject* parent) :
    QObject(parent)
{}

QFuture<UniqueWordCollector::StringSet> UniqueWordCollector::getUniqueWords(const QString& filePath)
{
    auto uniqueWordsWorker = [=](const QString& path) {
        QFile file(path);
        Q_ASSERT(file.exists());
        Q_ASSERT(file.open(QFile::Text | QFile::ReadOnly));
        QTextStream fileTextStream(&file);

        StringSet result;
        while (!fileTextStream.atEnd())
        {
            QString word;
            fileTextStream >> word;
            result.insert(word);
        }
        return result;
    };

    return QtConcurrent::run(uniqueWordsWorker, filePath);
}

}

