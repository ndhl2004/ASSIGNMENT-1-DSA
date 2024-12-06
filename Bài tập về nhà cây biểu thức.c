#include <stdio.h>
#include <math.h>
// Define the structure for a tree node
typedef struct Node {
    char value[10];
    struct Node* left;
    struct Node* right;
} Node;
// Memory pool for nodes
#define MAX_NODES 100
Node nodePool[MAX_NODES];
int nodePoolIndex = 0;
// Function to create a new node
Node* createNode(const char* value) {
    if (nodePoolIndex >= MAX_NODES) {
        return NULL; // Memory pool exhausted
    }
    Node* node = &nodePool[nodePoolIndex++];
    int i = 0;
    while (value[i] != '\0' && i < 9) {
        node->value[i] = value[i];
        i++;
    }
    node->value[i] = '\0';
    node->left = node->right = NULL;
    return node;
}
// Function to check if a given character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}
// Define a simple stack structure for nodes
typedef struct StackNode {
    Node* treeNode;
    struct StackNode* next;
} StackNode;
#define MAX_STACK_NODES 100
StackNode stackNodePool[MAX_STACK_NODES];
int stackNodePoolIndex = 0;
typedef struct Stack {
    StackNode* top;
} Stack;
void push(Stack* stack, Node* treeNode) {
    if (stackNodePoolIndex >= MAX_STACK_NODES) {
        return; // Stack node pool exhausted
    }
    StackNode* newNode = &stackNodePool[stackNodePoolIndex++];
    newNode->treeNode = treeNode;
    newNode->next = stack->top;
    stack->top = newNode;
}
Node* pop(Stack* stack) {
    if (stack->top == NULL) return NULL;
    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    return temp->treeNode;
}
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}
// Function to build the expression tree
Node* buildExpressionTree(const char* postfix) {
    Stack stack = {NULL};
    char buffer[10];
    int bufferIndex = 0;
    for (int i = 0; postfix[i] != '\0'; ++i) {
        char ch = postfix[i];
        if (ch == ' ') continue;
        if (isOperator(ch)) {
            buffer[bufferIndex] = '\0';
            if (bufferIndex > 0) {
                push(&stack, createNode(buffer));
                bufferIndex = 0;
            }
            char op[2] = {ch, '\0'};
            Node* node = createNode(op);
            node->right = pop(&stack);
            node->left = pop(&stack);
            push(&stack, node);
        } else {
            buffer[bufferIndex++] = ch;
        }
    }
    if (bufferIndex > 0) {
        buffer[bufferIndex] = '\0';
        push(&stack, createNode(buffer));
    }
    return pop(&stack);
}
// Function to evaluate the expression tree
double evaluate(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return atof(root->value);
    double left_val = evaluate(root->left);
    double right_val = evaluate(root->right);
    switch (root->value[0]) {
        case '+': return left_val + right_val;
        case '-': return left_val - right_val;
        case '*': return left_val * right_val;
        case '/': return left_val / right_val;
        case '^': return (int)pow(left_val, right_val);
    }
    return 0;
}
// Function to print the infix expression without parentheses
void printInfix(Node* root) {
    if (root != NULL) {
        printInfix(root->left);
        printf("%s ", root->value);
        printInfix(root->right);
    }
}
// Function to print the prefix expression
void printPrefix(Node* root) {
    if (!root) return;
    printf("%s ", root->value);
    printPrefix(root->left);
    printPrefix(root->right);
}
// Function to print the postfix expression
void printPostfix(Node* root) {
    if (!root) return;
    printPostfix(root->left);
    printPostfix(root->right);
    printf("%s ", root->value);
}
int main() {
    const char* postfix = "a 5 b * c / + c 8 ^ - d e 1 2 / ^ * +";
    Node* root = buildExpressionTree(postfix);
    printf("Infix expression: ");
    printInfix(root);
    printf("\n");
    printf("Prefix expression: ");
    printPrefix(root);
    printf("\n");
    printf("Postfix expression: ");
    printPostfix(root);
    printf("\n");
    return 0;
}