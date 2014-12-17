#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QObject>

namespace Interaction {
namespace Activities {

    class Activity : public QObject
    {
        Q_OBJECT
    public:
        virtual void run () = 0;
        virtual void dispose () = 0;

    signals:
        void completed ();
        void canselled ();
    };

}
}

#endif // ACTIVITY_H
