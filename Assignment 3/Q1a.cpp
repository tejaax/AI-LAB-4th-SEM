#include <bits/stdc++.h>
using namespace std;

char move(char loc, string action) {
    if (loc == 'A' && action == "Move Right") return 'B';
    if (loc == 'B' && action == "Move Left")  return 'A';
    if (loc == 'B' && action == "Move Right") return 'C';
    if (loc == 'C' && action == "Move Left")  return 'B';
    return loc;
}

int main() {
    map<char, string> rooms;
    rooms['A'] = "Dirt";
    rooms['B'] = "Dirt";
    rooms['C'] = "Dirt";

    set<char> cleanVisited;

    char location = 'A';

    cout << "Percept\t\tAction\t\tLocation\n";
    cout << "------------------------------------------\n";

    for (int i = 0; i < 7; i++) {
        string status = rooms[location];
        string action;
        if (status == "Dirt") {
            action = "Remove";
            rooms[location] = "No Dirt";
            cleanVisited.insert(location);
        }
        else {
            if (location == 'A') {
                action = "Move Right";
            }
            else if (location == 'C') {
                action = "Move Left";
            }
            else if (location == 'B') {
                if (cleanVisited.count('A') == 0)
                    action = "Move Left";
                else if (cleanVisited.count('C') == 0)
                    action = "Move Right";
                else
                    action = "No Op"; 
            }
        }

        cout << "(" << location << "," << status << ")\t"
             << action << "\t\t" << location << endl;

        if (action == "Move Left" || action == "Move Right") {
            location = move(location, action);
        }
    }
    return 0;
}
