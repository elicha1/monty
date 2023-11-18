#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_SIZE 1000

typedef struct {
    int stack[STACK_SIZE];
    int top;
} Stack;

void push(Stack *stack, int value) {
    if (stack->top < STACK_SIZE) {
        stack->stack[stack->top++] = value;
    } else {
        fprintf(stderr, "Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

void pall(Stack *stack) {
    int i;
    for (i = stack->top - 1; i >= 0; i--) {
        printf("%d\n", stack->stack[i]);
    }
}

int main() {
    FILE *file = fopen("bytecodes/00.m", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Can't open file\n");
        return EXIT_FAILURE;
    }

    Stack stack;
    stack.top = 0;

    char opcode[5];
    int value;

    while (fscanf(file, "%s %d", opcode, &value) == 2) {
        if (strcmp(opcode, "push") == 0) {
            push(&stack, value);
        } else if (strcmp(opcode, "pall") == 0) {
            pall(&stack);
        } else {
            fprintf(stderr, "Error: Unknown opcode '%s'\n", opcode);
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    fclose(file);
    return 0;
}
