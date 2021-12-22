#include <iostream>
#include <thread>
#include <queue>

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
void cleaners_func(const bool &done_flag, std::queue<Commands> &clean_queue)
{
    std::cout << "\tCleaners here: " << std::this_thread::get_id() << std::endl;
    while (!done_flag)
    {
        if (!clean_queue.empty())
        {
            auto command = clean_queue.front();
            if (command == Commands::Clean)
            {
                std::cout << "\tCleaning" << std::endl;
            } else {
                // in case of wrong command in the queue
                std::cout << "\tUnknown command for cleaners: " << command << std::endl;
            }

            clean_queue.pop();
            std::cout << "\tCleaners done" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } else {
            std::cout << "\tNothing to clean" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}

void engine_crew_func(const bool &done_flag, std::queue<Commands> &engine_queue)
{
    std::cout << "\tEngine crew here: " << std::this_thread::get_id() << std::endl;
    while (!done_flag)
    {
        if (!engine_queue.empty())
        {
            auto command = engine_queue.front();
            if (command == Commands::FullSpeedAhead)
            {
                std::cout << "\tFull speed engine!" << std::endl;
            } else if (command == Commands::Stop) {
                std::cout << "\tStop engine!" << std::endl;
            } else {
                // in case of wrong command in the queue
                std::cout << "\tUnknown command for engine crew: " << command << std::endl;
            }

            engine_queue.pop();
            std::cout << "\tEngine crew done" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } else {
            std::cout << "\tNothing to do with engine" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}

// Captain here
int main(int argc, char** argv)
{
    std::cout << "Captain here: " << std::this_thread::get_id() << std::endl;

    Commands command;
    // threads will stop if this flag is set
    bool done_flag = false;
    std::queue<Commands> clean_queue, engine_queue;

    // threads receive the flag and command queue
    std::thread cleaners(cleaners_func, std::ref(done_flag), std::ref(clean_queue));
    std::thread engine_crew(engine_crew_func, std::ref(done_flag), std::ref(engine_queue));

    cleaners.detach();
    engine_crew.detach();

    // get the commands
    do
    {
        std::cout << "Input the command: "
            << Commands::Clean << ", "
            << Commands::FullSpeedAhead << ", "
            << Commands::Stop << ", "
            << Commands::Exit << std::endl;

        std::cin >> command;

        if (command == Commands::Clean)
        {
            clean_queue.push(command);
        } else if (command == Commands::FullSpeedAhead || command == Commands::Stop) {
            engine_queue.push(command);
        } else if (command == Commands::Exit) {
            done_flag = true;
            break;
        } else {
            std::cout << "Invalid order: " << command << std::endl;
        }
    } while (command != Commands::Exit);

    std::cout << "Captain here: exiting" << std::endl;
}
