#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include <atomic>

#include <shared_mutex>

#include "../UI/DataClasses/TetrisBlock.h"


#include "../UI/UI.h"

class GameController
{
private:
    std::atomic<bool> GameRunning = false;
    TetrisBlock* CurrentBlock{};
    TetrisBlock* CurrentBlockLastUpdate{}; // Hier wird der Block vom letzten Update gespeichert -> So kann bei einer Aenderung das Spielfeld rekonstruiert werden
    std::vector<std::vector<Tile*>> Field;
    UI Ui;
    float BlocksSpawned[7]{};
    bool TryInsertCurrentBlockInField();
    void CreateBlock();
    bool CheckCanMove(TetrisBlock* block, char direction) const;
    void CheckRows();
    void DeleteRow(int row);
    mutable std::mutex MainLock;
    int WaitingTime[11] = { 18, 16, 15, 13, 11, 10, 8, 7, 5, 4, 3 };

    int MoveDownLimiter;
    bool IsSpawningBalanced(int number);
    bool CanDelete{};
    int Level{};
    int Score{};
    int RowsCleared{};
    void Finish();

public:
    GameController();
    bool IsGameRunning() const;
    void Update();
    void Start();
    void BKeyPressed();
    void DownKeyPressed() const;
    void LeftKeyPressed() const;
    void UpKeyPressed() const;
    void RightKeyPressed() const;
    void EnterKeyPressed() const;
    void Stop();
    int GetScore() const;
    int GetLevel() const;

    ~GameController();
};


#endif // GAMECONTROLLER_H