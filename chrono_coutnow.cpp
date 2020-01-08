#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

volatile int sink;
int main()
{
	auto timestamp= std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(timestamp);
	std::cout << std::ctime(&t) << "\n";

	auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << "2nd time: " << std::ctime(&tt) << "\n";

	auto t3 = std::time(nullptr);
	std::cout << "3rd time: " << std::put_time(std::localtime(&t3), "%F %T%z")<< "\n";

	auto t4 = std::chrono::system_clock::now();
	std::cout << "4th time" << std::put_time(std::gmtime(&t3), "%F %T") << "\n";

	time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::put_time(std::localtime(&now), "%F %T") <<  "\n";
      
	return 0;

}
