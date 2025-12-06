#include<iostream>
using namespace std;
template<typename T>
class subvector
{
public:
    T *mas;
    unsigned int top;
    unsigned int capacity;

    // Список инициализации лучше
    subvector() {
        top = 0;
        capacity = 0;
        mas = nullptr;
    }
    
    ~subvector() {
        delete[] mas;
    }
    // Список инициализации
    subvector(const subvector& other) {
        top = other.top;
        capacity = other.capacity;
        if (capacity > 0) {
            mas = new T[capacity];
            for (int i = 0; i < top; ++i)
                mas[i] = other.mas[i];
        } 
        else 
            mas = nullptr;
    }
    
    subvector& operator=(const subvector& other) {
        if (this == &other) {
            return *this;
        }
        delete[] mas;
        top = other.top;
        capacity = other.capacity;
        if (capacity > 0) {
            mas = new T[capacity];
            for (int i = 0; i < top; i++) {
                mas[i] = other.mas[i];
            }
        } else {
            mas = nullptr;
        }
        return *this;
    }

    // Список инициализации
    subvector(subvector&& other) {
        mas = other.mas;
        top = other.top;
        capacity = other.capacity;
        other.mas = nullptr;
        other.top = 0;
        other.capacity = 0;
    }
    
    subvector& operator=(subvector&& other) {
        if (this != &other) {
            delete[] mas;
            mas = other.mas;
            top = other.top;
            capacity = other.capacity;
            other.mas = nullptr;
            other.top = 0;
            other.capacity = 0;
        }
        return *this;
    }
    
    bool resize(unsigned int newcapacity) {
        if (newcapacity == 0) {
            delete[] mas;
            mas = nullptr;
            top = 0;
            capacity = 0;
            return true;
        }
        
        T* newmas = new T[newcapacity];
        unsigned int size = (top < newcapacity) ? top : newcapacity;
        
        for (int i = 0; i < size; i++)
            newmas[i] = mas[i];
            
        delete[] mas;
        mas = newmas;
        capacity = newcapacity;
        top = size;
        return true;
    }
    
    bool push_back(const T& d) {
        if (top >= capacity) {
            unsigned int new_capacity = (capacity == 0) ? 1 : capacity * 2;
            resize(new_capacity);
        }
        mas[top] = d;
        top++;
        return true;
    }
    
    T pop_back() {
        if (top == 0)
            return T{};
        T d = mas[top-1];
        top--;
        return d;
    }
    
    void shrink_to_fit() {
        if (top < capacity) {
            resize(top);
        }
    }
    
    void clear() {
        top = 0;
    }
};

using vector = subvector<int>;

// Профайлер не проверялся?
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
