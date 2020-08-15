#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    // DON'T CHANGE THIS VALUE!
    ERROR_SUCCESS = 0, // error code 0: success!
    MATRIX_CREATION_FAILURE = 1, // error code 1: memmory allocation failed while creating matrix
    MATRIX_SIZE_FAILURE = 2, // error code 2: matrices should have same size
    MATRIX_MULT_FAILURE = 3, // error code 3: matrices dimensions don't match up for multiplication
    INDEX_FAILURE = 4, // error code 4: indeces out of matrix's bounds
	NEG_INDEX_FAILURE = 5, // error code 5: matrix size/indeces must be positive
} ErrorCode;

/**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
bool error_isSuccess(ErrorCode code);

/**
 * @brief gets a textual error message for a given error code.
 *
 * @param[in] code the error code.
 * @return const char* the textual representation of the error code.
 */
const char* error_getErrorMessage(ErrorCode code);
