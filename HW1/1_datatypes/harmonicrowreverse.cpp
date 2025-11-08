#include <iostream>
#include <cmath>
using namespace std;

void h() {
    int k = 1;
    float s = 0;
    float ns = s+1.0/k;
    while (ns!=s) {
        k+=1;
        s=ns;
        ns=s+1.0/k; 
    }
    cout<<s<<endl<<ns<<endl<<k;
}

void hreverse() {
    int k = 2097152*2;
    float s = 0;
    while (k>0) {
        s+=1.0/k; 
        k-=1;
    }
    cout<<s<<endl;
}

int main() {
    hreverse();
    h();
    return 0;
}