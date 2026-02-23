#include "matrix.h"
#include <stdio.h>
#include <math.h>

void init_zero_matrix(float matrix[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0f;
        }
    }
}

void print_matrix(const float matrix[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void init_identity_matrix(float matrix[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

void scalar_multiply(float matrix[3][3], float scalar) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] *= scalar;
        }
    }
}

void multiply_matrices(const float a[3][3], const float b[3][3], float res[3][3]) {
    float tmp[3][3] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                tmp[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) res[i][j] = tmp[i][j];
}

Point transform_point(const float mat[3][3], Point p) {
    Point res;
    res.x = mat[0][0] * p.x + mat[0][1] * p.y + mat[0][2] * p.w;
    res.y = mat[1][0] * p.x + mat[1][1] * p.y + mat[1][2] * p.w;
    res.w = mat[2][0] * p.x + mat[2][1] * p.y + mat[2][2] * p.w;
    return res;
}

void scale(float mat[3][3], float sx, float sy) {
    float s_mat[3][3];
    init_identity_matrix(s_mat);
    s_mat[0][0] = sx;
    s_mat[1][1] = sy;
    multiply_matrices(s_mat, mat, mat);
}

void shift(float mat[3][3], float tx, float ty) {
    float t_mat[3][3];
    init_identity_matrix(t_mat);
    t_mat[0][2] = tx;
    t_mat[1][2] = ty;
    multiply_matrices(t_mat, mat, mat);
}

void rotate(float mat[3][3], float angle) {
    float r_mat[3][3];
    init_identity_matrix(r_mat);
    float c = cos(angle);
    float s = sin(angle);
    r_mat[0][0] = c;  r_mat[0][1] = -s;
    r_mat[1][0] = s;  r_mat[1][1] = c;
    multiply_matrices(r_mat, mat, mat);
}