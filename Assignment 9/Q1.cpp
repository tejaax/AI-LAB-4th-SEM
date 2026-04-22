#include <bits/stdc++.h>
using namespace std;

#define HUMAN 'O'
#define AI 'X'
#define EMPTY '_'

int nodes = 0;

// Print board
void printBoard(vector<vector<char>> &board) {
    for (auto &row : board) {
        for (auto &cell : row) cout << cell << " ";
        cout << endl;
    }
    cout << "-----------\n";
}

// Evaluate board
int evaluate(vector<vector<char>> &b) {
    for (int i = 0; i < 3; i++) {
        if (b[i][0] == b[i][1] && b[i][1] == b[i][2]) {
            if (b[i][0] == AI) return 10;
            if (b[i][0] == HUMAN) return -10;
        }
        if (b[0][i] == b[1][i] && b[1][i] == b[2][i]) {
            if (b[0][i] == AI) return 10;
            if (b[0][i] == HUMAN) return -10;
        }
    }

    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == AI) return 10;
        if (b[0][0] == HUMAN) return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == AI) return 10;
        if (b[0][2] == HUMAN) return -10;
    }

    return 0;
}

bool isMovesLeft(vector<vector<char>> &board) {
    for (auto &row : board)
        for (auto &cell : row)
            if (cell == EMPTY) return true;
    return false;
}

// Minimax with tree printing
int minimax(vector<vector<char>> &board, bool isMax, int depth) {
    nodes++;

    int score = evaluate(board);

    // Print node (visualization)
    cout << string(depth * 2, ' ') << "Depth " << depth 
         << " | Score: " << score << endl;

    if (score == 10 || score == -10) return score;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = -1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    best = max(best, minimax(board, false, depth + 1));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = 1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    best = min(best, minimax(board, true, depth + 1));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

// Find best move
pair<int,int> findBestMove(vector<vector<char>> &board) {
    int bestVal = -1000;
    pair<int,int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;

                int moveVal = minimax(board, false, 0);

                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main() {
    vector<vector<char>> board = {
        { 'X', 'O', 'X' },
        { 'O', 'O', '_' },
        { '_', '_', 'X' }
    };

    cout << "Initial Board:\n";
    printBoard(board);

    nodes = 0;
    pair<int,int> bestMove = findBestMove(board);

    cout << "\nBest Move (Minimax): (" 
         << bestMove.first << ", " << bestMove.second << ")\n";

    cout << "Total Nodes Explored: " << nodes << endl;

    return 0;
}