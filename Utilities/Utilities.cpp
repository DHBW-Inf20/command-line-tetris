#include "Utilities.h"
 
#include <random>

#include "MemoryLeakDetection.h"

int GetRandomNumberBetween(const int lower, const int upper)
{
    //Will be used to obtain a seed for the random number engine
    std::random_device rd;
    //Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(lower, upper);
    return dis(gen);
}

