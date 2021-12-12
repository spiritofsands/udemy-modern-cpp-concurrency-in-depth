#include <iostream>
#include <thread>

// Available commands
enum class Commands {
    Clean = 1,
    FullSpeedAhead = 2,
    Stop = 3,
    Exit = 100,
};

// Be able to print Command int representation
std::ostream& operator<<(std::ostream& stream, const Commands& c)
{
    return stream << static_cast<int>(c);
}

// Be able to read Command int representation
std::istream& operator>>(std::istream& stream, Commands& c)
{
    int command = 0;
    stream >> command;
    c = static_cast<Commands>(command);
    return stream;
}

// Workers functions
void clean_func()
{
    std::cout << "\tCleaners here: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    std::cout << "\tCleaners done" << std::endl;
}

void full_speed_ahead_func()
{
    std::cout << "\tEngine crew here: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    std::cout << "\tFull speed engine!" << std::endl;
}

void stop_func()
{
    std::cout << "\tEngine crew here: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    std::cout << "\tStop engine!" << std::endl;
}

// Captain here
int main(int argc, char** argv)
{
    std::cout << "Captain here: " << std::this_thread::get_id() << std::endl;

    Commands command;

    do
    {
        std::cout << "Input the command: "
            << Commands::Clean << ", "
            << Commands::FullSpeedAhead << ", "
            << Commands::Stop << ", "
            << Commands::Exit << std::endl;

        std::cin >> command;

        switch (command)
        {
            case Commands::Clean:
                {
                    std::thread cleaners(clean_func);
                    cleaners.detach();
                    break;
                }
            case Commands::FullSpeedAhead:
                {
                    std::thread engine_crew(full_speed_ahead_func);
                    engine_crew.join();
                    break;
                }
            case Commands::Stop:
                {
                    std::thread engine_crew(stop_func);
                    engine_crew.join();
                    break;
                }
            case Commands::Exit:
                {
                    break;
                }
            default:
                {
                    std::cout << "Invalid order: " << command << std::endl;
                }
        }
    } while (command != Commands::Exit);

    std::cout << "Captain here: exiting" << std::endl;
}
