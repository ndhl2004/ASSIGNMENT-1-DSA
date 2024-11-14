#include<stdio.h>
#include <stdlib.h> 
#include <string.h>
#define MWL 50
//khai bao nut
struct Node {
	char word[MWL];
	int frequency;
	struct Node* next;
};
//khai bao nut dau
struct Linkedlist {
	struct Node* head;
};
//khoi tao danh sach
void initList (struct Linkedlist* list) {
	list->head = 0;
}
//dua vao cac nut
void addword (struct Linkedlist* list, char* word) {
	struct Node* current = list -> head;
	while (current != 0) {
		int i = 0;
		while (current->word[i]!= '\0' && word[i]!= '\0'&& current->word[i] == word[i])
		i++;
	
	if (current -> word[i]=='\0'&& word[i]=='\0'){
		current->frequency++;
		return;
	}
	current = current->next;
	}
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	int j = 0;
	while (word[j]!='\0') {
		newNode->word[j]=word[j];
		j++;
	}
	newNode->word[j]='\0';
	newNode->frequency=1;
	newNode->next = list ->head;
	list->head = newNode;
}
//ham xac dinh tu xuat hien nhieu nhat trong cau
char* timtuxuathiennhieunhat(struct Linkedlist* list) {
	struct Node* current = list->head;
	struct Node* mostfrequent = 0;
	int maxfrequency = 0;
	while (current != 0){
		if (current->frequency > maxfrequency) {
			maxfrequency = current->frequency;
			mostfrequent = current;
		}
		current = current -> next;
	}
	return mostfrequent != 0? mostfrequent->word : 0;
}
//ham loai bo tu giong nhau
void removeword (struct Linkedlist* list) {
	struct Node* current = list->head;
	struct Node* prev = 0;
	while (current !=0){
		int len = 0;
		while (current->word[len] != '\0') {
			len++;
		}
		if (len % 2 == 0){
			int half = len /2;
			int isRepeated = 1;
			for (int i = 0; i< half; i++) {
				if (current ->word[i] != current -> word[i+half]) {
					isRepeated = 0;
					break;
				}
			}
			if (isRepeated) {
				if (prev == 0) {
					list -> head = current -> next;
			} else {
				prev->next = current -> next;
			}
			struct Node* temp = current;
			current = current -> next;
			free(temp);
			continue;
				}
			}
			prev = current;
			current = current->next;
		}
	}
//dem so luong tu trong cau
int countword (struct Linkedlist* list) {
	struct Node* current = list->head;
	int count = 0;
	while (current != 0) {
		count++;
		current = current ->next;
	}
	return count;
}
void printList(struct Linkedlist* list) {
    struct Node* current = list->head;
    while (current != 0) {
        printf("Tu: %s - Tan so: %d\n", current->word, current->frequency);
        current = current->next;
    }
}
void freeList(struct Linkedlist* list) {
    struct Node* current = list->head;
    while (current != 0) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = 0;
}
int main() {
	struct Linkedlist list;
	initList (&list);
	addword(&list, "xanh");
	addword(&list, "xanh");
    addword(&list, "dep");
    addword(&list, "xanh");
    addword(&list, "dep");
    addword(&list, "don");
    addword(&list, "don");
    char* mostfrequent = timtuxuathiennhieunhat(&list);
    if (mostfrequent != 0) {
        printf("Tu xuat hien nhieu nhat: %s\n", mostfrequent);
    } else {
        printf("Danh sach trong.\n");
    removeword(&list);
    printf("Danh sach sau khi loai bo tu lay:\n");
    printList(&list);
    removeword(&list);
    int uniqueWordCount = countword(&list);
    printf("So luong tu xuat hien trong cau: %d\n", uniqueWordCount);
    freeList(&list);
    return 0;
    }
}
