#include <iostream>
#include <thread>

static bool s_fin = false;

void DoWork(){
    using namespace std::literals::chrono_literals;
    std::cout << "Started thread id= " << std::this_thread::get_id() << std::endl;

    while (!s_fin){
        std::cout << "Working ... \n" << std::endl;
        std::this_thread::sleep_for(1s);
    }
    
}

int main() {
    // start worker thread
    std::thread worker (DoWork);

    std::cin.get();
    s_fin = true;

    // stop thread/ wait for this thread finish on current thread
    worker.join();

    std::cout << "All Done!!!" << std::endl;
    std::cout << "Started thread id= " << std::this_thread::get_id() << std::endl;

    std::cin.get();
}