#include<bits/stdc++.h>
using namespace std;

// pow2
double pow(double x, int n){

    assert(n >= 0);

    if(n == 0)
        return 1.0;

    double t = pow(x, n / 2);
    if(n % 2)
        return x * t * t;

    return t * t;
}

int main(){

    cout << pow(2,10) << endl;
    return 0;
}