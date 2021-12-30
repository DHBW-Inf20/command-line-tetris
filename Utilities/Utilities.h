
 #include <vector>
#include <random>
#include <iostream>

 
template <typename T> 
std::vector<std::vector<T>> create2DArray(unsigned height, unsigned width)
{
    return std::vector<std::vector<T>>(height, std::vector<T>(width, 0));
}


//Will be used to obtain a seed for the random number engine
std::random_device rd;
    //Standard mersenne_twister_engine seeded with rd()
std::mt19937 gen(rd());

int GetRandomNumberBetween(int lower, int upper){
    std::uniform_int_distribution<> dis(lower, upper);
    return dis(gen);
}

