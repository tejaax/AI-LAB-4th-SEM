#include <bits/stdc++.h>
using namespace std;

vector<string> railwayAgent(
    string emergencyMode,
    string trainIn,
    string trainOut,
    string obstacleState
) {
    if (emergencyMode == "Active")
        return {"Lower", "On", "Red"};

    if (obstacleState == "Blocked")
        return {"Lower", "On", "Red"};

    if (trainIn == "Detected" || trainOut == "Detected")
        return {"Lower", "On", "Green"};

    return {"Raise", "Off", "Green"};
}

int main() {

    vector<vector<string>> testCases = {
        {"Neutral","Detected","NotDetected","Clear"},
        {"Neutral","NotDetected","NotDetected","Blocked"},
        {"Active","NotDetected","NotDetected","Clear"},
        {"Neutral","NotDetected","NotDetected","Clear"}
    };

    cout << "Percepts\t\t\t\tAction (Gate, Hooter, Signal)\n";
    cout << "------------------------------------------------------------------\n";

    for (auto &p : testCases) {
        vector<string> action = railwayAgent(p[0], p[1], p[2], p[3]);

        cout << "("
             << p[0] << ", "
             << p[1] << ", "
             << p[2] << ", "
             << p[3] << ")\t("
             << action[0] << ", "
             << action[1] << ", "
             << action[2] << ")\n";
    }

    return 0;
}
