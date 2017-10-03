#include "thread_group.hpp"
#include <chrono>
#include <iostream>
#include <sstream>

using namespace std::chrono_literals;

void background_func(std::string const& message) {
    std::stringstream str_s;
    str_s << __func__ << ": " << message << std::endl;
    std::cout << str_s.str();
    std::this_thread::sleep_for(100s);
}

int main() {
    tds::Thread_group thread_group {};
    auto t = thread_group.create_thread(background_func, "Hello, World!");

    std::stringstream str_s;
    str_s << "size == " << thread_group.size() << std::endl;
    std::cout << str_s.str();
    str_s.str("");

    std::this_thread::sleep_for(1s);
    thread_group.remove_thread(t);
    thread_group.join_all();
    str_s << "main: end" << std::endl;
    std::cout << str_s.str();
}
