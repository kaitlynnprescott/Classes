/*******************************************************************************
 * Name        : maximumelement.c
 * Author      : Brian S. Borowski
 * Version     : 1.0
 * Date        : February 7, 2016
 * Description : Solution to HackerRank -> Data Structures -> Stacks ->
 *               Maximum Element
 ******************************************************************************/
#include <stdio.h>

int value_stack[100000], max_stack[100000];
int value_stack_top = -1, max_stack_top = -1;

int main() {
    int num_queries, query_type, value, i;
    scanf("%d", &num_queries);
    for (i = 0; i < num_queries; i++) {
        scanf("%d", &query_type);
        if (query_type == 1) {
            scanf("%d", &value);
            value_stack[++value_stack_top] = value;
            if (max_stack_top == -1 || value >= max_stack[max_stack_top]) {
                max_stack[++max_stack_top] = value;
            }
        } else if (query_type == 2) {
            value = value_stack[value_stack_top--];
            if (value == max_stack[max_stack_top]) {
                --max_stack_top;
            }
        } else {
            if (max_stack_top == -1) {
                printf("Stack is empty.\n");
            } else {
                printf("%d\n", max_stack[max_stack_top]);
            }
        }
    }
    return 0;
}
