#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>

class LogFile {
	std::mutex m_mutex;
	std::ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	} // Need destructor to close file
	void shared_print(std::string id, int value) {
		std::lock_guard<std::mutex> locker(m_mutex);
		f << "From " << id << ": " << value << std::endl;
	}
	// Never leak f to outside world, like this:
	//void processf(void fun(ofstream&)) {
	//	fun(f);
	//}

};

void function1(LogFile& log){
	for (int i=0; i>-100; i--)
		log.shared_print(std::string("From t1: "), i);
}

int main(){
	LogFile log;
	std::thread t1(function1, std::ref(log));

	for (int i=0; i<100; i++)
		log.shared_print(std::string("From main: "), i);

	t1.join();

	return 0;
}
