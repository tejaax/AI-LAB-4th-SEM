#include<bits/stdc++.h>
using namespace std;

#define M 200000

string q[M];
int front=0,rear=0;

unordered_set<string> visited;

int dx[4]={0,0,1,-1};
int dy[4]={-1,1,0,0};

int bfs(string start,string goal){
    front=rear=0;
    visited.clear();
    q[rear++]=start;
    visited.insert(start);
    int explored=0;
    while(front<rear){
        string cur=q[front++];
        explored++;

        if(cur==goal) return explored;
        int pos=cur.find('0');
        int x=pos/3,y=pos%3;

        for(int i=0;i<4;i++){
            int nx=x+dx[i],ny=y+dy[i];
            if(nx>=0&&nx<3&&ny>=0&&ny<3){
                string next=cur;
                swap(next[x*3+y],next[nx*3+ny]);
                if(!visited.count(next)){
                    visited.insert(next);
                    q[rear++]=next;
                }
            }
        }
    }
    return explored;
}

int main(){
    string start="724506831";
    string goal="012345678";
    cout<<"States explored using BFS: "<<bfs(start,goal);
    return 0;
}
