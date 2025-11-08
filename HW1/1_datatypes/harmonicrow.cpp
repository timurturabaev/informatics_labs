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
    cout<<s<<endl<<k;
}
int main() {
    h();
    return 0;
}