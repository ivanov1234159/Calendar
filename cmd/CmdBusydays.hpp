//
// Created by toi on 29/05/2020.
//

#ifndef CALENDAR_CMDBUSYDAYS_HPP
#define CALENDAR_CMDBUSYDAYS_HPP

#include "../Command.hpp"

class CmdBusydays : public Command {
public:
    CmdBusydays();
    virtual bool action(std::ostream& out, RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDBUSYDAYS_HPP
