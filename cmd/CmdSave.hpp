//
// Created by toi on 02/05/2020.
//

#ifndef CALENDAR_CMDSAVE_HPP
#define CALENDAR_CMDSAVE_HPP

#include "../Command.hpp"

class CmdSave : public Command {
public:
    CmdSave();
    virtual bool action(std::ostream& out, RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDSAVE_HPP
