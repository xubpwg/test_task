#include "wordcounter.hpp"

#include <QFile>
#include <QTextStream>
#include <QThreadPool>
#include <QDebug>
#include <QRegularExpression>

namespace
{

const QRegularExpression WORD_CLEAN_REGEXP("(?<=\\w)[[:punct:]](?!\\w)",
                                           QRegularExpression::CaseInsensitiveOption
                                               | QRegularExpression::UseUnicodePropertiesOption);

}

WordCounter::WordCounter(QObject* parent)
    : QObject{parent}
{}

void WordCounter::setInProgress(bool val)
{
    if (val != m_inProgress)
    {
        m_inProgress = val;
        emit inProgressChanged();
    }
}

void WordCounter::startProcessing(QString fileName)
{
    // 1. open file read-only
    QFile file(fileName);
    if (!file.exists())
        qt_assert("File not exists", __FILE__, __LINE__);

    if (!file.open(QFile::Text | QFile::ReadOnly))
        qt_assert("Can't open file", __FILE__, __LINE__);

    QTextStream textStream(&file);
    // then cycle until EOF:
    while (!textStream.atEnd())
    {
        // 2. read one word
        QString word;
        textStream >> word;
        word = word.remove(WORD_CLEAN_REGEXP);
        // 3. search in words hash
        auto uniqueWordIter = m_wordsCountMap.find(word);
        // 4. if not found (it's a new unique word), start a OneWordCountRunnable(fileName, word)
        if (uniqueWordIter == m_wordsCountMap.constEnd())
            m_wordsCountMap.insert(word, 1);
        else
        {
            ++uniqueWordIter.value();
            // 5. if found (it's not unique word and already counting), continue
            continue;
        }
    }
    qDebug() << "wordsCountMap:" << m_wordsCountMap;
    qDebug() << "wordsCountMap.count:" << m_wordsCountMap.count();
}

void WordCounter::stopProcessing()
{

}

void WordCounter::resetWordCounterState()
{
    m_wordsCountMap.clear();
}
