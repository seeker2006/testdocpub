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
    ServerError, ///< server side error
    Deactivated, ///< license was successfully deactivated
    ActivationNotFound, ///< invalid activation id
    ActivationCancelled, ///< activation cancelled by user
    LicenseExpired, ///< license is expired
    ValidationFailed ///< token broken, expired or signed with wrong key
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
