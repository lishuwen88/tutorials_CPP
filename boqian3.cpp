#include <iostream>
#include <thread>
#include <string>
#include <mutex>

std::mutex mu;

void shared_print(std::string msg, int id){
	mu.lock();
	std::cout << msg << id << "\n";
	mu.unlock();
}

void function1(){
	for (int i=0; i>-100; i--)
		shared_print(std::string("From t1: "), i);
}

int main(){
	std::thread t1(function1);

	for (int i=0; i<100; i++)
		shared_print(std::string("From main: "), i);

	t1.join();

	return 0;
}
