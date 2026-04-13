#include "vector.hpp"
#include <iostream>

using namespace std;

using vector = subvector<int>;

int main() {
    vector sv{};
    sv.resize(5);
    cout<<sv.top<<sv.capacity<<endl;
    for (int i = 0; i<8; i++)
        sv.push_back(i);
    for (int i = 0; i<8; i++)
        cout<<sv.mas[i]<<' ';
    cout<<endl;
    cout<<sv.top<<sv.capacity<<endl;
    sv.resize(3);
    for (int i = 0; i<sv.top; i++)
        cout<<sv.mas[i]<<' ';
    cout<<endl;
    cout<<sv.top<<sv.capacity<<endl;
    cout<<sv.pop_back()<<endl;
    cout<<sv.top<<sv.capacity<<endl;
    sv.resize(5);
    cout<<sv.top<<sv.capacity<<endl;
    sv.shrink_to_fit();
    cout<<sv.top<<sv.capacity<<endl;
    sv.clear();
    for (int i = 0; i<sv.top; i++)
        cout<<sv.mas[i]<<' ';
    cout<<endl;
    cout<<sv.top<<sv.capacity<<endl;
    return 0;
}