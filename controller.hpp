#pragma once

#include "uniquewordcollector.hpp"
#include "worddata.hpp"
#include <QObject>
#include <QQueue>

namespace wc
{

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject* parent = nullptr);

    Q_INVOKABLE void startProcessing(const QString& fileUrlString);
    Q_INVOKABLE void resetProcessing();

    Q_PROPERTY(QStringList topWords READ topWords WRITE setTopWords NOTIFY topWordsChanged FINAL);
    QStringList topWords() const;
    void setTopWords(const QStringList& val);

    Q_PROPERTY(QVariantList topWordsCount READ topWordsCount WRITE setTopWordsCount NOTIFY topWordsCountChanged FINAL);
    QVariantList topWordsCount() const;
    void setTopWordsCount(const QVariantList& val);

    Q_PROPERTY(double topCount READ topCount WRITE setTopCount NOTIFY topCountChanged);
    double topCount() const;
    void setTopCount(double val);

signals:
    void uniqueWordsSetChanged();
    void wordDataQueueChanged();
    void topWordsChanged();
    void topCountChanged();
    void topWordsCountChanged();

public slots:
    void refreshWordCount();
    void processWordDataQueue();

private:
    void setUniqueWords(const QSet<QString>& newUniqueWords);
    void enqueueWordData(const QPair<QString, quint64>& data);
    void updateTopWordsData(const WordData& wordData);

    QQueue<WordData> m_wordDataQueue;
    UniqueWordCollector* m_uniqueWordCollector = nullptr;
    QSet<QString> m_uniqueWords;
    QString m_filePath;
    QMutex m_wordCountMutex = QMutex();
    QHash<QString, QFuture<QPair<QString, quint64>>> m_oneWordCountHash;

    QStringList m_topWords;
    QVariantList m_topWordsCount;
    double m_topCount = 0.0;
};

}


