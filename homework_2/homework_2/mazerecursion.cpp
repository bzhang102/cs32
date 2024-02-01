//#include <string>
//#include <stack>
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
//bool dfs(string maze[], int r, int c, int er, int ec) {
//    maze[r][c] = 'X';
//
//    if(r == er && c == ec) {
//        return true;
//    }
//
//    return (maze[r][c + 1] == '.' && dfs(maze, r, c + 1, er, ec)) ||
//            (maze[r + 1][c] == '.' && dfs(maze, r + 1, c, er ,ec)) ||
//            (maze[r][c - 1] == '.' && dfs(maze, r, c - 1, er ,ec)) ||
//            (maze[r - 1][c] == '.' && dfs(maze, r - 1, c, er ,ec));
//}
//
//bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
//    return dfs(maze, sr, sc, er, ec);
//}
