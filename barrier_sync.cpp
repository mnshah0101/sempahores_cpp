#include <semaphore>
#include <thread>
#include <vector>
#include <iostream>
#include <chrono>

// (Your existing barrier implementation)
void barrier(int m)
{
    static std::counting_semaphore<> mutex(1);
    static std::counting_semaphore<> wait(0);
    static int count = 0;

    mutex.acquire();
    count = count + 1;

    if (count == m)
    {
        wait.release(); // let one thread through
    }
    mutex.release();

    wait.acquire(); // all threads block here until release
    wait.release(); // allow next waiting thread to proceed
}

int main()
{
    const int num_threads = 5;
    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    for (int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back([i, num_threads]()
                             {
            std::this_thread::sleep_for(std::chrono::milliseconds(100 * i));

            std::cout << "Thread " << i << " reached barrier\n";
            barrier(num_threads);
            std::cout << "Thread " << i << " passed barrier\n"; });
    }

    // join all threads
    for (auto &t : threads)
    {
        t.join();
    }

    return 0;
}
