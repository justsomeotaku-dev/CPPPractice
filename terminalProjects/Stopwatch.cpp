#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
//https://www.geeksforgeeks.org/cpp/how-to-make-a-countdown-timer-in-cpp/
//https://www.reddit.com/r/dailyprogrammer/comments/pjsdx/difficult_challenge_2/
// very simple functionality, only special thing is threading

std::atomic<bool> running(true); //atomic bool to avoid thread conflict

void stopwatch(){
    int seconds = 0;
    while (running)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        seconds++;
        std::system("cls");
        std::cout << "Stopwatch//Press enter to stop" << std::endl;
        std::cout << seconds;
    }
    
}

int main(int argc, char const *argv[])
{
    std::thread t(stopwatch); // new thread running stopwatch
    std::cin.get();
    running = false;

    t.join(); // wait for thread to finish

    return 0;
}
