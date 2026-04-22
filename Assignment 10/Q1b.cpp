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

        // Update centers (Newton Method)
        for (int i = 0; i < k; i++) {
            if (clusters[i].empty()) continue;

            double gx = 0, gy = 0;

            for (auto &p : clusters[i]) {
                gx += (centers[i][0] - p[0]);
                gy += (centers[i][1] - p[1]);
            }

            gx *= 2;
            gy *= 2;

            // Divide by Hessian (which is 2)
            centers[i][0] -= gx / (2 * clusters[i].size());
            centers[i][1] -= gy / (2 * clusters[i].size());
        }
    }

    // Output
    cout << "Newton Method Centers:\n";
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

    cout << "SSD (Newton): " << ssd << endl;

    return 0;
}