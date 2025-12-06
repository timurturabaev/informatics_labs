#include<iostream>
#include<cstdlib>
#include<cmath>

using namespace std;
template<typename T>
class subvector
{
public:
    T *mas;
    unsigned int top;
    unsigned int capacity;
    
    subvector() {
        top = 0;
        capacity = 0;
        mas = nullptr;
    }

    subvector(unsigned int size) {
        top = size;
        capacity = size;
        if (size>0)
            mas = new T[size];
        else
            mas = nullptr;
    }
    
    ~subvector() {
        delete[] mas;
    }
    
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

// Тут ещё должен быть второй оператор, который будет работать на чтение для константных векторов
// Иначе есть переменная с типом subvector будет аннотирвана const, то этот оператор будет не доступен
    T& operator[](unsigned int index) {
        return mas[index];
    }
};


template<typename T>
class matrix {
    subvector<T> data;
    unsigned cols, rows;

public:
    matrix(unsigned r, unsigned c, T value) {
        cols = c;
        rows = r;
        // А вот это очень плохой тон. Из класса матрицы лезем в поля другого класса, которые почему-то ещё и публичные.
        // А если этот класс писал другой человек, то про его внутреннее устройство вообще ничего не понятно.
        // Формально здесь реализована логика конструктора для вектора. Тогда было бы правильным решением сделать такой контнструктор
        // от размера и заданного значения
        data.mas = new T[r*c];
        for (int i = 0; i<r*c; i++)  
            data.push_back(value);         // использование push_back без использования resize перед ним -- это очень долго, потому что каждый раз происходит перевыделение памяти
        data.shrink_to_fit();
    }

    void randomize() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int sign = (rand()%2==0) ? 1 : -1;
                (*this)(i,j) = T(sign*rand()%100);
            }  
        }  
    }
    
    static matrix Identity(unsigned n) {
        matrix m(n, n, 0);
        for (int i = 0; i < n; i++) {
            m(i,i) = 1;
        }
        return m;
    }
    
    matrix submatrix(unsigned r, unsigned c) {
        unsigned n = rows;
        matrix m(rows - 1, cols - 1, 0);
        int ri = 0;
        for (int i = 0; i < rows; i++) {
            if (i == r) continue;
            int rj = 0;
            for (int j = 0; j < cols; j++) {
                if (j == c) continue;
                m(ri, rj) = (*this)(i, j);
                rj++;
            }
            ri++;
        }
        return m;
    }

    // Два метода транспонирования делают фактически одно и то же. Можно реализовать один через другой.
    matrix& transpose() {
        for (int i = 0; i < rows; i++) {
            for (int j = i + 1; j < cols; j++) {
                T temp = (*this)(i, j);
                (*this)(i, j) = (*this)(j, i);
                (*this)(j, i) = temp;
            }
        }
        return *this;
    }

    matrix transpose() const {
        matrix tm(cols, rows, 0);
        unsigned n = rows;
        for (int i = 0; i < rows; i++) {
            for (int j = i + 1; j < cols; j++) {
                tm(j, i) = (*this)(i, j);
            }
        }
        return tm;
    }

    T operator()(unsigned r, unsigned c) const {
        return data[r*cols+c];
    }

    T& operator()(unsigned r, unsigned c) {
        return data[r*cols+c];
    }

    void print() {
        if (rows == 0 || cols == 0 || data.mas == nullptr)
            return;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout<<(*this)(i, j)<<' ';
            }
            cout<<endl;
        }
    }

    void mulrow(unsigned r, T a) {
        for (int i = 0; i<cols; i++) {
            (*this)(r, i)*=a;
        }
    }

    void divrow(unsigned r, T a) {
        for (int i = 0; i<cols; i++) {
            (*this)(r, i)/=a;
        }
    }

    void sumrows(unsigned r, unsigned q, T a){
        for (int i = 0; i<cols; i++) {
            (*this)(r, i)+=(*this)(q, i)*a;
        }
    }

    T det_count() {
        unsigned n = rows;
        matrix<T> temp = *this;
        T det = 1;
        for (unsigned k = 0; k < n; k++) {
            unsigned p = k;
            // Было бы хорошо передавать эту 1е-10 как аргумент tolerance в функцию. 
            // Тогда мы могли бы считать детерминант с настраиваемой точностью.
            while (p < n && abs(temp(p, k)) < 1e-10) {
                p++;
            }
            // FYI: тут можно выбирать не первый попавшийся ненулевой элемент, а максимальный по модулю
            if (p == n) {
                return 0;
            }
            if (p != k) {
                // Перестановку строк можно было бы тоже вынести в отдельный метод
                for (unsigned j = 0; j < n; j++) {
                    T pmet = temp(k, j);
                    temp(k, j) = temp(p, j);
                    temp(p, j) = pmet;
                }
                det = -det;
            }
            T pvalue = temp(k, k);
            det *= pvalue;
            temp.divrow(k, pvalue);
            for (unsigned i = k + 1; i < n; i++) {
                T div = temp(i, k)/temp(k,k);
                temp.sumrows(i, k, -div);
            }
        }
        return det;
    }
};

template<typename T>
matrix<T> getSpecificDeterminant(unsigned n, T det) {
    matrix<T> u(n,n,0);
    matrix<T> l(n,n,0);
    matrix<T> m(n,n,0);
    for (int i = 0; i<n; i++) {
        for (int j = i+1; j<n; j++) {
            u(i, j) = rand()%10;
            l(j, i) = rand()%10;
        }
        u(i,i) = 1;
        l(i,i) = 1;
    }
    // FYI: в умножении матриц последние два цикла лучше поменят местами :-)
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            for (int k = 0; k<n; k++) {
                m(i, j)+=l(i,k)*u(k,j);
            }
        }
    }
    for (int i = 0; i<n; i++) {
        m(0,i)*=det;
    }
    return m;
}

//второй способ генерирует флоаты, не очень удобно
template<typename T>
matrix<T> getSpecificDeterminant_second(unsigned n, T det) {
    matrix<T> m(n,n,0);
    m.randomize();
    T d = m.det_count();
    if (d==0) {
        for (int i = 0; i<n; i++) {
            if (m(i,i)==0)
                m(i,i)+=T(1);
        }
    }
    if (det != T(0) && abs(d) > 1e-10) {
        if (det/d<0) {
            for (int i = 0; i<n; i++)
                m(i, 0)*=-1;
        }
        T l = pow(abs(det/d), 1.0/n);
        for (int i = 0; i<n; i++) {
            for (int j = 0; j<n; j++)
                m(i, j)*=l;
        }
    }
    return m;
}

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
