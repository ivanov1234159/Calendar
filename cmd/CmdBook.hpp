//
// Created by toi on 02/05/2020.
//

#ifndef CALENDAR_CMDBOOK_HPP
#define CALENDAR_CMDBOOK_HPP

#include "../Command.hpp"

class CmdBook : public Command {
public:
    CmdBook();
    virtual bool action(RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDBOOK_HPP
