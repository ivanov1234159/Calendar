//
// Created by toi on 02/05/2020.
//

#include "CmdExit.hpp"

CmdExit::CmdExit(): Command("exit", "", "exit from the program", true) {}

bool CmdExit::action(std::ostream& out, RunnerType&, std::istringstream&) const {
    out << "Exiting the program..." << std::endl;
    return true;
}