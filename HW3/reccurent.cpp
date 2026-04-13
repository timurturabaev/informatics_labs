#include <iostream>
#include <array>
using namespace std;

template<typename T, size_t n>
struct reccurent {
    array<T, n> coefs;
    array<T, n> initial;
    
    constexpr reccurent(const array<T, n>& c, const array<T, n>& init)
        : coefs(c), initial(init) {}
};

template<typename T, size_t n>
constexpr T get_element(const reccurent<T, n>& rec, size_t k) {
    if (k < n) {
        return rec.initial[k];
    }
    
    T result = 0;
    for (size_t i = 0; i < n; ++i) {
        result += rec.coefs[i] * get_element(rec, k - n + i);
    }
    return result;
}

int main() {
    cout << "Фибоначчи" << endl;
    constexpr array<int, 2> fib_coefs = {1, 1};
    constexpr array<int, 2> fib_initial = {0, 1};
    constexpr reccurent<int, 2> fib(fib_coefs, fib_initial);
    
    cout << "Порядок: 2" << endl;
    cout << "Коэффициенты (a0, a1): 1, 1" << endl;
    cout << "Начальные значения (x0, x1): 0, 1" << endl;
    cout << endl;
    
    constexpr int fib10 = get_element(fib, 10);
    constexpr int fib1 = get_element(fib, 1);
    
    static_assert(fib10 == 55, "Ошибка вычисления Фибоначчи(10)");
    static_assert(fib1 == 1, "Ошибка вычисления Фибоначчи(1)");
    
    cout << "Первые 10 членов:" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << "x" << i << " = " << get_element(fib, i);
        if (i < 9) cout << ", ";
    }
    cout << endl;
    cout << endl;
    
    cout << "Вычисления на этапе компиляции:" << endl;
    cout << "x10 = " << fib10 << " (проверено static_assert)" << endl;
    cout << "x1 = " << fib1 << " (проверено static_assert)" << endl;
    cout << endl;
    cout << endl;
    
    cout << "Трибоначчи" << endl;
    constexpr array<int, 3> trib_coefs = {1, 1, 1};
    constexpr array<int, 3> trib_initial = {0, 0, 1};
    constexpr reccurent<int, 3> rec3(trib_coefs, trib_initial);
    
    cout << "Порядок: 3" << endl;
    cout << "Коэффициенты (a0, a1, a2): 1, 1, 1" << endl;
    cout << "Начальные значения (x0, x1, x2): 0, 0, 1" << endl;
    cout << endl;
    
    constexpr int rec3_10 = get_element(rec3, 10);
    constexpr int rec3_1 = get_element(rec3, 1);
    
    static_assert(rec3_10 == 81, "Ошибка вычисления x10");
    static_assert(rec3_1 == 0, "Ошибка вычисления x1");
    
    cout << "Первые 10 членов:" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << "x" << i << " = " << get_element(rec3, i);
        if (i < 9) cout << ", ";
        if ((i + 1) % 4 == 0 && i < 9) cout << "\n";
    }
    cout << endl;
    cout << endl;
    
    cout << "Вычисления на этапе компиляции:" << endl;
    cout << "x10 = " << rec3_10 << " (проверено static_assert)" << endl;
    cout << "x1 = " << rec3_1 << " (проверено static_assert)" << endl;
    return 0;
}