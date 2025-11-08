#include <iostream>
#include <cmath>
using namespace std;

void bitint(int n) {
    for (int i=31;i>=0;i--)
        cout<<((n>>i)&1);
        cout<<endl;
}

int main() {
    bitint(7);
    bitint(-7);
    bitint(7+(-7));
    int x = 2147483647;
    cout<<x+1<<endl;
    bitint(x+1);
    bitint(-2147483648);
    return 0;
}
