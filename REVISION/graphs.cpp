#include <bits/stdc++.h>
using namespace std;



// LC 994 - rotten oranges
int solve(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    queue<pair<int, int>> q;
    int freshOranges = 0;

    // Initialize the queue with all the rotten oranges and count fresh oranges
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 2) {
                q.push({i, j});
            } else if (grid[i][j] == 1) {
                freshOranges++;
            }
        }
    }

    if (freshOranges == 0) return 0; 

    int minutes = 0;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty()) {
        int qSize = q.size();
        bool hasNewRotten = false;

        for (int i = 0; i < qSize; i++) {
            auto [x, y] = q.front();
            q.pop();

            for (auto& d : directions) {
                int newX = x + d.first;
                int newY = y + d.second;

                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY] == 1) {
                    grid[newX][newY] = 2;
                    freshOranges--;
                    q.push({newX, newY});
                    hasNewRotten = true;
                }
            }
        }

        if (hasNewRotten) {
            minutes++;
        }
    }

    return freshOranges == 0 ? minutes : -1;
}
int orangesRotting(vector<vector<int>>& grid) {
    return solve(grid);
}