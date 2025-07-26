#include "../exercise.h"

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    // 动态设置容量的构造器
    DynFibonacci(int cap) : capacity(cap), cached(2) {
        if (cap < 2) throw std::invalid_argument("Capacity must be at least 2");
        cache = new size_t[cap];
        cache[0] = 0;
        cache[1] = 1;
    }

    // 析构器释放动态内存
    ~DynFibonacci() {
        delete[] cache;
    }

    // 缓存优化的斐波那契计算
    size_t get(int i) {
        if (i >= capacity) {
            throw std::out_of_range("Index exceeds cache capacity");
        }
        
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        
        return cache[i];
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
