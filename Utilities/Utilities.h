#ifndef UTILITIES_H
#define UTILITIES_H


#include <vector>


template <typename T>
std::vector<std::vector<T>> Create2DArray(unsigned height, unsigned width)
{
    auto vector = std::vector<std::vector<T>>(height, std::vector<T>(width, 0));
	for(unsigned int i=0; i<vector.size();i++)
	{
		for(unsigned int j=0; j<vector[i].size();j++)
		{
			vector[i][j] = nullptr;
		}
	}
    return vector;
}


int GetRandomNumberBetween(int lower, int upper);



#endif // UTILITIES_H
