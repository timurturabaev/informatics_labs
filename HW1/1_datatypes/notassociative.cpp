#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float a = 1e23;
    float b = -1e23;
    float c = 1;
    cout<<(a+b)+c<<endl;
    cout<<a+(b+c)<<endl;
}