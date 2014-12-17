#ifndef INPUTPARAMETERACTIVITY_H
#define INPUTPARAMETERACTIVITY_H

#include <QObject>
#include "../activity.h"
#include "../textmanager.h"

namespace Commands {
namespace Activities {
class InputParameterActivity : public Activity
{
    Q_OBJECT
public:
    explicit InputParameterActivity(QString outputFormat, int* valueRef, TextManager *textManager, QObject *parent = 0);

    virtual void run ();
    virtual void dispose ();\

signals:
    void completed ();
    void canselled ();

private slots:
    void submitted ();

private:
    TextManager *textManager;
    QString outputFormat;
    int* valueRef;

};

}
}

#endif // INPUTPARAMETERACTIVITY_H
