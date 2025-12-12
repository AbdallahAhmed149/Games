#pragma once
#include "BoardGame_Classes.h"
#include "FourByFourBoard.h"
#include "FourByFourMove.h"

// Renamed from AIPlayer to FourByFour_AI_Player to avoid conflict
class FourByFour_AI_Player : public Player<char> {
public:
    FourByFour_AI_Player(string name, char symbol);
    Move<char>* get_move(Board<char>* b);

private:
    int minimax(FourByFourBoard* board, int depth, bool isMax);
};