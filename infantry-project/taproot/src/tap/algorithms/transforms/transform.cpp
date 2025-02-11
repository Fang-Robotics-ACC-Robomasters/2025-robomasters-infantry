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

#include "transform.hpp"

namespace tap::algorithms::transforms
{
Transform::Transform(const Position& translation, const Orientation& rotation)
    : translation(translation.coordinates()),
      rotation(rotation.matrix()),
      tRotation(rotation.matrix().transpose())
{
}

Transform::Transform(Position&& translation, Orientation&& rotation)
    : translation(std::move(translation.coordinates())),
      rotation(std::move(rotation.matrix())),
      tRotation(rotation.matrix().transpose())
{
}

Transform::Transform(const CMSISMat<3, 1>& translation, const CMSISMat<3, 3>& rotation)
    : translation(translation),
      rotation(rotation),
      tRotation(rotation.transpose())
{
}

Transform::Transform(CMSISMat<3, 1>&& translation, CMSISMat<3, 3>&& rotation)
    : translation(std::move(translation)),
      rotation(std::move(rotation)),
      tRotation(rotation.transpose())
{
}

Transform::Transform(float x, float y, float z, float roll, float pitch, float yaw)
    : translation({x, y, z}),
      rotation(fromEulerAngles(roll, pitch, yaw)),
      tRotation(rotation.transpose())
{
}

Position Transform::apply(const Position& position) const
{
    return Position(tRotation * (position.coordinates() - translation));
}

Vector Transform::apply(const Vector& vector) const
{
    return Vector(tRotation * vector.coordinates());
}

Orientation Transform::apply(const Orientation& orientation) const
{
    return Orientation(tRotation * orientation.matrix());
}

Transform Transform::getInverse() const
{
    // negative transposed rotation matrix times original position = new position
    CMSISMat<3, 1> invTranslation = tRotation * translation;
    invTranslation = -invTranslation;
    return Transform(invTranslation, tRotation);
}

Transform Transform::compose(const Transform& second) const
{
    CMSISMat<3, 3> newRot = this->rotation * second.rotation;
    CMSISMat<3, 1> newPos = this->translation + this->rotation * second.translation;
    return Transform(newPos, newRot);
}

float Transform::getRoll() const
{
    float jz = rotation.data[2 * 3 + 1];
    float kz = rotation.data[2 * 3 + 2];
    return atan2(jz, kz);
}

float Transform::getPitch() const
{
    float iz = rotation.data[2 * 3 + 0];
    return asinf(-iz);
}

float Transform::getYaw() const
{
    float iy = rotation.data[1 * 3 + 0];
    float ix = rotation.data[0 * 3 + 0];
    return atan2(iy, ix);
}

}  // namespace tap::algorithms::transforms
