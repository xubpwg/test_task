#include "controller.hpp"
#include "onewordcounter.hpp"
#include "worddata.hpp"
#include <QFutureWatcher>
#include <QUrl>

namespace wc
{

Controller::Controller(QObject* parent) :
    QObject(parent),
    m_uniqueWordCollector(new UniqueWordCollector(this))
{
    connect(this, &Controller::uniqueWordsSetChanged, this, &Controller::refreshWordCount);
    connect(this, &Controller::wordDataQueueChanged, this, &Controller::processWordDataQueue);
}

void Controller::startProcessing(const QString& fileUrlString)
{
    m_filePath = QUrl(fileUrlString).path();

    QFuture uniqueWordsFuture = m_uniqueWordCollector->getUniqueWords(m_filePath);
    auto* uniqueWordsWatcher = new QFutureWatcher<QSet<QString>>(this);
    connect(uniqueWordsWatcher, &QFutureWatcher<QSet<QString>>::finished, [this, &uniqueWordsFuture] {
        setUniqueWords(uniqueWordsFuture.result());
    });

    uniqueWordsWatcher->setFuture(uniqueWordsFuture);
}

void Controller::setUniqueWords(const QSet<QString>& newUniqueWords)
{
    if (m_uniqueWords != newUniqueWords)
    {
        m_uniqueWords = newUniqueWords;
        emit uniqueWordsSetChanged();
    }
}

void Controller::enqueueWordData(const QPair<QString, quint64>& data)
{
    WordData wordCountInfo { data.first, data.second };
    m_wordDataQueue.enqueue(wordCountInfo);
    emit wordDataQueueChanged();
}

void Controller::updateTopWordsData(const WordData& wordData)
{
    QList<WordData> tempTopWordsDataList;
    Q_ASSERT(m_topWords.size() == m_topWordsCount.size());

    for (int i = 0; i < m_topWords.size(); ++i)
        tempTopWordsDataList.append({ m_topWords.at(i), m_topWordsCount.at(i).toULongLong()});
    tempTopWordsDataList.append({ wordData.word, wordData.count });
    std::sort(tempTopWordsDataList.begin(), tempTopWordsDataList.end(), [](const WordData& a, const WordData& b){
        return (a.count > b.count);
    });

    if (!tempTopWordsDataList.isEmpty())
        setTopCount(tempTopWordsDataList.at(0).count);

    const bool isMaxSizeList = (tempTopWordsDataList.size() >= 15);
    QList<WordData> nameSortTempList(tempTopWordsDataList.begin(),
                                     isMaxSizeList ? tempTopWordsDataList.begin() + 15 : tempTopWordsDataList.end());
    std::sort(nameSortTempList.begin(), nameSortTempList.end(), [](const WordData& a, const WordData& b){
        return (a.word < b.word);
    });

    m_topWords.clear();
    m_topWordsCount.clear();

    for (const auto& wordData : nameSortTempList)
    {
        m_topWords.append(wordData.word);
        m_topWordsCount.append(wordData.count);
    }

    emit topWordsChanged();
    emit topWordsCountChanged();
}

QVariantList Controller::topWordsCount() const
{
    return (m_topWordsCount.size() > 15) ? QVariantList(m_topWordsCount.mid(0, 15)) : m_topWordsCount;
}

void Controller::setTopWordsCount(const QVariantList& val)
{
    if (m_topWordsCount == val)
        return;
    m_topWordsCount = val;
    emit topWordsCountChanged();
}

double Controller::topCount() const
{
    return m_topCount;
}

void Controller::setTopCount(double val)
{
    if (m_topCount == val)
        return;
    m_topCount = val;
    emit topCountChanged();
}

QStringList Controller::topWords() const
{
    return (m_topWords.size() > 15) ? QStringList(m_topWords.mid(0, 15)) : m_topWords;
}

void Controller::setTopWords(const QStringList& val)
{
    if (m_topWords == val)
        return;
    m_topWords = val;
    emit topWordsChanged();
}

void Controller::refreshWordCount()
{
    for (const auto& word : m_uniqueWords)
    {
        OneWordCounter* wordCounter = new OneWordCounter(word, m_filePath, this);
        QFuture oneWordCounterFuture = wordCounter->getWordCount();
        auto* oneWordCounterWatcher = new QFutureWatcher<QPair<QString, quint64>>(this);
        oneWordCounterWatcher->setFuture(oneWordCounterFuture);
        m_oneWordCountHash.insert(word, std::move(oneWordCounterFuture));

        connect(oneWordCounterWatcher, &QFutureWatcher<QPair<QString, quint64>>::finished, [this, &word] {
            QMutexLocker mutexLocker(&m_wordCountMutex);
            enqueueWordData(m_oneWordCountHash.find(word)->result());
        });
    }
}

void Controller::processWordDataQueue()
{
    while (!m_wordDataQueue.isEmpty())
    {
        const auto wordData = m_wordDataQueue.dequeue();
        updateTopWordsData(wordData);
    }
}

void Controller::resetProcessing()
{
    m_wordDataQueue.clear();
    m_uniqueWords.clear();
    m_filePath.clear();
    m_oneWordCountHash.clear();

    setTopWords({});
    setTopWordsCount({});
    setTopCount(0.0);
}

}


