#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <climits>
#include <iomanip>
#include <map>
#include <numeric>

using namespace std;

// --- CONFIGURATION ---
// Use constexpr for compile-time constants to avoid "expression must have a constant value"
constexpr int N = 8; 

const string cities[N] = {"A", "B", "C", "D", "E", "F", "G", "H"};

const int cost_matrix[N][N] = {
    {0, 10, 15, 20, 25, 30, 35, 40},
    {12, 0, 35, 15, 20, 25, 30, 45},
    {25, 30, 0, 10, 40, 20, 15, 35},
    {18, 25, 12, 0, 15, 30, 20, 10},
    {22, 18, 28, 20, 0, 15, 25, 30},
    {35, 22, 18, 28, 12, 0, 40, 20},
    {30, 35, 22, 18, 28, 32, 0, 15},
    {40, 28, 35, 22, 18, 25, 12, 0}
};

mt19937 gen(random_device{}());

// --- HELPER FUNCTIONS ---

int calculate_cost(const vector<int>& tour) {
    int total_cost = 0;
    for (int i = 0; i < N - 1; ++i) {
        total_cost += cost_matrix[tour[i]][tour[i+1]];
    }
    total_cost += cost_matrix[tour.back()][tour[0]]; // return to start
    return total_cost;
}

vector<int> random_tour() {
    vector<int> tour(N);
    iota(tour.begin(), tour.end(), 0); 
    shuffle(tour.begin(), tour.end(), gen);
    return tour;
}

vector<vector<int>> generate_neighbors(const vector<int>& tour) {
    vector<vector<int>> neighbors;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            vector<int> next_tour = tour;
            swap(next_tour[i], next_tour[j]);
            neighbors.push_back(next_tour);
        }
    }
    return neighbors;
}

// --- LOCAL BEAM SEARCH ---

int local_beam_search(int k, int max_iterations = 100) {
    cout << "\nRunning Local Beam Search with k = " << k << endl;

    vector<vector<int>> beam;
    for (int i = 0; i < k; ++i) beam.push_back(random_tour());

    int best_overall_cost = INT_MAX;
    vector<int> best_overall_tour;
    int iteration = 0;

    while (iteration < max_iterations) {
        iteration++;
        vector<vector<int>> all_neighbors;

        for (const auto& state : beam) {
            auto neighbors = generate_neighbors(state);
            all_neighbors.insert(all_neighbors.end(), neighbors.begin(), neighbors.end());
        }

        // Sort neighbors by cost (Ascending)
        sort(all_neighbors.begin(), all_neighbors.end(), [](const vector<int>& a, const vector<int>& b) {
            return calculate_cost(a) < calculate_cost(b);
        });

        // Select the top k unique neighbors for the next beam
        beam.clear();
        for (int i = 0; i < (int)all_neighbors.size() && (int)beam.size() < k; ++i) {
            beam.push_back(all_neighbors[i]);
        }

        int current_best_cost = calculate_cost(beam[0]);
        cout << "Iteration " << iteration << " | Best Cost: " << current_best_cost << endl;

        if (current_best_cost < best_overall_cost) {
            best_overall_cost = current_best_cost;
            best_overall_tour = beam[0];
        } else {
            cout << "Converged." << endl;
            break;
        }
    }

    cout << "Final Cost: " << best_overall_cost << endl;
    return best_overall_cost;
}

int main() {
    vector<int> k_values = {3, 5, 10};
    map<int, int> results;

    for (int k : k_values) {
        results[k] = local_beam_search(k);
    }

    // Final Table Output
    cout << "\n" << string(60, '=') << endl;
    cout << left << setw(10) << "k" << setw(20) << "Speed" << "Quality (Cost)" << endl;
    cout << string(60, '-') << endl;
    
    cout << left << setw(10) << "3" << setw(20) << "Fast" << results[3] << endl;
    cout << left << setw(10) << "5" << setw(20) << "Moderate" << results[5] << endl;
    cout << left << setw(10) << "10" << setw(20) << "Slower" << results[10] << endl;

    return 0;
}