// g++ shared_future.cpp -o shared_future -pthread --std=c++17

#include <iostream>
#include <future>
 
int main()
{   
    std::promise<void> main_promise;
    std::shared_future<void> main_future(main_promise.get_future());
 
    auto first_function = [&, main_future]() -> int
    {
        main_future.wait();
        return 1;
    };
 
    auto second_function = [&, main_future]() -> int
    {
        main_future.wait();
        return 2;
    }; 

    auto first_result = std::async(std::launch::async, first_function);
    auto second_result = std::async(std::launch::async, second_function);
 
    main_promise.set_value();
 
    std::cout << first_result.get() << " " << second_result.get() << "\n";
}
