#include <stdio.h>
#define soluong 100
typedef struct {
    char filename[256];
    int size; 
} Fileinfo;
void bubblesort(Fileinfo file[],int &h)
{
	int i,j;
	for (int i=0; i<h-2;i++)
	{
		for (int j=h-1; j>i;j--)
		{
			if (file[j].size<file[j-1].size)
			{
			Fileinfo doicho = file[j];
            file[j] = file[j - 1];
            file[j - 1] = doicho;
			}
		}
	}
}
int main() {
    int n; 
    printf("Nhap so luong tep: ");
    scanf("%d", &n);
    Fileinfo file[soluong];
    for (int i = 0; i < n; i++) {
        printf("Nhap ten tep %d: ", i + 1);
        scanf("%s", file[i].filename);
        printf("Nhap kich thuoc tep %d: ", i + 1);
        scanf("%d", &file[i].size);
    }
    bubblesort(file, n);
    printf("\nDanh sach tep sau khi sap xep theo kich thuoc tang dan:\n");
    for (int i = 0; i < n; i++) {
        printf("%s : %d bytes\n", file[i].filename, file[i].size);
    }
    return 0;
}
