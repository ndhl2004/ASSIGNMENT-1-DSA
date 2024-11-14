#include <iostream>
using namespace std;
struct FileNode {
    char fileName[100];     // Ten file
    unsigned long fileSize; // kich thuoc file
    unsigned long creationTime; // Thoi gian tao file
    FileNode* next;         // Con tro dan den file tiep theo
    FileNode(const char* name, unsigned long size, unsigned long time) {
        int i = 0;
        while (name[i] != '\0' && i < 100) {
            fileName[i] = name[i];
            i++;
        }
        fileName[i] = '\0';
        fileSize = size;
        creationTime = time;
        next = nullptr;
    }
};
class FileList {
private:
    FileNode* head;
public:
    FileList() : head(nullptr) {}
    // Ham them file theo trinh tu thoi gian
    void addFile(const char* name, unsigned long size, unsigned long time) {
        FileNode* newNode = new FileNode(name, size, time);
        if (!head || head->creationTime > time) {
            newNode->next = head;
            head = newNode;
            return;
        }
        FileNode* current = head;
        while (current->next && current->next->creationTime <= time) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    // Ham tinh kich thuoc cua cac file trong danh sach
    unsigned long calculateTotalSize() {
        unsigned long totalSize = 0;
        FileNode* current = head;
        while (current) {
            totalSize += current->fileSize;
            current = current->next;
        }
        return totalSize;
    }
    // Ham loai bo file co kich thuoc nho de phu hop voi dung luong usb
    void removeFilesForUSB(unsigned long usbSize) {
        while (calculateTotalSize() > usbSize) {
            FileNode* current = head;
            FileNode* smallest = head;
            FileNode* prev = nullptr;
            FileNode* prevSmallest = nullptr;
            while (current->next) {
                if (current->next->fileSize < smallest->fileSize) {
                    prevSmallest = current;
                    smallest = current->next;
                }
                current = current->next;
            }
            if (smallest == head) {
                head = head->next;
            } else if (prevSmallest) {
                prevSmallest->next = smallest->next;
            }
            delete smallest;
        }
    }
    void printList() {
        FileNode* current = head;
        while (current) {
            cout << "Ten file: " << current->fileName << ", Kich thuoc: " 
                 << current->fileSize << " bytes, Thoi gian tao: " << current->creationTime << endl;
            current = current->next;
        }
    }
};
int main() {
    FileList fileList;
    // tao file
    fileList.addFile("file1.txt", 200000000000, 1600);
    fileList.addFile("file2.txt", 500, 2000);
    fileList.addFile("file3.txt", 100, 1500);
    fileList.addFile("file4.txt", 200, 1600);
    fileList.addFile("file5.txt", 500, 2000);
    fileList.addFile("file6.txt", 100, 1500);
    // In danh sach file truoc khi sao luu
    cout << "Danh sach file truoc khi sao luu:\n";
    fileList.printList();
    // Tinh kich thuoc cac file
    unsigned long totalSize = fileList.calculateTotalSize();
    cout << "Tinh kich thuoc cac file: " << totalSize << " bytes\n";
    // Loai bo file dung luong nho sao luu vao USB 32GB 
    unsigned long usbSize = 32 * 1024 * 1024 * 1024;
    fileList.removeFilesForUSB(usbSize);
    // In danh sach file sau khi loai bo
    cout << "\nDanh sach file sau khi loai bo phu hop dung luong USB:\n";
    fileList.printList();
    return 0;
}

