#include "phrase.h"

using namespace Sound;


Phrase::Phrase(QFileInfo file, float priority)
    : file(file)
{
    setPriority(priority);
}

Phrase::Phrase(QString filename, float priority)
    : Phrase (QFileInfo(filename), priority)
{ }

void Phrase::setPriority(float x)
{
    if (x < 0) x = 0;
    if (x > 1) x = 1;
    priority = x;
}
