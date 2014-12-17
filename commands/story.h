#ifndef STORY_H
#define STORY_H

#include <QList>

#include "activity.h"

namespace Commands {

    class Story : public QList<Activities::Activity>
    {
    public:
        Story();
    };

}


#endif // STORY_H
