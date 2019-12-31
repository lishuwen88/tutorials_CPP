#include <iostream>
#include <thread>

void function1(){
	std::cout << "Beauty is only skin-deep\n";
}

int main(){
	std::thread t1(function1); // t1 starts running
	t1.join(); // main thread waits for t1 to finish
	// t1.detach(); // t1 will run freely on its own --deamon process
	// if (t1.joinable())
	// t1.join();

	return 0;
}
