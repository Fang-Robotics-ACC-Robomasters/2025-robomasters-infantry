/*****************************************************************************/
/********** !!! WARNING: CODE GENERATED BY TAPROOT. DO NOT EDIT !!! **********/
/*****************************************************************************/

/*
 * Copyright (c) 2020-2021 fang-robotics
 *
 * This file is part of Taproot.
 *
 * Taproot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Taproot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Taproot.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef TAPROOT_MOVE_UNJAM_COMPRISED_COMMAND_HPP_
#define TAPROOT_MOVE_UNJAM_COMPRISED_COMMAND_HPP_

#include "tap/control/comprised_command.hpp"

#include "move_command.hpp"
#include "unjam_command.hpp"

namespace tap
{
namespace control
{
namespace setpoint
{
// Forward declarations
class SetpointSubsystem;

/**
 * A comprised command that combines the unjam and move commands.
 *
 * Assuming no jams occur, this command behaves like a MoveCommand. It will
 * schedule once and end once the target displacement is reached. If it gets
 * jammed while trying to move then the command will then schedule a UnjamCommand.
 * At this point the command will end when the UnjamCommand ends.
 *
 * See `UnjamCommand` and `MoveCommand` for more details on their respective logic.
 */
class MoveUnjamComprisedCommand : public tap::control::ComprisedCommand
{
public:
    /**
     * @param[in] drivers A pointer to the `Drivers` struct.
     * @param[in] setpointSubsystem The subsystem to interact with.
     * @param[in] moveDisplacement The displacement the command will apply to the subsystem
     * @param[in] moveTime See `MoveCommand` for more details, passed on directly
     *      to its constructor.
     * @param[in] pauseAfterMoveTime See `MoveCommand` for more details, passed on directly
     *      to its constructor.
     * @param[in] setToTargetOnEnd See `MoveCommand` for more details, passed on directly
     *      to its constructor.
     * @param[in] setpointTolerance See `MoveCommand` for more details, passed on directly
     *      to its constructor.
     * @param[in] unjamDisplacement See `UnjamCommand`'s constructor for more details,
     *      passed on directly to this command's constructor.
     * @param[in] unjamThreshold See `UnjamCommand`'s constructor for more details,
     *      passed on directly to this command's constructor.
     * @param[in] unjamCycleCount See `UnjamCommand`'s constructor for more details,
     *      passed on directly to this command's constructor.
     * @param[in] maxUnjamWaitTime See `UnjamCommand`'s constructor for more details,
     *      passed on directly to this command's constructor.
     */
    MoveUnjamComprisedCommand(
        tap::Drivers* drivers,
        SetpointSubsystem* setpointSubsystem,
        float moveDisplacement,
        uint32_t moveTime,
        uint32_t pauseAfterMoveTime,
        bool setToTargetOnEnd,
        float setpointTolerance,
        float unjamDisplacement,
        float unjamThreshold,
        uint32_t maxUnjamWaitTime,
        uint_fast16_t unjamCycleCount);

    void initialize() override;

    void execute() override;

    void end(bool interrupted) override;

    bool isFinished() const override;

    const char* getName() const override { return "agitator shoot"; }

protected:
    SetpointSubsystem* setpointSubsystem;

    MoveCommand agitatorRotateCommand;

    UnjamCommand agitatorUnjamCommand;

    bool unjamSequenceCommencing;

    bool agitatorDisconnectFault;
};  // class MoveUnjamComprisedCommand

}  // namespace setpoint

}  // namespace control

}  // namespace tap

#endif  // TAPROOT_MOVE_UNJAM_COMPRISED_COMMAND_HPP_
