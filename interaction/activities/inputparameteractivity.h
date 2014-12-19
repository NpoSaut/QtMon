#ifndef INPUTPARAMETERACTIVITY_H
#define INPUTPARAMETERACTIVITY_H

#include <QObject>
#include "../activity.h"
#include "../textmanager.h"

namespace Interaction {
namespace Activities {

class InputParameterActivity : public Activity
{
    Q_OBJECT
public:
    explicit InputParameterActivity(QString outputFormat, int *value, TextManager *textManager, QObject *parent = 0);

    virtual void run ();
    virtual void dispose ();

private slots:
    void submitted ();

private:
    TextManager *textManager;
    QString outputFormat;
    int *value;

};

}
}

#endif // INPUTPARAMETERACTIVITY_H
