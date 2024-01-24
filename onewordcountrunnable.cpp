#include "onewordcountrunnable.hpp"

#include <QString>

OneWordCountRunnable::OneWordCountRunnable(QString word)
{
    Q_UNUSED(word);
    setAutoDelete(true);
}
