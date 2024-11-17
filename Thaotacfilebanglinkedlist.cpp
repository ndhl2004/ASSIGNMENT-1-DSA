#include <stdio.h>
#define MAX_FILES 100 
typedef struct FileInfo {
    char name[100];  
    int size;        
    int timeStored;  
    struct FileInfo *next; 
} FileInfo;
FileInfo fileList[MAX_FILES]; 
int fileCount = 0; 
//Ham sao chep chuoi
void copyString(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0' && i < 99) {  // Dam bao ko tran bo nho
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  
}
//Ham so sanh chuoi
int compareString(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0;  
        }
        i++;
    }
    return str1[i] == str2[i];
}
//Ham them tep
void addFile(char* name, int size, int timeStored) {
    if (fileCount >= MAX_FILES) {
        printf("Danh sach day. khong them tep moi\n");
        return;
    }
    FileInfo* newFile = &fileList[fileCount];
    copyString(newFile->name, name);
    newFile->size = size;
    newFile->timeStored = timeStored;
    newFile->next = NULL;
    fileCount++;
    if (fileCount == 1) {
        newFile->next = NULL;
    } else {
        fileList[fileCount - 2].next = newFile;
    }
}
// Ham xoa tep
void deleteFile(char* name) {
    if (fileCount == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    FileInfo* temp = &fileList[0];
    FileInfo* prev = NULL;
    if (temp != NULL && compareString(temp->name, name)) {
        if (fileCount > 1) {
            fileList[0] = fileList[1]; 
        }
        fileCount--; 
        printf("Xoa tep: %s\n", name);
        return;
    }
    while (temp != NULL && !compareString(temp->name, name)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Tep khong ton tai.\n");
        return;
    }
    prev->next = temp->next;
    fileCount--;
    printf("Xoa tep: %s\n", name);
}
//Ham in danh sach tep
void printFiles() {
    if (fileCount == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    printf("Danh sach tep:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("Ten: %s, Dung luong: %d KB, Thoi gian luu: %d ngay\n", fileList[i].name, fileList[i].size, fileList[i].timeStored);
    }
    printf("\n");
}
//Ham sap xep file theo dubblesort
void sortFilesBySize() {
    if (fileCount == 0 || fileCount == 1) return;
    for (int i = 0; i < fileCount - 1; i++) {
        for (int j = i + 1; j < fileCount; j++) {
            if (fileList[i].size > fileList[j].size) {
                FileInfo temp = fileList[i];
                fileList[i] = fileList[j];
                fileList[j] = temp;
            }
        }
    }
}
int main() {
    addFile("file1.txt", 500, 10);
    addFile("file2.txt", 200, 30);
    addFile("file3.txt", 200, 15);
    addFile("file4.txt", 1000, 5);
    printf("Danh sach tep ban dau:\n");
    printFiles();
    sortFilesBySize();
    printf("Danh sach sau khi sap xep theo dung luong tang dan:\n");
    printFiles();
    deleteFile("file3.txt");
    printf("Danh sach sau khi xoa tep file3.txt:\n");
    printFiles();
    addFile("file3.txt", 200, 30);
    printf("Danh sach sau khi them lai tep file3.txt:\n");
    printFiles();
    return 0;
}

