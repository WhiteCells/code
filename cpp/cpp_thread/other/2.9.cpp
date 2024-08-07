#include <thread>
#include <iostream>
#include <vector>
#include <numeric>

// 分块累加
template<typename Iterator, typename T>
struct accumulate_block {
    void operator()(Iterator first, Iterator last, T &result) {
        result = std::accumulate(first, last, result);
    }
};

// 并行累加
template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    // 迭代器之间的距离
    const unsigned long length = std::distance(first, last);

    if (!length) {
        return init;
    }

    // 
    const unsigned long min_per_thread = 25;
    // 启动线程的最大值
    const unsigned long max_threads = (length + min_per_thread - 1) / min_per_thread;
    // 硬件支持的线程数
    const unsigned long hardware_threads = std::thread::hardware_concurrency();
    // 启动的线程的数量
    // std::thread::hardware_concurrency() 返回 0 时，选择一个合适的启动线程数量
    const unsigned long num_threads = std::min(hardware_threads != 0 \
                                               ? hardware_threads : 2, max_threads);
    // (范围中的元素值 / 启动的线程的数量) = 分块的大小
    const unsigned long block_size = length / num_threads;

    // 存放分块的计算的结果
    std::vector<T> result(num_threads);
    // 启动之前已有一个主线程，所以启动的线程必须比 num_threads 少 1
    std::vector<std::thread> threads(num_threads - 1);

    // 分块的开始迭代器
    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
        Iterator block_end = block_start;
        // 更新分块的结束迭代器
        std::advance(block_end, block_size);
        threads[i] = std::thread(
            accumulate_block<Iterator, T>(),
            block_start,
            block_end,
            std::ref(result[i])
        );
        // 更新分块的开始迭代器
        block_start = block_end;
    }
    // 处理最后一个分块的结果
    accumulate_block<Iterator, T>()(
        block_start,
        last,
        result[num_threads - 1]);

    for (auto &thread : threads) {
        thread.join();
    }

    return std::accumulate(result.begin(), result.end(), init);
};

int main(int argc, char *argv[]) {
    std::vector<int> v;

    for (int i = 1; i < 1000000; ++i) {
        v.push_back(i);
    }

    auto start = std::chrono::high_resolution_clock::now();
    auto res = std::accumulate(v.begin(), v.end(), 0);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << diff.count() << std::endl;
    std::cout << res << std::endl;

    start = std::chrono::high_resolution_clock::now();
    res = parallel_accumulate(v.begin(), v.end(), 0);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << diff.count() << std::endl;
    std::cout << res << std::endl;
    return 0;
}