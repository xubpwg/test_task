#include "onewordcounter.hpp"
#include <QFile>
#include <QtConcurrent>

namespace wc
{

OneWordCounter::OneWordCounter(const QString& word, const QString& filePath, QObject* parent) :
    QObject { parent },
    m_word(word),
    m_filePath(filePath)
{}

QFuture<QPair<QString, quint64> > OneWordCounter::getWordCount()
{
    auto wordCounterWorker = [=](const QString& path) {
        QFile file(path);
        Q_ASSERT(file.exists());
        Q_ASSERT(file.open(QFile::Text | QFile::ReadOnly));
        QTextStream fileTextStream(&file);

        QPair<QString, quint64> result {"", 0};
        while (!fileTextStream.atEnd())
        {
            QString word;
            fileTextStream >> word;
            if (word == m_word)
                ++result.second;
        }
        result.first = std::move(m_word);
        return result;
    };

    return QtConcurrent::run(wordCounterWorker, m_filePath);
}

}
