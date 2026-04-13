#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <random>
using namespace std;

template<typename RandomAccessIterator, typename Compare>
void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    auto size = distance(first, last);
    if (size <= 1) return;
    
    auto mid = first + size / 2;
    
    sort(first, mid, comp);
    sort(mid, last, comp);
    
    vector<typename iterator_traits<RandomAccessIterator>::value_type> buffer;
    buffer.reserve(size);
    
    auto left = first;
    auto right = mid;
    
    while (left != mid && right != last) {
        if (comp(*left, *right)) {
            buffer.push_back(move(*left));
            ++left;
        } else {
            buffer.push_back(move(*right));
            ++right;
        }
    }
    
    while (left != mid) {
        buffer.push_back(move(*left));
        ++left;
    }
    while (right != last) {
        buffer.push_back(move(*right));
        ++right;
    }
    
    move(buffer.begin(), buffer.end(), first);
}

int main() {
    cout << "тестовый массив:" << "3 1 4 1 5" << endl;
    cout << endl;
    cout << "разные компараторы" << endl;
    
    vector<int> v = {3, 1, 4, 1, 5};
    
    vector<int> v1 = v;
    sort(v1.begin(), v1.end(), [](int a, int b) { return a < b; });
    cout << "по возрастанию: ";
    for (int x : v1) cout << x << " ";
    cout << endl;
    
    vector<int> v2 = v;
    sort(v2.begin(), v2.end(), [](int a, int b) { return a > b; });
    cout << "по убыванию: ";
    for (int x : v2) cout << x << " ";
    cout << endl;
    
    cout << endl << "разные контейнеры" << endl;
    
    vector<int> vec = {3, 1, 4, 1, 5};
    sort(vec.begin(), vec.end(), [](int a, int b) { return a < b; });
    cout << "vector: ";
    for (int x : vec) cout << x << " ";
    cout << endl;
    
    deque<int> deq = {3, 1, 4, 1, 5};
    sort(deq.begin(), deq.end(), [](int a, int b) { return a < b; });
    cout << "deque: ";
    for (int x : deq) cout << x << " ";
    cout << endl;
    
    int arr[] = {3, 1, 4, 1, 5};
    sort(arr, arr + 5, [](int a, int b) { return a < b; });
    cout << "массив: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    cout << endl << "сравнение скорости vector vs deque" << endl;
    
    const int N = 100000;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, N);
    
    vector<int> v_data(N);
    deque<int> d_data(N);
    for (int i = 0; i < N; i++) {
        int val = dis(gen);
        v_data[i] = val;
        d_data[i] = val;
    }
    
    auto start = chrono::high_resolution_clock::now();
    sort(v_data.begin(), v_data.end(), [](int a, int b) { return a < b; });
    auto end = chrono::high_resolution_clock::now();
    auto v_time = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    start = chrono::high_resolution_clock::now();
    sort(d_data.begin(), d_data.end(), [](int a, int b) { return a < b; });
    end = chrono::high_resolution_clock::now();
    auto d_time = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "vector: " << v_time.count() << " ms" << endl;
    cout << "deque:  " << d_time.count() << " ms" << endl;
    
    return 0;
}