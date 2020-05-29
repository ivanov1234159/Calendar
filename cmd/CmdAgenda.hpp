//
// Created by toi on 29/05/2020.
//

#ifndef CALENDAR_CMDAGENDA_HPP
#define CALENDAR_CMDAGENDA_HPP

#include "../Command.hpp"

class CmdAgenda : public Command {
public:
    CmdAgenda();
    virtual bool action(RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDAGENDA_HPP
