#include <iostream>
#include <cmath>
using namespace std;

void bitint(int n) {
    for (int i=7;i>=0;i--)
        cout<<((n>>i)&1);
}

void bitfloat(float n) {
    cout<<int(n<0)<<' ';
    int e=0;
    while (n<1) {
        e-=1;
        n*=2;
    }
    while (n>2) {
        e+=1;
        n/=2;
    }
    bitint(e);
    cout<<' ';
    float d = 1.0;
    for (int i=0; i<23; i++) {
        if (n-d>=0) {
            cout<<1;
            n-=d;
        }
        else {
            cout<<0;
        }
        d/=2;
    }
    cout<<endl;
}

int main() {
    cout<<"sign"<<' '<<"exponent"<<' '<<"mantissa"<<endl;
    bitfloat(0.25);
    return 0;
}