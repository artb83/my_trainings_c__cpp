#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

class SpinLock {
private:
    std::atomic<bool> flag;

public:
    SpinLock() : flag(false) {}

    void lock() {
        bool expected = false;
        while (!flag.compare_exchange_strong(expected, true)) {
            expected = false;
        }
    }

    void unlock() {
        flag.store(false);
    }
};

//class CASLock {
//private:
//    std::atomic<int> flag;
//
//public:
//    CASLock() : flag(0) {}
//
//    void lock() {
//        int expected = 0;
//        while (!flag.compare_exchange_strong(expected, 1)) {
//            expected = 0; // Reset expected as it gets modified by compare_exchange_strong
//        }
//    }
//
//    void unlock() {
//        flag.store(0);
//    }
//};

//Load-Linked and Store-Conditional lock - used on MIPS, ARM and PowerPC platforms
//class LLSCLock {
//private:
//    std::atomic<int> flag;
//
//public:
//    LLSCLock() : flag(0) {}
//
//    void lock() {
//        while (true) {
//            int expected = 0;
//            // Load-Linked equivalent: load the value
//            if (flag.load(std::memory_order_relaxed) == expected) {
//                // Store-Conditional equivalent: attempt to store a new value
//                if (flag.compare_exchange_strong(expected, 1)) {
//                    break; // Break if SC succeeds
//                }
//            }
//        }
//    }
//
//    void unlock() {
//        flag.store(0, std::memory_order_relaxed);
//    }
//};

void criticalSection(int threadID, SpinLock& spinLock) {
    std::cout << "Thread " << threadID << " attempting to acquire lock..." << std::endl;
    spinLock.lock();
    std::cout << "Thread " << threadID << " has acquired lock." << std::endl;
    std::cout << "Thread " << threadID << " is in critical section." << std::endl;
    spinLock.unlock();
    std::cout << "Thread " << threadID << " has released lock." << std::endl;
}

//void criticalSection(int threadID, CASLock& casLock) {
//    std::cout << "Thread " << threadID << " attempting to acquire lock..." << std::endl;
//    casLock.lock();
//    std::cout << "Thread " << threadID << " has acquired lock." << std::endl;
//    std::cout << "Thread " << threadID << " is in critical section." << std::endl;
//    casLock.unlock();
//    std::cout << "Thread " << threadID << " has released lock." << std::endl;
//}

//void criticalSection(int threadID, LLSCLock& llscLock) {
//    std::cout << "Thread " << threadID << " attempting to acquire lock..." << std::endl;
//    llscLock.lock();
//    std::cout << "Thread " << threadID << " has acquired lock." << std::endl;
//    std::cout << "Thread " << threadID << " is in critical section." << std::endl;
//    llscLock.unlock();
//    std::cout << "Thread " << threadID << " has released lock." << std::endl;
//}

int main() {
    const int numThreads = 5;
    SpinLock spinLock;
    //CASLock casLock;
    //LLSCLock llscLock;

    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(criticalSection, i, std::ref(spinLock));
        //threads.emplace_back(criticalSection, i, std::ref(casLock));
        //threads.emplace_back(criticalSection, i, std::ref(llscLock));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}