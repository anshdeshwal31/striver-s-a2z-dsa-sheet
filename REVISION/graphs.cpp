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
            int x = q.front().first;
            int y = q.front().second;
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


// LC 542 - 01 matrix
    // // brute force  
    // int solve(int row, int col, vector<vector<int>>& mat) {
    //     // using bfs traversal
    //     vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // up, right, down, left
    //     queue<pair<int, int>> q;
    //     q.push({row, col});

    //     // Change: Added a visited matrix to avoid revisiting
    //     vector<vector<bool>> visited(mat.size(), vector<bool>(mat[0].size(), false));
    //     visited[row][col] = true;

    //     int k = 0;
    //     while (!q.empty()) {
    //         int size = q.size();

    //         for (int i = 0; i < size; i++) {
    //             auto top = q.front();
    //             q.pop();
    //             int x = top.first;
    //             int y = top.second;

    //             // Check if current cell is 0
    //             if (mat[x][y] == 0) {
    //                 return k;  // return distance if zero is found
    //             }

    //             // Traverse in four directions
    //             for (auto d : dir) {
    //                 int newX = x + d[0];
    //                 int newY = y + d[1];
                    
    //                 // Change: Added condition to avoid revisiting cells
    //                 if (newX >= 0 && newX < mat.size() && newY >= 0 && newY < mat[0].size() && !visited[newX][newY]) {
    //                     q.push({newX, newY});
    //                     visited[newX][newY] = true;
    //                 }
    //             }
    //         }
    //         k++;  // Increase distance after checking one level of BFS
    //     }

    //     return -1;
    // }

    // vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    //     int n = mat.size();
    //     int m = mat[0].size();
    //     vector<vector<int>> res(n, vector<int>(m, 0));

    //     for (int i = 0; i < n; i++) {
    //         for (int j = 0; j < m; j++) {
    //             if (mat[i][j] != 0) {
    //                 // Change: Initialize distance as large value instead of 0
    //                 res[i][j] = solve(i, j, mat);
    //             }
    //         }
    //     }

    //     return res;
    // }


    // optimised solution 

    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> result(m, vector<int>(n, INT_MAX)); // Initialize result matrix
        queue<pair<int, int>> q;  // Queue to store coordinates for BFS
        
        // Initialize queue with all 0's and set their distance to 0
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 0) {
                    result[i][j] = 0;
                    q.push({i, j});  // Add all '0' positions to the queue
                }
            }
        }
    
        // Direction vectors for moving up, down, left, and right
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // Perform BFS
        while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
    
            for (auto dir : directions) {
                int newX = x + dir.first;
                int newY = y + dir.second;
                
                // If the new position is within bounds and we found a shorter distance
                if (newX >= 0 && newX < m && newY >= 0 && newY < n) {
                    if (result[newX][newY] > result[x][y] + 1) {
                        result[newX][newY] = result[x][y] + 1;  // Update distance
                        q.push({newX, newY});  // Add the new position to the queue
                    }
                }
            }
        }
    
        return result;
    }


    
    
    // number of distinct islands - https://www.geeksforgeeks.org/problems/number-of-distinct-islands/1
    void dfs(int i, int j, vector<vector<int>>& grid, vector<vector<bool>>& visited, string& path, string dir) {
        int n = grid.size(), m = grid[0].size();
        if (i < 0 || j < 0 || i >= n || j >= m || visited[i][j] || grid[i][j] == 0) return;

        visited[i][j] = true;
        path += dir;

        dfs(i+1, j, grid, visited, path, "D"); // down
        dfs(i-1, j, grid, visited, path, "U"); // up
        dfs(i, j+1, grid, visited, path, "R"); // right
        dfs(i, j-1, grid, visited, path, "L"); // left

        path += "B"; // backtrack
    }

    int countDistinctIslands(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        set<string> uniqueIslands;
        vector<vector<bool>> visited(n, vector<bool>(m, false));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!visited[i][j] && grid[i][j] == 1) {
                    string path = "";
                    dfs(i, j, grid, visited, path, ""); 
                    uniqueIslands.insert(path);
                }
            }
        }

        return uniqueIslands.size();
    }


    
    // LC 802. Find Eventual Safe States
    
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> revGraph(n);
        vector<int> indegree(n, 0);

        // Step 1: Build reverse graph and count indegrees
        for (int u = 0; u < n; ++u) {
            for (int v : graph[u]) {
                revGraph[v].push_back(u); 
                indegree[u]++;            // original outdegree becomes indegree
            }
        }

        // Step 2: Queue all nodes with 0 indegree (terminal nodes)
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> safe;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            safe.push_back(node);
            for (int neighbor : revGraph[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        sort(safe.begin(), safe.end());
        return safe;
    }