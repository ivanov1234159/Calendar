//
// Created by toi on 02/05/2020.
//

#ifndef CALENDAR_CMDEXIT_HPP
#define CALENDAR_CMDEXIT_HPP

#include "../Command.hpp"

class CmdExit : public Command {
public:
    CmdExit();
    virtual bool action(std::ostream& out, RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDEXIT_HPP
