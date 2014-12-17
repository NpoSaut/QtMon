#include "command.h"


namespace Commands {

Command::Command(int id)
    : id (id)
{
}

int Command::getId()
{
    return id;
}

}
