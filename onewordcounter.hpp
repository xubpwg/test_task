#pragma once

#include <QFuture>
#include <QObject>

namespace wc
{

class OneWordCounter : public QObject
{
public:
    OneWordCounter(const QString& word, const QString& filePath, QObject* parent = nullptr);

    QFuture<QPair<QString, quint64>> getWordCount();

private:
    QString m_word;
    QString m_filePath;
};

}

