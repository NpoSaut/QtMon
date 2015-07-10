#ifndef INPUTACTIVITY_H
#define INPUTACTIVITY_H

#include <QObject>
#include "../activity.h"
#include "../textmanager.h"

namespace Interaction {
namespace Activities {

class InputActivity : public Activity
{
    Q_OBJECT
public:
    explicit InputActivity(QString outputFormat, int *value, TextManager *textManager, QObject *parent = 0);

    virtual void run ();
    virtual void dispose ();

protected slots:
    void submitted ();

private:
    TextManager *textManager;
    QString outputFormat;
    int *value;

};

}
}

#endif // INPUTACTIVITY_H
