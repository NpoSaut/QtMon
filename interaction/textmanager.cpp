#include "textmanager.h"

namespace Interaction {

TextManager::TextManager(Keyboard *keyboard, QObject *parent) :
    firstHit(false), QObject(parent)
{
    connect (keyboard, SIGNAL(numberKeyDown(int)), this, SLOT(numericKeyPressed(int)));
    connect (keyboard, SIGNAL(backspaceKeyDown()), this, SLOT(backscapeKeyPressed()));
    connect (keyboard, SIGNAL(enterKeyDown()), this, SLOT(enterKeyPressed()));

    clear ();
}

void TextManager::clear()
{
    value = 0;
    outputFormat = "";
    emit outputStringChanged();
}

void TextManager::numericKeyPressed(int digit)
{
    if (firstHit)
    {
        value = 0;
        firstHit = false;
    }
    value = positiveOrZero(value) * 10 + digit;
    emit outputStringChanged();
}

void TextManager::backscapeKeyPressed()
{
    value = positiveOrZero(value) / 10;
    firstHit = false;
    emit outputStringChanged();
}

void TextManager::enterKeyPressed()
{
    emit submitted(getValue());
}

int TextManager::positiveOrZero(int x)
{
    return x > 0 ? x : 0;
}

void TextManager::init(QString format)
{
    init(format, 0);
}

void TextManager::init(QString format, int initialValue)
{
    outputFormat = format;
    value = initialValue;
    firstHit = true;
    emit outputStringChanged();
}

QString TextManager::getOuputString() const
{
    return outputFormat.arg(value);
}

int TextManager::getValue() const
{
    return value;
}

}
