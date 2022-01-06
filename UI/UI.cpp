#include "UI.h"

#include <string>



#include "Config.h"
#include "../Utilities/AnsiEscape.h"


void UI::Draw(const std::vector<std::vector<Tile*>>& field, const int score, const int level) // [Reihe][Spalte])
{          
    clearLine();
    hideCursor();

    for(auto i=0; i<rowCount;i++)
    { 
        for(auto j=0; j<columnCount;j++)
        {                  
            if(field[i][j] != nullptr) // Sicherstellen, dass ein Objekt existiert
            {
                ActualColor = field[i][j]->GetColor();
                switch (ActualColor)
                {
                case Color::yellow:
                    setTextColor(YELLOW_TXT);
                    break;
                case Color::black:
                    setTextColor(BLACK_TXT);
                    break;
                case Color::blue:
                    setTextColor(BLUE_TXT);
                    break;
                case Color::green:
                    setTextColor(GREEN_TXT);
                    break;
                case Color::orange:
                    setTextColor(RED_TXT); // Eigentlich orange, gibt es jedoch nicht bei dem ANSI Zeugs!!! @JDEV
                    break;
                case Color::red:
                    setTextColor(RED_TXT);
                    break;
                case Color::turquoise:
                    setTextColor(CYAN_TXT);
                    break;
                case Color::purple:
                    setTextColor(MAGENTA_TXT);
                    break;
                default:
                    setTextColor(WHITE_TXT);
                    break;
                }
            }     
            else
            {
                setTextColor(WHITE_TXT); // Kein Tile(nullptr) => White
            }               
            moveTo(i+1,(j*2)+1);
            puts("██"); //▉
            moveUp(1);                
        }    
    } 
    AddScoreAndLevel(score, level); // Show Score and Level
    moveTo(0,0);
}

void UI::Clear()
{
    clearScreen();
    restoreConsole();
    moveTo(0,0);
}

void UI::Init(std::vector<std::vector<Tile*>>& field)
{
	clearScreen();


	// Clear Field
	for (auto b = 0; b < rowCount; b++)
	{
		for (auto c = 0; c < columnCount; c++)
		{
			field[b][c] = nullptr;
		}
	}

	for (auto k = 0; k < columnCount; k++)
	{
		// Oben und Unten Rand
		field[0][k] = new Tile(Color::black);
		field[rowCount - 1][k] = new Tile(Color::black);
	}

	// Die obersten zwei Zeilen fehlen, deshalb +1 put
	// Die linkeste Zeile fehlt, deshalb +1 bei put

	for (auto h = 1; h < rowCount - 1; h++)
	{
		// Links und Rechts Rand, [1;21] weil die bei der anderen schon gemacht wurden
		field[h][0] = new Tile(Color::black);
		field[h][columnCount - 1] = new Tile(Color::black);
	}
}

UI::UI()
{
	
}
void UI::AddScoreAndLevel(const int score, const int level) const
{
	const auto strScore = std::to_string(score);
	const auto strLevel = std::to_string(level);
	const auto* chScore = strScore.c_str();
	const auto* chLevel = strLevel.c_str();

    // Berandung Score
    for(auto j = 27; j < 44; j++)
    {
        moveTo(5,j);
        puts("▄");
        moveTo(8,j);
        puts("▀");
    }
    moveTo(6,27);
    puts("█");
    moveTo(7,27);
    puts("█");
    moveTo(6,43);
    puts("█");
    moveTo(7,43);
    puts("█");
    
    // Eintragen Score&Level
    moveTo(6,28);
    puts("Level: ");
    moveTo(6,35);
    puts(chLevel);

    moveTo(7,28);
    puts("Score: ");
    moveTo(7,35);
    puts(chScore);
}
