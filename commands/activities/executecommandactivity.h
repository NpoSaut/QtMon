#ifndef EXECUTECOMMANDACTIVITY_H
#define EXECUTECOMMANDACTIVITY_H

#include "../activity.h"
#include "../contexts/executecommandcontext.h"

namespace Commands {
namespace Activities {

class ExecuteCommandActivity : public Activity
{
    Q_OBJECT
public:
    explicit ExecuteCommandActivity(Contexts::ExecuteCommandContext *context, QObject *parent = 0);

    virtual void run ();
    virtual void dispose ();\

signals:
    void completed ();
    void canselled ();

private:
    Contexts::ExecuteCommandContext *context;

};

}
}

#endif // EXECUTECOMMANDACTIVITY_H
