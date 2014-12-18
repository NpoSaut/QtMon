#ifndef STORY_H
#define STORY_H

#include <QObject>
#include <QVector>

#include "activity.h"
#include "context.h"

namespace Interaction {

    // Занимается запуском активностей из списка по цепочке
    class Story : public QObject
    {
        Q_OBJECT
    public:
        Story(Context *context, QVector<Activities::Activity *> activities, QObject *parent = 0);
        void begin();
        void dispose();
        ~Story();

    public slots:
        void abort();

    private slots:
        void switchNext();

    private:
        void disposeCurrent();
        void startNext();

        Context *context;
        QVector<Activities::Activity *> activities;
        int currentActivityIndex;
    };

}


#endif // STORY_H
