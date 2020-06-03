//
// Created by toi on 02/06/2020.
//

#ifndef CALENDAR_CMDFINDSLOTWITH_HPP
#define CALENDAR_CMDFINDSLOTWITH_HPP

#include "../Command.hpp"

class CmdFindSlotWith : public Command {
public:
    CmdFindSlotWith();
    virtual bool action(std::ostream& out, RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDFINDSLOTWITH_HPP
