#include <bits/stdc++.h>
using namespace std;



int main(){

    int arr[] = {1,3,5,6,7,10,13,15,19,20,30,50};
    int n = sizeof(arr)/sizeof(int);
    cout << binarySearch(arr, n, 3) << endl;
    cout << binarySearch(arr, n, 32) << endl;
    return 0;
}