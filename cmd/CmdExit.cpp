//
// Created by toi on 02/05/2020.
//

#include "CmdExit.hpp"

CmdExit::CmdExit(): Command("exit", "", "exit from the program", true) {}

bool CmdExit::action(RunnerType &runner, std::istringstream &iss) const {
    std::cout << "Exiting the program..." << std::endl;
    return true;
}