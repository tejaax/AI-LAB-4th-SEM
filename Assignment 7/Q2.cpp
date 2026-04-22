#include<bits/stdc++.h>
using namespace std;
#define ll long long int

const int N = 8;
mt19937 gen(random_device{}());

// --- HEURISTIC ---
int heuristic(const vector<int>& board) {
    int conflicts = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (board[i] == board[j] || abs(board[i] - board[j]) == abs(i - j)) {
                conflicts++;
            }
        }
    }
    return conflicts;
}

// --- GENERATORS ---
vector<int> random_board() {
    uniform_int_distribution<> dis(0, N - 1);
    vector<int> board(N);
    for (int i = 0; i < N; ++i) board[i] = dis(gen);
    return board;
}

vector<vector<int>> get_neighbors(const vector<int>& board) {
    vector<vector<int>> neighbors;
    for (int col = 0; col < N; ++col) {
        for (int row = 0; row < N; ++row) {
            if (board[col] != row) {
                vector<int> next_board = board;
                next_board[col] = row;
                neighbors.push_back(next_board);
            }
        }
    }
    return neighbors;
}

// --- FIRST CHOICE HILL CLIMBING ---
pair<vector<int>, int> first_choice_hill_climb(vector<int> board) {
    int steps = 0;
    while (true) {
        int current_h = heuristic(board);
        auto neighbors = get_neighbors(board);
        shuffle(neighbors.begin(), neighbors.end(), gen);

        bool found = false;
        for (const auto& n : neighbors) {
            if (heuristic(n) < current_h) {
                board = n;
                steps++;
                found = true;
                break;
            }
        }
        if (!found) return {board, steps};
    }
}

// --- STEEPEST ASCENT (Helper for Random Restart) ---
pair<vector<int>, int> hill_climb(vector<int> board) {
    int steps = 0;
    while (true) {
        auto neighbors = get_neighbors(board);
        vector<int> best = board;
        int best_h = heuristic(board);

        for (const auto& n : neighbors) {
            int h = heuristic(n);
            if (h < best_h) {
                best_h = h;
                best = n;
            }
        }

        if (best_h >= heuristic(board)) return {board, steps};
        board = best;
        steps++;
    }
}

// --- RANDOM RESTART HILL CLIMBING ---
pair<vector<int>, int> random_restart() {
    int total_steps = 0;
    while (true) {
        vector<int> board = random_board();
        auto [result, steps] = hill_climb(board);
        total_steps += steps;
        if (heuristic(result) == 0) return {result, total_steps};
    }
}

// --- SIMULATED ANNEALING ---
pair<vector<int>, int> simulated_annealing(vector<int> board) {
    double T = 100.0;
    int steps = 0;
    uniform_real_distribution<> dis(0.0, 1.0);
    uniform_int_distribution<> neigh_dis(0, (N * (N - 1)) - 1);

    while (T > 0.1) {
        int current_h = heuristic(board);
        if (current_h == 0) return {board, steps};

        auto neighbors = get_neighbors(board);
        vector<int> next_state = neighbors[neigh_dis(gen)];

        int delta = current_h - heuristic(next_state);

        if (delta > 0 || dis(gen) < exp(delta / T)) {
            board = next_state;
        }

        T *= 0.95;
        steps++;
    }
    return {board, steps};
}

// --- EXPERIMENT RUNNER ---
void run_experiment(string name) {
    cout << "\n--- " << name << " ---" << endl;
    int success = 0;

    for (int i = 1; i <= 50; ++i) {
        vector<int> board = random_board();
        int initial_h = heuristic(board);
        vector<int> final_board;
        int steps;

        if (name == "First Choice") {
            auto res = first_choice_hill_climb(board);
            final_board = res.first; steps = res.second;
        } else if (name == "Random Restart") {
            auto res = random_restart();
            final_board = res.first; steps = res.second;
        } else {
            auto res = simulated_annealing(board);
            final_board = res.first; steps = res.second;
        }

        int final_h = heuristic(final_board);
        bool solved = (final_h == 0);
        if (solved) success++;

        cout << setw(2) << i << " | Initial h: " << setw(2) << initial_h 
             << " | Final h: " << setw(2) << final_h 
             << " | Steps: " << setw(4) << steps 
             << " | Result: " << (solved ? "Solved" : "Fail") << endl;
    }
    cout << "Success rate: " << success << " / 50" << endl;
}

int main() {
    run_experiment("First Choice");
    run_experiment("Random Restart");
    run_experiment("Simulated Annealing");
    return 0;
}