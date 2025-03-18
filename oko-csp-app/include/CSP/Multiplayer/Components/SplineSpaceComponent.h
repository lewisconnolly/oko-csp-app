/*
 * Copyright 2023 Magnopus LLC

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// @file SplineSpaceComponent.h
/// @brief Definitions and support for spline components.

#pragma once

#include "CSP/Multiplayer/ComponentBase.h"

namespace csp::multiplayer
{

/// @brief Enumerates the list of properties that can be replicated for a spline component.
enum class SplinePropertyKeys
{
    Waypoints = 0,
    Num
};

/**
 * @ingroup SplineSpaceComponent
 * @brief Add a spline curve to your space. This can be used in conjunction with Scripts to align/animate objects along its length.
 */
class CSP_API SplineSpaceComponent : public ComponentBase
{
public:
    /// @brief Constructs the spline space component, and associates it with the specified Parent space entity.
    /// @param Parent The Space entity that owns this component.
    SplineSpaceComponent(SpaceEntity* Parent);

    /// @brief Generate a vector3 at a chosen position along the spline
    /// Note: Generates a cubic spline position from current Waypoints
    /// @param NormalisedDistance float : Distance along the spline being evaluated between a value of 0 and 1
    /// @return position value of X,Y,Z in Vector3 format of the generated spline position
    csp::common::Vector3 GetLocationAlongSpline(float NormalisedDistance);

    /// @brief Get waypoints used to generate spline
    /// Note: Get the number of positions generated by the spline
    /// @return Current waypoint Values Set
    csp::common::List<csp::common::Vector3> GetWaypoints() const;

    /// @brief Set waypoints to generate the spline
    /// Note: Set the number of positions generated by the spline
    /// @param Value csp::common::List<csp::common::Vector3> : number of positions between each waypoint
    void SetWaypoints(const csp::common::List<csp::common::Vector3>& Waypoints);
};

} // namespace csp::multiplayer
