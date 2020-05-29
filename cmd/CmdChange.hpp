//
// Created by toi on 29/05/2020.
//

#ifndef CALENDAR_CMDCHANGE_HPP
#define CALENDAR_CMDCHANGE_HPP

#include "../Command.hpp"

class CmdChange : public Command {
public:
    CmdChange();
    virtual bool action(RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDCHANGE_HPP
