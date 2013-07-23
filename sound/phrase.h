#ifndef PHRASE_H
#define PHRASE_H
#include <QString>

namespace sound
{
    class Phrase
    {
    public:
        Phrase()
            :fileName(""), priority(10)
        {}
        Phrase(QString filename)
            : fileName(filename), priority(10)
        {}
        Phrase(QString filename, int priority)
            : fileName(filename), priority(priority)
        {}

        QString fileName;
        int priority;
    };
}

#endif // PHRASE_H
