#include <iostream>
using namespace std;

struct subsubvector {
    int *mas;
    unsigned int top;
    unsigned int capacityacity;
};

bool init(subsubvector* vp) {
    vp->mas = NULL;
    vp->top = 0;
    vp->capacityacity = 0;
    return 1;
}

void destructor(subsubvector* vp) {
    delete[] vp->mas;
    subsubvector v;
    init(vp);
}

bool resize(subsubvector* vp, unsigned int new_capacityacity) {
    int* newmas = new int[new_capacityacity];
    unsigned int top = vp->top;
    for (int i =0;i<vp->top;i++) {
        newmas[i]=vp->mas[i];
    }
    destructor(vp);
    vp->mas = newmas;
    vp->top = top;
    vp->capacityacity = new_capacityacity;
    return 1;
}

bool push_back(subsubvector* vp, int elem) {
    if (vp->top<vp->capacityacity) {
        vp->mas[vp->top++] = elem;
    }
    else {
        resize(vp, 2*vp->capacityacity+1);
        vp->mas[vp->top++] = elem;
    }
    return 1;
}

void shrink_to_fit(subsubvector* vp) {
    int *newmas = new int[vp->top];
    for (int i = 0; i<vp->top; i++)
        newmas[i]=vp->mas[i];
    vp->mas = newmas;
    vp->capacityacity = vp->top;
}

int pop_back(subsubvector* vp) {
    if (vp->top) {
        int x = vp->mas[vp->top-1];
        vp->top-=1;
        return x;
    }
    return 0;
}

void clear(subsubvector* vp) {
    for (int i = 0; i<vp->top; i++)
        vp->mas[i]=0;
    vp->top = 0;
}

int main() 
{
    subsubvector v;
    subsubvector* vp = &v;
    init(vp);
    cout<<v.mas<<' '<<v.top<<' '<<v.capacityacity<<endl;
    for (int i = 0; i<9;i++) {
        push_back(vp,i);
        cout<<v.mas[i]<<' ';
    }
    cout<<endl;
    cout<<v.mas<<' '<<v.top<<' '<<v.capacityacity<<endl;
    cout<<pop_back(vp)<<endl;
    cout<<pop_back(vp)<<endl;
    cout<<pop_back(vp)<<endl;
    cout<<vp->capacityacity<<' '<<vp->top<<endl;
    shrink_to_fit(vp);
    cout<<vp->capacityacity<<' '<<vp->top<<endl;
    destructor(vp);
    return 0;
}