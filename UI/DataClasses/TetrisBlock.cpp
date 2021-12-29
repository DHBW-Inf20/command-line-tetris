#ifndef _tile_
#define _tile_
#include "Tile.cpp"
#endif


#ifndef _utilities_
#define _utilities_
#include "../../Utilities/Utilities.h"
#endif



#ifndef _config_
#define _config_
#include "../../UI/Config.cpp"
#endif

class TetrisBlock
{

    protected:
        std::vector<std::vector<Tile*>> matrix; // [Reihe][Spalte] -> [Y][X]
        int angle;
        int anchorPositionX;
        int anchorPositionY;       

    public:
        void moveLeft();      
        

        void moveRight();
        TetrisBlock()
        {
            matrix = create2DArray<Tile*>(4,4);
        }
        virtual void rotateRight()
        {
            
        }
        std::vector<std::vector<Tile*>> buildMatrix()
        {
            std::vector<std::vector<Tile *>> field = create2DArray<Tile*>(dimensionColumn, dimensionRow);

            for(int i=0; i<4;i++)
            {
                for(int j =0; j<4;j++)
                {
                    field[i+anchorPositionX][j+anchorPositionY] = matrix[i][j];                 
                }
            }           
            return field;
        }
        // Erbende Klassen ggf. noch eine Init-Methode, wo die 4x4-Matrix befüllt wird               
};

