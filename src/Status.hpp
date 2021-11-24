/*!
    @file Status.hpp
    ISUL
    @author Yuriy Scherbanovskiy
    @date 5/31/21
    @brief Represent Status for all ISUL operations
 */

#pragma once

/// @cond STL includes
#include <memory>
#include <string>
/// @endcond

namespace ISUL {

    #include "ValidationResult.h"

    /*!
        @brief Represent result of operation, with result code and description
     */
    struct Status {
        using ptr = std::shared_ptr<Status>;
        
        /*!
            @brief Get the status result
            @return ValidationResult
         */
        virtual ValidationResult GetResult() const = 0;

        /*!
            @brief Get the status description
            @return std::string
         */
        virtual std::string GetDescription() const = 0;
        
    };

}
