#include <iostream>
#include <thread>

void join_func()
{
    std::cout << "Join func: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Join func: end" << std::endl;
}

void detach_func()
{
    std::cout << "Detach func: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Detach func: end" << std::endl;
}

int main(int argc, char** argv)
{
    std::thread thread1(detach_func);
    thread1.detach();

    std::thread thread2(join_func);
    thread2.join();

    std::cout << "Hello main: " << std::this_thread::get_id() << std::endl;
}
