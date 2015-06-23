#include "popupactivity.h"

namespace Interaction {
namespace Activities {

PopupActivity::PopupActivity(QString message, int durationMs, TextManager *textManager, QObject *parent)
    : messageStorage (message), message (&messageStorage), textManager (textManager), timer(), Activity(parent)
{
    timer.setInterval(durationMs);
    timer.setSingleShot(true);
}

PopupActivity::PopupActivity(QString message, TextManager *textManager, QObject *parent)
    : PopupActivity (message, 5000, textManager, parent)
{ }

PopupActivity::PopupActivity(QString *message, int durationMs, TextManager *textManager, QObject *parent)
    : message (message), textManager (textManager), timer(), Activity(parent)
{
    timer.setInterval(durationMs);
    timer.setSingleShot(true);
}

PopupActivity::PopupActivity(QString *message, TextManager *textManager, QObject *parent)
    : PopupActivity (message, 5000, textManager, parent)
{ }

void PopupActivity::run()
{
    textManager->init(*message);
    connect(textManager, SIGNAL(submitted(int)), this, SLOT(submitted()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(submitted()));
    timer.start();
}

void PopupActivity::dispose()
{
    textManager->clear();
    disconnect(textManager, SIGNAL(submitted(int)), this, SLOT(submitted()));
    timer.stop();
    disconnect(&timer, SIGNAL(timeout()), this, SLOT(submitted()));
}

void PopupActivity::submitted()
{
    emit completed();
}

}
}
