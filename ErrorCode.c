#include <stdbool.h>
#include <stdint.h>
#include "ErrorCode.h"

/*
typedef enum {
    // DON'T CHANGE THIS VALUE!
    ERROR_SUCCESS = 0, // error code 0: success!
	MATRIX_CREATION_FAILURE = 1, // error code 1: memmory allocation failed while creating matrix
	MATRIX_SIZE_FAILURE = 2, // error code 2: matrices should have same size
	MATRIX_MULT_FAILURE = 3, // error code 3: matrices dimensions don't match up for multiplication
	INDEX_FAILURE = 4, // error code 4: indeces out of matrix's bounds
} ErrorCode;
*/

/**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
bool error_isSuccess(ErrorCode code) {
	if (code == 0) {
		return false;
	}
	return true;
}

/**
 * @brief gets a textual error message for a given error code.
 *
 * @param[in] code the error code.
 * @return const char* the textual representation of the error code.
 */
const char* error_getErrorMessage(ErrorCode code) {
	switch (code) {
		case 0:
			return "";
		case 1:
			return "error code 1: memmory allocation failed while creating matrix\n";
		case 2:
			return "error code 2: matrices should have same size\n";
		case 3:
			return "error code 3: matrices dimensions don't match up for multiplication\n";
		case 4:
			return "error code 4: index out of matrix's bounds\n";
	}
}
