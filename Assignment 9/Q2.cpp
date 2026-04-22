#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n = 14;

vector<string> city = {
    "Chicago","Indianapolis","Columbus","Cleveland","Detroit",
    "Buffalo","Pittsburgh","Baltimore","Philadelphia",
    "New York","Boston","Providence","Syracuse","Portland"
};

vector<vector<pair<int,int>>> adj(n);

// Alpha-Beta function
int alphaBeta(int curr, int dest, int depth, bool isMax,
              int alpha, int beta, vector<bool>& visited) {

    // If reached destination → leaf node
    if(curr == dest) {
        cout << "Depth " << depth << " | Reached " << city[curr]
             << " → Return 0\n";
        return 0;
    }

    visited[curr] = true;

    if(isMax) {
        int best = -INF;

        cout << "\n[ MAX Node ] City: " << city[curr]
             << " Depth: " << depth
             << " Alpha: " << alpha << " Beta: " << beta << "\n";

        for(auto &p : adj[curr]) {
            int next = p.first;
            int wt = p.second;

            if(!visited[next]) {
                int val = wt + alphaBeta(next, dest, depth+1, false,
                                         alpha, beta, visited);

                best = max(best, val);
                alpha = max(alpha, best);

                cout << "  -> Visiting " << city[next]
                     << " | Cost: " << val
                     << " | Updated Alpha: " << alpha << "\n";

                if(beta <= alpha) {
                    cout << "   PRUNED at " << city[next]
                         << " (Beta <= Alpha)\n";
                    break;
                }
            }
        }

        visited[curr] = false;
        return best;
    }
    else {
        int best = INF;

        cout << "\n[ MIN Node ] City: " << city[curr]
             << " Depth: " << depth
             << " Alpha: " << alpha << " Beta: " << beta << "\n";

        for(auto &p : adj[curr]) {
            int next = p.first;
            int wt = p.second;

            if(!visited[next]) {
                int val = wt + alphaBeta(next, dest, depth+1, true,
                                         alpha, beta, visited);

                best = min(best, val);
                beta = min(beta, best);

                cout << "  -> Visiting " << city[next]
                     << " | Cost: " << val
                     << " | Updated Beta: " << beta << "\n";

                if(beta <= alpha) {
                    cout << "  PRUNED at " << city[next]
                         << " (Beta <= Alpha)\n";
                    break;
                }
            }
        }

        visited[curr] = false;
        return best;
    }
}

int main() {

    vector<vector<int>> dist(n, vector<int>(n, INF));

    for(int i = 0; i < n; i++)
        dist[i][i] = 0;

    dist[0][4] = dist[4][0] = 283;
    dist[0][3] = dist[3][0] = 345;
    dist[0][1] = dist[1][0] = 182;
    dist[1][2] = dist[2][1] = 176;
    dist[2][3] = dist[3][2] = 144;
    dist[2][6] = dist[6][2] = 185;
    dist[3][4] = dist[4][3] = 169;
    dist[3][6] = dist[6][3] = 134;
    dist[3][5] = dist[5][3] = 189;
    dist[4][5] = dist[5][4] = 256;
    dist[5][12] = dist[12][5] = 150;
    dist[5][6] = dist[6][5] = 215;
    dist[6][8] = dist[8][6] = 305;
    dist[6][7] = dist[7][6] = 247;
    dist[7][8] = dist[8][7] = 101;
    dist[8][9] = dist[9][8] = 97;
    dist[8][12] = dist[12][8] = 253;
    dist[9][10] = dist[10][9] = 215;
    dist[9][11] = dist[11][9] = 181;
    dist[10][11] = dist[11][10] = 50;
    dist[10][13] = dist[13][10] = 107;
    dist[12][10] = dist[10][12] = 312;

    // Build adjacency list
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(dist[i][j] != INF && i != j) {
                adj[i].push_back({j, dist[i][j]});
            }
        }
    }

    int src = 12; // Syracuse
    int dest = 0; // Chicago

    vector<bool> visited(n, false);

    cout << "=== Alpha-Beta Pruning Simulation ===\n";

    int result = alphaBeta(src, dest, 0, true, -INF, INF, visited);

    cout << "\n\nFinal Result (Cost) = " << result << endl;

    return 0;
}