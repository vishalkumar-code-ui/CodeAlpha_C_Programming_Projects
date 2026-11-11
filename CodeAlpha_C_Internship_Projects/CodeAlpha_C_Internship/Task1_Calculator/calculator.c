#include <stdio.h>

int main(void) {
    double a, b;
    char op;

    printf("=== CodeAlpha Basic Calculator ===\n");
    printf("Enter an expression (example: 12.5 + 3): ");
    if (scanf("%lf %c %lf", &a, &op, &b) != 3) {
        printf("Invalid input. Use: number operator number\n");
        return 1;
    }

    switch (op) {
        case '+': printf("Result: %.2f\n", a + b); break;
        case '-': printf("Result: %.2f\n", a - b); break;
        case '*': printf("Result: %.2f\n", a * b); break;
        case '/':
            if (b == 0.0) {
                printf("Error: division by zero is not allowed.\n");
                return 1;
            }
            printf("Result: %.2f\n", a / b);
            break;
        default:
            printf("Invalid operator. Use +, -, * or /.\n");
            return 1;
    }
    return 0;
}
