#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "ErrorCode.h"
#include "Matrix.h"

// The implementation of the struct is up to you
typedef struct Matrix {
    double* topLeft;
    uint32_t width, height;
} Matrix;

/**
 * @brief Creates a new matrix of a given height an width,
 *  all values are initially zeroes.
 *
 * @param[out] matrix The address of a matrix pointer to receive
 *  the address of the created matrix.
 * @param[in] height Height of the matrix
 * @param[in] width Width of the matrix
 * @return ErrorCode
 */
ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
	if (height <= 0 || width <= 0) {
		return NEG_INDEX_FAILURE; // error code 5: matrix size/indeces must be positive
	}
	// allocating memory for the matrix (with calloc so all the values will be 0)
	if (!(((*matrix) = (Matrix*) malloc(1)) && ((*matrix) -> topLeft = calloc(height * width, 8)))) {
		return MATRIX_CREATION_FAILURE; // error code 1: memmory allocation failed while creating matrix
	}
    // iniatializing the matrix's members
	(*matrix) -> height = height;
	(*matrix) -> width = width;
    return ERROR_SUCCESS; // error code 0: success!
}

/**
 * @brief Creates a new matrix from an old matrix.
 *
 * @param[out] matrix The address of a matrix pointer to receive
 *  the address of the copied matrix.
 * @param[in] source The matrix to copy.
 * @return ErrorCode
 */
ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {
    if ((*result) -> height != source -> height || (*result) -> width != source -> width) {
		return MATRIX_SIZE_FAILURE; // error code 2: matrices should have same size
	}
    // creating new pointers to iterate over the matrices without moving its pointer
	double* sourceHelp = source -> topLeft;
	double* resultHelp = (*result) -> topLeft;
	// iterating over the matrices
	for (uint32_t i = 0; i < source -> height * source -> width; i++) {
		// copying the value
		(*resultHelp) = (*sourceHelp);
        // updating the help pointers
		sourceHelp++;
        resultHelp++;
	}
	return ERROR_SUCCESS; // error code 0: success!
}

/**
 * @brief Destroys a matrix.
 *
 * @param matrix the matrix to destroy.
 */
void matrix_destroy(PMatrix matrix) {
	free(matrix);
}

/**
 * @brief Returns the height of a give matrix.
 *
 * @param[in] matrix The matrix.
 * @param[out] result On output, contains the height of the matrix.
 * @return ErrorCode
 */
ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
	*result = matrix -> height;
	return ERROR_SUCCESS; // error code 0: success!
}

/**
 * @brief Returns the width of a give matrix.
 *
* @param[in] matrix The matrix.
 * @param[out] result On output, contains the height of the matrix.
 * @return ErrorCode
 */
ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
	*result = matrix -> width;
	return ERROR_SUCCESS; // error code 0: success!
}

/**
 * @brief Sets a value to the matrix.
 *
 * @param[in, out] matrix The matrix to operate on.
 * @param[in] rowIndex Row index of the value to set.
 * @param[in] colIndex Column index of the value to setF.
 * @param[in] value Value to set.
 * @return ErrorCode
 */
ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double value) {
    if (rowIndex >= matrix -> height || colIndex >= matrix -> width) {
        return INDEX_FAILURE; // error code 4: index out of matrix's bounds
    }
	// creating pointer and moving it to the correct spot and setting the value
	double* help = matrix -> topLeft;
    help += rowIndex * matrix -> width + colIndex;
	*help = value;
	return ERROR_SUCCESS; // error code 0: success!
}

/**
 * @brief Sets a value to the matrix.
 *
 * @param[in] matrix The matrix to operate on.
 * @param[in] rowIndex Row index of the value to get.
 * @param[in] colIndex Column index of the value to get.
 * @param[out] value The address of a double variable to receive
 *  the value from the matrix.
 * @return ErrorCode
 */
ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double* value) {
	if (rowIndex >= matrix -> height || colIndex >= matrix -> width) {
        return INDEX_FAILURE; // error code 4: index out of matrix's bounds
    }
    // creating pointer and moving it to the correct spot and getting the value
	double* help = matrix -> topLeft;
    help += rowIndex * matrix -> width + colIndex;
    *value = *help;
	return ERROR_SUCCESS; // error code 0: success!
}

/**
 * @brief Computes the addition of two matrices.
 *
 * @param[out] result The address of a matrix pointer to receive
 *  the address of the resulting matrix.
 * @param[in] lhs The left hand side of the addition operation.
 * @param[in] rhs The right hand side of the addition operation.
 * @return ErrorCode
 */
ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
	if ((*result) -> height != lhs -> height || (*result) -> width != lhs -> width
		 || (*result) -> height != rhs -> height || (*result) -> width != rhs -> width) {
        return MATRIX_SIZE_FAILURE; // error code 2: matrices should have same size
    }
	// creating new pointers to iterate over the matrices without moving its pointer
	double* lHelp = lhs -> topLeft;
	double* rHelp = rhs -> topLeft;
	double* resultHelp = (*result) -> topLeft;
	// iterating over the matrices
	for (uint32_t i = 0; i < lhs -> height * lhs -> width; i++) {
        // setting each value of the result matrix as the sum of the original matrices respective values
		*resultHelp = *lHelp + *rHelp;
		// updating the pointers
        lHelp++;
		rHelp++;
        resultHelp++;
    }
	return ERROR_SUCCESS; // error code 0: success!
}

/**
 * @brief Computes the multiplication of two matrices.
 *
 * @param[out] result The address of a matrix pointer to receive
 *  the address of the resulting matrix.
 * @param[in] lhs The left hand side of the multiplication operation.
 * @param[in] rhs The right hand side of the multiplication operation.
 * @return ErrorCode
 */
ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
	if (lhs -> height != (*result) -> height || rhs -> width != (*result) -> width
        || lhs -> width != rhs -> height) {
        return MATRIX_MULT_FAILURE; // error code 3: matrices dimensions don't match up for multiplication
    }
	// creating new pointers to iterate over the matrices without moving its pointer
	double* lHelp = lhs -> topLeft;
    double* rHelp = rhs -> topLeft;
    double* resultHelp = (*result) -> topLeft;
	// iterating over the matrices
	for (uint32_t i = 0; i < (*result) -> height; i++) {
		for (uint32_t j = 0; j < (*result) -> width; j++) {
			for (uint32_t k = 0; k < lhs -> width; k++) {
				*resultHelp += (*lHelp) * (*rHelp);
				lHelp++;
				rHelp += rhs -> width;
			}
			resultHelp++;
			lHelp -= (lhs -> width);
			rHelp -= (rhs -> width * rhs -> height - 1);
		}
		lHelp += lhs -> width;
		rHelp = rhs -> topLeft;
	}
	return ERROR_SUCCESS; // error code 0: success!
}

/**
 * @brief Multiplies a matrix with a scalar and stores the result in
 *  the given matrix.
 *
 * @param[in, out] matrix On input, the matrix to multiply with a scalar.
 *  On output, the result of the multiplication operation.
 * @param[in] scalar The scalar to multiply with.
 * @return ErrorCode
 */
ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) {
	// creating a new pointer to iterate over the matrix without moving its pointer
	double* help = (*matrix).topLeft;
    for (uint32_t i = 0; i < (*matrix).height * (*matrix).width; i++) {
        // multiplying each value of the matrix by the scalar
		*help *= scalar;
		// updating the pointer
        help++;
    }
	return ERROR_SUCCESS; // error code 0: success!
}

// the following functions aren't necessary but are usefull for testing

void matrix_print(CPMatrix matrix) {
	double* help = matrix -> topLeft;
	printf("\n");
	for (uint32_t i = 0; i < matrix -> height; i++) {
		for (uint32_t j = 0; j < matrix -> width; j++) {
			printf("%f ", *help);
			help++;
		}
		printf("\n");
	}
	printf("\n");
}

PMatrix matrix_createWithValues() {
	PMatrix matrix;
	uint32_t width, height;
	printf("enter matrix width: ");
	scanf("%d", &width);
	printf("enter matrix height: ");
	scanf("%d", &height);
	printf("%s", error_getErrorMessage(matrix_create(&matrix, height, width)));
	for (uint32_t i = 0; i < height; i++) {
		for (uint32_t j = 0; j < width; j++) {
			double value;
			printf("enter element %d %d: ", j, i);
			scanf("%lf", &value);
			printf("%s", error_getErrorMessage(matrix_setValue(matrix, i, j, value)));
		}
	}
	matrix_print(matrix);
	return matrix;
}
