#include "matrix.hpp"
#include <iostream>

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    cout<<"random 3x3 matrix"<<endl;
    matrix<int> m(3,3,0);
    m.randomize();
    m.print();
    cout<<"det = "<<m.det_count()<<endl;
    cout<<endl;

    cout<<"after transpose"<<endl;
    matrix<int> tm = m.transpose();
    tm.print();
    cout<<"det = "<<tm.det_count()<<endl;
    cout<<endl;

    cout<<"random 5x5 matrix with det = 5"<<endl;
    matrix<int> mat1 = getSpecificDeterminant<int>(5,5);
    mat1.print();
    cout<<"det = "<<mat1.det_count()<<endl;
    cout<<endl;

    cout<<"random 50x50 matrix with det = 50"<<endl;
    matrix<int> mat2 = getSpecificDeterminant<int>(50,50);
    mat2.print();
    cout<<"det = "<<mat2.det_count()<<endl;
    cout<<endl;

    cout<<"random 100x100 matrix with det = 100"<<endl;
    matrix<int> mat3 = getSpecificDeterminant<int>(100,100);
    mat3.print();
    cout<<"det = "<<mat3.det_count()<<endl;
    cout<<endl;
    return 0;
}