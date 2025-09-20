#include <iostream>
#include <thread>
#include <mutex>

std::mutex my_mutex;
int counter = 0;

void increment(const std::string& thread_name) {
    for (int i = 0; i < 5; ++i) {
        my_mutex.lock();  // Manually lock
        ++counter;
        std::cout << thread_name << " incremented counter to " << counter << "\n";
        my_mutex.unlock();  // Manually unlock
    }
}

int main() {
    std::thread t1(increment, "Thread 1");
    std::thread t2(increment, "Thread 2");

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << std::endl;
    return 0;
}

