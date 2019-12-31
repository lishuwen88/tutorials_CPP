#include <iostream>
#include <thread>
#include <string>

void function1(){
	std::cout << "Beauty is only skin-deep\n";
}

class Fctor{
public:
	void operator()(std::string msg){
		std::cout << "t1 says: " << msg << "\n";
	}
};

int main(){
	std::string s = "Where there is some bullshit";
	Fctor fct;
	std::thread t1(fct,s); // t1 start running
	// RAII, wrapper w(t1);	

	// try catch method to join
	try{
		std::cout << "from main: " << s << std::endl;
	} catch (...){
		t1.join();
		throw;
	}

	t1.join(); // main thread waits for t1 to finish
	
	std::cout << "hardware con: " << std::thread::hardware_concurrency()<< std::endl;

	return 0;
}
