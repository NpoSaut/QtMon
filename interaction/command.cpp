#include "command.h"


namespace Interaction {

Command::Command(int id)
    : id (id)
{
}

int Command::getId()
{
    return id;
}

}
