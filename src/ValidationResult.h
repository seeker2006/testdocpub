/**
 * @file ValidationResult.h
 * ISUL
 *
 * @author Oleksii Stepanenko
 * @date 13.07.2021.
 */

#pragma once

/*!
    @enum
    @brief Validation result codes
 */
typedef enum {
    OK = 0, ///< no error, succed
    InternalError, ///< library internal error
    ConnectionError, ///< netwotk connection error
    ServerError ///< server side error
} ValidationResult;

typedef enum {
    RequestSent,
    ResponseReceived
} ServerStatus;

typedef enum {
    Severe, 
    Medium, 
    Programflow, 
    EachLine
} LogSeverity;
