#include <stdio.h>
// Cấu trúc của một node trong cây AVL
typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;
#define MAX_NODES 100
AVLNode nodes[MAX_NODES];
int demnode = 0;
// Hàm tạo một node mới
AVLNode* taonode(int key) {
    if (demnode >= MAX_NODES) {
        printf("Bo nho da day!\n");
        return NULL;
    }
    AVLNode* node = &nodes[demnode++];
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}
// Hàm lấy chiều cao của một node
int tinhchieucao(AVLNode* node) {
    return node ? node->height : 0;
}
// Hàm tính cân bằng của một node
int tinhcanbang(AVLNode* node) {
    return node ? tinhchieucao(node->left) - tinhchieucao(node->right) : 0;
}
// Hàm xoay phải
AVLNode* xoayphai(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + (tinhchieucao(y->left) > tinhchieucao(y->right) ? tinhchieucao(y->left) : tinhchieucao(y->right));
    x->height = 1 + (tinhchieucao(x->left) > tinhchieucao(x->right) ? tinhchieucao(x->left) : tinhchieucao(x->right));
    return x;
}
// Hàm xoay trái
AVLNode* xoaytrai(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + (tinhchieucao(x->left) > tinhchieucao(x->right) ? tinhchieucao(x->left) : tinhchieucao(x->right));
    y->height = 1 + (tinhchieucao(y->left) > tinhchieucao(y->right) ? tinhchieucao(y->left) : tinhchieucao(y->right));
    return y;
}
// Hàm thêm một node vào cây AVL
AVLNode* chenthemnut(AVLNode* node, int key) {
    if (!node) return taonode(key);
    if (key < node->key)
        node->left = chenthemnut(node->left, key);
    else if (key > node->key)
        node->right = chenthemnut(node->right, key);
    else
        return node;
    node->height = 1 + (tinhchieucao(node->left) > tinhchieucao(node->right) ? tinhchieucao(node->left) : tinhchieucao(node->right));
    int balance = tinhcanbang(node);
    if (balance > 1 && key < node->left->key)
        return xoayphai(node);
    if (balance < -1 && key > node->right->key)
        return xoaytrai(node);
    if (balance > 1 && key > node->left->key) {
        node->left = xoaytrai(node->left);
        return xoayphai(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = xoayphai(node->right);
        return xoaytrai(node);
    }
    return node;
}
// Hàm duyệt root -> left -> right
void duyettruoc(AVLNode* root) {
    if (root) {
        printf("%d ", root->key);
        duyettruoc(root->left);
        duyettruoc(root->right);
    }
}
// Hàm duyệt left -> root -> right
void duyetgiua(AVLNode* root) {
    if (root) {
        duyetgiua(root->left);
        printf("%d ", root->key);
        duyetgiua(root->right);
    }
}
// Hàm duyệt left -> right -> root
void duyetsau(AVLNode* root) {
    if (root) {
        duyetsau(root->left);
        duyetsau(root->right);
        printf("%d ", root->key);
    }
}
int main() {
    int keys[] = {240,73,101,21,13,25,11,37,89,30,15,51};
    int n = sizeof(keys) / sizeof(keys[0]);
    AVLNode* root = NULL;
    printf("Qua trinh them cac phan tu vao cay AVL:\n");
    for (int i = 0; i < n; i++) {
        root = chenthemnut(root, keys[i]);
        printf("Sau khi them %d:\n", keys[i]);
        printf("Duyet goc trai phai: ");
        duyettruoc(root);
        printf("\n");
        printf("Duyet trai goc phai: ");
        duyetgiua(root);
        printf("\n");
        printf("Duyet trai phai goc: ");
        duyetsau(root);
        printf("\n\n");
    }
    return 0;
}