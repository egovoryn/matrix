#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;

typedef struct matrix_struct {
    double **matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;

// MAIN FUNCTIONS

matrix_t create_matrix(int rows, int columns);     // Create matrix
void remove_matrix(matrix_t *A);                   // Clean matrix
int eq_matrix(matrix_t *A, matrix_t *B);           // Matrix equality
matrix_t sum_matrix(matrix_t *A, matrix_t *B);     // Matrix addition
matrix_t sub_matrix(matrix_t *A, matrix_t *B);     // Matrix subtraction
matrix_t mult_number(matrix_t *A, double number);  // Multiplication of matrix and number
matrix_t mult_matrix(matrix_t *A, matrix_t *B);    // Multiplication of two matrices
matrix_t transpose(matrix_t *A);                   // Matrix transposition
matrix_t calc_complements(matrix_t *A);            // Matrix minor and matrix of algebraic complements
double determinant(matrix_t *A);
matrix_t inverse_matrix(matrix_t *A);

// SECONDARY FUNCTIONS

int check_inc(matrix_t *A);                             // Check the matrix for correctness
void check_output(matrix_t *A);                         // Set output matrix type
int check_input(matrix_t *A);                           // Find out the type of the input matrix
matrix_t cut_matrix(matrix_t *A, int row, int column);  // Trim matrix by i-j element
matrix_t minor_matrix(matrix_t *A);                     // Create a matrix of minors

#endif  // SRC_MATRIX_H_
