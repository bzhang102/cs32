#include <iostream>

#include "History.h"
#include "globals.h"

using namespace std;

History::History(int nRows, int nCols) {
    m_rows = nRows;
    m_cols = nCols;
    for (int r = 0; r < nRows; r++)
    {
        for (int c = 0; c < nCols; c++)
            m_data[r][c] = 0;
    }
}

bool History::record(int r, int c) {
    // Check for a valid location
    if(r < 1 || r > m_rows || c < 1 || c > m_cols) {
        return false;
    }

    m_data[r - 1][c - 1]++;
    return true;
}

void History::display() const
{
    char grid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill the grid with dots
    for (r = 0; r < m_rows; r++) {
        for (c = 0; c < m_cols; c++) {
            if(m_data[r][c] == 0) {
                grid[r][c] = '.';
            } else if (m_data[r][c] < 26) {
                grid[r][c] = 'A' + m_data[r][c] - 1;
            } else {
                grid[r][c] = 'Z';
            }
        }
    }

    // Draw the grid
    clearScreen();
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++) {
            cout << grid[r][c];
        }
        cout << endl;
    }
    cout << endl;
}

