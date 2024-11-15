#include <stdio.h>
typedef struct {
    char name[50];  
    int age;     
} Wood;
#define kichthuoc 100  
typedef struct {
    Wood data[kichthuoc];  
    int top;              
} Stack;
// Khoi tao stack
void khoitaostack(Stack* stack) {
    stack->top = -1;  
}
// Kiem tra stack rong
int Empty(Stack* stack) {
    return stack->top == -1;
}
// Kiem tra stack full
int Full(Stack* stack) {
    return stack->top == kichthuoc - 1;
}
// Them mot thanh go vao stack
int push(Stack* stack, Wood wood) {
    if (Full(stack)) {
        return 0;  // Stack day, khong the them
    }
    stack->data[++stack->top] = wood;  // Them phan tu vao vi tri moi
    return 1;
}
// Lay mot thanh go ra khoi stack
int pop(Stack* stack, Wood* wood) {
    if (Empty(stack)) {
        return 0;  // Stack rong, khong the lay
    }
    *wood = stack->data[stack->top--];  // Lay phan tu tren cung
    return 1;
}
// Dem so luong thanh go co tuoi cu the
int countage(Stack* stack, int age) {
    int count = 0;
    for (int i = 0; i <= stack->top; i++) {
        if (stack->data[i].age == age) {
            count++;
        }
    }
    return count;
}
// Hien thi stack
void display(Stack* stack) {
    if (Empty(stack)) {
        printf("Stack rong.\n");
        return;
    }
    printf("Danh sach cac thanh go trong stack:\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("Ten go: %s, Tuoi: %d\n", stack->data[i].name, stack->data[i].age);
    }
}
int main() {
    Stack stack;
    khoitaostack(&stack);
    int choice;
    do {
        printf("\n    MENU    \n");
        printf("1. Them thanh go\n");
        printf("2. Lay thanh go ra khoi stack\n");
        printf("3. Dem so thanh go co cung tuoi\n");
        printf("4. Hien thi danh sach go\n");
        printf("0. Thoat\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                if (Full(&stack)) {
                    printf("Stack day, khong the them.\n");
                } else {
                    Wood wood;
                    printf("Nhap ten go: ");
                    scanf("%s", wood.name);
                    printf("Nhap tuoi go: ");
                    scanf("%d", &wood.age);
                    push(&stack, wood);
                }
                break;
            }
            case 2: {
                Wood wood;
                if (pop(&stack, &wood)) {
                    printf("Ða lay ra: Ten go: %s, Tuoi: %d\n", wood.name, wood.age);
                } else {
                    printf("Stack rong, khong the lay ra.\n");
                }
                break;
            }
            case 3: {
                int age;
                printf("Nhap tuoi go can dem: ");
                scanf("%d", &age);
                int count = countage(&stack, age);
                printf("So thanh go co cung tuoi %d: %d\n", age, count);
                break;
            }
            case 4:
                display(&stack);
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop li. Vui long chon lai.\n");
        }
    } while (choice != 0);
    return 0;
}

