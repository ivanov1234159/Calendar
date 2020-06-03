//
// Created by toi on 03/06/2020.
//

#ifndef CALENDAR_CMDMERGE_HPP
#define CALENDAR_CMDMERGE_HPP

#include "../Command.hpp"

class CmdMerge : public Command {
public:
    CmdMerge();
    virtual bool action(std::ostream& out, RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDMERGE_HPP
