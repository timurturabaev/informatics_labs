#include <iostream>
using namespace std;

struct subvector {
    int *mas;
    unsigned int top;
    unsigned int capacity;
};

bool init(subvector* vp) {
    vp->mas = NULL;
    vp->top = 0;
    vp->capacity = 0;
    return 1;
}

void destructor(subvector* vp) {
    delete[] vp->mas;
    subvector v;
    init(vp);
}

bool resize(subvector* vp, unsigned int new_capacity) {
    int* newmas = new int[new_capacity];
    unsigned int top = vp->top;
    for (int i =0;i<vp->top;i++) {
        newmas[i]=vp->mas[i];
    }
    destructor(vp);
    vp->mas = newmas;
    vp->top = top;
    vp->capacity = new_capacity;
    return 1;
}

bool push_back(subvector* vp, int elem) {
    if (vp->top<vp->capacity) {
        vp->mas[vp->top++] = elem;
    }
    else {
        resize(vp, 2*vp->capacity+1);
        vp->mas[vp->top++] = elem;
    }
    return 1;
}

void shrink_to_fit(subvector* vp) {
    int *newmas = new int[vp->top];
    for (int i = 0; i<vp->top; i++)
        newmas[i]=vp->mas[i];
    vp->mas = newmas;
    vp->capacity = vp->top;
}

int pop_back(subvector* vp) {
    if (vp->top) {
        int x = vp->mas[vp->top-1];
        vp->top-=1;
        return x;
    }
    return 0;
}

void clear(subvector* vp) {
    for (int i = 0; i<vp->top; i++)
        vp->mas[i]=0;
    vp->top = 0;
}

int main() 
{
    subvector v;
    subvector* vp = &v;
    init(vp);
    cout<<v.mas<<' '<<v.top<<' '<<v.capacity<<endl;
    for (int i = 0; i<9;i++) {
        push_back(vp,i);
        cout<<v.mas[i]<<' ';
    }
    cout<<endl;
    cout<<v.mas<<' '<<v.top<<' '<<v.capacity<<endl;
    cout<<pop_back(vp)<<endl;
    cout<<pop_back(vp)<<endl;
    cout<<pop_back(vp)<<endl;
    cout<<vp->capacity<<' '<<vp->top<<endl;
    shrink_to_fit(vp);
    cout<<vp->capacity<<' '<<vp->top<<endl;
    destructor(vp);
    return 0;
}