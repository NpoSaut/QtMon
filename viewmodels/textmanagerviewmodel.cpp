#include "textmanagerviewmodel.h"

namespace ViewModels
{

TextManagerViewModel::TextManagerViewModel(QObject *parent) :
    textManager (nullptr), QObject(parent)
{
}

void TextManagerViewModel::assign(Interaction::TextManager *tm)
{
    if (textManager)
        disconnect(textManager, SIGNAL(outputStringChanged()), this, SLOT(update()));

    textManager = tm;
    connect(textManager, SIGNAL(outputStringChanged()), this, SLOT(update()));
    update ();
}

QString TextManagerViewModel::getText() const
{
    if (textManager)
        return textManager->getOuputString();
    else
        return "TextManager not assigned";
}

void TextManagerViewModel::update()
{
    emit TextChanged();
}

}
