#include <iostream>
#include <thread>

void test()
{
    std::cout << "Hello test: " << std::this_thread::get_id() << std::endl;
}

void function_a()
{
    std::cout << "Hello func_a: " << std::this_thread::get_id() << std::endl;

    std::thread threadC(test);
    threadC.join();
}

void function_b()
{
    std::cout << "Hello func_b: " << std::this_thread::get_id() << std::endl;
}

int main(int argc, char** argv)
{
    std::thread threadA(function_a);
    std::thread threadB(function_b);

    threadA.join();
    threadB.join();

    std::cout << "Hello main: " << std::this_thread::get_id() << std::endl;
}
