#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <iostream>

class Command {
    public:
        virtual void execute() = 0;
};



class DebugTestCommand : public Command {
    void execute();
};

#endif