#include <bits/stdc++.h>
using namespace std;

// O(NlogN)
void __merge(int arr[], int l, int mid, int r, int aux[]){

    for(int i = l ; i <= r ; i ++)
        aux[i] = arr[i];

    int i = l, j = mid + 1;
    for( int k = l ; k <= r; k ++ ){

        if(i > mid)   { arr[k] = aux[j]; j ++;}
        else if(j > r){ arr[k] = aux[i]; i ++;}
        else if(aux[i] < aux[j]){ arr[k] = aux[i]; i ++;}
        else          { arr[k] = aux[j]; j ++;}
    }
}

void mergeSort( int arr[], int n ){

    int *aux = new int[n];
    for(int i = 0 ; i < n ; i ++)
        aux[i] = arr[i];

    for(int sz = 1; sz < n ; sz += sz)
        for(int i = 0 ; i < n ; i += sz+sz)
            __merge(arr, i, i + sz - 1, min(i + sz + sz - 1, n - 1), aux);

    delete[] aux;

    return;
}

// O(n^2) Time Complexity
void selectionSort(int arr[], int n){

    for(int i = 0 ; i < n ; i ++){
        int minIndex = i;
        for( int j = i + 1 ; j < n ; j ++ )
            if( arr[j] < arr[minIndex] )
                minIndex = j;

        swap( arr[i] , arr[minIndex] );
    }
}

int main(){
    int arr[] = {4,1,9,2,10,3,5,6,8,11,23};
    int n = sizeof(arr) / sizeof(int);
    selectionSort(arr, n);
    for(int i = 0 ; i < n ; i ++)
        cout << arr[i] << " ";
    cout << endl;

    int arr1[] = {4,1,9,2,10,3,5,6,8,11,23};
    n = sizeof(arr1) / sizeof(int);
    mergeSort(arr1, n);
    for(int i = 0 ; i < n ; i ++)
        cout << arr1[i] << " ";
    cout << endl;

    return 0;
}