#ifndef PHRASENUMBERLEVITHAN_H
#define PHRASENUMBERLEVITHAN_H

#include <QDir>

#include "Speaker.h"

namespace Sound {

// Говорит фразу по номеру
// Фразы лежат в phrasesDir, воспроизводятся все файлы по шаблону N*.mp3
class PhraseNumberLevithan : public QObject
{
    Q_OBJECT
public:
    PhraseNumberLevithan(QDir phrasesDir, Speaker *speaker);

public slots:
    void sayPhrase (int n);

private:
    QDir dir;
    Speaker *speaker;
};

}

#endif // PHRASENUMBERLEVITHAN_H
