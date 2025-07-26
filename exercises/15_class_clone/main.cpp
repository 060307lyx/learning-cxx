#include "../exercise.h"
#include <stdexcept>

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;  // 新增容量成员，用于记录缓存大小

public:
    // 动态设置容量的构造器
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2), capacity(capacity) {
        if (capacity < 2) {
            throw std::invalid_argument("Capacity must be at least 2");
        }
        cache[0] = 0;  // 初始化斐波那契数列第0项
        cache[1] = 1;  // 初始化斐波那契数列第1项
    }

    // 复制构造器（显式弃置，禁止复制）
    DynFibonacci(DynFibonacci const &) = delete;

    // 析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;  // 释放动态分配的数组内存
    }

    // 缓存优化的斐波那契计算（非const版本，可扩展缓存）
    size_t get(int i) {
        if (i < 0) {
            throw std::out_of_range("Index cannot be negative");
        }
        if (i >= capacity) {
            throw std::out_of_range("Index exceeds cache capacity");
        }
        // 计算直到所需索引i（惰性计算）
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // const版本get方法（仅读取，不扩展缓存）
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;  // const对象调用const版本get
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
