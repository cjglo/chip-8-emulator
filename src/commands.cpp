#include "../include/commands.h"

using namespace std;

class DebugTestCommand : Command {
    void execute() {
        cout<<"INVALID COMMAND, TESTING ONLY"<<endl;
    }
};