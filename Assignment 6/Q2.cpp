#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n = 5;

// 0 = empty
// 1 = obstacle
// 2 = start
// 3 = reward
vector<vector<int>> grid = {
    {2,0,0,0,1},
    {0,1,0,0,3},
    {0,3,0,1,1},
    {0,1,0,0,1},
    {3,0,0,0,3}
};

class prio_queue {
private:
    pair<int, vector<pair<int,int>>> heap[1000];
    int sz = 0;

    bool better(pair<int, vector<pair<int,int>>> a,
                pair<int, vector<pair<int,int>>> b) {
        return a.first < b.first;  // smaller f(n) first
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
    void pushNode(int cost, vector<pair<int,int>> path) {
        heap[sz] = {cost, path};
        siftUp(sz);
        sz++;
    }

    pair<int, vector<pair<int,int>>> topNode() {
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

// Manhattan heuristic to nearest reward
int heuristic(int x, int y, vector<pair<int,int>> rewards) {
    int h = INF;
    for(auto r : rewards) {
        h = min(h, abs(x - r.first) + abs(y - r.second));
    }
    return h;
}

void AStar() {

    prio_queue pq;

    vector<pair<int,int>> rewards;
    pair<int,int> start;

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(grid[i][j] == 2)
                start = {i,j};
            if(grid[i][j] == 3)
                rewards.push_back({i,j});
        }
    }

    vector<pair<int,int>> finalPath;

    pair<int,int> current = start;
    int totalCost = 0;

    while(!rewards.empty()) {

        pq = prio_queue(); // reset pq
        vector<vector<bool>> visited(n, vector<bool>(n,false));

        pq.pushNode(0, {current});

        while(!pq.khaliHai()) {

            auto cur = pq.topNode();
            pq.popNode();

            int f = cur.first;
            vector<pair<int,int>> path = cur.second;
            auto node = path.back();

            int x = node.first;
            int y = node.second;

            if(visited[x][y]) continue;
            visited[x][y] = true;

            // check if reward
            bool found = false;
            for(int i=0;i<rewards.size();i++){
                if(rewards[i] == node){
                    rewards.erase(rewards.begin()+i);
                    found = true;
                    break;
                }
            }

            if(found) {
                totalCost += path.size() - 1;

                for(auto p : path)
                    finalPath.push_back(p);

                current = node;
                break;
            }

            int dx[4] = {-1,1,0,0};
            int dy[4] = {0,0,-1,1};

            for(int k=0;k<4;k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];

                if(nx>=0 && ny>=0 && nx<n && ny<n &&
                   grid[nx][ny] != 1 &&
                   !visited[nx][ny]) {

                    auto newPath = path;
                    newPath.push_back({nx,ny});

                    int g = newPath.size() - 1;
                    int h = heuristic(nx, ny, rewards);
                    int fn = g + h;

                    pq.pushNode(fn, newPath);
                }
            }
        }
    }

    cout << "A* Path Visiting All Rewards:\n";
    for(auto p : finalPath)
        cout << "(" << p.first << "," << p.second << ") -> ";

    cout << "END\n";
    cout << "TOTAL COST = " << totalCost << endl;
}

int main() {
    AStar();
    return 0;
}