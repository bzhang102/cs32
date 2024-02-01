//#include <string>
//#include <queue>
//
//using namespace std;
//
//class Coord
//{
//public:
//    Coord(int r, int c) : m_r(r), m_c(c) {}
//    int r() const { return m_r; }
//    int c() const { return m_c; }
//private:
//    int m_r;
//    int m_c;
//};
//
//
//bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
//    queue<Coord> coordQueue;
//    coordQueue.push(Coord(sr,sc));
//    maze[sr][sc] = 'X';
//
//    while(!coordQueue.empty()) {
//        Coord cur = coordQueue.front();
//        maze[cur.r()][cur.c()] = 'X';
//        coordQueue.pop();
//
//        if(cur.r() == er && cur.c() == ec) {
//            return true;
//        }
//
//        if(maze[cur.r() - 1][cur.c()] == '.') {
//            coordQueue.push(Coord(cur.r() - 1, cur.c()));
//        }
//        if(maze[cur.r()][cur.c() - 1] == '.') {
//            coordQueue.push(Coord(cur.r(), cur.c() - 1));
//        }
//        if(maze[cur.r() + 1][cur.c()] == '.') {
//            coordQueue.push(Coord(cur.r() + 1, cur.c()));
//        }
//        if(maze[cur.r()][cur.c() + 1] == '.') {
//            coordQueue.push(Coord(cur.r(), cur.c() + 1));
//        }
//    }
//
//    return false;
//}
