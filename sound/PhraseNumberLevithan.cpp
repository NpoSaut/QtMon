#include "PhraseNumberLevithan.h"

using namespace Sound;


PhraseNumberLevithan::PhraseNumberLevithan(QDir phrasesDir, Speaker *speaker)
    : dir (phrasesDir),
      speaker (speaker)
{ }

void PhraseNumberLevithan::sayPhrase(int n)
{
    QString fileMask = QString("%1*.mp3").arg(n, 2, 10, QChar('0'));
    auto files = dir.entryInfoList(QStringList(fileMask), QDir::NoFilter, QDir::Name);
    foreach (auto fileInfo, files)
        speaker->enqueuePhrase(Phrase(fileInfo));
}
