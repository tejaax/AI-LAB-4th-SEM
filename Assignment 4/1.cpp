#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

vector<string> city = {
    "Chicago","Indianapolis","Columbus","Cleveland","Detroit",
    "Buffalo","Pittsburgh","Baltimore","Philadelphia",
    "New York","Boston","Providence","Syracuse","Portland"
};

int n = 14;
vector<vector<int>> dist(n, vector<int>(n, INF));
vector<vector<int>> adj(n);

class prio_queue {
private:
    pair<int, vector<int>> heap[1000]; 
    int sz = 0;

    bool better(pair<int, vector<int>> a,
                pair<int, vector<int>> b) {
        return a.first < b.first;  
    }

    void siftUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (better(heap[p], heap[i])) break;
            swap(heap[p], heap[i]);
            i = p;
        }
    }

    void siftDown(int i) {
        while (true) {
            int l = 2*i + 1, r = 2*i + 2, best = i;
            if (l < sz && better(heap[l], heap[best])) best = l;
            if (r < sz && better(heap[r], heap[best])) best = r;
            if (best == i) break;
            swap(heap[i], heap[best]);
            i = best;
        }
    }

public:
    void pushNode(int cost, vector<int> path) {
        heap[sz] = {cost, path};
        siftUp(sz);
        sz++;
    }

    pair<int, vector<int>> topNode() {
        return heap[0];
    }

    void popNode() {
        heap[0] = heap[sz - 1];
        sz--;
        siftDown(0);
    }

    bool khaliHai() {
        return sz == 0;
    }
};

void BestFirstSearch(int src, int dest) {
    prio_queue pq;
    vector<bool> checked(n, false); 

    pq.pushNode(0, {src});

    while (!pq.khaliHai()) {
        auto cur = pq.topNode();
        pq.popNode();

        vector<int> path = cur.second;
        int u = path.back();

        if (checked[u]) continue;
        checked[u] = true;

        if (u == dest) {
            cout << "Best First Search Path:\n";
            int total = 0;
            for (int i = 0; i + 1 < path.size(); i++) {
                cout << city[path[i]] << " -> ";
                total += dist[path[i]][path[i+1]];
            }
            cout << city[dest] << "\n";
            cout << "TOTAL COST = " << total << endl;
            return;
        }

        for (int v : adj[u]) {
            if (!checked[v]) {
                auto newPath = path;
                newPath.push_back(v);

                int edgeCost = dist[u][v];  
                pq.pushNode(edgeCost, newPath);
            }
        }
    }

    cout << "No path found\n";
}
int main() {
    for (int i = 0; i < n; i++)
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

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (dist[i][j] != INF && i != j)
                adj[i].push_back(j);

    int src = 12; // Syracuse
    int dest = 0; // Chicago

    BestFirstSearch(src, dest);
    return 0;
}
