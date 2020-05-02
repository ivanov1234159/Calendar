//
// Created by toi on 02/05/2020.
//

#ifndef CALENDAR_CMDOPEN_HPP
#define CALENDAR_CMDOPEN_HPP

#include "../Command.hpp"

class CmdOpen: public Command {
public:
    CmdOpen();
    virtual bool action(RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDOPEN_HPP
