#include <bits/stdc++.h>
using namespace std;

double dist_sq(vector<double> a, vector<double> b) {
    return (a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1]);
}

int main() {
    vector<vector<double>> data;
    ifstream file("cities.csv");

    double x, y;
    while (file >> x >> y) {
        data.push_back({x, y});
    }

    int k = 3;
    vector<vector<double>> centers(k);

    // Initial centers
    for (int i = 0; i < k; i++)
        centers[i] = data[i];

    double alpha = 0.1;

    for (int iter = 0; iter < 20; iter++) {
        vector<vector<vector<double>>> clusters(k);

        // Assign cities
        for (auto &p : data) {
            int idx = 0;
            double best = 1e18;

            for (int i = 0; i < k; i++) {
                double d = dist_sq(p, centers[i]);
                if (d < best) {
                    best = d;
                    idx = i;
                }
            }
            clusters[idx].push_back(p);
        }

        // Update centers (Gradient Descent)
        for (int i = 0; i < k; i++) {
            if (clusters[i].empty()) continue;

            double gx = 0, gy = 0;

            for (auto &p : clusters[i]) {
                gx += (centers[i][0] - p[0]);
                gy += (centers[i][1] - p[1]);
            }

            gx *= 2;
            gy *= 2;

            centers[i][0] -= alpha * gx / clusters[i].size();
            centers[i][1] -= alpha * gy / clusters[i].size();
        }
    }

    // Output
    cout << "Gradient Descent Centers:\n";
    for (auto &c : centers)
        cout << c[0] << " " << c[1] << endl;

    // Compute SSD
    double ssd = 0;
    for (auto &p : data) {
        double best = 1e18;
        for (int i = 0; i < k; i++) {
            best = min(best, dist_sq(p, centers[i]));
        }
        ssd += best;
    }

    cout << "SSD (GD): " << ssd << endl;

    return 0;
}