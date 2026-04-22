#include<bits/stdc++.h>
using namespace std;

unordered_set<string> visited;
string goal="012345678";
int explored=0;
bool found=false;

int dx[4]={0,0,1,-1};
int dy[4]={-1,1,0,0};

void dfs(string cur,int depth,int limit){
    if(found || depth>limit) return;

    explored++;
    if(cur==goal){
        found=true;
        return;
    }

    visited.insert(cur);

    int pos=cur.find('0');
    int x=pos/3,y=pos%3;

    for(int i=0;i<4;i++){
        int nx=x+dx[i],ny=y+dy[i];
        if(nx>=0&&nx<3&&ny>=0&&ny<3){
            string next=cur;
            swap(next[x*3+y],next[nx*3+ny]);
            if(!visited.count(next)){
                dfs(next,depth+1,limit);
            }
        }
    }                                                                                                   visited.erase(cur);
}

int main(){
    string start="724506831";
    dfs(start,0,20);
    cout<<"States explored using DFS: "<<explored;
    return 0;
}
