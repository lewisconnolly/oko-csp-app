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

#pragma once

#include "CSP/CSPCommon.h"
#include "CSP/Common/String.h"

namespace csp::multiplayer
{

/// @brief Controls the asset and asset collection IDs used for storing external data.
CSP_INTERFACE class CSP_API IExternalResourceComponent
{
public:
    /// @brief Gets the ID for the asset used to store external data for this component.
    /// @return csp::common::String : The asset ID.
    virtual const csp::common::String& GetExternalResourceAssetId() const = 0;

    /// @brief Sets the ID for the asset used to store external data for this component.
    /// @param InValue csp::common::String : The new value.
    virtual void SetExternalResourceAssetId(const csp::common::String& InValue) = 0;

    /// @brief Gets the ID of the asset collection for the asset used to store external data for this component.
    /// @return csp::common::String : The asset ID.
    virtual const csp::common::String& GetExternalResourceAssetCollectionId() const = 0;

    /// @brief Sets the ID of the asset collection for the asset used to store external data for this component.
    /// @param InValue csp::common::String : The new value.
    virtual void SetExternalResourceAssetCollectionId(const csp::common::String& InValue) = 0;

protected:
    virtual ~IExternalResourceComponent() = default;
};

} // namespace csp::multiplayer
