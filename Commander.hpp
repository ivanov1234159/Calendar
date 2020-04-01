//
// Created by toi on 01/04/2020.
//

#ifndef CALENDAR_COMMANDER_HPP
#define CALENDAR_COMMANDER_HPP

#include <iostream>
//for: cout, endl, ostream
#include <sstream>
//for: istringstream
#include "Program.hpp"

typedef Program RunnerType;
typedef bool (*FuncCMD)(RunnerType&, std::istringstream&);

class Commander {
    /*
     * !!! IMPORTANT !!!
     * Commands::CMD_COUNT must be last
     *
     * !!! IMPORTANT !!!
     * Order matters (see the comment in Commander.cpp before Commander::cmd_list definition)
     */
    enum Commands {
        OPEN,
        CLOSE,
        SAVE,
        SAVE_AS,
        HELP,
        EXIT,
        CMD_COUNT
    };
    static const unsigned BUFFER_SIZE = 1024;
    static char const* cmd_list[][Commander::CMD_COUNT];
    static FuncCMD cmd_func[Commander::CMD_COUNT];
    Commander() = delete;
    Commander(Commander const& other) = delete;
    Commander& operator=(Commander const& other) = delete;

    static int findIndex(char const* cmd);// returns -1 if not found
    static void outUsage(unsigned index, std::ostream& out);
public:
    static void run(RunnerType& runner);
};

#endif //CALENDAR_COMMANDER_HPP
