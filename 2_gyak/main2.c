#include "matrix.h"
#include <stdio.h>

int main() {
    float mat[3][3];
    init_identity_matrix(mat);

    scale(mat, 2.0f, 2.0f);
    shift(mat, 10.0f, 5.0f);
    printf("Transformation matrix:\n");
    print_matrix(mat);

    scalar_multiply(mat, -1.0f);
    printf("Matrix multiplied by 1:\n");
    print_matrix(mat);

    Point p = {1.0f, 1.0f, 1.0f};
    Point tp = transform_point(mat, p);
    printf("Point (1,1) transformed: (%.2f, %.2f)\n", tp.x, tp.y);

    return 0;
}