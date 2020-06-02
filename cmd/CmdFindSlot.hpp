//
// Created by toi on 02/06/2020.
//

#ifndef CALENDAR_CMDFINDSLOT_HPP
#define CALENDAR_CMDFINDSLOT_HPP

#include "../Command.hpp"

class CmdFindSlot : public Command {
public:
    CmdFindSlot();
    virtual bool action(RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDFINDSLOT_HPP
