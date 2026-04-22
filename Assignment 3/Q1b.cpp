#include <bits/stdc++.h>
using namespace std;

set<char> cleanVisited;

string vacuum_agent(char location, string status) {

    // If dirt is present → clean
    if (status == "Dirt") {
        cleanVisited.insert(location);
        return "Remove";
    }
    // If no dirt, decide movement intelligently
    if (location == 'A')
        return "Move Right";

    if (location == 'C')
        return "Move Left";

    if (location == 'B') {
        // Go only to unclean rooms
        if (cleanVisited.count('A') == 0)
            return "Move Left";
        else if (cleanVisited.count('C') == 0)
            return "Move Right";
        else
            return "NoOp";   // all rooms clean
    }

    return "";
}

int main() {
    srand(time(0));

    int steps;
    cout << "Enter number of percepts: ";
    cin >> steps;

    cout << "\nPercept\t\tAction\n";
    cout << "------------------------------\n";

    for (int i = 0; i < steps; i++) {
        char location;
        string status;

        cout << "Enter Location (A/B/C): ";
        cin >> location;

        cout << "Enter Status (Dirt/NoDirt): ";
        cin >> status;

        string action = vacuum_agent(location, status);

        cout << "(" << location << ", " << status << ")\t"
             << action << endl;
    }

    return 0;
}
