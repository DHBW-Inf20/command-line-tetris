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
        int anchorPositionX;    // Spalte
        int anchorPositionY;    // Reihe

    public:
        void moveLeft();      
        

        void moveRight();
        TetrisBlock()
        {
            matrix = create2DArray<Tile*>(4,4);
            /* 
                0 1 2 3 4 5 6 7 8 9 10 11
              0 W N N N M M M M N N N  W
              1 W N N N M A M M N N N  W
              2 W N N N M M M M N N N  W
              3 W N N N M M M M N N N  W
              4 W N N N N N N N N N N  W
             */
            anchorPositionX = 5;
            anchorPositionY = 1;
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

