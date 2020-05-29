//
// Created by toi on 29/05/2020.
//

#ifndef CALENDAR_CMDFIND_HPP
#define CALENDAR_CMDFIND_HPP

#include "../Command.hpp"

class CmdFind : public Command {
public:
    CmdFind();
    virtual bool action(RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDFIND_HPP
