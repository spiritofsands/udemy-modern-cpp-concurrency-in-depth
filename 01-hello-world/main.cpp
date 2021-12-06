#include <iostream>
#include <thread>

void hello()
{
    std::cout << "Hello func: " << std::this_thread::get_id() << std::endl;
}

class CallableClass
{
    public:
        void operator()() const
        {
            std::cout << "Hello callable class: " << std::this_thread::get_id() << std::endl;
        }
};

int main(int argc, char** argv)
{
    std::thread thread1(hello);

    CallableClass callable_object;
    std::thread thread2(callable_object);

    std::thread thread3([]
            { std::cout << "Hello lambda: " << std::this_thread::get_id() << std::endl; });

    thread1.join();
    thread2.join();
    thread3.join();

    std::cout << "Hello main: " << std::this_thread::get_id() << std::endl;
}
