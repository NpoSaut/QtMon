#ifndef PHRASE_H
#define PHRASE_H

#include <QFileInfo>

namespace Sound
{
    class Phrase
    {
    public:
        Phrase(QFileInfo file, float priority = 0.1);
        Phrase(QString filename = QString(), float priority = 0.1);

        const QFileInfo &getFile () const {return file;}
        const float getPriority () const {return priority;} // 0 ... 1.0

    private:
        void setPriority (float x);
        QFileInfo file;
        float priority; // 0 ... 1.0
    };
}

#endif // PHRASE_H
