#include <iostream>
#include <thread>

void function1(){
	std::cout << "Beauty is only skin-deep\n";
}

class Fctor{
public:
	void operator()(){
		for (int i=0; i>-100; i--){
			std::cout << "from t1 " << i << std::endl;
		}
	}
};

int main(){
	Fctor fct;
	std::thread t1(fct); // t1 start running
	// RAII, wrapper w(t1);	

	// try catch method to join
	try{
		for (int i=0; i<100; i++)
			std::cout << "from main: " << i << std::endl;
	} catch (...){
		t1.join();
		throw;
	}

	t1.join(); // main thread waits for t1 to finish


	return 0;
}
