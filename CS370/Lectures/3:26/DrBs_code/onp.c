/*******************************************************************************
 * Name        : onp.c
 * Author      : Brian S. Borowski
 * Version     : 1.0
 * Date        : March 2, 2015
 * Description : Solution to SPOJ #4 - Reverse Polish Notation
 ******************************************************************************/
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 * Shunting-yard algorithm
 *   Simplified version that works with well-formed infix expressions only.
 *   No error handling.
 *
 * While there are tokens to be read:
 *     Read a token.
 *     If the token is an operand, add it to the output queue.
 *     If the token is an operator, o1:
 *         While there is an operator token, o2, at the top of the stack and
 *         o1's precedence is less than or equal to that of o2:
 *             Pop o2 off the stack and add it to the output queue.
 *         Push o1 onto the stack.
 *     If the token is a left parenthesis, push it onto the stack.
 *     If the token is a right parenthesis:
 *         Until the token at the top of the stack is a left parenthesis, pop
 *         operators off the stack and add them to the output queue.
 *         Pop the left parenthesis from the stack, but not do not add it to
 *         the output queue.
 * When there are no more tokens to read:
 *     While there are still operator tokens in the stack:
 *         Pop the operator from the stack and add it to the output queue.
 ******************************************************************************/

char expression[401], output[401], stack[400];
int precedence[128], stack_top;

void initialize_precedence_table() {
    precedence['+'] = 0;
    precedence['-'] = 1;
    precedence['*'] = 2;
    precedence['/'] = 3;
    precedence['^'] = 4;
}

inline int is_operand(char c) {
    return c >= 'a' && c <= 'z';
}

inline int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void shunting_yard() {
    int i = 0, output_index = 0, len = strlen(expression);
    char char_on_stack;

    /* Remove the new line character. */
    expression[--len] = '\0';
    /* Clear the stack. */
    stack_top = -1;

    while (i < len) {
        char c = expression[i];
        if (is_operand(c)) {
            output[output_index++] = c;
        } else if (is_operator(c)) {
            if (stack_top != -1) {
                char_on_stack = stack[stack_top];
                while (is_operator(char_on_stack) &&
                       precedence[(unsigned)c] <=
                           precedence[(unsigned)char_on_stack]) {
                    output[output_index++] = c;
                    --stack_top;
                    if (stack_top == -1) {
                        break;
                    }
                    char_on_stack = stack[stack_top];
                }
            }
            stack[++stack_top] = c;
        } else if (c == '(') {
            stack[++stack_top] = c;
        } else if (c == ')') {
            do {
                char_on_stack = stack[stack_top--];
                if (char_on_stack == '(') {
                    break;
                }
                output[output_index++] = char_on_stack;
            } while (1);
        }
        ++i;
    }
    while (stack_top > -1) {
        output[output_index++] = stack[stack_top--];
    }
    output[output_index] = '\0';
}

int main() {
    int num_lines, i;
    initialize_precedence_table();
    scanf("%d\n", &num_lines);
    for (i = 0; i < num_lines; ++i) {
        fgets(expression, 401, stdin);
        shunting_yard();
        printf("%s\n", output);
    }
    return 0;
}
