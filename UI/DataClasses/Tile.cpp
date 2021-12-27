#ifndef _color_
#define _color_
#include "Color.cpp"
#endif


class Tile
{
    private:
        Color color;
    public:
        Tile(Color col)
        {
            this->color = col;
        }
        Tile(){}
        Color getColor()
        {
            return this->color;
        }
};