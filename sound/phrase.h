#ifndef PHRASE_H
#define PHRASE_H

#include <QFileInfo>

namespace Sound
{
    class Phrase
    {
    public:
        Phrase()
            :file(QString()), priority(10)
        {}
        Phrase(QFileInfo file, int priority = 10)
            : file(file), priority(priority)
        {}
        Phrase(QString filename, int priority = 10)
            : file(filename), priority(priority)
        {}

        QFileInfo file;
        int priority;
    };
}

#endif // PHRASE_H
