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
    if (n<0) {
        n=-n;
    }
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

//погрешность d равна (2^e)*((1/2))^(-23)=2^(e-23)
//d==1 при e =2^23
//d>1 при e = 24
//x0 = 2^24

int main() {
    cout<<"sign"<<' '<<"exponent"<<' '<<"mantissa"<<endl;
    float a = 8388608.0;
    float b = 8388609.0;
    float x = 16777216.0;
    bitfloat(a);
    bitfloat(b);
    bitfloat(x);
    bitfloat(x+1);
    return 0;
}