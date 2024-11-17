#include <stdio.h>
struct Node {
    int data;     // du lieu nut
    Node* next;   // Con tro toi nut ke tiep
};
typedef Node* PNode;   
typedef PNode LinkedList;   
void DeleteNode(LinkedList& H, PNode P) {
    if (H == NULL) {
        printf("Danh sach rong\n");
        return;
    }
    if (H == P && P->next == NULL) { //neu danh sach H chi co 1 phan tu
        H = NULL;
        delete P;
    } else if (H == P) { // Neu P la nut dau tien
        H = P->next; 
        delete P;
    } else { 
        PNode R = H;
        while (R->next != P && R->next != NULL) { 
            R = R->next;
        }
        if (R->next == NULL) { 
            printf("Khong tim thay nut P trong danh sach\n");
            return;
        }

        if (P->next == NULL) { // Neu P la nut cuoi
            R->next = NULL;   
            delete P;         
        } else { 
            R->next = P->next; 
            delete P;          
        }
    }
}
// Them nut moi vao danh sach
void AddNode(LinkedList& H, int value) {
    PNode newNode = new Node{value, NULL};
    if (H == NULL) {
        H = newNode;
    } else {
        PNode temp = H;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
// in danh sach
void PrintList(LinkedList H) {
    PNode temp = H;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
int main() {
    LinkedList list = NULL;
    AddNode(list, 48390);
    AddNode(list, 34049);
    AddNode(list, 49594);
    AddNode(list, 84093);
    printf("Danh sach ban dau: ");
    PrintList(list);
    printf ("\nXoa nut dau tien:");
    DeleteNode(list, list);
    PrintList(list);
    printf ("\nXoa nut cuoi cung:");
    PNode temp = list;
    while (temp->next->next != NULL) temp = temp->next; 
    DeleteNode(list, temp->next);
    PrintList(list);
    printf ("\nXoa nut sau nut dau tien:");
    DeleteNode(list, list->next);
    PrintList(list);
    return 0;
}

