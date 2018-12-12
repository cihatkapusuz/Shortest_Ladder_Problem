#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <functional>
#include <queue>

struct Node{
public:
    int a;
    int b;
    int diff;
    Node(int _a, int _b, int _diff){
        this->a =_a;
        this->b =_b;
        this->diff =_diff;
    }
    bool operator<(Node other) const
    {
        return diff>other.diff;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }
    using namespace std;
    ifstream infile(argv[1]);
    string line;
    getline(infile, line);
    stringstream stream(line);
    int x;
    stream >> x;
    int y;
    stream >> y;
    int grid [x][y];
    int visited [x][y];
    for(int i=0; i<y; i++ ) {
        getline(infile, line);
        stringstream stream2(line);
        for (int j = 0; j < x; j++) {
            stream2 >> grid[i][j];
            visited[i][j]=0;
        }
    }
    int n_of_questioning;
    getline(infile, line);
    stringstream stream3(line);
    stream3 >> n_of_questioning;
    int x1;
    int y1;
    getline(infile, line);
    stringstream stream4(line);
    stream4 >> y1;
    stream4 >> x1;
    int x2;
    int y2;
    stream4 >> y2;
    stream4 >> x2;
    y1=y1-1;
    x1=x1-1;
    y2=y2-1;
    x2=x2-1;
    priority_queue<Node> path;
    if(x1<x-1){
        path.push(Node(y1,x1+1,abs(grid[y1][x1]-grid[y1][x1+1])));
    }
    if(x1>0){
        path.push(Node(y1,x1-1,abs(grid[y1][x1]-grid[y1][x1-1])));
    }
    if(y1<y-1){
        path.push(Node(y1+1,x1,abs(grid[y1][x1]-grid[y1+1][x1])));
    }
    if(y1>0){
        path.push(Node(y1-1,x1,abs(grid[y1][x1]-grid[y1-1][x1])));
    }
    visited[x1][y1]=1;
    int mx=-1;
    int xf= x1;
    int yf= y1;
    while(xf!=x2 || yf!=y2){
        while(visited [path.top().a][path.top().b]==1){
            path.pop();
        }
        Node taken = path.top();
        path.pop();
        mx=max(mx,taken.diff);
        visited[taken.a][taken.b]=1;
        if(taken.b<x-1){
            path.push(Node(taken.a,taken.b+1,abs(grid[taken.a][taken.b]-grid[taken.a][taken.b+1])));
        }
        if(taken.b>0){
            path.push(Node(taken.a,taken.b-1,abs(grid[taken.a][taken.b]-grid[taken.a][taken.b-1])));
        }
        if(taken.a<y-1){
            path.push(Node(taken.a+1,taken.b,abs(grid[taken.a][taken.b]-grid[taken.a+1][taken.b])));
        }
        if(taken.a>0){
            path.push(Node(taken.a-1,taken.b,abs(grid[taken.a][taken.b]-grid[taken.a-1][taken.b])));
        }
        xf=taken.b;
        yf=taken.a;
    }
  ofstream myfile;
    myfile.open(argv[2]);
    myfile << mx << endl;
}
