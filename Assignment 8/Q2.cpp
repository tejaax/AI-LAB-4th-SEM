#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

// --- GLOBAL SETTINGS ---
const int N = 8;
const string CITIES[N] = {"A", "B", "C", "D", "E", "F", "G", "H"};

const int COST_MATRIX[N][N] = {
    {0, 10, 15, 20, 25, 30, 35, 40},
    {12, 0, 35, 15, 20, 25, 30, 45},
    {25, 30, 0, 10, 40, 20, 15, 35},
    {18, 25, 12, 0, 15, 30, 20, 10},
    {22, 18, 28, 20, 0, 15, 25, 30},
    {35, 22, 18, 28, 12, 0, 40, 20},
    {30, 35, 22, 18, 28, 32, 0, 15},
    {40, 28, 35, 22, 18, 25, 12, 0}
};

// --- RANDOM GENERATOR ---
mt19937 rng(time(0));

// --- HELPER FUNCTIONS ---

int calculate_cost(const vector<int>& tour) {
    int total = 0;
    for (int i = 0; i < N - 1; i++) {
        total += COST_MATRIX[tour[i]][tour[i+1]];
    }
    total += COST_MATRIX[tour[N-1]][tour[0]];
    return total;
}

bool already_in_tour(const vector<int>& tour, int city) {
    for (int x : tour) {
        if (x == city) return true;
    }
    return false;
}

// Better shuffle using mt19937
vector<int> get_random_tour() {
    vector<int> tour;
    for (int i = 0; i < N; i++) tour.push_back(i);
    shuffle(tour.begin(), tour.end(), rng);
    return tour;
}

// --- SELECTION (Tournament) ---
vector<int> tournament_selection(const vector<vector<int>>& population) {
    int k = 3; // tournament size
    vector<int> best;
    int best_cost = INT_MAX;

    for (int i = 0; i < k; i++) {
        int idx = rng() % population.size();
        int cost = calculate_cost(population[idx]);
        if (cost < best_cost) {
            best_cost = cost;
            best = population[idx];
        }
    }
    return best;
}

// --- CROSSOVER ---
vector<int> crossover(const vector<int>& p1, const vector<int>& p2) {
    int start = rng() % N;
    int end = rng() % N;
    if (start > end) swap(start, end);

    vector<int> child(N, -1);

    // Copy segment from parent1
    for (int i = start; i <= end; i++) {
        child[i] = p1[i];
    }

    // Fill remaining from parent2
    int idx = 0;
    for (int i = 0; i < N; i++) {
        if (!already_in_tour(child, p2[i])) {
            while (child[idx] != -1) idx++;
            child[idx] = p2[i];
        }
    }

    return child;
}

// --- MUTATION ---
void mutate(vector<int>& tour) {
    if ((rng() % 100) < 20) { // 20% mutation
        int i = rng() % N;
        int j = rng() % N;
        swap(tour[i], tour[j]);
    }
}

// --- PRINT TOUR ---
void print_tour(const vector<int>& tour) {
    for (int i : tour) {
        cout << CITIES[i] << " ";
    }
    cout << CITIES[tour[0]]; // return to start
    cout << endl;
}

// --- MAIN GA ---
void run_genetic_algorithm(int generations, int pop_size) {
    vector<vector<int>> population;

    // Initial population
    for (int i = 0; i < pop_size; i++) {
        population.push_back(get_random_tour());
    }

    vector<int> best_tour;
    int best_cost = INT_MAX;

    cout << left << setw(10) << "Gen" << "Best Cost" << endl;
    cout << "----------------------" << endl;

    for (int g = 0; g <= generations; g++) {

        vector<vector<int>> next_gen;

        // --- FIND BEST (ELITISM) ---
        for (auto& tour : population) {
            int cost = calculate_cost(tour);
            if (cost < best_cost) {
                best_cost = cost;
                best_tour = tour;
            }
        }

        // Keep best solution
        next_gen.push_back(best_tour);

        // --- CREATE NEXT GENERATION ---
        while (next_gen.size() < pop_size) {
            vector<int> parent1 = tournament_selection(population);
            vector<int> parent2 = tournament_selection(population);

            vector<int> child = crossover(parent1, parent2);
            mutate(child);

            next_gen.push_back(child);
        }

        population = next_gen;

        if (g % 10 == 0) {
            cout << left << setw(10) << g << best_cost << endl;
        }
    }

    // --- FINAL RESULT ---
    cout << "\nBest Tour Found:\n";
    print_tour(best_tour);
    cout << "Minimum Cost: " << best_cost << endl;
}

// --- MAIN ---
int main() {
    run_genetic_algorithm(100, 50);
    return 0;
}