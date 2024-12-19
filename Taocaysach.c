#include <stdio.h>
// Định nghĩa cấu trúc Node
struct Node {
    char title[100];     // Tên chương, mục
    int pages;           // Số trang
    struct Node *child;  // node con
    struct Node *sibling; // node anh em
};
// Hàm tự viết để tính độ dài chuỗi
int tinhdodaichuoi(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}
// Hàm tự viết để sao chép chuỗi
void saochepchuoi(char *a, char *b) {
    int i = 0;
    while (b[i] != '\0') {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';
}
// Tạo node mới
struct Node* taoNode(char *title, int pages) {
    static struct Node nodes[1000]; 
    static int Nodeindex = 0;
    struct Node *newNode = &nodes[Nodeindex++];
    saochepchuoi(newNode->title, title);
    newNode->pages = pages;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}
// Thêm mục con
void themnodecon(struct Node *parent, struct Node *child) {
    if (!parent->child) {
        parent->child = child;
    } else {
        struct Node *temp = parent->child;
        while (temp->sibling) {
            temp = temp->sibling;
        }
        temp->sibling = child;
    }
}
// Đếm số chương
int demsochuong(struct Node *root) {
    int count = 0;
    struct Node *temp = root->child;
    while (temp) {
        count++;
        temp = temp->sibling;
    }
    return count;
}
// Tìm chương dài nhất
struct Node* timchuongdainhat(struct Node *root) {
    struct Node *temp = root->child;
    struct Node *longest = NULL;
    int maxpages = 0;
    while (temp) {
        if (temp->pages > maxpages) {
            maxpages = temp->pages;
            longest = temp;
        }
        temp = temp->sibling;
    }
    return longest;
}
// Tìm và xóa một mục
int timnodevaxoa(struct Node *parent, char *ten) {
    struct Node *current = parent->child;
    struct Node *prev = NULL;
    while (current) {
        int match = 1;
        for (int i = 0; i < tinhdodaichuoi(ten); i++) {
            if (current->title[i] != ten[i]) {
                match = 0;
                break;
            }
        }
        if (match) {
            if (prev) {
                prev->sibling = current->sibling;
            } else {
                parent->child = current->sibling;
            }
            parent->pages -= current->pages;  
            return 1;  
        }
        prev = current;
        current = current->sibling;
    }
    return 0;  
}
// Hiển thị cây
void hienthi(struct Node *node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("- %s (%d pages)\n", node->title, node->pages);
    hienthi(node->child, level + 1);
    hienthi(node->sibling, level);
}
int main() {
    // Tạo node gốc
    struct Node *book = taoNode("MUC LUC", 0);
    // Thêm các node con
    struct Node *chapter1 = taoNode("CHUONG 1: TONG QUAN VE CAU TRUC DU LIEU & GT", 6);
    struct Node *chapter2 = taoNode("CHUONG 2: KY THUAT TIM KIEM (Searching)", 17);
    struct Node *chapter3 = taoNode("CHUONG 3: KY THUAT SAP XEP (SORTING)", 82);
    themnodecon(book, chapter1);
    themnodecon(book, chapter2);
    themnodecon(book, chapter3);
    // Thêm các node cháu
    themnodecon(chapter1, taoNode("1.1. Tam quan trong cua CTDL & GT", 3));
    themnodecon(chapter1, taoNode("1.2. Danh gia Cau truc du lieu & Giai thuat", 3));
    themnodecon(chapter1, taoNode("1.3. Kieu du lieu", 4));
    themnodecon(chapter2, taoNode("2.1. Khai quat ve tim kiem", 8));
    themnodecon(chapter2, taoNode("2.2. Cac giai thuat tim kiem noi", 8));
    themnodecon(chapter2, taoNode("2.3. Cac giai thuat tim kiem ngoai", 14));
    themnodecon(chapter3, taoNode("3.1. Khai quat ve sap xep", 19));
    themnodecon(chapter3, taoNode("3.2. Cac giai thuat sap xep noi", 20));
    themnodecon(chapter3, taoNode("3.3. Cac giai thuat sap xep ngoai", 60));
    // Cấu trúc ban đầu của sách
    printf("Cau truc muc luc ban dau:\n");
    hienthi(book, 0);
    // Xác định số chương của cuốn sách
    printf("\nSo chuong trong sach: %d\n", demsochuong(book));
    // Tìm chương dài nhất của cuốn sách
    struct Node *longest = timchuongdainhat(book);
    if (longest) {
        printf("\nChuong dai nhat: %s (%d trang)\n", longest->title, longest->pages);
    }
    // Tìm một mục và xóa mục đó khỏi sách
    char tenXoa[100] = "2.2. Cac giai thuat tim kiem noi";
    if (timnodevaxoa(chapter2, tenXoa)) {
        printf("\nDa xoa: %s\n", tenXoa);
    } else {
        printf("\nKhong tim thay: %s\n", tenXoa);
    }
    // Mục lục sau khi xóa
    printf("\nCau truc muc luc sau khi xoa:\n");
    hienthi(book, 0);
    return 0;
}