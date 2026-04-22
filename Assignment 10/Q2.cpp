#include <bits/stdc++.h>
using namespace std;

// State = (location, A status, B status)
struct State {
    string loc, A, B;

    bool operator==(const State &other) const {
        return loc == other.loc && A == other.A && B == other.B;
    }
};

// For using State in set/vector search
bool contains(vector<State> &path, State s) {
    for (auto &p : path) {
        if (p == s) return true;
    }
    return false;
}

// Goal test
bool is_goal(State s) {
    return s.A == "Clean" && s.B == "Clean";
}

// Possible actions
vector<string> actions() {
    return {"Suck", "Left", "Right"};
}

// Result function (non-deterministic)
vector<State> results(State s, string action) {
    vector<State> res;

    if (action == "Suck") {
        if (s.loc == "A") {
            if (s.A == "Dirty") {
                res.push_back({"A", "Clean", s.B});
                res.push_back({"A", "Clean", "Clean"});
            } else {
                res.push_back({"A", "Clean", s.B});
                res.push_back({"A", "Dirty", s.B});
            }
        } else {
            if (s.B == "Dirty") {
                res.push_back({"B", s.A, "Clean"});
                res.push_back({"B", "Clean", "Clean"});
            } else {
                res.push_back({"B", s.A, "Clean"});
                res.push_back({"B", s.A, "Dirty"});
            }
        }
    }
    else if (action == "Left") {
        res.push_back({"A", s.A, s.B});
    }
    else if (action == "Right") {
        res.push_back({"B", s.A, s.B});
    }

    return res;
}

// AND-OR Search
// Returns pointer to plan (vector<string>) or nullptr
vector<string>* and_or_search(State state, vector<State> path) {
    if (is_goal(state)) {
        return new vector<string>(); // empty plan
    }

    if (contains(path, state)) {
        return nullptr;
    }

    for (string action : actions()) {
        vector<State> result_states = results(state, action);

        vector<string> plan;
        bool success = true;

        for (auto &s : result_states) {
            vector<State> new_path = path;
            new_path.push_back(state);

            vector<string>* subplan = and_or_search(s, new_path);

            if (subplan == nullptr) {
                success = false;
                break;
            }

            // Append subplan
            plan.insert(plan.end(), subplan->begin(), subplan->end());
        }

        if (success) {
            vector<string>* final_plan = new vector<string>();
            final_plan->push_back(action);
            final_plan->insert(final_plan->end(), plan.begin(), plan.end());
            return final_plan;
        }
    }

    return nullptr;
}

int main() {
    State start = {"B", "Dirty", "Dirty"};

    vector<State> path;

    vector<string>* plan = and_or_search(start, path);

    cout << "Plan:\n";

    if (plan == nullptr) {
        cout << "No solution\n";
    } else {
        for (auto &step : *plan) {
            cout << step << " ";
        }
        cout << endl;
    }

    return 0;
}