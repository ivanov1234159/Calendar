//
// Created by toi on 02/05/2020.
//

#ifndef CALENDAR_CMDCLOSE_HPP
#define CALENDAR_CMDCLOSE_HPP

#include "../Command.hpp"

class CmdClose : public Command {
public:
    CmdClose();
    virtual bool action(RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDCLOSE_HPP
