//
// Created by toi on 02/05/2020.
//

#include "CmdSaveAs.hpp"
#include "../Commander.hpp"

CmdSaveAs::CmdSaveAs(): Command("saveas", "<file>", "save the current state of the program in <file>") {}

bool CmdSaveAs::action(std::ostream& out, RunnerType &runner, std::istringstream &iss) const {
    String path;
    iss >> path;
    if(!iss){
        out << "Couldn't read the path." << std::endl;
        return false;
    }
    Calendar* calendar = runner.cloneCalendar();
    std::ostringstream oss;
    if(runner.opened()){
        Commander::call("close", runner, iss, oss);
    }
    std::istringstream iss2(path.get());
    Commander::call("open", runner, iss2, oss);
    runner.restoreCalendar(calendar);
    Commander::call("save", runner, iss2, out);
    return true;
}