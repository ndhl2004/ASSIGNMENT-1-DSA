#include <iostream>
#include <string>
using namespace std;
void bubblesort(int arr[],int &h)
{
	int i,j;
	cout <<"Sap xep theo bubble sort:"<<endl;
	for (int i=0; i<h-2;i++)
	{
		for (int j=h-1; j>i;j--)
		{
			if (arr[j]<arr[j-1])
			{
			swap (arr[j],arr[j-1]);
			}
		}
	}
}
void sapxepmang(string arr[],int n){
	int numarr[n];
	for (int i=0;i<n;i++)
	{
		if (arr[i]=="red")
		{
			numarr[i]=0;
		}
		if (arr[i]=="white")
		{
			numarr[i]=1;
		}
		if (arr[i]=="blue")
		{
			numarr[i]=2;
		}
	}
	bubblesort(numarr,n);
	for (int i=0;i<n;i++)
	{
		if (numarr[i]==0)
		{
			arr[i]="red";
		}
		if (numarr[i]==1)
		{
			arr[i]="white";
		}
		if (numarr[i]==2)
		{
			arr[i]="blue";
		}
	}
	}
int main() {
    string arr[] = {"blue", "red", "blue","red","red","white","red","blue","white"};
    int n = sizeof(arr) / sizeof(arr[0]);
    sapxepmang(arr, n);
    for (int i = 0; i < n; i++) {
        cout << arr[i]<<" ";
    }
    return 0;
}

