#include "PyramidBoard.h"

PyramidBoard::PyramidBoard() : Board<char>(3, 5) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 5; ++j)
            board[i][j] = ' '; // Invalid spots

    // Valid spots
    board[0][2] = '.';
    board[1][1] = board[1][2] = board[1][3] = '.';
    for (int j = 0; j < 5; ++j)
        board[2][j] = '.';
}

bool PyramidBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 5) return false;
    // We can only move if the spot is a valid empty spot ('.')
    if (board[x][y] != '.') return false;

    board[x][y] = s;
    n_moves++;
    return true;
}

// Added Implementation
void PyramidBoard::undo_move(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    if (x >= 0 && x < 3 && y >= 0 && y < 5) {
        board[x][y] = '.';
        n_moves--;
    }
}

// Added Implementation
char PyramidBoard::get_cell(int r, int c) const {
    if (r >= 0 && r < 3 && c >= 0 && c < 5)
        return board[r][c];
    return ' ';
}

bool PyramidBoard::is_win(Player<char>* p) {
    char s = p->get_symbol();

    // Check bottom row horizontal
    for (int j = 0; j <= 2; ++j)
        if (board[2][j] == s && board[2][j + 1] == s && board[2][j + 2] == s)
            return true;

    // Center vertical
    if (board[0][2] == s && board[1][2] == s && board[2][2] == s)
        return true;

    // Diagonals
    if (board[0][2] == s && board[1][1] == s && board[2][0] == s)
        return true;

    if (board[2][0] == s && board[1][2] == s && board[0][2] == s) // This looks redundant or specific shape check?
        return true;

    if (board[2][4] == s && board[1][3] == s && board[0][2] == s)
        return true;

    return false;
}

bool PyramidBoard::is_lose(Player<char>*) { return false; }
bool PyramidBoard::is_draw(Player<char>*) { return n_moves == 9; }
bool PyramidBoard::game_is_over(Player<char>* p) { return is_win(p) || is_draw(p); }