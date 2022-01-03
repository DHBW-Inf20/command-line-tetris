#ifndef _tile_
#define _tile_
#include "Tile.cpp"
#endif

#include "../../Utilities/Logger.h"

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
        int currentRow;
        int currentColumn;  
        virtual void rotateRight(){}
      

        /*
            xxxx
            xOxx   <-- Ankerpunkt in der 4x4 Matrix
            xxxx
            xxxx
        */

    public:
        virtual TetrisBlock* clone(TetrisBlock* block) { auto a = new TetrisBlock(*block); return a;};
        bool isColumnEmpty(int column)
        {
            for(int i = 0; i < matrix.size(); i++)
            {
                if(matrix[i][column] != nullptr)
                {
                    return false; // Es gibt ein Element in dieser Spalte
                }
            }
            return true;
        }
        
        bool isRowEmpty(int row)
        {
            for(int i = 0; i < matrix.size(); i++)
            {
                if(matrix[row][i] != nullptr)
                    return false; // Es gibt ein Element in dieser Reihe
            }
            return true;
        }

        bool tryMoveLeft()
        {
            if((currentColumn > 0 && isColumnEmpty(0)) || currentColumn > 1)
            {
                currentColumn--;
                return true;
            }
            return false;
        }     
        
        bool tryMoveRight()
        {
            if((currentColumn < 9 && (isColumnEmpty(3) && isColumnEmpty(2))) || (currentColumn < 8 && isColumnEmpty(3)) || (currentColumn < 7))
            {
                currentColumn++;
                return true;
            }
            return false;
        }

        bool tryMoveDown()
        {
            if((currentRow < rowCount-2 && isRowEmpty(3) && isRowEmpty(2)) || (currentRow < rowCount-3 && isRowEmpty(3)) ||  (currentRow < rowCount-4))
            {
                currentRow++;
                return true;
            }
            return false;
        }

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
            currentRow = 2;
            currentColumn = 5;
        }     
        
        TetrisBlock(const TetrisBlock& block) //Clone Constructor
        {         
            angle = block.angle;
            currentRow = block.currentRow;
            currentColumn = block.currentColumn;
            matrix = block.matrix;
        }        

      
        bool tryRotateRight()
        {         
        
           rotateRight();          
            for(int i=0; i<4;i++)
            {
                for(int j =0; j<4;j++)
                {
                    if(matrix[i][j]!=nullptr)
                    {
                        if(i+currentRow>=rowCount-1||j+currentColumn>=columnCount-1 || i+currentRow<1 || i+currentColumn <1)
                        { 
                            rotateRight(); //Originaldrehung wiederherstellen
                            rotateRight();
                            rotateRight();
                            return false;
                        }
                    }
                }
            }
            return true;     
        }

        std::vector<std::vector<Tile*>> buildMatrix()
        {
            std::vector<std::vector<Tile *>> field = create2DArray<Tile*>(rowCount, columnCount);

            for(int i=0; i<4;i++)
            {
                for(int j =0; j<4;j++)
                {
                    if(i+currentRow<rowCount&&j+currentColumn<columnCount) //Ist der Block ganz am Boden können Teile der Matrix mit Verschiebung außerhalb des Spielfelds sein (diese werden igonoriert)
                    {
                        field[i+currentRow][j+currentColumn] = matrix[i][j]; 
                    }                
                }
            }           
            return field;
        }
        // Erbende Klassen ggf. noch eine Init-Methode, wo die 4x4-Matrix befüllt wird    

};

