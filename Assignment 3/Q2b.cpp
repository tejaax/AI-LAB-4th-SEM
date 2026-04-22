#include <bits/stdc++.h>
using namespace std;

vector<string> railwayAgent(
    string emergencyStatus,
    string inboundTrain,
    string outboundTrain,
    string obstacleFlag
) {
    if (emergencyStatus == "Active")
        return {"Lower", "On", "Red"};

    if (obstacleFlag == "Blocked")
        return {"Lower", "On", "Red"};

    if (inboundTrain == "Detected" || outboundTrain == "Detected")
        return {"Lower", "On", "Green"};

    return {"Raise", "Off", "Green"};
}


int main() {

    int steps;
    cout << "Enter number of percepts: ";
    cin >> steps;

    cout << "\nPercepts\t\t\t\tAction (Gate, Hooter, Signal)\n";
    cout << "------------------------------------------------------------------\n";

    for (int i = 0; i < steps; i++) {
        string emergencyStatus, inboundTrain, outboundTrain, obstacleFlag;

        cout << "Manual Emergency (Active/Neutral): ";
        cin >> emergencyStatus;

        cout << "Train Inbound (Detected/NotDetected): ";
        cin >> inboundTrain;

        cout << "Train Outbound (Detected/NotDetected): ";
        cin >> outboundTrain;

        cout << "Obstacle Sensor (Blocked/Clear): ";
        cin >> obstacleFlag;

        vector<string> action = railwayAgent(
            emergencyStatus, inboundTrain, outboundTrain, obstacleFlag
        );

        cout << "(" << emergencyStatus << ", "
             << inboundTrain << ", "
             << outboundTrain << ", "
             << obstacleFlag << ")\t("
             << action[0] << ", "
             << action[1] << ", "
             << action[2] << ")\n\n";
    }

    return 0;
}
