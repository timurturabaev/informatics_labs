bool init(subvector *vp) {
    vp->mas = nullptr;
    vp->top = 0;
    vp->capacity = 0;
    return true;
}

void destructor(subvector *vp) {
    delete[] vp->mas;
    init(vp);
}

void clear(subvector *vp) {
    vp->top = 0;
}

bool resize(subvector *vp, unsigned int new_capacity) {
    int* new_mas = new int[new_capacity];
    
    if (new_mas == nullptr && new_capacity > 0) {
        return false;
    }
    
    unsigned int elements_to_copy = 0;
    if (new_capacity > vp->top) {
        elements_to_copy = vp->top;
    } else {
        elements_to_copy = new_capacity;
    }

    for (int i = 0; i < elements_to_copy; i++) {
        new_mas[i] = vp->mas[i];
    }

    delete[] vp->mas;

    vp->mas = new_mas;
    vp->capacity = new_capacity;
    vp->top = elements_to_copy;

    return true;
}

bool push_back(subvector *vp, int d) {
    if (vp->top >= vp->capacity) {
        unsigned int new_capacity = (vp->capacity == 0) ? 1 : vp->capacity * 2;
        if (!resize(vp, new_capacity)) {
            return false;
        }
    }
    
    vp->mas[vp->top] = d;
    vp->top++;
    
    return true;
}

int pop_back(subvector *vp) {
    if (vp->top == 0) {
        return 0;
    }
    
    vp->top--; 
    return vp->mas[vp->top];
}

void shrink_to_fit(subvector *vp) {
    if (vp->top < vp->capacity) {
        resize(vp, vp->top);
    }
}