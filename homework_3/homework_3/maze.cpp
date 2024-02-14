class Coord {
public:
    Coord(int r, int c) : m_r(r), m_c(c) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    maze[sr][sc] = 'X';
    if(sr == er && sc == ec) return true;
    return (maze[sr][sc + 1] == '.' && pathExists(maze, nRows, nCols, sr, sc + 1, er, ec)) ||
            (maze[sr + 1][sc] == '.' && pathExists(maze, nRows, nCols, sr + 1, sc, er ,ec)) ||
            (maze[sr][sc - 1] == '.' && pathExists(maze, nRows, nCols, sr, sc - 1, er ,ec)) ||
            (maze[sr - 1][sc] == '.' && pathExists(maze, nRows, nCols, sr - 1, sc, er ,ec));
}
