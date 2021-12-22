#include <iostream>
#include <thread>

void func(const int &x)
{
    while (true)
    {
        std::cout << "Thread X = " << x << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(int argc, char** argv)
{
    int x = 5;
    std::cout << "Main X = " << x << std::endl;

    std::thread thread(func, std::ref(x));
    thread.detach();

    std::this_thread::sleep_for(std::chrono::seconds(5));
    x = 15;
    std::cout << "Main X = " << x << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));
}
