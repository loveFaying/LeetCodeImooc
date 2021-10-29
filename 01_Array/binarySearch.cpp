#include <bits/stdc++.h>
using namespace std;

template<typename T>
int binarySearch(T arr[], int n, T target){

    int l = 0, r = n - 1; // 在[l...r]的范围里寻找target
    while(l <= r){    // 当 l == r时,区间[l...r]依然是有效的
        int mid = l + (r - l) / 2;
        if(arr[mid] == target) return mid;
        if(target > arr[mid])
            l = mid + 1;  // target在[mid+1...r]中; [l...mid]一定没有target
        else    // target < arr[mid]
            r = mid - 1;  // target在[l...mid-1]中; [mid...r]一定没有target
    }

    return -1;
}

template<typename T>
int binarySearch2(T arr[], int n, T target){

    int l = 0, r = n; // target在[l...r)的范围里
    while(l < r){    // 当 l == r 时, 区间[l...r)是一个无效区间
        int mid = l + (r - l) / 2;
        if(arr[mid] == target) return mid;
        if(target > arr[mid])
            l = mid + 1;    // target在[mid+1...r)中; [l...mid]一定没有target
        else// target < arr[mid]
            r = mid;        // target在[l...mid)中; [mid...r)一定没有target
    }

    return -1;
}

int main(){
    int n = 20;
    int* arr = new int[n];
    for(int i = 0 ; i < n ; i ++)
        arr[i] = 2*i;

    cout << binarySearch(arr, n, 10) << endl;
    cout << binarySearch(arr, n, 13) << endl;
    cout << binarySearch2(arr, n, 10) << endl;
    cout << binarySearch2(arr, n, 13) << endl;
    return 0;
}