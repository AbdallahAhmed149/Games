#include "TTC5_UI.h"
#include "AIPlayer3.h" // Include the AI header
#include <iostream>
using namespace std;

TTC5_UI::TTC5_UI() : UI("Welcome to 5x5 Tic Tac Toe!", 3) {}

// Fix: Return the Smart AI player
Player<char>* TTC5_UI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::COMPUTER || type == PlayerType::AI) {
        return new TTC5_AI_Player(name, symbol, PlayerType::AI);
    }
    return new Player<char>(name, symbol, type);
}

Move<char>* TTC5_UI::get_move(Player<char>* player) {
    // If it's the Smart AI
    TTC5_AI_Player* aiPtr = dynamic_cast<TTC5_AI_Player*>(player);
    if (aiPtr) {
        TTC5_Board* board = dynamic_cast<TTC5_Board*>(player->get_board_ptr());
        pair<int, int> bestMove = aiPtr->calculate_best_move(*board);
        return new Move<char>(bestMove.first, bestMove.second, player->get_symbol());
    }

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << "), enter your move:\n";
        int x = get_coordinate("Enter row (0-4): ");
        int y = get_coordinate("Enter column (0-4): ");
        return new Move<char>(x, y, player->get_symbol());
    }
    else {
        // Fallback for random computer if cast fails
        int x, y;
        Board<char>* board = player->get_board_ptr();
        auto board_matrix = board->get_board_matrix();
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (board_matrix[x][y] != ' ');
        cout << "Computer (" << player->get_symbol() << ") plays at (" << x << ", " << y << ")\n";
        return new Move<char>(x, y, player->get_symbol());
    }
}

int TTC5_UI::get_coordinate(const string& prompt) {
    int coord;
    while (true) {
        cout << prompt;
        cin >> coord;
        if (coord >= 0 && coord <= 4) {
            return coord;
        }
        cout << "Invalid input! Please enter a number between 0 and 4.\n";
    }
}