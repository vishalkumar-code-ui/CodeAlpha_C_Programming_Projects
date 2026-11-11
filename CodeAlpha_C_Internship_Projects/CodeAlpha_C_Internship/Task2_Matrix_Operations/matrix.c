#include <stdio.h>

#define MAX 10

void readMatrix(int a[MAX][MAX], int rows, int cols, const char *name) {
    int i, j;
    printf("Enter elements of %s (%d x %d):\n", name, rows, cols);
    for (i = 0; i < rows; ++i)
        for (j = 0; j < cols; ++j) {
            printf("%s[%d][%d]: ", name, i + 1, j + 1);
            while (scanf("%d", &a[i][j]) != 1) {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {}
                printf("Please enter an integer: ");
            }
        }
}

void displayMatrix(int a[MAX][MAX], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) printf("%6d", a[i][j]);
        putchar('\n');
    }
}

void addMatrices(int a[MAX][MAX], int b[MAX][MAX],
                 int result[MAX][MAX], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; ++i)
        for (j = 0; j < cols; ++j) result[i][j] = a[i][j] + b[i][j];
}

void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX],
                      int result[MAX][MAX], int rows, int common, int cols) {
    int i, j, k;
    for (i = 0; i < rows; ++i)
        for (j = 0; j < cols; ++j) {
            result[i][j] = 0;
            for (k = 0; k < common; ++k)
                result[i][j] += a[i][k] * b[k][j];
        }
}

void transposeMatrix(int a[MAX][MAX], int result[MAX][MAX],
                     int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; ++i)
        for (j = 0; j < cols; ++j) result[j][i] = a[i][j];
}

int main(void) {
    int choice, r1, c1, r2, c2;
    int a[MAX][MAX], b[MAX][MAX], result[MAX][MAX];

    printf("=== CodeAlpha Matrix Operations ===\n");
    printf("1. Addition\n2. Multiplication\n3. Transpose\nChoose: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid choice.\n");
        return 1;
    }

    if (choice == 1) {
        printf("Enter rows and columns (1-%d): ", MAX);
        if (scanf("%d%d", &r1, &c1) != 2 || r1 < 1 || r1 > MAX || c1 < 1 || c1 > MAX) {
            printf("Invalid dimensions.\n"); return 1;
        }
        readMatrix(a, r1, c1, "A");
        readMatrix(b, r1, c1, "B");
        addMatrices(a, b, result, r1, c1);
        printf("A + B:\n"); displayMatrix(result, r1, c1);
    } else if (choice == 2) {
        printf("Enter rows and columns of A: ");
        if (scanf("%d%d", &r1, &c1) != 2 || r1 < 1 || r1 > MAX || c1 < 1 || c1 > MAX) {
            printf("Invalid dimensions.\n"); return 1;
        }
        printf("Enter rows and columns of B: ");
        if (scanf("%d%d", &r2, &c2) != 2 || r2 < 1 || r2 > MAX || c2 < 1 || c2 > MAX || c1 != r2) {
            printf("Invalid dimensions: columns of A must equal rows of B.\n"); return 1;
        }
        readMatrix(a, r1, c1, "A");
        readMatrix(b, r2, c2, "B");
        multiplyMatrices(a, b, result, r1, c1, c2);
        printf("A x B:\n"); displayMatrix(result, r1, c2);
    } else if (choice == 3) {
        printf("Enter rows and columns (1-%d): ", MAX);
        if (scanf("%d%d", &r1, &c1) != 2 || r1 < 1 || r1 > MAX || c1 < 1 || c1 > MAX) {
            printf("Invalid dimensions.\n"); return 1;
        }
        readMatrix(a, r1, c1, "A");
        transposeMatrix(a, result, r1, c1);
        printf("Transpose of A:\n"); displayMatrix(result, c1, r1);
    } else {
        printf("Invalid choice.\n");
        return 1;
    }
    return 0;
}
