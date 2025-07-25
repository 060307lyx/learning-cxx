#include "../exercise.h"

// TODO: 改正函数实现，实现正确的缓存优化斐波那契计算
// THINk: 这个函数是一个纯函数（pure function）吗？
// READ: 纯函数 <https://zh.wikipedia.org/wiki/%E7%BA%AF%E5%87%BD%E6%95%B0>
static unsigned long long fibonacci(int i) {
    // 初始化缓存的前两个值为斐波那契数列的前两项
    static unsigned long long cache[96] = {0, 1};
    // 记录当前已缓存的斐波那契值数量（初始为2，因为前两个值已初始化）
    static int cached = 2;
    
    // 若需要计算的i大于已缓存的最大值，则扩展缓存
    for (; cached <= i; ++cached) {
        cache[cached] = cache[cached - 1] + cache[cached - 2];
    }
    
    return cache[i];
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT(fibonacci(0) == 0, "fibonacci(0) should be 0");
    ASSERT(fibonacci(1) == 1, "fibonacci(1) should be 1");
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(3) == 2, "fibonacci(3) should be 2");
    ASSERT(fibonacci(10) == 55, "fibonacci(10) should be 55");

    auto fib90 = fibonacci(90);
    std::cout << "fibonacci(90) = " << fib90 << std::endl;
    ASSERT(fib90 == 2880067194370816120, "fibonacci(90) should be 2880067194370816120");
    return 0;
}
