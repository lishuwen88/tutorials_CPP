#include "queue_spsc.h"
#include "queue_mutex.h"
#include <thread>
#include <future>
#include <cstdio>
#include <chrono>
#include <iostream>

const int NumItems = 100000000;

template <typename QueueType>
void producer(QueueType *queue)
{
	for (int i = 0; i < NumItems;) {
		if (queue->push_back(i)) {
			i++;
		}
		else {
			std::this_thread::yield();	
		}
	}
}

template <typename QueueType>
void test_queue()
{
    QueueType queue(4095);

    auto fut = std::async(std::launch::async, producer< QueueType >, &queue);

    for (int expected = 0; expected < NumItems; expected++) {
        int received;
        // Try repeatedly until we get an item
        while (!queue.pop_front(received)) {
            std::this_thread::yield();
        }

        if (received != expected) {
            std::printf("Error: Expected %d, received %d", expected, received);
        }
    }

    fut.wait();
}



int main()
{
    using namespace std::chrono;
    auto t0 = steady_clock::now();
    test_queue< queue_spsc<int> >();
    auto t1 = steady_clock::now();
    test_queue< queue_mutex<int> >();
    auto t2 = steady_clock::now();
    auto d1 = t1 - t0;
    auto d2 = t2 - t1;

    std::cout << "Lockless:" << duration<double, std::milli>(d1).count() << " ms" << std::endl;
    std::cout << "Locking:" << duration<double, std::milli>(d2).count() << " ms" << std::endl;
	return 0;
}
