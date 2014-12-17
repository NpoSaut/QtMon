#ifndef COMMAND_H
#define COMMAND_H

#include"story.h"

namespace Interaction {

class Command
{
public:
    Command(int id);
    Story getStory() = 0;
    int getId();

private:
    int id;
};

}

#endif // COMMAND_H
