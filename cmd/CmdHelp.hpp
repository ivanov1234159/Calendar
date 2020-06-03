//
// Created by toi on 02/05/2020.
//

#ifndef CALENDAR_CMDHELP_HPP
#define CALENDAR_CMDHELP_HPP

#include "../Command.hpp"

class CmdHelp : public Command {
public:
    CmdHelp();
    virtual bool action(std::ostream& out, RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDHELP_HPP
