#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    float x, y, w;
} Point;

void init_zero_matrix(float matrix[3][3]);
void print_matrix(const float matrix[3][3]);
void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

void init_identity_matrix(float matrix[3][3]);
void scalar_multiply(float matrix[3][3], float scalar);
void multiply_matrices(const float a[3][3], const float b[3][3], float res[3][3]);

Point transform_point(const float mat[3][3], Point p);
void scale(float mat[3][3], float sx, float sy);
void shift(float mat[3][3], float tx, float ty);
void rotate(float mat[3][3], float angle);

#endif