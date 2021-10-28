#include <iostream>

using namespace std;

// O(logn) Time Complexity
int binarySearch(int arr[], int n, int target){

    int l = 0, r = n-1;
    while( l <= r ){
        int mid = l + (r-l)/2;
        if(arr[mid] == target) return mid;
        if(arr[mid] > target) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}

int main(){
    int arr[5] = {3, 5, 9, 10, 16};
    cout << binarySearch(arr, 5, 9) << endl;
    cout << binarySearch(arr, 5, 13) << endl;
    return 0;
}