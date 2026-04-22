#include<bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> graph;

void addFriend(string u, string v){
    graph[u].push_back(v);
}

void BFS(string start){
    unordered_set<string> vis;
    queue<string> q;
    q.push(start);
    vis.insert(start);

    while(!q.empty()){
        string cur = q.front();
        q.pop();
        for(string nxt : graph[cur]){
            if(!vis.count(nxt)){
                vis.insert(nxt);
                q.push(nxt);
                cout << cur << " -> " << nxt << endl;
            }
        }
    }
}

void DFS(string u, unordered_set<string>& vis){
    vis.insert(u);
    for(string v : graph[u]){
        if(!vis.count(v)){
            cout << u << " -> " << v << endl;
            DFS(v, vis);
        }
    }
}

int main(){

    addFriend("Priya","Raj");
    addFriend("Priya","Aarav");

    addFriend("Raj","Sunil");
    addFriend("Raj","Neha1");

    addFriend("Neha1","Akash");
    addFriend("Neha1","Sneha");
    addFriend("Neha1","Arnav");
    addFriend("Neha1","Raj");


    addFriend("Sunil","Akash");
    addFriend("Sunil","Sneha");
    addFriend("Sunil","Raj");
    addFriend("Sunil","Maya");

    addFriend("Akash","Sunil");
    addFriend("Akash","Priya");


    addFriend("Aarav","Neha1");
    addFriend("Aarav","Neha2");
    addFriend("Aarav","Arjun1");


    addFriend("Sneha","Neha1");
    addFriend("Sneha","Rahul");
    addFriend("Sneha","Maya");
    addFriend("Sneha","Sunil");


    addFriend("Neha2","Neha1");
    addFriend("Neha2","Rahul");
    addFriend("Neha2","Priya");
    addFriend("Neha2","Arnav");


    addFriend("Arjun1","Aarav");
    addFriend("Arjun1","Neha");


    addFriend("Rahul","Arjun2");
    addFriend("Rahul","Maya");
    addFriend("Rahul","Sneha");
    addFriend("Rahul","Pooja");
    addFriend("Rahul","Neha1");


    addFriend("Maya","Arjun2");
    addFriend("Maya","Rahul");
    addFriend("Maya","Sunil");


    addFriend("Arjun2","Pooja");
    addFriend("Arjun2","Maya");
    addFriend("Arjun2","Rahul");

    addFriend("Pooja","Arjun2");
    addFriend("Pooja","Arjun1");
    addFriend("Pooja","Rahul");


    cout << "BFS Tree from Sneha\n";
    BFS("Priya");

    cout << "\nDFS Tree from Sneha\n";
    unordered_set<string> vis;
    DFS("Priya", vis);

    return 0;
}
