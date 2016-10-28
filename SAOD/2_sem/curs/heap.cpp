#include <iostream>
#include <algorithm>
#define NMAX 8
using namespace std;
int arr[NMAX+1];

void Heap(int l, int r) {
	int j = 2*l, t, buf;
    while (j+1 < r) {
        t = j+1;
        if ((t+1)<r && arr[t+1]>=arr[t])
        {
            t++;
        }
        if (arr[l]<arr[t]) {
            buf = arr[l];
            arr[l] = arr[t];
            arr[t] = buf;
            l = t;
            j = 2*l;
        } 
        else break;
    }
}

void heap_sort(int R)
{
    int r = R, buf;
    for (int l=r/2; l>=0; l--)
    {
        Heap(l, r);
    }
    while(r>0)
    {
        buf = arr[0];
        arr[0] = arr[r-1];
        arr[r-1] = buf;
        r--;
        Heap(0,r);
    }
}

int main()
{

    int n;
    cin>>n;
    for(int i = 0; i < n; i ++)
    {
        cin>> arr[i];
    }
    heap_sort(n);
    for(int i = 0; i < n; i ++)
    {
        cout <<  arr[i]<<endl;
    }
    system("PAUSE");
    return 0;
}
