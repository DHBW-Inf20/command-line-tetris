#include "Tile.h"

#include "Color.h"
#include "../../Utilities/MemoryLeakDetection.h"


Tile::Tile(const Color col)
{
	this->color = col;
}

Tile::Tile()
{
	this->color = Color::white;
}

Tile::Tile(const Tile& tile)
{
	this->color = tile.color;
}



Tile* Tile::Clone()
{
	auto* const a = new Tile(*this);
	return a;
}



Color Tile::GetColor() const
{
	return this->color;
}
