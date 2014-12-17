#ifndef INPUTCOMMANDACTIVITY_H
#define INPUTCOMMANDACTIVITY_H

#include "../activity.h"
#include "../textmanager.h"

namespace Commands {
namespace Activities {

class InputCommandActivity : public Activity
{
    Q_OBJECT
public:
    explicit InputCommandActivity(TextManager *textManager, QObject *parent = 0);

    virtual void run ();
    virtual void dispose ();

signals:
    void completed ();
    void canselled ();

private slots:
    void submitted ();

private:
    TextManager *textManager;
};

}
}

#endif // INPUTCOMMANDACTIVITY_H
