#pragma once

#include <QMap>
#include <QObject>

class WordCounter : public QObject
{
    Q_OBJECT
public:
    explicit WordCounter(QObject* parent = nullptr);

    Q_PROPERTY(bool inProgress READ isInProgress WRITE setInProgress NOTIFY inProgressChanged)
    bool isInProgress() const { return m_inProgress; }
    void setInProgress(bool val);

    Q_INVOKABLE void startProcessing(QString fileName);
    Q_INVOKABLE void stopProcessing();

signals:
    void inProgressChanged();

private:
    void resetWordCounterState();

    bool m_inProgress = false;
    QMap<QString, quint64> m_wordsCountMap;
};
