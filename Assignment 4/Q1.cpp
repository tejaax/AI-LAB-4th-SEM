#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

vector<string> cities = {
    "Chicago","Detroit","Cleveland","Indianapolis","Columbus",
    "Pittsburgh","Buffalo","Syracuse","New York",
    "Philadelphia","Baltimore","Boston","Providence","Portland"
};

int n = 14;

int adj[14][14];

struct Node {
    int state;        
    Node* parent;       
    int path_cost;      

    Node(int s, Node* p = nullptr, int c = 0) {
        state = s;
        parent = p;
        path_cost = c;
    }
};


struct PriorityQueue {
    vector<Node*> data;

    int f(Node* node) {
        return node->path_cost;  
    }

    void add(Node* node) {
        data.push_back(node);
        sort(data.begin(), data.end(),
             [&](Node* a, Node* b) {
                return f(a) < f(b);
             });
    }

    Node* pop() {
        Node* best = data.front();
        data.erase(data.begin());
        return best;
    }

    bool is_empty() {
        return data.empty();
    }
};


struct Problem {
    int INITIAL;
    int goal;

    Problem(int i, int g) {
        INITIAL = i;
        goal = g;
    }

    bool is_goal(int state) {
        return state == goal;
    }

    vector<int> ACTIONS(int state) {
        vector<int> actions;
        for (int i = 0; i < n; i++) {
            if (adj[state][i] != 0)
                actions.push_back(i);
        }
        return actions;
    }

    int RESULT(int state, int action) {
        return action;
    }

    int ACTION_COST(int s, int s_prime) {
        return adj[s][s_prime];
    }
};


vector<Node*> EXPAND(Problem& problem, Node* node) {
    vector<Node*> children;

    for (int action : problem.ACTIONS(node->state)) {
        int cost = node->path_cost + problem.ACTION_COST(node->state, action);
        Node* child = new Node(action, node, cost);
        children.push_back(child);
    }
    return children;
}


pair<Node*, int> BEST_FIRST_SEARCH(Problem& problem) {

    Node* node = new Node(problem.INITIAL);

    PriorityQueue frontier;
    frontier.add(node);

    unordered_map<int, Node*> reached;
    reached[problem.INITIAL] = node;

    int explored = 0;

    while (!frontier.is_empty()) {
        node = frontier.pop();
        explored++;

        if (problem.is_goal(node->state)) {
            return {node, explored};
        }

        for (Node* child : EXPAND(problem, node)) {
            int s = child->state;
            if (!reached.count(s) || child->path_cost < reached[s]->path_cost) {
                reached[s] = child;
                frontier.add(child);
            }
        }
    }

    return {nullptr, explored};
}


vector<string> get_path(Node* node) {
    vector<string> path;
    while (node) {
        path.push_back(cities[node->state]);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}


int main() {

    memset(adj, 0, sizeof(adj));

    vector<tuple<int,int,int>> edges = {
        {0,1,283},{0,2,345},{0,3,182},
        {1,2,169},{1,6,256},
        {2,6,189},{2,5,134},{2,4,144},
        {3,4,176},
        {4,5,185},
        {5,6,215},{5,9,305},{5,10,247},
        {6,7,150},
        {7,8,254},{7,11,312},
        {8,9,97},{8,12,181},
        {9,10,101},{9,11,215},
        {11,12,50},{11,13,107}
    };

    for (auto [u,v,w] : edges) {
        adj[u][v] = w;
        adj[v][u] = w;
    }

    int start = 7;  // Syracuse
    int goal  = 0;  // Chicago

    Problem problem(start, goal);

    auto [solution, explored] = BEST_FIRST_SEARCH(problem);

    cout << "Best First Search Path:\n";
    vector<string> path = get_path(solution);
    for (auto& c : path)
        cout << c << " -> ";
    cout << "END\n";

    cout << "Total cost: " << solution->path_cost << "\n";
    cout << "Number of paths explored: " << explored << "\n";

    return 0;
}
