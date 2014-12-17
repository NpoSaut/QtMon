#include "textmanager.h"

namespace Commands {

TextManager::TextManager(QObject *parent) :
    QObject(parent)
{
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
    value = value * 10 + digit;
    emit outputStringChanged();
}

void TextManager::backscapeKeyPressed()
{
    value /= 10;
    emit outputStringChanged();
}

void TextManager::enterKeyPressed()
{
    emit submitted(getValue);
}

void TextManager::setOutputFormat(QString s)
{
    outputFormat = s;
    emit outputStringChanged();
}

QString TextManager::getOuputString() const
{
    return outputFormat.arg(value);
}

void TextManager::setValue(int v)
{
    value = v;
    emit outputStringChanged();
}

int TextManager::getValue() const
{
    return value;
}

}
