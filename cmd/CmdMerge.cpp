//
// Created by toi on 03/06/2020.
//

#include "CmdMerge.hpp"

CmdMerge::CmdMerge(): Command("merge", "<calendar_path>",
    "add appointments from <calendar_path> in the current calendar")
{}

bool CmdMerge::action(std::ostream& out, RunnerType& runner, std::istringstream& iss) const {
    String path;
    iss >> path;
    if(!iss){
        out << "Couldn't read the path." << std::endl;
        return false;
    }
    if(!runner.opened()) {
        out << "There isn't an opened calendar." << std::endl;
        return true;
    }

    Calendar* calendar = nullptr;
    runner.open(path, calendar);
    if(runner.mergeWith(calendar, out, std::cin)){
        out << "All appointments were transferred successfully.";
    }else{
        out << "The file '" << path << "' is empty.";
    }
    out << std::endl;
    delete calendar;
    return true;
}