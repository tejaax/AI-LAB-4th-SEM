#include <bits/stdc++.h>
using namespace std;

struct Node {
    int x, y;
    int h; 
};

class prio_queue {
    vector<Node> heap;

public:
    bool empty() {
        return heap.empty();
    }

    void push(Node n) {
        heap.push_back(n);
        int i = heap.size() - 1;

        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap[parent].h <= heap[i].h)
                break;
            swap(heap[parent], heap[i]);
            i = parent;
        }
    }

    Node pop() {
        Node root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        int i = 0;
        int size = heap.size();

        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < size && heap[left].h < heap[smallest].h)
                smallest = left;
            if (right < size && heap[right].h < heap[smallest].h)
                smallest = right;

            if (smallest == i)
                break;

            swap(heap[i], heap[smallest]);
            i = smallest;
        }
        return root;
    }
};

int heuristic(int x, int y, int gx, int gy) {
    return abs(x - gx) + abs(y - gy); 
}

int main() {

    vector<vector<int>> grid = {
        {1,1,1,1,1,1,1,1,1},
        {1,0,0,1,0,0,0,0,1},
        {1,1,0,1,1,0,1,1,1},
        {1,0,0,0,0,0,0,0,1},
        {1,1,0,1,1,0,1,0,1},
        {1,1,0,1,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1}
    };

    int rows = grid.size();
    int cols = grid[0].size();
    int sx = 5, sy = 2;   // Entry
    int gx = 3, gy = 7;   // Exit

    prio_queue pq;
    vector<vector<bool>> checked(rows, vector<bool>(cols, false));
    vector<vector<pair<int,int>>> parent(rows,vector<pair<int,int>>(cols, {-1,-1}));

    pq.push({sx, sy, heuristic(sx, sy, gx, gy)});
    checked[sx][sy] = true;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (!pq.empty()) {
        Node curr = pq.pop();

        if (curr.x == gx && curr.y == gy) {
            cout << "Exit reached\n";
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < rows && ny < cols) {
                if (!checked[nx][ny] && grid[nx][ny] == 0) {
                    checked[nx][ny] = true;
                    parent[nx][ny] = {curr.x, curr.y};
                    pq.push({nx, ny,heuristic(nx, ny, gx, gy)});
                }
            }
        }
    }

    vector<pair<int,int>> path;
    int x = gx, y = gy;

    while (!(x == sx && y == sy)) {
        path.push_back({x, y});
        auto p = parent[x][y];
        x = p.first;
        y = p.second;
    }
    path.push_back({sx, sy});
    reverse(path.begin(), path.end());

    cout << "Evacuation Path:\n";
    for (auto &p : path)
        cout << "(" << p.first << "," << p.second << ") ";

    return 0;
}
