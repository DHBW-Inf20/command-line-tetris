#ifndef HIGHSCORE_H
#define HIGHSCORE_H

void WriteToFile(std::vector<std::string> lines);

std::vector<std::string> GetHighScores();

void ShowHighscore();

void AddHighscore(int score, std::string name);

#endif // HIGHSCORE_H
