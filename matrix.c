#include "matrix.h"

matrix_t create_matrix(int rows, int columns) {
    matrix_t temp = {NULL, 0, 0, CORRECT_MATRIX};
    if ((rows > 0) && (columns > 0)) {
        temp.matrix_type = ZERO_MATRIX;
        temp.rows = rows;
        temp.columns = columns;
        temp.matrix = (double **)calloc(sizeof(double *), rows);
        for (int i = 0; i < rows; i++) {
            temp.matrix[i] = (double *)calloc(sizeof(double), columns);
        }
    } else {
        temp.matrix_type = INCORRECT_MATRIX;
    }
    return temp;
}

int check_inc(matrix_t *A) {
    // 1 – ERROR; 0 – NO ERROR
    return A->matrix_type == INCORRECT_MATRIX ? 1 : 0;
}

int check_input(matrix_t *A) {
    int type = 0;
    if (!check_inc(A)) {
        int flag = 1;
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                int tmp = round(A->matrix[i][j] * 10000000);
                if (i == j) {
                    if (tmp != 1e7) flag = 0;
                } else {
                    if (tmp != 0) flag = 0;
                }
                if (!flag) break;
            }
            if (!flag) break;
        }
        if (flag) {
            type = 2;
        } else {
            flag = 1;
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    int tmp = round(A->matrix[i][j] * 10000000);
                    if (tmp != 0) {
                        flag = 0;
                        break;
                    }
                }
                if (!flag) break;
            }
            if (flag) type = 3;
        }
    } else {
        type = 1;
    }
    return type;
}

void check_output(matrix_t *A) {
    int flag = 1;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            int tmp = round(A->matrix[i][j] * 10000000);
            if (i == j) {
                if (tmp != 1e7) flag = 0;
            } else {
                if (tmp != 0) flag = 0;
            }
            if (!flag) break;
        }
        if (!flag) break;
    }
    if (flag) {
        A->matrix_type = IDENTITY_MATRIX;
    } else {
        flag = 1;
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                int tmp = round(A->matrix[i][j] * 10000000);
                if (tmp != 0) {
                    flag = 0;
                    break;
                }
            }
            if (!flag) break;
        }
        if (flag)
            A->matrix_type = ZERO_MATRIX;
        else
            A->matrix_type = CORRECT_MATRIX;
    }
}

void remove_matrix(matrix_t *A) {
    if (A->matrix_type != INCORRECT_MATRIX) {
        for (int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
        free(A->matrix);
        A->columns = 0;
        A->rows = 0;
        A->matrix_type = INCORRECT_MATRIX;
    }
}

int eq_matrix(matrix_t *A, matrix_t *B) {
    // 1 – SUCCESS; 0 – FAIL
    int flag = 0;
    if (!check_inc(A) && !check_inc(B)) {
        if (A->matrix_type == 2 && B->matrix_type == 2) {
            flag = 1;
        } else if (A->matrix_type == 3 && B->matrix_type == 3) {
            flag = 1;
        } else if (A->rows == B->rows && A->columns == B->columns) {
            flag = 1;
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
                        flag = 0;
                        break;
                    }
                }
                if (!flag) break;
            }
        }
    }
    return flag;
}

matrix_t sum_matrix(matrix_t *A, matrix_t *B) {
    // C(i,j) = A(i,j) + B(i,j)
    int rows = A->rows;
    int columns = A->columns;
    matrix_t C = {NULL, 0, 0, CORRECT_MATRIX};
    if (A->rows == B->rows && A->columns == B->columns && !check_inc(A) && !check_inc(B)) {
        C = create_matrix(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                C.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
        check_output(&C);
    } else {
        C.matrix_type = INCORRECT_MATRIX;
    }
    return C;
}

matrix_t sub_matrix(matrix_t *A, matrix_t *B) {
    // C(i,j) = A(i,j) - B(i,j)
    int rows = A->rows;
    int columns = A->columns;
    matrix_t C = {NULL, 0, 0, CORRECT_MATRIX};
    if (A->rows == B->rows && A->columns == B->columns && !check_inc(A) && !check_inc(B)) {
        C = create_matrix(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                C.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        }
        check_output(&C);
    } else {
        C.matrix_type = INCORRECT_MATRIX;
    }
    return C;
}

matrix_t mult_number(matrix_t *A, double number) {
    // B = λ × A = λ × A(i,j)
    int rows = A->rows;
    int columns = A->columns;
    matrix_t B = create_matrix(rows, columns);
    if (!check_inc(A)) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                B.matrix[i][j] = A->matrix[i][j] * number;
            }
        }
        check_output(&B);
    } else {
        B.matrix_type = INCORRECT_MATRIX;
    }
    return B;
}

matrix_t mult_matrix(matrix_t *A, matrix_t *B) {
    // C(i,j) = A(i,k) × B(k,j)
    int m = A->rows;     // rows A
    int q = B->columns;  // columns B
    int n = A->columns;  // columns A = rows B
    matrix_t C = {NULL, 0, 0, CORRECT_MATRIX};
    if (!check_inc(A) && !check_inc(B) && A->columns == B->rows) {
        C = create_matrix(m, q);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < q; j++) {
                C.matrix[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    C.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                }
            }
        }
        check_output(&C);
    } else {
        C.matrix_type = INCORRECT_MATRIX;
    }
    return C;
}

matrix_t transpose(matrix_t *A) {
    // A(j,i) = A(i,j)^T
    int m = A->rows, n = A->columns;
    matrix_t temp = {NULL, 0, 0, CORRECT_MATRIX};
    if (!check_inc(A)) {
        temp = create_matrix(n, m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                temp.matrix[j][i] = A->matrix[i][j];
            }
        }
        check_output(&temp);
    } else {
        temp.matrix_type = INCORRECT_MATRIX;
    }
    return temp;
}

matrix_t cut_matrix(matrix_t *A, int row, int column) {
    int offRow = 0;
    int offColumn = 0;
    int size = A->rows;
    int n = size - 1;
    matrix_t temp;
    temp = create_matrix(n, n);
    temp.matrix_type = 0;
    for (int i = 0; i < n; i++) {
        if (i == row) offRow = 1;
        offColumn = 0;
        for (int j = 0; j < n; j++) {
            if (j == column) offColumn = 1;
            temp.matrix[i][j] = A->matrix[i + offRow][j + offColumn];
        }
    }
    return temp;
}

double determinant(matrix_t *A) {
    double det = 0.0;
    if ((A->rows != A->columns) || (A->matrix_type == INCORRECT_MATRIX)) {
        det = NAN;
    } else {
        int size = A->rows;
        if (size == 1) {
            det = A->matrix[0][0];
        } else if (size == 2) {
            det = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
        } else {
            matrix_t temp;
            int degree = 1;
            for (int j = 0; j < size; j++) {
                temp = cut_matrix(A, 0, j);
                // (-1)^(1+j) * matrix[0][j] * minor_j
                det += degree * A->matrix[0][j] * determinant(&temp);
                remove_matrix(&temp);
                degree = -degree;
            }
        }
    }
    return det;
}

matrix_t minor_matrix(matrix_t *A) {
    matrix_t minor;
    minor = create_matrix(A->rows, A->columns);
    matrix_t tmp_matrix;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            tmp_matrix = cut_matrix(A, i, j);
            minor.matrix[i][j] = determinant(&tmp_matrix);
            remove_matrix(&tmp_matrix);
        }
    }
    return minor;
}

matrix_t calc_complements(matrix_t *A) {
    // M. = (-1)^(i+j) * minor_ij
    int size = A->rows;
    matrix_t temp = {NULL, 0, 0, CORRECT_MATRIX};
    if ((A->rows != A->columns) || (A->matrix_type == INCORRECT_MATRIX)) {
        temp.matrix_type = INCORRECT_MATRIX;
    } else {
        temp = minor_matrix(A);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                temp.matrix[i][j] *= pow(-1.0, i + j);
            }
        }
        check_output(&temp);
    }
    return temp;
}

matrix_t inverse_matrix(matrix_t *A) {
    matrix_t inverse;
    if ((A->rows != A->columns) || (A->matrix_type == INCORRECT_MATRIX)) {
        inverse.matrix_type = INCORRECT_MATRIX;
    } else {
        float det = determinant(A);
        if (det == 0) {
            inverse.matrix_type = INCORRECT_MATRIX;
        } else {
            matrix_t comp = calc_complements(A);
            matrix_t transp = transpose(&comp);
            remove_matrix(&comp);
            inverse = mult_number(&transp, 1 / det);
            remove_matrix(&transp);
            check_output(&inverse);
        }
    }
    return inverse;
}
