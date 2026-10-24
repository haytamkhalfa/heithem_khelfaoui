#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;


void initStack(Stack *s) {
    s->top = NULL;
}

int isEmpty(Stack s) {
    return s.top == NULL;
}

void push(Stack *s, char value) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = value;
    n->next = s->top;
    s->top = n;
}

char pop(Stack *s) {
    if (isEmpty(*s)) {
        printf("Error: stack is empty.\n");
        return 0;
    }
    Node *tmp = s->top;
    char value = tmp->data;
    s->top = tmp->next;
    free(tmp);
    return value;
}

char peek(Stack s) {
    if (isEmpty(s)) {
        printf("Error: stack is empty.\n");
        return 0;
    }
    return s.top->data;
}

void display(Stack s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack (top to bottom): ");
    Node *p = s.top;
    while (p != NULL) {
        printf("%c ", p->data);
        p = p->next;
    }
    printf("\n");
}


void practicalExample() {
    char expr[] = "(A+B)*C";
    Stack s;
    initStack(&s);
    int i;

    printf("Pushing: ");
    for (i = 0; expr[i] != '\0'; i++) {
        push(&s, expr[i]);
        printf("%c ", expr[i]);
    }

    printf("\nPopping: ");
    while (!isEmpty(s)) {
        printf("%c ", pop(&s));
    }
    printf("\n(Reverse order, so LIFO is confirmed)\n");
}


int evaluatePostfix(char expr[]) {
    Stack s;
    initStack(&s);
    int i;

    for (i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];

        if (c >= '0' && c <= '9') {
            push(&s, c - '0');
        } else {
            int b = pop(&s);
            int a = pop(&s);
            int result = 0;

            if (c == '+') result = a + b;
            else if (c == '-') result = a - b;
            else if (c == '*') result = a * b;
            else if (c == '/') {
                if (b == 0) {
                    printf("Error: division by zero.\n");
                    return 0;
                }
                result = a / b;
            } else {
                printf("Error: unknown symbol '%c'.\n", c);
                return 0;
            }
            push(&s, result);
        }
    }
    return pop(&s);
}


int main() {
    Stack s;
    initStack(&s);
    int choice;

    do {
        printf("\n===== STACK MENU =====\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Evaluate a postfix expression\n");
        printf("5. Run example (A+B)*C\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            char c;
            printf("Character to push: ");
            scanf(" %c", &c);
            push(&s, c);
        }
        else if (choice == 2) {
            if (isEmpty(s))
                printf("Error: stack is empty.\n");
            else
                printf("Popped: %c\n", pop(&s));
        }
        else if (choice == 3) {
            display(s);
        }
        else if (choice == 4) {
            char expr[100];
            char c;
            int i = 0;
            printf("Enter the postfix expression symbol by symbol, ");
            printf("end with = (example: 6 3 + 2 * 4 / =):\n");
            scanf(" %c", &c);
            while (c != '=' && i < 99) {
                expr[i] = c;
                i++;
                scanf(" %c", &c);
            }
            expr[i] = '\0';
            printf("Result = %d\n", evaluatePostfix(expr));
        }
        else if (choice == 5) {
            practicalExample();
        }
        else if (choice == 0) {
            printf("Goodbye!\n");
        }
        else {
            printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
