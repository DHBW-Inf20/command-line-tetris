#ifndef UI_H
#define UI_H


#include "DataClasses/Tile.h"

#include "../Utilities/Utilities.h"


class UI
{
	Color ActualColor;
	void AddScoreAndLevel(int score, int level) const;

public:
	void Draw(const std::vector<std::vector<Tile*>>& field, int score, int level); // [Reihe][Spalte]);

	UI();
	void Clear();
	void Init(std::vector<std::vector<Tile*>>& field);
	/* ~UI() Irgendwie so geht das
	{
	    for(int f = 0; f < 22; f++)
	    {
	        delete [] field[f];
	    }
	    delete [] field;
	} */
};

#endif // UI_H
