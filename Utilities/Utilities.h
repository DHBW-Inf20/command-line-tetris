
 #include <vector>
 
template <typename T> 
std::vector<std::vector<T>> create2DArray(unsigned height, unsigned width)
{
    return std::vector<std::vector<T>>(height, std::vector<T>(width, 0));
}