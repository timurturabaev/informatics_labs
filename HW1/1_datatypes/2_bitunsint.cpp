#include <iostream>
#include <cmath>
using namespace std;

void unsignedbitint(unsigned int n) {
    for (int i=31;i>=0;i--)
        cout<<((n>>i)&1);
        cout<<endl;
}

int main() {
    unsignedbitint(17);
    unsignedbitint(-17);
    unsignedbitint(2147483648);
    unsigned int x = 0;
    cout<<x-1<<endl;
    unsignedbitint(x-1);
    return 0;
}
