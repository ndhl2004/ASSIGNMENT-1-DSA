#include <stdio.h>
#define MAX 8
int adjMatrix[MAX][MAX] = {0}; 
char vertices[MAX] = {'a', 'b', 'c', 'd', 'e', 'g', 'h'}; 
int visited[MAX]; 
// Ham tim chi so cua mot dinh trong danh sach dinh
int getIndex(char vertex) {
    for (int i = 0; i < MAX; i++) {
        if (vertices[i] == vertex) return i;
    }
    return -1;
}
// Ham them canh vao do thi
void addEdge(char u, char v) {
    int i = getIndex(u);
    int j = getIndex(v);
    if (i != -1 && j != -1) {
        adjMatrix[i][j] = 1;
        adjMatrix[j][i] = 1; 
    }
}
// Ham duyet BFS
void BFS(char start) {
    int queue[MAX]; 
    int front = 0, rear = 0; 
    for (int i = 0; i < MAX; i++) visited[i] = 0; 
    int startIndex = getIndex(start);
    if (startIndex == -1) return;
    queue[rear++] = startIndex;
    visited[startIndex] = 1;
    printf("BFS: ");
    while (front < rear) {
        int current = queue[front++];
        printf("%c ", vertices[current]);
        for (int i = 0; i < MAX; i++) {
            if (adjMatrix[current][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}
int main() {
    addEdge('a', 'b');
    addEdge('a', 'c');
    addEdge('b', 'd');
    addEdge('c', 'e');
    addEdge('d', 'f');
    addEdge('e', 'g');
    addEdge('f', 'h');
    BFS('a');
    return 0;
}
