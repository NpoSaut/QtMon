#ifndef COMMAND_H
#define COMMAND_H

#include"story.h"

namespace Interaction {

class Command
{
public:
    Command(int id) : id (id) { }
    int getId() const { return id; }

    virtual Story *createStory() = 0;

private:
    int id;
};

}

#endif // COMMAND_H
