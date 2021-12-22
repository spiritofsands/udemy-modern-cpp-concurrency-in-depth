#include <iostream>
#include <thread>

void func_1()
{
    std::cout << "Thread 1: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void func_2()
{
    std::cout << "Thread 2: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}


int main(int argc, char** argv)
{
    std::cout << "Main thread: " << std::this_thread::get_id() << std::endl;

    std::thread thread1(func_1);
    std::thread thread2(func_2);

    std::thread thread3 = std::move(thread1);
    thread1 = std::thread(func_2);

    thread1.join();
    thread2.join();
    thread3.join();
}
