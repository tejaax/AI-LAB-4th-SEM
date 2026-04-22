#include<bits/stdc++.h>
using namespace std;
#define ll long long int

const int N = 8;

// Struct to store simulation results
struct Result {
    int initial_h;
    int final_h;
    int steps;
    bool solved;
};

// Function to generate a random board
vector<int> random_board(mt19937& gen) {
    uniform_int_distribution<> dis(0, N - 1);
    vector<int> board(N);
    for (int i = 0; i < N; ++i) {
        board[i] = dis(gen);
    }
    return board;
}

// Heuristic function: counts pairs of queens attacking each other
int heuristic(const vector<int>& state) {
    int h = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            // Same row
            if (state[i] == state[j]) {
                h++;
            }
            // Same diagonal
            if (abs(state[i] - state[j]) == abs(i - j)) {
                h++;
            }
        }
    }
    return h;
}

// Steepest Hill Climbing Algorithm
Result steepest_hill_climbing(vector<int> current) {
    int steps = 0;
    int init_h = heuristic(current);

    while (true) {
        int h_current = heuristic(current);
        if (h_current == 0) return {init_h, 0, steps, true};

        vector<int> best_neigh = current;
        int best_h = h_current;

        // Explore all neighbors
        for (int col = 0; col < N; ++col) {
            int original_row = current[col];
            for (int row = 0; row < N; ++row) {
                if (row == original_row) continue;

                vector<int> neighbor = current;
                neighbor[col] = row;
                int h_neigh = heuristic(neighbor);

                if (h_neigh < best_h) {
                    best_h = h_neigh;
                    best_neigh = neighbor;
                }
            }
        }

        // If no improvement can be made, we are at a local optimum
        if (best_h >= h_current) {
            return {init_h, h_current, steps, false};
        }

        current = best_neigh;
        steps++;
    }
}

int main() {
    // Seed for randomness
    random_device rd;
    mt19937 gen(rd());

    vector<Result> results;
    int solved_count = 0;

    // Run 50 simulations
    for (int i = 0; i < 50; ++i) {
        vector<int> board = random_board(gen);
        Result res = steepest_hill_climbing(board);
        results.push_back(res);
        if (res.solved) solved_count++;
    }

    // Print Results Header
    cout << setw(10) << "Initial h" << setw(10) << "Final h" 
         << setw(10) << "Steps" << setw(10) << "Solved" << endl;
    cout << string(40, '-') << endl;

    // Print each row
    for (const auto& r : results) {
        cout << setw(10) << r.initial_h 
             << setw(10) << r.final_h 
             << setw(10) << r.steps 
             << setw(10) << (r.solved ? "True" : "False") << endl;
    }

    cout << "\nSolved: " << solved_count << " / 50" << endl;

    return 0;
}