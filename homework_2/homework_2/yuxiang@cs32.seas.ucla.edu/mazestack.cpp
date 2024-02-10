#include <string>
#include <stack>
#include <iostream>

using namespace std;

class Coord
{
public:
    Coord(int r, int c) : m_r(r), m_c(c) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    stack<Coord> coordStack;
    coordStack.push(Coord(sr,sc));
    maze[sr][sc] = 'X';

    while(!coordStack.empty()) {
        Coord cur = coordStack.top();
        maze[cur.r()][cur.c()] = 'X';
        coordStack.pop();

        if(cur.r() == er && cur.c() == ec) {
            return true;
        }

        if(maze[cur.r() - 1][cur.c()] == '.') {
            coordStack.push(Coord(cur.r() - 1, cur.c()));
        }
        if(maze[cur.r()][cur.c() - 1] == '.') {
            coordStack.push(Coord(cur.r(), cur.c() - 1));
        }
        if(maze[cur.r() + 1][cur.c()] == '.') {
            coordStack.push(Coord(cur.r() + 1, cur.c()));
        }
        if(maze[cur.r()][cur.c() + 1] == '.') {
            coordStack.push(Coord(cur.r(), cur.c() + 1));
        }
    }

    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XXXXX.X.XX",
        "X...X.X..X",
        "X.X...X..X",
        "X.XXX.XXXX",
        "XXX....X.X",
        "X.XX.XXX.X",
        "X....X...X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10,10, 6,5, 1,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
