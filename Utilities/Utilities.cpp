#include "Utilities.h"
 
#include <random>

#include "MemoryLeakDetection.h"

/* Gibt eine Zufallszahl in zwei Grenzen zurück */
int GetRandomNumberBetween(const int lower, const int upper)
{
    //Will be used to obtain a seed for the random number engine
    std::random_device rd;
    //Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(lower, upper);
    return dis(gen);
}


void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}