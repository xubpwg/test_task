#pragma once

#include <QFuture>

namespace wc
{

class UniqueWordCollector : public QObject
{
    using StringSet = QSet<QString>;

public:
    UniqueWordCollector(QObject* parent = nullptr);

    QFuture<StringSet> getUniqueWords(const QString& filePath);
};

}
