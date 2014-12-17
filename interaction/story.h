#ifndef STORY_H
#define STORY_H

#include <QObject>
#include <QList>

#include "context.h"
#include "activity.h"

namespace Interaction {

    class Story : public QObject
    {
        Q_OBJECT
    public:
        Story(Context *storyContext, QList<Activities::Activity> activities, QObject *parent = 0);
        void Begin();
        void Dispose();

    public slots:
        void Abort();

    private slots:
        void SwitchNext();

    private:
        Context *context;
        int currentActivityIndex;
        QList<Activities::Activity> activities;
        void DisposeCurrent();
        void StartNext();

    };

}


#endif // STORY_H
