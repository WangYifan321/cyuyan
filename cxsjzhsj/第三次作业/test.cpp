#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
using namespace std;
struct coordinate {
    int y,x;
    //coordinate(int y = 0, int x = 0) : y(y), x(x) {}
};

const coordinate operator+ (const coordinate &a, const coordinate &b) {
    coordinate temp;
    temp.x = a.x + b.x;
    temp.y = a.y + b.y;
    return temp;
}

class Solve {

public:
    coordinate di[4] = {1,0,-1,0,0,1,0,-1};
    vector<vector<int>> map;
    vector<vector<bool>> vis;
    int count;
    int y, x;
    
    void init(istream &in) {
        in>>y>>x;
        map = vector<vector<int>> (y, vector<int> (x));
        vis = vector<vector<bool>> (y, vector<bool> (x));
        for (size_t i = 0; i < y; i++) {
            for (size_t j = 0; j < x; j++) {
                in>>map[i][j];
            }
        }
        count = 0;
    }
    int res(void (Solve::*fp)(const coordinate &now)) {
        for(int i = 0; i < y; i++) 
            for(int j = 0; j < x; j++) {
                if(!vis[i][j]) {
                    count++;
                    (this->*fp)({i,j});
                }
            }
        return count;
    }
    //pta不能函数指针
    int res2() {
    for(int i = 0; i < y; i++) 
        for(int j = 0; j < x; j++) {
            if(!vis[i][j]) {
                count++;
                dfs({i,j});
            }
        }
    return count;
    }
    bool legitimate(const coordinate &now) { return now.x < x && now.x >= 0 && now.y < y && now.y >= 0 && !vis[now.y][now.x]; }
    void dfs(const coordinate &now);
    void bfs(const coordinate &now);
};



void Solve::dfs(const coordinate &now) {
    vis[now.y][now.x] = true;
    for (size_t i = 0; i < 4; i++) {
        coordinate temp = now + di[i];
        if(legitimate(temp) && map[now.y][now.x] == map[temp.y][temp.x])
            dfs(temp);
    }
}

void Solve::bfs(const coordinate &now) {
    queue<coordinate> q;
    q.push(now);
    while(!q.empty()) {
        coordinate top = q.front();
        q.pop();
        vis[top.y][top.x] = true;
        coordinate temp;
        for(size_t i = 0; i < 4; i++) {
            temp = top + di[i];
            if(legitimate(temp) && map[top.y][top.x] == map[temp.y][temp.x]) {
                q.push(temp);
            }
        }
    }
}

int main() {
    int x, y;
    Solve solve;
    // ifstream in;
    // in.open("C:\\ProgrammingPractice\\test\\Random number\\week2_B.in");
    solve.init(cin);
    //solve.res(Solve::dfs);
    cout<<solve.res2()<<endl;
    //in.close();
    return 0;
}