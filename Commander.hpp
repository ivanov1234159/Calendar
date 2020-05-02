//
// Created by toi on 01/04/2020.
//

#ifndef CALENDAR_COMMANDER_HPP
#define CALENDAR_COMMANDER_HPP

#include <iostream>
//for: cout, endl, ostream
#include "Command.hpp"
#include "Array.hpp"

class Commander {
private:
    static Array<Command*> cmd_list;
    Commander() = delete;
    Commander(Commander const& other) = delete;
    Commander& operator=(Commander const& other) = delete;

    static Command* find(char const* cmd);// returns nullptr if not found
public:
    static const unsigned BUFFER_SIZE = 256;
    friend class CmdHelp;
    static void add(Command* item);
    static void run(RunnerType& runner);
};

/*
 * !!! IMPORTANT !!!
 * the exit command MUST be first, else change the static const in Commander class named EXIT
 *
 * the help command has a special function named cmd_help from type FuncCMD
 */
void build_commands();

#endif //CALENDAR_COMMANDER_HPP
