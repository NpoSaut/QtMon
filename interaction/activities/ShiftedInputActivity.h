#ifndef SHIFTEDINPUTACTIVITY_H
#define SHIFTEDINPUTACTIVITY_H

#include "inputactivity.h"

namespace Interaction {
namespace Activities {

class ShiftedInputActivity : public InputActivity
{
    Q_OBJECT
public:
    explicit ShiftedInputActivity(QString outputFormat, int *value, int shift, TextManager *textManager, QObject *parent = 0);

    virtual void run ();

protected slots:
    void submitted ();

private:
    int shiftedValue;
    int *value;
    int shift;
};

}
}

#endif // SHIFTEDINPUTACTIVITY_H
