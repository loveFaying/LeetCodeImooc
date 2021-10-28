#include <bits/stdc++.h>
using namespace std;

// O(sqrt(n)) Time Complexity
bool isPrime(int num){

    for(int x = 2 ; x * x <= num ; x ++ )
        if( num % x == 0 )
            return false;
    return true;
}

bool isPrime2(int num){

    if( num <= 1 ) return false;
    if( num == 2 ) return true;
    if( num % 2 == 0 ) return false;

    for(int x = 3 ; x * x <= num ; x += 2)
        if( num%x == 0 )
            return false;

    return true;
}

int main(){
    cout << isPrime(11) << endl;
    cout << isPrime2(12) << endl;
    return 0;
}