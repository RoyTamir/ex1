#include <stdbool.h>
#include <stdint.h>
#include "ErrorCode.h"

/**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
bool error_isSuccess(ErrorCode code) {
	return !code;
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
			return "error code 3: matrices' dimensions don't match up for multiplication\n";
		case 4:
			return "error code 4: index out of matrix's bounds\n";
		case 5:
			return "error code 5: matrix size/indeces must be positive\n";
	}
}
