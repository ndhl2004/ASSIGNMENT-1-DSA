#include <iostream>
#include <math.h>
using namespace std;

bool sangsonguyento(int n) {
    if (n < 2) {
        return false;
    }
    for (int i = 2; i <= sqrt(n); i++) {  
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
void tichtheocap(int arr[], int n, int result[], int &resultSize) {
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            result[index++] = arr[i] * arr[j];
        }
    }
    resultSize = index; 
}
void locBlum(int n, int blum[], int &blumCount) {
    int newarr[100]; 
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (sangsonguyento(i) && i % 4 == 3) {
            newarr[index++] = i;
        }
    }
    blumCount = 0; 
    tichtheocap(newarr, index, blum, blumCount);
}
void checkBlum(int n,int arr[],int M)
{
	bool x = false;
	for (int i=0;i<n;i++)
	{
		if (arr[i]== M)
		{
			cout<< "M co ton tai trong day Blum";
			x = true;
			break;
		}
	} 
	if (!x)
	{
		cout<< "M khong ton tai trong day Blum";
	}
}
int main() {
    int n = 10;
    int M=10;
    int blum[100]; 
    int blumCount; 
    locBlum(n, blum, blumCount);
    checkBlum (n,blum,M);
    return 0;
}

