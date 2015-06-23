#ifndef POPUPACTIVITY_H
#define POPUPACTIVITY_H

#include <QTimer>
#include "../activity.h"
#include "../textmanager.h"

namespace Interaction {
namespace Activities {

class PopupActivity : public Activity
{
    Q_OBJECT
public:
    explicit PopupActivity(QString message, int durationMs, TextManager *textManager, QObject *parent = 0);
    explicit PopupActivity(QString message, TextManager *textManager, QObject *parent = 0);
    explicit PopupActivity(QString *message, int durationMs, TextManager *textManager, QObject *parent = 0);
    explicit PopupActivity(QString *message, TextManager *textManager, QObject *parent = 0);

    virtual void run ();
    virtual void dispose ();

private slots:
    void submitted ();

private:
    QString messageStorage;
    QString *message;
    TextManager *textManager;
    QTimer timer;
};

}
}

#endif // POPUPACTIVITY_H
